#include "KeyCommandD.h"


KeyCommandD::KeyCommandD()
{
}


KeyCommandD::~KeyCommandD()
{
}

void KeyCommandD::Run(PlayerBase& player){
	player.GetStatus()._vector._x += 1.0f;
}