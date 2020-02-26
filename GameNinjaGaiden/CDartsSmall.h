#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CGameObjectCat.h"
#include "CBonusBlue.h"
#include "CDartsRed.h"
#include "CItemContainer4.h"


class CDartsSmall : public CGameObject
{
public:
	CDartsSmall(int id);
	CDartsSmall(int id, int x, int y, bool direction = true);
	~CDartsSmall();

private:
	int _angle;	
	//int _score;

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();

	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);
	//int GetScore();
};

