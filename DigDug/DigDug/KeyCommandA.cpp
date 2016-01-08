#include "KeyCommandA.h"

namespace{
	const int kLeftDirection = 180;

}
KeyCommandA::KeyCommandA()
{
}


KeyCommandA::~KeyCommandA()
{
}

void KeyCommandA::Run(PlayerBase& player){
	// îΩì]ÇíºÇ∑
	player.GetStatus()._rotation._z = NULL;
	// ç∂Ç…îΩì]
	player.GetStatus()._rotation._y = kLeftDirection;
	player.GetStatus()._position._x -= player.GetStatus()._speed;
}