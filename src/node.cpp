#include "../include/node.hpp"

Node::Node(Node* parent_, Move move_):
    parent(parent_),
    num_visits(0),
    q_value(0),
    u_value(0),
    move(move_)
{}

Node::~Node()
{
    for(auto child:children)
    {
        delete child;
    }
}



double Node::get_uct()
{
    u_value = std::sqrt(2.0 * std::log(double(parent->num_visits + 1)) / double(this->num_visits + 1));
    double uct = q_value + u_value;
    return uct;
}

Node* Node::select_uct()
{
    
    return *std::max_element(children.begin(), children.end(),
		[](Node* a, Node* b) { return a->get_uct() < b->get_uct(); });
    

}
void Node::expand(Board& board)
{
    std::vector<Move> available_moves = board.get_available_moves();
    if (!available_moves.empty())
    {
        for (Move move:available_moves)
        {
            Node* new_node = new Node(this, move);
            children.push_back(new_node);
        }
    }
}
void Node::update(int leaf_value)
{
    num_visits++;
    q_value += 1.0*(double(leaf_value) - q_value)/double(num_visits);
}
void Node::update_recursive(int leaf_value)
{
    // if not root, its parent should be updated first
    if (!is_root())
    {
        parent->update_recursive(-leaf_value);
    }
    update(leaf_value);
}
bool Node::is_leaf()
{
    return children.empty();
}
bool Node::is_root()
{   
    bool root = parent == nullptr;
    return root;
}

void Node::set_parent(Node* prt)
{
    parent = prt;
}