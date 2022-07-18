#ifndef Computer_h__
#define Computer_h__

#include "pch.h"

class Computer : public HyUiContainer
{
	HySprite2d		m_Dialog;

	HyButton		m_ExitBtn;

	HyButton		m_WorkBtn;

	HyText2d		m_BuyCumPrice;
	HyButton		m_BuyCumBtn;

	HyText2d		m_BuyGunPrice;
	HyButton		m_BuyGunBtn;

public:
	Computer(HyEntity2d *pParent = nullptr);
	virtual ~Computer();

	virtual float OnBeginShow() override;
	virtual void OnShown() override;
	virtual float OnBeginHide() override;
	virtual void OnHidden() override;

	virtual void OnContainerUpdate() override;

	static void OnExitBtn(HyButton *pBtn, void *pData);
	static void OnWorkBtn(HyButton *pBtn, void *pData);
	static void OnCumBtn(HyButton *pBtn, void *pData);
	static void OnGunBtn(HyButton *pBtn, void *pData);
};

#endif // Computer_h__
