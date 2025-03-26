//
// Created by korot on 24/03/2025.
//

#include "King.h"
using namespace chs;
King::King(BField* field,uint8_t side_) : CPiece(field, side_, 0, T_King){}

std::vector<std::vector<BField *>> King::get_valid_moves(std::vector<BField> &play_field) {
    std::vector<std::vector<BField*>> res;
    std::vector<std::pair<int32_t, char>> offsets = {
        {0, 1}, {1, 0}, {-1, 0}, {0, -1},
        {1, -1}, {-1, 1}, {1, 1}, {-1, -1}
    };
    for (auto& x : offsets) {
        BField f = {pos->index + x.first, static_cast<char>(pos->ch + x.second)};
        if (f.validate())
            res.emplace_back().push_back(&play_field[static_cast<int>(f)]);
    }
    return res;
}

void King::move(BField *field) {
    CPiece::move(field);
    ++moves;
}

void King::move_back(BField *field) {
    CPiece::move(field);
    --moves;
}
