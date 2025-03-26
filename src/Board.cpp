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
King* Board::w_king = nullptr;
King* Board::b_king = nullptr;

void Board::init_team(uint8_t side_) {
    std::vector<CPiece*>& team = side_ == T_White ? white : black;
    int32_t index = side_ == T_White ? 1 : 8;
    King *k = new King(&play_field[BField::get_arr_index(index, 'e')], side_);
    if (side_ == T_White)
        w_king = k;
    else
        b_king = k;
    team.push_back(k);
    team.push_back(new Queen(&play_field[BField::get_arr_index(index, 'd')], side_));
    Bishop::init_for_side(side_, team,  play_field);
    Knight::init_for_side(side_, team, play_field);
    Rook::init_for_side(side_, team, play_field);
    Pawn::init_for_side(side_, team, play_field);
}

bool Board::is_checked(uint8_t side_) {
    std::vector<CPiece*> op = side_ == T_White ? black : white;
    King* king = side_ == T_White ? w_king : b_king;
    std::vector<std::vector<BField*>> rays_diag{};
    std::vector<std::vector<BField*>> rays_strh{};
    CPiece::fill_diagonals(rays_diag, king->pos, play_field);
    CPiece::fill_straight(rays_strh, king->pos, play_field);
    for (auto& x : rays_diag) {
        if (x.empty())
            continue;
        CPiece* piece = x.back()->piece;
        if (piece != nullptr) {
            uint8_t type = piece->get_type();
            if (type == T_Bishop || type == T_Queen)
                return true;
            if (type == T_Pawn) {
                const auto& p_moves = piece->get_valid_moves(play_field);
                if ((p_moves.size() > 1 && p_moves[1].back()->piece == king) ||
                    (p_moves.size() > 2 && p_moves[2].back()->piece == king))
                    return true;
            }
        }
    }
    for (auto& x : rays_strh) {
        if (x.empty())
            continue;
        CPiece* piece = x.back()->piece;
        if (piece != nullptr) {
            uint8_t type = piece->get_type();
            if (type == T_Rook || type == T_Queen)
                return true;
        }
    }
    auto find_kn = [](CPiece* cp){return cp->get_type() == T_Knight;};

    for (auto it = std::find_if(op.begin(), op.end(), find_kn);
        it != op.end(); it = std::find_if(it + 1, op.end(), find_kn)) {
        const std::vector<std::vector<BField*>>& moves = (*it)->get_valid_moves(play_field);
        for (auto x : moves)
            if (x.back()->piece == king)
                return true;
    }
    return false;
}
//CPiece::move unbinds field;
void Board::remove_piece(CPiece *piece) {
    assert(piece->get_type() != T_King);
    std::vector<CPiece*>& team = piece->get_side() == T_White ? white : black;
    std::erase(team, piece);
    delete piece;
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
    if(start->piece == nullptr) return false;
    CPiece* piece = start->piece;
    if (piece->get_side() != turn)
        return false;
    CPiece* dest_p = dest->piece;
    if (dest_p != nullptr && (dest_p->get_side() == piece->get_side() || dest_p->get_type() == T_King))
        return false;
    int ev = 0;
    std::vector<std::vector<BField*>> moves = piece->get_valid_moves(play_field);
    for (auto& x : moves) {
        if (std::find(x.begin(), x.end(), dest) != x.end()) {
            piece->move(dest);
            if (is_checked(piece->get_side())) {
                piece->move_back(start, dest_p);
                return false;
            }
            if (dest_p != nullptr) {
                remove_piece(dest_p);
                ev |= BM_TAKEN;
            }
            const auto m = Move(start, dest, turn, piece, dest_p, ev);
            move_history.push_back(m);
            return end_turn();
        }
    }
    return false;
}

bool Board::end_turn() {
    assert(!move_history.empty());
    if (is_checked(turn_op()))
        move_history.back().ev |= BM_CHECK;
    turn = turn_op();
    return true;
}


