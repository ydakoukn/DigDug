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
	// ���]�𒼂�
	player.GetStatus()._rotation._z = NULL;
	// ���ɔ��]
	player.GetStatus()._rotation._y = kLeftDirection;
	player.GetStatus()._position._x -= player.GetStatus()._speed;
}