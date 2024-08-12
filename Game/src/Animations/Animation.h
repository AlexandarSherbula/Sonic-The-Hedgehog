#pragma once

#include "Alexio/Engine.h"

class Animation
{
public:
	Animation() {}
	Animation(const Alexio::Vector2& subImageSize, const Alexio::Vector2i& subImageUnitPos);

	virtual void HandleAnimation() = 0;

	inline void SetSubImageSize(const Alexio::Vector2& subImageSize) { mSubImageSize = subImageSize; };
	inline void SetSubImageUnitPos(const Alexio::Vector2& subImageUnitPos) { mSubImageUnitPos = subImageUnitPos; };

	virtual void ResetCounters();
protected:
	const char* mAnimationName;
	double mTimer;
	uint32_t mFrameCounter;
	uint32_t mMaxFrameCount;
	Alexio::Vector2 mDrawingPosition;
	Alexio::Vector2 mSubImagePosition;
	Alexio::Vector2 mSubImageSize;
	Alexio::Vector2i mSubImageUnitPos;
};


