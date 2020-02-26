#pragma once

enum eActionObject {
	STAND,
	SIT,
	JUMP,
	CLIMB,
	RUNOJBECT
};

// Enum of object Ryu
enum eStateRyu {
	STAND_STATE = 0,					// RIGHT: Dung yen
	ATTACKING_SWORD_STATE,				// Tan cong bang kiem
	ATTACKING_STAND_STATE,				// Tan cong khong dung kiem
	ATTACKING_STAND_DARTSSMALL_STATE,	// Tan cong su dung phi tieu nho
	CLIMGING_TO_WALL_STATE,				// Bam tren tuong
	CLIMBING_WALL_STATE,				// Dang leo tuong
	RUNNING_STATE,						// Dang chay
	SITTING_STATE,						// Dang ngoi
	ATTACKING_SITTING_STATE,			// Ngoi tan cong
	JUMPING_STATE,						// Dang nhay
	ATTACKING_JUMPING_STATE,			// Tan cong khi dang nhay
	BEING_ATTACKED_STATE,				// Bi tan cong
	//STAND_STATE_LEFT,					// LEFT: Dung yen
	//ATTACKING_SWORD_STATE_LEFT,			// Tan cong bang kiem
	//ATTACKING_STAND_STATE_LEFT,			// Tan cong khong dung kiem
	//CLIMGING_TO_WALL_STATE_LEFT,		// Bam tren tuong
	//CLIMBING_WALL_STATE_LEFT,			// Dang leo tuong
	//RUNNING_STATE_LEFT,					// Dang chay
	//SITTING_STATE_LEFT,					// Dang ngoi
	//ATTACKING_SITTING_STATE_LEFT,		// Ngoi tan cong
	//JUMPING_STATE_LEFT,					// Dang nhay
	//ATTACKING_JUMPING_STATE_LEFT,		// Tan cong khi dang nhay
};

enum eStateCat {
	DIE = 0,
	RUN
};

enum eStateDarts {
	HIDEDARTS = 0,
	SHOWDARTS
};

enum eStateFireBullet {
	HIDEFIREBULLET = 0,
	SHOWFIREBULLET
};

enum eStateDartsSmall {
	HIDEDARTSSMALL = 0,
	SHOWDARTSSMALL
};

enum eStateSword {
	HIDESWORD = 0,
	SHOWSWORD
};

enum eStateSwordMan {
	DIESWORDMAN = 0,
	RUNSWORDMAN
};

enum eStateBanshee {
	DIEBANSHEE = 0,
	RUNBANSHEE,
	ATTACKBANSHEE
};

enum eStateKnifeBanshee {
	HIDEKNIFEBANSHEE = 0,
	SHOWKNIFEBANSHEE
};

enum eStateMachineGunGuy
{
	DIEMACHINEGUNGUY = 0,
	RUNMACHINEGUNGUY,
	ATTACKMACHINEGUNGUY
};

enum eStateBulletMachineGunGuy {
	HIDEBULLETMACHINEGUNGUY = 0,
	SHOWBULLETMACHINEGUNGUY
};

enum eStateBirdBrown {
	DIEBIRDBROWN,
	FLYBIRDBROWN
};

enum eStateBat {
	DIEBAT,
	FLYBAT
};

enum eStateBoss {
	STANDBOSS,
	ATTACKBOSS,
	JUMPBOSS,
	DIEBOSS
};

enum eStateBulletBoss {
	HIDEBULLETBOSS,
	SHOWBULLETBOSS
};

enum eStateItem {
	HIDEITEM,
	SHOWITEM,
	DISAPPEARITEM
};