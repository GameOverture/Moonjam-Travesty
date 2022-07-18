#include "pch.h"
#include "Bills.h"
#include "Game.h"
#include "MoonjamTravesty.h"

Bills::Bills(HyEntity2d *pParent /*= nullptr*/) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(600, 700, 1), pParent),
	m_PaperPanel("UI", "BillsPanel", this),
	m_BillsTitle(HyPanelInit(), "UI", "Bills"),
	m_SavingsLbl(HyPanelInit(), "UI", "Bills"),
	m_SavingsVal(HyPanelInit(), "UI", "Bills"),
	m_PaycheckLbl(HyPanelInit(), "UI", "Bills"),
	m_PaycheckVal(HyPanelInit(), "UI", "Bills"),
	m_MortgageChk(HyPanelInit(32, 32, 2), "UI", "Bills"),
	m_MortgageVal(HyPanelInit(), "UI", "Bills"),
	m_FoodChk(HyPanelInit(32, 32, 2), "UI", "Bills"),
	m_FoodVal(HyPanelInit(), "UI", "Bills"),
	m_AcChk(HyPanelInit(32, 32, 2), "UI", "Bills"),
	m_AcVal(HyPanelInit(), "UI", "Bills"),
	m_MedicineChk(HyPanelInit(32, 32, 2), "UI", "Bills"),
	m_MedicineVal(HyPanelInit(), "UI", "Bills"),
	m_RepairsChk(HyPanelInit(32, 32, 2), "UI", "Bills"),
	m_RepairsVal(HyPanelInit(), "UI", "Bills"),
	m_DividerLine(HyPanelInit(175, 5, 1, HyColor::Black, HyColor::Black), "UI", "Bills"),
	m_RemainingMoney(HyPanelInit(), "UI", "Bills"),
	m_EndBtn(HyPanelInit(250, 75, 3), "UI", "Bills")
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Bills);
	pos.Set(100.0f, 20.0f);
	m_PaperPanel.SetDisplayOrder(DISPLAYORDER_Bills - 1);
	m_Panel.alpha.Set(0.0f);

	m_BillsTitle.SetText("BILLS");
	m_BillsTitle.SetTextState(2);
	m_SavingsLbl.SetText("Savings");
	m_SavingsLbl.SetTextState(1);
	m_PaycheckLbl.SetText("Paycheck");
	m_PaycheckLbl.SetTextState(1);
	m_MortgageChk.SetText("Mortgage");
	m_MortgageChk.SetChecked(true);
	m_MortgageChk.SetAsEnabled(false);
	m_FoodChk.SetText("Food");
	m_AcChk.SetText("Air Conditioning");
	m_MedicineChk.SetText("Medicine");
	m_RepairsChk.SetText("Repairs");

	SetLayoutMargin(20, 20, 20, 20);
}

/*virtual*/ Bills::~Bills()
{
}

void Bills::Assemble(int64 iPaycheckAmt)
{
	m_SavingsVal.SetText(HyLocale::Money_Format(MoonjamTravesty::GetGame().GetMoney()));
	m_SavingsVal.SetTextState(1);
	m_PaycheckVal.SetText(HyLocale::Money_Format(iPaycheckAmt));
	m_PaycheckVal.SetTextState(1);
	m_MortgageVal.SetText(HyLocale::Money_Format(iMORTGAGE_COST));
	m_FoodVal.SetText(HyLocale::Money_Format(iFOOD_COST));
	m_AcVal.SetText(HyLocale::Money_Format(iAC_COST));
	m_MedicineVal.SetText(HyLocale::Money_Format(iMEDICINE_COST));
	m_RepairsVal.SetText(HyLocale::Money_Format(iMEDICINE_COST));

	m_RemainingMoney.SetValue(0, 0.0f);

	ClearItems();
	InsertWidget(m_BillsTitle);
	
	InsertSpacer();

	HyLayoutHandle hSavings = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_SavingsLbl, hSavings);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hSavings);
	InsertWidget(m_SavingsVal, hSavings);

	HyLayoutHandle hPaycheck = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_PaycheckLbl, hPaycheck);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hPaycheck);
	InsertWidget(m_PaycheckVal, hPaycheck);

	HyLayoutHandle hMortgage = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_MortgageChk, hMortgage);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hMortgage);
	InsertWidget(m_MortgageVal, hMortgage);
	
	HyLayoutHandle hFood = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_FoodChk, hFood);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hFood);
	InsertWidget(m_FoodVal, hFood);

	HyLayoutHandle hAC = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_AcChk, hAC);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hAC);
	InsertWidget(m_AcVal, hAC);

	if(true)
	{
		HyLayoutHandle hMedicine = InsertLayout(HYORIEN_Horizontal);
		InsertWidget(m_MedicineChk, hMedicine);
		InsertSpacer(HYSIZEPOLICY_Expanding, 0, hMedicine);
		InsertWidget(m_MedicineVal, hMedicine);
	}

	if(true)
	{
		HyLayoutHandle hRepair = InsertLayout(HYORIEN_Horizontal);
		InsertWidget(m_RepairsChk, hRepair);
		InsertSpacer(HYSIZEPOLICY_Expanding, 0, hRepair);
		InsertWidget(m_RepairsVal, hRepair);
	}

	HyLayoutHandle hDivider = InsertLayout(HYORIEN_Horizontal);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hDivider);
	InsertWidget(m_DividerLine, hDivider);

	HyLayoutHandle hRemainingMoney = InsertLayout(HYORIEN_Horizontal);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hRemainingMoney);
	InsertWidget(m_RemainingMoney, hRemainingMoney);

	InsertWidget(m_EndBtn);
}

/*virtual*/ void Bills::OnContainerUpdate() /*override*/
{
}
