#pragma once
#include "Component.hpp"
#include "Vec2.hpp"
class PositionComponent : public Component {
public:
	Vec2 position{ 0, 0 };
	PositionComponent();
	PositionComponent(float x, float y);
	PositionComponent(const Vec2& v);
};