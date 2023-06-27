#pragma once
#include "Component.hpp"

enum class CollisionBoxType {
	RECTANGLE = 0,
	CIRCLE = 1
};

class CollisionComponent{
public:
	float halfWidth = 1.0f; // half width or radius
	float halfHeight = 1.0f;
	bool breakable = true;
	bool bouncible = false;
	bool doNotMoveWhenCollide = false;
	CollisionBoxType type = CollisionBoxType::RECTANGLE;
	CollisionComponent() = default;
};