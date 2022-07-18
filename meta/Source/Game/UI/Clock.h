#ifndef Clock_h__
#define Clock_h__

#include "pch.h"

class Clock : public HyEntity2d
{
	HySprite2d			m_StaminaBox;
	HySprite2d			m_StaminaBar;
	HyProgressBar		m_TimeBar;
	HySprite2d			m_DayNight;
	HySprite2d			m_Cover;
	HyRackMeter			m_MoneyBox;

	HyTimer				m_Timer;

public:
	Clock(HyEntity2d *pParent = nullptr);
	virtual ~Clock();

	virtual void OnUpdate() override;

	void Reset();
	void Start();
	void Pause();
	void OnSleep();

	int64 GetMoney();
	void OffsetMoney(int64 iOffsetAmt, float fDuration);
	void SetMoney(int64 iAmt, float fDuration);

	int64 GetCurWorkProfit();
	float GetPercentOfDayLeft();
};

#endif // Clock_h__
