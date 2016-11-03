#ifndef __board_h__
#define __board_h__

#include "zt_tools.h"
#include "zt_game.h"

// ------------------------------------------------------------------------------------------------

enum BlockType_Enum
{
	BlockType_Invalid,

	BlockType_Straight,
	BlockType_Square,
	BlockType_T,
	BlockType_J,
	BlockType_L,
	BlockType_S,
	BlockType_Z,

	BlockType_MAX,
};

// ------------------------------------------------------------------------------------------------

enum BlockStateFlags_Enum
{
	BlockStateFlags_Clearing = (1<<15),
};

// ------------------------------------------------------------------------------------------------

enum BoardState_Enum
{
	BoardState_Invalid,

	BoardState_Falling,     // block is falling
	BoardState_Processing,  // block has landed, need to test for line clears
	BoardState_Clearing,    // lines are being cleared
	BoardState_Waiting,     // waiting for next block to begin
};

// ------------------------------------------------------------------------------------------------

#define MAX_NEXT_BLOCKS	3
#define MAX_PREV_BLOCKS 5

// ------------------------------------------------------------------------------------------------

enum BoardInput_Enum
{
	BoardInput_MoveLeft,
	BoardInput_MoveRight,
	BoardInput_RotateLeft,
	BoardInput_RotateRight,
	BoardInput_SoftDrop,
	BoardInput_HardDrop,
	BoardInput_Hold,

	BoardInput_MAX
};

// ------------------------------------------------------------------------------------------------

struct Board
{
	i16           *board;
	ztPoint2       board_size;

	BlockType_Enum active_block          = BlockType_Invalid;
	int            active_block_rotation = 0;
	int            active_block_position = 0;

	BlockType_Enum hold = BlockType_Invalid;
	BlockType_Enum next[MAX_NEXT_BLOCKS];
	BlockType_Enum prev[MAX_PREV_BLOCKS];

	r32            time_to_drop = 0;
	r32            time_to_clear = 0;

	BoardState_Enum current_state = BoardState_Waiting;
};

struct BoardRules
{
	r32 drop_time;
	r32 clear_time;
	int max_next;
};

// ------------------------------------------------------------------------------------------------

Board           boardMake(int width, int height);
void            boardFree(Board *board);

BoardState_Enum boardUpdate(Board *board, r32 dt, BoardRules *rules, BoardInput_Enum *inputs, int inputs_count);

void            boardRender(Board *board, ztDrawList *draw_list, ztTextureID tex_block);

// ------------------------------------------------------------------------------------------------


#endif // include guard