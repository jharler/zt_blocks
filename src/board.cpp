#include "board.h"

// ------------------------------------------------------------------------------------------------

ztInternal void _boardGetBlockPieces(BlockType_Enum block, int rotation, i8 *pieces, int *center_idx, int *center_x, int *center_y)
{
	switch (block)
	{
		case BlockType_Straight: {
			if (center_idx) *center_idx = 10;
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

		case BlockType_Square: {
			if (center_idx) *center_idx = 10;
			i8 block_pieces[] = {
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 1, 1, 0,
				0, 1, 1, 0
			};
			zt_memCpy(pieces, 16, block_pieces, 16);
		} break;

		case BlockType_T: {
			if (center_idx) *center_idx = 9;
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
			if (center_idx) *center_idx = 9;
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
			if (center_idx) *center_idx = 9;
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
			if (center_idx) *center_idx = 9;
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
			if (center_idx) *center_idx = 9;
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

	if (center_idx) {
		if (center_y) *center_y = zt_convertToi32Floor(*center_idx / 4.f);
		if (center_x && center_y) *center_x = *center_idx - (*center_y * 4);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal ztPoint2 _boardPointFromIndex(Board *board, int index)
{
	int y = zt_convertToi32Floor(index / (r32)board->board_size.x);
	int x = index - (y * board->board_size.x);

	return ztPoint2(x, y);
}

// ------------------------------------------------------------------------------------------------

ztInternal int _boardIndexFromPoint(Board *board, int x, int y)
{
	return (board->board_size.x * y) + x;
}

// ------------------------------------------------------------------------------------------------

ztInternal int _boardIndexAdjust(Board *board, int from_idx, int x, int y)
{
	ztPoint2 point = _boardPointFromIndex(board, from_idx);
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

ztInternal bool _boardIsValidBlockPosition(Board *board, int index, BlockType_Enum block, int rotation)
{
	int center_idx, center_x, center_y;
	i8 pieces[16];
	_boardGetBlockPieces(block, rotation, pieces, &center_idx, &center_x, &center_y);

	ztPoint2 block_point = _boardPointFromIndex(board, index);

	zt_fiz(4) {
		int x = i;
		zt_fjz(4) {
			int y = j;
			int pidx = (y * 4) + x;
			if (pieces[pidx] != 0) {
				int idx = _boardIndexAdjust(board, index, x - center_x, y - center_y);
				if (idx == -1 || board->board[idx] != 0) {
					ztPoint2 board_point = _boardPointFromIndex(board, idx);
					return false;
				}
			}
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardRotateBlockLeft(Board *board)
{
	int new_rotation = board->active_block_rotation - 1;
	if (new_rotation < 0) {
		new_rotation += 4;
	}

	if (_boardIsValidBlockPosition(board, board->active_block_position, board->active_block, new_rotation)) {
		board->active_block_rotation = new_rotation;
		return true;
	}

	ztPoint2 block_point = _boardPointFromIndex(board, board->active_block_position);

	// check to the right
	int idx_right = _boardIndexFromPoint(board, block_point.x + 1, block_point.y);
	if (_boardIsValidBlockPosition(board, idx_right, board->active_block, new_rotation)) {
		board->active_block_position = idx_right;
		board->active_block_rotation = new_rotation;
	}

	// check to the left
	int idx_left = _boardIndexFromPoint(board, block_point.x - 1, block_point.y);
	if (_boardIsValidBlockPosition(board, idx_left, board->active_block, new_rotation)) {
		board->active_block_position = idx_left;
		board->active_block_rotation = new_rotation;
	}

	if (board->active_block == BlockType_Straight && block_point.x == 0) {
		int idx_right = _boardIndexFromPoint(board, block_point.x + 2, block_point.y);
		if (_boardIsValidBlockPosition(board, idx_right, board->active_block, new_rotation)) {
			board->active_block_position = idx_right;
			board->active_block_rotation = new_rotation;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardRotateBlockRight(Board *board)
{
	int new_rotation = (board->active_block_rotation + 1) % 4;

	if (_boardIsValidBlockPosition(board, board->active_block_position, board->active_block, new_rotation)) {
		board->active_block_rotation = new_rotation;
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardMovelockLeft(Board *board)
{
	int new_position = _boardIndexAdjust(board, board->active_block_position, -1, 0);
	if (new_position == -1) {
		return false;
	}

	if (_boardIsValidBlockPosition(board, new_position, board->active_block, board->active_block_rotation)) {
		board->active_block_position = new_position;
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _boardMoveBlockRight(Board *board)
{
	int new_position = _boardIndexAdjust(board, board->active_block_position, 1, 0);
	if (new_position == -1) {
		return false;
	}

	if (_boardIsValidBlockPosition(board, new_position, board->active_block, board->active_block_rotation)) {
		board->active_block_position = new_position;
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal BlockType_Enum _boardGetNextBlock(Board *board, BoardRules *rules)
{
	if (rules->max_next == 0) {
		return (BlockType_Enum)zt_randomInt(&board->randomizer, BlockType_Straight, BlockType_MAX);
	}

	BlockType_Enum next = board->next[0];
	if (next == BlockType_Invalid) {
		next = (BlockType_Enum)zt_randomInt(&board->randomizer, BlockType_Straight, BlockType_MAX);
	}

	zt_fiz(zt_elementsOf(board->next) - 1) {
		board->next[i] = board->next[i + 1];
	}
	board->next[zt_elementsOf(board->next) - 1] = BlockType_Invalid;


	zt_fiz(zt_min(zt_elementsOf(board->next), rules->max_next)) {
		if (board->next[i] == BlockType_Invalid) {
			board->next[i] = (BlockType_Enum)zt_randomInt(&board->randomizer, BlockType_Straight, BlockType_MAX);
		}
	}

	return next;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardCycleBlocks(Board *board, int max_next, BlockType_Enum next)
{
	zt_assertReturnOnFail(next > BlockType_Invalid && next < BlockType_MAX);
	board->active_block = next;
	board->active_block_rotation = 0;
	board->active_block_position = zt_convertToi32Floor(board->board_size.x / 2.f);
	board->block_has_held = false;

	if (!_boardIsValidBlockPosition(board, board->active_block_position, next, board->active_block_rotation)) {
		board->current_state = BoardState_Failed;
	}
	else {
		board->current_state = BoardState_Falling;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardProcessGravityDrop(Board *board)
{
	int next_idx = _boardIndexAdjust(board, board->active_block_position, 0, 1);
	if (_boardIsValidBlockPosition(board, next_idx, board->active_block, board->active_block_rotation)) {
		board->active_block_position = next_idx;
	}
	else {
		// piece drop
		int center_idx, center_x, center_y;
		i8 pieces[16];
		_boardGetBlockPieces(board->active_block, board->active_block_rotation, pieces, &center_idx, &center_x, &center_y);

		zt_fiz(4) {
			int x = i;
			zt_fjz(4) {
				int y = j;
				int pidx = (y * 4) + x;
				if (pieces[pidx] != 0) {
					int idx = _boardIndexAdjust(board, board->active_block_position, x - center_x, y - center_y);
					if (idx != -1) {
						board->board[idx] = board->active_block;
					}
				}
			}
		}

		board->active_block = BlockType_Invalid;
		board->current_state = BoardState_Processing;
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

		zt_fize(board->lines_clearing) {
			if (board->lines_clearing[i] == -1) {
				continue;
			}

			for (int j = board->lines_clearing[i]; j > 0; --j) {
				zt_fkz(board->board_size.x) {
					int idx_this = (j * board->board_size.x) + k;
					int idx_prev = ((j - 1) * board->board_size.x) + k;

					board->board[idx_this] = board->board[idx_prev];
				}
			}
			board->lines_clearing[i] = -1;
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
		case BlockType_Straight: color = ztVec4(146 / 255.f, 255 / 255.f, 255 / 255.f, 1); break;
		case BlockType_Square: color = ztVec4(249 / 255.f, 255 / 255.f, 146 / 255.f, 1); break;
		case BlockType_T: color = ztVec4(210 / 255.f, 146 / 255.f, 255 / 255.f, 1); break;
		case BlockType_J: color = ztVec4(146 / 255.f, 146 / 255.f, 255 / 255.f, 1); break;
		case BlockType_L: color = ztVec4(255 / 255.f, 205 / 255.f, 146 / 255.f, 1); break;
		case BlockType_S: color = ztVec4(255 / 255.f, 146 / 255.f, 146 / 255.f, 1); break;
		case BlockType_Z: color = ztVec4(146 / 255.f, 255 / 255.f, 146 / 255.f, 1); break;
		default: return;
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
	ztVec2 pos(board->board_size.x * -.25f + .25f, board->board_size.y * .25f - .25f);

	ztPoint2 point = _boardPointFromIndex(board, at_index);

	pos.x += point.x * .5f;
	pos.y -= point.y * .5f;

	_boardRenderBlockPiece(block, draw_list, pos);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardRenderBlock(Board *board, BlockType_Enum block, ztDrawList *draw_list, int at_index, int rotation)
{
	int center = 0, center_x, center_y;
	i8 pieces[16];
	_boardGetBlockPieces(block, rotation, pieces, &center, &center_x, &center_y);

	zt_fiz(4) {
		int x = i;
		zt_fjz(4) {
			int y = j;
			int pidx = (y * 4) + x;
			if (pieces[pidx] != 0) {
				int idx = _boardIndexAdjust(board, at_index, x - center_x, y - center_y);
				if (idx != -1) {
					_boardRenderBlockPiece(board, block, draw_list, idx);
				}
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal int _boardGetBlockHardDropPositionIndex(Board *board)
{
	int active_idx = board->active_block_position;
	ztPoint2 point = _boardPointFromIndex(board, active_idx);

	int idx_prev = board->active_block_position;
	for (int y = point.y + 1; y < board->board_size.y; ++y) {
		int idx = _boardIndexFromPoint(board, point.x, y);
		if (!_boardIsValidBlockPosition(board, idx, board->active_block, board->active_block_rotation)) {
			break;
		}
		idx_prev = idx;
	}

	return idx_prev;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

Board boardMake(int width, int height)
{
	Board board = {};
	board.board = zt_mallocStructArray(i16, width * height);
	board.board_size = ztPoint2(width, height);
	
	srand(0);
	zt_randomInit(&board.randomizer, rand());

	zt_fiz(width * height) {
		board.board[i] = BlockType_Invalid;
	}

	zt_fize(board.next) {
		board.next[i] = BlockType_Invalid;
	}
	zt_fize(board.prev) {
		board.prev[i] = BlockType_Invalid;
	}

	zt_fize(board.lines_clearing) {
		board.lines_clearing[i] = -1;
	}

	zt_fize(board.input_hold_time) {
		board.input_hold_time[i] = 0;
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
		board->board[i] = 0;
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

	board->time_to_drop = 0;
	board->time_to_clear = 0;

	zt_fize(board->input_hold_time) {
		board->input_hold_time[i] = 0;
	}
}

// ------------------------------------------------------------------------------------------------

BoardState_Enum boardUpdate(Board *board, r32 dt, BoardRules *rules, BoardInput_Enum *inputs, int inputs_count)
{
	zt_returnValOnNull(board, BoardState_Invalid);

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
						_boardMovelockLeft(board);
					} break;

					case BoardInput_MoveRight: {
						_boardMoveBlockRight(board);
					} break;

					case BoardInput_RotateLeft: {
						_boardRotateBlockLeft(board);
					} break;

					case BoardInput_RotateRight: {
						_boardRotateBlockRight(board);
					} break;

					case BoardInput_SoftDrop: {
						soft_drop = true;
					} break;

					case BoardInput_HardDrop: {
						board->active_block_position = _boardGetBlockHardDropPositionIndex(board);
						board->time_to_drop = rules->drop_time;
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
				_boardProcessGravityDrop(board);
			}
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
			_boardRenderBlock(board, board->active_block, draw_list, _boardGetBlockHardDropPositionIndex(board), board->active_block_rotation);
		}
		zt_drawListPopTexture(draw_list);
	}

	zt_drawListPushTexture(draw_list, tex_block);
	{
		// draw the board
		zt_fiz(board->board_size.x * board->board_size.y) {
			if (board->board[i] == 0) {
				continue;
			}

			i16 board_piece = board->board[i];
			_boardRenderBlockPiece(board, (BlockType_Enum)board_piece, draw_list, i);
		}

		if (board->active_block != BlockType_Invalid) {
			_boardRenderBlock(board, board->active_block, draw_list, board->active_block_position, board->active_block_rotation);
		}
	}
	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------

void boardRenderBlock(BlockType_Enum block, ztDrawList *draw_list, ztVec2 position, int rotation, ztTextureID tex_block)
{
	int center = 0, center_x, center_y;
	i8 pieces[16];
	_boardGetBlockPieces(block, rotation, pieces, &center, &center_x, &center_y);

	if (block == BlockType_Straight) {
		if (rotation == 0 || rotation == 2) {
			position.x += .25f;
		}
		else {
			position.y += .25f;
		}
	}
	if (block == BlockType_Square) {
		position.x += .25f;
	}

	zt_drawListPushTexture(draw_list, tex_block);
	{
		zt_fiz(4) {
			int x = i;
			zt_fjz(4) {
				int y = j;
				int pidx = (y * 4) + x;
				if (pieces[pidx] != 0) {

					int off_x = x - center_x;
					int off_y = y - center_y;

					_boardRenderBlockPiece(block, draw_list, position + ztVec2(off_x / 2.f, off_y / -2.f));
				}
			}
		}
	}
	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------