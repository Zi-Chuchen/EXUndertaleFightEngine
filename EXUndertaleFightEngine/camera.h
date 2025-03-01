#pragma once
#include "vec2D.h"
#include "timer.h"
#include <cstdlib>

extern IMAGE window_displayer;

class camera {
public:
	camera() {
		shake_timer.set_if_loop(false);
		shake_timer.set_call_back([&] {
			if_shake = false;
			});
	}
	~camera() = default;
	void shake(float s, int t) {
		if_shake = true;
		this->s = s;
		this->old_position = position;
		shake_timer.set_order_time(t);
		shake_timer.restart();
	}
	void reset() {//重置
		position = old_position;
	}
	vec2D& get_position() {
		return position;
	}
	void on_update(int time) {
		shake_timer.on_update(time);
		if (if_shake) {
			position.x = (-50 + rand() % 100) / 50.0f * s;
			position.y = (-50 + rand() % 100) / 50.0f * s;
		}
	}
	bool get_if_end() {
		return shake_timer.get_if_done();
	}
	double get_rotate_r() {
		return rotate_r;
	}
	void set_rotate_r(double new_r) {
		rotate_r = new_r;
	}
	POINT get_rotate_o() {
		return rotate_o;
	}
	void set_rotate_o(POINT rotate_o) {
		this->rotate_o = rotate_o;
	}
private:
	vec2D position;//位置
	vec2D old_position;//旧位置
	POINT rotate_o = { 0,0 };
	timer shake_timer;//计时器
	bool if_shake = false;
	float s = 0.9f;
	double rotate_r = 0;//弧度制
};