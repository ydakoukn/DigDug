#ifndef KEYCOMMANDD_H
#define KEYCOMMANDD_H
#include "KeyCommand.h"
class KeyCommandD :
	public KeyCommand
{
public:
	KeyCommandD();
	~KeyCommandD(); 
	virtual void Run(PlayerBase&)override;
};

#endif