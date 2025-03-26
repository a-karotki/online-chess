//
// Created by korot on 24/03/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "CPiece.h"
#include <cstdint>
#include <vector>
namespace chs {


    enum SP_Event : unsigned char{
        E_Null = 0,
        E_Taken = 1,
        E_Check = 2,
        E_Castle = 3,
    };
    struct Move {
        BField* start;
        BField* end;
        uint8_t side = T_White;
        CPiece* moved = nullptr;
        CPiece* taken = nullptr;
        SP_Event ev = E_Null;
    };
    class Board {
        static std::vector<CPiece*> white; //white pieces
        static std::vector<CPiece*> black; //black pieces

        static void init_team(uint8_t side_);
        static bool is_checked(uint8_t side_);
        static bool end_turn(BField *start, BField *dest, CPiece *piece_s, CPiece *piece_d, SP_Event ev);
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
