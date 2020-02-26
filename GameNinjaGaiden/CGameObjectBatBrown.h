#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CStateObject.h"
#include "CCamera.h"
#include "CSword.h"
#include "CDartsRed.h"
#include "CDartsSmall.h"
#include "CFireBullet.h"

class CGameObjectBatBrown : public CGameObject
{
public:
	CGameObjectBatBrown(int id);
	CGameObjectBatBrown(int id, int x, int y, bool direction = true);
	~CGameObjectBatBrown();

private:
	D3DXVECTOR2 _positionCutEnemi;
	int _angle;

public:
	bool IsAlive();
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	void SetState(int state);
	virtual void Reset();
	
};
