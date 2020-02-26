#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CStateObject.h"
#include "CSword.h"
#include "CDartsRed.h"
#include "CGameObjectGround.h"
#include "CGameObjectWall.h"

class CGameObjectSwordMan : public CGameObject
{
public:
	CGameObjectSwordMan(int id);
	CGameObjectSwordMan(int id, int x, int y, bool direction = true);
	~CGameObjectSwordMan();


	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	virtual RectEx GetBoundingBox();
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
	void Reset();

	bool IsAlive();

private:
	D3DXVECTOR2 _positionCutEnemi;
};
