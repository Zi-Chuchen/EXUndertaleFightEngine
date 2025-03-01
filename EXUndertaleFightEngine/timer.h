#pragma once
#include <functional>

class timer {
public:
	timer() = default;
	~timer() = default;
	void restart() {
		timer_count = 0;
		if_done = false;
	}
	void set_if_loop(bool set) {
		is_loop = set;
	}
	void paused_running() {
		is_running = false;
	}
	void continue_running() {
		is_running = true;
	}
	void set_call_back(const std::function<void()>& f) {
		call_back = f;
	}
	void set_order_time(int time) {
		order_time = time;
	}
	void on_update(int time) {
		if (!is_running) {
			return;
		}
		timer_count += time;
		if (timer_count >= order_time) {
			if ((is_loop || (!is_loop && !if_done)) && call_back)
				call_back();
			if_done = true;
			timer_count = 0;
		}
	}
	bool get_if_done() {
		return if_done;
	}
private:
	int timer_count = 0;
	int order_time = 0;
	std::function<void()> call_back;//回调函数
	bool is_loop = false;
	bool is_running = true;
	bool if_done = false;//是否被触发
};