#pragma once
#include "Vectors.h"

typedef char pad;
typedef float vec2[2];
typedef float vec3[3];


/*
#define OFFSET_GENTITY_BASE 0x21EF7C0  
#define OFFSET_GENTITY_SIZE 0x31C
#define VIEW_MATRIX 0x03441F80
#define OFFSET_ZOOM 0x0234BD98
*/

#define MAX_ENTITIES 1024
#define MAX_CLIENTS 18
#define OFFSET_GENTITY_BASE 0x21EF7C0  
#define OFFSET_GENTITY_SIZE 0x31C
#define VIEW_MATRIX 0x03B26880
#define OFFSET_ZOOM 0x0234BD98

#define OFFSET_CG_SIZE 0x5C8
#define OFFSET_CG_BASE 0x3BDE8C80
#pragma region Enums

enum eTeam
{
	TEAM_FREE,
	TEAM_ALLIES,
	TEAM_AXIS,
	TEAM_THREE,
	TEAM_FOUR,
	TEAM_FIVE,
	TEAM_SIX,
	TEAM_SEVEN,
	TEAM_EIGHT,
	TEAM_SPECTATOR,
	TEAM_MAX
};

enum WeaponID : __int32 {
	none = 0,
	defaultweapon = 1,
	mp7 = 2,
	pdw57 = 4,
	vector = 6,
	msmc = 8,
	chicom = 10,
	skorpion = 12,
	peacekeeper = 14,
	mtar = 16,
	type = 20,
	swat = 24,
	fal = 28,
	m27 = 32,
	scar = 36,
	smr = 40,
	m8a1 = 44,
	an94 = 48,
	remington = 52,
	s12 = 53,
	ksg = 54,
	m1216 = 55,
	mk48 = 56,
	qbblsw = 58,
	lsat = 60,
	hamr = 62,
	svu = 64,
	dsr50 = 65,
	ballista = 66,
	xpr = 67,
	fiveseven = 78,
	tac45 = 79,
	b23r = 80,
	executioner = 81,
	kap = 82,
	smaw = 84,
	stinger = 85,
	rpg = 86,
	riot = 89,
	crossbow = 90,
};

enum EntityType : unsigned short {
	GENERAL,
	PLAYER,
	PLAYER_CORPSE,
	ITEM,
	MISSILE,
	INVISIBLE,
	SCRIPTMOVIER,
	SOUND_BLEND,
	FX,
	LOOP_FX,
	PRIMARY_LIGHT,
	TURRET,
	HELICOPTER,
	PLANE,
	VEHICLE,
	VEHICLE_CORPSE,
	ZOMBIE,
	ZOMBIE_SPAWNER,
	ZOMBIE_CORPSE,
	STREAMER_HINT,
	ZBARRIER,
};

enum ePenetrateType
{
	PENETRATE_TYPE_NONE,
	PENETRATE_TYPE_SMALL,
	PENETRATE_TYPE_MEDIUM,
	PENETRATE_TYPE_LARGE,
	PENETRATE_TYPE_MAX
};
enum eWeaponType
{
	WEAPTYPE_BULLET,
	WEAPTYPE_GRENADE,
	WEAPTYPE_PROJECTILE,
	WEAPTYPE_BINOCULARS,
	WEAPTYPE_GAS,
	WEAPTYPE_BOMB,
	WEAPTYPE_MINE,
	WEAPTYPE_MELEE,
	WEAPTYPE_RIOTSHIELD,
	WEAPTYPE_MAX
};

namespace Offsets {
struct sSnapShot
{
private:
	char _0x0[0x8];
public:
	int iServerTime;
private:
	char _0xC[0xC];
public:
	int iPing;
};

struct sPlayerState
{
public:
	int iServerTime;
private:
	char _0x4[0x14];
public:
	int iOtherFlags;
private:
	char _0x1C[0xC];
public:
	vec3 vOrigin;
	vec3 vVelocity;
private:
	char _0x40[0xC];
public:
	float flWeaponTime;
	int iWeaponDelay;
private:
	char _0x54[0x30];
public:
	int iThirdPerson;
private:
	char _0x88[0x4];
public:
	int iGravity;
private:
	char _0x90[0x4];
public:
	int iSpeed;
	vec3 vDeltaAngles;
private:
	char _0xA4[0x12C];
public:
	int iWeaponState[2];
private:
	char _0x1D8[0x8];
public:
	float flZoomProgress;
private:
	char _0x1E4[0x4];
public:
	float flSpreadOverride;
	int iSpreadOverrideState;
private:
	char _0x1F0[0x8];
public:
	vec3 vViewAngles;
	int iPlayerHeight;
	vec3 vPlayerHeight;
private:
	char _0x214[0x18];
public:
	int iDamageYaw;
	int iDamagePitch;
	int iDamageCount;
private:
	char _0x238[0x8];
public:
	int iHealth;
private:
	char _0x244[0x4];
public:
	int iMaxHealth;
private:
	char _0x24C[0x74];
public:
	int iSecondaryWeaponID;
private:
	char _0x2C4[0x18];
public:
	int iPrimaryWeaponID;
private:
	char _0x2E0[0x124];
public:
	int iSecondaryAmmoStock;
	int iPrimaryAmmoStock;
private:
	char _0x40C[0x34];
public:
	int iSecondaryAmmoClip;
	int iPrimaryAmmoClip;
	int iLethalAmmo;
	int iTacticalAmmo;
private:
	char _0x450[0x5C];
public:
	int iSatalliteTypeEnabled;
private:
	char _0x4B0[0xA0];
public:
	int iPerkFlags;
};


struct sRefDef
{
public:
	int iX;
	int iY;
	int iWidth;
	int iHeight;
private:
	char _0x10[0x10];
public:
	float flFovX;
	float flFovY;
private:
	char _0x28[0x8];
public:
	float flFov;
	vec3 vViewOrigin;
private:
	char _0x40[0x4];
public:
	vec3 vViewAxis[3];
private:
	char _0x68[0x16D18];
public:
	int iSplitScreenBlurEdges;
	int iPlayerTeleported;
private:
	char _0x16D88[0x2D8];
};


struct sWeaponDef
{
private:
	char _0x0[0x1C];
public:
	eWeaponType iWeaponType;
private:
	char _0x20[0x4];
public:
	ePenetrateType iPenetrateType;
private:
	char _0x28[0x609];
public:
	bool bRifleBullet;
private:
	char _0x632[0x1AE];
public:
	float flADSSpread;
};

struct sModelMask
{
public:
	int iSlot;
	sWeaponDef* WeaponDef;
private:
	char _0x8[0x8];
};

struct sClientInfo
{
public:
	int iInfoValid;
	int iNextValid;
	int iClientNum;
	char szName[32];
	eTeam iTeam1;
	eTeam iTeam2;
	int iFFATeam;
private:
	char _0x38[0x28];
public:
	int iRank;
private:
	char _0x64[0x14];
public:
	unsigned __int64 qwXuid;
	char szClan[8];
private:
	char _0x88[0x7];
public:
	bool bDead;
private:
	char _0x90[0x4];
public:
	int iScore;
private:
	char _0x98[0x58];
public:
	char szPlayerModel[32];
private:
	char _0x110[0x3B4];
public:
	vec3 vViewAngles;
private:
	char _0x4D0[0xF4];
public:
	int iWeaponID;
private:
	char _0x5C8[0x1BC];
public:
	sModelMask ModelMask[8];
	int iOffHandWeaponID;
};

struct sCG
{
public:
	int iClientNum;
private:
	char _0x4[0x20];
public:
	sSnapShot* OldSnapShot;
	sSnapShot* NewSnapShot;
private:
	char _0x2C[0x58];
public:
	int iPing;
	int iServerTime;
	int iPhysicsTime;
	int iCommandTime;
private:
	char _0x94[0x24];
public:
	vec3 vOrigin;
	vec3 vVelocity;
private:
	char _0xD0[0x10];
public:
	int iWeaponDelay;
private:
	char _0xE4[0x78];
public:
	int iMoveType;
private:
	char _0x160[0x2C];
public:
	int iMoveFlag;
private:
	char _0x190[0xB8];
public:
	int iWeaponID;
private:
	char _0x24C[0x14];
public:
	int iWeaponState[2];
private:
	char _0x268[0x8];
public:
	float flZoomProgress;
private:
	char _0x274[0x54];
public:
	int iHealth;
private:
	char _0x2CC[0x47DB8];
public:
	float flFrameInterpolation;
	int iFrameTime;
	int iTime;
	int iOldTime;
private:
	char _0x48094[0x8];
public:
	int iThirdPerson;
private:
	char _0x480A0[0x8];
public:
	sPlayerState PlayerState;
private:
	char _0x485FC[0x5294];
public:
	sRefDef RefDef;
	vec3 vRefDefViewAngles;
private:
	char _0x648FC[0x130];
public:
	vec3 vWeaponAngles;
private:
	char _0x64A38[0x3890];
public:
	float flZoomSensitivity;
private:
	char _0x682CC[0x68C];
public:
	int iMatchUIVisibilityFlags;
private:
	char _0x6895C[0xD18];
public:
	int iWeaponSelect;
private:
	char _0x69678[0x54];
public:
	int iEquippedOffhand;
private:
	char _0x696D0[0xF8];
public:
	vec3 vKickAngles;
	vec3 vOffsetAngles;
	float flGunPitch;
	float flGunYaw;
private:
	char _0x697E8[0xB4];
public:
	float flShockSensitivity;
private:
	char _0x698A0[0x1C0];
public:
	sClientInfo ClientInfo[MAX_CLIENTS];
private:
	char _0x72AF0[0xE04C];
public:
	int iExtraButtonBits[2];
private:
	char _0x80B44[0x8];
public:
	int iPlayerTeleported;
private:
	char _0x80B50[0xC];
public:
	float flSpread;
private:
	char _0x80B60[0x6BD0];
public:
	char szGameType[4];
private:
	char _0x87734[0x1D90C];
public:
	//sCEntity CEntity[MAX_ENTITIES];
};

struct sTrajectory
{
public:
	int iType;
	int iTime;
	int iDuration;
	vec3 vBase;
	vec3 vDelta;
};

struct sLerpEntityState
{
public:
	int eFlags1;
	int eFlags2;
	sTrajectory PositionTrajectory;
	sTrajectory AngleTrajectory;
private:
	char _0x50[0xC];
public:
	int iWeaponID1;
	int iWeaponID2;
private:
	char _0x64[0x18];
};

struct sEntityState
{
public:
	int iEntityNum;
	sLerpEntityState LerpEntityState;
private:
	char _0x80[0x58];
public:
	short wEntityType;
	short wGroundEntityNum;
private:
	char _0xDA[0x2];
public:
	short wOtherEntityNum;
	short wAttackerEntityNum;
private:
	char _0xE2[0x2];
public:
	int iWeaponID;
private:
	char _0xE8[0x10];
};
struct sCEntity
{
private:
	char _0x0[0x2];
public:
	short wValid;
	short wUsedForPlayerMesh;
private:
	char _0x6[0x26];
public:
	vec3 vOrigin;
	vec3 vViewAngles;
private:
	char _0x44[0x11C];
public:
	sLerpEntityState CurrentEntityState;
	sEntityState NextEntityState;
private:
	char _0x2D4[0xA4];
public:
	int iAlive;
private:
	char _0x37C[0x4];
};


enum EntityFlags : unsigned __int32 {
	STANDING = 2,
	CROUCH = 6,
	PRONE = 10,
	BARRIER = 237,
	ZM = 67110914,
};

enum TeamType : __int32 {
	FRIEND = 1,
};

enum PerkFlags : __int32 {
	//0x10 = Reduced Spread, 0x80000 = Faster Knife
	A = 1 << 0, // binary 0001
	B = 1 << 1, // binary 0010
	C = 1 << 2, // binary 0100
	D = 1 << 3, // binary 1000
};

#pragma endregion





	//Screen
	

#pragma pack(push,1)
	struct Ammo { // This is not in order FIX IT!
		__int32 Wep3;			// 0x00 -> 2342BC8
		__int32 Wep1; 			// 0x04 -> 2342BCC
		__int32 WepGrenadeLthl; // 0x08 -> 2342BD0
		__int32 Wep2; 			// 0x0C -> 2342BD4
		__int32 Wep1Akimbo;		// 0x10 -> 2342BD8
		__int32 WepGrenadeTtcl; // 0x14 -> 2342BDC
		__int32 Wep2Akimbo; 	// 0x18 -> 2342BE0
	};

	// this is PlayerActor_t!!!
	struct PlayerInfo {
		vec3 Position;			// 0x00 -> 23427C8 // Position (x,y,z)
		vec3 Velocity;			// 0x0C -> 23427D4 // Velocity (x,y,z)
		char pad_0x84[0x84];	// 23427E0;
		float LastJump;			// 2342864 // Height where standing on last jump
		char pad_0x118[0x118];
		float ADS;				// 2342980 // % (0.00 to 1.00) of how much ADS
		char pad_0x14[0x14];
		vec2 Angle;				// 2342998 // x(-85up 85down) y(-180 180)
		char pad_0x53D0[0x53C8];
		__int32 Money;			// 2347D68
		__int32 Kills2;			// 2347D6C
		char pad_0x10[0x10];
		__int32 Kills;			// 2347D80
		__int32 Downs;			// 2347D84
		__int32 Revives;		// 2347D88
		__int32 Headshots;		// 2347D8C
		char pad_0x4[0x4];
		__int32 __8;			// Revives???
	};

	struct PlayerInfo_t {
		__int32 ServerTime;		// 0x0000 -> 23427A0
		pad _0x0004[0x24];		// 0x0004
		vec3 Position;			// 0x0028 -> 23427C8 // Position (x,y,z)
		vec3 Velocity;			// 0x0034 -> 23427D4 // Velocity (x,y,z)
		pad _0x0040[0x4C];		// 0x0040
		__int32 Gravity;		// 0x008C -> 234282C
		pad _0x0090[0x4];		// 0x0090
		__int32 Speed;			// 0x0094 -> 2342834
		pad _0x0098[0x2C];		// 0x0098
		float LastJump;			// 0x00C4 -> 2342864 // Height where standing on last jump
		pad _0x00C8[0x118];		// 0x00C8
		float ADS;				// 0x01E4 -> 2342980 // % (0.00 to 1.00) of how much ADS
		pad _0x01E8[0x14];		// 0x01E8
		vector2 Angle;				// 0x01FC -> 2342998 // x(-85up 85down) y(-180 180)
		pad _0x0200[0x04];		// 0x0200
		__int32 HeightInt;		// 0x0204 -> 23429A4
		float HeightFloat;		// 0x0208 
		pad _0x020C[0x2C];		// 0x020C
		__int32 Health;			// 0x0238 -> 23429D8 // Read only
		pad _0x023C[0x4];		// 0x023C
		__int32 MaxHealth;		// 0x0240 // xd doesn't work
		pad _0x0244[0x04];		// 0x0244
		__int32 Weapon2ID;		// 0x0248 -> 23429E8
		pad _0x024C[0x18];		// 0x024C -> 23429EC
		__int32 Weapon1ID;		// 0x0264 -> 2342A04
		pad _0x0268[0x18];		// 0x0268 -> 2342A08
		__int32 LethalID;		// 0x0280 -> 2342A20
		char _0x0284[0x18];		// 0x0284 -> 2342A24
		__int32 TacticalID;	// 0x02B8 -> 2342A3C
		char _0x02BC[0x14C];	// 0x02BC -> 2342A40
		__int32 Weapon1Stock;	// 0x03F0 -> 2342B8C
		char _0x03F4[0x4];		// 0x03F4
		__int32 Weapon2Stock;	// 0x03F8 
		char _0x03FC[0x30];		// 0x03FC
		__int32 Weapon1Clip;	// 0x042C -> 2342BC8
		pad fuk[0x4];			// 0x042C
		__int32 LethalAmmo;		// 0x0430 -> 2342BD0
		__int32 Weapon2Clip;	// 0x0434 
		__int32 TacticalAmmo;	// 0x0438 
		char _0x043C[0x110];	// 0x043C
		__int32 PerkFlags;		// 0x054C // 0x10 = Reduced Spread, 0x80000 = Faster Knife
		char _0x0550[0x4F5C];	// 0x0550
		char NameReadOnly[32];	// 0x54AC -> 2347C4C // Readonly 
		char _0x54BC[0x20];		// 0x54BC
		pad fuckinghell[0x48];
		char Name[32];			// 0x5534 -> 2347CD4 // Writable (Null terminate plz)
		char _0x5544[0x74];		// 0x5544
		__int32 Score;			// 0x55C8 -> 2347D68
		__int32 Kills1;			// 0x55CC -> 2347D6C
		pad _0x55D0[0x10];		// 0x55D0 -> 2347D70
		__int32 Kills;			// 0x55E0 -> 2347D80
		__int32 Downs;			// 0x55E4 -> 2347D84
		__int32 Revives;		// 0x55E8 -> 2347D88
		__int32 Headshots;		// 0x55EC -> 2347D8C
		pad _0x55F0[0x08];		// 0x55F0 -> 2347D90
		__int32 Headshots1;		// 0x55F8 -> 2347D98
		pad _0x55FC[0x28];		// 0x55FC -> 2347D9C
		__int32 Kills2;			// 0x5620 -> 2347DC0
		pad _0x5624[0x38];		// 0x5624 -> 2347DC4
		__int32 Headshots2;		// 0x565C -> 2347DFC
	}; // Size 0x045C ???

	struct TeamInfo_t {
		char _0x0000[4];	// 0x0000
		__int32 Team;	// 0x0004 // TeamType
		char _0x0008[56];	// 0x0008

	}; // Size 0x0040

	struct gentity_t {
		__int32 ClientNum;			// 0x0000
		EntityFlags Flags;			// 0x0004 // EntityFlags
		char _0x0008[16];			// 0x0008
		vec3 Position;				// 0x0018 // Position
		char _0x0024[24];			// 0x0024
		vector2 Angles;				// 0x003C // Angles x(-85up 85down) y(-180 180)
		char _0x0044[28];			// 0x0044
		__int32 HeldWeapon;			// 0x0060 // Weapon they're currently using
		char _0x0064[116];			// 0x0064
		EntityType Type;			// 0x00D8
		char _0x00DA[66];			// 0x00DA
		vec3 Position2;				// 0x011C // Other position ??
		char _0x0128[44];			// 0x0128
		PlayerInfo_t* PlayerInfo;	// 0x0154 
		char _0x0158[4];			// 0x0158
		TeamInfo_t* TeamInfo;		// 0x015C 
		char _0x0160[12];			// 0x0160
		__int32 ModelIndex;			// 0x016C // Model ID (44 == Bus)
		char _0x0170[56];			// 0x0170
		__int32 Health;				// 0x01A8 // Health
		char _0x01AC[29320];		// 0x01AC
	};

	struct entity_t { // 0x2E4EDCC4 wow
		char _0x0000[0x4];                            //0x0
		int iPlayerMesh;                              //0x4 (0x2E4EDCC4)
		char _0x0008[0x24];                           //0x8
		Vector3 vOrigin;                              //0x2C (0x2E4EDCEC)
		char _0x0038[0x13C];                          //0x38
		Vector3 vOldOrigin;                           //0x174 (0x2E4EDE34)
		char _0x0180[0x5C];                           //0x180
		int iClientNum;                               //0x1DC (0x2E4EDE9C)
		int iFlags;                                   //0x1E0 (0x2E4EDEA0)
		char _0x01E4[0x10];                           //0x1E4
		Vector3 vNewOrigin;                           //0x1F4 (0x2E4EDEB4)
		char _0x0200[0xB4];                           //0x200
		short shType;                                 //0x2B4 (0x2E4EDF74)
		char _0x02B6[0xA];                            //0x2B6
		int iWeaponID;                                //0x2C0 (0x2E4EDF80)
		char _0x02C4[0xB4];                           //0x2C4
		unsigned char bAlive;                         //0x378 (0x2E4EE038)
		char _0x0379[0x7];                            //0x379
	}; // size = 0x380

	struct ScreenSize { // ????
		__int32 Width;	// 0x00 -> 011A554C
		__int32 Height;	// 0x04 -> 011A5550
		__int32 WidthWrite;	// 0x08 -> 011A5554
		__int32 HeightWrite;// 0x0C -> 011A5558
	};


	typedef struct
	{
		int* szName; //0x0000 
		char _0x0004[108];
	}shader_t;//Size=0x0070


	typedef struct
	{
		char _0x0000[940];
		shader_t* pShader; //0x03AC 
		char _0x03B0[12];
		shader_t* pShader2; //0x03BC 
	}weapon2_t;//Size=0x03C0

	typedef struct
	{
		char _0x0000[12];
		char szName[32]; //0x000C 
		int iTeam; //0x002C 
		int iTeam2; //0x0030 
		char _0x0034[44];
		int iRank; //0x0060 
		char _0x0064[48];
		int iScore; //0x0094 
		char _0x0098[72];
		char szModel[64]; //0x00E0 
		char _0x0120[932];
		Vector3 ViewAngleY; //0x04C4 
		char _0x04D0[192];
		int N2399ED54; //0x0590 
		char _0x0594[48];
		int iWeaponID; //0x05C4 
		char _0x05C8[448];
		weapon2_t* pCurrentWeapon; //0x0788 
		char _0x078C[12];
		weapon2_t* pPrimaryWeapon; //0x0798 
		char _0x079C[108];
	}CClient;//Size=0x0808


	struct AnglePos { // ????
		vec3 Angle;		// 0x00 -> 011A58C4 // angle in percent??
		vec3 Position;	// 0x10 -> 011A58D0
	};
#pragma pack(pop)

	// Globals I guess
	//extern HWND SelfWnd;
	extern Vector3* Pos;
	extern ScreenSize* Screen;
	extern entity_t* Ent;
	extern gentity_t* GEnt;
	extern CClient* Client;
	//extern sCG* CEnt;
	extern const char* WeaponList[95];
	extern int WepLookup[];
}

// Funcs
Offsets::gentity_t* GetGentity(int index);
Offsets::sCG* GetClient(int index);
