#pragma once
#include "sense.h"
#include "sense_manager.h"
#include "menu_sense.h"
#include <functional>

extern menu_sense* menusense;

extern sense_manager* sensemanager;

class round_sense :public sense {//场景框架
public:
	round_sense() {

	}
	virtual ~round_sense() {

	}
	virtual void on_enter() {

	}//进入场景
	virtual void on_update(int time) {
		if (update)
			update(time);
	}//更新场景
	virtual void on_draw() {
		if (draw)
			draw();
	}//绘画场景
	virtual void on_input(const ExMessage& mes) {
		if (input)
			input(mes);
	}//处理输入
	virtual void on_exit() {
		sensemanager->switch_to(menusense);
	}//退出场景

	//外部设置
	void set_on_update(std::function<void(int)> update) {
		this->update = update;
	}
	void set_on_draw(std::function<void()> draw) {
		this->draw = draw;
	}
	void set_on_input(std::function<void(const ExMessage&)> input) {
		this->input = input;
	}
protected:
	std::function<void(int)> update;
	std::function<void()> draw;
	std::function<void(const ExMessage&)> input;
};