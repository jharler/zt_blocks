﻿#include "game_state.h"
#include "game.h"


// ------------------------------------------------------------------------------------------------

ztInternal ztVec2 _gs_menuBoxSize(int total_items)
{
	r32 ppu = zt_pixelsPerUnit();

	return ztVec2(7, total_items * ((100) / ppu));
}

// ------------------------------------------------------------------------------------------------

ztInternal void _gs_menuLocateOption(GameStateMenu *gs_menu, int item_idx, ztVec2 *position, ztVec2 *size)
{
	r32 ppu = zt_pixelsPerUnit();
	r32 spacing = 0;

	if (zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_LargeText)) {
		spacing = 20 / ppu;
		size->x = 300 / ppu;
		size->y = 105 / ppu;
	}
	else {
		spacing = 30 / ppu;
		size->x = 300 / ppu;
		size->y = 55 / ppu;
	}

	r32 total_height = (size->y * gs_menu->options_count) + (spacing * (gs_menu->options_count - 1));

	position->x = 0;
	position->y = ((total_height / 2.f) - ((spacing + size->y) * item_idx)) - size->y / 2.f;
}

// ------------------------------------------------------------------------------------------------

void gs_menuSetOptions(GameStateMenu *gs_menu, char **options, int options_count)
{
	gs_menu->options = zt_mallocStructArray(char*, options_count);
	zt_fiz(options_count) {
		int size = zt_strSize(options[i]);
		gs_menu->options[i] = zt_mallocStructArray(char, size);
		zt_strCpy(gs_menu->options[i], size, options[i], size);
	}
	gs_menu->options_count = options_count;
	gs_menu->menu_time = 0;
}

// ------------------------------------------------------------------------------------------------

void gs_menuFreeOptions(GameStateMenu *gs_menu)
{
	zt_fiz(gs_menu->options_count) {
		zt_free(gs_menu->options[i]);
	}
	if (gs_menu->options) {
		zt_free(gs_menu->options);
	}
	gs_menu->options = nullptr;
}

// ------------------------------------------------------------------------------------------------

void gs_menuBegin(GameStateMenu *gs_menu)
{
	gs_menu->menu_time = 0;
	gs_menu->select_time = 0;
}

// ------------------------------------------------------------------------------------------------

GameStateMenuResult_Enum gs_menuUpdate(GameStateMenu *gs_menu, ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse, ztVec2 offset)
{
	gs_menu->menu_time += dt;

	if (gs_menu->select_time == 0 && input_this_frame) {
		bool changed = false;
		if (input_keys[ztInputKeys_Up].justPressedOrRepeated() || input_controller->justPressed(ztInputControllerButton_DPadUp)) {
			changed = true;
			gs_menu->active_option -= 1;
			if (gs_menu->active_option < 0) {
				gs_menu->active_option = gs_menu->options_count - 1;
			}
		}
		if (input_keys[ztInputKeys_Down].justPressedOrRepeated() || input_controller->justPressed(ztInputControllerButton_DPadDown)) {
			changed = true;
			gs_menu->active_option = (gs_menu->active_option + 1) % gs_menu->options_count;
		}

		int mouse_over = -1;
		ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(&game->camera_2d, input_mouse->screen_x, input_mouse->screen_y);

		zt_fiz(gs_menu->options_count) {
			ztVec2 pos, size;
			_gs_menuLocateOption(gs_menu, i, &pos, &size);

			if (zt_collisionPointInRect(mouse_pos, pos + offset, size)) {
				if (input_mouse->delta_x != 0 || input_mouse->delta_y != 0) {
					if (gs_menu->active_option != i) {
						changed = true;
						gs_menu->active_option = i;
					}
				}
				mouse_over = i;
				break;
			}
		}

		if (changed) {
			if (game->audio_menu_change != ztInvalidID) {
				zt_audioClipPlayOnce(game->audio_menu_change);
			}
		}

		if (gs_menu->menu_time >= GS_MENU_SAFETY_THRESHOLD && ((mouse_over != -1 && input_mouse->leftJustPressed()) ||
			input_keys[ztInputKeys_Return].justPressed() || input_keys[ztInputKeys_Space].justPressed() ||
			input_controller->justPressed(ztInputControllerButton_Start) || input_controller->justPressed(ztInputControllerButton_A) )) {
			gs_menu->select_time = GS_MENU_SELECT_TIME;

			if (game->audio_menu_select != ztInvalidID) {
				zt_audioClipPlayOnce(game->audio_menu_select);
			}

			return GameStateMenuResult_Active;
		}
	}
	else if (gs_menu->select_time > 0) {
		gs_menu->select_time -= dt;
		if (gs_menu->select_time <= 0) {
			gs_menu->select_time = 0;
			return GameStateMenuResult_Selected;
		}
	}

	return GameStateMenuResult_Active;
}

// ------------------------------------------------------------------------------------------------

void gs_menuRender(GameStateMenu *gs_menu, ztGame *game, ztDrawList *draw_list, ztVec2 offset)
{
	zt_drawListPushTexture(draw_list, 0);

	if (zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_Darken)) {
		zt_drawListPushColor(draw_list, ztVec4(0, 0, 0, .75f));
		zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, zt_cameraOrthoGetViewportSize(&game->camera_2d), ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);
	}

	if (zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_Background)) {
		zt_drawListPushColor(draw_list, ztVec4(1, 0, 0, 1));
		zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, _gs_menuBoxSize(gs_menu->options_count) + ztVec2(.25f, .25f), ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);
		zt_drawListPushColor(draw_list, ztVec4(0, 0, 0, 1));
		zt_drawListAddFilledRect2D(draw_list, offset, _gs_menuBoxSize(gs_menu->options_count), ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);
	}

	zt_drawListPopTexture(draw_list);

	zt_fiz(gs_menu->options_count) {
		ztVec2 pos, size;
		_gs_menuLocateOption(gs_menu, i, &pos, &size);

		ztFontID font_id = zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_LargeText) ? game->font_huge : game->font_primary;

		i32 align = zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_AlignLeft) ? ztAlign_Left : ztAlign_Center;
		i32 anchor = align;

		if (gs_menu->active_option == i) {
			if (zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_BoxActive)) {
				ztVec2 box_pos = pos + offset + ztVec2(size.x / 2 - .25f, 0);
				zt_drawListPushTexture(draw_list, 0);
				zt_drawListPushColor(draw_list, ztVec4(1, 0, 0, 1));
				zt_drawListAddFilledRect2D(draw_list, box_pos, size + ztVec2(.25f, .25f), ztVec2::zero, ztVec2::one);
				zt_drawListPopColor(draw_list);
				zt_drawListPushColor(draw_list, ztVec4(0, 0, 0, 1));
				zt_drawListAddFilledRect2D(draw_list, box_pos, size, ztVec2::zero, ztVec2::one);
				zt_drawListPopColor(draw_list);
				zt_drawListPopTexture(draw_list);
			}

			r32 osc = zt_linearRemap(zt_sin(gs_menu->menu_time * 6), -1, 1, 0, 1);
			zt_strMakePrintf(text, 256, "<color=%02x%02x%02xff>%s</color>", zt_lerp(255, 251, osc), zt_lerp(255, 98, osc), zt_lerp(255, 20, osc), gs_menu->options[i]);
			zt_drawListAddFancyText2D(draw_list, font_id, text, offset + pos, align, anchor);

			if (gs_menu->select_time > 0) {
				r32 pct = 1 - gs_menu->select_time / GS_MENU_SELECT_TIME;

				zt_strMakePrintf(text_grow, 256, "<color=%02x%02x%02x%02x>%s</color>", zt_lerp(255, 251, osc), zt_lerp(255, 98, osc), zt_lerp(255, 20, osc), zt_lerp(255, 0, pct), gs_menu->options[i]);

				ztVec2 scale = ztVec2::lerp(ztVec2::one, ztVec2(2, 2), pct);
				ztVec2 pos_grow = pos;

				if (zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_AlignLeft)) {
					ztVec2 ext = zt_fontGetExtentsFancy(font_id, text);
					ztVec2 ext_grow = ext * scale;

					pos_grow.x -= (ext_grow.x - ext.x) / 2.f;
				}
				zt_drawListAddFancyText2D(draw_list, font_id, text_grow, offset + pos_grow, scale, align, anchor);
			}

			if (zt_bitIsSet(gs_menu->flags, GameStateMenuFlags_Pointer)) {
				// note: this only works right because we changed the '^' character in the bitmap font to be the arrow
				zt_drawListAddText2D(draw_list, font_id, "^   ", offset + pos + ztVec2(osc * .25f, 0), ztAlign_Right, ztAnchor_Right);
			}
		}
		else {
			zt_drawListAddText2D(draw_list, font_id, gs_menu->options[i], offset + pos, align, anchor);
		}
	}
}

// ------------------------------------------------------------------------------------------------
