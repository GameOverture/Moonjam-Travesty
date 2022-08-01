#ifndef EnemyGums_h__
#define EnemyGums_h__

#include "pch.h"
#include "IEnemy.h"

class EnemyGums : public IEnemy
{
	HySprite2d		m_Gums;

public:
	EnemyGums(uint32 uiHealth, float fDeferDuration, HyEntity2d *pParent = nullptr);
	virtual ~EnemyGums();

	virtual void OnUpdate() override;

	virtual void OnAttackUpdate() override;
};

#endif // EnemyGums_h__
