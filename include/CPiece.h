    //
// Created by korot on 24/03/2025.
//

#ifndef CPIECE_H
#define CPIECE_H
#include <cstdint>
#include <vector>
// #include <Board.h>
namespace chs {
    class CPiece;

    struct BField {
        int32_t index = 1;
        char ch = 'a';
        CPiece* piece = nullptr;
        bool validate() const {
            return index >= 1 && index <= 8 && ch >= 'a' && ch <= 'h';
        }

        explicit operator int() const {
            return (ch - 'a') + (index - 1) * 8;
        }

        bool operator==(const BField & pos) const{return (index == pos.index) && (ch == pos.ch);};


        static int get_arr_index(int32_t index, char ch) {
            return (ch - 'a') + (index - 1) * 8;
        }
    };


    enum uint8_t {
        T_King = 0,
        T_Queen = 1,
        T_Rook = 2,
        T_Knight = 3,
        T_Bishop = 4,
        T_Pawn = 5,
        T_Init = 6,
        T_Black = 0,
        T_White = 1,
    };
    class CPiece{
    protected:
        uint8_t side = T_White;
        uint32_t value = 0;
        uint8_t type = T_Init;
    public:
        BField* pos = nullptr;
        /*
         * Used to construct actual piece structures
         */
        CPiece() = default;
        CPiece(BField* pos_, uint8_t side_, uint32_t value_, uint8_t type_) :
            pos(pos_), side(side_), value(value_), type(type_) {
            pos_->piece = this;
        }

        virtual ~CPiece()= default;

        virtual std::vector<std::vector<BField *>> get_valid_moves(std::vector<BField> &play_field){return {};};
        //changes the position of the piece, doesn't validate the move, nor destroys other pieces
        virtual void move(BField *field) {
            pos->piece = nullptr;
            pos = field;
            field->piece = this;
        }

        virtual void move_back(BField * field, CPiece* prev) {
            pos->piece = prev;
            pos = field;
            field->piece = this;
        }

        virtual uint8_t get_type(){return type;}
        virtual uint8_t get_side(){return side;}

        static void fill_diagonals(std::vector<std::vector<BField *>> &vec, const BField *pos, std::vector<BField> &play_field);
        static void fill_straight(std::vector<std::vector<BField *>> &vec, BField *pos, std::vector<BField> &play_field);
    };

    inline void CPiece::fill_diagonals(std::vector<std::vector<BField *>> &vec, const BField *pos, std::vector<BField> &play_field) {
        std::vector<BField*>& layer1 = vec.emplace_back();
        CPiece* piece = pos->piece;
        for (BField x = *pos; x.ch <= 'h' && x.index <= 8; ++x.ch, ++x.index) {
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer1.push_back(f);
                break;
            }
            layer1.push_back(f);
        }
        std::vector<BField*>& layer2 = vec.emplace_back();
        for (BField x = *pos; x.ch <= 'h' && x.index >= 1; ++x.ch, --x.index){
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer2.push_back(f);
                break;
            }
            layer2.push_back(f);
        }
        std::vector<BField*>& layer3 = vec.emplace_back();
        for (BField x = *pos; x.ch >= 'a' && x.index <= 8; --x.ch, ++x.index){
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer3.push_back(f);
                break;
            }
            layer3.push_back(f);
        }
        std::vector<BField*>& layer4 = vec.emplace_back();
        for (BField x = *pos; x.ch >= 'a' && x.index >= 1; --x.ch, --x.index){
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer4.push_back(f);
                break;
            }
            layer4.push_back(f);
        }
    }

    inline void CPiece::fill_straight(std::vector<std::vector<BField *>> &vec, BField *pos, std::vector<BField> &play_field) {
        std::vector<BField*>& layer1 = vec.emplace_back();
        CPiece* piece = pos->piece;
        for (BField x = *pos; x.ch <= 'h'; ++x.ch){
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            layer1.push_back(f);
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer1.push_back(f);
                break;
            }
            layer1.push_back(f);
        }
        std::vector<BField*>& layer2 = vec.emplace_back();
        for (BField x = *pos; x.ch >= 'a'; --x.ch){
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer2.push_back(f);
                break;
            }
            layer2.push_back(f);
        }
        std::vector<BField*>& layer3 = vec.emplace_back();
        for (BField x = *pos; x.index <= 8; ++x.index){
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer3.push_back(f);
                break;
            }
            layer3.push_back(f);
        }
        std::vector<BField*>& layer4 = vec.emplace_back();
        for (BField x = *pos; x.index >= 1; --x.index){
            if (x == *pos)
                continue;
            BField* f = &play_field[static_cast<int>(x)];
            if (f->piece != nullptr) {
                if (f->piece->get_side() != piece->get_side())
                    layer4.push_back(f);
                break;
            }
            layer4.push_back(f);
        }
    }
}

#endif //CPIECE_H
