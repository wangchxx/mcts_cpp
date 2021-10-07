#include "include/board.hpp"
#include "include/node.hpp"
#include "include/mcts.hpp"




class MCTS_Player
{
public:
    Move get_move(Board& board)
    {
        Move move(-1,-1);
        std::vector<Move> available_moves = board.get_available_moves();
        if (!available_moves.empty())
        {
            move = mcts->get_best_move(board);
            mcts->update_tree(move);
        }
        return move;
    }
    MCTS_Player(char player_, int n_rollouts_):
        mcts(new MCTS(n_rollouts_)),
        player(player_)
        {}

// private:
    char player;
    MCTS* mcts;
};


class Human_Player
{
public:
    Move get_move(Board& board)
    {   int row,col;
        printf("Please input your move: row, col \n");
        std::cin >> row >> col;
        return Move(row,col);
    }
    Human_Player(char player_):
    player(player_)
    {}

// private:
    char player;
};


void game(Board& board)
{
    MCTS_Player player_1('X', 40000);
    Human_Player player_2('O');
    End_Winner result = board.get_result();
    Move move(-1,-1);
    while(!result.is_end)
    {
        int current_player = (player_1.player == board.player)?1:2;
        if (current_player == 1){move = player_1.get_move(board);}
        else {move = player_2.get_move(board);}
        board.act(move);
        board.print();
        result = board.get_result();
    }
    printf("Game Over. Winner = %c \n",result.winner);
};

int main()
{   
    Board chessboard('X');
    Board& board = chessboard;
    game(board);
    // Board board('O');
    
    // board.act(move);
    // board.print();
    // board.act(Move(0,0));
    // board.act(Move(1,1));
    // board.act(Move(0,1));
    // board.print();
    // End_Winner result = board.get_result();
    // std::cout << result.winner << std::endl;
    // board.act(Move(1,2));
    // board.print();
    // result = board.get_result();
    // std::cout << result.winner << std::endl;

    






    // printf("Check vector function .at(pos), size() and [pos] \n");
    // std::vector<Move> moves;
    // for (int i = 0; i<10; i++)
    // {
    //     Move move(i,i);
    //     moves.push_back(move);
    // }
    // std::cout << "moves.size()="<<moves.size() <<' ';
    // std::cout << "moves.at(3).move_col=" << moves.at(3).move_col << ' ';
    // std::cout << "moves[3].move_col="<< moves[3].move_col << '\n';

    // MCTS_Player player1 = MCTS_Player('O', 4000);
    // Move best_move = player1.get_move(board);
    // std::cout<< "best move row:"<<best_move.move_row << " col:"<<best_move.move_col<< '\n';

    
    return 0;
}