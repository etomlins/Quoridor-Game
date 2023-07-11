#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_, mixer()),
          mouse_position_(0,0)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, mouse_position_ );
}

void
Controller::on_mouse_move(ge211::Posn<int> position)
{
    mouse_position_ = position;
}


void
Controller::on_mouse_down(ge211::Mouse_button, ge211::Posn<int> pos)
{
    std::cout << "mouse clicked now\n";

    Pos board_position = view_.screen_to_board(pos);
    board_spot board_spot = (*model_.find_board_spot(model_.board_, board_position));
    if (board_spot.get_player() == model_.get_current_turn()) {
        std::cout << "clicked on player\n";
        model_.highlight_moves = model_.calc_next_moves();
    }
    else if (model_.is_in_highlight_next_moves(board_position)) {
        std::cout << "clicked on valid place to go\n";
        model_.play_move(board_position);
        return;

    }
    else if (model_.can_place_wall(board_position)) {
        std::cout << "should put wall now\n";
        model_.play_move(board_position);
        return;
        }
    else {
        model_.highlight_moves.clear();
    }


}
void
Controller::on_frame(double dt)
{
    if (view_.title_displays_) {
        view_.timer_ -= dt;

        if (view_.timer_ <= 0) {
            view_.title_displays_ = false;
        }

        // Check if music should be restarted
        view_.resume_music_if_ended();
    }
}

// if the position is a wall position
//     check if it's a valid wall?
//     if it's a valid wall,
//     place the wall.
//
//     if the position is a player spot
//     check that the spot is within the vector returned by calc_next_moves
//     if it is,
//     move the player to that spot.
//     advance game
//




Dim
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}


