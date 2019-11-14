#include "pch.h"

void parse_item_repository() {
	/*
		generate repo string and json document from binary header
	*/
	std::string item_repo = reinterpret_cast<const char*>(g_item_repo_raw);
	item_repo.pop_back();

	rapidjson::Document repository;
	repository.Parse(item_repo.c_str( ));

	/*
		iterate json document members
	*/
	for (rapidjson::Value::ConstMemberIterator itr = repository.MemberBegin(); itr != repository.MemberEnd(); ++itr) {
		hm2_item new_item;

		try {
			/*
				grabs the actual values of the json object
			*/
			auto inner_obj = itr->value.GetObjectW();

			if (inner_obj.FindMember("Title")->value.IsNull() || (inner_obj.FindMember("Title")->value.IsString() && inner_obj.FindMember("Title")->value.GetStringLength() < 3))
				new_item.m_name = inner_obj.FindMember("CommonName")->value.GetString();
			else
				new_item.m_name = inner_obj.FindMember("Title")->value.GetString();

			new_item.m_guid = inner_obj.FindMember("ID_")->value.GetString();
			new_item.m_type = inner_obj.FindMember("ItemType")->value.GetString();
			new_item.m_icon_type = inner_obj.FindMember("ItemHUDType")->value.GetString();
			new_item.m_rarity = inner_obj.FindMember("Rarity")->value.GetString();
		}
		catch (...) { 
			/*
				skip item if we encounter any exceptions
			*/
			continue; 
		}

		g_item_pool.push_back(new_item);
	}

}