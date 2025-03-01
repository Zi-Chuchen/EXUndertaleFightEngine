#pragma once
#include "round_sense.h"
#include <vector>

extern std::vector<round_sense> roundsenses;

#define round_num 20

void round_setup() {
	roundsenses.resize(round_num);
}