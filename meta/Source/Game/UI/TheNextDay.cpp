#include "pch.h"
#include "TheNextDay.h"

TheNextDay::TheNextDay(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_BG(this),
	m_Oval(this),
	m_T("UI", "TheNextDay", this),
	m_H("UI", "TheNextDay", this),
	m_E("UI", "TheNextDay", this),
	m_N("UI", "TheNextDay", this),
	m_E2("UI", "TheNextDay", this),
	m_X("UI", "TheNextDay", this),
	m_T2("UI", "TheNextDay", this),
	m_D("UI", "TheNextDay", this),
	m_A("UI", "TheNextDay", this),
	m_Y("UI", "TheNextDay", this),
	m_bStarted(false)
{
	SetDisplayOrder(DISPLAYORDER_Bills + 500);
	UseWindowCoordinates();

	m_BG.shape.SetAsBox(HyEngine::Window().GetWidthF(), HyEngine::Window().GetHeightF());
	m_BG.SetTint(HyColor::Black);

	m_Oval.shape.SetAsCircle(HyEngine::Window().GetWidthF(0.4f));
	m_Oval.scale.Set(1.0f, 0.75f);
	m_Oval.SetTint(HyColor::DarkGray);
	m_Oval.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.5f));
	
	float fStartX = HyEngine::Window().GetWidthF(0.3f);
	m_T.SetText("T");
	m_T.pos.Set(fStartX, HyEngine::Window().GetHeightF(0.5f));

	m_H.SetText("H");
	m_H.pos.Set(fStartX + m_T.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	
	m_E.SetText("E");
	m_E.pos.Set(fStartX + m_T.GetWidth() + m_H.GetWidth(), HyEngine::Window().GetHeightF(0.5f));

	
	
	fStartX = HyEngine::Window().GetWidthF(0.45f);
	m_N.SetText("N");
	m_N.pos.Set(fStartX, HyEngine::Window().GetHeightF(0.5f));
	
	m_E2.SetText("E");
	m_E2.pos.Set(fStartX + m_N.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	
	m_X.SetText("X");
	m_X.pos.Set(fStartX + m_N.GetWidth() + m_E2.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	
	m_T2.SetText("T");
	m_T2.pos.Set(fStartX + m_N.GetWidth() + m_E2.GetWidth() + m_X.GetWidth(), HyEngine::Window().GetHeightF(0.5f));

	
	
	fStartX = HyEngine::Window().GetWidthF(0.6f);
	m_D.SetText("D");
	m_D.pos.Set(fStartX, HyEngine::Window().GetHeightF(0.5f));

	m_A.SetText("A");
	m_A.pos.Set(fStartX + m_D.GetWidth(), HyEngine::Window().GetHeightF(0.5f));

	m_Y.SetText("Y");
	m_Y.pos.Set(fStartX + m_D.GetWidth() + m_A.GetWidth(), HyEngine::Window().GetHeightF(0.5f));

	Reset();
}

/*virtual*/ TheNextDay::~TheNextDay()
{
}

/*virtual*/ void TheNextDay::OnUpdate() /*override*/
{
}

void TheNextDay::Reset()
{
	float fStartX = HyEngine::Window().GetWidthF(0.3f);
	m_T.pos.Set(fStartX, HyEngine::Window().GetHeightF(0.5f));
	m_T.scale.Set(1.0f, 1.0f);
	m_H.pos.Set(fStartX + m_T.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	m_H.scale.Set(1.0f, 1.0f);
	m_E.pos.Set(fStartX + m_T.GetWidth() + m_H.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	m_E.scale.Set(1.0f, 1.0f);

	fStartX = HyEngine::Window().GetWidthF(0.45f);
	m_N.pos.Set(fStartX, HyEngine::Window().GetHeightF(0.5f));
	m_N.scale.Set(1.0f, 1.0f);
	m_E2.pos.Set(fStartX + m_N.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	m_E2.scale.Set(1.0f, 1.0f);
	m_X.pos.Set(fStartX + m_N.GetWidth() + m_E2.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	m_X.scale.Set(1.0f, 1.0f);
	m_T2.pos.Set(fStartX + m_N.GetWidth() + m_E2.GetWidth() + m_X.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	m_T2.scale.Set(1.0f, 1.0f);

	fStartX = HyEngine::Window().GetWidthF(0.6f);
	m_D.pos.Set(fStartX, HyEngine::Window().GetHeightF(0.5f));
	m_D.scale.Set(1.0f, 1.0f);
	m_A.pos.Set(fStartX + m_D.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	m_A.scale.Set(1.0f, 1.0f);
	m_Y.pos.Set(fStartX + m_D.GetWidth() + m_A.GetWidth(), HyEngine::Window().GetHeightF(0.5f));
	m_Y.scale.Set(1.0f, 1.0f);

	m_bStarted = false;
}

#define DOWN_RAND -100.0f, -50.0f
#define UP_RAND -100.0f, -50.0f

void TheNextDay::Start()
{
	m_bStarted = true;

	const float fDURATION = 4.2f;

	m_T.scale.Tween(1.0f, 3.0f, fDURATION);
	m_T.pos.TweenOffset(0.0f, HyRand::Range(DOWN_RAND), fDURATION);
	m_H.scale.Tween(1.0f, 3.0f, fDURATION);
	m_H.pos.TweenOffset(0.0f, HyRand::Range(UP_RAND), fDURATION);
	m_E.scale.Tween(1.0f, 3.0f, fDURATION);
	m_E.pos.TweenOffset(0.0f, HyRand::Range(DOWN_RAND), fDURATION);
	m_N.scale.Tween(1.0f, 3.0f, fDURATION);
	m_N.pos.TweenOffset(0.0f, HyRand::Range(UP_RAND), fDURATION);
	m_E2.scale.Tween(1.0f, 3.0f, fDURATION);
	m_E2.pos.TweenOffset(0.0f, HyRand::Range(DOWN_RAND), fDURATION);
	m_X.scale.Tween(1.0f, 3.0f, fDURATION);
	m_X.pos.TweenOffset(0.0f, HyRand::Range(UP_RAND), fDURATION);
	m_T2.scale.Tween(1.0f, 3.0f, fDURATION);
	m_T2.pos.TweenOffset(0.0f, HyRand::Range(DOWN_RAND), fDURATION);
	m_D.scale.Tween(1.0f, 3.0f, fDURATION);
	m_D.pos.TweenOffset(0.0f, HyRand::Range(UP_RAND), fDURATION);
	m_A.scale.Tween(1.0f, 3.0f, fDURATION);
	m_A.pos.TweenOffset(0.0f, HyRand::Range(DOWN_RAND), fDURATION);
	m_Y.scale.Tween(1.0f, 3.0f, fDURATION);
	m_Y.pos.TweenOffset(0.0f, HyRand::Range(UP_RAND), fDURATION);
}

bool TheNextDay::IsFinished()
{
	return (m_bStarted && m_T.pos.IsAnimating() == false);
}
