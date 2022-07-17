#include "pch.h"
#include "Computer.h"

Computer::Computer(HyEntity2d *pParent /*= nullptr*/) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(820, 650, 2), pParent),
	m_Dialog("UI", "Dialog", this),
	m_WorkBtn(HyPanelInit("UI", "WorkBtn")),
	m_WorkLabel(HyPanelInit(), "UI", "Computer"),
	m_BuyCumBtn(HyPanelInit("UI", "BuyCumBtn")),
	m_BuyCumLabel(HyPanelInit(), "UI", "Computer"),
	m_BuyGunBtn(HyPanelInit("UI", "BuyGunBtn")),
	m_BuyGunLabel(HyPanelInit(), "UI", "Computer")
{
	SetDisplayOrder(DISPLAYORDER_Computer);
	m_Dialog.SetDisplayOrder(DISPLAYORDER_Computer - 1);
	m_Panel.alpha.Set(0.0f);
	m_WorkBtn.SetButtonClickedCallback(OnWorkBtn, this);
	m_WorkBtn.scale.Set(0.5f, 0.5f);
	m_WorkLabel.SetText("Start Work - Ends day, collects cash");
	m_BuyCumBtn.SetButtonClickedCallback(OnCumBtn, this);
	m_BuyCumBtn.scale.Set(0.5f, 0.5f);
	m_BuyCumLabel.SetText("Buy Sticky Paste");
	m_BuyGunBtn.SetButtonClickedCallback(OnGunBtn, this);
	m_BuyGunBtn.scale.Set(0.5f, 0.5f);
	m_BuyGunLabel.SetText("Buy Self Defense Drone");

	HyLayoutHandle hWorkRow = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_WorkBtn, hWorkRow);
	InsertWidget(m_WorkLabel, hWorkRow);

	HyLayoutHandle hBuyRow = InsertLayout(HYORIEN_Horizontal);
	
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hBuyRow);
	HyLayoutHandle hCumCol = InsertLayout(HYORIEN_Vertical, hBuyRow);
	InsertWidget(m_BuyCumLabel, hCumCol);
	InsertWidget(m_BuyCumBtn, hCumCol);
	
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hBuyRow);
	HyLayoutHandle hGunCol = InsertLayout(HYORIEN_Vertical, hBuyRow);
	InsertWidget(m_BuyGunLabel, hGunCol);
	InsertWidget(m_BuyGunBtn, hGunCol);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hBuyRow);
}

/*virtual*/ Computer::~Computer()
{
}

/*virtual*/ void Computer::OnContainerUpdate() /*override*/
{
}

/*static*/ void Computer::OnExitBtn(HyButton *pBtn, void *pData)
{
}

/*static*/ void Computer::OnWorkBtn(HyButton *pBtn, void *pData)
{
}

/*static*/ void Computer::OnCumBtn(HyButton *pBtn, void *pData)
{
}

/*static*/ void Computer::OnGunBtn(HyButton *pBtn, void *pData)
{
}
