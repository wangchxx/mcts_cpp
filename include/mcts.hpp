#ifndef MCTS_HEADER
#define MCTS_HEADER

#include "board.hpp"
#include "node.hpp"
#include <random>
#include <memory>
class MCTS
{
private:
    // Node* root;
    std::unique_ptr<Node> root;
    int n_rollouts;
    std::default_random_engine random_engine;
    void rollout(Board board);
    int evaluate_rollout(Board& board);

public:
    MCTS(int n_rullouts);
    ~MCTS();

    Move get_best_move(Board& board);
    void update_tree(Move move);
    template<typename RandomEngine>
    Move random_policy(std::vector<Move>& moves, RandomEngine* engine);


};



#endif