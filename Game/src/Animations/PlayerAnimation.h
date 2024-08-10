#pragma once

#include "Animation.h"

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
	PUSHING,
	AIR_WALK,
	BALANCING
};

class PlayerAnimation : public Animation
{
protected:
	PlayerAnimState mAnimationState;
	uint8_t mBoredOneCount;
	uint8_t mBoredTwoCount;
	uint8_t mBoredTwoMidCount;
public:
	PlayerAnimation();
	PlayerAnimation(const Alexio::Vector2& subImageSize, const Alexio::Vector2i& subImageUnitPos);

	void HandleAnimation() override {};
	void ResetCounters() override;

	void SetAnimationState(PlayerAnimState state, const Alexio::Vector2i& subImageUnitPos = { 0, 0 });
};