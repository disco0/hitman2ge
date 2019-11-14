#include "pch.h"

bool g_should_unload = false;
HINSTANCE g_this_module = NULL;
bool g_menu_open = false;
std::vector<hm2_item> g_item_pool = { };
bool g_tool_enabled = false;
const std::array<std::string, 38> g_type_filters = { "No filter", "cCC_Book_A", "eCC_C4Brick", "eCC_PetrolCan", "eSyringe_Lethal", "eCC_Cleaver", "eCC_PoliceBaton", "eCC_Katana", "eCC_MetalPipe", "eCC_BaseballBat", "eGun_Taurus24_7", "eGun_HardBaller_01", "eCC_FireExtinguisher_01", "eCC_Axe", "eCC_Hammer", "eCC_FiberWire", "eCC_Bong", "eCC_Radio", "eCC_Knife", "eSyringe_Sedative", "eShotgun_M500New", "eShotgun_Spas12", "eCC_Brick", "eItemAmmo", "eSniper_SakoTRGSilenced", "eCC_Bottle", "eRifle_HK416", "eSyringe_Emetic", "eSMG_HK_UMP", "eSuitcase", "eCC_Screwdriver", "eDetonator", "eCC_Wrench", "eOther_Keycard_A", "eUnknownItemType", "eOther_GenericPickup", "eSniper_SakoTRG", "eCC_RemoteExplosive" };
const char* g_current_filter = "No filter";
char g_filter_buffer[ 128 ];
hm2_item* g_slot1_item = nullptr;
hm2_item* g_slot2_item = nullptr;
hm2_item* g_slot3_item = nullptr;
bool g_picker_open = false;
HWND g_this_hwnd;
picker_selection g_picker_selection;
bool g_can_apply_disguise_override = false;
bool g_randomizer_mod_installed = false;