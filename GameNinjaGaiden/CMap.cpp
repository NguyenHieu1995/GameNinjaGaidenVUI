#include "CMap.h"
#include "Tiny/tinyxml.h"
#include "CFunction.h"

//=====================================================================
// Object Map
//=====================================================================
CMap::CMap(int id, LPCWSTR fileText, LPDIRECT3DTEXTURE9 texture)
{
	_iID = id;

	_iHeight = 0;
	_iWidth = 0;
	_iRow = 0;
	_iColumn = 0;
	_matrixMap = NULL;

	_pTexture = NULL;
	LoadMap(fileText, texture);
}

CMap::~CMap()
{
	//this->_pTexture->Release();
	if (this->_pTexture != NULL)
	{
		//this->_pTexture = NULL;
		//this->_pTexture->Release();
		this->_pTexture = NULL;
	}

	if (_matrixMap != NULL)
	{
		for (int i = 0; i < _iRow; ++i)
		{
			delete[] _matrixMap[i];
			_matrixMap[i] = NULL;
		}
		delete[] _matrixMap;
		_matrixMap = NULL;
	}
}

bool CMap::LoadMap(LPCWSTR fileText, LPDIRECT3DTEXTURE9 texture)
{
	ifstream in;

	in.open(fileText);

	int item;

	if (in.is_open())
	{
		in >> _iWidth;
		in >> _iHeight;
		in >> _iRow;
		in >> _iColumn;

		if (_matrixMap == NULL)
		{
			this->_matrixMap = new int* [_iRow];
			for (int i = 0; i < _iRow; i++)
			{
				_matrixMap[i] = new int[_iColumn];
				for (int j = 0; j < _iColumn; j++)
				{
					in >> item;
					_matrixMap[i][j] = item;
				}
			}
		}
		in.close();

		_pTexture = texture;

		return true;
	}
	else
	{
		return false;
	}
}

//
void CMap::Render()
{
	RECT testRect;

	for (int i = 0; i < _iRow; i++)
	{
		for (int j = 0; j < _iColumn; j++)
		{
			testRect.top = 0;
			testRect.left = _matrixMap[i][j] * 16;
			testRect.right = _matrixMap[i][j] * 16 + 16;
			testRect.bottom = 16;

			CDirectX::GetInstance()->DrawSprite((float)j * 16, float(((_iRow - 1) * 16) - (i * 16)), this->_pTexture, testRect, 255);
		}
	}
}

//=====================================================================
// Database Map
//=====================================================================
CMaps* CMaps::_instance = NULL;

CMaps* CMaps::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CMaps();
	}

	return _instance;
}

CMaps::CMaps()
{

}

CMaps::~CMaps()
{
	for (auto item = _maps.begin(); item != _maps.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_maps.clear();
}

bool CMaps::LoadFileXML(LPCWSTR filePath)
{
	_bstr_t path(filePath);
	TiXmlDocument doc(path);

	if (!doc.LoadFile())
	{
		DebugOut(L"[ERROR] Load file XML Sprites that bai! Loi: %s\n", doc.ErrorDesc());
		return false;
	}

	//DebugOut(L"[INFO] Duong dan file XML SPrites: %s\n", filePath);

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* map = nullptr;
	int id;
	LPCWSTR pathText;
	int idTexture;

	for (map = root->FirstChildElement(); map != NULL; map = map->NextSiblingElement())
	{
		map->QueryIntAttribute("id", &id);
		pathText = GetWC(map->Attribute("text"));
		map->QueryIntAttribute("idTexture", &idTexture);

		this->Add(id, pathText, CTextures::GetInstance()->Get(idTexture));
	}

	//DebugOut(L"[SUCCESS] Load all Texture success");

	return true;
}

LPCMAP CMaps::Get(unsigned int id)
{
	return _maps[id];
}

void CMaps::Add(int id, LPCWSTR fileText, LPDIRECT3DTEXTURE9 texture)
{
	LPCMAP map = new CMap(id, fileText, texture);
	_maps[id] = map;
}