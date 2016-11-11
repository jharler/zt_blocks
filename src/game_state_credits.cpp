#include "game_state.h"
#include "game.h"

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

bool gs_creditsBegin(ztGame *game)
{
	game->game_state_credits.time_open = GS_CREDITS_TIME_FADE_IN;
	game->game_state_credits.time_out = 0;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool gs_creditsUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	if (game->game_state_credits.time_open > 0) {
		game->game_state_credits.time_open -= dt;

	}
	else if (game->game_state_credits.time_out > 0) {
		game->game_state_credits.time_out -= dt;
		if (game->game_state_credits.time_out <= 0) {
			game->game_state_transition_to = GameState_MenuMain;
		}
	}
	else if (input_this_frame) {
		game->game_state_credits.time_open = 0;
		game->game_state_credits.time_out  = GS_CREDITS_TIME_FADE_OUT;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_creditsRender(ztGame *game, ztDrawList *draw_list)
{
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

	zt_drawListPushTexture(draw_list, 0);
	zt_drawListPushColor(draw_list, ztVec4(1, 0, 0, 1));
	zt_drawListAddFilledRect2D(draw_list, ztVec3(0, -1.5f, 0), ztVec2(10.5f, 5.5f), ztVec2::zero, ztVec2::one);
	zt_drawListPopColor(draw_list);

	zt_drawListPushColor(draw_list, ztVec4(0, 0, 0, 1));
	zt_drawListAddFilledRect2D(draw_list, ztVec3(0, -1.5f, 0), ztVec2(10, 5), ztVec2::zero, ztVec2::one);
	zt_drawListPopColor(draw_list);
	zt_drawListPopTexture(draw_list);

	char *credits =
		"Coding, Design, Audio\n\n"
		"<color=fb6214>Joshua Harler</color>  "
		"<color=14acfb>@jharler_dev</color>\n\n"
		"www.github.com/jharler"
		;

	zt_drawListAddFancyText2D(draw_list, game->font_primary, credits, ztVec2(0, -1.5f), ztAlign_Center, ztAnchor_Center);

	r32 black_pct = 0;

	if (game->game_state_credits.time_out > 0) {
		black_pct = 1 - (game->game_state_credits.time_out / GS_CREDITS_TIME_FADE_OUT);
	}
	else if(game->game_state_credits.time_open > 0) {
		black_pct = zt_min(1, game->game_state_credits.time_open / GS_CREDITS_TIME_FADE_IN);
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
		if (game->game_state_credits.time_out > 0) {
			zt_drawListPushColor(draw_list, ztVec4(1, 1, 1, zt_lerp(0.f, GS_ZT_LOGO_SMALL_OPACITY, game->game_state_credits.time_out / GS_CREDITS_TIME_FADE_OUT)));
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
