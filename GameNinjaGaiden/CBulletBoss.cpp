#include "CBulletBoss.h"


CBulletBoss::CBulletBoss(int id) : CGameObject(id)
{
	this->_animation.push_back(CAnimations::GetInstance()->Get(4002));
	this->_animationCurrent = _animation[0];

	SetState(eStateBulletBoss::SHOWBULLETBOSS);
	this->_tag = eObjectType::BULLETBOSS;

	this->_vX = BULLETBOSS_SPEED;
}

CBulletBoss::CBulletBoss(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_animation.push_back(CAnimations::GetInstance()->Get(4002));
	this->_animationCurrent = _animation[0];

	SetState(eStateBulletBoss::SHOWBULLETBOSS);
	this->_tag = eObjectType::BULLETBOSS;

	//this->_vX = BULLETBOSS_SPEED;

	if (direction)
	{
		_nx = 1;
		_nxStart = _nx;
		this->_vX = BULLETBOSS_SPEED;
	}
	else
	{
		_nx = -1;
		_nxStart = _nx;
		this->_vX = -BULLETBOSS_SPEED;
	}
}

CBulletBoss::~CBulletBoss()
{

}

void CBulletBoss::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_positionX < CCamera::GetInstance()->GetBound().left || _positionX > CCamera::GetInstance()->GetBound().right)
	{
		SetState(eStateBulletBoss::HIDEBULLETBOSS);
	}

	if (_currentState == eStateBulletBoss::HIDEBULLETBOSS)
	{
		return;
	}

	this->_vX = _nx * BULLETBOSS_SPEED;

	_frameTime += dt;

	if (_currentState == eStateBulletBoss::SHOWBULLETBOSS)
	{
		CGameObject::Update(dt, coObject);

		_positionX += _dx;
		_positionY += _dy;
	}

	if (_positionX < CCamera::GetInstance()->GetBound().left || _positionX > CCamera::GetInstance()->GetBound().right)
	{
		SetState(eStateBulletBoss::HIDEBULLETBOSS);
	}
}

void CBulletBoss::Render()
{
	if (_currentState == eStateBulletBoss::HIDEBULLETBOSS)
	{
		return;
	}

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

		bool flip = false;
		if (_nx >= 0)
		{
			flip = false;
		}
		else
		{
			flip = true;
		}

		_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 255, flip);
	}
}

RectEx CBulletBoss::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CBulletBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CBulletBoss::SetState(int state)
{
	CGameObject::SetState(state);

	switch (_currentState)
	{
	case eStateBulletBoss::HIDEBULLETBOSS:
		this->_width = 0.0f;
		this->_height = 0.0f;
		break;

	case eStateBulletBoss::SHOWBULLETBOSS:
		this->_width = BULLETBOSS_COLLISION_WIDTH;
		this->_height = BULLETBOSS_COLLISION_HEIGHT;
		this->_animationCurrent = _animation[0];
		break;

	default:
		break;
	}
}

