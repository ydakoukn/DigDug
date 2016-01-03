#ifndef KEYCOMMANDW_H
#define KEYCOMMANDW_H
#include "KeyCommand.h"
class KeyCommandW :
	public KeyCommand
{
public:
	KeyCommandW();
	~KeyCommandW();

	virtual void Run(PlayerBase&)override;
};

#endif