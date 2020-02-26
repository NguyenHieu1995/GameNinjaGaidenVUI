#include "CGameObjectWall.h"

CGameObjectWall::CGameObjectWall(int id) : CGameObject(id)
{
	this->_tag = eObjectType::WALL;
}

CGameObjectWall::CGameObjectWall(int id, int x, int y, int w, int h) : CGameObject(id, x, y)
{
	this->_width = (float)w;
	this->_height = (float)h;
	this->_tag = eObjectType::WALL;
}

CGameObjectWall::~CGameObjectWall()
{
}

void CGameObjectWall::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{

}

RectEx CGameObjectWall::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CGameObjectWall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}