//
// Created by korot on 24/03/2025.
//

#ifndef PAWN_H
#define PAWN_H

#include "CPiece.h"
namespace chs {
    class Pawn : public CPiece{
        int moves = 0;
        static BField get_init_field(uint8_t side, int num);
    public:
        Pawn() = default;
        Pawn(BField* field, uint8_t side_);

        static void init_for_side(uint8_t side_, std::vector<CPiece *> &vec,
                                  std::vector<BField> &play_field);
        //the first vec - moves, the second - left hit, the third - right hit
        std::vector<std::vector<BField *>> get_valid_moves(std::vector<BField> &play_field) override;
        void move(BField *field) override;
        void move_back(BField *field, CPiece* prev) override;
    };
}



#endif //PAWN_H
