#ifndef TheNextDay_h__
#define TheNextDay_h__

#include "pch.h"

class TheNextDay : public HyEntity2d
{
public:
	TheNextDay(HyEntity2d *pParent = nullptr);
	virtual ~TheNextDay();

	virtual void OnUpdate() override;
};

#endif // TheNextDay_h__
