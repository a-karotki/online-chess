//
// Created by korot on 24/03/2025.
//

#ifndef ROOK_H
#define ROOK_H
#include <CPiece.h>

namespace chs {
    class Rook : public CPiece{
        static BField get_init_field(uint8_t side, int num);
        int moves = 0;
    public:
        Rook() = default;
        explicit Rook(BField* field, uint8_t side_);

        static void init_for_side(uint8_t side_, std::vector<CPiece *> &vec, std::vector<BField> &play_field);

        std::vector<std::vector<BField *>> get_valid_moves(std::vector<BField> &play_field) override;

        void move(BField *field) override;
        void move_back(BField *field, CPiece* prev) override;
    };
}



#endif //ROOK_H
