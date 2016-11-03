#include "board.h"

// ------------------------------------------------------------------------------------------------

ztPoint2 boardPointFromIndex(Board *board, int index)
{
	int y = zt_convertToi32Floor(index / (r32)board->board_size.x);
	int x = index - (y * board->board_size.x);

	return ztPoint2(x, y);
}

// ------------------------------------------------------------------------------------------------

int boardIndexFromPoint(Board *board, int x, int y)
{
	return (board->board_size.x * y) + x;
}

// ------------------------------------------------------------------------------------------------

int boardIndexAdjust(Board *board, int from_idx, int x, int y)
{
	ztPoint2 point = boardPointFromIndex(board, from_idx);
	point.x += x;
	point.y += y;

	if (point.x >= board->board_size.x || point.x < 0 || point.y >= board->board_size.y || point.y < 0) {
		return -1;
	}

	return boardIndexFromPoint(board, point.x, point.y);
}

// ------------------------------------------------------------------------------------------------

Board boardMake(int width, int height)
{
	Board board = {};
	board.board = zt_mallocStructArray(i16, width * height);
	board.board_size = ztPoint2(width, height);

	zt_fiz(width * height) {
		board.board[i] = BlockType_Invalid;
	}

	zt_fize(board.next) {
		board.next[i] = BlockType_Invalid;
	}
	zt_fize(board.prev) {
		board.prev[i] = BlockType_Invalid;
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

bool boardRotateBlockLeft(Board *board)
{
	return false;
}

// ------------------------------------------------------------------------------------------------

bool boardRotateBlockRight(Board *board)
{
	return false;
}

// ------------------------------------------------------------------------------------------------

BlockType_Enum boardGetNextBlock(Board *board)
{
	return BlockType_Square;
}

// ------------------------------------------------------------------------------------------------

void boardCycleBlocks(Board *board, int max_next, BlockType_Enum next)
{
	board->active_block = next;
	board->active_block_rotation = 0;
	board->active_block_position = 5;

	board->current_state = BoardState_Falling;
}

// ------------------------------------------------------------------------------------------------

void boardGetBlockPieces(BlockType_Enum block, int rotation, i8 *pieces, int *center)
{
	switch (block)
	{
		case BlockType_Straight: {
			if (center) *center = 10;
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
			if (center) *center = 10;
			i8 block_pieces[] = {
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 1, 1, 0,
				0, 1, 1, 0
			};
			zt_memCpy(pieces, 16, block_pieces, 16);
		} break;

		case BlockType_T: {
			if (center) *center = 9;
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
			if (center) *center = 9;
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
			if (center) *center = 9;
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
			if (center) *center = 9;
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
			if (center) *center = 9;
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

bool boardIsValidBlockPosition(Board *board, int index, BlockType_Enum next, int rotation)
{
	return false;
}

// ------------------------------------------------------------------------------------------------

void boardProcessGravityDrop(Board *board)
{
	board->active_block_position = boardIndexAdjust(board, board->active_block_position, 0, 1);
}

// ------------------------------------------------------------------------------------------------

BoardState_Enum boardUpdate(Board *board, r32 dt, BoardRules *rules, BoardInput_Enum *inputs, int inputs_count)
{
	zt_returnValOnNull(board, BoardState_Invalid);

	if (board->current_state == BoardState_Waiting && board->active_block == BlockType_Invalid) {
		boardCycleBlocks(board, rules->max_next, boardGetNextBlock(board));
		zt_assertReturnValOnFail(board->active_block != BlockType_Invalid, BoardState_Invalid);
	}

	zt_fiz(inputs_count) {
		switch (inputs[i])
		{
			case BoardInput_MoveLeft: {

			} break;

			case BoardInput_MoveRight: {
			} break;

			case BoardInput_RotateLeft: {
				board->active_block_rotation -= 1;
				if (board->active_block_rotation < 0) {
					board->active_block_rotation += 4;
				}
			} break;

			case BoardInput_RotateRight: {
				board->active_block_rotation = (board->active_block_rotation + 1) % 4;
			} break;

			case BoardInput_SoftDrop: {
			} break;

			case BoardInput_HardDrop: {
			} break;

			case BoardInput_Hold: {
			} break;
		}
	}

	if (board->current_state == BoardState_Falling) {
		board->time_to_drop += dt;
		if (board->time_to_drop >= rules->drop_time) {
			board->time_to_drop -= rules->drop_time;
			boardProcessGravityDrop(board);
		}
	}

	return BoardState_Falling;
}

// ------------------------------------------------------------------------------------------------

void boardRenderBlockPiece(Board *board, BlockType_Enum block, ztDrawList *draw_list, int at_index)
{
	ztVec2 pos(board->board_size.x * -.25f + .25f, board->board_size.y * .25f - .25f);

	ztPoint2 point = boardPointFromIndex(board, at_index);

	pos.x += point.x * .5f;
	pos.y -= point.y * .5f;

	ztVec4 color = ztVec4::one;
	switch (block)
	{
		case BlockType_Straight: color = ztVec4(146 / 255.f, 255 / 255.f, 255 / 255.f, 1); break;
		case BlockType_Square  : color = ztVec4(249 / 255.f, 255 / 255.f, 146 / 255.f, 1); break;
		case BlockType_T       : color = ztVec4(210 / 255.f, 146 / 255.f, 255 / 255.f, 1); break;
		case BlockType_J       : color = ztVec4(146 / 255.f, 146 / 255.f, 255 / 255.f, 1); break;
		case BlockType_L       : color = ztVec4(255 / 255.f, 205 / 255.f, 146 / 255.f, 1); break;
		case BlockType_S       : color = ztVec4(255 / 255.f, 146 / 255.f, 146 / 255.f, 1); break;
		case BlockType_Z       : color = ztVec4(146 / 255.f, 255 / 255.f, 146 / 255.f, 1); break;
		default: return;
	}

	zt_drawListPushColor(draw_list, color);
	{
		zt_drawListAddFilledRect2D(draw_list, ztVec3(pos, 0), ztVec2(.5f, .5f), ztVec2(0, 0), ztVec2(1, 1));
	}
	zt_drawListPopColor(draw_list);
}

// ------------------------------------------------------------------------------------------------

void boardRenderBlock(Board *board, BlockType_Enum block, ztDrawList *draw_list, int at_index, int rotation)
{
	int center = 0;
	i8 pieces[16];
	boardGetBlockPieces(block, rotation, pieces, &center);

	int center_y = zt_convertToi32Floor(center / 4.f);
	int center_x = center - (center_y * 4);

	zt_fiz(4) {
		int x = i;
		zt_fjz(4) {
			int y = j;
			int pidx = (y * 4) + x;
			if (pieces[pidx] != 0) {
				int idx = boardIndexAdjust(board, at_index, x - center_x, y - center_y);
				if (idx != -1) {
					boardRenderBlockPiece(board, block, draw_list, idx);
				}
			}

		}
	}

}

// ------------------------------------------------------------------------------------------------

void boardRender(Board *board, ztDrawList *draw_list, ztTextureID tex_block)
{
	zt_drawListPushTexture(draw_list, tex_block);
	{
		//void 
		if (board->active_block != BlockType_Invalid) {
			boardRenderBlock(board, BlockType_T, draw_list, board->active_block_position, board->active_block_rotation);
		}
	}
	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------
