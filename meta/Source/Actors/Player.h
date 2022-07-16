#ifndef Player_h__
#define Player_h__

#include "pch.h"

class Player : public HyEntity2d
{
public:
	Player(HyEntity2d *pParent = nullptr);
	virtual ~Player();

	virtual void OnUpdate() override;
};

#endif // Player_h__
