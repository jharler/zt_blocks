/**************************************************************************************************
 ** file: src\main_dll.cpp
 **
 ** This file was automatically generated.
 **************************************************************************************************/

// headers ========================================================================================

#include "game.h"


// types/enums/defines ============================================================================

// structs/classes ================================================================================

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

	game->font_primary     = zt_fontMakeFromBmpFontAsset(&game->asset_manager, zt_assetLoad(&game->asset_manager, "fonts/impact_large.fnt"));
	game->font_huge        = zt_fontMakeFromBmpFontAsset(&game->asset_manager, zt_assetLoad(&game->asset_manager, "fonts/impact_huge.fnt"));
	game->tex_background   = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/background.png"));
	game->tex_zt_logo      = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/zt_logo.png"));
	game->tex_logo         = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/zt_blocks_logo.png"));
	game->tex_gui_checkbox = zt_textureMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "textures/checkbox.png"));

	if (game->font_primary == ztInvalidID || game->tex_background == ztInvalidID || game->tex_zt_logo == ztInvalidID || game->tex_logo == ztInvalidID || game->tex_gui_checkbox == ztInvalidID) {
		return false;
	}

	game->audio_menu_change = zt_audioClipMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "audio/boop.wav"));
	game->audio_menu_select = zt_audioClipMake(&game->asset_manager, zt_assetLoad(&game->asset_manager, "audio/line_clear_1.wav"));

	game->scene = zt_sceneMake(zt_memGetGlobalArena());

	game->game_state               = GameState_Invalid;
	game->game_state_transition_to = GameState_Intro;

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

ztInternal void dll_gameStateCleanup(ztGame *game)
{
	switch (game->game_state)
	{
		case GameState_Intro: {
			gs_introCleanup(game);
		} break;

		case GameState_MenuMain: {
			gs_menuMainCleanup(game);
		} break;

		case GameState_Playing: {
			gs_playingCleanup(game);
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

ZT_DLLEXPORT void dll_cleanup(void *memory)
{
	ztGame *game = (ztGame*)memory;

	dll_gameStateCleanup(game);

	zt_audioClipFree(game->audio_menu_change);
	zt_audioClipFree(game->audio_menu_select);
	zt_fontFree(game->font_primary);
	zt_fontFree(game->font_huge);
	zt_textureFree(game->tex_background);
	zt_textureFree(game->tex_zt_logo);
	zt_textureFree(game->tex_logo);
	zt_textureFree(game->tex_gui_checkbox);

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

//	ztInputKeys       *input_keys       = zt_inputKeysAccessState();
//	ztInputMouse      *input_mouse      = zt_inputMouseAccessState();
//	ztInputController *input_controller = zt_inputControllerAccessState(0);
	ztInputKeys_Enum   input_keystrokes[16];
	zt_inputGetKeyStrokes(input_keystrokes);

	ztInputKeys       local_input_keys[ztInputKeys_MAX];
	ztInputMouse      local_input_mouse;
	ztInputController local_input_controller;

	zt_inputKeysCopyState(local_input_keys);
	zt_inputMouseCopyState(&local_input_mouse);
	zt_inputControllerCopyState(&local_input_controller, 0);


	zt_guiManagerUpdate(game->gui_manager, dt);
	bool gui_input = zt_guiManagerHandleInput(game->gui_manager, local_input_keys, input_keystrokes, &local_input_mouse);
	if(!gui_input) {
		if (local_input_keys[ztInputKeys_Tilda].justPressed()) {
			bool console_shown = false;
			zt_debugConsoleToggle(&console_shown);
			if (console_shown) {
				zt_guiManagerSetKeyboardFocus(game->gui_manager);
			}
		}
	}
	else { //if(zt_guiManagerHasKeyboardFocus(game->gui_manager)) {
		zt_memSet(local_input_keys, zt_sizeof(ztInputKeys) * ztInputKeys_MAX, 0);
		zt_memSet(&local_input_mouse, zt_sizeof(ztInputMouse), 0);
		zt_memSet(&local_input_controller, zt_sizeof(ztInputController), 0);
	}

	if (!gui_input && local_input_keys[ztInputKeys_M].justPressed()) {
		zt_audioSetMute(!zt_audioGetMute());
	}

	if (game->game_state_transition_to != GameState_Invalid) {
		dll_gameStateCleanup(game);

		game->game_state = game->game_state_transition_to;
		game->game_state_transition_to = GameState_Invalid;

		switch (game->game_state)
		{
			case GameState_Intro: {
				if (!gs_introBegin(game)) {
					return false;
				}
			} break;

			case GameState_MenuMain: {
				if (!gs_menuMainBegin(game)) {
					return false;
				}
			} break;

			case GameState_Credits: {
				if (!gs_creditsBegin(game)) {
					return false;
				}
			} break;

			case GameState_Playing: {
				if (!gs_playingBegin(game)) {
					return false;
				}
			} break;
		}
	}

	bool input_this_frame = zt_inputThisFrame();
	switch (game->game_state)
	{
		case GameState_Intro: {
			if (!gs_introUpdate(game, dt, input_this_frame, local_input_keys, &local_input_controller, &local_input_mouse)) {
				return false;
			}
		} break;

		case GameState_MenuMain: {
			if (!gs_menuMainUpdate(game, dt, input_this_frame, local_input_keys, &local_input_controller, &local_input_mouse)) {
				return false;
			}
		} break;

		case GameState_Credits: {
			if (!gs_creditsUpdate(game, dt, input_this_frame, local_input_keys, &local_input_controller, &local_input_mouse)) {
				return false;
			}
		} break;

		case GameState_Playing: {
			if (!gs_playingUpdate(game, dt, input_this_frame, local_input_keys, &local_input_controller, &local_input_mouse)) {
				return false;
			}
		} break;
	}

	i32 draw_list_flags = 0;
#if defined(ZT_DEBUG)
	if (local_input_keys[ztInputKeys_Control].pressed() && local_input_keys[ztInputKeys_Menu].pressed() && local_input_keys[ztInputKeys_Shift].pressed()) {
		if (local_input_keys[ztInputKeys_D].justPressed()) {
			draw_list_flags |= ztRenderDrawListFlags_DebugDump;
		}
	}
#endif

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
		switch (game->game_state)
		{
			case GameState_Intro: {
				gs_introRender(game, &game->draw_list);
			} break;

			case GameState_MenuMain: {
				gs_menuMainRender(game, &game->draw_list);
			} break;

			case GameState_Credits: {
				gs_creditsRender(game, &game->draw_list);
			} break;

			case GameState_Playing: {
				gs_playingRender(game, &game->draw_list);
			} break;
		}

	}
	zt_drawListPopShader(&game->draw_list);
	zt_renderDrawList(&game->camera_2d, &game->draw_list, ztVec4::zero, ztRenderDrawListFlags_NoDepthTest | 0);

	{
		zt_drawListPushShader(&game->draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
		{
			zt_guiManagerRender(game->gui_manager, &game->draw_list);
		}
		zt_drawListPopShader(&game->draw_list);
		zt_renderDrawList(&game->camera_2d, &game->draw_list, ztVec4::zero, ztRenderDrawListFlags_NoDepthTest | ztRenderDrawListFlags_NoClear | draw_list_flags);
	}

	zt_assetManagerCheckForChanges(&game->asset_manager);
	return true;
}

// ------------------------------------------------------------------------------------------------
