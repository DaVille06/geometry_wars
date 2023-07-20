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
	sf::CircleShape circle;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CTransform
{
public:
	Vec2 pos{ 0.0, 0.0 };
	Vec2 velocity{ 0.0, 0.0 };
	float angle{ 0 };

	CTransform(const Vec2& p, const Vec2& v, float a)
		: pos{p}, velocity{v}, angle{a} { }
};

#endif // !COMPONENTS_H
