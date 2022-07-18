#ifndef EnemyBorpa_h__
#define EnemyBorpa_h__

#include "pch.h"
#include "IEnemy.h"

class EnemyBorpa : public IEnemy
{
	HySprite2d		m_Borpa;

public:
	EnemyBorpa(uint32 uiHealth, float fDeferDuration, HyEntity2d *pParent = nullptr);
	virtual ~EnemyBorpa();

	virtual void OnUpdate() override;
};

#endif // EnemyBorpa_h__
