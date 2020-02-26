#include "CGame.h"
#include "CSampleKeyHandler.h"

CGame* CGame::_instance = NULL;

CGame::CGame()
{
	_initialized = false;
	_paused = false;
	_fps = 0.0f;
	_listObject.clear();
}

CGame::~CGame()
{
	delete CInput::GetInstance();

	delete CGameObjects::GetInstance();
	_listObject.clear();

	if (collisionTest != NULL)
		delete collisionTest;

	delete this->_gridMapTest;


	//delete this->_map;
	this->_map = NULL;
	//delete CFunction::GetInstance();
	delete CMaps::GetInstance();
	delete CAnimations::GetInstance();
	delete CSprites::GetInstance();
	delete CTextures::GetInstance();
	delete CDirectX::GetInstance();
	delete CTime::GetInstance();
	delete CCamera::GetInstance();
	delete CCollision::GetInstance();

	// Release the DirectSound buffer created above
	/*if (_DSBuffer)
	{
		_DSBuffer->Release();
		_DSBuffer = NULL;
	}*/

	// shutdown DirectSound
	//_testSound->shutdownDirectSound();
}

CGame* CGame::GetInstance()
{
	if (_instance == NULL)
		_instance = new CGame();

	return _instance;
}

bool CGame::Init()
{
	// Init Class DirectX
	if (CDirectX::GetInstance()->Init() == false)
		return false;

	// Load All Resource of Game
	this->LoadResource();
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

	//CBulletMachineGunGuy* test = new CBulletMachineGunGuy(1501, 500, 50);
	/*CFirebullet* test1 = new CFirebullet(1710, 10, 50, 0.15, 0.03);
	CGameObjects::GetInstance()->AddObject(test1);

	CFirebullet* test2 = new CFirebullet(1711, 10, 50, 0.15, 0.06);
	CGameObjects::GetInstance()->AddObject(test2);

	CFirebullet* test3 = new CFirebullet(1712, 10, 50, 0.15, 0.09);
	CGameObjects::GetInstance()->AddObject(test3);*/

	unordered_map<int, LPCGAMEOBJECT> listObject = CGameObjects::GetInstance()->GetListObject();

	for (auto object = listObject.begin(); object != listObject.end(); ++object)
	{
		if (object->second != NULL)
		{
			_listObject.push_back(object->second);
		}
	}

	QueryPerformanceFrequency(&_timerFreq);
	QueryPerformanceCounter(&_timeStart);

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

	CMaps::GetInstance()->LoadFileXML(PATH_XML_MAP);

	this->_map = CMaps::GetInstance()->Get(1);

	// Test 
	//this->_gridMapTest = new CGridMap(1, 16, 128, 256);
	this->_gridMapTest = new CGridMap(GRIDMAP_XML_PATH, 1, 16, 128, 256);

	_initialized = true;

	_score = 0;
	_time = 0;
	_idWeapon = 28;
	_number_P = 0;
	_spiritualStrengthPoint = 0;
	_stageFirst = 0; 
	_stageSecond = 0;
	_healthNinja = 0;
	_healthEnemy = 0;

	_timeFrameCurrent_Timer = 0;

	/*_testSound = new CGameSound();
	_testSound->initDirectSound(CWindow::GetInstance()->GetHwnd());
	_DSBuffer = _testSound->LoadWaveToSoundBuffer("sound1.wav");
	_DSBuffer->SetVolume(5000);
	_testSound->playSoundLoop(_DSBuffer);*/

	return true;
}

// Main Loop
void CGame::Run()
{
	// Check Direct Device
	if (CDirectX::GetInstance()->GetDirect3DDevice() == NULL)
		return;

	QueryPerformanceCounter(&_timeEnd);
	_frameTime = (float)(_timeEnd.QuadPart - _timeStart.QuadPart) / (float)_timerFreq.QuadPart;

	if (_frameTime < MIN_FRAME_TIME)
	{
		_sleepTime = (DWORD)((MIN_FRAME_TIME - _frameTime) * 1000);
		timeBeginPeriod(1);
		Sleep(_sleepTime);
		timeEndPeriod(1);
		return;
	}

	if (_frameTime > 0.0)
	{
		_fps = (_fps * 0.99f) + (0.01f / _frameTime);
	}

	if (_frameTime > MAX_FRAME_TIME)
	{
		_frameTime = MAX_FRAME_TIME;
	}

	_timeStart = _timeEnd;

	if (!_paused)
	{
		Update(DWORD(_frameTime * 1000));
	}

	Render();

}

// Update Object of Game
void CGame::Update(DWORD dt)
{
	CInput::GetInstance()->Update(_objectRyu);

	vector<LPCGAMEOBJECT> test = _gridMapTest->GetListObject();

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

	for (auto object = listObject.begin(); object != listObject.end(); ++object)
	{
		_listObject.push_back(object->second);

		if (object->second->GetTag() == eObjectType::BULLETMACHINEGUNGUY)
		{
			DebugOut(L"\nNew Object: %d", object->first);
		}
	}

	for (UINT i = 0; i < _listObject.size(); i++)
	{
		//_listObject.at(i)->SetVx(0);
		//_listObject.at(i)->SetVy(0);
		_listObject.at(i)->Update(dt, &_listObject);
		//DebugOut(L"\nSo luong doi tuong: %d", _listObject.size());
	}

	CCamera::GetInstance()->Update();

	_timeFrameCurrent_Timer += dt;
	if (_timeFrameCurrent_Timer > 1000)
	{
		_timeFrameCurrent_Timer = 0;
		_time++;
	}

	this->_healthNinja = _objectRyu->GetHealth();
	this->_number_P = _objectRyu->GetRevival();
	this->_idWeapon = _objectRyu->GetWeapon();
	this->_score += _objectRyu->GetBonus();
	this->_spiritualStrengthPoint = _objectRyu->GetSpiritualStrength();
}

// Render All Object in Game
void CGame::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = CDirectX::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backbuffer = CDirectX::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = CDirectX::GetInstance()->GetSpriteHandler();

	if (SUCCEEDED(d3ddv->BeginScene()))
	{
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//_map->Render();

		for (auto item = this->_listObject.begin(); item != _listObject.end(); ++item)
		{
			(*item)->Render();
			(*item)->RenderBoundingBox();
			//(*item)->RenderCollisionBox();
		}

		//this->_gridMapTest->RenderGridMap();

		CCamera::GetInstance()->Render(_score, _time, _idWeapon, _number_P, _spiritualStrengthPoint, _stageFirst, _stageSecond, _healthNinja, _healthEnemy);

		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

// Load All Resource Of Game
void CGame::LoadResource()
{
	// Load All Texture Form file XML
	CTextures::GetInstance()->LoadTexturesFromFileXML(TEXTURES_XML_PATH);
	CSprites::GetInstance()->LoadSpritesFromFileXML(SPRITES_XML_PATH);
	CAnimations::GetInstance()->LoadAnimationsFromFileXML(ANIMATIONS_XML_PATH);
}
