#include "PlayerInputComponent.hpp"
PlayerInputComponent::PlayerInputComponent()
	: Component(ComponentType::PLAYER_INPUT),
	isMovingLeft(false),
	isMovingRight(false)
{

}