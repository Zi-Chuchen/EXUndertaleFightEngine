#pragma once
#include <easyx.h>

class sense {//�������
public:
	sense() = default;
	virtual ~sense() = default;
	virtual void on_enter() {}//���볡��
	virtual void on_update(int time) {}//���³���
	virtual void on_draw() {}//�滭����
	virtual void on_input(const ExMessage& mes) {}//��������
	virtual void on_exit() {}//�˳�����
protected:
};