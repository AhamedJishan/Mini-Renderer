#pragma once

#include <iostream>

template <class T>
struct Vec3
{
	T x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

	Vec3<T> operator+(const Vec3<T>& v) { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
	Vec3<T> operator-(const Vec3<T>& v) { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
	Vec3<T> operator*(float s)			{ return Vec3<T>(x * s, y * s, z * s); }

	template <class > friend std::ostream& operator<<(std::ostream& s, Vec3<T>& v);
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template <class T> std::ostream& operator<<(std::ostream& s, Vec3<T>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}