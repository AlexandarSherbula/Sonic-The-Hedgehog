#pragma once

#include "Alexio/Engine.h"

#include "Act.h"
#include "Player.h"
#include "CameraController.h"

class Game : public Alexio::Engine
{
public:
	Game();

	bool OnStart() override;
	bool OnUpdate() override;
	bool OnFixedUpdate() override;
	
	void OnImGuiRender();
public:
	std::unique_ptr<Act> currentAct;
	std::unique_ptr<Player> player;
	std::unique_ptr<CameraController> cameraController;
};

inline Game game;