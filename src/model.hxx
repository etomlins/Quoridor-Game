#pragma once

#include <ge211.hxx>
#include "board.hxx"
#include <iostream>

// Make Dim, Pos, and Rect their own thing
using Dim = ge211::Dims<int>;
using Pos = ge211::Posn<int>;
using Rect = ge211::Rect<int>;

class Model
{
public:
 Model()
 :  moves_made_(0),
    bruce_walls_remaining_(10),
    rachel_walls_remaining_(10),
    turn_(Player::bruce)
    {};

 Player get_current_turn() const {
     return turn_;
 }

 Player get_winner() const {
     return winner_;
 }


Pos get_turn_position() const;


 // check game over
bool check_game_over();
int player_adjacent(board_spot) const;
Player other_player(Player player);
bool check_boundary_x(Pos) const;
bool check_boundary_y(Pos) const;
void advance_game();
void move_player(Player& player, Pos new_position);
// place wall
bool can_place_wall(Pos board_pos) const;
// calculate next moves
std::vector<Pos> calc_next_moves() const;
// move player
void play_move();
void initialize_players();
void switch_turn();
Pos get_player_position(cell_state player) const;
void move_player(board_spot& destination_spot);
const board_spot* find_board_spot(const Board& board, const Pos& position) const;
bool is_move_valid(std::vector<Pos>& valid_moves, Pos p) const;
void play_move(Pos pos);
Player check_winner();
void place_wall(board_spot& destination);
bool is_in_highlight_next_moves(Pos p);
board_spot* retrieve_board_spot(Board& board, const Pos& position);


    Board board_;
    std::vector<Pos> highlight_moves;
    int moves_made_;
    int bruce_walls_remaining_;
    int rachel_walls_remaining_;


private:
    Player turn_;
    Player winner_ = Player::neither;
    void really_play_move_();

};
