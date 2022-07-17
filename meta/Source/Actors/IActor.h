#ifndef IActor_h__
#define IActor_h__

#include "pch.h"

class IActor : public HyEntity2d
{
protected:
	float			m_fMovementMod;

public:
	IActor(HyEntity2d *pParent = nullptr);
	virtual ~IActor();

	virtual void OnUpdate() override;

	void SetMoveModifer(float fMoveMod);
};

#endif // IActor_h__
