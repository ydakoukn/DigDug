#ifndef KEYCOMMAND_H
#define KEYCOMMAND_H
#include "PlayerBase.h"
/*
	�R�}���h�̊��N���X
	�����L�[���͂𑝂₷�Ƃ��͂��̃N���X���p������

*/
class KeyCommand
{
public:
	virtual ~KeyCommand()=default;

	virtual void Run(PlayerBase&) = 0;
};

#endif