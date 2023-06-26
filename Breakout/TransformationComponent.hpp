#pragma once
#include "Component.hpp"
#include "Vec2.hpp"
class TransformationComponent {
public:
	Vec2 position{ 0, 0 };
	Vec2 velocity{ 0, 0 };
	Vec2 acceleration{ 0, 0 };
	TransformationComponent() = default;
};