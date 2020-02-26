#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CGameObjectGround.h"
#include "CGameObjectCat.h"
#include "CSword.h"
#include "CDartsRed.h"
#include "CGameObjectSwordMan.h"
#include "CKnifeBanshee.h"
#include "CBulletMachineGunGuy.h"
#include "CGameObjectWall.h"
#include "CGameObjectBirdBrown.h"
#include "CGameObjectMachineGunGuy.h"
#include "CGameObjectBanshee.h"
#include "CGameObjectBoss.h"



class CGameObjectRyu : public CGameObject
{
public:
	CGameObjectRyu(int id);
	CGameObjectRyu(int id, int x, int y);
	~CGameObjectRyu();

private:
	bool _untouchable;			// Bien kiem tra co trang thai khong va cham hay khong
	DWORD _untouchable_start;	// Thoi gian bat dau trang thay khong va cham
	bool _isAttackSword;
	bool _isAttackDarts;
	bool _isAttackDartsSmall;

	int _numberRevival; // So mang con lai
	//int _health; // So mau cua nhan vat
	eTypeWeaponRyu _idWeapon; // Loai vu khi
	int _bonus;		// So diem thuong
	int _spiritualStrength;		// So spiritualStrength
	int _TimeFreeze;			// thoi gian bang
	
	//bool _isCutEnemi;
	bool _isBeingAttacked;

	//D3DXVECTOR2 _positionCutEnemi;
	//float _timeCutEnemi;

	int _idDart;
	bool _isResetTime;

public:
	virtual void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	virtual void SetState(int state);
	void Reset();

	int GetRevival();
	//int GetHealth();
	int GetWeapon();
	int GetBonus();
	int GetSpiritualStrength();
	bool IsResetTime();
};
