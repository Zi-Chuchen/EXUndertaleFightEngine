#pragma once


class vec2D {
public:
	vec2D(float x = 0, float y = 0) :x(x), y(y) {}
	~vec2D() = default;
	void operator+=(float num) {
		x += num;
		y += num;
	}
	void operator-=(float num) {
		x -= num;
		y -= num;
	}
	vec2D& operator +(float num) {
		x += num;
		y += num;
		return *this;
	}
	vec2D& operator -(float num) {
		x -= num;
		y -= num;
		return *this;
	}
	void reset() {
		x = 0;
		y = 0;
	}
public:
	float x = 0;
	float y = 0;
};