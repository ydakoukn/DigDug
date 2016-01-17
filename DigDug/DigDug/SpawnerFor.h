#pragma once
#include "Spawner.h"
template <class Type>
class SpawnerFor :
	public Spawner
{
public:
	SpawnerFor(){}
	~SpawnerFor(){}

	virtual std::shared_ptr<EnemyBase> Create()override{
		return std::make_shared<Type>();
	}
};

