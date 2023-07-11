#include "model.hxx"
#include <iostream>
#include "board.cxx"

#include <algorithm>


const board_spot* Model::find_board_spot(const Board& board, const Pos& position) const {

    if (!check_boundary_x(position) || !check_boundary_y(position)) {
        return nullptr;
    }

    for (size_t col = 0; col < board.grid.size(); col++) {
        for (size_t row = 0; row < board.grid[col].size(); row++) {
            const board_spot& spot = board.grid[col][row];
            if (spot.get_position() == position) {
                return &spot;
            }
        }
    }
    return nullptr;
}

board_spot* Model::retrieve_board_spot(Board& board, const Pos& position) {

    if (!check_boundary_x(position) || !check_boundary_y(position)) {
        return nullptr;
    }

    for (size_t col = 0; col < board.grid.size(); col++) {
        for (size_t row = 0; row < board.grid[col].size(); row++) {
            board_spot& spot = board.grid[col][row];
            if (spot.get_position() == position) {
                return &spot;
            }
        }
    }
    return nullptr;
}

Pos Model::get_turn_position() const {

    for (size_t col = 0; col < board_.grid.size(); col++) {
        for (size_t row = 0; row < board_.grid[col].size(); row++) {
            if (board_.grid[col][row].get_player() == turn_) {
                return board_.grid[col][row].get_position();
            }
        }
    }
    throw std::runtime_error("Player not found on  board");
}

// helper function: check if there is an adjacent player
int Model::player_adjacent(board_spot player_spot) const {
    Pos player_pos = player_spot.get_position();
    // Check right
    if (player_pos.x + 2 < 17 &&
        (board_.grid[player_pos.x + 2][player_pos.y].get_state() == cell_state::bruce ||
         board_.grid[player_pos.x + 2][player_pos.y].get_state() == cell_state::rachel)) {
        return 3;
    }
    // Check left
    if (player_pos.x - 2 >= 0 &&
        (board_.grid[player_pos.x - 2][player_pos.y].get_state() == cell_state::bruce ||
         board_.grid[player_pos.x - 2][player_pos.y].get_state() == cell_state::rachel)) {
        return 4;
    }
    // Check down
    if (player_pos.y + 2 < 17 &&
        (board_.grid[player_pos.x][player_pos.y + 2].get_state() == cell_state::bruce ||
         board_.grid[player_pos.x][player_pos.y + 2].get_state() == cell_state::rachel)) {
        return 2;
    }
    // Check up
    if (player_pos.y - 2 >= 0 &&
        (board_.grid[player_pos.x][player_pos.y - 2].get_state() == cell_state::bruce ||
         board_.grid[player_pos.x][player_pos.y - 2].get_state() == cell_state::rachel)) {
        return 1;
    }
    // No adjacent player
    return 0;
}
bool Model::check_boundary_x (Pos position) const {
     if (position.x >= 0 && position.x < 17) {
     return true;
     } else {
     return false;
     }
 }
bool Model::check_boundary_y (Pos position) const {
    if (position.y >= 0 && position.y < 17) {
        return true;
    } else {
        return false;
    }
}
// std::vector<Pos> Model::calculate_next_moves(Pos player_position) const {
//
// }


// switches
void Model::advance_game() {
//    std::vector<Pos> valid_moves = calculate_next_moves(turn_);

    switch_turn();
    if (check_game_over()) {
        turn_ = Player::neither;
    }
}
//
void Model::switch_turn() {
    if (turn_ == Player::bruce) {
        turn_ = Player::rachel;
    } else {
        turn_ = Player::bruce;
    }
}


Pos Model::get_player_position(cell_state player) const
{
    for (size_t col = 0; col < board_.grid.size(); col++) {
        for (size_t row = 0; row < board_.grid[col].size(); row++) {
            if (board_.grid[col][row].get_state() == player) {
                return board_.grid[col][row].get_position();
            }
        }
    }
    throw std::runtime_error("Player not found on board");
}




// check wall
// Pos
// place_wall(Pos mouse_pos) {
//     //if  mouse_pos is over a wall
//     if (screen_to_board(mouse_pos) == placed_wall) {
//         // dont do anything
//     }
//     if (screen_to_board(mouse_pos) + one over in x and y)
//     // dont do anything
//     {
//
//     }
//     if (screen_to_board(mouse_pos) is in the boundaries) {
//
//     }
//
//
// }


// bruce starts at top (row 0), rachel starts at bottom (row 16)


bool Model::check_game_over()
{
    // Check the top row for Rachel
    for (auto& cell : board_.grid[0]) {
        if (cell.get_state() == cell_state::rachel) {
            return true;
        }
    }
    // Check the bottom row for Bruce
    for (auto& cell : board_.grid[16]) {
        if (cell.get_state() == cell_state::bruce) {
            return true;
        }
    }
    return false;
}

Player Model::check_winner()
{
    // Check the top row for Rachel
    for (auto& cell : board_.grid[0]) {
        if (cell.get_state() == cell_state::rachel) {
            return Player::rachel;
        }
    }
    // Check the bottom row for Bruce
    for (auto& cell : board_.grid[16]) {
        if (cell.get_state() == cell_state::bruce) {
            return Player::bruce;
        }
    }
    return Player::neither;
}

bool Model::can_place_wall(Pos board_pos) const
{
    if (find_board_spot(board_, board_pos) != nullptr) {
        board_spot new_pos = *(find_board_spot(board_, board_pos));
        if (new_pos.get_x() % 2 == 0 && new_pos.get_y() % 2 == 0) { // if it's a player spot....
            return false;
        }
    } else {
        return false;
    }

    // check that spot is empty
    const board_spot* potential_wall_spot = find_board_spot(board_, board_pos);
    if (potential_wall_spot == nullptr || potential_wall_spot->get_state() == cell_state::wall) {
        return false;
    }

    Pos next_spot = {0,0};

    // this checks if there's a wall in the way parallel to the wall being placed
    if (potential_wall_spot->get_x() % 2 == 0) {  //case where it's a horizontal wall
        next_spot = {potential_wall_spot->get_x() + 2, potential_wall_spot->get_y()};
        if (!check_boundary_x(next_spot) ||
            (find_board_spot(board_, next_spot) != nullptr &&
             find_board_spot(board_, next_spot)->get_state() == cell_state::wall)) {
            return false;
        }
    } else {  //case for vertical wall
        next_spot = {potential_wall_spot->get_x(), potential_wall_spot->get_y() + 2};
        if (!check_boundary_y(next_spot) ||
            (find_board_spot(board_, next_spot) != nullptr &&
             find_board_spot(board_, next_spot)->get_state() == cell_state::wall)) {
            return false;
        }
    }

    // This checks for a perpendicular wall
    if (potential_wall_spot->get_x() % 2 == 0) { // Horizontal wall
        next_spot = {potential_wall_spot->get_x() + 1, potential_wall_spot->get_y()};
        if (
            find_board_spot(board_, next_spot) != nullptr &&
            find_board_spot(board_, next_spot)->get_state() == cell_state::wall) {
            return false;
        }
    } else { // Vertical wall
        next_spot = {potential_wall_spot->get_x(), potential_wall_spot->get_y() + 1};
        if (find_board_spot(board_, next_spot) != nullptr &&
            find_board_spot(board_, next_spot)->get_state() == cell_state::wall) {
            return false;
        }
    }
    if (turn_ == Player::rachel){
        if (bruce_walls_remaining_ == 0) {
            return false;
        }
    } else if (turn_ == Player::bruce){
        if (rachel_walls_remaining_ == 0){
            return false;
        }
    }
    return true;
}





// calculate next moves
//std::vector<Pos> calculate_next_moves(Pos) ;

// move player
//void play_move();


std::vector<Pos> Model::calc_next_moves() const {
    Pos player_pos = get_turn_position();
    board_spot player_board_spot = *find_board_spot(board_, player_pos);
    std::vector<Pos> valid_moves_vector;
    Pos up_pos(player_pos.x, player_pos.y - 2);
    Pos down_pos(player_pos.x, player_pos.y + 2);
    Pos left_pos(player_pos.x - 2, player_pos.y);
    Pos right_pos(player_pos.x + 2, player_pos.y);

    if (player_adjacent(player_board_spot) != 0)
    {
        switch (player_adjacent(player_board_spot))
        {
        case 1: // if there's a guy up
            if (check_boundary_y(up_pos) && find_board_spot(board_, {up_pos.x, up_pos.y - 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({up_pos.x, up_pos.y - 2});
            }
            else if (find_board_spot(board_,{up_pos.x, up_pos.y - 1})->get_state() == cell_state::wall)
            {
                if (find_board_spot(board_, {up_pos.x + 1,up_pos.y})->get_state() != cell_state::wall && check_boundary_x({up_pos.x + 2,up_pos.y}) && check_boundary_y({up_pos.x + 2, up_pos.y}))
                {
                    valid_moves_vector.push_back({player_pos.x + 2, player_pos.y - 2});
                }
                if (find_board_spot(board_,{up_pos.x -1,up_pos.y})->get_state() != cell_state::wall && check_boundary_x({up_pos.x - 2,up_pos.y})  && check_boundary_y({up_pos.x - 2,up_pos.y}))
                {
                    valid_moves_vector.push_back({player_pos.x - 2, player_pos.y - 2});
                }
            }

            if (check_boundary_x({player_pos.x+2, player_pos.y}) && find_board_spot(board_,{player_pos.x + 1, player_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x+2, player_pos.y});
            }
            if (check_boundary_x({player_pos.x-2, player_pos.y}) && find_board_spot(board_,{player_pos.x - 1, player_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x-2, player_pos.y});
            }
            if (check_boundary_y({player_pos.x, player_pos.y+2}) && find_board_spot(board_, {player_pos.x, player_pos.y + 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x, player_pos.y+2});
            }
            break;

        case 2: // if there's a guy down
            if (check_boundary_y(down_pos) && find_board_spot(board_,{down_pos.x, down_pos.y + 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({down_pos.x, down_pos.y+2});
            }
            else if (find_board_spot(board_,{down_pos.x, down_pos.y + 1})->get_state() == cell_state::wall)
            {
                if (find_board_spot(board_,{down_pos.x-1, down_pos.y })->get_state() != cell_state::wall && check_boundary_x({down_pos.x-2,down_pos.y}) && check_boundary_y({down_pos.x-2,down_pos.y}))
                {
                    valid_moves_vector.push_back({player_pos.x-2, player_pos.y+2});
                }
                if (find_board_spot(board_,{down_pos.x+1, down_pos.y})->get_state() != cell_state::wall && check_boundary_x({down_pos.x+2, down_pos.y}) && check_boundary_y({down_pos.x+2, down_pos.y}))
                {
                    valid_moves_vector.push_back({player_pos.x+2, player_pos.y+2});
                }
            }

            if (check_boundary_x({player_pos.x + 2, player_pos.y}) && find_board_spot(board_,{player_pos.x + 1,player_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x+2,player_pos.y});
            }
            if (check_boundary_x({player_pos.x - 2, player_pos.y}) && find_board_spot(board_,{player_pos.x - 1,player_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x-2,player_pos.y});
            }
            if (check_boundary_y({player_pos.x, player_pos.y - 2}) && find_board_spot(board_, {player_pos.x, player_pos.y - 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x,player_pos.y-2});
            }
            break;

        case 3: //
            if (check_boundary_x(right_pos) && find_board_spot(board_,{right_pos.x + 1,right_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({right_pos.x + 2, right_pos.y});
            }
            else if (find_board_spot(board_,{right_pos.x + 1, right_pos.y})->get_state() == cell_state::wall)
            {
                if (find_board_spot(board_,{right_pos.x, right_pos.y - 1})->get_state() != cell_state::wall
                && check_boundary_y({right_pos.x,right_pos.y-2}) && check_boundary_x({right_pos.x,right_pos.y-2}))
                {
                    valid_moves_vector.push_back({player_pos.x + 2, player_pos.y - 2});
                }
                if (find_board_spot(board_,{right_pos.x, right_pos.y + 1})->get_state() != cell_state::wall
                && check_boundary_y({right_pos.x,right_pos.y+2}) && check_boundary_x({right_pos.x,right_pos.y+2}))
                {
                    valid_moves_vector.push_back({player_pos.x + 2, player_pos.y + 2});
                }
            }
            if (check_boundary_y({player_pos.x, player_pos.y+2}) && find_board_spot(board_, {player_pos.x, player_pos.y + 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x, player_pos.y+2});
            }
            if (check_boundary_x({player_pos.x - 2, player_pos.y}) && find_board_spot(board_,{player_pos.x - 1,player_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x - 2,player_pos.y});
            }
            if (check_boundary_y({player_pos.x, player_pos.y - 2}) && find_board_spot(board_, {player_pos.x, player_pos.y - 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x,player_pos.y-2});
            }
                  break;
        case 4: //
            if (check_boundary_x(left_pos) && find_board_spot(board_,{left_pos.x - 1,left_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({left_pos.x - 2, left_pos.y});
            }
            else if (find_board_spot(board_,{left_pos.x - 1, left_pos.y})->get_state() == cell_state::wall)
            {
                if (find_board_spot(board_,{left_pos.x, left_pos.y - 1})->get_state() != cell_state::wall && check_boundary_y({left_pos.x,left_pos.y-2}) && check_boundary_x({left_pos.x,left_pos.y-2}))
                {
                    valid_moves_vector.push_back({player_pos.x - 2, player_pos.y - 2});
                }
                if (find_board_spot(board_,{left_pos.x, left_pos.y + 1})->get_state() != cell_state::wall && check_boundary_y({left_pos.x,left_pos.y+2}) && check_boundary_x({left_pos.x,left_pos.y+2}))
                {
                    valid_moves_vector.push_back({player_pos.x - 2, player_pos.y + 2});
                }
            }
            if (check_boundary_y({player_pos.x, player_pos.y+2}) && find_board_spot(board_, {player_pos.x, player_pos.y + 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x, player_pos.y+2});
            }
            if (check_boundary_x({player_pos.x + 2, player_pos.y}) && find_board_spot(board_,{player_pos.x + 1,player_pos.y})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x+2,player_pos.y});
            }
            if (check_boundary_y({player_pos.x, player_pos.y - 2}) && find_board_spot(board_, {player_pos.x, player_pos.y - 1})->get_state() != cell_state::wall)
            {
                valid_moves_vector.push_back({player_pos.x,player_pos.y-2});
            }
            break;
        }
    } else {
        if (check_boundary_y({player_pos.x, player_pos.y+2}) && find_board_spot(board_, {player_pos.x, player_pos.y + 1})->get_state() != cell_state::wall)
        {
            valid_moves_vector.push_back({player_pos.x, player_pos.y+2});
        }
        if (check_boundary_x({player_pos.x + 2, player_pos.y}) && find_board_spot(board_,{player_pos.x + 1,player_pos.y})->get_state() != cell_state::wall)
        {
            valid_moves_vector.push_back({player_pos.x+2,player_pos.y});
        }
        if (check_boundary_y({player_pos.x, player_pos.y - 2}) && find_board_spot(board_, {player_pos.x, player_pos.y - 1})->get_state() != cell_state::wall)
        {
            valid_moves_vector.push_back({player_pos.x,player_pos.y-2});
        }
        if (check_boundary_x({player_pos.x - 2, player_pos.y}) && find_board_spot(board_,{player_pos.x - 1,player_pos.y})->get_state() != cell_state::wall)
        {
            valid_moves_vector.push_back({player_pos.x - 2,player_pos.y});
        }
    }
    return valid_moves_vector;
}


// Player
// Model::other_player(Player player)
// {
//     switch (player) {
//     case Player::bruce:
//         return Player::rachel;
//     case Player::rachel:
//         return Player::bruce;
//     default:
//         return player;
//     }
// }

// bool
// Model::advance_turn_()
// {
//     // switch to the other player
//     turn_ = other_player(turn_);
//
// }
//
//



// move player to the board spot and remove from last spot
void Model::move_player(board_spot& destination)
{
    board_spot* current_pos = retrieve_board_spot(board_, get_turn_position());
    if (!current_pos) {
        std::cout << "Could not find current position on board.\n";
        return;
    }
    cell_state the_player = current_pos->get_state();

    destination.set_player(turn_);
    destination.set_state(the_player);

    moves_made_ += 1;

    current_pos->set_state(cell_state::empty);
    current_pos->set_player(Player::neither);

    std::cout<<"successfully moved player! :)";
}

void Model::place_wall(board_spot& wall_destination)
{
    std::cout<<"placing wall now :)";
    wall_destination.set_state(cell_state::wall);
    if (wall_destination.get_x() % 2 == 0 && wall_destination.get_y() % 2 != 0)// horizontal
     { // if horizontal wall
        board_spot& rivulet = *(retrieve_board_spot(board_, {wall_destination.get_x() + 1, wall_destination.get_y()}));
        board_spot& second_half_of_wall = *(retrieve_board_spot(board_, {wall_destination.get_x() +2 , wall_destination.get_y()}));
        rivulet.set_state(cell_state::wall);
        second_half_of_wall.set_state(cell_state::wall);
    }
    if (wall_destination.get_x() % 2 != 0 && wall_destination.get_y() % 2 == 0) { // if vertical wall
        board_spot& rivulet = *(retrieve_board_spot(board_, {wall_destination.get_x(), wall_destination.get_y() + 1}));
        board_spot& second_half_of_wall = *(retrieve_board_spot(board_, {wall_destination.get_x(), wall_destination.get_y() + 2}));
        rivulet.set_state(cell_state::wall);
        second_half_of_wall.set_state(cell_state::wall);
    }


    if (turn_ == Player::rachel) {
        bruce_walls_remaining_ += -1;
    } else {
        rachel_walls_remaining_ += -1;
    }

}

bool Model::is_in_highlight_next_moves(Pos p) {
    bool found = false;
    for (auto thing : highlight_moves) {
        if (p == thing) {
            found = true;
        }
    }
    return found;
}

void Model::really_play_move_() {
    advance_game();
    if (turn_ == Player::neither) {
        winner_ = check_winner();
    }
}

bool Model::is_move_valid(std::vector<Pos>& valid_moves, Pos p) const
{
    Player current = turn_;
    std::cout << "Running find_move....";
    std::cout << "CURRENT PLAYER IS...." << current << "\n";
    auto it = std::find(valid_moves.begin(), valid_moves.end(), p);
    if (it != valid_moves.end()) {
        std::cout<<"you can place move a player here! :) :) \n";
        return true;
    } else if (can_place_wall(p)) {
        std::cout<<"you can place a wall here! :) \n";
        return true;
    }

    return false;
}

void Model::play_move(Pos p)
{
    std::vector<Pos> valid_moves = calc_next_moves();
    std::cout<<"running play_move \n";

    if (is_move_valid(valid_moves, p)) {
        board_spot* target_spot = retrieve_board_spot(board_,p);
        // check if the target spot is a horizontal or vertical wall

        if ((target_spot->get_x() % 2 == 0 && target_spot->get_y() % 2 != 0) || (target_spot->get_x() % 2 != 0 && target_spot->get_y() % 2 == 0) ){
            std::cout<<"placing the wall :) \n";
            place_wall(*target_spot);
        } else {
            std::cout<<"moving the player :) \n";
            move_player(*target_spot);
        }
        really_play_move_();
        highlight_moves.clear();
    }
}



