#include "pch.h"

void run_menu() {
	{
		ImGui::SetNextWindowSize({ 300, 300 });
		ImGui::Begin("Hitman 2 Gear Editor by dom", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		ImGui::Checkbox("Enable", &g_tool_enabled); 
		//ImGui::SameLine(); ImGui::Checkbox("can_apply_disguise hook", &g_can_apply_disguise_override);

		if (ImGui::BeginTabBar("main_tab", ImGuiTabBarFlags_NoTooltip)) {
			if (ImGui::BeginTabItem("Weapon Slot")) {
				ImGui::Text("Selected item");

				if (g_slot1_item == nullptr)
					ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.f), "<no override>");
				else
					ImGui::Text(g_slot1_item->m_name.c_str());


				if (ImGui::Button("Select", { 135, 0 })) {
					g_picker_selection = picker_selection::WEAPON_SLOT;
					g_picker_open = true;
				}

				ImGui::SameLine();

				if (ImGui::Button("Clear Override", { 135, 0 })) {
					g_slot1_item = nullptr;
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Tool Slot 1")) {
				ImGui::Text("Selected item");

				if (g_slot2_item == nullptr)
					ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.f), "<no override>");
				else
					ImGui::Text(g_slot2_item->m_name.c_str());

				if (ImGui::Button("Select", { 135, 0 })) {
					g_picker_selection = picker_selection::TOOL_SLOT1;
					g_picker_open = true;
				}

				ImGui::SameLine();

				if (ImGui::Button("Clear Override", { 135, 0 })) {
					g_slot2_item = nullptr;
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Tool Slot 2")) {
				ImGui::Text("Selected item");

				if (g_slot3_item == nullptr)
					ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.f), "<no override>");
				else
					ImGui::Text(g_slot3_item->m_name.c_str());

				if (ImGui::Button("Select", { 135, 0 })) {
					g_picker_selection = picker_selection::TOOL_SLOT2;
					g_picker_open = true;
				}

				ImGui::SameLine();

				if (ImGui::Button("Clear Override", { 135, 0 })) {
					g_slot3_item = nullptr;
				}

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	if (g_picker_open) {
		{
			ImGui::SetNextWindowSize({ 640, 420 });
			ImGui::Begin(" ", &g_picker_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

			ImGui::Text("Filter by type"); ImGui::SameLine();

			if (ImGui::BeginCombo("##combo", g_current_filter)) {
				for (int n = 0; n < g_type_filters.size(); n++) {
					bool is_selected = !strcmp(g_current_filter, g_type_filters[n].c_str());

					if (ImGui::Selectable(g_type_filters[n].c_str(), is_selected))
						g_current_filter = g_type_filters[n].c_str();

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
			ImGui::Text("Filter by name"); ImGui::SameLine();

			ImGui::InputText("", g_filter_buffer, 128);

			ImGui::BeginChild("content", ImVec2(0, -(ImGui::GetStyle().ItemSpacing.y)), false, 0);

			/*
				setup columns
			*/
			ImGui::Columns(4, "mycolumns");
			ImGui::Separator();

			ImGui::SetColumnWidth(-1, 60);
			ImGui::Text("GUID"); ImGui::NextColumn();

			ImGui::Text("Title"); ImGui::NextColumn();

			ImGui::SetColumnWidth(1, 315);
			ImGui::Text("ItemType"); ImGui::NextColumn();

			ImGui::Text(" "); ImGui::NextColumn();

			ImGui::Separator();

			for (int i = 0; i < g_item_pool.size(); i++) {
				/*
					filter out non-matching items when filtering
					by type
				*/
				if (strcmp(g_current_filter, "No filter") != 0 && g_item_pool[i].m_type != g_current_filter)
					continue;

				if (strlen(g_filter_buffer)) {
					/*
						transform the strings to lower case for
						better search results
					*/
					std::string search_value = g_filter_buffer;
					std::transform(search_value.begin(), search_value.end(), search_value.begin(), ::tolower);

					std::string name = g_item_pool[i].m_name;
					std::transform(name.begin(), name.end(), name.begin(), ::tolower);

					if (name.find(search_value) == std::string::npos)
						continue;
				}

				/*
					fill row with info
				*/
				ImGui::Text(g_item_pool[i].m_guid.c_str());
				ImGui::NextColumn();
				ImGui::Text(g_item_pool[i].m_name.c_str());
				ImGui::NextColumn();
				ImGui::Text(g_item_pool[i].m_type.c_str());
				ImGui::NextColumn();

				/*
					add uuid to button identifier, so imgui
					knows which item to process
				*/
				std::string buffer = "Select##";
				buffer.append(g_item_pool[i].m_guid);

				if (ImGui::Button(buffer.c_str())) {
					switch (g_picker_selection) {
					case picker_selection::WEAPON_SLOT: g_slot1_item = &g_item_pool[i]; break;
					case picker_selection::TOOL_SLOT1: g_slot2_item = &g_item_pool[i]; break;
					case picker_selection::TOOL_SLOT2: g_slot3_item = &g_item_pool[i]; break;
					}

					g_picker_open = false;
				}

				ImGui::NextColumn();
			}
			ImGui::Columns(1);
			ImGui::EndChild();

			ImGui::End();
		}
	}
}

void apply_menu_style() {
	/*
		credits: https://github.com/ocornut/imgui/issues/707#issuecomment-512669512
	*/

	ImGui::GetStyle().FrameRounding = 4.0f;
	ImGui::GetStyle().GrabRounding = 4.0f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
