#ifndef TitleOverlay_h__
#define TitleOverlay_h__

#include "pch.h"

class TitleOverlay : public HyEntity2d
{
	HyPrimitive2d	m_WhiteCover;

	HyText2d		m_MainTitle;
	HyText2d		m_SubTitle;

	HyText2d		m_PressToStart;

	HySprite2d		m_HowToPanel;
	HySprite2d		m_Noted;

	int				m_iPage;
	bool			m_bIsFinished;

	bool			m_bInitialWait;
	float			m_fElapsedTime;

public:
	TitleOverlay(HyEntity2d *pParent = nullptr);
	virtual ~TitleOverlay();

	virtual void OnUpdate() override;

	bool IsFinished();
};

#endif // TitleOverlay_h__
