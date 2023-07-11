#include "view.hxx"
#include <chrono>

static Dim const player_dims = {50,50};
static Dim const horizontal_wall_dims = {10, 50};
static Dim const vertical_wall_dims = {50, 10};
static Dim const rivulet_dims = {10,10};
static std::string const music_filename {"relaxingsure.mp3"};
// music from Guustavv, copyright free

View::View(Model const& model, ge211::Mixer& mixer_)
        :  model_(model),
        mixer_(mixer_),
        player_spot(player_dims, ge211::Color(255,0,100)),
        rivulet(rivulet_dims, ge211::Color::black()),
        horizontal_wall(horizontal_wall_dims, ge211::Color::white()),
        vertical_wall(vertical_wall_dims, ge211::Color::white()),
        bruce_sprite(player_dims.height/2, ge211::Color::black()),
        rachel_sprite(player_dims.height/2, ge211::Color(255,255,100)),
        potential_horizontal_wall({horizontal_wall_dims.width, 2*horizontal_wall_dims.height + 10}, ge211::Color::medium_cyan()),
        potential_vertical_wall({2*horizontal_wall_dims.height + 10,horizontal_wall_dims.width }, ge211::Color::medium_cyan()),
        highlight_sprite(player_dims, ge211::Color(255,100,100)),
        place_horizontal_wall(horizontal_wall_dims, ge211::Color::medium_cyan()),
        place_vertical_wall(vertical_wall_dims, ge211::Color::medium_cyan()),
        place_rivulet_wall(rivulet_dims,ge211::Color::medium_cyan())

{
    title_displays_ = true;
    timer_ = 3.0;  // Title disappears after 3 seconds
    ge211::Text_sprite::Builder title_builder(cool_font);
    title_builder.color(ge211::Color::white()) << "QUORIDOR";
    QUORIDOR_title_sprite.reconfigure(title_builder);

    ge211::Text_sprite::Builder ellen_and_rhys_builder(impact);
    ellen_and_rhys_builder.color(ge211::Color::white()) << "By Rhys and Ellen";
    by_rhys_and_ellen_sprite.reconfigure(ellen_and_rhys_builder);

    ge211::Text_sprite::Builder label_builder(sans30);
    label_builder.color(ge211::Color::white()) << "Moves made:";
    label_sprite.reconfigure(label_builder);

    if (mixer_.is_enabled()) {
        load_audio_();
    }
}

void
View::draw(ge211::Sprite_set& set, Pos mouse_posn)
{
    if (title_displays_) {
        set.add_sprite(QUORIDOR_title_sprite, {65, 200}, 10);
        set.add_sprite(by_rhys_and_ellen_sprite, {123, 275});
    } else {

    // initialize grid
    for (int row = 0; row < 17; ++row) {
        for (int col = 0; col < 17; ++col) {
            Pos board_pos {col, row};
            Pos screen_pos = board_to_screen(board_pos);

            // If the row and col are both even, it's a Player Spot
            if (row % 2 == 0 && col % 2 == 0) {
                set.add_sprite(player_spot, screen_pos, 0);
            }
                // If the row and col are both odd, it's a Rivulet
            else if (row % 2 != 0 && col % 2 != 0) {
                set.add_sprite(rivulet, screen_pos,0);
            }
                // If the row is odd and col is even, it's a vertical Wall
            else if (row % 2 != 0 && col % 2 == 0) {
                set.add_sprite(vertical_wall, screen_pos,0);
            }
                // If the row is even and col is odd, it's a horizontal Wall
            else if (row % 2 == 0 && col % 2 != 0) {
                set.add_sprite(horizontal_wall, screen_pos,0);
            }
        }
    }

    // draw players
    Pos bruce_position = model_.get_player_position(cell_state::bruce);
    Pos rachel_position = model_.get_player_position(cell_state::rachel);

    set.add_sprite(bruce_sprite, board_to_screen(bruce_position),1 );
    set.add_sprite(rachel_sprite, board_to_screen(rachel_position),1 );

    // convert mouse position to board position
    Pos board_pos = screen_to_board(mouse_posn);
    // check if a wall can be placed at the mouse position
    if (model_.can_place_wall(board_pos)) {
        // if it can, add a potential wall sprite at the mouse position
        if (board_pos.x % 2 == 0 && board_pos.y % 2 != 0) {
            set.add_sprite(potential_vertical_wall, board_to_screen(board_pos), 1);
        } else if (board_pos.x % 2 != 0 && board_pos.y % 2 == 0) {
            set.add_sprite(potential_horizontal_wall, board_to_screen(board_pos), 1);
        }
    }
    // highlight next moves
    for (Pos move: model_.highlight_moves) {
        set.add_sprite(highlight_sprite, board_to_screen(move), 1);
    }
    // place walls
    for (size_t col = 0; col < model_.board_.grid.size(); col++) {
        for (size_t row = 0; row < model_.board_.grid[col].size(); row++) {
            const board_spot& spot = model_.board_.grid[col][row];
            Pos board_pos = {static_cast<int>(col), static_cast<int>(row)};
            if (spot.get_state() == cell_state::wall) {
                if (board_pos.x % 2 == 0 && board_pos.y % 2 != 0) {
                    set.add_sprite(place_vertical_wall, board_to_screen(board_pos), 2);
                } else if (board_pos.x % 2 != 0 && board_pos.y % 2 == 0) {
                    set.add_sprite(place_horizontal_wall, board_to_screen(board_pos), 2);
                } else {
                    set.add_sprite(place_rivulet_wall, board_to_screen(board_pos), 2);
                }
            }
        }
    }
    set.add_sprite(label_sprite, {300, 525}, 2);


    ge211::Text_sprite::Builder moves_builder(sans30);
    moves_builder.color(ge211::Color::white()) << model_.moves_made_;
    moves_sprite.reconfigure(moves_builder);
    set.add_sprite(moves_sprite, {490, 525}, 2);

    ge211::Text_sprite::Builder bruce_walls_builder(sans30);
    bruce_walls_builder.color(ge211::Color::white()) << model_.bruce_walls_remaining_;
    batman_walls_remaining_sprite.reconfigure(bruce_walls_builder);
    set.add_sprite(batman_walls_remaining_sprite, {50, 525});

    ge211::Text_sprite::Builder rachel_walls_builder(sans30);
    rachel_walls_builder.color(ge211::Color(255,255,100)) << model_.rachel_walls_remaining_;
    rachel_walls_remaining_sprite.reconfigure(rachel_walls_builder);
    set.add_sprite(rachel_walls_remaining_sprite, {10, 525});

    // display game over
    if ((model_.get_winner() == Player::bruce || model_.get_winner() == Player::rachel) && model_.get_current_turn() == Player::neither) {
        // display the game over
    }
    }



}




Pos
View::board_to_screen(Pos board_pos) const
{
    int x,y;
    // (col, row)
    int col = board_pos.x;
    int row = board_pos.y;

    int unit_width = player_dims.width + horizontal_wall_dims.width;
    int unit_height = player_dims.height + vertical_wall_dims.height;

    // vertical wall
    if (row % 2 == 0 && col % 2 != 0) { // even row and odd col
        x = unit_width * ((col+1)/2 - 1) + player_dims.width;
        y = unit_height * row/2;
    }
        // horizontal wall
    else if (col % 2 == 0 && row % 2 != 0) { // even col and odd row
        x = unit_width * col/2;
        y = unit_height * ((row+1)/2 - 1) + player_dims.height;
    }
        // rivulet
    else if (row % 2 != 0 && col % 2 != 0) { // both odd
        x = (((col+1)/2 -1) * rivulet_dims.height) + (((col+1)/2) * player_dims
                .height);
        y = (((row+1)/2 -1) * rivulet_dims.height) + (((row+1)/2) * player_dims
                .height);
     } // player spot
        else {
        x = unit_width * col/2;
        y = unit_height * row/2;
    }

    return {x, y};
}


Pos
View::screen_to_board(Pos screen_pos) const
{
    int x, y;
    // (col, row)
    int col = screen_pos.x;
    int row = screen_pos.y;

    int unit_width = player_dims.width + horizontal_wall_dims.width;
    int unit_height = player_dims.height + vertical_wall_dims.height;

    // player spot
    if (col % unit_width < player_dims.width && row % unit_height < player_dims.height) {
        x = (col / unit_width) * 2;
        y = (row / unit_height) * 2;
    }
        // horizontal wall
    else if (col % unit_width < player_dims.width) {
        x = (col / unit_width) * 2;
        y = ((row - player_dims.height) / unit_height) * 2 + 1;
    }
        // vertical wall
    else if (row % unit_height < player_dims.height) {
        x = ((col - player_dims.width) / unit_width) * 2 + 1;
        y = (row / unit_height) * 2;
    }
        // rivulet
    else {
        x = ((col - player_dims.width) / rivulet_dims.width) * 2 + 1;
        y = ((row - player_dims.height) / rivulet_dims.height) * 2 + 1;
    }

    return {x, y};
}



View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    Dimensions screen_dims = {530,580};
    return screen_dims;
}

void
View::resume_music_if_ended() const
{
    // restart music if it stops. Checked each frame
    if (mixer_.get_music_state() == ge211::Mixer::State::paused) {
        mixer_.resume_music();
    }
}

void
View::load_audio_()
{
    // Load audio

    music_.try_load(music_filename, mixer_);

    // Start background music
    mixer_.play_music(music_);
}