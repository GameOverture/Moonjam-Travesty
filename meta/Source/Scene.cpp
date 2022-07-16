#include "pch.h"
#include "Scene.h"

Scene::Scene(HyEntity2d *pParent /*= nullptr*/) :
	HyPhysicsGrid2d(pParent)
{
}

/*virtual*/ Scene::~Scene()
{
}

/*virtual*/ void Scene::OnUpdate() /*override*/
{
}
