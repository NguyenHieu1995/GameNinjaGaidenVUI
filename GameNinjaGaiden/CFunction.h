#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>

#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"

using namespace std;

inline wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wc, cSize, c, _TRUNCATE);
	return wc;
}



