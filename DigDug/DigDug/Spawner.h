#pragma once
/*
	すぽなー基底クラス

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

