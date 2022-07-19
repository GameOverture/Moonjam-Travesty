#include "pch.h"
#include "Bills.h"
#include "Game.h"
#include "MoonjamTravesty.h"

Bills::Bills(HyEntity2d *pParent /*= nullptr*/) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(600, 700, 1), pParent),
	m_PaperPanel("UI/Bills", "BillsPanel", this),
	m_BillsTitle(HyPanelInit(), "UI", "Bills", this),
	m_SavingsLbl(HyPanelInit(), "UI", "Bills", this),
	m_SavingsVal(HyPanelInit(), "UI", "Bills", this),
	m_PaycheckLbl(HyPanelInit(), "UI", "Bills", this),
	m_PaycheckVal(HyPanelInit(), "UI", "Bills", this),
	m_MortgageLbl(HyPanelInit(), "UI", "Bills", this),
	m_MortgageVal(HyPanelInit(), "UI", "Bills", this),
	m_FoodChk(HyPanelInit(32, 32, 2), "UI", "Bills", this),
	m_FoodVal(HyPanelInit(), "UI", "Bills", this),
	//m_AcChk(HyPanelInit(32, 32, 2), "UI", "Bills", this),
	//m_AcVal(HyPanelInit(), "UI", "Bills", this),
	m_MedicineChk(HyPanelInit(32, 32, 2), "UI", "Bills", this),
	m_MedicineVal(HyPanelInit(), "UI", "Bills", this),
	m_RepairsLbl(HyPanelInit(), "UI", "Bills", this),
	m_RepairsVal(HyPanelInit(), "UI", "Bills", this),
	m_DividerLine(HyPanelInit(175, 5, 1, HyColor::Black, HyColor::Black), "UI", "Bills", this),
	m_RemainingMoney(HyPanelInit(), "UI", "Bills", this),
	m_EndBtn(HyPanelInit(300, 75, 3), "UI", "Bills", 10, 5, 10, 5, this),
	m_BillyStatus(this),
	m_AudBillyHasStatus("Sounds", "BillySick", this),
	m_AudBillyJuicer("Sounds", "ShameOnBilly", this)
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
	m_MortgageLbl.SetText("Mortgage");
	m_FoodChk.SetText("Food x2");
	//m_AcChk.SetText("Air Conditioning");
	m_MedicineChk.SetText("Medicine");
	m_RepairsLbl.SetText("Home Repairs");

	m_SavingsVal.SetAsSpinningMeter(false);
	m_SavingsVal.SetNumFormat(HyNumberFormat().SetFractionPrecision(0, 0));
	m_SavingsVal.ShowAsCash(true);
	m_PaycheckVal.SetAsSpinningMeter(false);
	m_PaycheckVal.ShowAsCash(true);
	m_MortgageVal.SetAsSpinningMeter(false);
	m_MortgageVal.ShowAsCash(true);
	m_FoodVal.SetAsSpinningMeter(false);
	m_FoodVal.ShowAsCash(true);
	//m_AcVal.SetAsSpinningMeter(false);
	//m_AcVal.ShowAsCash(true);
	m_MedicineVal.SetAsSpinningMeter(false);
	m_MedicineVal.ShowAsCash(true);
	m_RepairsVal.SetAsSpinningMeter(false);
	m_RepairsVal.ShowAsCash(true);

	m_RemainingMoney.SetAsSpinningMeter(false);
	m_RemainingMoney.ShowAsCash(true);

	m_EndBtn.SetButtonClickedCallback(OnExitBtn, this);
	m_EndBtn.SetTextState(4);

	m_BillyStatus.pos.Set(640, 0);

	SetLayoutMargin(20, 20, 20, 20);
}

/*virtual*/ Bills::~Bills()
{
}

void Bills::Assemble(int64 iPaycheckAmt, int64 iRepairCost, BillyFeels eBillyStatus, BillyGrade eBillyGrades)
{
	if(eBillyGrades == BILLYGRADE_F) // Game over
		eBillyStatus = BILLY_Juicer;

	switch(eBillyStatus)
	{
	case BILLY_Okage:	m_BillyStatus.m_Status.SetText("Status: Okage"); break;
	case BILLY_Hunger:	m_BillyStatus.m_Status.SetText("Status: Hunger"); m_AudBillyHasStatus.Play(); break;
	case BILLY_Sick:	m_BillyStatus.m_Status.SetText("Status: Sick"); m_AudBillyHasStatus.Play(); break;
	case BILLY_Juicer:	m_BillyStatus.m_Status.SetText("Status: Juicer"); m_AudBillyJuicer.Play(); break;
	}
	m_BillyStatus.m_Status.SetSpriteState(eBillyStatus);
	m_BillyStatus.m_GradeLetter.SetState(eBillyGrades);

	m_SavingsVal.SetValue(MoonjamTravesty::GetGame().GetMoney(), 0.0f);
	m_SavingsVal.SetTextState(1);
	m_PaycheckVal.SetValue(iPaycheckAmt, 0.0f);
	m_PaycheckVal.SetTextState(1);
	m_MortgageVal.SetValue(iMORTGAGE_COST, 0.0f);
	m_FoodVal.SetValue(iFOOD_COST, 0.0f);
	//m_AcVal.SetValue(iAC_COST, 0.0f);
	m_MedicineVal.SetValue(iMEDICINE_COST, 0.0f);
	m_RepairsVal.SetValue(iRepairCost, 0.0f);

	m_FoodChk.SetChecked(false);
	//m_AcChk.SetChecked(false);
	m_MedicineChk.SetChecked(false);

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
	InsertWidget(m_MortgageLbl, hMortgage);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hMortgage);
	InsertWidget(m_MortgageVal, hMortgage);

	HyLayoutHandle hRepair = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_RepairsLbl, hRepair);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hRepair);
	InsertWidget(m_RepairsVal, hRepair);
	
	HyLayoutHandle hFood = InsertLayout(HYORIEN_Horizontal);
	InsertWidget(m_FoodChk, hFood);
	InsertSpacer(HYSIZEPOLICY_Expanding, 0, hFood);
	InsertWidget(m_FoodVal, hFood);

	//HyLayoutHandle hAC = InsertLayout(HYORIEN_Horizontal);
	//InsertWidget(m_AcChk, hAC);
	//InsertSpacer(HYSIZEPOLICY_Expanding, 0, hAC);
	//InsertWidget(m_AcVal, hAC);

	if(eBillyStatus == BILLY_Sick)
	{
		m_MedicineChk.alpha.Set(1.0f);
		m_MedicineVal.alpha.Set(1.0f);

		HyLayoutHandle hMedicine = InsertLayout(HYORIEN_Horizontal);
		InsertWidget(m_MedicineChk, hMedicine);
		InsertSpacer(HYSIZEPOLICY_Expanding, 0, hMedicine);
		InsertWidget(m_MedicineVal, hMedicine);
	}
	else
	{
		m_MedicineChk.alpha.Set(0.0f);
		m_MedicineVal.alpha.Set(0.0f);
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
	if(IsShown() == false)
		return;

	int64 iRemainingMoney = 0;
	iRemainingMoney += m_SavingsVal.GetValue();
	iRemainingMoney += m_PaycheckVal.GetValue();
	iRemainingMoney -= m_MortgageVal.GetValue();
	iRemainingMoney -= m_RepairsVal.GetValue();

	if(m_FoodChk.IsChecked())
		iRemainingMoney -= m_FoodVal.GetValue();
	//if(m_AcChk.IsChecked())
	//	iRemainingMoney -= m_AcVal.GetValue();
	if(m_MedicineChk.IsChecked())
		iRemainingMoney -= m_MedicineVal.GetValue();

	if(m_RemainingMoney.GetValue() != iRemainingMoney)
	{
		if(iRemainingMoney < 0)
			m_RemainingMoney.SetValue(0, 1.0f);
		else
			m_RemainingMoney.SetValue(iRemainingMoney, 1.0f);
	}

	if(m_BillyStatus.m_GradeLetter.GetState() == BILLYGRADE_F)
		m_EndBtn.SetText("Billy is a juicer");
	else if(m_RemainingMoney.GetValue() > 0)
		m_EndBtn.SetText("Go to sleep");
	else
		m_EndBtn.SetText("Declare Bankruptcy");
}

/*static*/ void Bills::OnExitBtn(HyButton *pBtn, void *pData)
{
	Bills *pThis = reinterpret_cast<Bills *>(pData);

	if(pThis->m_BillyStatus.m_GradeLetter.GetState() == BILLYGRADE_F)
		MoonjamTravesty::GameOver(GAMEOVER_Juicer);
	else if(pThis->m_RemainingMoney.GetValue() < 0)
		MoonjamTravesty::GameOver(GAMEOVER_Bankruptcy);
	else
		MoonjamTravesty::Sleep(pThis->m_RemainingMoney.GetValue(), pThis->m_MedicineChk.IsChecked(), pThis->m_FoodChk.IsChecked());
}
