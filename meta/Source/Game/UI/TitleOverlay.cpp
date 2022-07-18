#include "pch.h"
#include "TitleOverlay.h"

TitleOverlay::TitleOverlay(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_WhiteCover(this),
	m_MainTitle("", "Main", this),
	m_SubTitle("", "Main", this),
	m_PressToStart("", "Main", this)
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_LoadCover);

	m_WhiteCover.shape.SetAsBox(HyEngine::Window().GetWidthF(), HyEngine::Window().GetHeightF());
	m_WhiteCover.SetTint(HyColor::White);
	m_WhiteCover.alpha.Set(0.25f);

	m_MainTitle.SetText("A Means to an End");
	m_MainTitle.SetState(1);
	m_MainTitle.scale.Set(1.8f, 1.8f);
	m_MainTitle.SetTextAlignment(HYALIGN_Center);
	m_MainTitle.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.75f));
	
	m_SubTitle.SetText("A Travesty on Daily Life");
	m_SubTitle.SetState(2);
	m_SubTitle.scale.Set(1.0f, 1.0f);
	m_SubTitle.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.75f));
	m_SubTitle.pos.Offset(0.0f, -m_MainTitle.GetHeight());

	m_PressToStart.SetText("Press space to start");
	m_PressToStart.SetState(2);
	m_PressToStart.scale.Set(1.0f, 1.0f);
	m_PressToStart.SetTextAlignment(HYALIGN_Center);
	m_PressToStart.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.4f));
}

/*virtual*/ TitleOverlay::~TitleOverlay()
{
}

/*virtual*/ void TitleOverlay::OnUpdate() /*override*/
{
}
