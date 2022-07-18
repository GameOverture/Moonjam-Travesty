#include "pch.h"
#include "BillyChecklist.h"

BillyChecklist::BillyChecklist(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_Background(this),
	m_Title("UI", "Bills", this),
	m_SnackChk(HyPanelInit(32, 32, 2), "UI", "Bills", this),
	m_HomeworkChk(HyPanelInit(32, 32, 2), "UI", "Bills", this),
	m_DinnerChk(HyPanelInit(32, 32, 2), "UI", "Bills", this),
	m_eBillyFeels(BILLY_Okage),
	m_iBillyGrade(BILLYGRADE_A),
	m_iFoodCount(2)
{
	m_Background.shape.SetAsBox(250, 300);
	m_Background.SetTint(HyColor::DarkGray);
	m_Background.alpha.Set(0.6f);
	
	m_Title.SetText("Billy Checklist");
	m_Title.SetState(4);
	m_Title.SetTextAlignment(HYALIGN_Center);
	m_Title.pos.Set(125, 260);

	m_SnackChk.pos.Set(20, 200);
	m_SnackChk.SetText("Snack");
	m_SnackChk.SetTextState(4);
	m_SnackChk.SetAsEnabled(false);
	m_SnackChk.SetChecked(false);

	m_HomeworkChk.pos.Set(20, 140);
	m_HomeworkChk.SetText("Homework");
	m_HomeworkChk.SetTextState(4);
	m_HomeworkChk.SetAsEnabled(false);
	m_HomeworkChk.SetChecked(false);

	m_DinnerChk.pos.Set(20, 80);
	m_DinnerChk.SetText("Dinner");
	m_DinnerChk.SetTextState(4);
	m_DinnerChk.SetAsEnabled(false);
	m_DinnerChk.SetChecked(false);
}

/*virtual*/ BillyChecklist::~BillyChecklist()
{
}

/*virtual*/ void BillyChecklist::OnUpdate() /*override*/
{
}

BillyFeels BillyChecklist::GetBillyFeels()
{
	return m_eBillyFeels;
}

BillyGrade BillyChecklist::GetBillyGrade()
{
	return static_cast<BillyGrade>(m_iBillyGrade);
}

void BillyChecklist::ResetTasks()
{
	m_SnackChk.SetChecked(false);
	m_HomeworkChk.SetChecked(false);
	m_DinnerChk.SetChecked(false);
}

int BillyChecklist::GetFoodCount()
{
	return m_iFoodCount;
}

void BillyChecklist::OnSnackTask()
{
	m_SnackChk.SetChecked(true);
	m_iFoodCount--;
}

void BillyChecklist::OnHomeworkTask()
{
	m_HomeworkChk.SetChecked(true);
}

void BillyChecklist::OnDinnerTask()
{
	m_DinnerChk.SetChecked(true);
	m_iFoodCount--;
}

void BillyChecklist::OnEndDay() // BEFORE BILLS
{
	int iFoodPts = -2;
	if(m_SnackChk.IsChecked())
		iFoodPts++;
	if(m_DinnerChk.IsChecked())
		iFoodPts++;

	int iGradePts = 0;
	switch(iFoodPts)
	{
	case 0:
		if(m_HomeworkChk.IsChecked())
			iGradePts = 1;
		break;

	case -1:
		if(m_eBillyFeels == BILLY_Okage) // Billy was...
			m_eBillyFeels = BILLY_Hunger;
		else if(m_eBillyFeels == BILLY_Hunger) // Billy was...
		{
			m_eBillyFeels = BILLY_Sick;
			iGradePts--;
		}
		else if(m_eBillyFeels == BILLY_Sick)
			iGradePts -= 2;

		if(m_HomeworkChk.IsChecked() == false)
			iGradePts--;
		break;

	case -2:
		if(m_eBillyFeels == BILLY_Okage) // Billy was...
		{
			m_eBillyFeels = BILLY_Sick;
			iGradePts--;
		}
		else if(m_eBillyFeels == BILLY_Hunger || m_eBillyFeels == BILLY_Sick) // Billy was...
		{
			m_eBillyFeels = BILLY_Sick;
			iGradePts -= 2;
		}

		if(m_HomeworkChk.IsChecked() == false)
			iGradePts--;
		break;
	}

	m_iBillyGrade = HyClamp(m_iBillyGrade + iGradePts, static_cast<int32>(BILLYGRADE_F), static_cast<int32>(BILLYGRADE_A));
}

void BillyChecklist::OnSleep(bool bBoughtMedicine, bool bBoughtFood) // AFTER BILLS
{
	if(bBoughtMedicine)
		m_eBillyFeels = BILLY_Okage;

	if(bBoughtFood)
		m_iFoodCount += 2;
}
