#ifndef NODE_HEADER
#define NODE_HEADER

#include <vector>
#include <random>
#include <algorithm>
#include "board.hpp"
// #include <string>
// #include <memory>




// struct Action_Node
// {
//     Action_Node()
//     {
//         this->move = Move(-1,-1);
//         this->node = nullptr;
//     }
//     Move move;
//     Node* node;

// };

class Node
{
public:
    Node* parent;
    std::vector<Node*> children;
    Move move;
    int num_visits;

    Node(Node* parent, Move move);
    ~Node();

    double get_uct();
    Node* select_uct();
    void expand(Board& board);
    void update(int leaf_value);
    void update_recursive(int leaf_value);
    bool is_leaf();
    bool is_root();
    void set_parent(Node* parent);
    

private:
    
    
    // char player_to_move;
    double q_value;
    double u_value;

    void update(double leaf_value);


};


#endif