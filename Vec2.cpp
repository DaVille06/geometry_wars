#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {}

Vec2::Vec2(float xin, float yin)
	: x{ xin }, y{ yin } { }

bool Vec2::operator==(const Vec2& rhs) const
{
	// todo
	return false;
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	// todo
	return false;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	// todo
	return Vec2{ 0, 0 };
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	// todo
	return Vec2{ 0, 0 };
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	// todo
	return Vec2{ 0, 0 };
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
	// todo
	return Vec2{ 0, 0 };
}

void Vec2::operator+=(const Vec2& rhs)
{
	// todo
}

void Vec2::operator-=(const Vec2& rhs)
{
	// todo
}

void Vec2::operator*=(const float val)
{
	// todo
}

void Vec2::operator/=(const float val)
{
	// todo
}

float Vec2::dist(const Vec2& rhs) const
{
	// todo
	return 0.0f;
}

float Vec2::length() const
{
	// todo
	return 0.0f;
}

void Vec2::normalize()
{
	// todo
}