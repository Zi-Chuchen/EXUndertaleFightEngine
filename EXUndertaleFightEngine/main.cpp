#include <easyx.h>
#include "camera.h"
#include "audio.h"
#include "sense_types.h"
#include "D2Ddraw.h"
#include "fight_round.h"
#pragma comment(lib,"winmm.lib")

IMAGE window_displayer;

IMAGE gameover;
IMAGE battlebg;
IMAGE blconwdshrt;
IMAGE dumbtarget;
IMAGE hpname;

camera* main_camera = NULL;

audio* audio_player = NULL;

load_sense* loadsense = NULL;
menu_sense* menusense = NULL;
fight_sense* fightsense = NULL;
mercy_sense* mercysense = NULL;
item_sense* itemsense = NULL;
act_sense* actsense = NULL;
std::vector<round_sense> roundsenses;

sense_manager* sensemanager = NULL;//场景管理者

D2Ddraw* D2D = NULL;
void setup() {
	initgraph(800, 600, EX_SHOWCONSOLE | EX_NOMINIMIZE);

	BeginBatchDraw();

	window_displayer.Resize(getwidth(), getheight());

	D2D = new D2Ddraw(&window_displayer);

	loadimage(&gameover, _T("resourses\\image\\battle_screen\\spr_gameoverbg.png"));
	loadimage(&battlebg, _T("resourses\\image\\battle_screen\\spr_battlebg.png"));
	loadimage(&blconwdshrt, _T("resourses\\image\\battle_screen\\spr_blconwdshrt.png"));
	loadimage(&dumbtarget, _T("resourses\\image\\battle_screen\\spr_dumbtarget.png"));
	loadimage(&hpname, _T("resourses\\image\\battle_screen\\spr_hpname.png"));

	AddFontResourceEx(_T("resourses\\font\\undertaleuse.ttf"), FR_PRIVATE, NULL);//字体

	loadsense = new load_sense();
	menusense = new menu_sense();
	fightsense = new fight_sense();
	mercysense = new mercy_sense();
	itemsense = new item_sense();
	actsense = new act_sense();
	round_setup();

	main_camera = new camera();

	audio_player = new audio();

	sensemanager = new sense_manager();
	sensemanager->switch_to(&roundsenses[0]);
}
void setdown() {
	delete D2D;

	delete loadsense;
	delete menusense;
	delete fightsense;
	delete mercysense;
	delete itemsense;
	delete actsense;

	delete main_camera;

	delete audio_player;

	EndBatchDraw();
	closegraph();
}
int main() {
	setup();
	ExMessage mes;//获取的消息
	int FPS = 60;//帧率
	DWORD b_t = 0;
	DWORD e_t = 0;
	float i = 3.1;
	//main_camera->set_rotate_o({ 30,30 });
	while (true) {
		DWORD begin_time = GetTickCount();
		while (peekmessage(&mes)) {//消息处理
			sensemanager->on_input(mes);
		}
		/*i += 0.1;
		main_camera->set_rotate_r(i);*/
		e_t = GetTickCount();
		if (b_t == 0)//排除
			b_t = e_t;
		sensemanager->on_update(e_t - b_t);
		b_t = e_t;
		sensemanager->on_draw();
		DWORD end_time = GetTickCount();
		if (end_time - begin_time < 1000 / FPS) {
			Sleep(1000 / FPS - (end_time - begin_time));
		}

	}
	return 0;
}