#include "CGameSound.h"
#include "Tiny/tinyxml.h"
#include "CDebug.h"

CGameSound* CGameSound::_pInstance = NULL;

CGameSound* CGameSound::GetInstance()
{
	if (_pInstance == NULL)
	{
		_pInstance = new CGameSound();
	}

	return _pInstance;
}

void CGameSound::playSound(string nameSound, bool  isLoop, int times)
{
	if (_listSoundBuffer[nameSound] == NULL)
		return;

	if (true == isLoop)
	{
		_listSoundBuffer[nameSound]->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		_listSoundBuffer[nameSound]->Stop();
		_listSoundBuffer[nameSound]->SetCurrentPosition(0);
		_listSoundBuffer[nameSound]->Play(0, 0, times - 1);
	}
}

void CGameSound::stopSound(string nameSound)
{
	_listSoundBuffer[nameSound]->Stop();
}

bool CGameSound::LoadFromFileXML(string filename)
{
	if (filename == "")
	{
		/*_listSoundBuffer["test"] = LoadWaveToSoundBuffer("sound//34.wav");*/
		return false;
	}
	
	_bstr_t path(filename.c_str());
	TiXmlDocument doc(path);

	if (!doc.LoadFile())
	{
		DebugOut(L"[ERROR] Load file XML Sprites that bai! Loi: %s\n", doc.ErrorDesc());
		return false;
	}

	//DebugOut(L"[INFO] Duong dan file XML SPrites: %s\n", filePath);

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* sound = nullptr;
	string pathSound;
	string name;

	for (sound = root->FirstChildElement(); sound != NULL; sound = sound->NextSiblingElement())
	{
		name = sound->Attribute("name");
		pathSound = sound->Attribute("path");
			
		_listSoundBuffer[name] = LoadWaveToSoundBuffer(pathSound);
		//delete[] pathTexture;
		//DebugOut(L"[INFO]Add Texture: %d\n", id);
	}
	
	return true;
}

//===========================================================================================

CGameSound::CGameSound() 
{
}

CGameSound::~CGameSound()
{
	
}

/*******************************************************************
* shutdownDirectSound
* Releases the DirecSound device
*******************************************************************/
void CGameSound::shutdownDirectSound(void)
{
	for (auto item = _listSoundBuffer.begin(); item != _listSoundBuffer.end(); ++item)
	{
		if (item->second)
		{
			item->second->Release();
			item->second = NULL;
		}
	}
	_listSoundBuffer.clear();

	if (_pDirectXSound)
	{
		_pDirectXSound->Release();
		_pDirectXSound = NULL;
	}
}
/*******************************************************************
* initDirectSound
* Initializes DirectSound
*******************************************************************/
bool CGameSound::initDirectSound(HWND hwnd)
{
	HRESULT hr;

	_wndHandle = hwnd;

	hr = DirectSoundCreate8(NULL, &_pDirectXSound, NULL);
	if FAILED(hr)
		return false;

	// Set DirectSound cooperative level 
	hr = _pDirectXSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if FAILED(hr)
		return false;

	return true;
}

/*******************************************************************
* LoadWaveToSoundBuffer
* Loads a wave file into a DirectSound Buffer
*******************************************************************/
LPDIRECTSOUNDBUFFER CGameSound::LoadWaveToSoundBuffer(std::string wavFilename)
{
	LPDIRECTSOUNDBUFFER apDSBuffer = NULL;
	CWaveFile* wavFile;
	HRESULT hr;

	wavFile = new CWaveFile();
	//wavFile->Open((LPTSTR)L"sound//34.wav", NULL, WAVEFILE_READ);
	wchar_t* fileName = GetWC(wavFilename.c_str());
	wavFile->Open((LPTSTR)fileName, NULL, WAVEFILE_READ);
	delete fileName;

	if (wavFile->GetSize() == 0)
	{
		MessageBox(_wndHandle, L"invalid file", L"ERROR", MB_OK);
		return false;
	}

	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = 0;
	dsbd.dwBufferBytes = wavFile->GetSize();
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = wavFile->m_pwfx;

	hr = _pDirectXSound->CreateSoundBuffer(&dsbd, &apDSBuffer, NULL);
	if FAILED(hr)
	{
		MessageBox(NULL, L"unable to create sound buffer", L"ERROR", MB_OK);
		return NULL;
	}

	VOID* pDSLockedBuffer = NULL; // Pointer to locked buffer memory
	DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
	DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file 

	hr = apDSBuffer->Lock(0, wavFile->GetSize(),
		&pDSLockedBuffer, &dwDSLockedBufferSize,
		NULL, NULL, 0L);
	if FAILED(hr)
		return NULL;

	// Reset the wave file to the beginning 
	wavFile->ResetFile();

	// Read the wave file
	hr = wavFile->Read((BYTE*)pDSLockedBuffer,
		dwDSLockedBufferSize,
		&dwWavDataRead);
	// Check to make sure that this was successful
	if FAILED(hr)
		return NULL;

	// Check to make sure the wav file is not empty
	if (dwWavDataRead == 0)
	{
		// Wav is blank, so just fill with silence
		FillMemory((BYTE*)pDSLockedBuffer,
			dwDSLockedBufferSize,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}
	else if (dwWavDataRead < dwDSLockedBufferSize)
	{
		// Don't repeat the wav file, just fill in silence 
		FillMemory((BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	// Unlock the buffer, we don't need it anymore.
	apDSBuffer->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

	// Clean up
	delete wavFile;

	return apDSBuffer;
}

/*******************************************************************
* playSound
* plays a sound currently in a buffer only once
*******************************************************************/
void CGameSound::playSound(LPDIRECTSOUNDBUFFER whichBuffer)
{
	whichBuffer->Play(0, 0, 0);
}

/*******************************************************************
* playSoundLoop
* plays a sound in a buffer repeatedly
*******************************************************************/
void CGameSound::playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer)
{
	whichBuffer->Play(0, 0, DSBPLAY_LOOPING);
}

/*******************************************************************
* stopSound
* stops the sound in this buffer from playing
*******************************************************************/
void CGameSound::stopSound(LPDIRECTSOUNDBUFFER whichBuffer)
{
	whichBuffer->Stop();
}

LPDIRECTSOUND8 CGameSound::GetDirectSound()
{
	return _pDirectXSound;
}


