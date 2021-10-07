#ifndef BOARD_HEADER
#define BOARD_HEADER

#include <vector>
#include <iostream>

// int ROW = 8;
// int COL = 8;
// int SUCCESS_N = 5;

struct Move
{
    Move(int row, int col)
    {
        this->move_row = row;
        this->move_col = col;
    }
    int move_row;
    int move_col;
};


struct End_Winner
{
    End_Winner(bool is_end, char winner)
    {
        this->is_end = is_end;
        this->winner = winner;
    }
    bool is_end;
    char winner;
};


class Board
{
private:
    const int row_num = 8;
    const int col_num = 8;
    std::vector<std::vector<char>> board;
    const int success_n = 5;
    

public:
    Board(char player);
    ~Board();
    void act(Move move);
    std::vector<Move> get_available_moves();
    char player;
    
    bool is_full();
    char check_win();
    End_Winner get_result();
    
    
    void print();

};

#endif