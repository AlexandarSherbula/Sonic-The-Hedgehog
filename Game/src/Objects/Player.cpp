#include "Player.h"
#include "Game.h"
#include <iostream>

Player::Player() : MovingObject()
{
    state = PlayerStates::NORMAL;
    lookState = PlayerLookStates::NORMAL;
}

Player::Player(const Alexio::Vector2& position, int widthRad, int heightRad, Direction direction, const std::string& gfxFilePath)
    : MovingObject(position, widthRad, heightRad, direction, gfxFilePath), PlayerAnimation(Alexio::Vector2(48.0f, 48.0f), Alexio::Vector2(0.0f, 0.0f))
{
    mPointA = AnchorPoint({ 0,  1 }, TileSolidity::GROUD_ONLY);
    mPointB = AnchorPoint({ 0,  1 }, TileSolidity::GROUD_ONLY);

    mPointC = AnchorPoint({ 0, -1 }, TileSolidity::SIDE_AND_CEILING);
    mPointD = AnchorPoint({ 0, -1 }, TileSolidity::SIDE_AND_CEILING);

    mPointE = AnchorPoint({ -1,  0 }, TileSolidity::SIDE_AND_CEILING);
    mPointF = AnchorPoint({  1,  0 }, TileSolidity::SIDE_AND_CEILING);

    mPointG = AnchorPoint({ 0,  1 }, TileSolidity::GROUD_ONLY);
 
    mTop = 10.0f;
    mAngle = 0.0f;

    mAcceleration = mFriction = 0.046875f;
    mAirAcceleration = 0.093750f;
    mGravityForce = 0.21875f;
    mDeceleration = 0.5f;
    mJumpForce = 6.5f;

    mRollFrictionSpeed = 0.0234375f;
    mRollDecelerationSpeed = 0.125f;

    mJumped = false;
    mJumpLock = false;

    state = PlayerStates::NORMAL;
    lookState = PlayerLookStates::NORMAL;

    mTimerBeforeCameraShift = 0;
    mLookUpOrDownCameraShift = 0;
}

void Player::Update()
{
    HandleAnimation();
}

void Player::FixedUpdate()
{
    switch (state)
    {
        case PlayerStates::NORMAL:
        {
            ResetLookStateCamera();

            if (game.JumpButtonReleased())
            {
                mJumpLock = false;
            }

            CheckForJump();

            CheckForMovement();

            LookUpOrDown();

            PushSensors();

            if (mAnimationState == PlayerAnimState::PUSHING)
                if ((game.LeftButtonReleased() && mDirection == Direction::LEFT) || (game.RightButtonReleased() && mDirection == Direction::RIGHT))
                    if (state == PlayerStates::NORMAL)
                        SetAnimationState(PlayerAnimState::IDLE);

            UpdateMovement();

            if (mSpeed.y >= 0.0f)
                GroundSensors();
            break;
        }
        case PlayerStates::ROLLING:
        {
            ResetLookStateCamera();

            if (game.JumpButtonReleased())
            {
                mJumpLock = false;
            }

            CheckForJump();

            if (std::abs(mGroundSpeed) > mRollFrictionSpeed + mRollDecelerationSpeed)
            {
                bool oppositeDirectionPressed = (game.LeftButtonHeld() && mDirection == Direction::RIGHT) || (game.RightButtonHeld() && mDirection == Direction::LEFT);

                mGroundSpeed -= (mRollFrictionSpeed + ((oppositeDirectionPressed) ? mRollDecelerationSpeed : 0.0f)) * ((mGroundSpeed > 0.0f) ? 1.0f : -1.0f);
            }
            else
            {
                mGroundSpeed = 0.0f;
                mHitbox.heightRad = 16.0f;
                position.y -= 6.0f;
                state = PlayerStates::NORMAL;
            }

            PushSensors();

            UpdateMovement();

            GroundSensors();

            break;
        }
        case PlayerStates::AIRBORNE:
        {
            ResetLookStateCamera();

            if (mTimerBeforeCameraShift != 0)
                mTimerBeforeCameraShift = 0;

            lookState = PlayerLookStates::NORMAL;
            if (game.JumpButtonReleased())
            {
                if (mSpeed.y < -4.0f)
                    mSpeed.y = -4.0f;
            }

            CheckForMovement();

            AirDrag();

            UpdateMovement();

            ApplyGravity();

            PushSensors();

            if (mSpeed.y < 0.0f)
                CeilingSensors();
            else
                GroundSensors();

            break;
        }
    }
}

bool Player::MoveInCorrectDirection()
{
    return (mGroundSpeed < 0.0f && mDirection == Direction::LEFT && game.LeftButtonHeld()) || (mGroundSpeed > 0.0f && mDirection == Direction::RIGHT && game.RightButtonHeld());
}

void Player::ResetLookStateCamera()
{
    if (mLookUpOrDownCameraShift < 0 && lookState != PlayerLookStates::LOOK_UP)
        mLookUpOrDownCameraShift += 2;

    if (mLookUpOrDownCameraShift > 0 && lookState != PlayerLookStates::LOOK_DOWN)
        mLookUpOrDownCameraShift -= 2;
}

void Player::CheckForJump()
{
    if (game.JumpButtonHeld() && !mJumped && !mJumpLock)
    {
        FindSurface(mPointC);
        FindSurface(mPointD);

        float ceilingDistance = std::max(mPointC.distance, mPointD.distance);

        if (ceilingDistance < -6.5f)
        {
            if (state == PlayerStates::ROLLING)
                position.y -= 6.0f;

            state = PlayerStates::AIRBORNE;

            mSpeed.x -= mJumpForce * sinf(mAngle);
            mSpeed.y -= mJumpForce * cosf(mAngle);
            mAirSpeed = mSpeed.x;
            
            mHitbox.heightRad = 11.0f;

            SetAnimationState(PlayerAnimState::JUMP, { 0, 8 });

            mJumped = true;
            mJumpLock = true;
        }
    }
}

void Player::CheckForMovement()
{
    if (game.LeftButtonHeld() == game.RightButtonHeld() && state != PlayerStates::AIRBORNE)
    {
        mGroundSpeed -= std::min(std::fabs(mGroundSpeed), mFriction) * ((mGroundSpeed > 0.0f) ? 1.0f : -1.0f);
    }
    else
    {
        if (lookState == PlayerLookStates::NORMAL)
        {
            if (game.LeftButtonHeld())
            {
                if (position.x <= 16.0f)
                {
                    mSpeed.x = 0.0f;
                    mAirSpeed = 0.0f;
                    mGroundSpeed = 0.0f;
                    position.x = 16.0f;
                }
                else
                {
                    if (state == PlayerStates::AIRBORNE)
                    {
                        if (mAirSpeed > -mTop)
                        {
                            mDirection = Direction::LEFT;
                            mAirSpeed -= mAirAcceleration;
                            if (mAirSpeed <= -mTop)
                                mAirSpeed = -mTop;
                        }
                    }
                    else
                    {
                        if (mGroundSpeed > 0.0f)
                        {
                            if (mGroundSpeed >= 4.0f)
                            {
                                if (mDirection == Direction::LEFT)
                                    mDirection = Direction::RIGHT;
                                SetAnimationState(PlayerAnimState::SKID, {0, 7});
                            }

                            mGroundSpeed -= mDeceleration;

                            if (mGroundSpeed <= 0)
                            {
                               if (mAnimationState == PlayerAnimState::SKID)
                               {
                                    SetAnimationState(PlayerAnimState::SKID_TURN, { 9, 7 });
                               }

                               mGroundSpeed = -mDeceleration;
                            }
                        }
                        else if (mGroundSpeed > -mTop)
                        {
                            if (mAnimationState != PlayerAnimState::SKID_TURN && mAnimationState != PlayerAnimState::PUSHING)
                            {
                                SetAnimationState(PlayerAnimState::MOVE, {0, 3});
                                mDirection = Direction::LEFT;
                            }
                            mGroundSpeed -= mAcceleration;
                            if (mGroundSpeed <= -mTop)
                                mGroundSpeed = -mTop;
                        }
                    }
                }
            }

            if (game.RightButtonHeld())
            {
                if (state == PlayerStates::AIRBORNE)
                {
                    if (mAirSpeed < mTop)
                    {
                        mDirection = Direction::RIGHT;
                        mAirSpeed += mAirAcceleration;
                        if (mAirSpeed >= mTop)
                            mAirSpeed = mTop;
                    }
                }
                else
                {
                    if (mGroundSpeed < 0.0f)
                    {
                        if (mGroundSpeed <= -4.0f)
                        {
                            if (mDirection == Direction::RIGHT)
                                mDirection = Direction::LEFT;
                            SetAnimationState(PlayerAnimState::SKID, { 0, 7 });
                        }

                        mGroundSpeed += mDeceleration;

                        if (mGroundSpeed >= 0)
                        {
                            if (mAnimationState == PlayerAnimState::SKID)
                                SetAnimationState(PlayerAnimState::SKID_TURN, { 9, 7 });
                            mGroundSpeed = mDeceleration;
                        }
                    }
                    else if (mGroundSpeed < mTop)
                    {
                        if (mAnimationState != PlayerAnimState::SKID_TURN && mAnimationState != PlayerAnimState::PUSHING)
                        {
                            SetAnimationState(PlayerAnimState::MOVE, { 0, 3 });
                            mDirection = Direction::RIGHT;
                        }

                        mGroundSpeed += mAcceleration;
                        if (mGroundSpeed >= mTop)
                            mGroundSpeed = mTop;
                    }
                }
            }
        }
    }
}

void Player::LookUpOrDown()
{
    if (mGroundSpeed == 0.0f)
    {
        if (game.UpButtonReleased() || game.DownButtonReleased())
        {
            if (game.UpButtonReleased() && lookState == PlayerLookStates::LOOK_UP)
            {
                lookState = PlayerLookStates::NORMAL;
                if (mAnimationState == PlayerAnimState::LOOK_UP)
                    SetSubImageUnitPos({ 5, 2 });
            }

            if (game.DownButtonReleased() && lookState == PlayerLookStates::LOOK_DOWN)
            {
                mHitbox.heightRad = 16.0f;
                position.y -= 6.0f;
                lookState = PlayerLookStates::NORMAL;

                if (mAnimationState == PlayerAnimState::LOOK_DOWN)
                    SetSubImageUnitPos({ 11, 2 });

                UpdateSensors();
            }
            mTimerBeforeCameraShift = 0;
        }

        if (game.UpButtonHeld() && lookState != PlayerLookStates::LOOK_DOWN)
        {
            if (lookState == PlayerLookStates::NORMAL)
            {
                lookState = PlayerLookStates::LOOK_UP;
                SetAnimationState(PlayerAnimState::LOOK_UP, { 0, 2 });
            }
            if (mTimerBeforeCameraShift < 60)
                mTimerBeforeCameraShift++;
            else
            {
                if (mLookUpOrDownCameraShift > -104 && Alexio::Engine::GetInstance()->GetCamera()->GetPosition().y < 0.0f)
                    mLookUpOrDownCameraShift -= 2;
            }
        }
    }

    if (game.DownButtonHeld() && (!game.LeftButtonHeld() && !game.RightButtonHeld()))
    {
        if (std::abs(mGroundSpeed) >= 0.5f)
        {
            mHitbox.heightRad = 10.0f;
            position.y += 6.0f;
            state = PlayerStates::ROLLING;
            SetAnimationState(PlayerAnimState::ROLLING, { 0, 8 });
        }
        else if (mGroundSpeed == 0.0f && lookState != PlayerLookStates::LOOK_UP)
        {
            if (lookState == PlayerLookStates::NORMAL)
            {
                mHitbox.heightRad = 10.0f;
                position.y += 6.0f;
                lookState = PlayerLookStates::LOOK_DOWN;
                SetAnimationState(PlayerAnimState::LOOK_DOWN, { 7, 2 });
            }

            if (mTimerBeforeCameraShift < 60)
                mTimerBeforeCameraShift++;
            else
            {
                if (mLookUpOrDownCameraShift < 88 && Alexio::Engine::GetInstance()->GetCamera()->GetPosition().y >(game.currentAct.screenSize.y - game.cameraController.projectionSize.y) * -1.0f)
                    mLookUpOrDownCameraShift += 2;
            }
        }
    }
}

void Player::UpdateMovement()
{
    if (state == PlayerStates::AIRBORNE)
        mSpeed.x = mAirSpeed;
    else
    {
        mSpeed.x = mGroundSpeed * cosf(mAngle);
        mSpeed.y = mGroundSpeed * -sinf(mAngle);
    }

    if (position.x < 16.0f)
    {
        mSpeed.x = 0.0f;
        mAirSpeed = 0.0f;
        mGroundSpeed = 0.0f;
        position.x = 16.0f;
    }
    else
        position.x += mSpeed.x;

    position.y += mSpeed.y;
    UpdateSensors();
}

void Player::PushSensors()
{
    if (mGroundSpeed < 0.0f || state == PlayerStates::AIRBORNE)
        FindSurface(mPointE);
    if (mGroundSpeed > 0.0f || state == PlayerStates::AIRBORNE)
        FindSurface(mPointF);

    if (mSpeed.x != 0.0f)
    {
        if (mPointE.distance > 0.0f)
        {
            position.x += mPointE.distance;
            if (state == PlayerStates::AIRBORNE)
            {
                mAirSpeed = 0.0f;
            }
            else if (state == PlayerStates::NORMAL && MoveInCorrectDirection())
            {
                SetAnimationState(PlayerAnimState::PUSHING, { 0, 9 });
            } 
            mSpeed.x = 0.0f;
            mGroundSpeed = 0.0f;
            mPointE.distance = 0.0f;
        
            UpdateSensors();
        }
        
        if (mPointF.distance < 0.0f)
        {
            position.x += mPointF.distance;
            if (state == PlayerStates::AIRBORNE)
            {
                mAirSpeed = 0.0f;
                mSpeed.x = 0.0f;
            }
            else if (state == PlayerStates::NORMAL && MoveInCorrectDirection())
            {
                SetAnimationState(PlayerAnimState::PUSHING, { 0, 9 });
            }
            mGroundSpeed = 0.0f;
            mPointF.distance = 0.0f;
        
            UpdateSensors();
        }
    }
}

void Player::CeilingSensors()
{
    FindSurface(mPointC);
    FindSurface(mPointD);

    float ceilingDistance = std::max(mPointC.distance, mPointD.distance);

    if (ceilingDistance >= 0.0f && ceilingDistance < 14.0f)
    {
        position.y -= ceilingDistance;
        mSpeed.y = 0.0f;

        UpdateSensors();
    }
}

void Player::GroundSensors()
{
    FindSurface(mPointA);
    FindSurface(mPointB);

    if (mSpeed.x == 0.0f && state != PlayerStates::AIRBORNE)
        FindSurface(mPointG);

    float groundDistance = std::min(mPointA.distance, mPointB.distance);
    if (groundDistance > -14.0f && groundDistance < std::min(std::abs(mSpeed.x) + 4, 14.0f))
    {
        if (state == PlayerStates::AIRBORNE)
        {
            if (mJumped)
            {
                mJumped = false;
                if (!game.JumpButtonHeld())
                    mJumpLock = false;
            }
            state = PlayerStates::NORMAL;
            mHitbox.heightRad = 16.0f;
            mSpeed.y = 0.0f;
            mAirSpeed = 0.0f;
            mGroundSpeed = mSpeed.x;
            if (mGroundSpeed != 0.0f)
                SetAnimationState(PlayerAnimState::MOVE, {0, 3});
            else
                SetAnimationState(PlayerAnimState::IDLE);
        }
        position.y += groundDistance;
        UpdateSensors();
    }
    else if (state != PlayerStates::AIRBORNE)
    {
        if (!mJumped && std::abs(mGroundSpeed) < mTop)
            SetAnimationState(PlayerAnimState::AIR_WALK, { 0, 10 });
        state = PlayerStates::AIRBORNE;
        mAirSpeed = mSpeed.x;
    }

    if (mPointG.distance >= 16.0f && state == PlayerStates::NORMAL && mSpeed.x == 0.0f && lookState == PlayerLookStates::NORMAL)
        SetAnimationState(PlayerAnimState::BALANCING);
}

void Player::AirDrag()
{
    if (mSpeed.y > -4.0f && mSpeed.y < 0.0f)
    {
        mSpeed.x -= ((int)(mSpeed.x / 0.125f) / 256.0f);
    }
}

void Player::ApplyGravity()
{
    mSpeed.y += mGravityForce;
    if (mSpeed.y > 16.0f)
        mSpeed.y = 16.0f;
    game.cameraController.speed = mSpeed;
}

void Player::UpdateSensors()
{
    mHitbox.position = { position.x - mHitbox.widthRad, position.y - mHitbox.heightRad };
    mHitbox.size = { mHitbox.widthRad * 2 + 1, mHitbox.heightRad * 2 + 1 };

    if (mJumped)
    {
        mPointA.position = { position.x - mHitbox.widthRad + 1.0f, position.y + mHitbox.heightRad + 3.0f };
        mPointB.position = { position.x + mHitbox.widthRad - 1.0f, position.y + mHitbox.heightRad + 3.0f };

        mPointC.position = { position.x - mHitbox.widthRad + 1.0f, position.y - mHitbox.heightRad - 3.0f };
        mPointD.position = { position.x + mHitbox.widthRad - 1.0f, position.y - mHitbox.heightRad - 3.0f };
    }
    else
    {
        mPointA.position = { position.x - mHitbox.widthRad - 1.0f, position.y + mHitbox.heightRad + 3.0f };
        mPointB.position = { position.x + mHitbox.widthRad + 1.0f, position.y + mHitbox.heightRad + 3.0f };
        
        mPointG.position = { position.x, position.y + mHitbox.heightRad + 3.0f };

        mPointC.position = { position.x - mHitbox.widthRad - 1.0f, position.y - mHitbox.heightRad - 3.0f };
        mPointD.position = { position.x + mHitbox.widthRad + 1.0f, position.y - mHitbox.heightRad - 3.0f };
    }

    mPointE.position = { position.x - mHitbox.widthRad - 2.0f, (state == PlayerStates::NORMAL) ? position.y + 8.0f : position.y };
    mPointF.position = { position.x + mHitbox.widthRad + 2.0f, (state == PlayerStates::NORMAL) ? position.y + 8.0f : position.y };
}

void Player::Draw()
{
    /*
    * Because the physical position in Y axis drops down by 10 while crouching, we need to offset the drawing image position by so.
    * We're checking the functionality state instead of animation state, because animation goes through standing up phase before it
    * switches to another animation, but the physical original position needs to switch back immediately after down button has been 
    * released.
    */
    if (lookState == PlayerLookStates::LOOK_DOWN)
        mDrawingPosition.y = position.y - 10.0f; 

    
    Alexio::Renderer::DrawPartialSprite(mGFX, mDrawingPosition, mSubImagePosition, mSubImageSize, 0.0f, Alexio::Vector4(1.0f), { 1.0f * (int)mDirection, 1.0f });

    //DrawHitbox();
}

void Player::DrawHitbox()
{
    // mHitbox
    Alexio::Renderer::DrawQuad(mHitbox.position, mHitbox.size, { 1.0f, 0.0f, 1.0f, 0.5f });

    if (mSpeed.y >= 0.0f)
    {
        // GROUND SENSORS

        // Sensor A line and mPoint
        Alexio::Renderer::DrawQuad({ mPointA.position.x, mPointA.position.y - mHitbox.heightRad - 3.0f }, { 1, mHitbox.heightRad + 3.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
        Alexio::Renderer::DrawQuad({ mPointA.position.x, mPointA.position.y }, { 1, 1 });

        if (mSpeed.x == 0.0f && state != PlayerStates::AIRBORNE)
        {
            // Sensor G line and mPoint
            Alexio::Renderer::DrawQuad({ mPointG.position.x, mPointG.position.y - mHitbox.heightRad - 3.0f }, { 1, mHitbox.heightRad + 3.0f }, { 56.0f / 255.0f, 1.0f, 162.0f / 255.0f, 1.0f });
            Alexio::Renderer::DrawQuad({ mPointG.position.x, mPointG.position.y }, { 1, 1 });
        }

        // Sensor B line and mPoint
        Alexio::Renderer::DrawQuad({ mPointB.position.x, mPointB.position.y - mHitbox.heightRad - 3.0f }, { 1, mHitbox.heightRad + 3.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
        Alexio::Renderer::DrawQuad({ mPointB.position.x, mPointB.position.y }, { 1, 1 });
    }
    else
    {
        // AIR SENSORS

       // Sensor C line and mPoint
        Alexio::Renderer::DrawQuad({ mPointC.position.x, mPointC.position.y }, { 1, mHitbox.heightRad + 3.0f }, { 0, 174.0f / 255.0f, 239.0f / 255.0f, 1.0f });
        Alexio::Renderer::DrawQuad({ mPointC.position.x, mPointC.position.y }, { 1, 1 });

        // Sensor D line and mPoint
        Alexio::Renderer::DrawQuad({ mPointD.position.x, mPointD.position.y }, { 1, mHitbox.heightRad + 3.0f }, { 1.0f, 242.0f / 255.0f, 56.0f / 255.0f, 1.0f });
        Alexio::Renderer::DrawQuad({ mPointD.position.x, mPointD.position.y }, { 1, 1 });
    }

    // PUSH SENSORS
    if (mGroundSpeed < 0.0f || state == PlayerStates::AIRBORNE)
    {
        // Sensor E line and mPoint
        Alexio::Renderer::DrawQuad({ mPointE.position.x + 1, mPointE.position.y }, { mHitbox.widthRad, 1 }, { 1.0f, 56 / 255.0f, 1.0f, 1.0f });
        Alexio::Renderer::DrawQuad({ mPointE.position.x, mPointE.position.y }, { 1, 1 });
    }
    if (mGroundSpeed > 0.0f || state == PlayerStates::AIRBORNE)
    {
        // Sensor F line and mPoint
        Alexio::Renderer::DrawQuad({ mPointF.position.x - mHitbox.widthRad, mPointF.position.y }, { mHitbox.widthRad, 1 }, { 1.0f, 84.0f / 255.0f, 84.0f / 255.0f, 1.0f });
        Alexio::Renderer::DrawQuad({ mPointF.position.x, mPointF.position.y }, { 1, 1 });
    }

    // Position mPoint
    Alexio::Renderer::DrawQuad({ (position.x - 1), position.y }, { 1, 1 });
    Alexio::Renderer::DrawQuad({ (position.x + 1), position.y }, { 1, 1 });
    Alexio::Renderer::DrawQuad({ position.x, position.y - 1 }, { 1, 1 });
    Alexio::Renderer::DrawQuad({ position.x, position.y + 1 }, { 1, 1 });
    Alexio::Renderer::DrawQuad({ position.x, position.y }, { 1, 1 }, { 0.0f, 0.0f, 0.0f, 1.0f });
}

void Player::OnImGuiRender()
{
    char* cPlayerState = "??????";
    if (state == PlayerStates::NORMAL) cPlayerState = "NORMAL";
    else if (state == PlayerStates::ROLLING) cPlayerState = "ROLLING";
    else if (state == PlayerStates::AIRBORNE) cPlayerState = "AIRBORNE";

    char* cPlayerLookState = "??????";
    if (lookState == PlayerLookStates::NORMAL) cPlayerLookState = "NORMAL";
    else if (lookState == PlayerLookStates::LOOK_UP) cPlayerLookState = "LOOK UP";
    else if (lookState == PlayerLookStates::LOOK_DOWN) cPlayerLookState = "LOOK DOWN";

    char* cDirection = "??????";
    if (mDirection == Direction::LEFT) cDirection = "LEFT";
    else if (mDirection == Direction::RIGHT) cDirection = "RIGHT";

    ImGui::Begin("Player");
    ImGui::Text("Position: X: %.6f, Y: %.6f", position.x, position.y);
    ImGui::Text("Speed: X: %.6f, Y: %.6f", mSpeed.x, mSpeed.y);
    ImGui::Text("Direction: %s", cDirection);
    ImGui::Text("Ground Speed: %.6f", mGroundSpeed);
    ImGui::Text("Air Speed: %.6f", mAirSpeed);
    ImGui::Text("Jumping: %s", mJumped ? "true" : "false");
    ImGui::Text("Jump lock: %s", mJumpLock ? "true" : "false");
    ImGui::Text("State: %s", cPlayerState);
    ImGui::Text("Look State: %s", cPlayerLookState);
    ImGui::Text("Animation: %s", mAnimationName);
    ImGui::Text("");
    ImGui::Text("A distance: %.6f, B distance: %.6f", mPointA.distance, mPointB.distance);
    ImGui::Text("C distance: %.6f, D distance: %.6f", mPointC.distance, mPointD.distance);
    ImGui::Text("E distance: %.6f, F distance: %.6f", mPointE.distance, mPointF.distance);
    ImGui::Text("G distance: %.6f", mPointG.distance);
    ImGui::Text("");
    ImGui::Text("Camera Shift Offset: %d", mLookUpOrDownCameraShift);
    ImGui::Text("Timer Before Camera Shift: %d", mTimerBeforeCameraShift);

    ImGui::End();
}
