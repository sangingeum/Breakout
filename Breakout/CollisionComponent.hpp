#pragma once
#include "Component.hpp"

enum class CollisionBoxType {
	RECTANGLE = 0,
	CIRCLE = 1
};

class CollisionComponent : public Component {
public:
	float x = 1.0f;
	float y = 1.0f;
	CollisionBoxType type = CollisionBoxType::RECTANGLE;
	CollisionComponent();
	CollisionComponent(CollisionBoxType type);
};