//
// Created by korot on 24/03/2025.
//

#include "Board.h"

#include <Bishop.h>
#include <cassert>
#include <King.h>
#include <Knight.h>
#include <Pawn.h>
#include <Queen.h>
#include <Rook.h>
using namespace chs;
std::vector<Move> Board::move_history{}; // More than average
std::vector<CPiece*> Board::black{};
std::vector<CPiece*> Board::white{};
std::vector<BField> Board::play_field{};
chs::uint8_t Board::turn{T_White};

void Board::init_team(uint8_t side_) {
    std::vector<CPiece*>& team = side_ == T_White ? white : black;
    int32_t index = side_ == T_White ? 1 : 8;
    team.push_back(new King(&play_field[BField::get_arr_index(index, 'e')], side_));
    team.push_back(new Queen(&play_field[BField::get_arr_index(index, 'd')], side_));
    Bishop::init_for_side(side_, team,  play_field);
    Knight::init_for_side(side_, team, play_field);
    Rook::init_for_side(side_, team, play_field);
    Pawn::init_for_side(side_, team, play_field);
}

bool Board::is_checked(uint8_t side_) {
    std::vector<CPiece*>& op = side_ == T_White ? black : white;
    for (auto& x : op) {
        if (x->get_type() == T_King || x->get_type() == T_Pawn)
            continue;
        std::vector<std::vector<BField*>> moves = x->get_valid_moves(play_field);
        for (auto& v : moves) {
            if (v.empty())
                continue;
            CPiece* pointing =  v[v.size() - 1]->piece;
            if (pointing != nullptr && pointing->get_side() == side_ && pointing->get_type() == T_King)
                return true;
        }
    }
    return false;
}

void Board::init(uint8_t f_to_move) {
    turn = f_to_move;
    for (int i = 1; i != 9; ++i) {
        for (char j = 'a'; j <= 'h'; ++j) {
            play_field.push_back(BField{i, j});
        }
    }
    init_team(T_White);
    init_team(T_Black);
}

bool Board::move(const BField& start, const BField& dest) {
    BField* f1 = &play_field[static_cast<int>(start)];
    BField* f2 = &play_field[static_cast<int>(dest)];
    return move(f1, f2);
};

bool Board::move(BField *start, BField *dest) {
    assert(start->piece != nullptr);
    CPiece* piece = start->piece;
    CPiece* dest_p = dest->piece;
    if (dest_p != nullptr && (dest_p->get_side() == piece->get_side() || dest_p->get_type() == T_King))
        return false;
    std::vector<std::vector<BField*>> moves = piece->get_valid_moves(play_field);
    for (auto& x : moves) {
        if (std::find(x.begin(), x.end(), dest) != x.end()) {
            piece->move(dest);
            if (is_checked(piece->get_side())) {
                piece->move_back(start);
                return false;
            }
            // return end_turn(start, dest, piece, dest_p, dest_p == nullptr ? E_Null : E_Taken);
            return true;
        }
    }
    return false;
}

// bool Board::end_turn(BField *start, BField *dest, CPiece *piece_s, CPiece *piece_d, SP_Event ev) {
//     Move m(start, dest, piece_s->get_side(), piece_s, piece_d, ev);
// }


