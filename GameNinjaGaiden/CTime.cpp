#include "CTime.h"

CTime* CTime::_instance = NULL;

CTime::CTime()
{
	
}

CTime::~CTime()
{
	
}

CTime* CTime::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CTime();
	}

	return _instance;
}
 
void CTime::StartCounter()
{
	if (!QueryPerformanceFrequency(&_freq))
	{
		return;
	}

	QueryPerformanceCounter(&_start);
}

double CTime::GetTime()
{
	QueryPerformanceCounter(&_end);
	return double((_end.QuadPart - _start.QuadPart) * 10000 / _freq.QuadPart);
}