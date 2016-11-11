#include "game_state.h"

// ------------------------------------------------------------------------------------------------

enum GameStateMenuMainItems_Enum
{
	GameStateMenuMainItems_PlayArcade,
	GameStateMenuMainItems_Options,
	GameStateMenuMainItems_Credits,
	GameStateMenuMainItems_Exit,

	GameStateMenuMainItems_MAX,
};

// ------------------------------------------------------------------------------------------------

ztInternal char *_gs_menuMainItems[GameStateMenuMainItems_MAX] = {
	"Play",
	"Options",
	"Credits",
	"Exit",
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

enum GameStateMenuOptionsItems_Enum
{
//	GameStateMenuOptionsItems_Music,
	GameStateMenuOptionsItems_Sound,
	GameStateMenuOptionsItems_Fullscreen,
	GameStateMenuOptionsItems_Back,

	GameStateMenuOptionsItems_MAX,
};

// ------------------------------------------------------------------------------------------------

ztInternal char *_gs_menuOptionsItems[GameStateMenuOptionsItems_MAX] = {
//	"Music",
	"Sound",
	"Fullscreen",
	"Back to Main Menu"
};

// ------------------------------------------------------------------------------------------------

ztInternal GameStateMenuOptionType_Enum _gs_menuOptionsTypes[GameStateMenuOptionsItems_MAX] = {
//	GameStateMenuOptionType_Bool,
	GameStateMenuOptionType_Bool,
	GameStateMenuOptionType_Bool,
	GameStateMenuOptionType_None,
};

// ------------------------------------------------------------------------------------------------

ztInternal char *_gs_menuOptionsKeys[GameStateMenuOptionsItems_MAX] = {
//	"music",
	"sound",
	"fullscreen",
	"",
};

// ------------------------------------------------------------------------------------------------

ztInternal char *_gs_menuOptionsKeysDefaults[GameStateMenuOptionsItems_MAX] = {
//	"true",
	"true",
	"false",
	"",
};

// ------------------------------------------------------------------------------------------------

ztInternal char _gs_iniFile[ztFileMaxPath] = { 0 };

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal void _gs_menuMainLocateOption(int item_idx, ztVec2 *position, ztVec2 *size)
{
	r32 ppu = zt_pixelsPerUnit();
	r32 spacing = 30 / ppu;

	size->x = 300 / ppu;
	size->y = 95 / ppu;

	r32 total_height = ((size->y + spacing) * GameStateMenuMainItems_MAX) - spacing;

	position->x = 0;
	position->y = ((total_height / 2.f) - ((spacing + size->y) * item_idx)) - 3.f;
}

// ------------------------------------------------------------------------------------------------

bool gs_menuMainBegin(ztGame *game)
{
	game->game_state_main_menu.time_open = 0;
	game->game_state_main_menu.time_out = 0;
	game->game_state_main_menu.in_options = false;

	gs_menuSetOptions(&game->game_state_main_menu.gs_menu, _gs_menuMainItems, zt_elementsOf(_gs_menuMainItems));
	game->game_state_main_menu.gs_menu.flags |= GameStateMenuFlags_LargeText | GameStateMenuFlags_Pointer | GameStateMenuFlags_AlignLeft | GameStateMenuFlags_BoxActive;
	gs_menuBegin(&game->game_state_main_menu.gs_menu);

	if (_gs_iniFile[0] == 0) {
		char ini_file_path[ztFileMaxPath];
		zt_fileGetAppPath(ini_file_path, ztFileMaxPath);
		zt_fileConcatFileToPath(_gs_iniFile, ztFileMaxPath, ini_file_path, "settings.cfg");
	}

	game->game_state_main_menu.gs_options_menu_options = zt_mallocStructArray(GameStateMenuOption, zt_elementsOf(_gs_menuOptionsTypes));
	zt_fize(_gs_menuOptionsTypes) {
		game->game_state_main_menu.gs_options_menu_options[i].type = _gs_menuOptionsTypes[i];

		switch (_gs_menuOptionsTypes[i])
		{
			case GameStateMenuOptionType_Bool: {
				char value[128];
				zt_iniFileGetValue(_gs_iniFile, "general", _gs_menuOptionsKeys[i], _gs_menuOptionsKeysDefaults[i], value, zt_elementsOf(value));
				game->game_state_main_menu.gs_options_menu_options[i].val_bool = zt_strEquals(value, "true", false);

				switch (i)
				{
					case GameStateMenuOptionsItems_Sound: {
						zt_audioSetMute(!game->game_state_main_menu.gs_options_menu_options[i].val_bool);
					} break;
				}

			} break;
		}
	}

	gs_menuSetOptions(&game->game_state_main_menu.gs_options_menu, _gs_menuOptionsItems, zt_elementsOf(_gs_menuOptionsItems), game->game_state_main_menu.gs_options_menu_options);
	game->game_state_main_menu.gs_options_menu.flags = GameStateMenuFlags_AlignLeft | GameStateMenuFlags_BoxActive;

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_menuMainCleanup(ztGame *game)
{
	gs_menuFreeOptions(&game->game_state_main_menu.gs_menu);
	gs_menuFreeOptions(&game->game_state_main_menu.gs_options_menu);
	zt_free(game->game_state_main_menu.gs_options_menu_options);
}

// ------------------------------------------------------------------------------------------------

bool gs_menuMainUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	if (!game->game_state_main_menu.in_options) {
		if (gs_menuUpdate(&game->game_state_main_menu.gs_menu, game, dt, input_this_frame, input_keys, input_controller, input_mouse, GS_MENU_MAIN_OFFSET) == GameStateMenuResult_Selected) {
			switch (game->game_state_main_menu.gs_menu.active_option)
			{
				case GameStateMenuMainItems_PlayArcade: {
					game->game_state_main_menu.next_state = GameState_Playing;
					game->game_state_main_menu.time_out = GS_MENU_MAIN_TIME_FADE_OUT;
				} break;

				case GameStateMenuMainItems_Options: {
					game->game_state_main_menu.in_options = true;
					game->game_state_main_menu.options_transition_time = GS_MENU_MAIN_TIME_FADE_OUT;

					gs_menuBegin(&game->game_state_main_menu.gs_options_menu);
				} break;

				case GameStateMenuMainItems_Credits: {
					game->game_state_main_menu.next_state = GameState_Credits;
					game->game_state_main_menu.time_out = GS_MENU_MAIN_TIME_FADE_OUT;
				} break;

				case GameStateMenuMainItems_Exit: {
					game->game_state_main_menu.next_state = GameState_Invalid;
					game->game_state_main_menu.time_out = GS_MENU_MAIN_TIME_FADE_OUT;
					return true;
				} break;
			}
		}
	}
	else {
		if (gs_menuUpdate(&game->game_state_main_menu.gs_options_menu, game, dt, input_this_frame, input_keys, input_controller, input_mouse, GS_MENU_MAIN_OFFSET) == GameStateMenuResult_Selected) {

			int opt = game->game_state_main_menu.gs_options_menu.active_option;
			switch (opt)
			{
				//case GameStateMenuOptionsItems_Music:
				case GameStateMenuOptionsItems_Sound:
				case GameStateMenuOptionsItems_Fullscreen: {
					zt_iniFileSetValue(_gs_iniFile, "general", _gs_menuOptionsKeys[opt], game->game_state_main_menu.gs_options_menu_options[opt].val_bool ? "true" : "false");
				} break;
			}

			switch (game->game_state_main_menu.gs_options_menu.active_option)
			{
				//case GameStateMenuOptionsItems_Music:
				case GameStateMenuOptionsItems_Sound: {
					zt_audioSetMute(!game->game_state_main_menu.gs_options_menu_options[opt].val_bool);
				} break;

				case GameStateMenuOptionsItems_Back: {
					game->game_state_main_menu.in_options = false;
					game->game_state_main_menu.options_transition_time = GS_MENU_MAIN_TIME_FADE_OUT;
					return true;
				} break;
			}
		}
	}
	game->game_state_main_menu.time_open += dt;

	if (game->game_state_main_menu.options_transition_time > 0) {
		game->game_state_main_menu.options_transition_time -= dt;
	}

	if (game->game_state_main_menu.time_out > 0) {
		game->game_state_main_menu.time_out -= dt;
		if (game->game_state_main_menu.time_out <= 0) {
			if (game->game_state_main_menu.next_state == GameState_Invalid) {
				return false;
			}

			game->game_state_transition_to = game->game_state_main_menu.next_state;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_menuMainRender(ztGame *game, ztDrawList *draw_list)
{
	if (game->game_state_transition_to != GameState_Invalid) {
		return;
	}

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));

	ztVec4 color = ztVec4::one;
	ztVec2 cam_size = zt_cameraOrthoGetViewportSize(&game->camera_2d);

	zt_drawListPushTexture(draw_list, game->tex_background);
	zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, cam_size, ztVec2::zero, ztVec2::one);
	zt_drawListPopTexture(draw_list);

	zt_drawListPushTexture(draw_list, game->tex_logo);
	zt_drawListAddFilledRect2D(draw_list, GS_MENU_LOGO_POSITION, GS_MENU_LOGO_SIZE, ztVec2::zero, ztVec2::one);
	zt_drawListPopTexture(draw_list);

	ztVec2 offset_main_offscreen = ztVec2(-20, 0);
	ztVec2 offset_options_offscreen = ztVec2(20, 0);

	ztVec2 offset_main = ztVec2::zero;
	ztVec2 offset_options = ztVec2(-4, 0);

	if (game->game_state_main_menu.options_transition_time > 0) {
		r32 pct = 1 - (game->game_state_main_menu.options_transition_time / GS_MENU_MAIN_TIME_FADE_OUT);
		if (game->game_state_main_menu.in_options) {
			offset_main = ztVec2::lerp(ztVec2::zero, offset_main_offscreen, pct);
			offset_options = ztVec2::lerp(offset_options_offscreen, offset_options, pct);
		}
		else {
			offset_main = ztVec2::lerp(offset_main_offscreen, offset_main, pct);
			offset_options = ztVec2::lerp(ztVec2::zero, offset_options_offscreen, pct);
		}
	}
	else {
		if (game->game_state_main_menu.in_options) {
			offset_main = offset_main_offscreen;
		}
		else {
			offset_options = offset_options_offscreen;
		}
	}

	gs_menuRender(&game->game_state_main_menu.gs_menu, game, draw_list, GS_MENU_MAIN_OFFSET + offset_main);
	gs_menuRender(&game->game_state_main_menu.gs_options_menu, game, draw_list, GS_MENU_MAIN_OFFSET + offset_options);

	r32 black_pct = 0;

	if (game->game_state_main_menu.time_out > 0) {
		black_pct = 1 - (game->game_state_main_menu.time_out / GS_MENU_MAIN_TIME_FADE_OUT);
	}
	else {
		black_pct = 1 - zt_min(1, game->game_state_main_menu.time_open / GS_MENU_MAIN_TIME_FADE_IN);
	}

	if (black_pct != 0) {
		zt_drawListPushTexture(draw_list, 0);
		{
			zt_drawListPushColor(draw_list, ztVec4(0, 0, 0, black_pct));
			{
				ztVec2 cam_size = zt_cameraOrthoGetViewportSize(&game->camera_2d);
				zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, cam_size, ztVec2::zero, ztVec2::one);
			}
			zt_drawListPopColor(draw_list);
		}
		zt_drawListPopTexture(draw_list);
	}


	zt_drawListPushTexture(draw_list, game->tex_zt_logo);
	{
		if (game->game_state_main_menu.time_out > 0) {
			zt_drawListPushColor(draw_list, ztVec4(1, 1, 1, zt_lerp(0.f, GS_ZT_LOGO_SMALL_OPACITY, game->game_state_main_menu.time_out / GS_MENU_MAIN_TIME_FADE_OUT)));
		}
		else {
			zt_drawListPushColor(draw_list, ztVec4(1, 1, 1, GS_ZT_LOGO_SMALL_OPACITY));
		}
		{
			zt_drawListAddFilledRect2D(draw_list, GS_ZT_LOGO_SMALL_POSITION, GS_ZT_LOGO_SMALL_SIZE, ztVec2::zero, ztVec2::one);
		}
		zt_drawListPopColor(draw_list);
	}
	zt_drawListPopTexture(draw_list);

	zt_drawListPopShader(draw_list);
}

// ------------------------------------------------------------------------------------------------
