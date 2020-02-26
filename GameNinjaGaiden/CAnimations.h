#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CDebug.h"
#include "CConstant.h"
#include <unordered_map>
#include "Tiny/tinyxml.h"
#include "CFunction.h"
#include "CSprites.h"

class CAnimationFrame
{
private:
	LPCSPRITE _sprite;
	DWORD _time;

public:
	CAnimationFrame(LPCSPRITE sprite, int time);
	DWORD GetTime();
	LPCSPRITE GetSprite();
	virtual ~CAnimationFrame();
};
typedef CAnimationFrame* LPCANIMATIONFRAME;

class CAnimation
{
public:
	virtual ~CAnimation();
	CAnimation(int defaultTime);
	void Add(int IdSprite, DWORD time = 0);
	//void Update(DWORD deltaTime);
	void Render(float x, float y, int currentFrame, int alpha, bool flipX = false, bool flipY = false, float angle = 0.0f); // angle: tinh bang do (degrees) 
	//void Render(float x, float y, int currentFrame, bool FlipX, float xFlip, bool FlipY, float yFlip);
	bool IsFinishFrame(int idFrame); // Kiem tra id frame co phai frame cuoi
	float GetFrameTime(int idFrame);
	int GetTotalFrame();

private:
	DWORD _frameTime;					// Thoi gian frame
	int _defaultTime;					// Thoi gian mac dinh neu khong set
	//int _currentFrame;					// So thu tu frame hien tai
	//bool _isFinishFrame;				// Kiem tra da hoan thanh 1 frame chua
	vector<LPCANIMATIONFRAME> _frames;	// Danh sach frame
};

typedef CAnimation* LPCANIMATION;

class CAnimations
{
private:
	CAnimations();

public:
	virtual ~CAnimations();

private:

	static CAnimations* _instance;
	unordered_map<int, LPCANIMATION> _animation;

public:
	static CAnimations* GetInstance();
	void LoadAnimationsFromFileXML(LPCWSTR filePath);

	void Add(int id, LPCANIMATION animation);
	LPCANIMATION Get(int id);
	
};

