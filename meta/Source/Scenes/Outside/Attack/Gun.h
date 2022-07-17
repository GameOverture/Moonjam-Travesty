#ifndef Gun_h__
#define Gun_h__

#include "pch.h"
#include "IItem.h"

class Gun : public IItem
{
	HySprite2d			m_Base;
	HySprite2d			m_Top;

	HyPrimitive2d		m_Debug;

public:
	Gun(HyEntity2d *pParent = nullptr);
	virtual ~Gun();

	virtual void OnUpdate() override;

	virtual void StartSetupLoop(float fDuration) override;
};

#endif // Gun_h__
