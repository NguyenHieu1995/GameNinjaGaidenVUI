#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "CGameObject.h"

class CGameObjectWall : public CGameObject
{
public:
	CGameObjectWall(int id);
	CGameObjectWall(int id, int x, int y, int w, int h);
	~CGameObjectWall();

private:


public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetVx(float vx) {}
	void SetVy(float vy) {}
	void Render() {}
	void SetState(int state) {}
};


