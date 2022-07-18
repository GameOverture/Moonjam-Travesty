#include "pch.h"
#include "Computer.h"
#include "MoonjamTravesty.h"

const float fTRANS_IN_DUR = 0.42f;

Computer::Computer(HyEntity2d *pParent /*= nullptr*/) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(820, 650, 2), pParent),
	m_Dialog("UI", "Dialog", this),
	m_ExitBtn(HyPanelInit("UI", "ComputerExitBtn"), this),
	m_WorkBtn(HyPanelInit("UI", "WorkBtn"), "UI/Clock", "Text", 5, 34, 5, 34, this),
	m_BuyCumPrice("UI/Clock", "Text", this),
	m_BuyCumBtn(HyPanelInit("UI", "BuyCumBtn"), this),
	m_BuyGunPrice("UI/Clock", "Text", this),
	m_BuyGunBtn(HyPanelInit("UI", "BuyGunBtn"), this)
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Computer);
	m_Dialog.SetDisplayOrder(DISPLAYORDER_Computer - 1);
	m_Panel.alpha.Set(0.0f);


	m_ExitBtn.pos.Set(746, 580);
	m_ExitBtn.SetButtonClickedCallback(OnExitBtn, this);
	
	m_WorkBtn.pos.Set(354, 453);
	m_WorkBtn.SetButtonClickedCallback(OnWorkBtn, this);
	m_WorkBtn.SetTextMonospacedDigits(true);


	m_BuyCumBtn.SetButtonClickedCallback(OnCumBtn, this);
	m_BuyCumBtn.pos.Set(91.0f, 54.0f);

	m_BuyCumPrice.SetText(HyLocale::Money_Format(iCUM_COST));
	m_BuyCumPrice.pos.Set(200.0f, 100.0f);
	
	m_BuyGunBtn.SetButtonClickedCallback(OnGunBtn, this);
	m_BuyGunBtn.pos.Set(570.0f, 54.0f);

	m_BuyGunPrice.SetText(HyLocale::Money_Format(iGUN_COST));
	m_BuyGunPrice.pos.Set(677.0f, 100.0f);
}

/*virtual*/ Computer::~Computer()
{
}

// Returns the duration (in seconds) of the show transition
/*virtual*/ float Computer::OnBeginShow() /*override*/
{
	//alpha.Set(0.0f);
	//alpha.Tween(1.0f, fTRANS_IN_DUR);

	scale.Set(0.0001f, 0.0001f);
	scale.Tween(1.0f, 1.0f, fTRANS_IN_DUR, HyTween::QuadOut);
	SetVisible(true);

	return fTRANS_IN_DUR;
}

/*virtual*/ void Computer::OnShown()
{
	SetVisible(true);
	SetInputAllowed(true);
}

// Returns the duration (in seconds) of the hide transition
/*virtual*/ float Computer::OnBeginHide() /*override*/
{
	scale.Tween(0.0001f, 0.0001f, fTRANS_IN_DUR, HyTween::QuadOut);

	return fTRANS_IN_DUR;
}

/*virtual*/ void Computer::OnHidden()
{
	SetVisible(false);
	SetInputAllowed(false);
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
	MoonjamTravesty::EndDay();
}

/*static*/ void Computer::OnCumBtn(HyButton *pBtn, void *pData)
{
	MoonjamTravesty::BuyCum();
}

/*static*/ void Computer::OnGunBtn(HyButton *pBtn, void *pData)
{
	MoonjamTravesty::BuyGun();
}
