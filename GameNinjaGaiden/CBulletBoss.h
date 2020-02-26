#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CCamera.h"


class CBulletBoss : public CGameObject
{
public:
	CBulletBoss(int id);
	CBulletBoss(int id, int x, int y, bool direction = true);
	~CBulletBoss();

private:
	

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};
