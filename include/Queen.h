//
// Created by korot on 24/03/2025.
//

#ifndef QUEEN_H
#define QUEEN_H
#include "CPiece.h"

namespace chs {
    class Queen : public CPiece {
    public:
        Queen() = default;
        explicit Queen(BField* field ,uint8_t side_);

        std::vector<std::vector<BField *>> get_valid_moves(std::vector<BField> &play_field) override;
    };

}


#endif //QUEEN_H
