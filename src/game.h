#ifndef __game_h__
#define __game_h__

// ------------------------------------------------------------------------------------------------

#include "zt_tools.h"
#include "zt_game.h"
#include "zt_game_gui.h"
//#include "zt_vr.h"

#include "board.h"
#include "game_state.h"
#include "game_type_arcade.h"

// ------------------------------------------------------------------------------------------------

// NOTE: do not assign values in the struct definition
//       for some reason, setting game_type in the struct caused nothing to draw on screen

struct ztGame
{
	ztGameDetails       *details;
	ztGameSettings      *settings;
				        
	ztCamera             camera_2d;
	ztCamera             camera_3d;
	ztGuiManagerID       gui_manager;
	//ztVrSystem          *vr;
	ztAssetManager       asset_manager;
	ztDrawList           draw_list;
	ztScene             *scene;
	ztLight              scene_light;

	GameState_Enum       game_state;
	GameState_Enum       game_state_transition_to;

	GameStateIntro       game_state_intro;
	GameStateMenuMain    game_state_main_menu;
	GameStatePlaying     game_state_playing;

	ztFontID             font_primary;
	ztFontID             font_huge;

	ztTextureID          tex_background;
	ztTextureID          tex_zt_logo;

	ztAudioClipID        audio_menu_change;
	ztAudioClipID        audio_menu_select;
};


#endif // include guard