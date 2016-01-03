#ifndef KEYCOMMANDS_H
#define KEYCOMMANDS_H
#include "KeyCommand.h"
class KeyCommandS :
	public KeyCommand
{
public:
	KeyCommandS();
	~KeyCommandS();
	virtual void Run(PlayerBase&)override;
};

#endif