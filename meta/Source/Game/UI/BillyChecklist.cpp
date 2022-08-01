#include "pch.h"
#include "BillyChecklist.h"

BillyChecklist::BillyChecklist(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_Background(this),
	m_Title("UI", "Bills", this),
	m_SnackChkBox("UI", "BillyCheckBox", this),
	m_SnackLbl("UI", "Bills", this),
	m_HomeworkChkBox("UI", "BillyCheckBox", this),
	m_HomeworkLbl("UI", "Bills", this),
	m_DinnerChkBox("UI", "BillyCheckBox", this),
	m_DinnerLbl("UI", "Bills", this),

	m_eBillyFeels(BILLY_Okage),
	m_iBillyGrade(BILLYGRADE_A),
	m_iFoodCount(2)
{
	m_Background.shape.SetAsBox(250, 280);
	m_Background.SetTint(HyColor::Black);
	m_Background.alpha.Set(0.75f);
	
	m_Title.SetText("Billy Checklist");
	m_Title.SetState(4);
	m_Title.SetTextAlignment(HYALIGN_Center);
	m_Title.pos.Set(125, 260);

	m_SnackChkBox.pos.Set(20, 210);
	m_SnackLbl.SetText("Snack");
	m_SnackLbl.pos.Set(50, 200);
	m_SnackLbl.SetState(4);

	m_HomeworkChkBox.pos.Set(20, 150);
	m_HomeworkLbl.SetText("Homework");
	m_HomeworkLbl.pos.Set(50, 140);
	m_HomeworkLbl.SetState(4);

	m_DinnerChkBox.pos.Set(20, 90);
	m_DinnerLbl.SetText("Dinner");
	m_DinnerLbl.pos.Set(50, 80);
	m_DinnerLbl.SetState(4);
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
	m_SnackChkBox.SetState(0);
	m_HomeworkChkBox.SetState(0);
	m_DinnerChkBox.SetState(0);
}

int BillyChecklist::GetFoodCount()
{
	return m_iFoodCount;
}

void BillyChecklist::OnSnackTask()
{
	m_SnackChkBox.SetState(1);
	m_iFoodCount--;
}

void BillyChecklist::OnHomeworkTask()
{
	m_HomeworkChkBox.SetState(1);
}

void BillyChecklist::OnDinnerTask()
{
	m_DinnerChkBox.SetState(1);
	m_iFoodCount--;
}

void BillyChecklist::OnEndDay() // BEFORE BILLS
{
	int iFoodPts = -2;
	if(m_SnackChkBox.GetState() == 1)
		iFoodPts++;
	if(m_DinnerChkBox.GetState() == 1)
		iFoodPts++;

	int iGradePts = 0;
	switch(iFoodPts)
	{
	case 0:
		if(m_HomeworkChkBox.GetState() == 1 && m_eBillyFeels == BILLY_Okage)
			iGradePts = 1;
		break;

	case -1:
		if(m_eBillyFeels == BILLY_Okage) // Billy was...
		{
			m_eBillyFeels = BILLY_Hunger;
			iGradePts--;
		}
		else if(m_eBillyFeels == BILLY_Hunger) // Billy was...
		{
			m_eBillyFeels = BILLY_Sick;
			iGradePts--;
		}
		else if(m_eBillyFeels == BILLY_Sick)
			iGradePts -= 2;

		if(m_HomeworkChkBox.GetState() == 0)
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

		if(m_HomeworkChkBox.GetState() == 0)
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
