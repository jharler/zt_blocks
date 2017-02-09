#include "board_renderer_2d.h"

// ------------------------------------------------------------------------------------------------

ztVec4 _boardRenderer2dBlockPieceColor(Board *board, BoardRules *rules, BlockType_Enum block)
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

		case BlockType_None: {
			r32 osc = zt_linearRemap(zt_sin(board->current_state_time * 6), -1, 1, 0, 1);
			color = ztVec4::lerp(ztVec4(.5f, .5f, .5f, 1), ztVec4(.45f, .45f, .45f, 1), osc);
		} break;

		case BlockType_Clearing: {
			color = ztVec4(1, 1, 1, zt_lerp(0.f, 1.f, board == nullptr || rules == nullptr ? 0 : board->time_to_clear / rules->clear_time));
		} break;

		default: color = ztVec4(.5f, .5f, .5f, .25f);
	}

	return color;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardRenderer2dBlockPiece(Board *board, BoardRules *rules, BlockType_Enum block, ztDrawList *draw_list, ztVec2 position)
{
	ztVec4 color = _boardRenderer2dBlockPieceColor(board, rules, block);

	zt_drawListPushColor(draw_list, color);
	{
		zt_drawListAddFilledRect2D(draw_list, ztVec3(position, 0), ztVec2(.5f, .5f), ztVec2(0, 0), ztVec2(1, 1));
	}
	zt_drawListPopColor(draw_list);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardRenderer2dBlockPiece(Board *board, BoardRules *rules, BlockType_Enum block, ztDrawList *draw_list, int at_index)
{
	ztVec2 pos(board->board_size.x * -.25f + .25f, (board->board_size.y * .25f - .25f) + (BOARD_TOP_BUFFER_COUNT / 2.f - .5f));

	ztVec2i point = boardPointFromIndex(board, at_index, 0);

	pos.x += point.x * .5f;
	pos.y -= point.y * .5f;

	_boardRenderer2dBlockPiece(board, rules, block, draw_list, pos);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _boardRenderer2dBlock(Board *board, BoardRules *rules, BlockType_Enum block, ztDrawList *draw_list, int at_index, int col_adjust, int rotation)
{
	i8 pieces[16];
	boardGetBlockPieces(board->rotation_system, block, rotation, pieces);

	//_boardRenderer2dBlockPiece(board, BlockType_MAX, draw_list, at_index);

	int min_idx = BOARD_TOP_BUFFER_COUNT * board->board_size.x;

	zt_fiz(4) {
		int x = i;
		zt_fjz(4) {
			int y = j;
			int pidx = (y * 4) + x;
			if (pieces[pidx] != 0) {
				int idx = boardIndexAdjust(board, at_index, x - col_adjust, y);
				if (idx != -1 && idx >= min_idx) {
					_boardRenderer2dBlockPiece(board, rules, block, draw_list, idx);
				}
			}
			//else if(pidx != 0) {
			//	int idx = boardIndexAdjust(board, at_index, x - col_adjust, y);
			//	if (idx != -1) {
			//		_boardRenderer2dBlockPiece(board, BlockType_Invalid, draw_list, idx);
			//	}
			//}
		}
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool boardRenderer2dMake(BoardRenderer2d *renderer, Board *board, ztAssetManager *asset_manager)
{
	renderer->tex_block       = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, "textures/block.png"));
	renderer->tex_block_ghost = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, "textures/block_ghost.png"));
	renderer->tex_block_blur  = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, "textures/block_blur.png"));

	if (renderer->tex_block == ztInvalidID || renderer->tex_block_ghost == ztInvalidID || renderer->tex_block_ghost == ztInvalidID) {
		return false;
	}

	renderer->hard_drop_time = 0;

	return true;
}

// ------------------------------------------------------------------------------------------------

void boardRenderer2dFree(BoardRenderer2d *renderer)
{
	zt_textureFree(renderer->tex_block);
	zt_textureFree(renderer->tex_block_ghost);
	zt_textureFree(renderer->tex_block_blur);
}

// ------------------------------------------------------------------------------------------------

void boardRenderer2dUpdate(BoardRenderer2d *renderer, Board *board, BoardRules *rules, r32 dt)
{
	int            last_idx   = renderer->active_block_last_idx;
	int            last_col   = renderer->active_block_last_col;
	int            last_rot   = renderer->active_block_last_rot;
	BlockType_Enum last_block = renderer->active_block_last_block;

	renderer->active_block_last_idx   = board->active_block_pos_idx;
	renderer->active_block_last_col   = board->active_block_pos_col;
	renderer->active_block_last_rot   = board->active_block_rotation;
	renderer->active_block_last_block = board->active_block;

	if (board->hard_drop) {// && renderer->hard_drop_time <= 0) {
		ztVec2i block_point_prev = boardPointFromIndex(board, last_idx, last_col);
		ztVec2i block_point_curr = boardPointFromIndex(board, board->active_block_pos_idx, board->active_block_pos_col);

		renderer->hard_drop_pos = ztVec2(block_point_prev.x / 2.f, block_point_prev.y / -2.f) + ztVec2(board->board_size.x * -.25f + .25f, (board->board_size.y * .25f - .25f) + (BOARD_TOP_BUFFER_COUNT / 2.f - .5f));;

		i8 pieces[16];
		boardGetBlockPieces(board->rotation_system, last_block, last_rot, pieces);

		int x_min = 4, x_max = 0;
		int y_min = 4, y_max = 0;
		zt_fiz(4) {
			int y = i;
			zt_fjz(4) {
				int x = j;
				int idx = (y * 4) + x;

				if (pieces[idx] != 0) {
					x_min = zt_min(x_min, x);
					x_max = zt_max(x_max, x);
					y_min = zt_min(y_min, y);
					y_max = zt_max(y_max, y);
				}
			}
		}

		renderer->hard_drop_size.x = ((1 + (x_max - x_min)) / 2.f);
		renderer->hard_drop_size.y = ((1 + (y_max - y_min)) / 2.f) + ((block_point_curr.y - block_point_prev.y) / 2.f);

		renderer->hard_drop_pos.x += (x_min / 2.f) + (renderer->hard_drop_size.x / 2.f) - .25f;
		renderer->hard_drop_pos.y -= (y_min / 2.f) + (renderer->hard_drop_size.y / 2.f) - .25f;

		renderer->hard_drop_time = BOARD_RENDERER_2D_HARD_DROP_TIME;
		renderer->hard_drop_color = _boardRenderer2dBlockPieceColor(board, rules, last_block);
		int debug_stop = 0;

	}
	else if (renderer->hard_drop_time > 0) {
		renderer->hard_drop_time -= dt;
	}
}

// ------------------------------------------------------------------------------------------------

void boardRenderer2dRender(BoardRenderer2d *renderer, Board *board, BoardRules *rules, ztDrawList *draw_list, ztVec2 position)
{
	// draw the ghost block where the hard drop would go
	if (renderer->tex_block_ghost != ztInvalidID) {
		zt_drawListPushTexture(draw_list, renderer->tex_block_ghost);
		{
			_boardRenderer2dBlock(board, rules, board->active_block, draw_list, boardGetBlockHardDropPositionIndex(board), board->active_block_pos_col, board->active_block_rotation);
		}
		zt_drawListPopTexture(draw_list);
	}

	zt_drawListPushTexture(draw_list, renderer->tex_block);
	{
		// draw the board
		int min = board->board_size.x * 2;

		zt_fiz(board->board_size.x * board->board_size.y) {
			if (i < min || board->board[i] == BlockType_Invalid) {
				//_boardRenderer2dBlockPiece(board, BlockType_MAX, draw_list, i);
				continue;
			}

			i16 board_piece = board->board[i];
			_boardRenderer2dBlockPiece(board, rules, (BlockType_Enum)board_piece, draw_list, i);
		}

		if (board->active_block != BlockType_Invalid) {
			_boardRenderer2dBlock(board, rules, board->active_block, draw_list, board->active_block_pos_idx, board->active_block_pos_col, board->active_block_rotation);
		}
	}
	zt_drawListPopTexture(draw_list);

	if (renderer->hard_drop_time > 0) {
		zt_drawListPushTexture(draw_list, renderer->tex_block_blur);
		ztVec4 color = renderer->hard_drop_color;
		color.a = zt_lerp(0.f, 1.f, renderer->hard_drop_time / BOARD_RENDERER_2D_HARD_DROP_TIME);
		zt_drawListPushColor(draw_list, color);
		zt_drawListAddFilledRect2D(draw_list, ztVec3(renderer->hard_drop_pos + position, 0), renderer->hard_drop_size, ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);
		zt_drawListPopTexture(draw_list);
	}

}

// ------------------------------------------------------------------------------------------------

void boardRenderer2dRenderBlock(BoardRenderer2d *renderer, BoardRotationSystem_Enum rotation_system, BlockType_Enum block, ztDrawList *draw_list, ztVec2 position, int rotation)
{
	i8 pieces[16];
	boardGetBlockPieces(rotation_system, block, rotation, pieces);

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

	zt_drawListPushTexture(draw_list, renderer->tex_block);
	{
		zt_fiz(4) {
			int x = i;
			zt_fjz(4) {
				int y = j;
				int pidx = (y * 4) + x;
				if (pieces[pidx] != 0) {
					_boardRenderer2dBlockPiece(nullptr, nullptr, block, draw_list, position + ztVec2(x / 2.f, y / -2.f));
				}
			}
		}
	}
	zt_drawListPopTexture(draw_list);
}
