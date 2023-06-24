#pragma once
#include "Component.hpp"
class PlayerInputComponent : public Component {
public:
	bool isMovingLeft = false;
	bool isMovingRight = false;
	PlayerInputComponent();
};