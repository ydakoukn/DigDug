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
	// ���]�𒼂�
	player.GetStatus()._rotation._z = NULL;
	// �E�ɔ��]
	player.GetStatus()._rotation._y = kRightDirection;
	player.GetStatus()._position._x += player.GetStatus()._speed;
}