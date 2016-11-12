#ifndef __board_renderer_2d__
#define __board_renderer_2d__

#include "board.h"

// ------------------------------------------------------------------------------------------------

struct BoardRenderer2d
{
	ztTextureID tex_block;
	ztTextureID tex_block_ghost;
	ztTextureID tex_block_blur;

	int            active_block_last_idx;
	int            active_block_last_col;
	int            active_block_last_rot;
	BlockType_Enum active_block_last_block;

	ztVec2 hard_drop_pos;
	ztVec2 hard_drop_size;
	r32    hard_drop_time;
	ztVec4 hard_drop_color;
};

// ------------------------------------------------------------------------------------------------

#define BOARD_RENDERER_2D_HARD_DROP_TIME	.45f

// ------------------------------------------------------------------------------------------------

bool boardRenderer2dMake(BoardRenderer2d *renderer, Board *board, ztAssetManager *asset_manager);
void boardRenderer2dFree(BoardRenderer2d *renderer);

void boardRenderer2dUpdate(BoardRenderer2d *renderer, Board *board, r32 dt);
void boardRenderer2dRender(BoardRenderer2d *renderer, Board *board, BoardRules *rules, ztDrawList *draw_list, ztVec2 position);

void boardRenderer2dRenderBlock(BoardRenderer2d *renderer, BoardRotationSystem_Enum rotation_system, BlockType_Enum block, ztDrawList *draw_list, ztVec2 position, int rotation);


// ------------------------------------------------------------------------------------------------


#endif // include guard