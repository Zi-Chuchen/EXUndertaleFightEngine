#pragma once
#include "sense.h"
#include <iostream>
extern IMAGE gameover;

class load_sense:public sense {//场景框架
public:
	load_sense() {

	}
	virtual ~load_sense(){

	}
	virtual void on_enter() {

	}//进入场景
	virtual void on_update(int time) {

	}//更新场景
	virtual void on_draw() {
		
	}//绘画场景
	virtual void on_input(const ExMessage& mes) {

	}//处理输入
	virtual void on_exit() {

	}//退出场景
protected:
};