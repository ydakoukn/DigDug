#include "KeyCommandW.h"

namespace{
	const int kUpDirection = 90;
}

KeyCommandW::KeyCommandW()
{
}


KeyCommandW::~KeyCommandW()
{
}

void KeyCommandW::Run(PlayerBase& player){
	// 上を向かせる
	player.GetStatus()._rotation._z = kUpDirection;
	player.GetStatus()._position._y += player.GetStatus()._speed;
}