#pragma once

#include <vector>

#include "globals.h"
#include <functional>
#include "Structs.h"

namespace Helper
{


	static UObject* GetBGAClass() { static auto BGAClass = FindObject("/Script/Engine.BlueprintGeneratedClass"); return BGAClass; }
	static void DestroyActor(UObject* Actor) { static auto fn = FindObject<UFunction>("/Script/Engine.Actor.K2_DestroyActor"); Actor->ProcessEvent(fn); }

	


	UObject* GetGameMode();
	UObject* GetGameState();
	int* GetPlayersLeft();
	void SetSnowIndex(int SnowIndex);







}