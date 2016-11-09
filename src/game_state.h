#ifndef __game_state_h__
#define __game_state_h__

// ------------------------------------------------------------------------------------------------

#include "zt_game.h"
#include "game_type.h"
#include "game_type_arcade.h"


// ------------------------------------------------------------------------------------------------

enum GameState_Enum
{
	GameState_Invalid,

	GameState_Intro,
	GameState_MenuMain,
	GameState_MenuOptions,
	GameState_Playing,

	GameState_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztGame;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct GameStateIntro
{
	r32 time_left;
};


bool gs_introBegin(ztGame *game);
void gs_introCleanup(ztGame *game);
bool gs_introUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gs_introRender(ztGame *game, ztDrawList *draw_list);

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct GameStateMenuMain
{
	int active_option;
};

bool gs_menuMainBegin(ztGame *game);
bool gs_menuMainUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gs_menuMainRender(ztGame *game, ztDrawList *draw_list);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//struct GameStateMenuOptions
//{
//
//};


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct GameStatePlaying
{
	GameType_Enum  game_type;
	GameTypeArcade game_type_arcade;
};

bool gs_playingBegin(ztGame *game);
void gs_playingCleanup(ztGame *game);
bool gs_playingUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gs_playingRender(ztGame *game, ztDrawList *draw_list);


#endif // include guard