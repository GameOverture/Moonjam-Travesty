#ifndef ProgressBar_h__
#define ProgressBar_h__

#include "pch.h"

class ProgressBar : public HyProgressBar
{
public:
	ProgressBar(HyEntity2d *pParent = nullptr);
	virtual ~ProgressBar();

	virtual void OnUpdate() override;
};

#endif // ProgressBar_h__
