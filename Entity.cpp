#include "Entity.h"

Entity::Entity()
{

}

void Entity::destroy()
{

}

bool Entity::isActive()
{
	return m_active;
}

std::string& Entity::tag()
{
	return m_tag;
}

size_t Entity::id()
{
	return m_id;
}