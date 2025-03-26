//
// Created by korot on 24/03/2025.
//

#include "Rook.h"
using namespace chs;

BField Rook::get_init_field(uint8_t side, int num) {
    BField res;
    if (num == 0)
        res.ch = 'a';
    else
        res.ch = 'h';
    if (side == T_White)
        res.index = 1;
    else
        res.index = 8;
    return res;
}

Rook::Rook(BField* field , uint8_t side_) : CPiece(field, side_, 5, T_Rook){}

void Rook::init_for_side(uint8_t side_, std::vector<CPiece*> &vec, std::vector<BField>& play_field) {
    for (int i = 0; i != 2; ++i) {
        BField f = get_init_field(side_, i);
        auto* b = new Rook(&play_field[static_cast<int>(f)], side_);
        vec.push_back(b);
    }
}

std::vector<std::vector<BField *>> Rook::get_valid_moves(std::vector<BField> &play_field) {
    std::vector<std::vector<BField*>> res;
    fill_straight(res, pos, play_field);
    return res;
}


