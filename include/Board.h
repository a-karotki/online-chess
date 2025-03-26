//
// Created by korot on 24/03/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "CPiece.h"
#include <cstdint>
#include <vector>
namespace chs {
    class King;


    enum BM_Event{
        BM_NULL = 0 << 0,
        BM_TAKEN = 0 << 1,
        BM_CHECK = 0 << 2,
        BM_CASTLE = 0 << 3,
    };
    struct Move {
        BField* start = nullptr;
        BField* end = nullptr;
        uint8_t side = T_White;
        CPiece* moved = nullptr;
        CPiece* taken = nullptr;
        int32_t ev = 0;
    };
    class Board {
        static std::vector<CPiece*> white; //white pieces
        static std::vector<CPiece*> black; //black pieces
        static King* w_king;
        static King* b_king;

        static void init_team(uint8_t side_);
        static bool is_checked(uint8_t side_);
        static bool end_turn();
        static void remove_piece(CPiece* piece);
        static uint8_t turn_op() {return turn == T_White ? T_Black : T_White;}
    public:
        static std::vector<Move> move_history;
        static std::vector<BField> play_field;
        static uint8_t turn;
        //restarts the game
        static void init(uint8_t f_to_move = T_White);

        static bool move(const BField &start, const BField &dest);

        /*
         * returns true on success and changes the position of the piece
         * (may cause additional changes (e.g. check))
         * returns false on failure, board remains unchanged
         */
        static bool move(BField *start, BField *dest);
    };
}



#endif //BOARD_H
