#pragma once

using can_apply_disguise_func = bool(__fastcall*)(void*);
extern can_apply_disguise_func original_can_apply_disguise;
bool __fastcall hooked_can_apply_disguise(void* _outfit_kit);

using push_item_func = __int64(__fastcall*)(__int64*, UUID, __int64, __int64*, __int64, __int64, __int64*, __int64*, char*, char);
extern push_item_func original_push_item;
__int64 __fastcall hooked_push_item(__int64* world_inventory, UUID uuid, __int64 a3, __int64* a4, __int64 a5, __int64 a6, __int64* a7, __int64* a8, char* a9, char a10);
