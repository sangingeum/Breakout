#include "Component.hpp"

Component::Component()
	: m_type(ComponentType::DEFAULT)
{}

Component::Component(ComponentType type)
	: m_type(type)
{}

ComponentType Component::getComponentType()
{
	return m_type;
}