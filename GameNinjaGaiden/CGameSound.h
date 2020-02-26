#pragma once

#include <dsound.h>
#include "dsutil.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <d3dx9.h>
#include <Windows.h>
#include <unordered_map>
#include "CFunction.h"

using namespace std;

class CGameSound
{
public:
	~CGameSound();

private:
	CGameSound();
	static CGameSound* _pInstance;

	LPDIRECTSOUND8 _pDirectXSound;//g_pDS;	// The DirectSound Device
	HWND _wndHandle;

	unordered_map<string, LPDIRECTSOUNDBUFFER> _listSoundBuffer;
	//unordered_map<string, IDirectSoundBuffer*> _listSoundBuffer;

public:
	static CGameSound* GetInstance();

	bool initDirectSound(HWND hwnd);
	void shutdownDirectSound(void);
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename);
	void playSound(string nameSound, bool  isLoop, int times);
	void stopSound(string nameSound);
	void playSound(LPDIRECTSOUNDBUFFER whichBuffer);
	void playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer);
	void stopSound(LPDIRECTSOUNDBUFFER whichBuffer);
	LPDIRECTSOUND8 GetDirectSound();

	bool LoadFromFileXML(string filename = "");
};
typedef CGameSound* LPCGAMESOUND;


//class CGameSounds
//{
//public:
//	CGameSounds();
//	~CGameSounds();
//
//protected:
//	static CGameSounds* _pInstance;
//	unordered_map<int, LPCGAMESOUND> _listGameSound;
//
//
//public:
//	static CGameSounds* GetInstance();
//	LPCGAMESOUND Get(unsigned int id);
//};

