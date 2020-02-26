#include "CStateFirst.h"
#include "CDebug.h"
#include "CGameBase.h"
#include "CStateThird.h"
#include "CStateEnd.h"
#include "CConstant.h"

CStateFirst::CStateFirst() : CState()
{
	_score = 0;
	_time = 150;
	_idWeapon = 0;
	_number_P = 0;
	_spiritualStrengthPoint = 0;
	_stageFirst = 3;
	_stageSecond = 1;
	_healthNinja = 0;
	_healthEnemy = 16;
}

CStateFirst::~CStateFirst()
{
	
}

void CStateFirst::Init()
{
	//CGameObjects::GetInstance()->ClearListObject();
	CGameObjects::GetInstance()->LoadFromFile(LISTOBJECT_XML_PATH);

	// Init object Game
	this->_objectRyu = new CGameObjectRyu(100, 0, 70);
	CGameObjects::GetInstance()->AddObject(_objectRyu);
	//_listObject.push_back(_objectRyu);

	_objectDarts = new CDartsRed(101, 0, 0);
	CGameObjects::GetInstance()->AddObject(_objectDarts);
	//_listObject.push_back(_objectDarts);

	_objectSword = new CSword(102, 0, 0);
	CGameObjects::GetInstance()->AddObject(_objectSword);

	unordered_map<int, LPCGAMEOBJECT> listObject = CGameObjects::GetInstance()->GetListObject();

	for (auto object = listObject.begin(); object != listObject.end(); ++object)
	{
		if (object->second != NULL)
		{
			_listObject.push_back(object->second);
		}
	}

	CSampleKeyHandler* keyHandler = new CSampleKeyHandler();

	//_testInput = new CInput(keyHandler);
	CInput::GetInstance()->Initialize(CWindow::GetInstance()->GetHIntance(), CWindow::GetInstance()->GetHwnd(), SCREEN_WIDTH, SCREEN_HEIGHT, keyHandler);

	// Init Camera
	// Get size window client
	RECT _rectClientWindow;
	GetClientRect(CWindow::GetInstance()->GetHwnd(), (LPRECT)& _rectClientWindow); // get client coords
	ClientToScreen(CWindow::GetInstance()->GetHwnd(), (LPPOINT)& _rectClientWindow.left); // convert top-left
	ClientToScreen(CWindow::GetInstance()->GetHwnd(), (LPPOINT)& _rectClientWindow.right); // convert bottom-rignt
	CCamera::GetInstance()->SetPositionViewport(0.0f, float(_rectClientWindow.bottom - _rectClientWindow.top)); // 

	CCamera::GetInstance()->GetBound();
	CCamera::GetInstance()->Lock(_objectRyu);

	//CMaps::GetInstance()->LoadFileXML(PATH_XML_MAP);

	this->_map = new CMap(0, L"map\\map31.txt", CTextures::GetInstance()->Get(310));//CMaps:: GetInstance()->Get(1);

	// Test 
	//this->_gridMapTest = new CGridMap(1, 16, 128, 256);
	this->_gridMapTest = new CGridMap(GRIDMAP_XML_PATH, 1, 16, 128, 256);	

	_timeFrameCurrent_Timer = 0;

	CCamera::GetInstance()->SetMaxPostionX(_gridMapTest->GetColumn() * _gridMapTest->GetWidthCell());

	//_testSound = new CGameSound();
	//_testSound->initDirectSound(CWindow::GetInstance()->GetHwnd());
	//_DSBuffer = _testSound->LoadWaveToSoundBuffer("sound1.wav");
	//_DSBuffer->SetVolume(500);
	//_testSound->playSoundLoop(_DSBuffer);
	//CGameSound::GetInstance()->playSound("attack", true, 0);
}

void CStateFirst::Update(DWORD dt)
{
	CInput::GetInstance()->Update(_objectRyu);	

	unordered_map<int, LPCGAMEOBJECT> listObject = CGameObjects::GetInstance()->GetListObject();
	int checkDelete = false;
	_listObject.clear();
	for (auto object = listObject.begin(); object != listObject.end(); ++object)
	{
		if (object->second != NULL)
		{
			if ((object->second->GetTag() == eObjectType::KNIFEBANSHEE) &&
				(object->second->GetState() == eStateKnifeBanshee::HIDEKNIFEBANSHEE))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::BULLETMACHINEGUNGUY) &&
				(object->second->GetState() == eStateBulletMachineGunGuy::HIDEBULLETMACHINEGUNGUY))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::BULLETBOSS) &&
				(object->second->GetState() == eStateBulletBoss::HIDEBULLETBOSS))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::BONUSBLUE) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::ITEMCONTAINER4) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::BONUSRED) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::FIREWHEEL) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::RESTOREPHYSICALSTRENGTH) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::SPIRITUALSTRENGTHBLUE) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::SPIRITUALSTRENGTHRED) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::THROWINGSTAR) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::TIMEFREEZE) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::FIRE) &&
				(object->second->GetState() == eStateItem::DISAPPEARITEM))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if ((object->second->GetTag() == eObjectType::FIREBULLET) &&
				(object->second->GetState() == eStateFireBullet::HIDEFIREBULLET))
			{
				CGameObjects::GetInstance()->RemoveObject(object->first);
				checkDelete = true;
			}

			if (object->second->GetTag() == eObjectType::BOSS)
			{
				CGameObjectBoss* boss = dynamic_cast<CGameObjectBoss*>(object->second);
				_healthEnemy = boss->GetHealth();
			}
		}
	}

	if (checkDelete)
	{
		listObject.clear();
		listObject = CGameObjects::GetInstance()->GetListObject();
	}

	/*this->_gridMapTest->ReloadGridMap();
	_listObject = this->_gridMapTest->GetListObject();*/

	//vector<LPCGAMEOBJECT> test = _gridMapTest->GetListObject();

	//_gridMapTest->ReloadGridMap();
	_listObject = _gridMapTest->GetListObject();
	if (!(std::find(_listObject.begin(), _listObject.end(), _objectSword) != _listObject.end()))
	{
		_listObject.push_back(_objectSword);
	}

	if (!(std::find(_listObject.begin(), _listObject.end(), _objectDarts) != _listObject.end()))
	{
		_listObject.push_back(_objectDarts);
	}

	//for (auto object = listObject.begin(); object != listObject.end(); ++object)
	//{
	//	_listObject.push_back(object->second);

	//	/*if (object->second->GetTag() == eObjectType::BULLETMACHINEGUNGUY)
	//	{
	//		DebugOut(L"\nNew Object: %d", object->first);
	//	}*/
	//}

	for (UINT i = 0; i < _listObject.size(); i++)
	{
		//_listObject.at(i)->SetVx(0);
		//_listObject.at(i)->SetVy(0);
		_listObject.at(i)->Update(dt, &_listObject);
		//DebugOut(L"\nSo luong doi tuong: %d", _listObject.size());
	}

	CCamera::GetInstance()->Update();

	for (UINT i = 0; i < _listObject.size(); i++)
	{
		if ((_listObject.at(i)->GetTag() == eObjectType::DARTSRED) ||
			(_listObject.at(i)->GetTag() == eObjectType::DARTSSMALL) ||
			(_listObject.at(i)->GetTag() == eObjectType::SWORD) ||
			(_listObject.at(i)->GetTag() == eObjectType::FIREBULLET))
		{
			this->_score += _listObject.at(i)->GetScore();
		}
	}

	_timeFrameCurrent_Timer += dt;
	if (_timeFrameCurrent_Timer >= 1000)
	{
		_timeFrameCurrent_Timer = 0;
		_time--;
	}

	this->_healthNinja = _objectRyu->GetHealth();
	this->_number_P = _objectRyu->GetRevival();
	this->_idWeapon = _objectRyu->GetWeapon();
	this->_score += _objectRyu->GetBonus();
	this->_spiritualStrengthPoint = _objectRyu->GetSpiritualStrength();

	if (_time <= 0)
	{
		_time = 150;
		_objectRyu->Reset();
	}

	//if (_objectRyu->GetPosition().x > CCamera::GetInstance()->GetMaxPostionX() - 30)
	if (_objectRyu->GetPosition().x > CCamera::GetInstance()->GetMaxPostionX() - 1800)
	{
		CStates::GetInstance()->SwitchState(new CStateThird(this->_score, this->_number_P, this->_idWeapon));
	}

	if (_objectRyu->GetRevival() < 0)
	{
		CStates::GetInstance()->SwitchState(new CStateFirst());
	}

	if (_objectRyu->IsResetTime())
	{
		_time = 150;
	}
}

void CStateFirst::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = CDirectX::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backbuffer = CDirectX::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = CDirectX::GetInstance()->GetSpriteHandler();

	if (SUCCEEDED(d3ddv->BeginScene()))
	{
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		_map->Render();

		for (auto item = this->_listObject.begin(); item != _listObject.end(); ++item)
		{
			(*item)->Render();
			//(*item)->RenderBoundingBox();
			//(*item)->RenderCollisionBox();
		}

		//this->_gridMapTest->RenderGridMap();

		CCamera::GetInstance()->Render(_score, _time, _idWeapon, _number_P, _spiritualStrengthPoint, _stageFirst, _stageSecond, _healthNinja, _healthEnemy);

		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void CStateFirst::Exit()
{
	//delete CInput::GetInstance();
	//delete CGameObjects::GetInstance();
	//_listObject.clear();
	//_listObject.erase(_listObject.begin(), _listObject.end());

	//CGameObjects::GetInstance()->ClearListObject();

	delete this->_gridMapTest;
	delete this->_map;
	this->_map = NULL;
	//delete CMaps::GetInstance();

	/*delete CTime::GetInstance();
	delete CCamera::GetInstance();
	delete CCollision::GetInstance();*/

	// Release the DirectSound buffer created above
		/*if (_DSBuffer)
		{
			_DSBuffer->Release();
			_DSBuffer = NULL;
		}*/
}