#include "CItemContainer4.h"

CItemContainer4::CItemContainer4(int id) : CGameObject(id)
{
	this->_width = ITEMCONTAINER4_COLLISION_WIDTH;
	this->_height = ITEMCONTAINER4_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(1008));

	this->_animationCurrent = _animation[0];

	SetState(eStateItem::SHOWITEM);

	this->_tag = eObjectType::ITEMCONTAINER4;
}

CItemContainer4::CItemContainer4(int id, int x, int y) : CGameObject(id, x, y)
{
	this->_width = ITEMCONTAINER4_COLLISION_WIDTH;
	this->_height = ITEMCONTAINER4_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(1008));

	this->_animationCurrent = _animation[0];

	SetState(eStateItem::SHOWITEM);

	this->_tag = eObjectType::ITEMCONTAINER4;
}

CItemContainer4::~CItemContainer4()
{
}

void CItemContainer4::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_currentState == eStateItem::HIDEITEM || _currentState == eStateItem::DISAPPEARITEM)
		return;

	_frameTime += dt;
}

void CItemContainer4::Render()
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

RectEx CItemContainer4::GetBoundingBox()
{
	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CItemContainer4::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + this->_width;
	top = bottom + this->_height;
}

void CItemContainer4::SetState(int state)
{
	CGameObject::SetState(state);

	switch (_currentState)
	{

	case eStateItem::HIDEITEM:
		this->_width = ITEMCONTAINER4_COLLISION_WIDTH;
		this->_height = ITEMCONTAINER4_COLLISION_HEIGHT;
		this->_animationCurrent = NULL;
		this->_currentState = eStateItem::HIDEITEM;
		break;

	case eStateItem::SHOWITEM:
		this->_width = ITEMCONTAINER4_COLLISION_WIDTH;
		this->_height = ITEMCONTAINER4_COLLISION_HEIGHT;
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