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

// ------------------------------------------------------------------------------------------------

#define GS_ZT_LOGO_SMALL_SIZE			ztVec2(1.5f, 1.5f)
#define GS_ZT_LOGO_SMALL_POSITION       ztVec3(-8.75f, -4.5f, 0)
#define GS_ZT_LOGO_SMALL_OPACITY		.5f

#define GS_INTRO_TIME	2
#define GS_INTRO_TIME_FADE_IN	.5f
#define GS_INTRO_TIME_FADE_OUT	.5f

// ------------------------------------------------------------------------------------------------

bool gs_introBegin(ztGame *game);
void gs_introCleanup(ztGame *game);
bool gs_introUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gs_introRender(ztGame *game, ztDrawList *draw_list);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

enum GameStateMenuFlags_Enum
{
	GameStateMenuFlags_LargeText  = (1 << 0),
	GameStateMenuFlags_Pointer    = (1 << 1),
	GameStateMenuFlags_Darken     = (1 << 2),
	GameStateMenuFlags_Background = (1 << 3),
	GameStateMenuFlags_AlignLeft  = (1 << 4),
	GameStateMenuFlags_BoxActive  = (1 << 5),
};


struct GameStateMenu
{
	int    active_option;
	i32    flags;
	char **options;
	int    options_count;
	r32    menu_time;
	r32    select_time;
};

enum GameStateMenuResult_Enum
{
	GameStateMenuResult_Active,
	GameStateMenuResult_Selected,
};

#define GS_MENU_SAFETY_THRESHOLD    .25f
#define GS_MENU_SELECT_TIME         .25f


void gs_menuSetOptions(GameStateMenu *gs_menu, char **options, int options_count);
void gs_menuFreeOptions(GameStateMenu *gs_menu);

void                     gs_menuBegin(GameStateMenu *gs_menu);
GameStateMenuResult_Enum gs_menuUpdate(GameStateMenu *gs_menu, ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse, ztVec2 offset = ztVec2::zero);
void                     gs_menuRender(GameStateMenu *gs_menu, ztGame *game, ztDrawList *draw_list, ztVec2 offset = ztVec2::zero);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct GameStateMenuMain
{
	r32 time_open;
	r32 time_out;

	GameState_Enum next_state;

	ztTextureID    tex_logo;

	GameStateMenu  gs_menu;
};

// ------------------------------------------------------------------------------------------------

#define GS_MENU_LOGO_SIZE		ztVec2(1280 / 64.f, 604 / 64.f)
#define GS_MENU_LOGO_POSITION	ztVec3(0, 1.25f, 0)

#define GS_MENU_MAIN_TIME_FADE_IN	.5f
#define GS_MENU_MAIN_TIME_FADE_OUT	.5f

#define GS_MENU_MAIN_OFFSET         ztVec2(0, -2)

// ------------------------------------------------------------------------------------------------

bool gs_menuMainBegin(ztGame *game);
void gs_menuMainCleanup(ztGame *game);
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