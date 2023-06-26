#pragma once
#include "Component.hpp"

enum class CollisionBoxType {
	RECTANGLE = 0,
	CIRCLE = 1
};

class CollisionComponent{
public:
	float width = 1.0f; // width or radius
	float height = 1.0f;
	bool breakable = true;
	CollisionBoxType type = CollisionBoxType::RECTANGLE;
	CollisionComponent() = default;
};