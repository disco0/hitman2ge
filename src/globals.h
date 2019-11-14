#pragma once

extern bool g_should_unload;
extern HINSTANCE g_this_module;
extern bool g_menu_open;
extern std::vector<hm2_item> g_item_pool;
extern bool g_tool_enabled;
extern const std::array<std::string, 38> g_type_filters;
extern const char* g_current_filter;
extern char g_filter_buffer[128];
extern hm2_item* g_slot1_item;
extern hm2_item* g_slot2_item;
extern hm2_item* g_slot3_item;
extern bool g_picker_open;
extern HWND g_this_hwnd;

enum class picker_selection {
	WEAPON_SLOT,
	TOOL_SLOT1,
	TOOL_SLOT2
};

extern picker_selection g_picker_selection;
extern bool g_can_apply_disguise_override;
extern bool g_randomizer_mod_installed;