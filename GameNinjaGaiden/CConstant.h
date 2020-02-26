#pragma once

#include <d3d9.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }

#define		SCREEN_HEIGHT				256//512//256
#define		SCREEN_WIDTH				256//1600//256
#define		WINDOW_CLASS_NAME			L"Sample Window"
#define		WINDOW_TITLE				L"Title Name"
#define		BACKGROUND_COLOR			D3DCOLOR_XRGB(0, 0, 0)
#define		MARIO_TEXTURE_PATH			L"Images/mario.png"	

#define		PATH_XML_TEST				L"XML/test.xml"
#define		TEXTURES_XML_PATH			L"XML/textures.xml"
#define		SPRITES_XML_PATH			L"XML/sprites.xml"
#define		ANIMATIONS_XML_PATH			L"XML/animations.xml"
#define		LISTOBJECT_XML_PATH			L"XML/listobject.xml"
//#define		LISTOBJECT_XML_PATH			L"XML/listobjecttest.xml"
#define		LISTOBJECT_THIRD_XML_PATH			L"XML/listobjectthird.xml"
#define		GRIDMAP_XML_PATH			L"XML/gridmap.xml"
#define		GRIDMAP_THIRD_XML_PATH			L"XML/gridmapthird.xml"
#define		SOUND_XML_PATH			"XML/sound.xml"

#define		PATH_TEXT_MAP				L"map/Map31.txt"
#define		PATH_TIDE_MAP				L"Map/Map31.png"
#define		PATH_XML_MAP				L"XML/map.xml"

//#define		DIRECTINPUT_VERSION			0x0800
#define		KEYBOARD_BUFFER_SIZE		1024

// game
const double PI = 3.14159265f;
const float FRAME_RATE = 30.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations

const float GRAVITY = -0.002f;	// Gia toc Game
const float FRICTION = 0.02f;

const int WIDTH_CELL_GRID = 128;
const int HEIGHT_CELL_GRID = 256;

const int RYU_UNTOUCHABLE_TIME = 1000;
const float RYU_JUMP_SPEED = 0.5f;
const float RYU_RUN_SPEED = 0.15f;
const int RYU_HEALTH = 16;

// Speed object
const float SWORDMAN_SPEED				= 0.05f;
const float CAT_SPEED					= 0.17f;
const float CAT_JUMP					= 0.1f;
const float BANSHEE_SPEED				= 0.05f;
const float MACHINEGUNGUY_SPEED			= 0.05f;
const float DARTS_SPEED					= 0.1f;
const float KNIFEBANSHEE_SPEED			= 0.05f;
const float KNIFEBANSHEE_JUMP			= 0.5f;
const float BULLETMACHINEGUNGUY_SPEED	= 0.1f;
const float DARTSSMALL_SPEED			= 0.1f;
const float BIRDBROWN_SPEED				= 0.05f;
const float BAT_SPEED					= 0.05f;
const float BOSS_SPEED					= 0.2f;
const float BOSS_JUMP					= 0.8f;
const float BULLETBOSS_SPEED			= 0.1f;
const int ENEMI_HEALTH					= 16;

// Kich thuoc va cham cua cac doi tuong
// Ryu
const float RYU_STAND_WIDTH = 18.0f;
const float RYU_STAND_HEIGHT = 32.0f;
 
const float RYU_RUN_WIDTH = 18.0f;
const float RYU_RUN_HEIGHT = 31.0f;

const float RYU_ATTACKING_SWORD_WIDTH = 18.0f;
const float RYU_ATTACKING_SWORD_HEIGHT  = 29.0f;

const float RYU_ATTACKING_STAND_WIDTH = 18.0f;
const float RYU_ATTACKING_STAND_HEIGHT = 29.0f;

const float RYU_SIT_COLLISION_WIDTH = 18.0f;
const float RYU_SIT_COLLISION_HEIGHT = 23.0f;

const float RYU_JUMP_COLLISION_WIDTH = 18.0f;
const float RYU_JUMP_COLLISION_HEIGHT = 16.0f;

const float RYU_STAND_COLLISION_WIDTH = 32.0f;
const float RYU_STAND_COLLISION_HEIGHT = 32.0f;

const float RYU_CLIMB_COLLISION_WIDTH = 18.0f;
const float RYU_CLIMB_COLLISION_HEIGHT = 30.0f;

const float RYU_BEING_ATTACKED_COLLISION_WIDTH = 16.0f;
const float RYU_BEING_ATTACKED_COLLISION_HEIGHT = 22.0f;

// Boss
const float BOSS_COLLISION_WIDTH = 38.0f;
const float BOSS_COLLISION_HEIGHT = 54.0f;

// Enemi
const float BANSHEE_COLLISION_WIDTH = 16.0f;
const float BANSHEE_COLLISION_HEIGHT = 32.0f;

const float BATBROWN_COLLISION_WIDTH = 16.0f;
const float BATBROWN_COLLISION_HEIGHT = 13.0f;

const float BIRDBROWN_COLLISION_WIDTH = 17.0f;
const float BIRDBROWN_COLLISION_HEIGHT = 25.0f;

const float CAT_COLLISION_WIDTH = 31.0f;
const float CAT_COLLISION_HEIGHT = 15.0f;

const float MACHINEGUNGUY_COLLISION_WIDTH = 16.0f;
const float MACHINEGUNGUY_COLLISION_HEIGHT = 32.0f;

const float SWORDMAN_COLLISION_WIDTH = 16.0f;
const float SWORDMAN_COLLISION_HEIGHT = 32.0f;

const float ITEMCONTAINER4_COLLISION_WIDTH = 15.0f;
const float ITEMCONTAINER4_COLLISION_HEIGHT = 15.0f;

const float BONUSBLUE_COLLISION_WIDTH = 15.0f;
const float BONUSBLUE_COLLISION_HEIGHT = 15.0f;

const float BONUSRED_COLLISION_WIDTH = 15.0f;
const float BONUSRED_COLLISION_HEIGHT = 15.0f;

const float FIREWHEEL_COLLISION_WIDTH = 15.0f;
const float FIREWHEEL_COLLISION_HEIGHT = 15.0f;

const float RESTOREPHYSICALSTRENGTH_COLLISION_WIDTH = 15.0f;
const float RESTOREPHYSICALSTRENGTH_COLLISION_HEIGHT = 15.0f;

const float SPIRITUALSTRENGTHBLUE_COLLISION_WIDTH = 15.0f;
const float SPIRITUALSTRENGTHBLUE_COLLISION_HEIGHT = 15.0f;

const float SPIRITUALSTRENGTHRED_COLLISION_WIDTH = 15.0f;
const float SPIRITUALSTRENGTHRED_COLLISION_HEIGHT = 15.0f;

const float THROWINGSTART_COLLISION_WIDTH = 15.0f;
const float THROWINGSTART_COLLISION_HEIGHT = 15.0f;

const float TIMEFREEZE_COLLISION_WIDTH = 15.0f;
const float TIMEFREEZE_COLLISION_HEIGHT = 15.0f;

const float FIRE_COLLISION_WIDTH = 15.0f;
const float FIRE_COLLISION_HEIGHT = 15.0f;

// Weapons
const float SWORD_COLLISION_WIDTH = 21.0f;
const float SWORD_COLLISION_HEIGHT = 15.0f;

const float DARTSRED_COLLISION_WIDTH = 16.0f;
const float DARTSRED_COLLISION_HEIGHT = 16.0f;

const float KNIFEBANSHEE_COLLISION_WIDTH = 8.0f;
const float KNIFEBANSHEE_COLLISION_HEIGHT = 15.0f;

const float BULLETMACHINEGUNGUY_COLLISION_WIDTH = 8.0f;
const float BULLETMACHINEGUNGUY_COLLISION_HEIGHT = 4.0f;

const float DARTSSMALL_COLLISION_WIDTH = 8.0f;
const float DARTSSMALL_COLLISION_HEIGHT = 8.0f;

const float BULLETBOSS_COLLISION_WIDTH = 5.0f;
const float BULLETBOSS_COLLISION_HEIGHT = 5.0f;

//
const float TIME_CUT_ENEMI = 150.0f;

// 
const int NUMBER_MACHINEGUNGUY = 3;

// 
const int TIME_DELAY_JUMP_BOSS = 1000;		// Thoi gian delay de nhay
const int JUMP_DISTANCE_BOSS = 150;			// Khoang cach nhay cua boss

// Thong tin in ra chu trong game
const int POSITON_X_DRAW_BLOCK_TEXT_1 = 10;
const int POSITON_Y_DRAW_BLOCK_TEXT_1 = 10;
const int POSITON_X_DRAW_BLOCK_TEXT_2 = POSITON_X_DRAW_BLOCK_TEXT_1 + 104;
const int POSITON_Y_DRAW_BLOCK_TEXT_2 = POSITON_Y_DRAW_BLOCK_TEXT_1;
const int WIDTH_TEXT = 8;
const int HEIGHT_TEXT = 9;
const int WIDTH_BLOOD = 4;