#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class CCollision
{
public:
	float radius{0.0f};

	CCollision() {}
};

class CInput
{
	CInput() {}
};

class CLifespan
{
	CLifespan() {}
};

class CScore
{
public:
	int score{0};

	CScore() {}
};

class CShape
{
public:
	sf::CircleShape shape;

	CShape() {}
};

class CTransform
{
public:
	Vec2 pos;
	Vec2 speed;
	Vec2 scale;
	double angle;

	CTransform();
	CTransform(const Vec2& p, const Vec2& v);
};

#endif // !COMPONENTS_H
