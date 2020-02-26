#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CStateObject.h"
#include "CSword.h"
#include "CDartsRed.h"

class CGameObjectCat : public CGameObject
{
public:
	CGameObjectCat(int id);
	CGameObjectCat(int id, int x, int y, bool direction = true);
	~CGameObjectCat();


	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	virtual RectEx GetBoundingBox();
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
	virtual void Reset();
	bool IsAlive();

private:
	D3DXVECTOR2 _positionCutEnemi;

};
