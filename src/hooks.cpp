#include "pch.h"

/*
	experimental, used for testing non-equippable disguises
*/
can_apply_disguise_func original_can_apply_disguise = nullptr;
bool __fastcall hooked_can_apply_disguise(void* _outfit_kit) {
	if (g_can_apply_disguise_override)
		return true;

	return original_can_apply_disguise(_outfit_kit);
}

push_item_func original_push_item = nullptr;
__int64 __fastcall hooked_push_item(__int64* world_inventory, UUID uuid, __int64 a3, __int64* a4, __int64 a5, __int64 a6, __int64* a7, __int64* a8, char* a9, char a10) {
	static const auto hero_inventory_retaddr = get_hero_inventory_return_address();

	/*
		skip if the item is not being pushed to
		the hero's inventory

		(the trampoline address for the randomizer is always the 
		same, so a static address is fine here)
	*/
	if (!g_randomizer_mod_installed && _ReturnAddress() != (void*)hero_inventory_retaddr
	 || g_randomizer_mod_installed && _ReturnAddress() != (void*)0x17F00002E )
		return original_push_item(world_inventory, uuid, a3, a4, a5, a6, a7, a8, a9, a10);

	slog("push_item(): %s", uuid_to_str(uuid).c_str());

	if (g_tool_enabled) {
		static uint8_t item_stage = 0;
		item_stage++;
		/*
			quite a bad method of figuring out item slots,
			but it's probably the most consistant way without
			further reversing
		*/

		if (item_stage == 1 && g_slot1_item) {
			log("\t=> %s", g_slot1_item->m_name.c_str());

			return original_push_item(world_inventory, uuid_from_str(g_slot1_item->m_guid.c_str()), a3, a4, a5, a6, a7, a8, a9, a10);
		}

		if (item_stage == 2 && g_slot2_item) {
			log("\t=> %s", g_slot2_item->m_name.c_str());

			return original_push_item(world_inventory, uuid_from_str(g_slot2_item->m_guid.c_str()), a3, a4, a5, a6, a7, a8, a9, a10);
		}

		if (item_stage == 3 && g_slot3_item) {
			log("\t=> %s", g_slot3_item->m_name.c_str());

			return original_push_item(world_inventory, uuid_from_str(g_slot3_item->m_guid.c_str()), a3, a4, a5, a6, a7, a8, a9, a10);
		}

		/*
			skip the last 2 coins if the 3rd slot
			is overridden
		*/

		if (item_stage == 4 && g_slot3_item)
			return 0;

		if (item_stage >= 5) {
			item_stage = 0;

			if (g_slot3_item)
				return 0;
		}
	}

	/*
		push the original uuid if tool is disabled
	*/
	return original_push_item(world_inventory, uuid, a3, a4, a5, a6, a7, a8, a9, a10);
}