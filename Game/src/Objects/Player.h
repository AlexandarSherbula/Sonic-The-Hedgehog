#pragma once

#include "Alexio/Engine.h"

#include "Object.h"
#include "Animations/PlayerAnimation.h"

enum class PlayerStates
{
	NORMAL,
	ROLLING,
	AIRBORNE
};

enum class PlayerLookStates
{
	LOOK_UP = -1,
	NORMAL = 0,
	LOOK_DOWN = 1
};

class Player : public MovingObject, public PlayerAnimation
{
public:
	PlayerStates state;
	PlayerLookStates lookState;
private:
	AnchorPoint mPointA;
	AnchorPoint mPointB;
	AnchorPoint mPointC;
	AnchorPoint mPointD;
	AnchorPoint mPointE;
	AnchorPoint mPointF;
	AnchorPoint mPointG;

	float mAcceleration;
	float mFriction;
	float mDeceleration;
	float mTop;
	float mAngle;

	float mAirAcceleration;
	float mJumpForce;
	float mGravityForce;

	bool  mJumped;
	bool  mJumpLock;

	float mRollFrictionSpeed;
	float mRollDecelerationSpeed;

	uint8_t mTimerBeforeCameraShift;
	int8_t mLookUpOrDownCameraShift;
public:
	Player();
	Player(const Alexio::Vector2& position, int widthRad, int heightRad, Direction direction = Direction::RIGHT, const std::string& gfxFilePath = "");

	void Update() override;
	void FixedUpdate() override;
	void Draw() override;

	void DrawHitbox();
	void OnImGuiRender();

	inline int8_t GetLookUpAndDownCameraShiftOffset() { return mLookUpOrDownCameraShift; }
private:
	void ResetLookStateCamera();
	void CheckForJump();
	void CheckForMovement();
	void PushSensors();
	void CeilingSensors();
	void UpdateMovement();
	void GroundSensors();

	void HandleAnimation() override;

	void AirDrag();
	void ApplyGravity();

	void UpdateSensors();
};