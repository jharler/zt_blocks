#ifndef __board_h__
#define __board_h__

#include "zt_tools.h"
#include "zt_game.h"

// ------------------------------------------------------------------------------------------------

enum BlockType_Enum
{
	BlockType_Invalid,

	BlockType_I,
	BlockType_O,
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

enum BoardRandomizer_Enum
{
	BoardRandomizer_PureRandom,
	BoardRandomizer_Pool,
	BoardRandomizer_PoolGMA,
	BoardRandomizer_GM1,
	BoardRandomizer_GM2P,

	// BoardRandomizer_GM3TI, // http://tetris.wikia.com/wiki/TGM_randomizer

	BoardRandomizer_MAX
};

// ------------------------------------------------------------------------------------------------

enum BoardRotationSystem_Enum
{
	BoardRotationSystem_GM,
	BoardRotationSystem_SRS, // super rotation system
};

// ------------------------------------------------------------------------------------------------

enum BoardState_Enum
{
	BoardState_Invalid,

	BoardState_Falling,     // block is falling
	BoardState_Processing,  // block has landed, need to test for line clears
	BoardState_Clearing,    // lines are being cleared
	BoardState_Waiting,     // waiting for next block to begin
	BoardState_Failed,      // blocks have reached the top
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

struct BoardStats
{
	int lines_cleared   = 0;
	r32 time_played     = 0;
	int hard_drops      = 0;

	int rotations_left  = 0;
	int rotations_right = 0;

	int block_count[BlockType_MAX];
	int block_drought[BlockType_MAX];

	int clears[4];
};

// ------------------------------------------------------------------------------------------------

struct Board
{
	i16                     *board;
	ztPoint2                 board_size;

	BoardRotationSystem_Enum rotation_system = BoardRotationSystem_SRS;

	BlockType_Enum           active_block          = BlockType_Invalid;
	int                      active_block_rotation = 0;
	int                      active_block_pos_idx  = 0;
	int                      active_block_pos_col  = 0;

	BlockType_Enum           hold = BlockType_Invalid;
	BlockType_Enum           next[MAX_NEXT_BLOCKS];
	BlockType_Enum           prev[MAX_PREV_BLOCKS];

	int                      lines_clearing[4];

	r32                      time_to_drop = 0;
	r32                      time_to_clear = 0;

	r32                      time_to_lock_soft = 0;
	r32                      time_to_lock_hard = 0;

	r32                      input_hold_time[BoardInput_MAX];

	BoardState_Enum          current_state = BoardState_Waiting;

	bool                     block_has_held;
	bool                     hard_drop;


	BoardRandomizer_Enum     randomizer_type = BoardRandomizer_Pool;
	ztRandom                 randomizer;

	union {
		struct {
			BlockType_Enum   pool[BlockType_MAX - 1];
			int              pool_idx;
		} randomizer_pool;

		struct {
			BlockType_Enum   previous[4];
		} randomizer_gm;
	};

	ztAudioClipID            audio_block_move   = ztInvalidID;
	ztAudioClipID            audio_block_rotate = ztInvalidID;
	ztAudioClipID            audio_block_drop   = ztInvalidID;
	ztAudioClipID            audio_block_hold   = ztInvalidID;
	ztAudioClipID            audio_line_clear   = ztInvalidID;


	BoardStats               stats;
};

// ------------------------------------------------------------------------------------------------

struct BoardRules
{
	r32 drop_time;
	r32 drop_time_soft;

	r32 lock_time_soft;
	r32 lock_time_hard;

	r32 clear_time;
	int max_next;

	r32 input_delay_move;
	r32 input_delay_rotation;
	r32 input_delay_hard_drop;
};

// ------------------------------------------------------------------------------------------------

Board           boardMake(int width, int height, BoardRandomizer_Enum randomizer, BoardRotationSystem_Enum rotation_system);
void            boardFree(Board *board);

void            boardReset(Board *board);

BoardState_Enum boardUpdate(Board *board, r32 dt, BoardRules *rules, BoardInput_Enum *inputs, int inputs_count);
void            boardRender(Board *board, ztDrawList *draw_list, ztTextureID tex_block, ztTextureID tex_block_ghost);

void            boardRenderBlock(BoardRotationSystem_Enum rotation_system, BlockType_Enum block, ztDrawList *draw_list, ztVec2 position, int rotation, ztTextureID tex_block);


// ------------------------------------------------------------------------------------------------

#endif // include guard