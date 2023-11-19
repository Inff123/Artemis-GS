#include "helper.h"
#include <format>
#include "globals.h"
#include "FortPlayerControllerAthena.h"
#include "FortPlaysetItemDefinition.h"
#include "FortAthenaCreativePortal.h"
#include "BuildingContainer.h"
#include "MegaStormManager.h"
#include "FortLootPackage.h"
#include "FortPlayerPawn.h"
#include "FortPickup.h"
#include "bots.h"

#include "FortAbilitySet.h"
#include "NetSerialization.h"
#include "GameplayStatics.h"
#include "DataTableFunctionLibrary.h"
#include "LevelStreamingDynamic.h"
#include "KismetStringLibrary.h"
#include "SoftObjectPtr.h"
#include "discord.h"
#include "BuildingGameplayActorSpawnMachine.h"
#include "BP_IslandScripting.h"

#include "vehicles.h"
#include "globals.h"
#include "events.h"
#include "FortPlaylistAthena.h"
#include "reboot.h"
#include "ai.h"
#include "Map.h"
#include "OnlineReplStructs.h"
#include "BGA.h"
#include "vendingmachine.h"
#include "FortAthenaMutator.h"
#include "calendar.h"
#include "gui.h"
#include <random>
#include "FortGameModeAthena.h"







void Helper::SetSnowIndex(int SnowIndex)
{
	auto GameState = ((AFortGameModeAthena*)GetWorld()->GetGameMode())->GetGameStateAthena();

	if (Fortnite_Version == 19.10)
	{
		auto sjt9ase9i = FindObject("/SpecialSurfaceCoverage/Maps/SpecialSurfaceCoverage_Artemis_Terrain_LS_Parent_Overlay.SpecialSurfaceCoverage_Artemis_Terrain_LS_Parent_Overlay.PersistentLevel.BP_Artemis_S19Progression_C_0");

		// std::cout << "sjt9ase9i: " << sjt9ase9i << '\n';

		if (sjt9ase9i)
		{
			auto setprogr = FindObject<UFunction>("/SpecialSurfaceCoverage/Items/BP_Artemis_S19Progression.BP_Artemis_S19Progression_C.SetSnowProgressionPhase");
			sjt9ase9i->ProcessEvent(setprogr, &SnowIndex);

			auto agh = FindObject<UFunction>("/SpecialSurfaceCoverage/Items/BP_Artemis_S19Progression.BP_Artemis_S19Progression_C.UpdateSnowVisualsOnClient");
			sjt9ase9i->ProcessEvent(agh); // idk if this is needed
		}
	}
}