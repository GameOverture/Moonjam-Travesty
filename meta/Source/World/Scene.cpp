#include "pch.h"
#include "Scene.h"

Scene::Scene(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent)
{
}

/*virtual*/ Scene::~Scene()
{
}

/*virtual*/ void Scene::OnUpdate() /*override*/
{
}
