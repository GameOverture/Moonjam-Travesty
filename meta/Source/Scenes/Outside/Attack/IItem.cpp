#include "pch.h"
#include "IItem.h"

IItem::IItem(std::string sPackageName, float fEffectiveRange, HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_fEFFECTIVE_RANGE(fEffectiveRange),
	m_eItemState(ITEMSTATE_Packaged),
	m_Package("Outside/Attack", sPackageName, this)
{
	m_Package.pos.Set(0.0f, 50.0f);
}

/*virtual*/ IItem::~IItem()
{
}

/*virtual*/ void IItem::OnUpdate() /*override*/
{
}

float IItem::GetRange() const
{
	return m_fEFFECTIVE_RANGE;
}

ItemState IItem::GetItemState() const
{
	return m_eItemState;
}

void IItem::SetItemState(ItemState eState)
{
	m_eItemState = eState;
}

HySprite2d &IItem::GetPackage()
{
	return m_Package;
}
