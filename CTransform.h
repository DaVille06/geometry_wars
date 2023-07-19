#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "Vec2.h"

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

#endif // !CTRANSFORM_H
