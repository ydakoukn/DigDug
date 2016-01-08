#include "KeyCommandD.h"
namespace{
	const int kRightDirection = 0;
}

KeyCommandD::KeyCommandD()
{
}


KeyCommandD::~KeyCommandD()
{
}

void KeyCommandD::Run(PlayerBase& player){
	// ”½“]‚ð’¼‚·
	player.GetStatus()._rotation._z = NULL;
	// ‰E‚É”½“]
	player.GetStatus()._rotation._y = kRightDirection;
	player.GetStatus()._position._x += player.GetStatus()._speed;
}