//
// Created by korot on 24/03/2025.
//
#include <Bishop.h>
#include <cassert>
#include <stdlib.h>
#include "CPiece.h"
#include "Board.h"

#include <iostream>
#include <string>
#include <vector>

#define RED_COLOR 31
#define WHITE_COLOR 37

void set_color(chs::uint8_t team)
{
    if (team == chs::T_White)
        std::cout << "\033[" << WHITE_COLOR << "m";
    else
        std::cout << "\033[" << RED_COLOR << "m";
}
void reset_color() { std::cout << "\033[0m"; }
char get_char(chs::uint8_t type) {
    switch (type) {
        case chs::T_King:
            return 'K';
        case chs::T_Bishop:
            return 'B';
        case chs::T_Pawn:
            return 'p';
        case chs::T_Knight:
            return 'N';
        case chs::T_Queen:
            return 'Q';
        case chs::T_Rook:
            return 'R';
        default:
            return ' ';
    }
}

void print_board(std::vector<chs::BField>& vec) {
    // int i = 0;
    assert(vec.size() == 64);
    for (char ch = 'a'; ch <= 'h'; ++ch)
        std::cout << ch << ' ';
    std::cout << std::endl;
    std::string str{};
    int j = 8;
    for (int i = chs::BField::get_arr_index(j, 'a'); i >= 0; ++i) {
        const auto& field = vec[i];
        char c;
        if (field.piece == nullptr)
            c = ' ';
        else {
            c = get_char(field.piece->get_type());
            set_color(field.piece->get_side());
        }
        std::cout << c << ' ';
        reset_color();
        if (field.ch == 'h') {
            std::cout << j << std::endl;
            i = chs::BField::get_arr_index(--j, 'a') - 1;
        }
    }
    for (char ch = 'a'; ch <= 'h'; ++ch)
        std::cout << ch << ' ';
    std::cout<<std::endl;
}

int main() {
    chs::Board::init();
    char c_start, c_dest;
    int32_t i_start, i_dest;
    while (true) {
        print_board(chs::Board::play_field);
        L_AGAIN:
        std::cin >> c_start >> i_start >> c_dest >> i_dest;
        if (!chs::Board::move({i_start ,c_start}, {i_dest, c_dest})) {
            std::cout << "Try again!" <<std::endl;
            goto L_AGAIN;
        }
        system("clear");
        std::cout << c_start << std::to_string(i_start) << " to " << c_dest << std::to_string(i_dest) <<std::endl;
    }
}
