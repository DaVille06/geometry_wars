#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
	double x;
	double y;

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;
	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const Vec2& rhs) const;
	Vec2 operator / (const Vec2& rhs) const;

	void normalize();
	double length();
};

#endif // !VEC2_H
