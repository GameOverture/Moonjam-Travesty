#include "pch.h"
#include "GameOver.h"

GameOver::GameOver(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_GameOver("", "Main", this),
	m_StoryEnds("Sounds", "StoryEnd", this)
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_LoadCover);

	m_GameOver.SetText("Game Over");
	m_GameOver.SetState(1);
	m_GameOver.scale.Set(1.8f, 1.8f);
	m_GameOver.SetTextAlignment(HYALIGN_Center);
	m_GameOver.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.75f));
}

/*virtual*/ GameOver::~GameOver()
{
}

/*virtual*/ void GameOver::OnUpdate() /*override*/
{
}
