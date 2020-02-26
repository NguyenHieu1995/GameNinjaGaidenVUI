#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameObject.h"

class CGameObjectGround : public CGameObject
{
public:
	CGameObjectGround(int id);
	CGameObjectGround(int id, int x, int y, int w, int h);
	~CGameObjectGround();

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
