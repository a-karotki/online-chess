//
// Created by korot on 24/03/2025.
//

#include "Knight.h"
using namespace chs;

BField Knight::get_init_field(uint8_t side, int num) {
    BField res;
    if (num == 0)
        res.ch = 'b';
    else
        res.ch = 'g';
    if (side == T_White)
        res.index = 1;
    else
        res.index = 8;
    return res;
}

Knight::Knight(BField* field, uint8_t side_) : CPiece(field, side_, 3, T_Knight){}

void Knight::init_for_side(uint8_t side_, std::vector<CPiece*> &vec, std::vector<BField>& play_field) {
    for (int i = 0; i != 2; ++i) {
        BField f = get_init_field(side_, i);
        auto* b = new Knight(&play_field[static_cast<int>(f)], side_);
        vec.push_back(b);
    }
}

std::vector<std::vector<BField *>> Knight::get_valid_moves(std::vector<BField> &play_field) {
    std::vector<std::vector<BField*>> res;
    std::vector<std::pair<int32_t, char>> offsets = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {2, -1}, {1, -2}, {-1, -2}, {-2, -1}
    };
    for (auto& x : offsets) {
        BField f = {pos->index + x.first, static_cast<char>(pos->ch + x.second)};
        if (f.validate())
            res.emplace_back().push_back(&play_field[static_cast<int>(f)]);
    }
    return res;
}
