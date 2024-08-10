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

	inline Alexio::Vector2 GetSubImageUnitPos() { return mSubImageUnitPos; };
	inline Alexio::Vector2 GetSubImagePosition() { return Alexio::Vector2(mSubImageSize.x * mSubImageUnitPos.x, mSubImageSize.y * mSubImageUnitPos.y); }
	inline Alexio::Vector2 GetSubImageSize() { return mSubImageSize; }

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


