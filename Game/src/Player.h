#pragma once

#include "Alexio/Engine.h"

#include "Object.h"
#include "Animation.h"

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
	
	inline bool UpButtonHeld()        {  return Alexio::Input::KeyHeld(UP) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_UP) || Alexio::Gamepad::L_ThumbStickHeldUp(); }
	inline bool UpButtonReleased()    {  return Alexio::Input::KeyReleased(UP) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_UP) || Alexio::Gamepad::L_ThumbStickReleasedUp(); }

	inline bool DownButtonHeld()      {  return Alexio::Input::KeyHeld(DOWN) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_DOWN) || Alexio::Gamepad::L_ThumbStickHeldDown(); }
	inline bool DownButtonReleased()  {  return Alexio::Input::KeyReleased(DOWN) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_DOWN) || Alexio::Gamepad::L_ThumbStickReleasedDown(); }

	inline bool LeftButtonHeld()      {  return Alexio::Input::KeyHeld(LEFT) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_LEFT) || Alexio::Gamepad::L_ThumbStickHeldLeft(); }
	inline bool LeftButtonReleased()  {  return Alexio::Input::KeyReleased(LEFT) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_LEFT) || Alexio::Gamepad::L_ThumbStickReleasedLeft(); }

	inline bool RightButtonHeld()     {  return Alexio::Input::KeyHeld(RIGHT) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_RIGHT) || Alexio::Gamepad::L_ThumbStickHeldRight(); }
	inline bool RightButtonReleased() {  return Alexio::Input::KeyReleased(RIGHT) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_RIGHT) || Alexio::Gamepad::L_ThumbStickReleasedRight(); }

	inline bool JumpButtonHeld()      {  return Alexio::Input::KeyHeld(A) || Alexio::Input::KeyHeld(S) || Alexio::Input::KeyHeld(D) ||
	                                          Alexio::Gamepad::ButtonHeld(Xbox::BUTTON_A) || Alexio::Gamepad::ButtonHeld(Xbox::BUTTON_B) || Alexio::Gamepad::ButtonHeld(Xbox::BUTTON_X); }

	inline bool JumpButtonReleased()  {  return Alexio::Input::KeyReleased(A) || Alexio::Input::KeyReleased(S) || Alexio::Input::KeyReleased(D) ||
	                                          Alexio::Gamepad::ButtonReleased(Xbox::BUTTON_A) || Alexio::Gamepad::ButtonReleased(Xbox::BUTTON_B) || Alexio::Gamepad::ButtonReleased(Xbox::BUTTON_X); }
};