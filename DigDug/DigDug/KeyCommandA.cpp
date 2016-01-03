#include "KeyCommandA.h"


KeyCommandA::KeyCommandA()
{
}


KeyCommandA::~KeyCommandA()
{
}

void KeyCommandA::Run(PlayerBase& player){
	player.GetStatus()._vector._x -= 1.0f;
}