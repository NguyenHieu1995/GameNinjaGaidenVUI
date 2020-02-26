#pragma once
#include <Windows.h>
#include "CGameObject.h"
#include <algorithm>
#include "CStruct.h"

//struct CCollisionEvent;
//struct CCollisionEvent
//{
//	LPCGAMEOBJECT obj;
//	float t, nx, ny;
//	CCollisionEvent(float t, float nx, float ny, LPCGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }
//
//	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
//	{
//		return a->t < b->t;
//	}
//};
//
//typedef CCollisionEvent * LPCOLLISIONEVENT;

//
// Struct quan ly thong tin va cham
struct CCollisionInfo
{
	float _t;		// Thoi gian va cham
	float _nx, _ny;	// Huong va cham

	CCollisionInfo(float nx, float ny, float t) { this->_t = t; this->_nx = nx; this->_ny = ny; }
};
typedef CCollisionInfo* LPCCOLLISIONINFO;


// Clas tinh toan va cham giua 2 doi tuong
class CCollision
{
public:
	CCollision();
	~CCollision();

	static CCollision* GetInstance();	
	LPCCOLLISIONINFO SweptAABB(RectEx rectMove, D3DXVECTOR2 speed, RectEx rectStatic);
	void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny);

private:
	float _dx_entry, _dx_exit, _tx_entry, _tx_exit; // Thong tin va cham theo chieu x
	float _dy_entry, _dy_exit, _ty_entry, _ty_exit; // Thong tin va cham theo chieu y
	float _t_entry, _t_exit;						// thoi gian va cham
	
	float _bl, _bt, _br, _bb;						// BroadPhase

private:
	// Kiem tra BroadPhase
	bool CheckBroadPhase(RectEx rectMove, D3DXVECTOR2 speed, RectEx rectStatic);
	static CCollision* _instance;
};
