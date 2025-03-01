#pragma once
#include "sense.h"
#include "sense_manager.h"
#include "menu_sense.h"
#include <functional>

extern menu_sense* menusense;

extern sense_manager* sensemanager;

class round_sense :public sense {//�������
public:
	round_sense() {

	}
	virtual ~round_sense() {

	}
	virtual void on_enter() {

	}//���볡��
	virtual void on_update(int time) {
		if (update)
			update(time);
	}//���³���
	virtual void on_draw() {
		if (draw)
			draw();
	}//�滭����
	virtual void on_input(const ExMessage& mes) {
		if (input)
			input(mes);
	}//��������
	virtual void on_exit() {
		sensemanager->switch_to(menusense);
	}//�˳�����

	//�ⲿ����
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