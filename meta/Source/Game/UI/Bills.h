#ifndef Bills_h__
#define Bills_h__

#include "pch.h"

class Bills : public HyUiContainer
{
	HySprite2d			m_PaperPanel;

	HyLabel				m_BillsTitle;

	HyLabel				m_SavingsLbl;
	HyRackMeter			m_SavingsVal;
	HyLabel				m_PaycheckLbl;
	HyRackMeter			m_PaycheckVal;
	HyLabel				m_MortgageLbl;
	HyRackMeter			m_MortgageVal;
	HyCheckBox			m_FoodChk;
	HyRackMeter			m_FoodVal;
	//HyCheckBox			m_AcChk;
	//HyRackMeter			m_AcVal;
	HyCheckBox			m_MedicineChk;
	HyRackMeter			m_MedicineVal;
	HyLabel				m_RepairsLbl;
	HyRackMeter			m_RepairsVal;

	HyLabel				m_DividerLine;
	HyRackMeter			m_RemainingMoney;
	HyButton			m_EndBtn;

	HyAudio2d			m_AudBillyHasStatus;
	HyAudio2d			m_AudBillyJuicer;

	// Billy Status
	class BillyStatus : public HyEntity2d
	{
	public:
		HyPrimitive2d	m_Background;
		HyText2d		m_Title;

		HyLabel			m_Status;

		HyText2d		m_Grades;
		HySprite2d		m_GradeLetter;

		BillyStatus(HyEntity2d *pParent) :
			HyEntity2d(pParent),
			m_Background(this),
			m_Title("UI", "Bills", this),
			m_Status(HyPanelInit("UI/Bills", "BillyIcon"), "UI", "Bills", this),
			m_Grades("UI", "Bills", this),
			m_GradeLetter("UI/Bills", "BillyGrade", this)
		{
			m_Background.shape.SetAsBox(500, 700);
			m_Background.SetTint(HyColor::DarkGray);
			m_Background.alpha.Set(0.9f);

			m_Title.SetText("Little Billy");
			m_Title.SetState(3);
			m_Title.SetTextAlignment(HYALIGN_Center);
			m_Title.pos.Set(250, 590);

			m_Status.SetText("Status: ");
			m_Status.SetAsSideBySide(false);
			m_Status.SetTextState(4);
			m_Status.pos.Set(50, 420);

			m_Grades.SetText("School Report Card:");
			m_Grades.SetState(4);
			m_Grades.SetTextAlignment(HYALIGN_Center);
			m_Grades.pos.Set(250, 320);

			m_GradeLetter.pos.Set(250, 200);
		}
	};
	BillyStatus			m_BillyStatus;

public:
	Bills(HyEntity2d *pParent = nullptr);
	virtual ~Bills();

	void Assemble(int64 iPaycheckAmt, int64 iRepairCost, BillyFeels eBillyStatus, BillyGrade eBillyGrades);

	virtual void OnContainerUpdate() override;

	static void OnExitBtn(HyButton *pBtn, void *pData);
};

#endif // Bills_h__
