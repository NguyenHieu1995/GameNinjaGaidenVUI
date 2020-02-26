#pragma once
#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <comdef.h>


using namespace std;

// Class management all texture of Game

class CTextures
{
private:
	static CTextures *_instance;

	// Database texture of Game
	unordered_map<int, LPDIRECT3DTEXTURE9> _textures;
	CTextures();

	// Add texture to list Management textures
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);

public:
	virtual ~CTextures();

	void LoadTexturesFromFileXML(LPCWSTR filePath);
	// Get Texture by id
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	// 
	static CTextures* GetInstance();

};
