#pragma once
#include <vector>
#include "model.hxx"
#include <iostream>
using Pos = ge211::Posn<int>;

const int BOARD_SIZE = 17;
const Pos BRUCE_START_POS{0, 8};
const Pos RACHEL_START_POS{16, 8};

// (col,row)
// (odd,odd) -> rivulet
// (even,even) -> player
// (even,odd) -> horizontal
// (odd, even) -> vertical


enum class Action_Type {
    PLACE_WALL,
    MOVE
};

struct Action
{
    Action_Type type;
    Pos position;
};

enum class Player {
    bruce,
    rachel,
    neither
};
std::ostream& operator<<(std::ostream&, Player);

enum class cell_state {
    bruce,
    rachel,
    wall,
    empty
};

class board_spot {

private:
    Pos position_;
    cell_state state_;
    Player player_;

public:
    board_spot()
    : position_{0,0},
      state_(cell_state::empty),
      player_(Player::neither)
    {};


    void set_state(cell_state new_state) {
        state_ = new_state;
    }
    void set_position(Pos new_position) {
        position_ = new_position;
    }
    void set_player(Player new_player) {
        player_ = new_player;
    }
    Player get_player() const {
        return player_;
    }
    Pos get_position() const {
        return position_;
    }
    int get_x() const {
        return position_.x;
    }
    int get_y() const {
        return position_.y;
    }
    cell_state get_state() const {
        return state_;
    }


};




class Board
{
public:

    Board() : grid(BOARD_SIZE, std::vector<board_spot>(BOARD_SIZE))
    {
        initialize_grid();
        place_players();
    }
    void initialize_grid()
    {
        for (int col = 0; col < BOARD_SIZE; col++) {
            for (int row = 0; row < BOARD_SIZE; row++) {
                grid[col][row].set_state(cell_state::empty);
                grid[col][row].set_position({col, row});
            }
        }
    }

    void place_players () {
        grid[8][0].set_state(cell_state::rachel);
        grid[8][0].set_player(Player::rachel);

        grid[8][16].set_state(cell_state::bruce);
        grid[8][16].set_player(Player::bruce);
    };

public:
    std::vector<std::vector<board_spot>> grid;
};







    // bool canMove(int x, int y) const;
    // bool canPlaceWall(int x, int y, Orientation::Type orientation) const;
    // etc.

