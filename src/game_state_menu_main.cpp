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
	"Play Arcade",
	"Options",
	"Exit",
};

// ------------------------------------------------------------------------------------------------

ztInternal void _gs_menuMainLocateOption(int item_idx, ztVec2 *position, ztVec2 *size)
{
	r32 ppu = zt_pixelsPerUnit();
	r32 spacing = 20 / ppu;

	size->x = 400 / ppu;
	size->y = 50 / ppu;

	r32 total_height = ((size->y + spacing) * GameStateMenuMainItems_MAX) - spacing;

	position->x = 0;
	position->y = (total_height / 2.f) - ((spacing + size->y) * item_idx);
}

// ------------------------------------------------------------------------------------------------

bool gs_menuMainBegin(ztGame *game)
{
	game->game_state_main_menu.active_option = 0;
	return true;
}

// ------------------------------------------------------------------------------------------------

bool gs_menuMainUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	if (input_keys[ztInputKeys_Up].justPressedOrRepeated() || input_controller->justPressed(ztInputControllerButton_DPadUp)) {
		game->game_state_main_menu.active_option -= 1;
		if (game->game_state_main_menu.active_option < 0) {
			game->game_state_main_menu.active_option = GameStateMenuMainItems_MAX - 1;
		}
	}
	if (input_keys[ztInputKeys_Down].justPressedOrRepeated() || input_controller->justPressed(ztInputControllerButton_DPadDown)) {
		game->game_state_main_menu.active_option = (game->game_state_main_menu.active_option + 1) % GameStateMenuMainItems_MAX;
	}

	int mouse_over = -1;
	ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(&game->camera_2d, input_mouse->screen_x, input_mouse->screen_y);

	zt_fiz(GameStateMenuMainItems_MAX) {
		ztVec2 pos, size;
		_gs_menuMainLocateOption(i, &pos, &size);

		if (zt_collisionPointInRect(mouse_pos, pos, size)) {
			if (input_mouse->delta_x != 0 || input_mouse->delta_y != 0) {
				game->game_state_main_menu.active_option = i;
			}
			mouse_over = i;
			break;
		}
	}

	if ((mouse_over != -1 && input_mouse->leftJustPressed()) ||
		input_keys[ztInputKeys_Return].justPressed() || input_keys[ztInputKeys_Space].justPressed() ||
		input_controller->justPressed(ztInputControllerButton_Start) || input_controller->justPressed(ztInputControllerButton_A)
		) {

		switch (game->game_state_main_menu.active_option)
		{
			case GameStateMenuMainItems_PlayArcade: {
				game->game_state_transition_to = GameState_Playing;
			} break;

			case GameStateMenuMainItems_Options: {
			} break;

			case GameStateMenuMainItems_Exit: {
				return false;
			} break;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void gs_menuMainRender(ztGame *game, ztDrawList *draw_list)
{
	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	{
		zt_fiz(GameStateMenuMainItems_MAX) {
			ztVec2 pos, size;
			_gs_menuMainLocateOption(i, &pos, &size);

			if (i == game->game_state_main_menu.active_option) {
				zt_drawListPushColor(draw_list, ztVec4(0, 1, 0, 1));
				{
					zt_strMakePrintf(item, 128, "- %s -", _gs_menuMainItems[i]);
					zt_drawListAddText2D(draw_list, game->font_primary, item, pos);
				}
				zt_drawListPopColor(draw_list);
			}
			else {
				zt_drawListAddText2D(draw_list, game->font_primary, _gs_menuMainItems[i], pos);
			}
		}
	}
	zt_drawListPopShader(draw_list);
}

// ------------------------------------------------------------------------------------------------
