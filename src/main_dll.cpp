/**************************************************************************************************
 ** file: src\main_dll.cpp
 **
 ** This file was automatically generated.
 **************************************************************************************************/

// headers ========================================================================================

#include "zt_tools.h"
#include "zt_game.h"
#include "zt_game_gui.h"
//#include "zt_vr.h"

#include "board.h"


// types/enums/defines ============================================================================

// structs/classes ================================================================================

struct ztGame
{
	ztGameDetails  *details;
	ztGameSettings *settings;

	ztCamera        camera_2d;
	ztCamera        camera_3d;
	ztGuiManagerID  gui_manager;
	//ztVrSystem     *vr;
	ztAssetManager  asset_manager;
	ztDrawList      draw_list;
	ztScene        *scene;
	ztLight         scene_light;

	ztTextureID     background;
	ztTextureID     board_grid;
	ztTextureID     block;
	ztTextureID     block_ghost;

	ztFontID        font_primary;
	ztFontID        font_large;

	Board           board;

	bool            paused;
};


// structs/classes ================================================================================

// variables ======================================================================================

// private functions ==============================================================================

// functions ======================================================================================

ZT_DLLEXPORT bool dll_settings(ztGameDetails* details, ztGameSettings* settings)
{
	settings->memory   = zt_megabytes(128);
	settings->native_w = 1280;
	settings->native_h =  720;
	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT bool dll_init(ztGameDetails* details, ztGameSettings* settings, void** game_memory)
{
	ztGame *game = zt_mallocStruct(ztGame);
	*game = {};
	*game_memory = game;

	game->details = details;
	game->settings = settings;

	game->gui_manager = zt_guiManagerMake(&game->camera_2d, nullptr, zt_memGetGlobalArena());
	zt_guiInitDebug(game->gui_manager);

	//game->vr = zt_vrIsHeadsetPresent() ? zt_vrMake() : nullptr;


	zt_strMakePrintf(data_path, ztFileMaxPath, "%s%cdata", details->user_path, ztFilePathSeparator, ztFilePathSeparator);
	if (!zt_directoryExists(data_path)) {
		zt_strPrintf(data_path, ztFileMaxPath, "%s%crun%cdata", details->user_path, ztFilePathSeparator, ztFilePathSeparator);
	}

	if (!zt_assetManagerLoadDirectory(&game->asset_manager, data_path)) {
		zt_logCritical("Unable to load game assets");
		return false;
	}

	if (!zt_drawListMake(&game->draw_list, 1024 * 128)) {
		zt_logCritical("Unable to initialize draw list");
		return false;
	}

	game->scene = zt_sceneMake(zt_memGetGlobalArena());

	game->background   = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/background.png"));
	game->board_grid   = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/board_grid.png"));
	game->block        = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/block.png"));
	game->block_ghost  = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/block_ghost.png"));
	game->font_primary = zt_fontMakeFromBmpFontAsset(&game->asset_manager, zt_assetLoad(&game->asset_manager, "fonts/impact.fnt"));
	game->font_large   = zt_fontMakeFromBmpFontAsset(&game->asset_manager, zt_assetLoad(&game->asset_manager, "fonts/impact_large.fnt"));

	if (game->background == ztInvalidID || game->board_grid == ztInvalidID || game->block == ztInvalidID || game->font_primary == ztInvalidID || game->font_large == ztInvalidID) {
		return false;
	}

	game->board = boardMake(10, 20);
	game->paused = false;

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT bool dll_reload(void *memory)
{
#	if defined(ZT_DLL)
	ztGame *game = (ztGame*)memory;
	zt_dllGuiLoad();
#	endif
	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT bool dll_unload(void *memory)
{
#	if defined(ZT_DLL)
	ztGame *game = (ztGame*)memory;
	zt_dllGuiUnload();
#	endif
	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT void dll_screenChange(ztGameSettings *settings, void *memory)
{
	ztGame *game = (ztGame*)memory;
	zt_cameraMakeOrtho(&game->camera_2d, settings->screen_w, settings->screen_h, settings->native_w, settings->native_h, 0.1f, 100.f, game->camera_2d.position);
	zt_cameraRecalcMatrices(&game->camera_2d);
	zt_cameraMakePersp(&game->camera_3d, settings->screen_w, settings->screen_h, zt_degreesToRadians(60), 0.1f, 100.f, game->camera_3d.position, game->camera_3d.rotation);
	zt_cameraRecalcMatrices(&game->camera_3d);
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT void dll_cleanup(void *memory)
{
	ztGame *game = (ztGame*)memory;

	boardFree(&game->board);

	zt_textureFree(game->background);
	zt_textureFree(game->board_grid);
	zt_textureFree(game->block);
	zt_textureFree(game->block_ghost);
	zt_fontFree(game->font_primary);

	//if(game->vr) {
	//	if (game->vr->headset.model) {
	//		zt_sceneRemoveModel(game->scene, game->vr->headset.model);
	//	}
	//	zt_fiz(game->vr->controllers_count) {
	//		if (game->vr->controllers[i].model && zt_sceneHasModel(game->scene, game->vr->controllers[i].model)) {
	//			zt_sceneRemoveModel(game->scene, game->vr->controllers[i].model);
	//		}
	//	}
	//	zt_vrFree(game->vr);
	//}
	zt_sceneFreeAllModels(game->scene);
	zt_sceneFree(game->scene);
	zt_drawListFree(&game->draw_list);
	zt_assetManagerFree(&game->asset_manager);
	zt_guiManagerFree(game->gui_manager);
	zt_free(game);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _drawLabeledArea(ztGame *game, char *label, ztVec3 position, ztVec2 size, ztVec4 color_bg, ztVec4 color_fg, r32 border, r32 header_size, ztAlign_Enum align_vert, ztAlign_Enum align_horz)
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

	zt_drawListPushTexture(&game->draw_list, 0);
	zt_drawListPushColor(&game->draw_list, color_bg);
	zt_drawListAddFilledRect2D(&game->draw_list, position + ztVec3(vert_off, horz_off, 0), size + ztVec2(border * 2, border * 2 + header_size), ztVec2(0, 0), ztVec2(1, 1));
	zt_drawListPopColor(&game->draw_list);

	zt_drawListPushColor(&game->draw_list, color_fg);
	zt_drawListAddFilledRect2D(&game->draw_list, position + ztVec3(vert_off, horz_off, 0) - ztVec3(0, header_size / 2.f, 0), size, ztVec2(0, 0), ztVec2(1, 1));
	zt_drawListPopColor(&game->draw_list);
	zt_drawListPopTexture(&game->draw_list);

	zt_drawListPushColor(&game->draw_list, ztVec4(0, 1, 0, 1));
	zt_drawListAddText2D(&game->draw_list, game->font_primary, label, position.xy + ztVec2(vert_off, horz_off) + ztVec2(size.x / -2.f, (size.y + border) / 2.f), ztAlign_Left, ztAnchor_Left);
	zt_drawListPopColor(&game->draw_list);
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT bool dll_gameLoop(void *memory, r32 dt)
{
	ztGame *game = (ztGame*)memory;

	ztInputKeys       *input_keys       = zt_inputKeysAccessState();
	ztInputMouse      *input_mouse      = zt_inputMouseAccessState();
	ztInputController *input_controller = zt_inputControllerAccessState(0);
	ztInputKeys_Enum   input_keystrokes[16];
	zt_inputGetKeyStrokes(input_keystrokes);

	zt_guiManagerUpdate(game->gui_manager, dt);
	bool gui_input = zt_guiManagerHandleInput(game->gui_manager, input_keys, input_keystrokes, input_mouse);
	if(!gui_input) {
		if (input_keys[ztInputKeys_Tilda].justPressed()) {
			bool console_shown = false;
			zt_debugConsoleToggle(&console_shown);
			if (console_shown) {
				zt_guiManagerSetKeyboardFocus(game->gui_manager);
			}
		}
	}

	zt_rendererClear(ztVec4(.25f, 0, 0, 0));

	//if (game->vr) {
	//	if (zt_vrUpdate(game->vr)) {
	//		zt_vrUpdateScene(game->vr, game->scene, ztVrUpdateSceneFlags_IncludeControllers);
	//
	//		ztCamera *cameras[2] = { &game->vr->camera_left, &game->vr->camera_right };
	//		ztTextureID textures[2] = { game->vr->tex_left, game->vr->tex_right };
	//
	//		zt_fiz(2) {
	//			zt_sceneCull(game->scene, cameras[i]);
	//			zt_sceneLighting(game->scene, cameras[i]);
	//
	//			zt_textureRenderTargetPrepare(textures[i]);
	//			zt_rendererClear(ztVec4(0, 0, 0, 1));
	//			zt_sceneRender(game->scene, cameras[i]);
	//			zt_textureRenderTargetCommit(textures[i]);
	//		}
	//
	//		zt_vrSubmit(game->vr);
	//	}
	//}

	//	zt_sceneCull(game->scene, &game->camera_3d);
	//	zt_sceneLighting(game->scene, &game->camera_3d);
	//	zt_sceneRender(game->scene, &game->camera_3d);

	if (input_keys[ztInputKeys_Escape].justPressed() || input_controller->justPressed(ztInputControllerButton_Start)) {
		game->paused = !game->paused;
	}

	BoardRules rules = {};
	rules.max_next              = 3;
	rules.drop_time             = .5f;
	rules.drop_time_soft        = .01f;
	rules.clear_time            = .10f;
	rules.input_delay_move      = .05f;
	rules.input_delay_rotation  = .25f;
	rules.input_delay_hard_drop = 1000;

	if(!game->paused) {
		BoardInput_Enum inputs[BoardInput_MAX];
		int inputs_count = 0;

		if (input_keys[ztInputKeys_A].pressed() || input_controller->pressed(ztInputControllerButton_X)) {
			inputs[inputs_count++] = BoardInput_RotateLeft;
		}
		if (input_keys[ztInputKeys_D].pressed() || input_controller->pressed(ztInputControllerButton_B)) {
			inputs[inputs_count++] = BoardInput_RotateRight;
		}
		if (input_keys[ztInputKeys_Down].pressed() || input_controller->pressed(ztInputControllerButton_DPadDown)) {
			inputs[inputs_count++] = BoardInput_SoftDrop;
		}
		if (input_keys[ztInputKeys_Up].pressed() || input_controller->pressed(ztInputControllerButton_DPadUp)) {
			inputs[inputs_count++] = BoardInput_HardDrop;
		}
		if (input_keys[ztInputKeys_Left].pressed() || input_controller->pressed(ztInputControllerButton_DPadLeft)) {
			inputs[inputs_count++] = BoardInput_MoveLeft;
		}
		if (input_keys[ztInputKeys_Right].pressed() || input_controller->pressed(ztInputControllerButton_DPadRight)) {
			inputs[inputs_count++] = BoardInput_MoveRight;
		}
		if (input_keys[ztInputKeys_Tab].pressed() || input_controller->pressed(ztInputControllerButton_A) || input_controller->pressed(ztInputControllerButton_Y)) {
			inputs[inputs_count++] = BoardInput_Hold;
		}

		if (input_keys[ztInputKeys_R].justPressed()) {
			boardReset(&game->board);
		}

		boardUpdate(&game->board, dt, &rules, inputs, inputs_count);
	}


	zt_drawListPushShader(&game->draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));

	{
		// draw background
		zt_drawListPushTexture(&game->draw_list, game->background);

		ztVec2 cam_size = zt_cameraOrthoGetViewportSize(&game->camera_2d);
		zt_drawListAddFilledRect2D(&game->draw_list, ztVec3::zero, cam_size, ztVec2(0, 0), ztVec2(1, 1));

		zt_drawListPopTexture(&game->draw_list);
	}

	r32 game_border = 10 / zt_pixelsPerUnit();
	r32 header_border = 31 / zt_pixelsPerUnit();
	ztVec4 area_color_bg(200 / 255.f, 31 / 255.f, 31 / 255.f, 1.f);
	ztVec4 area_color_fg(0, 0, 0, 1);
	{
		// draw game board
		zt_drawListPushTexture(&game->draw_list, 0);
		zt_drawListPushColor(&game->draw_list, area_color_bg);
		zt_drawListAddFilledRect2D(&game->draw_list, ztVec3::zero, ztVec2(5 + game_border * 2, 10 + game_border * 2), ztVec2(0, 0), ztVec2(1, 1));
		zt_drawListPopColor(&game->draw_list);

		zt_drawListPushColor(&game->draw_list, area_color_fg);
		zt_drawListAddFilledRect2D(&game->draw_list, ztVec3::zero, ztVec2(5, 10), ztVec2(0, 0), ztVec2(1, 1));
		zt_drawListPopColor(&game->draw_list);
		zt_drawListPopTexture(&game->draw_list);

		zt_drawListPushTexture(&game->draw_list, game->board_grid);
		zt_drawListAddFilledRect2D(&game->draw_list, ztVec3::zero, ztVec2(5, 10), ztVec2(0, 0), ztVec2(1, 1));
		zt_drawListPopTexture(&game->draw_list);
	}
	{

		boardRender(&game->board, &game->draw_list, game->block, game->block_ghost);
	}

	{
		// draw hold area
		_drawLabeledArea(game, "Hold", ztVec3(-3.25f, 4.76f, 0), ztVec2(2.5f, 2.5f), area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		if (game->board.hold != BlockType_Invalid) {
			boardRenderBlock(game->board.hold, &game->draw_list, ztVec2(-4.5f, 3.5f), 0, game->block);
		}
	}

	{
		// draw next area
		_drawLabeledArea(game, "Next", ztVec3(3.25f, 4.76f, 0), ztVec2(2.5f, 7.5f), area_color_bg, area_color_fg, game_border, header_border, ztAlign_Left, ztAlign_Top);

		zt_fiz(rules.max_next) {
			if (game->board.next[i] != BlockType_Invalid) {
				boardRenderBlock(game->board.next[i], &game->draw_list, ztVec2(4.5f, 3.5f - (i * 2.5f)), 0, game->block);
			}
		}
	}

	ztVec2 size(4.25f, 0.95f);
	r32 x_pos = -3.25f;

	{
		// draw level
		ztVec3 pos(x_pos, .5f, 0);
		_drawLabeledArea(game, "Level", pos, size, area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		zt_drawListAddText2D(&game->draw_list, game->font_large, "000", ztVec2(pos.x - size.x / 2.f, pos.y - (header_border + game_border)));
	}

	{
		// draw lines
		ztVec3 pos(x_pos, -1.65f, 0);
		_drawLabeledArea(game, "Lines", pos, size, area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		zt_drawListAddText2D(&game->draw_list, game->font_large, "000", ztVec2(pos.x - size.x / 2.f, pos.y - (header_border + game_border)));
	}

	{
		// draw score
		ztVec3 pos(x_pos, -3.8f, 0);
		_drawLabeledArea(game, "Score", pos, size, area_color_bg, area_color_fg, game_border, header_border, ztAlign_Right, ztAlign_Top);

		zt_drawListAddText2D(&game->draw_list, game->font_large, "000,000,000", ztVec2(pos.x - size.x / 2.f, pos.y - (header_border + game_border)));
	}

	if (game->paused) {
		zt_drawListAddText2D(&game->draw_list, game->font_large, "Paused", ztVec2(4.5f, -4), ztAlign_Center, ztAnchor_Center);
	}

	zt_drawListPopShader(&game->draw_list);

	{
		zt_drawListPushShader(&game->draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
		zt_guiManagerRender(game->gui_manager, &game->draw_list);
		zt_drawListPopShader(&game->draw_list);
		zt_renderDrawList(&game->camera_2d, &game->draw_list, ztVec4::zero, ztRenderDrawListFlags_NoDepthTest | ztRenderDrawListFlags_NoClear);
	}
	zt_assetManagerCheckForChanges(&game->asset_manager);
	return true;
}

// ------------------------------------------------------------------------------------------------
