#pragma once
#include "CGameBase.h"
#include "CStates.h"
#include "CStateIntro.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "CConstant.h"
#include "CDebug.h"
#include "CDirectX.h"
#include "Tiny/tinyxml.h"
#include "CFunction.h"
#include "CTextures.h"
#include "CSprites.h"
#include "CAnimations.h"
#include "CTime.h"
#include <mmsystem.h>
#include "CInput.h"
#include "CCamera.h"
#include "CCollision.h"
#include "CGameObject.h"
#include "CMap.h"
#include "CGameObjectRyu.h"
#include "CGameObjectGround.h"
#include "CGridMap.h"
#include "CGameObjects.h"
#include "CSampleKeyHandler.h"
#include "CGameSound.h"

class CGameNinjaGaiden : public CGameBase
{

public:
	CGameNinjaGaiden();
	virtual ~CGameNinjaGaiden();

public:
	bool Init();
	void Destroy();
	void LoadResource();

};

