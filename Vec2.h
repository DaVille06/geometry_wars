#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
	double x{ 0 };
	double y{ 0 };

	Vec2();
	Vec2(float xin, float yin);

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const Vec2& rhs) const;
	Vec2 operator / (const Vec2& rhs) const;

	void operator += (const Vec2& rhs);
	void operator -= (const Vec2& rhs);
	void operator *= (const float val);
	void operator /= (const float val);

	float dist(const Vec2& rhs) const;
	float length() const;
	void normalize();
};

#endif // !VEC2_H
