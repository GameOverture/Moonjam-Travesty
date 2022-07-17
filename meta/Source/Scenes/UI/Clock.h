#ifndef Clock_h__
#define Clock_h__

#include "pch.h"

class Clock : public HyEntity2d
{
	HySprite2d			m_StaminaBox;
	HySprite2d			m_StaminaBar;
	HySprite2d			m_DayNight;
	HySprite2d			m_Cover;

public:
	Clock(HyEntity2d *pParent = nullptr);
	virtual ~Clock();

	virtual void OnUpdate() override;
};

#endif // Clock_h__
