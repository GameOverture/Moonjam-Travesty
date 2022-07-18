#ifndef Bills_h__
#define Bills_h__

#include "pch.h"

class Bills : public HyUiContainer
{
	HySprite2d		m_PaperPanel;

	HyLabel			m_BillsTitle;

	HyLabel			m_SavingsLbl;
	HyLabel			m_SavingsVal;
	HyLabel			m_PaycheckLbl;
	HyLabel			m_PaycheckVal;
	HyCheckBox		m_MortgageChk;
	HyLabel			m_MortgageVal;
	HyCheckBox		m_FoodChk;
	HyLabel			m_FoodVal;
	HyCheckBox		m_AcChk;
	HyLabel			m_AcVal;
	HyCheckBox		m_MedicineChk;
	HyLabel			m_MedicineVal;
	HyCheckBox		m_RepairsChk;
	HyLabel			m_RepairsVal;

	HyLabel			m_DividerLine;
	HyRackMeter		m_RemainingMoney;
	HyButton		m_EndBtn;

public:
	Bills(HyEntity2d *pParent = nullptr);
	virtual ~Bills();

	void Assemble(int64 iPaycheckAmt);

	virtual void OnContainerUpdate() override;

	static void OnEndBtn(HyButton *pBtn, void *pData);
};

#endif // Bills_h__
