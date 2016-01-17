#pragma once
#include "EnemyBase.h"
class Enemy :
	public EnemyBase
{
	public:
		Enemy();
		~Enemy();

	private:
		virtual void CollideBuffer()override;
		virtual void InitializeBuffer()override;
		virtual void RenderBuffer()override;
		virtual void UpdateBuffer()override;

	private:
		float m_vec;
};

