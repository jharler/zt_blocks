#include "game_type_arcade.h"
#include "zt_game_gui.h"


ZT_FUNCTION_POINTER_REGISTER(console_displayStats, ZT_FUNC_DEBUG_CONSOLE_COMMAND(console_displayStats))
{
	GameTypeArcade *gta = (GameTypeArcade*)user_data;

	zt_logInfo("Game Stats:");
	zt_logInfo("  Lines cleared: %d", gta->board.stats.lines_cleared);
	zt_logInfo("  Time played: %d", zt_convertToi32Floor(gta->board.stats.time_played));
	zt_logInfo("  Hard drops: %d", gta->board.stats.hard_drops);
	zt_logInfo("  Rotations left: %d", gta->board.stats.rotations_left);
	zt_logInfo("  Rotations right: %d", gta->board.stats.rotations_right);

	struct local
	{
		static char *block_name(int type)
		{
			char *names[] = {
				"Invalid",
				"I",
				"O",
				"T",
				"J",
				"L",
				"S",
				"Z",
			};

			return names[type];
		}
	};

	zt_logInfo("  Block Count:");
	for (int i = 1; i < BlockType_MAX; ++i) {
		zt_logInfo("    %s: %d", local::block_name(i), gta->board.stats.block_count[i]);
	}

	zt_logInfo("  Block Drought:");
	for (int i = 1; i < BlockType_MAX; ++i) {
		zt_logInfo("    %s: %d", local::block_name(i), gta->board.stats.block_drought[i]);
	}

	zt_logInfo("  1 line  clears: %d", gta->board.stats.clears[0]);
	zt_logInfo("  2 line  clears: %d", gta->board.stats.clears[1]);
	zt_logInfo("  3 line  clears: %d", gta->board.stats.clears[2]);
	zt_logInfo("  4 line  clears: %d", gta->board.stats.clears[3]);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _gta_drawLabeledArea(ztDrawList *draw_list, ztFontID font, char *label, ztVec3 position, ztVec2 size, ztVec4 color_bg, ztVec4 color_fg, r32 border, r32 header_size, ztAlign_Enum align_vert, ztAlign_Enum align_horz)
{
	r32 vert_off = 0;
	r32 horz_off = 0;

	switch (align_vert)
	{
		case ztAlign_Left: vert_off += size.x / 2.f; break;
		case ztAlign_Right: vert_off -= size.x / 2.f; break;
	}

	switch (align_horz)
	{
		case ztAlign_Top: horz_off -= size.y / 2.f; break;
		case ztAlign_Bottom: horz_off += size.y / 2.f; break;
	}

	zt_drawListPushTexture(draw_list, 0);
	zt_drawListPushColor(draw_list, color_bg);
	zt_drawListAddFilledRect2D(draw_list, position + ztVec3(vert_off, horz_off, 0), size + ztVec2(border * 2, border * 2 + header_size), ztVec2(0, 0), ztVec2(1, 1));
	zt_drawListPopColor(draw_list);

	zt_drawListPushColor(draw_list, color_fg);
	zt_drawListAddFilledRect2D(draw_list, position + ztVec3(vert_off, horz_off, 0) - ztVec3(0, header_size / 2.f, 0), size, ztVec2(0, 0), ztVec2(1, 1));
	zt_drawListPopColor(draw_list);
	zt_drawListPopTexture(draw_list);

	zt_drawListPushColor(draw_list, ztVec4(0, 1, 0, 1));
	zt_drawListAddText2D(draw_list, font, label, position.xy + ztVec2(vert_off, horz_off) + ztVec2(size.x / -2.f, (size.y + border) / 2.f), ztAlign_Left, ztAnchor_Left);
	zt_drawListPopColor(draw_list);
}

// ------------------------------------------------------------------------------------------------

bool gt_arcadeMake(GameTypeArcade *gta_ptr, ztAssetManager *asset_manager)
{
	GameTypeArcade gta;
	gta.board = boardMake(10, 20, BoardRandomizer_PoolGMA, BoardRotationSystem_SRS);
	
	gta.rules = {};
	gta.rules.max_next              = 3;
	gta.rules.clear_time            = .10f;
	gta.rules.input_delay_move      = .05f;
	gta.rules.input_delay_rotation  = .25f;
	gta.rules.input_delay_hard_drop = 1000;

	ztInternal r32 _gta_drop_times[] = { .5f, .45f, .4f, .35f, .3f, .25f, .2f, .15f, .1f, .05f };
	ztInternal r32 _gta_lock_times[] = { 7.f, 6.5f, 6.f, 5.5f, 5.f, 4.5f, 4.f, 3.5f, 2.5f, 2.0f };

	int idx = zt_min(zt_elementsOf(_gta_drop_times) - 1, 0);
	gta.rules.drop_time      =_gta_drop_times[idx];
	gta.rules.drop_time_soft = gta.rules.drop_time * .02f;
	gta.rules.lock_time_hard = _gta_lock_times[idx];
	gta.rules.lock_time_soft = gta.rules.lock_time_hard * .2f;

	gta.background   = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, "textures/background.png"));
	gta.board_grid   = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, "textures/board_grid.png"));
	gta.block        = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, "textures/block.png"));
	gta.block_ghost  = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, "textures/block_ghost.png"));
	gta.font_primary = zt_fontMakeFromBmpFontAsset(asset_manager, zt_assetLoad(asset_manager, "fonts/impact.fnt"));
	gta.font_large   = zt_fontMakeFromBmpFontAsset(asset_manager, zt_assetLoad(asset_manager, "fonts/impact_large.fnt"));

	if (gta.background == ztInvalidID || gta.board_grid == ztInvalidID || gta.block == ztInvalidID || gta.font_primary == ztInvalidID || gta.font_large == ztInvalidID) {
		return false;
	}

	gta.board.audio_block_move   = zt_audioClipMake(asset_manager, zt_assetLoad(asset_manager, "audio/plop.wav"));
	gta.board.audio_block_rotate = zt_audioClipMake(asset_manager, zt_assetLoad(asset_manager, "audio/boop.wav"));
	gta.board.audio_block_drop   = zt_audioClipMake(asset_manager, zt_assetLoad(asset_manager, "audio/drop.wav"));
	gta.board.audio_line_clear   = zt_audioClipMake(asset_manager, zt_assetLoad(asset_manager, "audio/line_clear.wav"));

	gta.paused = false;

	*gta_ptr = gta;

	zt_debugConsoleAddCommand("stats", "Display stats for current game", console_displayStats_FunctionID, ztInvalidID, gta_ptr);

	return true;
}

// ------------------------------------------------------------------------------------------------

void gt_arcadeFree(GameTypeArcade *gta)
{
	zt_audioClipFree(gta->board.audio_block_move);
	zt_audioClipFree(gta->board.audio_block_rotate);
	zt_audioClipFree(gta->board.audio_block_drop);
	zt_audioClipFree(gta->board.audio_line_clear);

	boardFree(&gta->board);

	zt_textureFree(gta->background);
	zt_textureFree(gta->board_grid);
	zt_textureFree(gta->block);
	zt_textureFree(gta->block_ghost);
	zt_fontFree(gta->font_primary);

}

// ------------------------------------------------------------------------------------------------

void gt_arcadeUpdate(GameTypeArcade *gta, r32 dt, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	if (input_keys[ztInputKeys_Escape].justPressed() || input_controller->justPressed(ztInputControllerButton_Start)) {
		gta->paused = !gta->paused;
	}

	if (input_keys[ztInputKeys_R].justPressed()) {
		boardReset(&gta->board);
	}

	if (!gta->paused) {
		BoardInput_Enum inputs[BoardInput_MAX];
		int inputs_count = 0;

		if (input_keys[ztInputKeys_A].pressed() || input_controller->pressed(ztInputControllerButton_X)) {
			inputs[inputs_count++] = BoardInput_RotateLeft;
		}
		if (input_keys[ztInputKeys_D].pressed() || input_keys[ztInputKeys_Up].pressed() || input_controller->pressed(ztInputControllerButton_Y)) {
			inputs[inputs_count++] = BoardInput_RotateRight;
		}
		if (input_keys[ztInputKeys_Down].pressed() || input_controller->pressed(ztInputControllerButton_DPadDown)) {
			inputs[inputs_count++] = BoardInput_SoftDrop;
		}
		if (input_keys[ztInputKeys_Space].pressed() || input_controller->pressed(ztInputControllerButton_DPadUp)) {
			inputs[inputs_count++] = BoardInput_HardDrop;
		}
		if (input_keys[ztInputKeys_Left].pressed() || input_controller->pressed(ztInputControllerButton_DPadLeft)) {
			inputs[inputs_count++] = BoardInput_MoveLeft;
		}
		if (input_keys[ztInputKeys_Right].pressed() || input_controller->pressed(ztInputControllerButton_DPadRight)) {
			inputs[inputs_count++] = BoardInput_MoveRight;
		}
		if (input_keys[ztInputKeys_Tab].pressed() || input_controller->pressed(ztInputControllerButton_TriggerLeft) || input_controller->pressed(ztInputControllerButton_TriggerRight)) {
			inputs[inputs_count++] = BoardInput_Hold;
		}

		boardUpdate(&gta->board, dt, &gta->rules, inputs, inputs_count);
	}

	gta->mouse_screen_pos = ztPoint2(input_mouse->screen_x, input_mouse->screen_y);
}

// ------------------------------------------------------------------------------------------------

void gt_arcadeRender(GameTypeArcade *gta, ztDrawList *draw_list, ztCamera *camera_2d)
{
	int level = zt_convertToi32Floor(gta->board.stats.lines_cleared / 10.f);

	int score = 0;
	score += gta->board.stats.clears[0] * 100;
	score += gta->board.stats.clears[1] * 200;
	score += gta->board.stats.clears[2] * 400;
	score += gta->board.stats.clears[3] * 800;

	{
		// draw background
		zt_drawListPushTexture(draw_list, gta->background);

		ztVec2 cam_size = zt_cameraOrthoGetViewportSize(camera_2d);
		zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, cam_size, ztVec2(0, 0), ztVec2(1, 1));

		zt_drawListPopTexture(draw_list);
	}

	r32 game_border = 10 / zt_pixelsPerUnit();
	r32 header_border = 31 / zt_pixelsPerUnit();
	ztVec4 area_color_bg(200 / 255.f, 31 / 255.f, 31 / 255.f, 1.f);
	ztVec4 area_color_fg(0, 0, 0, 1);
	{
		// draw game board
		zt_drawListPushTexture(draw_list, 0);
		zt_drawListPushColor(draw_list, area_color_bg);
		zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, ztVec2(5 + game_border * 2, 10 + game_border * 2), ztVec2(0, 0), ztVec2(1, 1));
		zt_drawListPopColor(draw_list);

		zt_drawListPushColor(draw_list, area_color_fg);
		zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, ztVec2(5, 10), ztVec2(0, 0), ztVec2(1, 1));
		zt_drawListPopColor(draw_list);
		zt_drawListPopTexture(draw_list);

		zt_drawListPushTexture(draw_list, gta->board_grid);
		zt_drawListAddFilledRect2D(draw_list, ztVec3::zero, ztVec2(5, 10), ztVec2(0, 0), ztVec2(1, 1));
		zt_drawListPopTexture(draw_list);
	}
	{

		boardRender(&gta->board, draw_list, gta->block, gta->block_ghost);
	}

	{
		// draw hold area
		_gta_drawLabeledArea(draw_list, gta->font_primary, "Hold", ztVec3(-3.25f, 4.76f, 0), ztVec2(2.5f, 2.5f), area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		if (gta->board.hold != BlockType_Invalid) {
			boardRenderBlock(gta->board.rotation_system, gta->board.hold, draw_list, ztVec2(-4.5f, 3.5f), 0, gta->block);
		}
	}

	{
		// draw next area
		_gta_drawLabeledArea(draw_list, gta->font_primary, "Next", ztVec3(3.25f, 4.76f, 0), ztVec2(2.5f, 7.5f), area_color_bg, area_color_fg, game_border, header_border, ztAlign_Left, ztAlign_Top);

		zt_fiz(gta->rules.max_next) {
			if (gta->board.next[i] != BlockType_Invalid) {
				boardRenderBlock(gta->board.rotation_system, gta->board.next[i], draw_list, ztVec2(4.5f, 3.5f - (i * 2.5f)), 0, gta->block);
			}
		}
	}

	ztVec2 size(4.25f, 0.95f);
	r32 x_pos = -3.25f;

	{
		// draw level
		ztVec3 pos(x_pos, .5f, 0);
		_gta_drawLabeledArea(draw_list, gta->font_primary, "Level", pos, size, area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		zt_strMakePrintf(level_str, 8, "%d", level + 1);
		zt_drawListAddText2D(draw_list, gta->font_large, level_str, ztVec2(pos.x - size.x / 2.f, pos.y - (header_border + game_border)));
	}

	{
		// draw lines
		ztVec3 pos(x_pos, -1.65f, 0);
		_gta_drawLabeledArea(draw_list, gta->font_primary, "Lines", pos, size, area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		zt_strMakePrintf(lines_str, 8, "%d", gta->board.stats.lines_cleared);
		zt_drawListAddText2D(draw_list, gta->font_large, lines_str, ztVec2(pos.x - size.x / 2.f, pos.y - (header_border + game_border)));
	}

	{
		// draw score
		ztVec3 pos(x_pos, -3.8f, 0);
		_gta_drawLabeledArea(draw_list, gta->font_primary, "Score", pos, size, area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		char score_str[64];
		zt_strNumberToString(score_str, zt_elementsOf(score_str), (i64)score);
		zt_drawListAddText2D(draw_list, gta->font_large, score_str, ztVec2(pos.x - size.x / 2.f, pos.y - (header_border + game_border)));
	}

	if(false){
		ztVec2 pos(-2.25, 4.5f);
		ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(camera_2d, gta->mouse_screen_pos.x, gta->mouse_screen_pos.y);

		zt_fiz(gta->board.board_size.y) {
			int y = i;
			zt_fjz(gta->board.board_size.x) {
				int x = j;

				ztVec2 grid_pos(pos.x + (x * .5f), pos.y - (y * .5f));

				if (zt_collisionPointInRect(mouse_pos, grid_pos, ztVec2(.5f, .5f))) {
					int idx = (y * gta->board.board_size.x) + x;
					zt_strMakePrintf(str, 16, "%d,%d\n%d", x, y, idx);
					zt_drawListAddText2D(draw_list, gta->font_primary, str, ztVec2(-9, 0), ztAlign_Center, ztAnchor_Center);
				}
			}
		}
	}

	if (gta->paused) {
		zt_drawListAddText2D(draw_list, gta->font_large, "Paused", ztVec2(4.5f, -4), ztAlign_Center, ztAnchor_Center);
	}
}

// ------------------------------------------------------------------------------------------------

