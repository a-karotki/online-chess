//
// Created by korot on 24/03/2025.
//

#include "Queen.h"
using namespace chs;

Queen::Queen(BField* field, uint8_t side_): CPiece(field, side_, 9, T_Queen) {}

std::vector<std::vector<BField *>> Queen::get_valid_moves(std::vector<BField> &play_field) {
    std::vector<std::vector<BField*>> res;
    fill_diagonals(res, pos, play_field);
    fill_straight(res, pos, play_field);
    return res;
}
