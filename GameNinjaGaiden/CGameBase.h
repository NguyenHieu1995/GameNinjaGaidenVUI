#pragma once

#include <Windows.h>
#include "CDirectX.h"
#include "CConstant.h"

class CGameBase
{
public:
	virtual ~CGameBase();

protected:
	CGameBase();
	static CGameBase* _pInstance;

protected:
	bool _isAlived;
	bool _isPaused;

public:
	bool IsAlive();
	bool IsPause();
	virtual void Run();
	virtual void Exit();
	virtual void Pause();
	virtual void Resume();

	static CGameBase* GetInstance();

	virtual bool Init() = 0;
	virtual void Destroy() = 0;


protected:
	LARGE_INTEGER _timeStart;		// Performance Counter start value
	LARGE_INTEGER _timeEnd;			// Performance Counter end value
	LARGE_INTEGER _timerFreq;		// Performance Counter frequency
	float _frameTime;				// time required for last frame
	float _fps;						// frames per second
	DWORD _sleepTime;				// number of milli-seconds to sleep between frames
};

