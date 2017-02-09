#ifndef __game_type_arcade_h__
#define __game_type_arcade_h__

#include "board.h"
#include "board_renderer_2d.h"
#include "game_type.h"


struct ztGame;
struct GameStateMenu;

struct GameTypeArcade
{
	Board            board;
	BoardRules       rules;

	int              score;
	bool             paused;

	ztTextureID      board_grid;

	ztFontID         font_primary;
	ztFontID         font_large;

	ztVec2i         mouse_screen_pos;

	BoardRenderer2d  board_renderer2d;

	bool             ignore_input;

	GameStateMenu    *game_state_menu;
	GameStateMenu    *game_over;
};


bool gt_arcadeMake(GameTypeArcade *gta, ztAssetManager *asset_manager);
void gt_arcadeFree(GameTypeArcade *gta);
bool gt_arcadeUpdate(GameTypeArcade *gta, ztGame *game, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gt_arcadeRender(GameTypeArcade *gta, ztGame *game, ztDrawList *draw_list, ztCamera *camera_2d, ztTextureID tex_background);



#endif // include guard