#include "../include/board.hpp"

Board::Board(char plyer)
{
    player = plyer;
    board.resize(col_num, std::vector<char>(col_num, '-'));
}

Board::~Board()
{
    
}

void Board::act(Move move)
{
    board[move.move_row][move.move_col] = player;
    // change player
    player = (player=='X')? 'O':'X';
}

std::vector<Move> Board::get_available_moves()
{
    std::vector<Move> available_moves;
    for(int row = 0; row<row_num; row++)
    {
        for (int col = 0; col<col_num; col++)
        {
            if(board[row][col] == '-')
            {
                Move move(row,col);
                available_moves.push_back(move);
            }

        }
    }
    return available_moves;
}

bool Board::is_full()
{
    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < col_num; j++)
        {
            if (board[i][j] == '-')
            {
                return false;
            }
        }
    }
    return true;
}

char Board::check_win()
{
    
    int max_col = col_num - success_n;
    int max_row = row_num - success_n;
    for (int i = 0; i<row_num; i++)
    {
        for (int j = 0; j<col_num; j++)
        {
            // check row: XXXXX
            int row_X = 0, row_O = 0;
            if (j <= max_col)
            {
                for (int k = 0; k < success_n && board[i][j+k] == 'X'; k++) row_X++;
                for (int k = 0; k < success_n && board[i][j+k] == 'O'; k++) row_O++;
            }
            
            if (row_X == success_n)
            {
                return 'X';
            }
            if (row_O == success_n)
            {
                return 'O';
            }

            // check col 
            // X
            // X
            // X
            // X
            // X
            int col_X = 0, col_O = 0;
            if (i <= max_row)
            {
                for (int k = 0; k < success_n && board[i+k][j] == 'X'; k++) col_X++;
                for (int k = 0; k < success_n && board[i+k][j] == 'O'; k++) col_O++;
            }
            
            if (col_X == success_n)
            {
                return 'X';
            }
            if (col_O == success_n)
            {
                return 'O';
            }

            //check right-down
            // X
            //  X
            //   X
            //    X
            //     X
            int rd_X = 0, rd_O = 0;
            if (i<= max_row && j <= max_col)
            {
                for (int k = 0; k < success_n && board[i+k][j+k] == 'X'; k++) rd_X++;
                for (int k = 0; k < success_n && board[i+k][j+k] == 'O'; k++) rd_O++;
            }
            if (rd_X == success_n)
            {
                return 'X';
            }
            if (rd_O == success_n)
            {
                return 'O';
            }


            // check left_down
            int ld_X = 0, ld_O = 0;
            if (i<= max_row && j >= success_n -1)
            {
                for (int k = 0; k < success_n && board[i+k][j-k] == 'X'; k++) ld_X++;
                for (int k = 0; k < success_n && board[i+k][j-k] == 'O'; k++) ld_O++;
            }
            if (ld_X == success_n)
            {
                return 'X';
            }
            if (ld_O == success_n)
            {
                return 'O';
            }




            
        }
    }
    // if no winner, return '-'
    return '-';
}


End_Winner Board::get_result()
{
    End_Winner result(false, '-');
    bool full = is_full();
    if (full)
    {
        result.is_end = full;
        result.winner = check_win();
    }
    else
    {
        char winner = check_win();
        result.winner = winner;
        if (winner == '-')
        {
            result.is_end = false;
            
        }
        else
        {
            result.is_end = true;
        }

    }
    return result;

}

void Board::print()
{
    
    std::cout << std::endl;
    std::cout << "  ";
    for (int col = 0; col < col_num - 1; col++) {
        std::cout << col << ' ';
    }
    std::cout << col_num - 1 << std::endl;
    for (int row = 0; row < row_num; row++) {
        std::cout << row <<"|";
        for (int col = 0; col < col_num - 1; col++) {
            std::cout << board[row][col] << ' ';
        }
        std::cout << board[row][col_num - 1] << "|" << std::endl;
    }
    std::cout << " +";
    for (int col = 0; col < col_num - 1; col++) {
        std::cout << "--";
    }
    std::cout << "-+" << std::endl;
    std::cout << player << " to move " << std::endl << std::endl;
	
}