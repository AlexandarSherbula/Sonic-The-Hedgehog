#pragma once

#include "Alexio/Engine.h"

#include "Player.h"

class CameraController
{
public:
	Alexio::Vector2 position;
	Alexio::Vector2 speed;

	Alexio::Vector2 offset;
	Alexio::Vector2 focalPoint;

	Alexio::Vector2 projectionSize;
public:
	CameraController();

	void Update(Player* player, const Alexio::Vector2& actSize);
	void DrawBorders();
};