#pragma once
/*
#include "reboot.h"
#include "Stack.h"
#include "Actor.h"
#include "hooking.h"
#include "SoftObjectPtr.h"
#include "FortGameModeAthena.h"
#include "GameplayStatics.h"
#include "FortVehicleItemDefinition.h"
#include "FortDagwoodVehicle.h"






static inline void SpawnWeatherV2()
{
	static auto FortAthenaVehicleSpawnerClass = FindObject<UClass>(L"/Script/FortniteGame.FortAthenaVehicleSpawner");
	TArray<AActor*> AllVehicleSpawners = UGameplayStatics::GetAllActorsOfClass(GetWorld(), FortAthenaVehicleSpawnerClass);

	int AmountOfVehiclesSpawned = 0;

	for (int i = 0; i < AllVehicleSpawners.Num(); i++)
	{
		auto VehicleSpawner = AllVehicleSpawners.at(i);
		auto Vehicle = SpawnVehicleFromSpawner(VehicleSpawner);

		if (Vehicle)
		{
			AmountOfVehiclesSpawned++;
		}
	}

	auto AllVehicleSpawnersNum = AllVehicleSpawners.Num();

	AllVehicleSpawners.Free();

	LOG_INFO(LogGame, "Spawned {}/{} vehicles.", AmountOfVehiclesSpawned, AllVehicleSpawnersNum);
}
*/