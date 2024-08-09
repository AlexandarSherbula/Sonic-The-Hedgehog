#include "Animation.h"
#include "Player.h"

Animation::Animation(const Alexio::Vector2& subImageSize, const Alexio::Vector2i& subImageUnitPos)
{
	mSubImageSize = subImageSize;
	mSubImageUnitPos = subImageUnitPos;

	mTimer = 0.0f;
}

void Animation::ResetCounters()
{
    mTimer = 0.0f;
    mFrameCounter = 0.0f;
}

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

    char* test = ENUM_TO_STRING_CASE(mAnimationState);

    AIO_LOG_WARN(test);
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

const char* PlayerAnimation::GetAnimationName()
{
    return "Unknown";
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
    switch (mAnimationState)
    {
        case PlayerAnimState::IDLE:
        {
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

            break;
        }
        case PlayerAnimState::LOOK_UP:
        {
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
            break;
        }
        case PlayerAnimState::LOOK_DOWN:
        {
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
            break;
        }
        case PlayerAnimState::MOVE:
        {
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
            else
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

            break;
        }
        case PlayerAnimState::SKID:
        {
            if ((mDirection == Direction::LEFT && mGroundSpeed < 0.0f) ||
                (mDirection == Direction::RIGHT && mGroundSpeed > 0.0f))
            {
                mSubImageUnitPos.y = 7;
                mMaxFrameCount = 1;

                if (mFrameCounter >= mMaxFrameCount)
                {
                    if (mSubImageUnitPos.x == 8)
                    {
                        mAnimationState = PlayerAnimState::MOVE;
                    }
                    else
                        mSubImageUnitPos.x++;

                    mFrameCounter = 0;
                }
                else
                    mFrameCounter++;
            }
            else
            {
                SetAnimationState(PlayerAnimState::MOVE, { 0, 3 });
            }

            break;
        }
        case PlayerAnimState::SKID_TURN:
        {
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

            break;
        }
        case PlayerAnimState::JUMP: case PlayerAnimState::ROLLING:
        {
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
            break;
        }
        case PlayerAnimState::PUSHING:
        {
            mMaxFrameCount = 5;
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

            break;
        }
    }
}