//
// Created by korot on 24/03/2025.
//

#ifndef KING_H
#define KING_H

#include "CPiece.h"
namespace chs {
    class King : public CPiece{
        int moves = 0;
    public:
        King() = default;
        explicit King(BField* field, uint8_t side_);

        std::vector<std::vector<BField *>> get_valid_moves(std::vector<BField> &play_field) override;
        void move(BField *field) override;
        void move_back(BField *field) override;
    };
}



#endif //KING_H
