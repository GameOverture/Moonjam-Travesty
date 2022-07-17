#ifndef IItem_h__
#define IItem_h__

#include "pch.h"
#include "ProgressBar.h"

class IItem : public HyEntity2d
{
protected:
	const float					m_fEFFECTIVE_RANGE;

	ItemState					m_eItemState;

	HySprite2d					m_Package;

public:
	IItem(std::string sPackageName, float fEffectiveRange, HyEntity2d *pParent = nullptr);
	virtual ~IItem();

	virtual void OnUpdate() override;

	float GetRange() const;

	ItemState GetItemState() const;
	void SetItemState(ItemState eState);

	HySprite2d &GetPackage();

	virtual void StartSetupLoop(float fDuration) = 0;
};

#endif // IItem_h__
