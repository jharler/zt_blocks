#include "game_state.h"

// ------------------------------------------------------------------------------------------------

bool gs_playingBegin(ztGame *game)
{
	game->game_state_playing.game_type = GameType_Arcade;
	
	switch (game->game_state_playing.game_type)
	{
		case GameType_Arcade: {
			if (!gt_arcadeMake(&game->game_state_playing.game_type_arcade, &game->asset_manager)) {
				return false;
			}
		} break;
		
		default: zt_assert(false);
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_playingCleanup(ztGame *game)
{
	switch (game->game_state_playing.game_type)
	{
		case GameType_Arcade: {
			gt_arcadeFree(&game->game_state_playing.game_type_arcade);
		} break;
	
		default: zt_assert(false);
	}
}

// ------------------------------------------------------------------------------------------------

bool gs_playingUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	switch (game->game_state_playing.game_type)
	{
		case GameType_Arcade: {
			if (!gt_arcadeUpdate(&game->game_state_playing.game_type_arcade, dt, input_this_frame, input_keys, input_controller, input_mouse)) {
				game->game_state_transition_to = GameState_MenuMain;
			}
		} break;
	
		default: zt_assert(false);
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_playingRender(ztGame *game, ztDrawList *draw_list)
{
	switch (game->game_state_playing.game_type)
	{
		case GameType_Arcade: {
			gt_arcadeRender(&game->game_state_playing.game_type_arcade, &game->draw_list, &game->camera_2d);
		} break;
	
		default: zt_assert(false);
	}
}

// ------------------------------------------------------------------------------------------------
