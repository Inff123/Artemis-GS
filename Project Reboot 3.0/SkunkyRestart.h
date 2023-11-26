#pragma once
/*
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3d9.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx9.h>

#include <string>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_stdlib.h>
#include <vector>
#include <format>
#include <imgui/imgui_internal.h>
#include <set>
#include <fstream>
#include <olectl.h>

#include "addresses.h"

#include "Class.h"
#include "KismetSystemLibrary.h"
#include "UObjectArray.h"
#include "Package.h"
#include "objectviewer.h"
#include "FortAthenaMutator_Disco.h"
#include "globals.h"
#include "Fonts/ruda-bold.h"
#include "Vector.h"
#include "reboot.h"
#include "FortGameModeAthena.h"
#include "UnrealString.h"
#include "KismetTextLibrary.h"
#include "KismetSystemLibrary.h"
#include "GameplayStatics.h"
#include "Text.h"
#include <Images/reboot_icon.h>
#include "FortGadgetItemDefinition.h"
#include "FortWeaponItemDefinition.h"
#include "events.h"
#include "FortAthenaMutator_Heist.h"
#include "BGA.h"
#include "vendingmachine.h"
#include "die.h"
#include "Helper.h"
#include "SetSnowIndex.h"
#include "gui.h"
#include "Object.h"
// SKunked

namespace Skunked
{

	UObject* GetPawnFromController(UObject* PC)
	{
		if (!PC)
			return nullptr;

		static auto PawnOffset = GetWorld()->GetOffset("Pawn");

		return *(UObject**)(__int64(PC) + PawnOffset);
	}


	void LoopConnections(std::function<void(UObject* Controller)> fn, bool bPassWithNoPawn = false)
	{
		auto World = GetWorld();

		if (World)
		{
			static auto NetDriverOffset = GetWorld()->GetOffset("NetDriver");
			auto NetDriver = *(UObject**)(__int64(World) + NetDriverOffset);
			if (NetDriver)
			{
				static auto ClientConnectionsOffset = GetWorld()->GetOffset("ClientConnections");
				auto ClientConnections = (TArray<UObject*>*)(__int64(NetDriver) + ClientConnectionsOffset);

				if (ClientConnections)
				{
					for (int i = 0; i < ClientConnections->Num(); i++)
					{
						auto Connection = ClientConnections->At(i);

						if (!Connection)
							continue;

						static auto Connection_PlayerControllerOffset = GetWorld()->GetOffset("PlayerController");
						auto aaController = *(UObject**)(__int64(Connection) + Connection_PlayerControllerOffset);

						if (aaController)
						{
							// auto aaPlayerState = Helper::GetPlayerStateFromController(aaController);
							auto aaPawn = GetPawnFromController(aaController);

							if (aaPawn || bPassWithNoPawn)
							{
								fn(aaController);
							}
						}
					}
				}
			}
		}
	}
}
*/
