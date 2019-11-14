#include "pch.h"

/*
	these sigs work on both dx11 and dx12, and should last a few game updates
*/

void* get_push_item_address() {
	static const auto push_item = find_signature("\x74\x19\x48\x8B\x4D\x67", "xxxxxx") - 0x39;
	return (void*)push_item;
}

void* get_can_apply_disguise_address() {
	static const auto can_apply_disguise = find_signature("\x41\x56\x48\x83\xEC\x50\x80\xB9\x08\x04\x00\x00\x00", "xxxxxxxxxxxxx");
	return (void*)can_apply_disguise;
}

void* get_hero_inventory_return_address() {
	static const auto hero_inventory_return_address = find_signature("\x3B\x05\x00\x00\x00\x00\x8B\xD8", "xx????xx");
	return (void*)hero_inventory_return_address;
}