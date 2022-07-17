#include "pch.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(HyEntity2d *pParent /*= nullptr*/) :
	HyProgressBar(HyPanelInit(75, 10, 1), "", "", pParent)
{
}

/*virtual*/ ProgressBar::~ProgressBar()
{
}

/*virtual*/ void ProgressBar::OnUpdate() /*override*/
{
}
