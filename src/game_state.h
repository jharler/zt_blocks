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
	GameState_Credits,
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

#define GS_ZT_LOGO_SMALL_SIZE			zt_vec2(1.5f, 1.5f)
#define GS_ZT_LOGO_SMALL_POSITION       zt_vec3(-8.75f, -4.5f, 0)
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

// ------------------------------------------------------------------------------------------------

enum GameStateMenuOptionType_Enum
{
	GameStateMenuOptionType_None,
	GameStateMenuOptionType_Bool,

	GameStateMenuOptionType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct GameStateMenuOption
{
	GameStateMenuOptionType_Enum type;

	union {
		bool val_bool;
	};
};

// ------------------------------------------------------------------------------------------------

struct GameStateMenu
{
	int                  active_option;
	i32                  flags;
	char               **options;
	int                  options_count;
	r32                  menu_time;
	r32                  select_time;
	r32                  max_width;

	GameStateMenuOption *option_vals;
};

// ------------------------------------------------------------------------------------------------

enum GameStateMenuResult_Enum
{
	GameStateMenuResult_Active,
	GameStateMenuResult_Selected,
};

// ------------------------------------------------------------------------------------------------

#define GS_MENU_SAFETY_THRESHOLD    .25f
#define GS_MENU_SELECT_TIME         .25f

// ------------------------------------------------------------------------------------------------

void gs_menuSetOptions(GameStateMenu *gs_menu, char **options, int options_count, GameStateMenuOption *option_vals = nullptr);
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

	GameStateMenu  gs_menu;
	GameStateMenu  gs_options_menu;

	GameStateMenuOption *gs_options_menu_options;

	bool in_options;
	r32  options_transition_time;
};

// ------------------------------------------------------------------------------------------------

#define GS_MENU_LOGO_SIZE		zt_vec2(1280 / 64.f, 604 / 64.f)
#define GS_MENU_LOGO_POSITION	zt_vec3(0, 1.75f, 0)

#define GS_MENU_MAIN_TIME_FADE_IN	.5f
#define GS_MENU_MAIN_TIME_FADE_OUT	.5f

#define GS_MENU_MAIN_OFFSET         zt_vec2(0, -1.65f)

// ------------------------------------------------------------------------------------------------

bool gs_menuMainBegin(ztGame *game);
void gs_menuMainCleanup(ztGame *game);
bool gs_menuMainUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gs_menuMainRender(ztGame *game, ztDrawList *draw_list);



// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct GameStateCredits
{
	r32 time_open;
	r32 time_out;
};

// ------------------------------------------------------------------------------------------------

#define GS_CREDITS_TIME_FADE_IN   .5f
#define GS_CREDITS_TIME_FADE_OUT  .5f

// ------------------------------------------------------------------------------------------------

bool gs_creditsBegin(ztGame *game);
bool gs_creditsUpdate(ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gs_creditsRender(ztGame *game, ztDrawList *draw_list);


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