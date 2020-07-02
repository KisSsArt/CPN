#pragma once
//#include "../../dependencies/utilities/csgo.hpp"
#include "../features/features.hpp"
//#include "../features/misc/engine_prediction.hpp"
#include "../menu/menu.hpp"
#include "../../core/features/visuals/hitmarker.hpp"
#include "../../_D3DDraw/DrawManager.hpp"

hooks::create_move::fn create_move_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;

bool hooks::initialize() {

	auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 24));
	auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));

	if (MH_Initialize() != MH_OK) {
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");
		return false;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}


	/*if (MH_Initialize() == MH_OK) {
		console::log("[setup] hooks initialized!\n");
		return true;
	}
	else {
		throw std::runtime_error("[setup] failed to initialize.");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return false;
	}*/

	std::cout << "[setup] hooks initialized!\n";
	return true;
}


/////
void hooks::release() 
{
	/*std::thread mhU([]() { MH_Uninitialize(); });
	mhU.detach();*/

	std::thread mhD([]() 
		{
			MH_DisableHook(MH_ALL_HOOKS);
		});
	mhD.detach();
    
	/*MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);*/
}


bool __fastcall hooks::create_move::hook(void* ecx, void* edx, int input_sample_frametime, c_usercmd* cmd) {
	//create_move_original(input_sample_frametime, cmd);

	//if (!cmd || !cmd->command_number)
	//	return create_move_original(input_sample_frametime, cmd);

	//csgo::local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	//uintptr_t* frame_pointer;
	//__asm mov frame_pointer, ebp;
	//bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);

	//auto old_viewangles = cmd->viewangles;
	//auto old_forwardmove = cmd->forwardmove;
	//auto old_sidemove = cmd->sidemove;



	/*std::thread bhop(misc::movement::bunny_hop, cmd);
	bhop.detach();


	std::thread glow(visuals::wh::glow, cmd);
	glow.detach();


	std::thread ESP(visuals::wh::ESP, cmd);
	ESP.detach();


	std::thread Radar(misc::radar::radarHack, cmd);
	Radar.detach();


	std::thread antiflash(misc::visuals::antiflash, cmd);
	antiflash.detach();


	std::thread triggerBot(aimbot::aim::trigger, cmd);
	triggerBot.detach();*/

	std::thread FOV([cmd]()
		{
			visuals::FOV::FovChanger(cmd);
		});
	FOV.detach();


	std::thread glow([cmd]() 
		{ 
			visuals::wh::glow(cmd); 
		});
	glow.detach();


	std::thread Radar([cmd]()
		{
			misc::allMisc::radarHack(cmd);
		});
	Radar.detach();


	std::thread antiflash([cmd]()
		{
			misc::allMisc::antiflash(cmd);
		});
	antiflash.detach();
	

	std::thread triggerBot([cmd]()
		{
			aimbot::aim::trigger(cmd);
		});
	triggerBot.detach();
	

	std::thread bhop([cmd]() 
		{
			misc::allMisc::bunny_hop(cmd);
		});
	bhop.detach();


	std::thread clanTag([cmd]()
		{
			misc::allMisc::ClanTagChanger(cmd);
		});
	clanTag.detach();


	std::thread ESP([cmd]()
		{
			visuals::wh::ESP(cmd);
		});
	ESP.detach();

	
	g_Render.InitDeviceObjects(Memory::pDevice());

	//hitmarker.run(cmd);
	
	//prediction::start(cmd); {
	//} prediction::end();

	//math::correct_movement(old_viewangles, cmd, old_forwardmove, old_sidemove);

	//cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	//cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
	//cmd->upmove = std::clamp(cmd->sidemove, -320.0f, 320.0f);

	//cmd->viewangles.normalize();
	//cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	//cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	//cmd->viewangles.z = 0.0f;

	return false;
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) {
	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));

	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):
		
		render::draw_text_string(10, 10, render::fonts::watermark_font, variables::menu_params::watermark, false, color::white(255));

		menu::toggle();
		menu::render();

		break;

	case fnv::hash("FocusOverlayPanel"):
		interfaces::panel->set_keyboard_input_enabled(panel, variables::menu_params::opened);
		interfaces::panel->set_mouse_input_enabled(panel, variables::menu_params::opened);
		break;
	}

	paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
}