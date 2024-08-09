#pragma once

#include "Alexio/Engine.h"

#define ENUM_TO_STRING_CASE(value) #value;

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
	double mTimer;
	uint32_t mFrameCounter;
	uint32_t mMaxFrameCount;
	Alexio::Vector2 mSubImageSize;
	Alexio::Vector2i mSubImageUnitPos;
};


enum class PlayerAnimState
{
	IDLE,
	LOOK_UP,
	LOOK_DOWN,
	MOVE,
	SKID,
	SKID_TURN,
	JUMP,
	ROLLING,
	PUSHING
};

class PlayerAnimation : public Animation
{
protected:
	PlayerAnimState mAnimationState;
	uint8_t mBoredOneCount;
	uint8_t mBoredTwoCount;
	uint8_t mBoredTwoMidCount;

	const char* mAnimationName;
public:
	PlayerAnimation();
	PlayerAnimation(const Alexio::Vector2& subImageSize, const Alexio::Vector2i& subImageUnitPos);

	void HandleAnimation() override {};
	void ResetCounters() override;

	void SetAnimationState(PlayerAnimState state, const Alexio::Vector2i& subImageUnitPos = {0, 0});

	const char* GetAnimationName();
};