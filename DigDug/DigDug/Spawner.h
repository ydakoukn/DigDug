#pragma once
/*
	‚·‚Û‚È[Šî’êƒNƒ‰ƒX

*/
#include "EnemyBase.h"
#include <memory>
class Spawner
{
public:
	Spawner(){}
	virtual ~Spawner() = default;
	virtual std::shared_ptr<EnemyBase> Create() = 0;
};

