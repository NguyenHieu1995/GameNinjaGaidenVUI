#include "CGameObjects.h"

CGameObjects* CGameObjects::_instance = NULL;

CGameObjects* CGameObjects::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CGameObjects();
	}

	return _instance;
}

CGameObjects::CGameObjects()
{
}

void CGameObjects::ClearListObject()
{
	for (auto item = _listObject.begin(); item != _listObject.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
			//_listObject.erase(item);
		}
	}
	//_listObject.erase(_listObject.begin(), _listObject.end());
	_listObject.erase(_listObject.begin(), _listObject.end());
	_listObject.clear();
}

CGameObjects::~CGameObjects()
{
	for (auto item = _listObject.begin(); item != _listObject.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_listObject.clear();
	//_listObject.erase(_listObject.begin(), _listObject.end());
}

bool CGameObjects::LoadFromFile(LPCWSTR filePath)
{
	ClearListObject();

	_bstr_t path(filePath);
	TiXmlDocument doc(path);

	if (!doc.LoadFile())
	{
		DebugOut(L"[ERROR] Load file XML Object that bai! Loi: %s\n", doc.ErrorDesc());
		return false;
	}

	DebugOut(L"[INFO] Duong dan file XML Object: %s\n", filePath);

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* object = nullptr;
	int id;		// ID cua object
	int type;	// Loai object
	int x, y;	// Vi tri object
	int w, h;	// Size of object
	int d;		// Huong di chuyen cua object

	for (object = root->FirstChildElement(); object != NULL; object = object->NextSiblingElement())
	{
		object->QueryIntAttribute("id", &id);
		object->QueryIntAttribute("type", &type);
		object->QueryIntAttribute("x", &x);
		object->QueryIntAttribute("y", &y);
		object->QueryIntAttribute("d", &d);
		object->QueryIntAttribute("w", &w);
		object->QueryIntAttribute("h", &h);		

		this->_listObject[id] = CreateObject(type, id, x, y, d, w, h);
		DebugOut(L"[SUCCESS] Load object success: %d\n", id);
	}

	DebugOut(L"[SUCCESS] Load all list object success");

	return true;
}

LPCGAMEOBJECT CGameObjects::CreateObject(int type, int id, int x, int y, int d, int w, int h)
{
	LPCGAMEOBJECT object = NULL;
	
	switch (type)
	{
	case eObjectType::RYU:
		object = new CGameObjectRyu(id, x, y);
		break;

	case eObjectType::BANSHEE:
		object = new CGameObjectBanshee(id, x, y, d);
		break;

	case eObjectType::BATBROWN:
		object = new CGameObjectBatBrown(id, x, y, d);
		break;

	case eObjectType::BIRDBROWN:
		object = new CGameObjectBirdBrown(id, x, y, d);
		break;

	case eObjectType::CAT:
		object = new CGameObjectCat(id, x, y, d);
		break;

	case eObjectType::MACHINEGUNGUY:
		object = new CGameObjectMachineGunGuy(id, x, y, d);
		break;

	case eObjectType::SWORDMAN:
		object = new CGameObjectSwordMan(id, x, y, d);
		break;

	case eObjectType::GROUND:
		object = new CGameObjectGround(id, x, y, w, h);
		break;

	case eObjectType::BONUSRED:
		object = new CBonusRed(id, x, y);
		break;

	case eObjectType::BONUSBLUE:
		object = new CBonusBlue(id, x, y);
		break;

	case eObjectType::FIREWHEEL:
		object = new CFireWheel(id, x, y);
		break;

	case eObjectType::RESTOREPHYSICALSTRENGTH:
		object = new CRestorePhysicalStrength(id, x, y);
		break;

	case eObjectType::SPIRITUALSTRENGTHBLUE:
		object = new CSpiritualStrengthBlue(id, x, y);
		break;

	case eObjectType::SPIRITUALSTRENGTHRED:
		object = new CSpiritualStrengthRed(id, x, y);
		break;

	case eObjectType::THROWINGSTAR:
		object = new CThrowingStart(id, x, y);
		break;

	case eObjectType::TIMEFREEZE:
		object = new CTimeFreeze(id, x, y);
		break;

	case eObjectType::ITEMCONTAINER4:
		object = new CItemContainer4(id, x, y);
		break;

	case eObjectType::BOSS:
		object = new CGameObjectBoss(id, x, y, d);
		break;

	case eObjectType::BULLETMACHINEGUNGUY:
		object = new CBulletMachineGunGuy(id, x, y);
		break;

	case eObjectType::BULLETBOSS:
		object = new CBulletBoss(id, x, y);
		break;

	case eObjectType::KNIFEBANSHEE:
		object = new CKnifeBanshee(id, x, y);
		break;

	case eObjectType::WALL:
		object = new CGameObjectWall(id, x, y, w, h);
		break;

	case eObjectType::FIRE:
		object = new CFire(id, x, y);
		break;

	case eObjectType::FIREBULLET:
		object = new CFirebullet(id, x, y);
		break;

	default: 
		break;
	}

	return object;
}

unordered_map<int, LPCGAMEOBJECT> CGameObjects::GetListObject()
{
	return _listObject;
}

LPCGAMEOBJECT CGameObjects::GetObjectByID(int id)
{
	return _listObject[id];
}

bool CGameObjects::AddObject(LPCGAMEOBJECT object)
{
	this->_listObject[object->GetID()] = object;
	return true;
}

void CGameObjects::RemoveObject(int id)
{
	delete this->_listObject[id];
	this->_listObject.erase(id);
}