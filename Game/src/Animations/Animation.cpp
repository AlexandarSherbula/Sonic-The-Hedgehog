#include "Animation.h"

Animation::Animation(const Alexio::Vector2& subImageSize, const Alexio::Vector2i& subImageUnitPos)
{
	mSubImageSize = subImageSize;
	mSubImageUnitPos = subImageUnitPos;

    mSubImagePosition = (Alexio::Vector2)(1 + mSubImageUnitPos) + Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y);

	mTimer = 0.0f;

    mAnimationName = "Unknown";
}

void Animation::ResetCounters()
{
    mTimer = 0.0f;
    mFrameCounter = 0.0f;
}

