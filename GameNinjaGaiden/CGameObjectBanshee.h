#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CStateObject.h"
#include "CSword.h"
#include "CDartsRed.h"
#include "CKnifeBanshee.h"
#include "CDartsSmall.h"
#include "CFireBullet.h"

class CGameObjectBanshee : public CGameObject
{
public:
	CGameObjectBanshee(int id);
	CGameObjectBanshee(int id, int x, int y, bool direction = true);
	~CGameObjectBanshee();


	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();


	void SetState(int state);
	virtual void Reset();

private:
	D3DXVECTOR2 _positionCutEnemi;

	int _timeAttack;
	int _idKnife;
	bool _isAttack;

	bool IsAlive();
};
