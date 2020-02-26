#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CCamera.h"

class CBulletMachineGunGuy : public CGameObject
{
public:
	CBulletMachineGunGuy(int id);
	CBulletMachineGunGuy(int id, int x, int y);
	~CBulletMachineGunGuy();

private:


public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();

	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);

};

