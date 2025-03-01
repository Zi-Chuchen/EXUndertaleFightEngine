#pragma once
#include <easyx.h>
#include <vector>

#pragma comment(lib,"winmm.lib")

class audio {
public:
	enum class name {
		choose,
		choose_yes,
		add_hp,
		after_fight,
		after_GB,
		after_into_fight,
		after_player_died,
		before_GB,
		before_into_fight,
		before_player_died,
		enemy_died,
		get_hurt,
		improve_LV,
		knife_fight,
		return_,
		save,
		switch_soul
	};
	audio() {
		mciSendString(_T("open resourses\\music\\choose.wav alias choose"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\choose_yes.wav alias choose_yes"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\add_hp.wav alias add_hp"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\after_fight.wav alias after_fight"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\after_GB.wav alias after_GB"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\after_into_fight.wav alias after_into_fight"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\after_player_died.wav alias after_player_died"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\before_GB.wav alias before_GB"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\before_into_fight.wav alias before_into_fight"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\before_player_died.wav alias before_player_died"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\enemy_died.wav alias enemy_died"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\get_hurt.wav alias get_hurt"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\improve_LV.wav alias improve_LV"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\knife_fight.wav alias knife_fight"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\return_.wav alias return_"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\save.wav alias save"), NULL, 0, NULL);
		mciSendString(_T("open resourses\\music\\switch_soul.wav alias switch_soul"), NULL, 0, NULL);
	}
	void push(name m) {
		if (!m_list.empty()) {
			if (m_list.back() != m) {
				m_list.push_back(m);
			}

		}
		else {
			m_list.push_back(m);
		}

	}
	void play() {
		for (int i = 0; i < m_list.size(); i++) {
			once_play(m_list[i]);
		}
		reset();
	}
	void reset() {
		m_list.clear();
	}
	void pop() {
		if (!m_list.empty()) {
			m_list.pop_back();
		}
	}
private:
	void once_play(name n) {
		switch (n)
		{
		case name::choose:
			mciSendString(_T("play choose from 0"), NULL, 0, NULL);
			break;
		case name::choose_yes:
			mciSendString(_T("play choose_yes from 0"), NULL, 0, NULL);
			break;
		case name::add_hp:
			mciSendString(_T("play add_hp from 0"), NULL, 0, NULL);
			break;
		case name::after_fight:
			mciSendString(_T("play after_fight from 0"), NULL, 0, NULL);
			break;
		case name::after_GB:
			mciSendString(_T("play after_GB from 0"), NULL, 0, NULL);
			break;
		case name::after_into_fight:
			mciSendString(_T("play after_into_fight from 0"), NULL, 0, NULL);
			break;
		case name::after_player_died:
			mciSendString(_T("play after_player_died from 0"), NULL, 0, NULL);
			break;
		case name::before_GB:
			mciSendString(_T("play before_GB from 0"), NULL, 0, NULL);
			break;
		case name::before_into_fight:
			mciSendString(_T("play before_into_fight from 0"), NULL, 0, NULL);
			break;
		case name::before_player_died:
			mciSendString(_T("play before_player_died from 0"), NULL, 0, NULL);
			break;
		case name::enemy_died:
			mciSendString(_T("play enemy_died from 0"), NULL, 0, NULL);
			break;
		case name::get_hurt:
			mciSendString(_T("play get_hurt from 0"), NULL, 0, NULL);
			break;
		case name::improve_LV:
			mciSendString(_T("play improve_LV from 0"), NULL, 0, NULL);
			break;
		case name::knife_fight:
			mciSendString(_T("play knife_fight from 0"), NULL, 0, NULL);
			break;
		case name::return_:
			mciSendString(_T("play return_ from 0"), NULL, 0, NULL);
			break;
		case name::save:
			mciSendString(_T("play save from 0"), NULL, 0, NULL);
			break;
		case name::switch_soul:
			mciSendString(_T("play switch_soul from 0"), NULL, 0, NULL);
			break;
		}
	}
	std::vector<name> m_list;
};