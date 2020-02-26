#pragma once

#include <Windows.h>
#include "CGameObject.h"
#include "CGameObjectCat.h"
#include "CBonusBlue.h"
#include "CDartsRed.h"
#include "CItemContainer4.h"

class CFirebullet : public CGameObject
{
public:
	CFirebullet(int id);
	CFirebullet(int id, int x, int y, float vx = 0.0f, float vy = 0.0f, bool direction = true);
	~CFirebullet();

private:
	int _angle;
	double _x1, _y1, _x2, _y2, _x3, _y3;
	double _timeAngle;
	//int _score;

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();

	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);

	//int GetScore();
	//void Reset();
};

