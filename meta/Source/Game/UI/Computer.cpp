#include "pch.h"
#include "Computer.h"
#include "MoonjamTravesty.h"

Computer::Computer(HyEntity2d *pParent /*= nullptr*/) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(820, 650, 2), pParent),
	m_Dialog("UI", "Dialog", this),
	m_ExitBtn(HyPanelInit("UI", "ComputerExitBtn")),
	m_WorkBtn(HyPanelInit("UI", "WorkBtn"), "UI/Clock", "Text", 5, 34, 5, 34),
	m_WorkLabel(HyPanelInit(), "UI", "Computer"),
	m_ShopLabel(HyPanelInit(), "UI", "Computer"),
	m_BuyCumLabel(HyPanelInit(), "UI", "Computer"),
	m_BuyCumBtn(HyPanelInit("UI", "BuyCumBtn")),
	m_BuyGunLabel(HyPanelInit(), "UI", "Computer"),
	m_BuyGunBtn(HyPanelInit("UI", "BuyGunBtn"))
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Computer);
	m_Dialog.SetDisplayOrder(DISPLAYORDER_Computer - 1);
	m_Panel.alpha.Set(0.0f);
	m_ExitBtn.SetButtonClickedCallback(OnExitBtn, this);
	
	m_WorkBtn.SetButtonClickedCallback(OnWorkBtn, this);
	m_WorkBtn.SetTextMonospacedDigits(true);
	m_WorkLabel.SetText("Work.exe : Ends Day; Collects Cash");

	m_ShopLabel.SetText("SHOP");

	m_BuyCumLabel.SetText("Buy Sticky Paste\nHome Defense!");
	m_BuyCumBtn.SetButtonClickedCallback(OnCumBtn, this);
	m_BuyGunLabel.SetText("Buy Self Defense Drone\n\"Stand your ground!\"");
	m_BuyGunBtn.SetButtonClickedCallback(OnGunBtn, this);



	HyLayoutHandle hTitleBarRow = InsertLayout(HYORIEN_Horizontal);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hTitleBarRow);
	InsertWidget(m_ExitBtn, hTitleBarRow);
	InsertSpacer(HYSIZEPOLICY_Fixed, 8, hTitleBarRow);

	HyLayoutHandle hWorkRow = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_WorkBtn, hWorkRow);
	InsertWidget(m_WorkLabel, hWorkRow);

	InsertSpacer(HYSIZEPOLICY_Fixed, 50);
	InsertWidget(m_ShopLabel);
	HyLayoutHandle hBuyRow = InsertLayout(HYORIEN_Horizontal);
	
	//InsertSpacer(HYSIZEPOLICY_Expanding, 0, hBuyRow);
	HyLayoutHandle hCumCol = InsertLayout(HYORIEN_Vertical, hBuyRow);
	InsertWidget(m_BuyCumLabel, hCumCol);
	InsertWidget(m_BuyCumBtn, hCumCol);
	
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hBuyRow);
	HyLayoutHandle hGunCol = InsertLayout(HYORIEN_Vertical, hBuyRow);
	InsertWidget(m_BuyGunLabel, hGunCol);
	InsertWidget(m_BuyGunBtn, hGunCol);
	//InsertSpacer(HYSIZEPOLICY_Expanding, 0, hBuyRow);

	InsertSpacer(HYSIZEPOLICY_Fixed, 25);
}

/*virtual*/ Computer::~Computer()
{
}

/*virtual*/ void Computer::OnContainerUpdate() /*override*/
{
	int64 iCurMoney = MoonjamTravesty::GetGame().GetMoney();
	m_BuyCumBtn.SetAsEnabled(iCurMoney >= iCUM_COST);
	m_BuyGunBtn.SetAsEnabled(iCurMoney >= iGUN_COST);

	int64 iCurWorkProfit = MoonjamTravesty::GetGame().GetCurWorkProfit();
	m_WorkBtn.SetText(HyLocale::Money_Format(iCurWorkProfit));
}

/*static*/ void Computer::OnExitBtn(HyButton *pBtn, void *pData)
{
	Computer *pThis = reinterpret_cast<Computer *>(pData);
	pThis->Hide();
}

/*static*/ void Computer::OnWorkBtn(HyButton *pBtn, void *pData)
{
}

/*static*/ void Computer::OnCumBtn(HyButton *pBtn, void *pData)
{
	MoonjamTravesty::BuyCum();
}

/*static*/ void Computer::OnGunBtn(HyButton *pBtn, void *pData)
{
	MoonjamTravesty::BuyGun();
}
