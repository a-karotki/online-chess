//
// Created by korot on 24/03/2025.
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "CPiece.h"
namespace chs {
    class Knight : public CPiece{
        //returns dummy lookup field
        static BField get_init_field(uint8_t side, int num);
    public:
        Knight() = default;
        Knight(BField* field, uint8_t side_);

        static void init_for_side(uint8_t side_, std::vector<CPiece *> &vec, std::vector<BField> &play_field);

        std::vector<std::vector<BField *>> get_valid_moves(std::vector<BField> &play_field) override;
    };
}


#endif //KNIGHT_H
