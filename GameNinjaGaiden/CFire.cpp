#include "CFire.h"

CFire::CFire(int id) : CGameObject(id)
{
	this->_width = FIRE_COLLISION_WIDTH;
	this->_height = FIRE_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(1009));

	SetState(eStateItem::HIDEITEM);

	this->_tag = eObjectType::FIRE;
}

CFire::CFire(int id, int x, int y) : CGameObject(id, x, y)
{
	this->_width = FIRE_COLLISION_WIDTH;
	this->_height = FIRE_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(1009));

	SetState(eStateItem::HIDEITEM);

	this->_tag = eObjectType::FIRE;
}

CFire::~CFire(){}

void CFire::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_currentState == eStateItem::HIDEITEM || _currentState == eStateItem::DISAPPEARITEM)
		return;

	_vY += GRAVITY * dt;
	_frameTime += dt;

	CGameObject::Update(dt, coObject);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPCGAMEOBJECT> listMapObject;
	listMapObject.clear();

	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetTag() == eObjectType::GROUND ||
			coObject->at(i)->GetTag() == eObjectType::WALL)
		{
			listMapObject.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&listMapObject, coEvents);
	listMapObject.clear();


	if (coEvents.size() == 0)
	{
		_positionX += _dx;
		_positionY += _dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		_positionX += min_tx * _dx + nx * 0.4f;
		_positionY += min_ty * _dy + ny * 0.4f;
		if (nx != 0) _vX = 0;
		if (ny != 0) _vY = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CFire::Render()
{
	if (this->_currentState == eStateItem::HIDEITEM || this->_currentState == eStateItem::DISAPPEARITEM)
		return;

	if (_animationCurrent != NULL)
	{
		if ((_currentFrame == -1) || (_currentFrame > (_animationCurrent->GetTotalFrame() - 1)))
		{
			_currentFrame = 0;
			_frameTime = 0.0f;
		}
		else
		{
			if (_frameTime > _animationCurrent->GetFrameTime(_currentFrame))
			{
				_frameTime = 0.0f;

				if (_animationCurrent->IsFinishFrame(_currentFrame))
				{
					_currentFrame = 0;
				}
				else
				{
					_currentFrame++;
				}
			}
		}

		_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 255);
	}
}

RectEx CFire::GetBoundingBox()
{
	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + this->_width;
	top = bottom + this->_height;
}

void CFire::SetState(int state)
{
	CGameObject::SetState(state);

	switch (_currentState)
	{

	case eStateItem::HIDEITEM:
		this->_width = FIRE_COLLISION_WIDTH;
		this->_height = FIRE_COLLISION_HEIGHT;
		this->_animationCurrent == NULL;
		this->_currentState = eStateItem::HIDEITEM;
		break;

	case eStateItem::SHOWITEM:
		this->_width = FIRE_COLLISION_WIDTH;
		this->_height = FIRE_COLLISION_HEIGHT;
		this->_animationCurrent = _animation[0];
		this->_currentState = eStateItem::SHOWITEM;
		break;

	case eStateItem::DISAPPEARITEM:
		this->_vX = 0;
		this->_vY = 0;
		this->_width = 0;
		this->_height = 0;
		this->_animationCurrent == NULL;
		this->_currentState = eStateItem::DISAPPEARITEM;
		break;

	default:
		break;
	}
}