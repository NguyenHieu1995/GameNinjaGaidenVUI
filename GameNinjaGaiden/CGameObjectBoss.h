#pragma once
#include "CGameObject.h"
#include "CSword.h"
#include "CDartsRed.h"
#include "CDartsSmall.h"
#include "CGameObjectGround.h"
#include "CGameObjectWall.h"
#include "CBulletBoss.h"

class CGameObjectBoss : public CGameObject
{
public:
	CGameObjectBoss(int id);
	CGameObjectBoss(int id, int x, int y, bool direction = true);
	~CGameObjectBoss();

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
	virtual void Reset();


private:
	D3DXVECTOR2 _positionCutEnemi;
	int _timeDelay;
	int _numberJump;

	int _idBullet;

	//int _health;

	LPCANIMATION _animationExplode;
	int _currentFrameExplode;
	float _frameTimeExplode;

	float _timeDie;
};

