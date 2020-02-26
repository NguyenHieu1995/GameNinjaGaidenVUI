#include "CGameNinjaGaiden.h"
#include "CDebug.h"

CGameNinjaGaiden::CGameNinjaGaiden() : CGameBase()
{
}

CGameNinjaGaiden::~CGameNinjaGaiden()
{
}

bool CGameNinjaGaiden::Init()
{
	CStates::GetInstance()->SwitchState(new CStateIntro());
	DebugOut(L"Init Management State!\n");

	// Init Class DirectX
	if (CDirectX::GetInstance()->Init() == false)
		return false;

	if (CDirectX::GetInstance()->GetDirect3DDevice() == NULL)
		return false;

	CGameSound::GetInstance()->initDirectSound(CWindow::GetInstance()->GetHwnd());

	// Load All Resource of Game
	this->LoadResource();

	//CSampleKeyHandler* keyHandler = new CSampleKeyHandler();

	//_testInput = new CInput(keyHandler);
	//CInput::GetInstance()->Initialize(CWindow::GetInstance()->GetHIntance(), CWindow::GetInstance()->GetHwnd(), SCREEN_WIDTH, SCREEN_HEIGHT, keyHandler);
	CGameObjects::GetInstance();
	return true;
}

void CGameNinjaGaiden::Destroy()
{
	DebugOut(L"Destroy Management State!\n");

	delete CGameObjects::GetInstance();

	CGameSound::GetInstance()->shutdownDirectSound();
	delete CGameSound::GetInstance();

	CInput::GetInstance()->ShutDown();
	delete CInput::GetInstance();

	delete CAnimations::GetInstance();
	delete CSprites::GetInstance();
	delete CTextures::GetInstance();
	delete CDirectX::GetInstance();

	delete CTime::GetInstance();
	delete CCamera::GetInstance();
	delete CCollision::GetInstance();
}

// Load All Resource Of Game
void CGameNinjaGaiden::LoadResource()
{
	// Load All Texture Form file XML
	CTextures::GetInstance()->LoadTexturesFromFileXML(TEXTURES_XML_PATH);
	CSprites::GetInstance()->LoadSpritesFromFileXML(SPRITES_XML_PATH);
	CAnimations::GetInstance()->LoadAnimationsFromFileXML(ANIMATIONS_XML_PATH);
	CGameSound::GetInstance()->LoadFromFileXML(SOUND_XML_PATH);
}