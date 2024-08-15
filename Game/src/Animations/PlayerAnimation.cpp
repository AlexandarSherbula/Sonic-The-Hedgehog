#include "PlayerAnimation.h"

#include "Objects/Player.h"

PlayerAnimation::PlayerAnimation()
    : Animation()
{
}

PlayerAnimation::PlayerAnimation(const Alexio::Vector2& subImageSize, const Alexio::Vector2i& subImageUnitPos)
    : Animation(subImageSize, subImageUnitPos)
{
    mAnimationState = PlayerAnimState::IDLE;
    mFrameCounter = 0;
    mMaxFrameCount = 3;

    mBoredOneCount = 0;
    mBoredTwoCount = 0;
    mBoredTwoMidCount = 0;

    mDrawingPosition = { 0.0f, 0.0f };
}

void PlayerAnimation::SetAnimationState(PlayerAnimState state, const Alexio::Vector2i& subImageUnitPos)
{
    if (mAnimationState != state)
    {
        mAnimationState = state;
        mSubImageUnitPos = subImageUnitPos;
        ResetCounters();
    }
}

void PlayerAnimation::ResetCounters()
{
    mTimer = 0.0f;
    mFrameCounter = 0;

    if (mAnimationState == PlayerAnimState::MOVE)
        mSubImageUnitPos.x = 0;

    mBoredOneCount = 0;
    mBoredTwoCount = 0;
    mBoredTwoMidCount = 0;
}


void Player::HandleAnimation()
{
    if (mGroundSpeed == 0.0f && (mAnimationState == PlayerAnimState::MOVE || mAnimationState == PlayerAnimState::ROLLING))
        SetAnimationState(PlayerAnimState::IDLE);

    mSubImageSize = { 48.0f, 48.0f };
    mDrawingPosition = { position.x, position.y - 4.0f };

    switch (mAnimationState)
    {
    case PlayerAnimState::IDLE:
    {
        mAnimationName = "IDLE";
        if (mTimer < 3.0f)
        {
            mSubImageUnitPos = { 0, 0 };

            mTimer += Alexio::Timer::DetlaTime();
        }
        else
        {
            // BORED ONE
            mMaxFrameCount = 3;

            uint8_t firstUnitOffset = 6;
            uint8_t lastUnitOffset = 10;

            if (mBoredOneCount >= 12)
            {
                // BORED TWO
                mSubImageUnitPos.y = 1;

                if (mBoredTwoCount == 1 && mBoredTwoMidCount == 3)
                {
                    mSubImageUnitPos.x = 16;
                    mBoredTwoMidCount++;
                    mBoredTwoCount++;
                }
                else
                {
                    if (mBoredTwoMidCount < 4)
                    {
                        firstUnitOffset = 8;
                        lastUnitOffset = 14;
                    }
                    else
                    {
                        lastUnitOffset = 15;
                    }
                }

                if (mSubImageUnitPos.x == 6)
                    mMaxFrameCount = 36;
            }
            else
            {
                if (mSubImageUnitPos.x == 6 || mSubImageUnitPos.x == 8)
                    mMaxFrameCount = 12;
            }

            if (mFrameCounter == mMaxFrameCount)
            {
                if (mSubImageUnitPos.x == lastUnitOffset)
                {
                    mSubImageUnitPos.x = firstUnitOffset;

                    if (mBoredOneCount < 12)
                    {
                        mBoredOneCount++;
                        if (mBoredOneCount == 12)
                            mSubImageUnitPos.x = 0;
                    }
                    else
                    {
                        if (mBoredTwoMidCount < 4 && mSubImageUnitPos.x >= 8)
                            mBoredTwoMidCount++;
                        else
                        {
                            mBoredTwoCount++;
                            mBoredTwoMidCount = 0;
                        }
                    }

                }
                else
                    mSubImageUnitPos.x++;

                mFrameCounter = 0;
            }
            else
                mFrameCounter++;

            if (mSubImageUnitPos.x == 19)
            {
                mAnimationState = PlayerAnimState::IDLE;
                mSubImageUnitPos = { 0, 0 };
                ResetCounters();
            }

        }

        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::LOOK_UP:
    {
        mAnimationName = "LOOK UP";
        mMaxFrameCount = 3;

        if (mFrameCounter == mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 4)
            {
                mSubImageUnitPos.x = 4;
            }
            else
            {
                mSubImageUnitPos.x++;

                if (mSubImageUnitPos.x == 7)
                {
                    mAnimationState = PlayerAnimState::IDLE;
                    mSubImageUnitPos = { 0, 0 };
                }
            }
            mFrameCounter = 0;
        }

        mFrameCounter++;

        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::LOOK_DOWN:
    {
        mAnimationName = "LOOK DOWN";
        mMaxFrameCount = 3;

        if (mFrameCounter == mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 10)
            {
                mSubImageUnitPos.x = 10;
            }
            else
            {
                mSubImageUnitPos.x++;

                if (mSubImageUnitPos.x == 12)
                {
                    mAnimationState = PlayerAnimState::IDLE;
                    mSubImageUnitPos = { 0, 0 };
                }
            }
            mFrameCounter = 0;
        }

        mFrameCounter++;
        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::MOVE:
    {
        mAnimationName = "MOVE";

        uint8_t firstUnitOffset = 0;
        uint8_t lastUnitOffset = 17;
        uint8_t lastSubImageY = mSubImageUnitPos.y;

        if (std::abs(mGroundSpeed) < 4.0f)
        {
            mMaxFrameCount = std::floor(std::max(0.0f, 6.0f - std::abs(mGroundSpeed)));
            if (lastSubImageY != 3)
            {
                mSubImageUnitPos = { 0, 3 };
                lastSubImageY = mSubImageUnitPos.y;
            }

            firstUnitOffset = 0;
            lastUnitOffset = 11;
        }
        else if (std::abs(mGroundSpeed) > 4.0f && std::abs(mGroundSpeed) < 6.0f)
        {
            mMaxFrameCount = std::floor(std::max(0.0f, 7.0f - std::abs(mGroundSpeed)));
            if (lastSubImageY != 4)
            {
                mSubImageUnitPos = { 0, 4 };
                lastSubImageY = mSubImageUnitPos.y;
            }

            firstUnitOffset = 0;
            lastUnitOffset = 9;
        }
        else if (std::abs(mGroundSpeed) >= 6.0f && std::abs(mGroundSpeed) < 10.0f)
        {
            mMaxFrameCount = std::floor(std::max(0.0f, 7.0f - std::abs(mGroundSpeed)));
            if (lastSubImageY != 5)
            {
                mSubImageUnitPos = { 0, 5 };
                lastSubImageY = mSubImageUnitPos.y;
            }
            firstUnitOffset = 0;
            lastUnitOffset = 7;
        }
        else
        {
            mMaxFrameCount = std::floor(std::max(0.0f, 7.0f - std::abs(mGroundSpeed)));
            if (lastSubImageY != 6)
            {
                mSubImageUnitPos = { 0, 6 };
                lastSubImageY = mSubImageUnitPos.y;
            }

            firstUnitOffset = 1;
            lastUnitOffset = 4;
        }

        if (mFrameCounter >= mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == lastUnitOffset)
                mSubImageUnitPos.x = firstUnitOffset;
            else
                mSubImageUnitPos.x++;

            mFrameCounter = 0;
        }
        else
            mFrameCounter++;

        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::SKID:
    {
        mAnimationName = "SKID";

        mSubImageUnitPos.y = 7;
        mMaxFrameCount = std::ceil(std::max(1.0f, std::abs(mGroundSpeed) - 6.0f));

        if (mFrameCounter >= mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 8)
                mAnimationState = PlayerAnimState::MOVE;
            else
                mSubImageUnitPos.x++;

            mFrameCounter = 0;
        }
        else
            mFrameCounter++;

        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::SKID_TURN:
    {
        mAnimationName = "SKID TURN";

        mSubImageUnitPos.y = 7;
        mMaxFrameCount = 1;

        if (mFrameCounter >= mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 11)
                mAnimationState = PlayerAnimState::MOVE;
            else
                mSubImageUnitPos.x++;
            mFrameCounter = 0;
        }
        else
            mFrameCounter++;

        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::JUMP: case PlayerAnimState::ROLLING:
    {
        if (mAnimationState == PlayerAnimState::JUMP)
            mAnimationName = "JUMP";
        else if (mAnimationState == PlayerAnimState::ROLLING)
            mAnimationName = "ROLLING";

        mMaxFrameCount = std::floor(std::max(0.0f, 4.0f - std::abs(mGroundSpeed)));

        if (mFrameCounter >= mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 15)
                mSubImageUnitPos.x = 0;
            else
                mSubImageUnitPos.x++;

            mFrameCounter = 0;
        }
        else
            mFrameCounter++;

        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::PUSHING:
    {
        mAnimationName = "PUSHING";
        mMaxFrameCount = 5;

        if (mDirection == Direction::RIGHT)
            mDrawingPosition.x = position.x + 1.0f;

        if (mFrameCounter >= mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 9)
                mSubImageUnitPos.x = 0;
            else
                mSubImageUnitPos.x++;

            mFrameCounter = 0;
        }
        else
            mFrameCounter++;

        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);
        break;
    }
    case PlayerAnimState::AIR_WALK:
    {
        mAnimationName = "AIR WALK";

        mMaxFrameCount = 3;
        if (mFrameCounter >= mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 11)
                mSubImageUnitPos.x = 0;
            else
                mSubImageUnitPos.x++;

            mFrameCounter = 0;
        }
        else
            mFrameCounter++;

        mDrawingPosition = { position.x, position.y + 3.5f };
        mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y + 7.0f);
        break;
    }
    case PlayerAnimState::BALANCING:
    {
        mAnimationName = "BALANCING";

        if (mPointA.distance >= 16.0f)
        {
            mDrawingPosition.x = position.x + 6.0f;
            if (mDirection == Direction::RIGHT)
            {
                mSubImagePosition.y = 701.0f;
            }
            else
            {
                mSubImageSize.x = 56.0f;
                mSubImagePosition.y = 750.0f;
            }
        }
        else if (mPointB.distance >= 16.0f)
        {
            mDrawingPosition.x = position.x - 6.0f;

            if (mDirection == Direction::RIGHT)
            {
                mSubImageSize.x = 56.0f;
                mSubImagePosition.y = 750.0f;
            }
            else
            {
                mSubImagePosition.y = 701.0f;
            }
        }

        mSubImagePosition.x = (1 + mSubImageUnitPos.x) + mSubImageSize.x * mSubImageUnitPos.x;

        mMaxFrameCount = 3;
        if (mFrameCounter >= mMaxFrameCount)
        {
            if (mSubImageUnitPos.x == 7)
                mSubImageUnitPos.x = 0;
            else
                mSubImageUnitPos.x++;

            mFrameCounter = 0;
        }
        else
            mFrameCounter++;


        break;
    }
    default:
        mAnimationName = "Unknown";
    }
}
