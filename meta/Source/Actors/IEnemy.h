#ifndef IEnemy_h__
#define IEnemy_h__

#include "pch.h"
#include "IActor.h"

#define MAX_LIFE 5

class IEnemy : public IActor
{
	std::vector<HySprite2d *>		m_HeartList;
	uint32							m_uiCurHealth;

	float							m_fDeferDuration;

public:
	IEnemy(uint32 uiMaxHealth, float fDeferDuration, HyEntity2d *pParent = nullptr);
	virtual ~IEnemy();

	virtual void OnUpdate() override;

	void TakeDamage();
};

#endif // IEnemy_h__
