#pragma once
#include "Component.hpp"
class PlayerInputComponent{
public:
	bool isMovingLeft = false;
	bool isMovingRight = false;
	PlayerInputComponent() = default;
};