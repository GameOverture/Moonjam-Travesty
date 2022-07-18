#ifndef TitleOverlay_h__
#define TitleOverlay_h__

#include "pch.h"

class TitleOverlay : public HyEntity2d
{
	HyPrimitive2d	m_WhiteCover;

	HyText2d		m_MainTitle;
	HyText2d		m_SubTitle;

	HyText2d		m_PressToStart;

public:
	TitleOverlay(HyEntity2d *pParent = nullptr);
	virtual ~TitleOverlay();

	virtual void OnUpdate() override;
};

#endif // TitleOverlay_h__
