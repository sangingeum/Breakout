#pragma once
#include "Component.hpp"
class PlayerInputComponent{
public:
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isMovingUp = false;
	bool isMovingDown = false;
	bool leftRightMode = true;
	PlayerInputComponent() = default;
};