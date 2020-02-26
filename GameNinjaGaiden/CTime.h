#pragma once
#include <Windows.h>


class CTime
{
public:
	CTime();
	~CTime();

private:
	LARGE_INTEGER _start;
	LARGE_INTEGER _end;
	LARGE_INTEGER _freq;

	static CTime* _instance;

public:
	static CTime* GetInstance();
	
	void StartCounter();
	double GetTime();	
};
