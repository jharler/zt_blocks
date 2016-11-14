#include "game_state.h"
#include "game.h"

// ------------------------------------------------------------------------------------------------

bool gs_introBegin(ztGame *game)
{
	game->game_state_intro.time_left = GS_INTRO_TIME;
	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_introCleanup(ztGame *game)
{
}

// ------------------------------------------------------------------------------------------------

bool gs_introUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	game->game_state_intro.time_left -= dt;
	if (game->game_state_intro.time_left < 0) {
		game->game_state_transition_to = GameState_MenuMain;
	}

	if (input_keys[ztInputKeys_Space].justPressed() ||
		input_keys[ztInputKeys_Return].justPressed() ||
		input_controller->justPressed(ztInputControllerButton_Start) || input_controller->justPressed(ztInputControllerButton_A) ||
		input_mouse->leftJustPressed() || input_mouse->rightJustPressed() || input_mouse->middleJustPressed()
		) {

		game->game_state_intro.time_left = zt_min(game->game_state_intro.time_left, GS_INTRO_TIME_FADE_OUT);
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_introRender(ztGame *game, ztDrawList *draw_list)
{
	zt_drawListPushTexture(draw_list, game->tex_zt_logo);
	{
		ztPoint2 tex_size = zt_textureGetSize(game->tex_zt_logo);
		ztVec2 size(tex_size.x / zt_pixelsPerUnit(), tex_size.y / zt_pixelsPerUnit());
		ztVec3 pos(0, 0, 0);
		ztVec4 color(1, 1, 1, 1);

		if (game->game_state_intro.time_left < GS_INTRO_TIME_FADE_OUT) {
			r32 pct = 1 - (game->game_state_intro.time_left / GS_INTRO_TIME_FADE_OUT);

			ztVec3 beg_pos = pos;
			ztVec3 end_pos = GS_ZT_LOGO_SMALL_POSITION;
			pos = ztVec3::lerp(beg_pos, end_pos, pct);

			ztVec2 beg_size = size;
			ztVec2 end_size = GS_ZT_LOGO_SMALL_SIZE;
			size = ztVec2::lerp(beg_size, end_size, pct);

			color.a = zt_lerp(1.f, GS_ZT_LOGO_SMALL_OPACITY, pct);
		}

		zt_drawListPushColor(draw_list, color);
		zt_drawListAddFilledRect2D(draw_list, pos, size, ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);
	}
	zt_drawListPopTexture(draw_list);

	{
		r32 black_pct = 0;

		if (GS_INTRO_TIME - game->game_state_intro.time_left < GS_INTRO_TIME_FADE_IN) {
			black_pct = zt_linearRemap(GS_INTRO_TIME - game->game_state_intro.time_left, 0, GS_INTRO_TIME_FADE_IN, 1, 0);
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
	}

}

// ------------------------------------------------------------------------------------------------
