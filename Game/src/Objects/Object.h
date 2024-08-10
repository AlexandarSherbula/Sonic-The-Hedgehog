#pragma once

#include "Alexio/Engine.h"
#include "Act.h"

enum class Direction
{
	LEFT = -1,
	RIGHT = 1
};

struct AnchorPoint
{
	Alexio::Vector2i direction;
	Alexio::Vector2 position;
	float distance;

	TileSolidity tileChecker;

	AnchorPoint() {}
	AnchorPoint(const Alexio::Vector2i& direction, TileSolidity tileChecker);
};

class Object
{
public:
	Alexio::Vector2 position;
private:
	struct HitBox
	{
		Alexio::Vector2 position;
		Alexio::Vector2 size;
		int widthRad;
		int heightRad;
	};
protected:
	Direction mDirection;
	HitBox mHitbox;
	Alexio::Ref<Alexio::Texture> mGFX;
public:
	Object();
	Object(const Alexio::Vector2& position, int widthRadius, int heightRadius, Direction direction = Direction::RIGHT, const std::string& gfxFilePath = "");

	virtual void Draw();
};


class MovingObject : public Object
{
protected:
	Alexio::Vector2 mSpeed;
	float mGroundSpeed;
	float mAirSpeed;
public:
	MovingObject();
	MovingObject(const Alexio::Vector2& position, int widthRad, int heightRad, Direction direction = Direction::RIGHT, const std::string& gfxFilePath = "");
	void FindSurface(AnchorPoint& point);

	virtual void Update() {};
	virtual void FixedUpdate() {};
};