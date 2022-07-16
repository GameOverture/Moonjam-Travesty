#ifndef Outside_h__
#define Outside_h__

#include "pch.h"

class Outside : public HyPhysicsGrid2d
{
	std::vector<HySprite2d *>	m_SkyList;
	std::vector<HySprite2d *>	m_GrassList;
	std::vector<HySprite2d *>	m_PathList;

	HySprite2d					m_Cottage;

public:
	Outside(HyEntity2d *pParent = nullptr);
	virtual ~Outside();

	virtual void OnUpdate() override;
};

#endif // Outside_h__
