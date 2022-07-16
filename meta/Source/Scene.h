#ifndef Scene_h__
#define Scene_h__

#include "pch.h"

class Scene : public HyPhysicsGrid2d
{
public:
	Scene(std::string sSceneLevel, HyEntity2d *pParent = nullptr);
	virtual ~Scene();

	virtual void OnUpdate() override;
};

#endif // Scene_h__
