#pragma once
#include "sense.h"
#include "utils.h"
#include "camera.h"
#include <vector>

extern IMAGE window_displayer;

extern camera* main_camera;

class sense_manager {//场景状态管理者
	
public:
	sense_manager() = default;
	~sense_manager() = default;
	void switch_to(sense* set_sense) {
		if (now_sense)
			now_sense->on_exit();
		now_sense = set_sense;
		now_sense->on_enter();
	}
	void on_update(int time) {
		now_sense->on_update(time);
	}
	void on_draw() {
		SetWorkingImage(&window_displayer);
		now_sense->on_draw();
		SetWorkingImage();
		rotate_putimage(&window_displayer, main_camera->get_rotate_r(), main_camera->get_rotate_o());
		FlushBatchDraw();
		cleardevice();
	}
	void on_input(const ExMessage& mes) {
		now_sense->on_input(mes);
	}
private:
	sense* now_sense = NULL;//目前场景状态
};