#include "CSprites.h"
#include "CDirectX.h"
#include "CDebug.h"
#include "Tiny/tinyxml.h"
#include "CFunction.h"


// Class Sprite (Object Sprite)
CSprite::CSprite(int id, RECT rect, LPDIRECT3DTEXTURE9 texture, float xf, float yf)
{
	this->_id = id;
	this->_rect = rect;
	this->_texture = texture;
	this->_xFlip = xf;
	this->_yFlip = yf;
}

CSprite::~CSprite()
{
	if (this->_texture != NULL)
	{
		this->_texture->Release();
		this->_texture = NULL;
	}
}

void CSprite::Draw(float x, float y, int alpha, bool FlipX, bool FlipY, float angle)
{
	CDirectX::GetInstance()->DrawSprite(x, y, this->_texture, this->_rect, alpha, 1.0f, FlipX, _xFlip, FlipY, _yFlip, angle);
}

//void CSprite::Draw(float x, float y, bool FlipX, float xFlip, bool FlipY, float yFlip)
//{
//	CDirectX::GetInstance()->DrawSprite(x, y, this->_texture, this->_rect, 1.0f, FlipX, xFlip, FlipY, yFlip);
//}

// Clas Sprites -> Class management all sprite
CSprites* CSprites::_instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CSprites();
	}

	return _instance;
}

LPCSPRITE CSprites::Get(unsigned int id)
{
	return _sprites[id];
}

void CSprites::Add(int id, RECT rect, LPDIRECT3DTEXTURE9 texture, float xf, float yf)
{
	LPCSPRITE sprite = new CSprite(id, rect, texture, xf, yf);
	this->_sprites[id] = sprite;
}

void CSprites::LoadSpritesFromFileXML(LPCWSTR filePath)
{
	_bstr_t path(filePath);
	TiXmlDocument doc(path);

	if (!doc.LoadFile())
	{
		DebugOut(L"[ERROR] Load file XML Sprites that bai! Loi: %s\n", doc.ErrorDesc());
		return;
	}

	//DebugOut(L"[INFO] Duong dan file XML SPrites: %s\n", filePath);

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* sprite = nullptr;
	int id, idTexture;
	int x, y, w, h;
	float xf, yf;
	RECT rect;

	for (sprite = root->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
	{
		sprite->QueryIntAttribute("id", &id);
		sprite->QueryIntAttribute("idTexture", &idTexture);
		sprite->QueryIntAttribute("x", &x);
		sprite->QueryIntAttribute("y", &y);
		sprite->QueryIntAttribute("w", &w);
		sprite->QueryIntAttribute("h", &h);
		sprite->QueryFloatAttribute("xf", &xf);
		sprite->QueryFloatAttribute("yf", &yf);

		rect.left = x;
		rect.top = y;
		rect.right = x + w;
		rect.bottom = y + h;

		//DebugOut(L"Rect: %d %d %d %d \n", rect.left, rect.top, rect.right, rect.bottom);


		this->Add(id, rect, CTextures::GetInstance()->Get(idTexture), xf, yf);

		//DebugOut(L"[INFO] Add Sprite: %d\n", id);
	}

	//DebugOut(L"[SUCCESS] Load all Texture success");
	
}

CSprites::~CSprites()
{
	for (auto item = _sprites.begin(); item != _sprites.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_sprites.clear();
}