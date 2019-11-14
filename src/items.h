#pragma once

struct hm2_item {
	std::string m_name = "n/a";
	std::string m_guid = "n/a";
	std::string m_type = "n/a";
	std::string m_icon_type = "n/a";
	std::string m_rarity = "n/a";
};

void parse_item_repository( );

/*
std::string load_repo_from_resource() {
	auto resource_ref = FindResource(nullptr, MAKEINTRESOURCE(IDR_JSON1), RT_STRING);
	auto resource = LoadResource(nullptr, resource_ref);

	void* data_ptr = LockResource(resource);
	size_t data_size = SizeofResource(nullptr, resource_ref);

	return std::string(reinterpret_cast<char*>(data_ptr), data_size);
}*/