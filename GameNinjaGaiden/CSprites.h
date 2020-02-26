#pragma once

// Object Sprite
#include <d3dx9.h>
#include <unordered_map>
#include <Windows.h>
#include <comdef.h>
#include <d3d9.h>
#include "CTextures.h"

using namespace std;

class CSprite
{
public:
	CSprite(int id, RECT rect, LPDIRECT3DTEXTURE9 texture, float xf = 1.0f, float yf = 1.0f);
	virtual ~CSprite();

private:
	int _id;
	RECT _rect;
	LPDIRECT3DTEXTURE9 _texture;
	float _xFlip, _yFlip;			// Vi tri lat hinh (Gia tri tu 0 -> 1)

public:
	void Draw(float x, float y, int alpha, bool FlipX = false, bool FlipY = false, float angle = 0.0f); // Draw Sprite
	//void Draw(float x, float y, bool FlipX, bool FlipY);
};

typedef CSprite* LPCSPRITE;

// Class management all Sprite of Game
class CSprites
{
private:
	static CSprites* _instance;
	
	// database sprite of game
	unordered_map<int, LPCSPRITE> _sprites;
	void Add(int id, RECT rect, LPDIRECT3DTEXTURE9 texture, float xf, float yf);

public:
	virtual ~CSprites();
	LPCSPRITE Get(unsigned int id);

	static CSprites* GetInstance();
	void LoadSpritesFromFileXML(LPCWSTR filePath);
};