#include "KeyCommandW.h"

KeyCommandW::KeyCommandW()
{
}


KeyCommandW::~KeyCommandW()
{
}

void KeyCommandW::Run(PlayerBase& player){
	player.GetStatus()._vector._y += 1.0f;
}