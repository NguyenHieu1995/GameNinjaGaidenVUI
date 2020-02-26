#include "CTextures.h"

#include "CDebug.h"
#include "CDirectX.h"
#include "Tiny/tinyxml.h"
#include "CFunction.h"

CTextures * CTextures::_instance = NULL;

CTextures::CTextures()
{
}

CTextures::~CTextures()
{
	//HRESULT hr;

	for (auto item = _textures.begin(); item != _textures.end(); ++item)
	{
		//DebugOut(L"[ERROR] Realse Failed! 0x%", &item->second);

		if (item->second != NULL)
		{
			item->second->Release();
			item->second = NULL;
		}
	}
	/*unordered_map<int, LPDIRECT3DTEXTURE9>::iterator item;
	for ( item = _textures.begin(); item != _textures.end();)
	{
		(item->second)->Release();
		item = _textures.erase(item);
	}*/

	_textures.clear();
}

CTextures *CTextures::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CTextures();
	}

	return _instance;
}

LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i)
{
	return _textures[i];
}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
	}

	LPDIRECT3DDEVICE9 d3ddv = CDirectX::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	_textures[id] = texture;
	texture = NULL;

	//DebugOut(L"[INFO] Texture loaded OK: id=%d, %s \n", id, filePath);
}

void CTextures::LoadTexturesFromFileXML(LPCWSTR filePath)
{
	_bstr_t path(filePath);
	TiXmlDocument doc(path);

	if (!doc.LoadFile())
	{
		//printf("%s", doc.ErrorDesc);
		DebugOut(L"[ERROR] Load file XML Texture that bai! Loi: %s\n", doc.ErrorDesc());
		return;
	}

	//DebugOut(L"[INFO] Duong dan file XML Textures: %s\n", filePath);

	// Element ROOT
	TiXmlElement* root = doc.RootElement();

	TiXmlElement* texture = nullptr;
	int id;
	LPCWSTR pathTexture;
	int red, green, blue;

	for (texture = root->FirstChildElement(); texture != NULL; texture = texture->NextSiblingElement())
	{
		texture->QueryIntAttribute("id", &id);
		pathTexture = GetWC(texture->Attribute("path"));

		texture->QueryIntAttribute("red", &red);
		texture->QueryIntAttribute("green", &green);
		texture->QueryIntAttribute("blue", &blue);


		this->Add(id, pathTexture, D3DCOLOR_XRGB(red, green, blue));

		delete[] pathTexture;
		//DebugOut(L"[INFO]Add Texture: %d\n", id);
	}

	//DebugOut(L"[SUCCESS] Load all Texture success");
}