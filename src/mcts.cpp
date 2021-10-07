#include "../include/mcts.hpp"


MCTS::MCTS(int n_rollouts_):
    // root(new Node(nullptr, Move(-1,-1))),
    n_rollouts(n_rollouts_)
{
    root = std::unique_ptr<Node>(new Node(nullptr, Move(-1,-1)));
}





MCTS::~MCTS()
{
    // delete root;
}

void MCTS::rollout(Board chessboard)
{
    // Node* node = root;
    auto node = root.get();
    
    // int i = 0;
    // for (auto child:root->children)
    // {
    //     printf("num_visits move %d,%d = %d \n",child->move.move_row,child->move.move_col, child->num_visits);
    //     printf("uct=%.4f \n",child->get_uct());
    //     i++;
    //     // if(i>0)
    //     // break;
    // }
    
    Board& board = chessboard;
    while(1)
    {
        // uct selection until reaching a leaf node
        if (node->is_leaf())
        {
            break;
        }
        node = node->select_uct();
        // std::cout<<"utc move row,col="<<node->move.move_row<< ',' <<node->move.move_col << '\n';
        board.act(node->move);
        // board.print();
    }

    // expand the leaf node if it is not the end of game
    End_Winner result = board.get_result();
    if (!result.is_end)
    {
        node->expand(board);
    }
    int leaf_value = evaluate_rollout(board);
    node->update_recursive(-leaf_value);


}

int MCTS::evaluate_rollout(Board& board)
{
    char player = board.player;
    End_Winner result(false, '-');
    while(1)
    {
        result = board.get_result();
        if (result.is_end)
        {
            break;
        }
        std::vector<Move> available_moves = board.get_available_moves();
        Move random_move = random_policy(available_moves, &random_engine);
        // std::cout<<"random move row,col="<<random_move.move_row<<random_move.move_col << '\n';
        board.act(random_move);
        // board.print();
    }
    if (result.winner == '-')
    {
        return 0;
    }
    else if (result.winner == player)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    

}

Move MCTS::get_best_move(Board& board)
{
    for (int i = 0; i<n_rollouts; i++)
    {
        // printf("Epoch = %d \n",i);
        rollout(board);
    }
    

    // print win rate of each child node
    for (auto child:root->children)
    {
        printf("num_visits of move %d,%d = %d/%d \n",child->move.move_row,child->move.move_col, child->num_visits,n_rollouts);
    }
  
    Node* best_child = *std::max_element(root->children.begin(), root->children.end(),
		[](Node* a, Node* b) { return a->num_visits < b->num_visits;});

    // best_move = best_child->move;
    return best_child->move;
}

void MCTS::update_tree(Move move)
{
    // delete root;
    // root = new Node(nullptr, move);
    root = std::unique_ptr<Node>(new Node(nullptr, move));
}

template<typename RandomEngine>
Move MCTS::random_policy(std::vector<Move>& moves, RandomEngine* engine)
{
    std::uniform_int_distribution<int> moves_distribution(0, moves.size() - 1);
    return moves[moves_distribution(*engine)];
}