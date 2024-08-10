#include "CameraController.h"

#include <iostream>

CameraController::CameraController()
{
    

}

void CameraController::Create()
{
    projectionSize =
    {
        Alexio::Engine::GetInstance()->GetWindow()->GetProjectionWidth(),
        Alexio::Engine::GetInstance()->GetWindow()->GetProjectionHeight()
    };

    speed = { 0.0f, 0.0f };
    position = { 0.0f, -352.0f };
}

void CameraController::Update(Player& player, const Alexio::Vector2& actSize)
{
    focalPoint = Alexio::Vector2(projectionSize.x / 2.0f - position.x, (projectionSize.y / 2.0f - position.y));

    offset = player.position - focalPoint;

    if (offset.x >= 8.0f)
        position.x = -player.position.x + 220.0f;
    else if (offset.x <= -8.0f)
        position.x = -player.position.x + 204.0f;

    if (player.state == PlayerStates::AIRBORNE)
    {
        if (offset.y < -32.0f)
        {
            position.y = -player.position.y + 88.0f;
            offset.y = -32.0f;
        }
        else if (offset.y > 32.0f)
        {
            position.y = -player.position.y + 152.0f;
            offset.y = 32.0f;
        }
    }
    else if (player.state == PlayerStates::ROLLING)
    {
        position.y = -player.position.y + 126.0f;
    }
    else if (player.state == PlayerStates::NORMAL)
    {
        if (speed.y != 0.0f)
        {
            if (offset.y <= speed.y)
            {
                offset.y = 0.0f;
                speed.y = 0.0f;
            }
            position.y -= speed.y;
        }
        else if (player.lookState == PlayerLookStates::NORMAL)
            position.y = -player.position.y + 120.0f;
    }

    if (position.x >= 0.0f)
        position.x = 0.0f;
    else if (position.x <= (actSize.x - projectionSize.x) * -1.0f)
        position.x = (actSize.x - projectionSize.x) * -1.0f;
    
    if (position.y >= 0.0f)
        position.y = 0.0f;
    else if (position.y <= (actSize.y - projectionSize.y) * -1.0f)
        position.y = (actSize.y - projectionSize.y) * -1.0f;

    Alexio::Engine::GetInstance()->GetCamera()->SetPosition(Alexio::Vector2(position.x, position.y - player.GetLookUpAndDownCameraShiftOffset()));
}

void CameraController::DrawBorders()
{
    float leftBorder = projectionSize.x / 2.0f - 8.0f;
    float rightBorder = projectionSize.x / 2.0f + 8.0f;
    float topBorder = projectionSize.y / 2.0f - 32.0f;
    float bottomBorder = projectionSize.y / 2.0f + 32.0f;

    Alexio::Renderer::DrawQuad(Alexio::Vector2(leftBorder, topBorder) - position, Alexio::Vector2(16.0f, 1.0f));
    Alexio::Renderer::DrawQuad(Alexio::Vector2(leftBorder, topBorder) - position, Alexio::Vector2(1.0f, 64.0f));
    Alexio::Renderer::DrawQuad(Alexio::Vector2(rightBorder, topBorder) - position, Alexio::Vector2(1.0f, 64.0f));
    Alexio::Renderer::DrawQuad(Alexio::Vector2(leftBorder, bottomBorder) - position, Alexio::Vector2(17.0f, 1.0f));

    Alexio::Renderer::DrawQuad(Alexio::Vector2(leftBorder, topBorder + 32.0f) - position, Alexio::Vector2(17.0f, 1.0f), { 0.0f, 1.0f, 0.0f, 1.0f });
}
