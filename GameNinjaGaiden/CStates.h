#pragma once

#include <Windows.h>

class CState
{
public:
	CState() {}
	virtual ~CState() {}
	virtual void Init() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

class CStates
{
public:
	~CStates();

protected:
	CStates();

protected:
	static CStates* _pInstance;
	CState* _pCurrentState;
	CState* _pNextState;

public:
	static CStates* GetInstance();
	void Update(bool isPause, DWORD dt);
	void SwitchState(CState* nextState);

};

