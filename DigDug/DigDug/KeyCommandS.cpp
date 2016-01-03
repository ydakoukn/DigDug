#include "KeyCommandS.h"


KeyCommandS::KeyCommandS()
{
}


KeyCommandS::~KeyCommandS()
{
}

void KeyCommandS::Run(PlayerBase& player){
	player.GetStatus()._vector._y -= 1.0f;
}