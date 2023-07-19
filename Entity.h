#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <string>
#include "CTransform.h"
#include "CShape.h"
#include "CCollision.h"
#include "CScore.h"

class Entity
{
public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	// std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	// std::shared_ptr<CLifespan> cLifespan;

	void destroy();
	bool isActive();
	std::string& tag();
	size_t id();

private:
	std::string m_tag;
	bool m_active;
	size_t m_id;
};

#endif // !ENTITY_H
