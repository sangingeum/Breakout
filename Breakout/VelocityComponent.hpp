#pragma once
#include "Component.hpp"
#include "Vec2.hpp"
class VelocityComponent : public Component {
public:
	Vec2 velocity{ 0, 0 };
	VelocityComponent();
	VelocityComponent(float x, float y);
	VelocityComponent(const Vec2& v);
};