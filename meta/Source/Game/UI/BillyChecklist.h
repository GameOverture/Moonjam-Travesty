#ifndef BillyChecklist_h__
#define BillyChecklist_h__

#include "pch.h"

class BillyChecklist : public HyEntity2d
{
	HyPrimitive2d		m_Background;
	HyText2d			m_Title;

	HySprite2d			m_SnackChkBox;
	HyText2d			m_SnackLbl;
	HySprite2d			m_HomeworkChkBox;
	HyText2d			m_HomeworkLbl;
	HySprite2d			m_DinnerChkBox;
	HyText2d			m_DinnerLbl;

	// Stats
	BillyFeels			m_eBillyFeels;
	int32				m_iBillyGrade;

	int32				m_iFoodCount;

public:
	BillyChecklist(HyEntity2d *pParent = nullptr);
	virtual ~BillyChecklist();

	virtual void OnUpdate() override;

	BillyFeels GetBillyFeels();
	BillyGrade GetBillyGrade();

	void ResetTasks();

	int GetFoodCount();
	void OnSnackTask();
	void OnHomeworkTask();
	void OnDinnerTask();

	void OnEndDay();
	void OnSleep(bool bBoughtMedicine, bool bBoughtFood);
};

#endif // BillyChecklist_h__
