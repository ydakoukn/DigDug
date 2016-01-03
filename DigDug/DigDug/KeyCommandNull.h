#ifndef KEYCOMMANDNULL_H
#define KEYCOMMANDNULL_H
#include "KeyCommand.h"
class KeyCommandNull :
	public KeyCommand
{
public:
	KeyCommandNull();
	~KeyCommandNull();
	virtual void Run(PlayerBase&)override;
};

#endif