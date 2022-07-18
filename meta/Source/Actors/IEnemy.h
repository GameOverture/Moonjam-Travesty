#ifndef IEnemy_h__
#define IEnemy_h__

#include "pch.h"
#include "IActor.h"

#define MAX_LIFE 5

class IEnemy : public IActor
{
public:
	std::vector<HySprite2d *>		m_HeartList;
	uint32							m_uiCurHealth;

	float							m_fDeferDuration;

	//HyPrimitive2d					m_Debug;

	bool							m_bHasWarCry;
	bool							m_bCanAttack;

public:
	IEnemy(uint32 uiMaxHealth, float fDeferDuration, HyEntity2d *pParent = nullptr);
	virtual ~IEnemy();

	virtual void OnUpdate() override;

	void DoWarcry();
	bool HasWarcry();

	bool CanAttack();

	float GetDeferTime();
	void TakeDamage();

	void AttackUpdate();

	void Kill();

	void AttackHouse();
};

#endif // IEnemy_h__
