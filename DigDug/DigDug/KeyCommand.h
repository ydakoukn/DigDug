#ifndef KEYCOMMAND_H
#define KEYCOMMAND_H
#include "PlayerBase.h"
/*
	コマンドの基底クラス
	何かキー入力を増やすときはこのクラスを継承する

*/
class KeyCommand
{
public:
	virtual ~KeyCommand()=default;

	virtual void Run(PlayerBase&) = 0;
};

#endif