//
// Created by korot on 24/03/2025.
//

#ifndef BISHOP_H
#define BISHOP_H
#include "CPiece.h"

namespace chs {
    class Bishop : public CPiece {
        static BField get_init_field(uint8_t side, int num);
        int moves = 0;
    public:
        Bishop() = default;
        static void init_for_side(uint8_t side_, std::vector<CPiece *> &vec, std::vector<BField> &play_field);
        Bishop(BField* field ,uint8_t side_);

        std::vector<std::vector<BField *>> get_valid_moves(std::vector<BField> &play_field) override;

        void move(BField *field) override;
        void move_back(BField *field) override;
    };
}



#endif //BISHOP_H
