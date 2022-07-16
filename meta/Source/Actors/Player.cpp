#include "pch.h"
#include "Player.h"

Player::Player(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent)
{
}

/*virtual*/ Player::~Player()
{
}

/*virtual*/ void Player::OnUpdate() /*override*/
{
}
