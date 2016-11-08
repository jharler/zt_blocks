#include "board.h"

#include <time.h>

// ------------------------------------------------------------------------------------------------

#define BOARD_TOP_BUFFER_COUNT 2

// ------------------------------------------------------------------------------------------------

ztInternal void _boardGetBlockPieces_GM(BlockType_Enum block, int rotation, i8 *pieces)
{
	switch (block)
	{
		case BlockType_I: {
			switch (rotation)
			{
				case 2:
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 1,
						0, 0, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3:
				case 1: {
					i8 block_pieces[] = {
						0, 0, 1, 0,
						0, 0, 1, 0,
						0, 0, 1, 0,
						0, 0, 1, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_O: {
			i8 block_pieces[] = {
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 1, 1, 0,
				0, 1, 1, 0
			};
			zt_memCpy(pieces, 16, block_pieces, 16);
		} break;

		case BlockType_T: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 1, 0,
						0, 0, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						0, 1, 1, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_J: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 0,
						0, 0, 1, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 0, 0, 0,
						1, 1, 1, 0,
						0, 0, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 1, 0,
						0, 1, 0, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_L: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 0,
						1, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 1, 0,
						1, 1, 1, 0,
						0, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0,
						0, 1, 1, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_S: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 1, 1, 0,
						1, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 1, 1, 0,
						1, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_Z: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 1, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0,
						1, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 1, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0,
						1, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardGetBlockPieces_SRS(BlockType_Enum block, int rotation, i8 *pieces)
{
	switch (block)
	{
		case BlockType_I: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 1, 1, 1,
						0, 0, 0, 0,
						0, 0, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 1, 0,
						0, 0, 1, 0,
						0, 0, 1, 0,
						0, 0, 1, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 1,
						0, 0, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 1, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_O: {
			i8 block_pieces[] = {
				0, 0, 0, 0,
				0, 1, 1, 0,
				0, 1, 1, 0,
				0, 0, 0, 0
			};
			zt_memCpy(pieces, 16, block_pieces, 16);
		} break;

		case BlockType_T: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 1, 0,
						0, 0, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						0, 1, 1, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_J: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 0, 0, 0,
						1, 1, 1, 0,
						0, 0, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 1, 0,
						0, 1, 0, 0,
						0, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 0,
						0, 0, 1, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_L: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 1, 0,
						1, 1, 1, 0,
						0, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0,
						0, 1, 1, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 1, 0,
						1, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 0, 0,
						0, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_S: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 1, 0,
						1, 1, 0, 0,
						0, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						0, 1, 1, 0,
						0, 0, 1, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 1, 1, 0,
						1, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;

		case BlockType_Z: {
			switch (rotation)
			{
				case 0: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 1, 0,
						0, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 1: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 1, 0,
						0, 1, 1, 0,
						0, 1, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 2: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						1, 1, 0, 0,
						0, 1, 1, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
				case 3: {
					i8 block_pieces[] = {
						0, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0,
						1, 0, 0, 0,
					};
					zt_memCpy(pieces, 16, block_pieces, 16);
				} break;
			}
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardGetBlockPieces(BoardRotationSystem_Enum rotation_system, BlockType_Enum block, int rotation, i8 *pieces)
{
	switch (rotation_system)
	{
		case BoardRotationSystem_GM: {
			_boardGetBlockPieces_GM(block, rotation, pieces);
			return;
		} 

		case BoardRotationSystem_SRS: {
			_boardGetBlockPieces_SRS(block, rotation, pieces);
			return;
		}

		default: zt_assert(false);
	}
}
// ------------------------------------------------------------------------------------------------

ztInternal ztPoint2 _boardPointFromIndex(Board *board, int index, int col_adjust)
{
	int y = zt_convertToi32Floor(index / (r32)board->board_size.x);
	int x = index - (y * board->board_size.x);

	return ztPoint2(x - col_adjust, y);
}

// ------------------------------------------------------------------------------------------------

ztInternal int _boardIndexFromPoint(Board *board, int x, int y)
{
	if (x < 0 || x >= board->board_size.x || y < 0 || y >= board->board_size.y) {
		return -1;
	}

	return (board->board_size.x * y) + x;
}

// ------------------------------------------------------------------------------------------------

ztInternal int _boardIndexAdjust(Board *board, int from_idx, int x, int y)
{
	ztPoint2 point = _boardPointFromIndex(board, from_idx, 0);
	point.x += x;
	point.y += y;

	if (point.y < 0) {
		point.y = 0;
	}

	if (point.x >= board->board_size.x || point.x < 0 || point.y >= board->board_size.y || point.y < 0) {
		return -1;
	}

	return _boardIndexFromPoint(board, point.x, point.y);
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardIsValidBlockPosition(Board *board, int index, int col_adjust, BlockType_Enum block, int rotation)
{
	i8 pieces[16];
	_boardGetBlockPieces(board->rotation_system, block, rotation, pieces);

	zt_fiz(4) {
		int x = i;
		zt_fjz(4) {
			int y = j;
			int pidx = (y * 4) + x;
			if (pieces[pidx] != 0) {
				int idx = _boardIndexAdjust(board, index, x - col_adjust, y);
				if (idx == -1 || board->board[idx] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardProcessRotation(Board *board, BoardRules *rules, int new_rotation)
{
	bool result = false;

	if (_boardIsValidBlockPosition(board, board->active_block_pos_idx, board->active_block_pos_col, board->active_block, new_rotation)) {
		board->active_block_rotation = new_rotation;
		result = true;
	}

	if (!result) {
		ztPoint2 block_point = _boardPointFromIndex(board, board->active_block_pos_idx, 0);

		// check to the right
		int idx_right = _boardIndexFromPoint(board, block_point.x + 1, block_point.y);
		if (_boardIsValidBlockPosition(board, idx_right, board->active_block_pos_col, board->active_block, new_rotation)) {
			board->active_block_rotation = new_rotation;

			if (board->active_block_pos_col > 0) {
				board->active_block_pos_col -= 1;
			}
			else {
				board->active_block_pos_idx = idx_right;
			}
			result = true;
		}

		if (!result) {
			// check to the left
			int idx_left = _boardIndexFromPoint(board, block_point.x - 1, block_point.y);
			if (_boardIsValidBlockPosition(board, idx_left, board->active_block_pos_col, board->active_block, new_rotation)) {
				if (block_point.x <= 0) {
					board->active_block_pos_col -= 1;
				}
				else {
					board->active_block_pos_idx = idx_left;
				}
				board->active_block_rotation = new_rotation;
				result = true;
			}
		}

		if (!result) {
			if (board->active_block == BlockType_I && block_point.x == 0 && board->active_block_pos_col == 2) {
				int idx_right = _boardIndexFromPoint(board, block_point.x + 2, block_point.y);
				if (_boardIsValidBlockPosition(board, idx_right, board->active_block_pos_col, board->active_block, new_rotation)) {
					board->active_block_pos_col  = 0;
					board->active_block_rotation = new_rotation;
					result = true;
				}
			}
		}

		if (!result) {
			if (board->active_block == BlockType_I && block_point.x == board->board_size.x - 2) {
				int idx_left = _boardIndexFromPoint(board, block_point.x - 2, block_point.y);
				if (_boardIsValidBlockPosition(board, idx_left, board->active_block_pos_col, board->active_block, new_rotation)) {
					if (board->active_block_pos_col > 0) {
						board->active_block_pos_col -= 1;
					}
					else {
						board->active_block_pos_idx = idx_left;
						board->active_block_pos_col = 0;
					}
					board->active_block_rotation = new_rotation;
					result = true;
				}
			}
		}

	}

	if (result && board->time_to_lock_soft > 0) {
		board->time_to_lock_soft = rules->lock_time_soft;
	}

	if (result && board->audio_block_rotate != ztInvalidID) {
		zt_audioClipPlayOnce(board->audio_block_rotate);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardRotateBlockLeft(Board *board, BoardRules *rules)
{
	int new_rotation = board->active_block_rotation - 1;
	if (new_rotation < 0) {
		new_rotation += 4;
	}

	if (_boardProcessRotation(board, rules, new_rotation)) {
		board->stats.rotations_left += 1;
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardRotateBlockRight(Board *board, BoardRules *rules)
{
	int new_rotation = (board->active_block_rotation + 1) % 4;

	if (_boardProcessRotation(board, rules, new_rotation)) {
		board->stats.rotations_right += 1;
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardMoveBlockLeft(Board *board, BoardRules *rules)
{
	if (board->active_block_pos_col >= 2) {
		return false;
	}

	int new_position = _boardIndexAdjust(board, board->active_block_pos_idx, -1 - board->active_block_pos_col, 0);
	if (new_position == -1) {
		new_position = board->active_block_pos_idx;
	}

	int col_adjust = 0;
	if (new_position == board->active_block_pos_idx) {
		col_adjust = 1;
	}

	if (_boardIsValidBlockPosition(board, new_position, board->active_block_pos_col + col_adjust, board->active_block, board->active_block_rotation)) {
		board->active_block_pos_idx = new_position;
		board->active_block_pos_col += col_adjust;

		if (board->time_to_lock_soft > 0) {
			board->time_to_lock_soft = rules->lock_time_soft;
		}

		if (board->audio_block_move != ztInvalidID) {
			zt_audioClipPlayOnce(board->audio_block_move);
		}

		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardMoveBlockRight(Board *board, BoardRules *rules)
{
	int new_position = _boardIndexAdjust(board, board->active_block_pos_idx, 1 - board->active_block_pos_col, 0);
	if (new_position == -1) {
		new_position = board->active_block_pos_idx;
	}

	int col_adjust = 0;
	if (new_position == board->active_block_pos_idx) {
		col_adjust = -1;
	}

	if (_boardIsValidBlockPosition(board, new_position, board->active_block_pos_col + col_adjust, board->active_block, board->active_block_rotation)) {
		board->active_block_pos_idx = new_position;
		board->active_block_pos_col += col_adjust;

		if (board->time_to_lock_soft > 0) {
			board->time_to_lock_soft = rules->lock_time_soft;
		}

		if (board->audio_block_move != ztInvalidID) {
			zt_audioClipPlayOnce(board->audio_block_move);
		}

		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal BlockType_Enum _boardGetRandomBlock(Board *board)
{
	int total_block_count = 0;
	zt_fize(board->stats.block_count) {
		total_block_count += board->stats.block_count[i];
	}

	switch (board->randomizer_type)
	{
		case BoardRandomizer_PureRandom: {
			return (BlockType_Enum)zt_randomInt(&board->randomizer, BlockType_I, BlockType_MAX);
		} break;

		case BoardRandomizer_PoolGMA:
		case BoardRandomizer_Pool: {
			if (board->randomizer_pool.pool_idx < 0) {
				BlockType_Enum blocks[] = { BlockType_I, BlockType_O, BlockType_T, BlockType_J, BlockType_L, BlockType_S, BlockType_Z };

				zt_fize(blocks) {
					int idx = ++board->randomizer_pool.pool_idx;

					while (true) {
						int rand_val = zt_randomInt(&board->randomizer, 0, zt_elementsOf(blocks));
						if (blocks[rand_val] != BlockType_Invalid) {
							if (idx == 0 && board->randomizer_type == BoardRandomizer_PoolGMA && total_block_count == 0) {
								switch (blocks[rand_val])
								{
									case BlockType_O:
									case BlockType_S:
									case BlockType_Z:
										continue;
								}
							}
							board->randomizer_pool.pool[idx] = blocks[rand_val];
							blocks[rand_val] = BlockType_Invalid;
							break;
						}
					}
				}
				board->randomizer_pool.pool_idx = 0;
			}

			BlockType_Enum result = board->randomizer_pool.pool[board->randomizer_pool.pool_idx++];

			if (board->randomizer_pool.pool_idx >= zt_elementsOf(board->randomizer_pool.pool)) {
				board->randomizer_pool.pool_idx = -1;
			}

			return result;

		} break;

		case BoardRandomizer_GM1:
		case BoardRandomizer_GM2P: {
			BlockType_Enum result = BlockType_Invalid;

			if (total_block_count == 0 && board->randomizer_gm.previous[0] == BlockType_Invalid) {
				BlockType_Enum list[] = { BlockType_I, BlockType_T, BlockType_J, BlockType_L };
				result = list[zt_randomInt(&board->randomizer, 0, zt_elementsOf(list))];
			}
			else {
				result = (BlockType_Enum)zt_randomInt(&board->randomizer, BlockType_I, BlockType_MAX);

				int tries = board->randomizer_type == BoardRandomizer_GM1 ? 4 : 6;

				zt_fjzr(tries - 1) {
					bool found_duplicate = false;
					zt_fize(board->randomizer_gm.previous) {
						if (board->randomizer_gm.previous[i] == result) {
							found_duplicate = true;
							break;
						}
					}

					if (found_duplicate) {
						result = (BlockType_Enum)zt_randomInt(&board->randomizer, BlockType_I, BlockType_MAX);
					}
					else break;
				}
			}

			zt_fizre(board->randomizer_gm.previous) {
				if (i > 0) board->randomizer_gm.previous[i] = board->randomizer_gm.previous[i - 1];
			}
			board->randomizer_gm.previous[0] = result;

			return result;
		} break;
	}

	return BlockType_Invalid;
}

// ------------------------------------------------------------------------------------------------

ztInternal BlockType_Enum _boardGetNextBlock(Board *board, BoardRules *rules)
{
	BlockType_Enum result = BlockType_Invalid;

	if (rules->max_next == 0) {
		result = _boardGetRandomBlock(board);
	}

	if (result == BlockType_Invalid) {
		BlockType_Enum next = board->next[0];
		if (next == BlockType_Invalid) {
			next = _boardGetRandomBlock(board);
		}

		zt_fiz(zt_elementsOf(board->next) - 1) {
			board->next[i] = board->next[i + 1];
		}
		board->next[zt_elementsOf(board->next) - 1] = BlockType_Invalid;


		zt_fiz(zt_min(zt_elementsOf(board->next), rules->max_next)) {
			if (board->next[i] == BlockType_Invalid) {
				board->next[i] = _boardGetRandomBlock(board);
			}
		}

		result = next;
	}

	if (result != BlockType_Invalid) {
		board->stats.block_count[result] += 1;

		zt_fize(board->stats.block_drought) {
			if (i == result) {
				board->stats.block_drought[i] = 0;
			}
			else {
				board->stats.block_drought[i] += 1;
			}
		}
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardCycleBlocks(Board *board, int max_next, BlockType_Enum next)
{
	zt_assertReturnOnFail(next > BlockType_Invalid && next < BlockType_MAX);
	board->active_block          = next;
	board->active_block_pos_idx  = zt_convertToi32Floor((board->board_size.x / 2.f) - 2);
	board->active_block_pos_col  = 0;
	board->active_block_rotation = 0;
	board->block_has_held        = false;
	board->hard_drop             = false;

	i8 pieces[16];
	_boardGetBlockPieces(board->rotation_system, next, 0, pieces);

	if (!_boardIsValidBlockPosition(board, board->active_block_pos_idx, board->active_block_pos_col, next, board->active_block_rotation)) {
		board->current_state = BoardState_Failed;
	}
	else {
		board->current_state = BoardState_Falling;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardProcessGravityDrop(Board *board, BoardRules *rules)
{
	int next_idx = _boardIndexAdjust(board, board->active_block_pos_idx, 0, 1);
	if (_boardIsValidBlockPosition(board, next_idx, board->active_block_pos_col, board->active_block, board->active_block_rotation)) {
		board->active_block_pos_idx = next_idx;

		board->time_to_lock_soft = 0;
		board->time_to_lock_hard = 0;
	}
	else {
		if (board->time_to_lock_soft == 0 && board->time_to_lock_hard == 0) {
			board->time_to_lock_soft = rules->lock_time_soft;
			board->time_to_lock_hard = rules->lock_time_hard;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardProcessBlockLock(Board *board, r32 dt)
{
	if (board->time_to_lock_soft != 0 || board->time_to_lock_hard != 0 || board->hard_drop) {
		board->time_to_lock_soft -= dt;
		board->time_to_lock_hard -= dt;

		if (board->time_to_lock_soft < 0 || board->time_to_lock_hard < 0 || board->hard_drop) {
			// piece drop
			i8 pieces[16];
			_boardGetBlockPieces(board->rotation_system, board->active_block, board->active_block_rotation, pieces);

			zt_fiz(4) {
				int x = i;
				zt_fjz(4) {
					int y = j;
					int pidx = (y * 4) + x;
					if (pieces[pidx] != 0) {
						int idx = _boardIndexAdjust(board, board->active_block_pos_idx, x - board->active_block_pos_col, y);
						if (idx != -1) {
							board->board[idx] = board->active_block;
						}
					}
				}
			}

			board->active_block      = BlockType_Invalid;
			board->current_state     = BoardState_Processing;
			board->time_to_lock_soft = 0;
			board->time_to_lock_hard = 0;

			if (board->audio_block_drop != ztInvalidID) {
				zt_audioClipPlayOnce(board->audio_block_drop);
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal r32 _boardInputDelay(BoardRules *rules, int movement_type)
{
	switch (movement_type)
	{
		case BoardInput_RotateLeft:
		case BoardInput_RotateRight:
			return rules->input_delay_rotation;

		case BoardInput_HardDrop:
			return rules->input_delay_hard_drop;
	}

	return rules->input_delay_move;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardCheckForLines(Board *board, BoardRules *rules)
{
	int cleared_lines = 0;

	zt_fiz(board->board_size.y) {
		int start = i * board->board_size.x;

		bool found_empty = false;
		zt_fjz(board->board_size.x) {
			int x = j + start;

			if (board->board[x] == 0) {
				found_empty = true;
				break;
			}
		}

		if (!found_empty) {
			board->lines_clearing[cleared_lines++] = i;
		}
	}

	if (cleared_lines > 0) {
		board->current_state = BoardState_Clearing;
		board->time_to_clear = rules->clear_time;

		if (board->audio_line_clear[cleared_lines - 1] != ztInvalidID) {
			zt_audioClipPlayOnce(board->audio_line_clear[cleared_lines - 1]);
		}

	}
	else {
		board->current_state = BoardState_Waiting;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardClearLines(Board *board, r32 dt)
{
	board->time_to_clear -= dt;
	if (board->time_to_clear < 0) {
		board->time_to_clear = 0;

		int cleared = 0;
		zt_fize(board->lines_clearing) {
			if (board->lines_clearing[i] == -1) {
				continue;
			}

			cleared += 1;
			board->stats.lines_cleared += 1;

			for (int j = board->lines_clearing[i]; j > 0; --j) {
				zt_fkz(board->board_size.x) {
					int idx_this = (j * board->board_size.x) + k;
					int idx_prev = ((j - 1) * board->board_size.x) + k;

					board->board[idx_this] = board->board[idx_prev];
				}
			}
			board->lines_clearing[i] = -1;
		}

		if (cleared > 0) {
			board->stats.clears[cleared - 1] += 1;
		}

		board->current_state = BoardState_Waiting;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardRenderBlockPiece(BlockType_Enum block, ztDrawList *draw_list, ztVec2 position)
{
	ztVec4 color = ztVec4::one;
	switch (block)
	{
		case BlockType_I: color = ztVec4(146 / 255.f, 255 / 255.f, 255 / 255.f, 1); break;
		case BlockType_O: color = ztVec4(249 / 255.f, 255 / 255.f, 146 / 255.f, 1); break;
		case BlockType_T: color = ztVec4(210 / 255.f, 146 / 255.f, 255 / 255.f, 1); break;
		case BlockType_J: color = ztVec4(146 / 255.f, 146 / 255.f, 255 / 255.f, 1); break;
		case BlockType_L: color = ztVec4(255 / 255.f, 205 / 255.f, 146 / 255.f, 1); break;
		case BlockType_S: color = ztVec4(146 / 255.f, 255 / 255.f, 146 / 255.f, 1); break;
		case BlockType_Z: color = ztVec4(255 / 255.f, 146 / 255.f, 146 / 255.f, 1); break;

		case BlockType_Invalid: color = ztVec4(1,1,1, .25f); break;
		default: color = ztVec4(.5f, .5f, .5f, .25f); 
	}

	zt_drawListPushColor(draw_list, color);
	{
		zt_drawListAddFilledRect2D(draw_list, ztVec3(position, 0), ztVec2(.5f, .5f), ztVec2(0, 0), ztVec2(1, 1));
	}
	zt_drawListPopColor(draw_list);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardRenderBlockPiece(Board *board, BlockType_Enum block, ztDrawList *draw_list, int at_index)
{
	ztVec2 pos(board->board_size.x * -.25f + .25f, (board->board_size.y * .25f - .25f) + (BOARD_TOP_BUFFER_COUNT / 2.f - .5f));

	ztPoint2 point = _boardPointFromIndex(board, at_index, 0);

	pos.x += point.x * .5f;
	pos.y -= point.y * .5f;

	_boardRenderBlockPiece(block, draw_list, pos);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardRenderBlock(Board *board, BlockType_Enum block, ztDrawList *draw_list, int at_index, int col_adjust, int rotation)
{
	i8 pieces[16];
	_boardGetBlockPieces(board->rotation_system, block, rotation, pieces);

	//_boardRenderBlockPiece(board, BlockType_MAX, draw_list, at_index);

	int min_idx = BOARD_TOP_BUFFER_COUNT * board->board_size.x;

	zt_fiz(4) {
		int x = i;
		zt_fjz(4) {
			int y = j;
			int pidx = (y * 4) + x;
			if (pieces[pidx] != 0) {
				int idx = _boardIndexAdjust(board, at_index, x - col_adjust, y);
				if (idx != -1 && idx >= min_idx) {
					_boardRenderBlockPiece(board, block, draw_list, idx);
				}
			}
			//else if(pidx != 0) {
			//	int idx = _boardIndexAdjust(board, at_index, x - col_adjust, y);
			//	if (idx != -1) {
			//		_boardRenderBlockPiece(board, BlockType_Invalid, draw_list, idx);
			//	}
			//}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal int _boardGetBlockHardDropPositionIndex(Board *board)
{
	int active_idx = board->active_block_pos_idx;
	ztPoint2 point = _boardPointFromIndex(board, active_idx, 0);

	int idx_prev = board->active_block_pos_idx;
	for (int y = point.y + 1; y < board->board_size.y; ++y) {
		int idx = _boardIndexFromPoint(board, point.x, y);
		if (!_boardIsValidBlockPosition(board, idx, board->active_block_pos_col, board->active_block, board->active_block_rotation)) {
			break;
		}
		idx_prev = idx;
	}

	return idx_prev;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

Board boardMake(int width, int height, BoardRandomizer_Enum randomizer, BoardRotationSystem_Enum rotation_system)
{
	Board board = {};
	board.board = zt_mallocStructArray(i16, width * (height + BOARD_TOP_BUFFER_COUNT));
	board.board_size = ztPoint2(width, height + BOARD_TOP_BUFFER_COUNT);
	board.rotation_system = rotation_system;
	
	srand((unsigned int)time(0));
	zt_randomInit(&board.randomizer, rand());

	board.randomizer_type = randomizer;

	boardReset(&board);

	zt_fize(board.audio_line_clear) {
		board.audio_line_clear[i] = ztInvalidID;
	}

	return board;
}

// ------------------------------------------------------------------------------------------------

void boardFree(Board *board)
{
	if (board == nullptr) {
		return;
	}

	zt_free(board->board);
}

// ------------------------------------------------------------------------------------------------

void boardReset(Board *board)
{
	zt_fiz(board->board_size.x * board->board_size.y) {
		board->board[i] = BlockType_Invalid;
	}

	board->active_block = BlockType_Invalid;
	board->current_state = BoardState_Waiting;

	board->hold = BlockType_Invalid;

	zt_fize(board->next) {
		board->next[i] = BlockType_Invalid;
	}
	zt_fize(board->prev) {
		board->prev[i] = BlockType_Invalid;
	}

	board->time_to_drop      = 0;
	board->time_to_clear     = 0;
	board->time_to_lock_soft = 0;
	board->time_to_lock_hard = 0;

	zt_fize(board->lines_clearing) {
		board->lines_clearing[i] = -1;
	}

	zt_fize(board->input_hold_time) {
		board->input_hold_time[i] = 0;
	}

	board->stats = {};

	zt_fize(board->stats.block_count) {
		board->stats.block_count[i] = 0;
	}
	zt_fize(board->stats.block_drought) {
		board->stats.block_drought[i] = 0;
	}

	zt_fize(board->stats.clears) {
		board->stats.clears[i] = 0;
	}

	switch (board->randomizer_type)
	{
		case BoardRandomizer_PureRandom: {
			// do nothing
		} break;

		case BoardRandomizer_PoolGMA:
		case BoardRandomizer_Pool: {
			board->randomizer_pool.pool_idx = -1;
		} break;

		case BoardRandomizer_GM1: {
			board->randomizer_gm.previous[0] = BlockType_Z;
			board->randomizer_gm.previous[1] = BlockType_Z;
			board->randomizer_gm.previous[2] = BlockType_Z;
			board->randomizer_gm.previous[3] = BlockType_Z;
		} break;

		case BoardRandomizer_GM2P : {
			board->randomizer_gm.previous[0] = BlockType_Z;
			board->randomizer_gm.previous[1] = BlockType_S;
			board->randomizer_gm.previous[2] = BlockType_S;
			board->randomizer_gm.previous[3] = BlockType_Z;
		} break;

		default: zt_assert(false);
	}
}

// ------------------------------------------------------------------------------------------------

BoardState_Enum boardUpdate(Board *board, r32 dt, BoardRules *rules, BoardInput_Enum *inputs, int inputs_count)
{
	zt_returnValOnNull(board, BoardState_Invalid);

	board->stats.time_played += dt;

	if (board->current_state == BoardState_Waiting && board->active_block == BlockType_Invalid) {
		_boardCycleBlocks(board, rules->max_next, _boardGetNextBlock(board, rules));

		if (board->current_state == BoardState_Failed) {
			boardReset(board);
			return board->current_state;
		}
	}

	if (board->current_state == BoardState_Processing) {
		_boardCheckForLines(board, rules);
	}

	if (board->current_state == BoardState_Clearing) {
		_boardClearLines(board, dt);
	}
	else {
		bool pressed[BoardInput_MAX];
		bool repeating[BoardInput_MAX];
		zt_fize(pressed) {
			pressed[i] = false;
			repeating[i] = false;
		}

		zt_fize(board->input_hold_time) {
			if (board->input_hold_time[i] != 0) {
				board->input_hold_time[i] -= dt;
				if (board->input_hold_time[i] < 0) {
					board->input_hold_time[i] = 0;
				}
				repeating[i] = true;
			}
		}

		bool soft_drop = false;

		zt_fiz(inputs_count) {
			pressed[inputs[i]] = true;

			if (board->input_hold_time[inputs[i]] == 0) {
				board->input_hold_time[inputs[i]] = _boardInputDelay(rules, inputs[i]) * (repeating[inputs[i]] ? 1 : 3);

				switch (inputs[i])
				{
					case BoardInput_MoveLeft: {
						_boardMoveBlockLeft(board, rules);
					} break;

					case BoardInput_MoveRight: {
						_boardMoveBlockRight(board, rules);
					} break;

					case BoardInput_RotateLeft: {
						_boardRotateBlockLeft(board, rules);
					} break;

					case BoardInput_RotateRight: {
						_boardRotateBlockRight(board, rules);
					} break;

					case BoardInput_SoftDrop: {
						soft_drop = true;
					} break;

					case BoardInput_HardDrop: {
						// check to make sure we haven't moved this frame
						bool has_moved = false;
						zt_fjz(inputs_count) {
							if (inputs[j] == BoardInput_MoveLeft || inputs[j] == BoardInput_MoveRight) {
								has_moved = true;
								break;
							}
						}
						if (!has_moved) {
							board->active_block_pos_idx = _boardGetBlockHardDropPositionIndex(board);
							board->time_to_drop = rules->drop_time;
							board->hard_drop = true;
							board->stats.hard_drops += 1;
						}
					} break;

					case BoardInput_Hold: {
						if (board->block_has_held == false) {
							if (board->hold != BlockType_Invalid) {
								BlockType_Enum next = board->hold;
								board->hold = board->active_block;

								_boardCycleBlocks(board, rules->max_next, next);
							}
							else {
								board->hold = board->active_block;
								_boardCycleBlocks(board, rules->max_next, _boardGetNextBlock(board, rules));
							}

							board->block_has_held = true;
						}
					} break;
				}
			}
		}

		zt_fize(pressed) {
			if (!pressed[i]) {
				board->input_hold_time[i] = 0;
			}
		}

		if (board->current_state == BoardState_Falling) {
			board->time_to_drop += dt;
			r32 drop_time = soft_drop ? rules->drop_time_soft : rules->drop_time;
			if (board->time_to_drop >= drop_time) {
				board->time_to_drop -= drop_time;
				_boardProcessGravityDrop(board, rules);
			}

			_boardProcessBlockLock(board, dt);
		}
	}

	return BoardState_Falling;
}

// ------------------------------------------------------------------------------------------------

void boardRender(Board *board, ztDrawList *draw_list, ztTextureID tex_block, ztTextureID tex_block_ghost)
{
	// draw the ghost block where the hard drop would go
	if (tex_block_ghost != ztInvalidID) {
		zt_drawListPushTexture(draw_list, tex_block_ghost);
		{
			_boardRenderBlock(board, board->active_block, draw_list, _boardGetBlockHardDropPositionIndex(board), board->active_block_pos_col, board->active_block_rotation);
		}
		zt_drawListPopTexture(draw_list);
	}

	zt_drawListPushTexture(draw_list, tex_block);
	{
		// draw the board
		zt_fiz(board->board_size.x * board->board_size.y) {
			if (board->board[i] == 0) {
				//_boardRenderBlockPiece(board, BlockType_MAX, draw_list, i);
				continue;
			}

			i16 board_piece = board->board[i];
			_boardRenderBlockPiece(board, (BlockType_Enum)board_piece, draw_list, i);
		}

		if (board->active_block != BlockType_Invalid) {
			_boardRenderBlock(board, board->active_block, draw_list, board->active_block_pos_idx, board->active_block_pos_col, board->active_block_rotation);
		}
	}
	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------

void boardRenderBlock(BoardRotationSystem_Enum rotation_system, BlockType_Enum block, ztDrawList *draw_list, ztVec2 position, int rotation, ztTextureID tex_block)
{
	i8 pieces[16];
	_boardGetBlockPieces(rotation_system, block, rotation, pieces);

	position.y += .5f;
	position.x -= .5f;

	if (block == BlockType_I) {
		if (rotation == 0 || rotation == 2) {
			position.x -= .25f;
			position.y -= .25f;
		}
	}
	if (block == BlockType_O) {
		position.x -= .25f;
	}

	zt_drawListPushTexture(draw_list, tex_block);
	{
		zt_fiz(4) {
			int x = i;
			zt_fjz(4) {
				int y = j;
				int pidx = (y * 4) + x;
				if (pieces[pidx] != 0) {
					_boardRenderBlockPiece(block, draw_list, position + ztVec2(x / 2.f, y / -2.f));
				}
			}
		}
	}
	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------
