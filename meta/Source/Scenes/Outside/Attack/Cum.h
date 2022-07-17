#ifndef Cum_h__
#define Cum_h__

#include "pch.h"
#include "IItem.h"

class Cum : public IItem
{
	HyPrimitive2d	m_Ground;

public:
	Cum(HyEntity2d *pParent = nullptr);
	virtual ~Cum();

	virtual void OnUpdate() override;

	virtual void StartSetupLoop(float fDuration) override;
};

#endif // Cum_h__
