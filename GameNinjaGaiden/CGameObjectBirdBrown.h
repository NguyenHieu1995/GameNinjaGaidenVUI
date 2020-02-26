#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CStateObject.h"
#include "CSword.h"
#include "CDartsRed.h"
#include "CDartsSmall.h"

class CGameObjectBirdBrown : public CGameObject
{
public:
	CGameObjectBirdBrown(int id);
	CGameObjectBirdBrown(int id, int x, int y, bool direction = true);
	~CGameObjectBirdBrown();

private:
	D3DXVECTOR2 _positionCutEnemi;
	float _posCharacterX;
	float _posCharecterY;

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	void SetState(int state);
	virtual void Reset();

	void SetPositionCharacter(float x, float y);
	bool IsAlive();
};
