#ifndef __game_type_arcade_h__
#define __game_type_arcade_h__

#include "board.h"
#include "game_type.h"


struct GameTypeArcade
{
	Board           board;
	BoardRules      rules;

	int             score;
	bool            paused;

	ztTextureID     background;
	ztTextureID     board_grid;
	ztTextureID     block;
	ztTextureID     block_ghost;

	ztFontID        font_primary;
	ztFontID        font_large;

	ztPoint2        mouse_screen_pos;

	bool            ignore_input;
};


bool gt_arcadeMake(GameTypeArcade *gta, ztAssetManager *asset_manager);
void gt_arcadeFree(GameTypeArcade *gta);
bool gt_arcadeUpdate(GameTypeArcade *gta, r32 dt, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void gt_arcadeRender(GameTypeArcade *gta, ztDrawList *draw_list, ztCamera *camera_2d);



#endif // include guard