#ifndef GameOver_h__
#define GameOver_h__

#include "pch.h"

class GameOver : public HyEntity2d
{
public:
	HyText2d		m_GameOver;

	HyAudio2d		m_StoryEnds;

public:
	GameOver(HyEntity2d *pParent = nullptr);
	virtual ~GameOver();

	virtual void OnUpdate() override;
};

#endif // GameOver_h__
