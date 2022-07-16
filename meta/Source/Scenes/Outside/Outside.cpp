#include "pch.h"
#include "Outside.h"

Outside::Outside(HyEntity2d *pParent /*= nullptr*/) :
	HyPhysicsGrid2d(glm::vec2(0.0f, 0.0f), 120.0f)
{
	for(uint32 i = 0; i < 2; i++)
	{
		HySprite2d *pNewSky = HY_NEW HySprite2d("Outside", "Sky", this);
		pNewSky->pos.Set((i & 1) ? i * pNewSky->GetFrameWidth(1.0f) : pNewSky->GetFrameWidth(-1.0f), 0.0f);
		m_SkyList.push_back(pNewSky);
	}

	for(uint32 i = 0; i < 2; i++)
	{
		HySprite2d *pNewGrass = HY_NEW HySprite2d("Outside", "Grass", this);
		pNewGrass->pos.Set(i * 1000.0f, 0.0f);
		m_GrassList.push_back(pNewGrass);
	}

	for(uint32 i = 0; i < 2; i++)
	{
		HySprite2d *pNewPath = HY_NEW HySprite2d("Outside", "Path", this);
		if(i != 0)
			pNewPath->SetState(1);

		pNewPath->pos.Set(i * 1000.0f, 0.0f);
		m_PathList.push_back(pNewPath);
	}

	m_Cottage.Init("Outside", "Cottage", this);
}

/*virtual*/ Outside::~Outside()
{
	for(auto *pNode : m_SkyList)
		delete pNode;
	for(auto *pNode : m_GrassList)
		delete pNode;
	for(auto *pNode : m_PathList)
		delete pNode;
}

/*virtual*/ void Outside::OnUpdate() /*override*/
{
}
