#include "KeyCommandS.h"

namespace{
	const int kDownDirection = -90;
}

KeyCommandS::KeyCommandS()
{
}


KeyCommandS::~KeyCommandS()
{
}

void KeyCommandS::Run(PlayerBase& player){
	player.GetStatus()._rotation._z = kDownDirection;
	player.GetStatus()._position._y -= player.GetStatus()._speed;
}