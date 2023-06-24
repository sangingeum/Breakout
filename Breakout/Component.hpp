#pragma once

enum class ComponentType {
	DEFAULT = 0,
	POSITION = 1,
	VELOCITY = 2,
	COLLISION = 3,
	PLAYER_INPUT = 4,
	SHAPE_RENDER = 5
};

class Component {
	ComponentType m_type = ComponentType::DEFAULT;
public:
	Component();
	Component(ComponentType type);
	ComponentType getComponentType();
};