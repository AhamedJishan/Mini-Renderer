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



template <class T>
struct Vec2
{
	T x, y;

	Vec2() : x(0), y(0) {}
	Vec2(T _x, T _y) : x(_x), y(_y) {}

	Vec2<T> operator+(const Vec2<T>& v) { return Vec2<T>(x + v.x, y + v.y); }
	Vec2<T> operator-(const Vec2<T>& v) { return Vec2<T>(x - v.x, y - v.y); }
	Vec2<T> operator*(float s) { return Vec2<T>(x * s, y * s); }

	template <class > friend std::ostream& operator<<(std::ostream& s, Vec2<T>& v);
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

template <class T> std::ostream& operator<<(std::ostream& s, Vec2<T>& v) {
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}