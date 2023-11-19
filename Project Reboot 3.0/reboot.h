#pragma once

#include "UObjectGlobals.h"
#include "Engine.h"
// #include "World.h"

#include "RandomStream.h"
#include "Class.h"
#include "globals.h"
#include <set>

#include "NetSerialization.h"

/* enum class REBOOT_ERROR : uint8
{
	FAILED_STRINGREF = 1,
	FAILED_CREATE_NETDRIVER = 2,
	FAILED_LISTEN = 3
}; */

extern inline UObject* (*StaticLoadObjectOriginal)(UClass*, UObject*, const wchar_t* InName, const wchar_t* Filename, uint32_t LoadFlags, UObject* Sandbox, bool bAllowObjectReconciliation) = nullptr;

template <typename T = UObject>
static inline T* FindObject(const TCHAR* Name, UClass* Class = nullptr, UObject* Outer = nullptr)
{
	auto res = (T*)StaticFindObject/*<T>*/(Class, Outer, Name);
	return res;
}

template <typename T = UObject>
static inline T* LoadObject(const TCHAR* Name, UClass* Class = T::StaticClass(), UObject* Outer = nullptr)
{
	if (!StaticLoadObjectOriginal)
	{
		std::wstring NameWStr = std::wstring(Name);
		LOG_WARN(LogDev, "We should load {} but static load object is null!", std::string(NameWStr.begin(), NameWStr.end()));
		return FindObject<T>(Name, Class, Outer);
	}

	auto Object = (T*)StaticLoadObjectOriginal(Class, Outer, Name, nullptr, 0, nullptr, false);

	if (!Object)
	{
		LOG_WARN(LogDev, "Failed to load object!");
	}

	return Object;
}

template <typename T = UObject>
static inline T* LoadObject(const std::string& NameStr, UClass* Class = nullptr, UObject* Outer = nullptr)
{
	auto NameCWSTR = std::wstring(NameStr.begin(), NameStr.end()).c_str();
	return (T*)StaticLoadObjectOriginal(Class, Outer, NameCWSTR, nullptr, 0, nullptr, false);
}

template <typename T = UObject>
static inline T* FindObject(const std::string& NameStr, UClass* Class = nullptr, UObject* Outer = nullptr)
{
	std::string name = NameStr;
	auto NameCWSTR = std::wstring(name.begin(), name.end()).c_str();
	return StaticFindObject<T>(Class, Outer, NameCWSTR);
}

static inline UEngine* GetEngine()
{
	static UEngine* Engine = FindObject<UEngine>(L"/Engine/Transient.FortEngine_0");

	if (!Engine)
	{
		__int64 starting = 2147482000;

		for (__int64 i = starting; i < (starting + 1000); i++)
		{
			if (Engine = FindObject<UEngine>("/Engine/Transient.FortEngine_" + std::to_string(i)))
				break;
		}
	}

	return Engine;
}

static inline class UWorld* GetWorld()
{
	static UObject* Engine = GetEngine();
	static auto GameViewportOffset = Engine->GetOffset("GameViewport");
	auto GameViewport = Engine->Get<UObject*>(GameViewportOffset);

	static auto WorldOffset = GameViewport->GetOffset("World");

	return GameViewport->Get<class UWorld*>(WorldOffset);
}

static TArray<UObject*>& GetLocalPlayers()
{
	static UObject* Engine = GetEngine();

	static auto GameInstanceOffset = Engine->GetOffset("GameInstance");
	UObject* GameInstance = Engine->Get(GameInstanceOffset);

	static auto LocalPlayersOffset = GameInstance->GetOffset("LocalPlayers");

	return GameInstance->Get<TArray<UObject*>>(LocalPlayersOffset);
}



static inline std::string GetNPC(std::string NPCToCheck)
{
	std::string NPCClass;

	if (Fortnite_Version >= 13.00)
	{
		if (NPCToCheck == "shark")
			NPCClass = "/SpicySake/Pawns/NPC_Pawn_SpicySake_Parent.NPC_Pawn_SpicySake_Parent_C";
	}

	if (Fortnite_Version >= 16.00)
	{
		if (NPCToCheck == "chicken")
			NPCClass = "/Irwin/AI/Prey/Nug/Pawns/NPC_Pawn_Irwin_Prey_Nug.NPC_Pawn_Irwin_Prey_Nug_C";
		else if (NPCToCheck == "boar")
			NPCClass = "/Irwin/AI/Prey/Burt/Pawns/NPC_Pawn_Irwin_Prey_Burt.NPC_Pawn_Irwin_Prey_Burt_C";
		else if (NPCToCheck == "wolf")
			NPCClass = "/Irwin/AI/Predators/Grandma/Pawns/NPC_Pawn_Irwin_Predator_Grandma.NPC_Pawn_Irwin_Predator_Grandma_C";
		else if (NPCToCheck == "raptor")
			NPCClass = "/Irwin/AI/Predators/Robert/Pawns/NPC_Pawn_Irwin_Predator_Robert.NPC_Pawn_Irwin_Predator_Robert_C";
		else if (NPCToCheck == "frog")
			NPCClass = "/Irwin/AI/Simple/Smackie/Pawns/NPC_Pawn_Irwin_Simple_Smackie.NPC_Pawn_Irwin_Simple_Smackie_C";
		else if (NPCToCheck == "crow")
			NPCClass = "/Irwin/AI/Simple/Avian/Pawns/NPC_Pawn_Irwin_Simple_Avian_Crow.NPC_Pawn_Irwin_Simple_Avian_Crow_C";
	}

	if (Fortnite_Version >= 17.00)
	{
		if (NPCToCheck == "alien")
			NPCClass = "/MotherGameplay/Items/AvacadoEaterBird/BGA_Athena_AvacadoEaterBird.BGA_Athena_AvacadoEaterBird_C";
	}

	if (Fortnite_Version >= 18.21)
	{
		if (NPCToCheck == "caretaker")
			NPCClass = "/Caretaker/Pawns/NPC_Pawn_Irwin_Monster_Caretaker_Smash.NPC_Pawn_Irwin_Monster_Caretaker_Smash_C";
	}

	if (Fortnite_Version >= 19.10)
	{
		if (NPCToCheck == "klombo")
			NPCClass = "/ButterCake/Pawns/NPC_Pawn_ButterCake_Base.NPC_Pawn_ButterCake_Base_C";
		else if (NPCToCheck == "klombo2")
			NPCClass = "/ButterCake/Pawns/NPC_Pawn_ButterCake_A.NPC_Pawn_ButterCake_A_C";
		else if (NPCToCheck == "klombo3")
			NPCClass = "/ButterCake/Pawns/NPC_Pawn_ButterCake_B.NPC_Pawn_ButterCake_B_C";
		else if (NPCToCheck == "klombo4")
			NPCClass = "/ButterCake/Pawns/NPC_Pawn_ButterCake_C.NPC_Pawn_ButterCake_C_C";
		else if (NPCToCheck == "klombo5")
			NPCClass = "/ButterCake/Pawns/NPC_Pawn_ButterCake_D.NPC_Pawn_ButterCake_D_C";
	}

	return NPCClass;
}

static inline std::string GetWeatherCondition(std::string ConditionToCheck)
{
	std::string ConditionClass;

	if (Fortnite_Version >= 19.01)
	{
		if (ConditionToCheck == "tornado")
			ConditionClass = "/Superstorm/Tornado/BP_Tornado.BP_Tornado_C";
		else if (ConditionToCheck == "lightning")
			ConditionClass = "/Superstorm/Lightning/BP_Lightning.BP_Lightning_C";
		else if (ConditionToCheck == "lightningbolt")
			ConditionClass = "/Superstorm/Lightning/BP_LightningBolt.BP_LightningBolt_C";
	}

	return ConditionClass;
}


static inline std::string GetVehicle(std::string VehicleToCheck)
{
	std::string VehicleClass;

	if (VehicleToCheck == "driftboard")
		VehicleClass = "/Game/Athena/DrivableVehicles/JackalVehicle_Athena.JackalVehicle_Athena_C";
	else if (VehicleToCheck == "surfboard")
		VehicleClass = "/Game/Athena/DrivableVehicles/SurfboardVehicle_Athena.SurfboardVehicle_Athena_C";
	else if (VehicleToCheck == "quadcrasher")
		VehicleClass = "/Game/Athena/DrivableVehicles/AntelopeVehicle.AntelopeVehicle_C";
	else if (VehicleToCheck == "baller")
		VehicleClass = "/Game/Athena/DrivableVehicles/Octopus/OctopusVehicle.OctopusVehicle_C";
	else if (VehicleToCheck == "plane")
		VehicleClass = "/Game/Athena/DrivableVehicles/Biplane/BluePrints/FerretVehicle.FerretVehicle_C";
	else if (VehicleToCheck == "golfcart")
		VehicleClass = "/Game/Athena/DrivableVehicles/Golf_Cart/Golf_Cart_Base/Blueprints/GolfCartVehicleSK.GolfCartVehicleSK_C";
	else if (VehicleToCheck == "cannon")
		VehicleClass = "/Game/Athena/DrivableVehicles/PushCannon.PushCannon_C";
	else if (VehicleToCheck == "shoppingcart")
		VehicleClass = "/Game/Athena/DrivableVehicles/ShoppingCartVehicleSK.ShoppingCartVehicleSK_C";
	else if (VehicleToCheck == "brute")
		VehicleClass = "/Game/Athena/DrivableVehicles/Mech/TestMechVehicle.TestMechVehicle_C";
	else if (VehicleToCheck == "truck")
		VehicleClass = "/Valet/BasicTruck/Valet_BasicTruck_Vehicle.Valet_BasicTruck_Vehicle_C";
	else if (VehicleToCheck == "car")
		VehicleClass = "/Valet/BasicCar/Valet_BasicCar_Vehicle.Valet_BasicCar_Vehicle_C";
	else if (VehicleToCheck == "sportcar")
		VehicleClass = "/Valet/SportsCar/Valet_SportsCar_Vehicle.Valet_SportsCar_Vehicle_C";
	else if (VehicleToCheck == "taxi")
		VehicleClass = "/Valet/TaxiCab/Valet_TaxiCab_Vehicle.Valet_TaxiCab_Vehicle_C";
	else if (VehicleToCheck == "mudflap")
		VehicleClass = "/Valet/BigRig/Valet_BigRig_Vehicle.Valet_BigRig_Vehicle_C";
	else if (VehicleToCheck == "starkcar")
		VehicleClass = "/Valet/SportsCar/Valet_SportsCar_Vehicle_HighTower.Valet_SportsCar_Vehicle_HighTower_C";
	else if (VehicleToCheck == "octane")
		VehicleClass = "/Valet/SportsCar/Valet_SportsCar_Vehicle_Turbo.Valet_SportsCar_Vehicle_Turbo_C";
	else if (VehicleToCheck == "boat")
		VehicleClass = "/Game/Athena/DrivableVehicles/Meatball/Meatball_Large/MeatballVehicle_L.MeatballVehicle_L_C";
	else if (VehicleToCheck == "helicopter")
		VehicleClass = "/Hoagie/HoagieVehicle.HoagieVehicle_C";
	else if (VehicleToCheck == "ufo")
		VehicleClass = "/Nevada/Blueprints/Vehicle/Nevada_Vehicle_V2.Nevada_Vehicle_V2_C";
	else if (VehicleToCheck == "ferrari")
		VehicleClass = "/Foray/Vehicle/Foray_Vehicle.Foray_Vehicle_C";

	return VehicleClass;
}

static UObject* GetLocalPlayer()
{
	auto& LocalPlayers = GetLocalPlayers();

	return LocalPlayers.Num() ? LocalPlayers.At(0) : nullptr;
}

static inline UObject* GetLocalPlayerController()
{
	auto LocalPlayer = GetLocalPlayer();

	if (!LocalPlayer)
		return nullptr;

	static auto PlayerControllerOffset = LocalPlayer->GetOffset("PlayerController");

	return LocalPlayer->Get(PlayerControllerOffset);
}

template <typename T>
static __forceinline T* Cast(UObject* Object, bool bCheckType = true)
{
	if (bCheckType)
	{
		if (Object && Object->IsA(T::StaticClass()))
		{
			return (T*)Object;
		}
	}
	else
	{
		return (T*)Object;
	}

	return nullptr;
}

extern inline int AmountOfRestarts = 0; // DO NOT CHANGE
extern inline FRandomStream ReplicationRandStream = (0);
extern inline int32 GSRandSeed = 0;
extern inline std::set<std::string> ReplicatedActors = {};

inline uint8_t GetFieldMask(void* Property, int additional = 0)
{
	if (!Property)
		return -1;

	// 3 = sizeof(FieldSize) + sizeof(ByteOffset) + sizeof(ByteMask)

	if (Engine_Version <= 424 || Fortnite_Version >= 20)
		return *(uint8_t*)(__int64(Property) + (112 + 3 + additional));
	else if (Engine_Version >= 425)
		return *(uint8_t*)(__int64(Property) + (120 + 3 + additional));

	return -1;
}

inline bool ReadBitfield(void* Addr, uint8_t FieldMask)
{
	auto Bitfield = (PlaceholderBitfield*)Addr;

	// niceeeee

	if (FieldMask == 0x1)
		return Bitfield->First;
	else if (FieldMask == 0x2)
		return Bitfield->Second;
	else if (FieldMask == 0x4)
		return Bitfield->Third;
	else if (FieldMask == 0x8)
		return Bitfield->Fourth;
	else if (FieldMask == 0x10)
		return Bitfield->Fifth;
	else if (FieldMask == 0x20)
		return Bitfield->Sixth;
	else if (FieldMask == 0x40)
		return Bitfield->Seventh;
	else if (FieldMask == 0x80)
		return Bitfield->Eighth;
	else if (FieldMask == 0xFF)
		return *(bool*)Bitfield;

	return false;
}

inline void SetBitfield(void* Addr, uint8_t FieldMask, bool NewVal)
{
	auto Bitfield = (PlaceholderBitfield*)Addr;

	// niceeeee

	if (FieldMask == 0x1)
		Bitfield->First = NewVal;
	else if (FieldMask == 0x2)
		Bitfield->Second = NewVal;
	else if (FieldMask == 0x4)
		Bitfield->Third = NewVal;
	else if (FieldMask == 0x8)
		Bitfield->Fourth = NewVal;
	else if (FieldMask == 0x10)
		Bitfield->Fifth = NewVal;
	else if (FieldMask == 0x20)
		Bitfield->Sixth = NewVal;
	else if (FieldMask == 0x40)
		Bitfield->Seventh = NewVal;
	else if (FieldMask == 0x80)
		Bitfield->Eighth = NewVal;
	else if (FieldMask == 0xFF)
		*(bool*)Bitfield = NewVal;
}

template<typename T = UObject>
inline std::vector<T*> GetAllObjectsOfClass(UClass* Class)
{
	std::vector<T*> Objects;

	if (!Class)
		return Objects;

	auto ObjectNum = ChunkedObjects ? ChunkedObjects->Num() : UnchunkedObjects ? UnchunkedObjects->Num() : 0;

	for (int i = 0; i < ObjectNum; i++)
	{
		auto Object = GetObjectByIndex(i);

		if (!Object)
			continue;

		if (Object->IsA(Class))
			Objects.push_back(Object);
	}

	return Objects;
}

template<typename T = UObject>
inline T* GetRandomObjectOfClass(UClass* Class)
{
	auto AllObjectsVec = GetAllObjectsOfClass<T>(Class);

	return AllObjectsVec.size() > 0 ? AllObjectsVec.at(std::rand() % AllObjectsVec.size()) : nullptr;
}

inline void* FindPropertyStruct(const std::string& StructName, const std::string& MemberName, bool bWarnIfNotFound = true)
{
	UObject* Struct = FindObject(StructName);

	if (!Struct)
	{
		if (bWarnIfNotFound)
			LOG_WARN(LogFinder, "Unable to find struct4 {}", StructName);

		return nullptr;
	}

	// LOG_INFO(LogFinder, "Struct: {}", Struct->GetFullName());

	for (auto CurrentClass = Struct; CurrentClass; CurrentClass = *(UObject**)(__int64(CurrentClass) + Offsets::SuperStruct))
	{
		void* Property = *(void**)(__int64(CurrentClass) + Offsets::Children);

		if (Property)
		{
			std::string PropName = GetFNameOfProp(Property)->ToString();

			if (PropName == MemberName)
			{
				return Property;
			}

			while (Property)
			{
				// LOG_INFO(LogFinder, "PropName: {}", PropName);

				if (PropName == MemberName)
				{
					return Property;
				}

				Property = Engine_Version >= 425 ? *(void**)(__int64(Property) + 0x20) : ((UField*)Property)->Next;
				PropName = Property ? GetFNameOfProp(Property)->ToString() : "";
			}
		}
	}

	if (bWarnIfNotFound)
		LOG_WARN(LogFinder, "Unable to find6 {}", MemberName);

	return nullptr;
}

inline int FindOffsetStruct(const std::string& StructName, const std::string& MemberName, bool bWarnIfNotFound = true)
{
	UObject* Struct = FindObject(StructName);

	if (!Struct)
	{
		if (bWarnIfNotFound)
			LOG_WARN(LogFinder, "Unable to find struct {}", StructName);

		return 0;
	}

	// LOG_INFO(LogFinder, "Struct: {}", Struct->GetFullName());

	for (auto CurrentClass = Struct; CurrentClass; CurrentClass = *(UObject**)(__int64(CurrentClass) + Offsets::SuperStruct))
	{
		void* Property = *(void**)(__int64(CurrentClass) + Offsets::Children);

		if (Property)
		{
			std::string PropName = GetFNameOfProp(Property)->ToString();

			if (PropName == MemberName)
			{
				return *(int*)(__int64(Property) + Offsets::Offset_Internal);
			}

			while (Property)
			{
				// LOG_INFO(LogFinder, "PropName: {}", PropName);

				if (PropName == MemberName)
				{
					return *(int*)(__int64(Property) + Offsets::Offset_Internal);
				}

				Property = GetNext(Property);
				PropName = Property ? GetFNameOfProp(Property)->ToString() : "";
			}
		}
	}

	if (bWarnIfNotFound)
		LOG_WARN(LogFinder, "Unable to find1 {}", MemberName);

	return -1;
}

// template <typename T>
static void CopyStruct(void* Dest, void* Src, size_t Size, UStruct* Struct = nullptr)
{
	if (!Src)
		return;

	memcpy_s(Dest, Size, Src, Size);

	if (Struct)
	{
		/* if (std::is_same<T, FFastArraySerializerItem>::value)
		{

		} */

		// TODO: Loop through all the children, check type, if it is ArrayProperty then we need to properly copy it over.
	}
}

class Assets
{
public:
	static UObject* LoadAsset(FName Name, bool ShowDelayTimes = false);
	static UObject* LoadSoftObject(void* SoftObjectPtr);
};

template <typename T = __int64>
static T* Alloc(size_t Size = sizeof(T), bool bUseFMemoryRealloc = false)
{
	auto mem = bUseFMemoryRealloc ? (T*)FMemory::Realloc(0, Size, 0) : (T*)VirtualAlloc(0, Size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	// RtlSecureZeroMemory(mem, Size);
	return mem;
}

namespace MemberOffsets
{
	namespace FortPlayerPawnAthena
	{
		extern inline int LastFallDistance = 0;
	}
	namespace FortPlayerPawn
	{
		extern inline int CorrectTags = 0;
	}
	namespace FortPlayerState
	{
		extern inline int PawnDeathLocation = 0;
	}
	namespace FortPlayerStateAthena
	{
		extern inline int DeathInfo = 0;
		extern inline int KillScore = 0;
		extern inline int TeamKillScore = 0;
	}
	namespace DeathReport
	{
		extern inline int Tags = 0, KillerPlayerState = 0, KillerPawn = 0, DamageCauser = 0;
	}
	namespace DeathInfo
	{
		extern inline int bDBNO = 0, Downer = 0, FinisherOrDowner = 0, DeathCause = 0, Distance = 0, DeathLocation = 0, bInitialized = 0, DeathTags = 0;
	}
}

static inline float GetMaxTickRateHook() { return 30.f; }

#define VALIDATEOFFSET(offset) if (!offset) LOG_WARN(LogDev, "[{}] Invalid offset", __FUNCTIONNAME__);

#define GET_PLAYLIST(GameState) static auto CurrentPlaylistDataOffset = GameState->GetOffset("CurrentPlaylistData", false); \
auto CurrentPlaylist = CurrentPlaylistDataOffset == -1 && Fortnite_Version < 6 ? nullptr : GameState->GetCurrentPlaylist();