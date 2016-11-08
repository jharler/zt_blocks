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
#include "game_type_arcade.h"

// types/enums/defines ============================================================================

// structs/classes ================================================================================

// NOTE: do not assign values in the struct definition
//       for some reason, setting game_type in the struct caused nothing to draw on screen

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

	GameType_Enum  game_type;
	GameTypeArcade game_type_arcade;
};


// structs/classes ================================================================================

// variables ======================================================================================

// private functions ==============================================================================

// ------------------------------------------------------------------------------------------------


// functions ======================================================================================

ZT_DLLEXPORT bool dll_settings(ztGameDetails* details, ztGameSettings* settings)
{
	settings->memory = zt_megabytes(128);
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

	game->game_type = GameType_Arcade;

	switch (game->game_type)
	{
		case GameType_Arcade: {
			if (!gt_arcadeMake(&game->game_type_arcade, &game->asset_manager)) {
				return false;
			}
		} break;
	
		default: zt_assert(false);
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT bool dll_reload(void *memory)
{
	ztGame *game = (ztGame*)memory;
#	if defined(ZT_DLL)
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

	switch (game->game_type)
	{
		case GameType_Arcade: {
			gt_arcadeFree(&game->game_type_arcade);
		} break;
	
		default: zt_assert(false);
	}

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

	if (!gui_input && input_keys[ztInputKeys_M].justPressed()) {
		zt_audioSetMute(!zt_audioGetMute());
	}

	switch (game->game_type)
	{
		case GameType_Arcade: {
			gt_arcadeUpdate(&game->game_type_arcade, dt, input_keys, input_controller, input_mouse);
		} break;

		default: zt_assert(false);
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

	zt_drawListPushShader(&game->draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	{
		switch (game->game_type)
		{
			case GameType_Arcade: {
				gt_arcadeRender(&game->game_type_arcade, &game->draw_list, &game->camera_2d);
			} break;

			default: zt_assert(false);
		}
	}
	zt_drawListPopShader(&game->draw_list);
	zt_renderDrawList(&game->camera_2d, &game->draw_list, ztVec4::zero, ztRenderDrawListFlags_NoDepthTest);

	{
		zt_drawListPushShader(&game->draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
		{
			zt_guiManagerRender(game->gui_manager, &game->draw_list);
		}
		zt_drawListPopShader(&game->draw_list);
		zt_renderDrawList(&game->camera_2d, &game->draw_list, ztVec4::zero, ztRenderDrawListFlags_NoDepthTest | ztRenderDrawListFlags_NoClear);
	}

	zt_assetManagerCheckForChanges(&game->asset_manager);
	return true;
}

// ------------------------------------------------------------------------------------------------
