#ifndef KEYCOMMANDA_H
#define KEYCOMMANDA_H
#include "KeyCommand.h"
class KeyCommandA :
	public KeyCommand
{
public:
	KeyCommandA();
	~KeyCommandA();
	virtual void Run(PlayerBase&)override;
};

#endif