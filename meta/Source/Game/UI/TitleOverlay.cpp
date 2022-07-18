#include "pch.h"
#include "TitleOverlay.h"

TitleOverlay::TitleOverlay(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_WhiteCover(this),
	m_MainTitle("", "Main", this),
	m_SubTitle("", "Main", this),
	m_PressToStart("", "Main", this),
	m_HowToPanel("UI/Title", "HowToPanel", this),
	m_Noted("UI/Title", "Noted", this),
	m_iPage(-1),
	m_bIsFinished(false),
	m_bInitialWait(true),
	m_fElapsedTime(0.0f)
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_LoadCover);

	m_WhiteCover.shape.SetAsBox(HyEngine::Window().GetWidthF(), HyEngine::Window().GetHeightF());
	m_WhiteCover.SetTint(HyColor::White);
	m_WhiteCover.alpha.Set(0.42f);

	m_MainTitle.SetText("A Means to an End");
	m_MainTitle.SetState(1);
	m_MainTitle.scale.Set(1.8f, 1.8f);
	m_MainTitle.SetTextAlignment(HYALIGN_Center);
	m_MainTitle.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.75f));
	
	m_SubTitle.SetText("A Travesty on Daily Life");
	m_SubTitle.SetState(2);
	m_SubTitle.scale.Set(0.75f, 0.75f);
	m_SubTitle.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.75f));
	m_SubTitle.pos.Offset(0.0f, -m_MainTitle.GetHeight());

	m_PressToStart.SetText("Press space to start");
	m_PressToStart.SetState(2);
	m_PressToStart.scale.Set(1.0f, 1.0f);
	m_PressToStart.SetTextAlignment(HYALIGN_Center);
	m_PressToStart.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.4f));

	m_MainTitle.alpha.Set(0.0f);
	m_SubTitle.alpha.Set(0.0f);
	m_PressToStart.alpha.Set(0.0f);

	m_HowToPanel.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.5f));
	m_HowToPanel.SetVisible(false);

	m_Noted.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.5f));
	m_Noted.pos.Offset(-325.0f, -250.0f);
	m_Noted.SetVisible(false);
}

/*virtual*/ TitleOverlay::~TitleOverlay()
{
}

/*virtual*/ void TitleOverlay::OnUpdate() /*override*/
{
	if(m_bInitialWait)
	{
		m_fElapsedTime += HyEngine::DeltaTime();
		if(m_fElapsedTime >= 1.5f)
		{
			m_MainTitle.alpha.Tween(1.0f, 0.5f);
			m_SubTitle.alpha.Tween(1.0f, 0.5f);
			m_PressToStart.alpha.Tween(1.0f, 0.5f);
			m_bInitialWait = false;
		}
	}
	else
	{
		if(HyEngine::Input().IsActionReleased(INPUT_Jump))
		{
			m_MainTitle.alpha.Tween(0.0f, 0.5f);
			m_SubTitle.alpha.Tween(0.0f, 0.5f);
			m_PressToStart.alpha.Tween(0.0f, 0.5f);

			m_iPage++;
			if(m_iPage >= m_HowToPanel.GetNumStates())
			{
				m_bIsFinished = true;
			}
			else
			{
				m_Noted.SetVisible(true);
				m_HowToPanel.SetVisible(true);
				m_HowToPanel.SetState(m_iPage);
			}
		}
	}
}

bool TitleOverlay::IsFinished()
{
	return m_bIsFinished;
}
