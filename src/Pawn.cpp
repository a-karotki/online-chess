//
// Created by korot on 24/03/2025.
//

#include "Pawn.h"

#include <cassert>
using namespace chs;
BField Pawn::get_init_field(uint8_t side, int num) {
    assert(num <= 7);
    BField res;
    if (side == T_White)
        res.index = 2;
    else
        res.index = 7;
    res.ch = 'a' + num;
    return res;
}

Pawn::Pawn(BField* field ,uint8_t side_) : CPiece(field, side_, 1, T_Pawn){}

void Pawn::init_for_side(uint8_t side_, std::vector<CPiece*> &vec, std::vector<BField>& play_field) {
    for (int i = 0; i != 8; ++i) {
        BField f = get_init_field(side_, i);
        auto* b = new Pawn(&play_field[static_cast<int>(f)], side_);
        vec.push_back(b);
    }
}

std::vector<std::vector<BField *>> Pawn::get_valid_moves(std::vector<BField> &play_field) {
    std::vector<std::vector<BField*>> res{1};
    int mv = side == T_White ? 1 : -1;
    BField f = {pos->index + mv, pos->ch};
    if (f.validate())
        res[0].push_back(&play_field[static_cast<int>(f)]);
    if (moves == 0) {
        f = {pos->index + 2 * mv, pos->ch};
        if (f.validate())
            res[0].push_back(&play_field[static_cast<int>(f)]);
    }
    f = {pos->index + mv, static_cast<char>(pos->ch + 1)};
    if (f.validate() && play_field[static_cast<int>(f)].piece != nullptr)
        res.emplace_back().push_back(&play_field[static_cast<int>(f)]);
    f = {pos->index + mv, static_cast<char>(pos->ch - 1)};
    if (f.validate() && play_field[static_cast<int>(f)].piece != nullptr)
        res.emplace_back().push_back(&play_field[static_cast<int>(f)]);
    return res;
}

void Pawn::move(BField *field) {
    CPiece::move(field);
    ++moves;
}

void Pawn::move_back(BField *field) {
    CPiece::move(field);
    --moves;
}
