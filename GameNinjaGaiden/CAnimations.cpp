#include "CAnimations.h"

//============================================================================================
// CAnimationFrame
//============================================================================================
CAnimationFrame::CAnimationFrame(LPCSPRITE sprite, int time) 
{
	this->_sprite = sprite;
	this->_time = time;
}

DWORD CAnimationFrame::GetTime() 
{
	return _time;
}

LPCSPRITE CAnimationFrame::GetSprite() 
{
	return _sprite;
}

CAnimationFrame::~CAnimationFrame()
{
	_sprite = NULL;
}

//============================================================================================
// CAnimation
//============================================================================================
CAnimation::~CAnimation()
{
	//for (std::vector<LPCANIMATIONFRAME>::iterator item = _frames.begin(); item != _frames.end(); ++it) {
	//	/* std::cout << *it; ... */
	//	delete item;
	//}


	for (auto item = _frames.begin(); item != _frames.end(); ++item)
	{
		delete *item;
	}
	_frames.clear();
}
CAnimation::CAnimation(int defaultTime)
{
	this->_defaultTime = defaultTime;
	//this->_currentFrame = -1;
	this->_frameTime = -1;
	//this->_isFinishFrame = false;
}

bool CAnimation::IsFinishFrame(int idFrame)
{
	return (idFrame >= (_frames.size() - 1));
}

void CAnimation::Add(int IdSprite, DWORD time)
{
	int t = time;
	if (time == 0)
		t = this->_defaultTime;

	LPCSPRITE sprite = CSprites::GetInstance()->Get(IdSprite);
	LPCANIMATIONFRAME frame = new CAnimationFrame(sprite, t);
	_frames.push_back(frame);
}



void CAnimation::Render(float x, float y, int currentFrame, int alpha, bool flipX, bool flipY, float angle)
{
	_frames[currentFrame]->GetSprite()->Draw(x, y, alpha, flipX, flipY, angle);
}

//void CAnimation::Render(float x, float y, int currentFrame, bool FlipX, float xFlip, bool FlipY, float yFlip)
//{
//	_frames[currentFrame]->GetSprite()->Draw(x, y, FlipX, xFlip, FlipY, yFlip);
//}

float CAnimation::GetFrameTime(int idFrame)
{
	return (float)this->_frames[idFrame]->GetTime();
}

int CAnimation::GetTotalFrame()
{
	return (int)this->_frames.size();
}

//============================================================================================
// CAnimations
//============================================================================================
CAnimations* CAnimations::_instance = NULL;

CAnimations* CAnimations::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CAnimations();
	}

	return _instance;
}

CAnimations::CAnimations()
{

}

CAnimations::~CAnimations()
{
	for (auto item = _animation.begin(); item != _animation.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_animation.clear();
}

void CAnimations::LoadAnimationsFromFileXML(LPCWSTR filePath)
{
	_bstr_t path(filePath);
	TiXmlDocument doc(path);

	if (!doc.LoadFile())
	{
		DebugOut(L"[ERROR] Load file XML Animations that bai! Loi: %s\n", doc.ErrorDesc());
		return;
	}

	//DebugOut(L"[INFO] Duong dan file XML Animation: %s\n", filePath);

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* animation = nullptr;
	TiXmlElement * sprite = nullptr;
	int id, timeDefault;
	int idSprite, timeSprite;

	CAnimation* animationAdd;

	for (animation = root->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement())
	{
		animation->QueryIntAttribute("id", &id);
		animation->QueryIntAttribute("timeDefault", &timeDefault);
		//DebugOut(L"[SUCCESS] Load animation id %d timeDeault %d\n", id, timeDefault);

		animationAdd = new CAnimation(timeDefault);

		for (sprite = animation->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
		{
			sprite->QueryIntAttribute("id", &idSprite);
			sprite->QueryIntAttribute("time", &timeSprite);

			animationAdd->Add(idSprite, timeSprite);

			//DebugOut(L"[SUCCESS] Load Sprite %d for animation %d\n", idSprite, timeSprite);
		}
		CAnimations::GetInstance()->Add(id, animationAdd);
		animationAdd = NULL;
	}

	//DebugOut(L"[SUCCESS] Load all Animation success");

}

void CAnimations::Add(int id, LPCANIMATION animation)
{
	_animation[id] = animation;
}

LPCANIMATION CAnimations::Get(int id)
{
	return _animation[id];
}
