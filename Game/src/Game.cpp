#include "Game.h"

#include <iostream>

Game::Game()
{

}

bool Game::OnStart()
{
    currentAct.Load("GHZ_Act_1", "GHZ_Tiles");

    cameraController.Create();

    player = Player(Alexio::Vector2(212.0f, 492.0f), 8, 16, Direction::RIGHT, "assets/images/character/SonicSpriteSheet.png");

	return true;
}

bool Game::OnFixedUpdate()
{
    player.FixedUpdate();

    cameraController.Update(player, currentAct.screenSize);

	return true;
}

bool Game::OnUpdate()
{
    player.Update();

    Alexio::Renderer::Clear(0.0f, 0.8f, 1.0f, 1.0f);

    currentAct.Draw();

    player.Draw();

    OnImGuiRender();
    return !Alexio::Input::KeyPressed(ESCAPE);
}


void Game::OnImGuiRender()
{
    char* apiName = "";
#if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
    apiName = (Alexio::Renderer::GetGraphicsAPI() == OpenGL) ? "OpenGL 4.5" : "DirectX 11";
#elif defined(AIO_API_OPENGL)
    apiName = "OpenGL";
#elif defined(AIO_API_DX11)
    apiName = "DirectX11";
#endif

    ImGui::Begin("App Info");
    ImGui::Text("Graphics API: %s", apiName);
    ImGui::Text("Application Time: %.2f", Alexio::Timer::Get());    
    ImGui::Text("Application framerate: %.3f ms/frame (%.1f FPS)", Alexio::Timer::DetlaTime() * 1000.0f, 1.0f / Alexio::Timer::DetlaTime());
    ImGui::Text("Camera: X: %.6f, Y: %.6f", cameraController.position.x, cameraController.position.y);
    ImGui::End();

    player.OnImGuiRender();
}

int main(int argc, char** agrv)
{
	game.Run("Sonic the Hedgehog", 424, 240, 3, false);
	return 0;
}