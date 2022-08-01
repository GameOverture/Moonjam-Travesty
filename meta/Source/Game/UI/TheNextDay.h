#ifndef TheNextDay_h__
#define TheNextDay_h__

#include "pch.h"

class TheNextDay : public HyEntity2d
{
	HyPrimitive2d			m_BG;
	HyPrimitive2d			m_Oval;

	HyText2d				m_T;
	HyText2d				m_H;
	HyText2d				m_E;

	HyText2d				m_N;
	HyText2d				m_E2;
	HyText2d				m_X;
	HyText2d				m_T2;

	HyText2d				m_D;
	HyText2d				m_A;
	HyText2d				m_Y;

	bool					m_bStarted;

public:
	TheNextDay(HyEntity2d *pParent = nullptr);
	virtual ~TheNextDay();

	virtual void OnUpdate() override;

	void Reset(bool bChangeToHexed);
	void Start();
	bool IsFinished();
};

#endif // TheNextDay_h__
