#include "CCamera.h"

// Pattern Singleton
CCamera* CCamera::_instance = NULL;

CCamera* CCamera::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CCamera();
	}

	return _instance;
}

CCamera::CCamera()
{
	this->_positionX = 0;
	this->_positionY = 0;
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;
	_objectLock = NULL;

	_minPositioX = 0;
	_maxPostionX = 256;
}

CCamera::~CCamera()
{
	_objectLock = NULL;
}

void CCamera::SetPositionViewport(float x, float y)
{
	this->_positionX = x;
	this->_positionY = y;
}

D3DXVECTOR2 CCamera::GetPostionInViewport(float x, float y)
{
	D3DXVECTOR4 posWorld(x, y, 1.0f, 1.0f); // Vector 4x4 vi tri cua doi tuong trong world
	D3DXMATRIX mt;							// Ma tran bien doi world => viewport
	D3DXVECTOR4 posViewport;				// Vector 4x4 vi tri cua doi truong tren viewport

	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = (-1) * _positionX;
	mt._42 = _positionY;

	D3DXVec4Transform(&posViewport, &posWorld, &mt);

	return D3DXVECTOR2(posViewport.x, posViewport.y);
}

RECT CCamera::GetBound()
{
	RECT rect;
	rect.left = (LONG)_positionX;
	rect.right = (LONG)(rect.left + _width);
	rect.top = (LONG)_positionY;
	rect.bottom = (LONG)(_height - _positionY);

	//DebugOut(L"\n[INFO] CCamera.cpp Bound of Camera: l: %d - t: %d - b: %d - r: %d\n", rect.left, rect.top, rect.bottom, rect.right);
	return rect;
}

void CCamera::Update()
{
	// if doi tuong != NULL thi update vi tri camera theo doi tuong
	if (_objectLock != NULL)
	{
		D3DXVECTOR2 p;
		p = _objectLock->GetPosition();

		_positionX = p.x - _width / 2;
		_positionY = SCREEN_HEIGHT - 40;
		//_positionY = p.y + _height / 2;

		if (_positionX < 0)
		{
			_positionX = 0;
		}

		if (_positionX > _maxPostionX - SCREEN_WIDTH)
		{
			_positionX = _maxPostionX - SCREEN_WIDTH;
		}

		////if (_positionX + SCREEN_HEIGHT > )

		//if (_positionY - SCREEN_HEIGHT < 40)
		//{
		//	_positionY = SCREEN_HEIGHT - 40;
		//}
	}
}

void CCamera::Lock(CGameObject* object)
{
	// Set doi tuong khoa man hinh
	_objectLock = object;
}

void CCamera::UnLock()
{
	// Xoa doi tuong
	_objectLock = NULL;
}

int ConvertStringToSprite(char string)
{
	switch (string)
	{

	case 'A':
		return 2000;

	case 'B':
		return 2001;

	case 'C':
		return 2002;

	case 'D':
		return 2003;

	case 'E':
		return 2004;

	case 'F':
		return 2005;

	case 'G':
		return 2006;

	case 'H':
		return 2007;

	case 'I':
		return 2008;

	case 'J':
		return 2009;

	case 'K':
		return 2010;

	case 'L':
		return 2011;

	case 'M':
		return 2012;

	case 'N':
		return 2013;

	case 'O':
		return 2014;

	case 'P':
		return 2015;

	case 'Q':
		return 2016;

	case 'R':
		return 2017;

	case 'S':
		return 2018;

	case 'T':
		return 2019;

	case 'U':
		return 2020;

	case 'V':
		return 2021;

	case 'W':
		return 2022;

	case 'X':
		return 2023;

	case 'Y':
		return 2024;

	case 'Z':
		return 2025;

	case '0':
		return 2054;

	case '1':
		return 2055;

	case '2':
		return 2056;

	case '3':
		return 2057;

	case '4':
		return 2058;

	case '5':
		return 2059;

	case '6':
		return 2060;

	case '7':
		return 2061;

	case '8':
		return 2062;

	case '9':
		return 2063;

	case '-':
		return 2079;

	default:
		return 2088;
	}
}

char ConvertIntToChar(int number)
{
	switch (number)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';

	default:
		return '@';
	}
}

char* ConvertNumberToArray(int number, int size)
{
	char* result = new char[size];
	int numberTemp = number;

	for(int i = size - 1; i >=0; --i)
	{
		result[i] = ConvertIntToChar(numberTemp % 10);
		numberTemp /= 10;
	}

	return result;
}

void CCamera::Render(int score, int time, int idWeapon, int number_P, int spiritualStrengthPoint, int stageFirst, int stageSecond, int healthNinja, int healthEnemy)
{
	/*int healthNinja = 8;
	int healthEnemy = 14;
	int stageFirst = 3;
	int stageSecond = 1;
	int time = 118;
	int score = 63800;
	int idWeapon = 28;
	int number_P = 2;
	int spiritualStrengthPoint = 10;*/

	// Cot - Hang

	// 1 - 1 => SCORE-
	CSprites::GetInstance()->Get(ConvertStringToSprite('S'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 0 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('C'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 1 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('O'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 2 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('R'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 3 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('E'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 4 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('-'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 5 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);

	char* arrScore = ConvertNumberToArray(score, 6);
	for (int i = 0; i < 6; i++)
	{
		CSprites::GetInstance()->Get(ConvertStringToSprite(arrScore[i]))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + ((6 + i) * WIDTH_TEXT), _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	}
	delete[] arrScore;

	// 1 - 2 => TIMER-
	CSprites::GetInstance()->Get(ConvertStringToSprite('T'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 0 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('I'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 1 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('M'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 2 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('E'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 3 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('R'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 4 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('-'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 5 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);

	char* arrTime = ConvertNumberToArray(time, 3);
	for (int i = 0; i < 3; i++)
	{
		CSprites::GetInstance()->Get(ConvertStringToSprite(arrTime[i]))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + ((6 + i) * WIDTH_TEXT), _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	}
	delete[] arrTime;

	CSprites::GetInstance()->Get(2067)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 9 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	if (idWeapon != 0)
	{
		CSprites::GetInstance()->Get(idWeapon)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 10 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	}
	CSprites::GetInstance()->Get(2067)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 12 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);

	// 1 - 3 => P-02
	CSprites::GetInstance()->Get(2015)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 0 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(2079)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 1 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	char* arrP = ConvertNumberToArray(number_P, 2);
	for (int i = 0; i < 2; i++)
	{
		CSprites::GetInstance()->Get(ConvertStringToSprite(arrP[i]))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + (2 + i) * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	}
	delete[] arrP;

	CSprites::GetInstance()->Get(2202)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 5 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(2079)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 6 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	char* arrSSP = ConvertNumberToArray(spiritualStrengthPoint, 2);
	for (int i = 0; i < 2; i++)
	{
		CSprites::GetInstance()->Get(ConvertStringToSprite(arrSSP[i]))->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + (7 + i) * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	}
	delete[] arrSSP;

	CSprites::GetInstance()->Get(2067)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 9 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(2067)->Draw(POSITON_X_DRAW_BLOCK_TEXT_1 + _positionX + 12 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);

	// 2 - 1 => STAGE-
	CSprites::GetInstance()->Get(ConvertStringToSprite('S'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 0 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('T'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 1 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('A'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 2 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('G'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 3 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('E'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 4 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('-'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 5 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);

	CSprites::GetInstance()->Get(ConvertStringToSprite(ConvertIntToChar(stageFirst)))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 6 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('-'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 7 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite(ConvertIntToChar(stageSecond)))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 8 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 0 * HEIGHT_TEXT, 255);

	// 2 - 2 => NINJA-
	CSprites::GetInstance()->Get(ConvertStringToSprite('N'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 0 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('I'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 1 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('N'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 2 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('J'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 3 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('A'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 4 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('-'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 5 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);

	for (int i = 0; i < 16; i++)
	{
		if (i < healthNinja)
		{
			CSprites::GetInstance()->Get(2200)->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 6 * WIDTH_TEXT + i * WIDTH_BLOOD, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
		}
		else
		{
			CSprites::GetInstance()->Get(2201)->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 6 * WIDTH_TEXT + i * WIDTH_BLOOD, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 1 * HEIGHT_TEXT, 255);
		}
	}

	// 2 - 3 => ENEMY-
	CSprites::GetInstance()->Get(ConvertStringToSprite('E'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 0 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('N'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 1 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('E'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 2 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('M'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 3 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('Y'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 4 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
	CSprites::GetInstance()->Get(ConvertStringToSprite('-'))->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 5 * WIDTH_TEXT, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);

	for (int i = 0; i < 16; i++)
	{
		if (i < healthEnemy)
		{
			CSprites::GetInstance()->Get(2200)->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 6 * WIDTH_TEXT + i * WIDTH_BLOOD, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
		}
		else
		{
			CSprites::GetInstance()->Get(2201)->Draw(POSITON_X_DRAW_BLOCK_TEXT_2 + _positionX + 6 * WIDTH_TEXT + i * WIDTH_BLOOD, _positionY - POSITON_Y_DRAW_BLOCK_TEXT_1 - 2 * HEIGHT_TEXT, 255);
		}
	}

}


int CCamera::GetMinPositioX()
{
	return _minPositioX;
}

int CCamera::GetMaxPostionX()
{
	return _maxPostionX;
}

void CCamera::SetMinPositioX(int x)
{
	_minPositioX = x;
}

void CCamera::SetMaxPostionX(int x)
{
	_maxPostionX = x;
}
