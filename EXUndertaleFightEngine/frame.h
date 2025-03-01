#pragma once
#include <windows.h>

//4像素
//15与102

class frame {
public:
	struct farme_info {
		POINT pos;//左上方点的坐标
		int weight;
		int height;
		bool operator!=(farme_info l) {
			if (l.pos.x == this->pos.x && l.pos.y == this->pos.y && l.weight == this->weight && l.height == this->height) {
				return true;
			}
		}
	};
public:
	frame() {
		now_info.pos = { 249,234 };
		now_info.weight = 102;
		now_info.height = 102;
	}
	void on_update(int time) {
		if (now_info != old_info) {

		}
	}
	void on_draw() {

	}
	void set_speed(int s) {
		speed = s;
	}
	farme_info get_farme_info() {
		return now_info;
	}

private:
	int speed = 10;
	farme_info now_info{};
	farme_info old_info{};
};