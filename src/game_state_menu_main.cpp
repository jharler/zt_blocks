#include "game_state.h"

// ------------------------------------------------------------------------------------------------

enum GameStateMenuMainItems_Enum
{
	GameStateMenuMainItems_PlayArcade,
	GameStateMenuMainItems_Options,
	GameStateMenuMainItems_Exit,

	GameStateMenuMainItems_MAX,
};

// ------------------------------------------------------------------------------------------------

ztInternal char *_gs_menuMainItems[GameStateMenuMainItems_MAX] = {
	"Play",
	"Options",
	"Exit",
};

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

	game->game_state_main_menu.tex_logo = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/zt_blocks_logo.png"));
	if (game->game_state_main_menu.tex_logo == ztInvalidID) {
		return false;
	}

	gs_menuSetOptions(&game->game_state_main_menu.gs_menu, _gs_menuMainItems, zt_elementsOf(_gs_menuMainItems));

	game->game_state_main_menu.gs_menu.flags |= GameStateMenuFlags_LargeText | GameStateMenuFlags_Pointer | GameStateMenuFlags_AlignLeft | GameStateMenuFlags_BoxActive;
	gs_menuBegin(&game->game_state_main_menu.gs_menu);

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_menuMainCleanup(ztGame *game)
{
	gs_menuFreeOptions(&game->game_state_main_menu.gs_menu);
	zt_textureFree(game->game_state_main_menu.tex_logo);
}

// ------------------------------------------------------------------------------------------------

bool gs_menuMainUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	if (gs_menuUpdate(&game->game_state_main_menu.gs_menu, game, dt, input_this_frame, input_keys, input_controller, input_mouse, GS_MENU_MAIN_OFFSET) == GameStateMenuResult_Selected) {
		switch (game->game_state_main_menu.gs_menu.active_option)
		{
			case GameStateMenuMainItems_PlayArcade: {
				game->game_state_main_menu.next_state = GameState_Playing;
				game->game_state_main_menu.time_out = GS_MENU_MAIN_TIME_FADE_OUT;
			} break;

			case GameStateMenuMainItems_Options: {
			} break;

			case GameStateMenuMainItems_Exit: {
				game->game_state_main_menu.next_state = GameState_Invalid;
				game->game_state_main_menu.time_out = GS_MENU_MAIN_TIME_FADE_OUT;
				return true;
			} break;
		}
	}

	game->game_state_main_menu.time_open += dt;

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

	zt_drawListPushTexture(draw_list, game->game_state_main_menu.tex_logo);
	zt_drawListAddFilledRect2D(draw_list, GS_MENU_LOGO_POSITION, GS_MENU_LOGO_SIZE, ztVec2::zero, ztVec2::one);
	zt_drawListPopTexture(draw_list);

	gs_menuRender(&game->game_state_main_menu.gs_menu, game, draw_list, GS_MENU_MAIN_OFFSET);

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
