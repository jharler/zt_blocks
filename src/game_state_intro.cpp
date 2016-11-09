#include "game_state.h"
#include "game.h"

// ------------------------------------------------------------------------------------------------

#define GS_INTRO_TIME	5

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

		game->game_state_transition_to = GameState_MenuMain;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_introRender(ztGame *game, ztDrawList *draw_list)
{
	zt_drawListAddText2D(draw_list, game->font_primary, "ZT Blocks", ztVec2::zero);
}

// ------------------------------------------------------------------------------------------------
