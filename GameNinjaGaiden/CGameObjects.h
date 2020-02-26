#pragma once

#include <d3dx9.h>
#include <unordered_map>
#include <comdef.h>
#include <Windows.h>
#include "CGameObject.h"
#include "CEnumsOfGame.h"
#include "CGameObjectBanshee.h"
#include "CGameObjectBatBrown.h"
#include "CGameObjectBirdBrown.h"
#include "CGameObjectCat.h"
#include "CGameObjectMachineGunGuy.h"
#include "CGameObjectSwordMan.h"
#include "CGameObjectGround.h"
#include "CGameObjectBoss.h"
#include "CGameObjectRyu.h"
#include "CBonusRed.h"
#include "CBonusBlue.h"
#include "CFireWheel.h"
#include "CRestorePhysicalStrength.h"
#include "CSpiritualStrengthBlue.h"
#include "CSpiritualStrengthRed.h"
#include "CThrowingStar.h"
#include "CTimeFreeze.h"
#include "CItemContainer4.h"
#include "CGameObjectWall.h"
#include "CGameObjectBoss.h"
#include "CBulletBoss.h"
#include "CFireBullet.h"
#include "CFire.h"

class CGameObjects
{
public:
	virtual ~CGameObjects();

private:
	static CGameObjects* _instance;
	unordered_map<int, LPCGAMEOBJECT> _listObject;	// List of object in game

	CGameObjects();
	/// Create Object
	/// type: loai object
	/// id: ID object
	/// x, y: positon of object
	/// d: direction (0: right, 1: left)
	/// w, h: size of object
	LPCGAMEOBJECT CreateObject(int type, int id, int x = 0, int y = 0, int d = 0, int w = 0, int h = 0);

public:
	static CGameObjects* GetInstance();
	bool LoadFromFile(LPCWSTR filePath);
	unordered_map<int, LPCGAMEOBJECT> GetListObject();
	LPCGAMEOBJECT GetObjectByID(int id);
	bool AddObject(LPCGAMEOBJECT object);
	void RemoveObject(int id);
	void ClearListObject();
};

