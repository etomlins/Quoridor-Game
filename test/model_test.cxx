#include "model.hxx"
#include <catch.hxx>
#include <algorithm>

TEST_CASE("Test board initialization")
{
    Model m;

    CHECK(m.board_.grid[8][0].get_state() == cell_state::rachel);
    CHECK(m.board_.grid[8][16].get_state() == cell_state::bruce);
    CHECK(m.board_.grid[8][0].get_player() == Player::rachel);
    CHECK(m.board_.grid[8][16].get_player() == Player::bruce);

    for (size_t i = 0; i < 17; i++) {
        for (size_t j = 0; i < 17; i++) {
            if (!(i == 8 && (j == 0 || j == 16))) {
                CHECK(m.board_.grid[i][j].get_player() == Player::neither);
                CHECK(m.board_.grid[i][j].get_state() == cell_state::empty);
            }
        }
    }
}

TEST_CASE("Check that someone wins")
{
    Model m;
    while (!m.check_game_over()) {
        std::vector<Pos> valid_moves = m.calc_next_moves();
        Pos target_pos = {0,0};

        for (Pos move : valid_moves) {
            if (m.is_move_valid(valid_moves, move)) {
                target_pos = move;
                break;
            }
        }
        m.play_move(target_pos);
    }

    Player winner = m.get_winner();
    CHECK(m.check_game_over());
    bool did_bruce_win = winner == Player::bruce;
    CHECK(did_bruce_win);

}
TEST_CASE("Test Rachel jumping over Bruce") //1
{
    Model m;
    m.switch_turn(); // make it bruce's turn

    // move bruce to {8,2}
    m.move_player(*(m.retrieve_board_spot(m.board_, {8, 2})));

    std::vector<Pos> valid_moves = m.calc_next_moves();
    bool jump_move_present = false;
    for (const Pos& move : valid_moves) {
        if (move == Pos{8, 4}) {
            jump_move_present = true;
            break;
        }
    }
    CHECK(jump_move_present);

    m.play_move({8, 4});

    board_spot rachel_previous_spot = *(m.retrieve_board_spot(m.board_, {8, 0}));
    board_spot rachel_target_spot = *(m.retrieve_board_spot(m.board_, {8, 4}));

    CHECK(rachel_previous_spot.get_state() == cell_state::empty);
    CHECK(rachel_previous_spot.get_player() == Player::neither);
    CHECK(rachel_target_spot.get_state() == cell_state::rachel);
    CHECK(rachel_target_spot.get_player() == Player::rachel);
}
TEST_CASE("Check borders don't return moves out of bounds")
{
    Model m;
    // move rachel to {0,0}
    m.move_player(*(m.retrieve_board_spot(m.board_, {0, 0})));
    m.play_move({0,0});

    m.switch_turn();
    std::vector<Pos> valid_moves = m.calc_next_moves();
    bool jump_move_present = true;

    for (const Pos& move : valid_moves) {
        if (move == Pos{0, -1} || move == Pos{-1,0}) {
            jump_move_present = false;
        }
    }
    CHECK(jump_move_present);
}
TEST_CASE("Test jump with wall") {
    Model m;
    m.place_wall(*(m.retrieve_board_spot(m.board_, {8, 3})));

    m.switch_turn(); // make it bruce's turn

    // move bruce to {8,2}
    m.play_move({8,2});

    //now it's rachel's turn. Check that {8,4} IS NOT in her valid_moves
    std::vector<Pos> valid_moves = m.calc_next_moves();
    bool is_eight_four_in_valid_moves = false;
    for (const Pos& move : valid_moves) {
        if (move == Pos{8, 4}) {
            is_eight_four_in_valid_moves = true;
            break;
        }
    }
    CHECK(!is_eight_four_in_valid_moves);

    m.place_wall(*(m.retrieve_board_spot(m.board_, {9, 0})));
    std::vector<Pos> moves = m.calc_next_moves();
    bool is_ten_two_in_moves = false;
    for (const Pos& move : moves) {
        if (move == Pos{10, 2}) {
            is_ten_two_in_moves = true;
            break;
        }
    }
    CHECK(!is_ten_two_in_moves);

}




// TEST_CASE("Test Bruce jumping to the side of rachel") //2
// {
//     Model m;
//     // m.place_wall(*(m.retrieve_board_spot(m.board_, {8, 1})));
//     // m.place_wall(*(m.retrieve_board_spot(m.board_, {9, 1})));
//     // m.place_wall(*(m.retrieve_board_spot(m.board_, {9, 2})));
//     // m.place_wall(*(m.retrieve_board_spot(m.board_,{8, 2})));
//
//     m.move_player(*(m.retrieve_board_spot(m.board_, {8, 2})));
//
//     std::vector<Pos> valid_moves = m.calc_next_moves();
//     bool side_move_present = false;
//     for (const Pos& move : valid_moves) {
//         if (move == Pos{8, 4}) {
//             side_move_present = true;
//             break;
//         }
//     }
//     CHECK(side_move_present);
//
//     m.play_move({8, 4});
//
//     board_spot rachel_previous_spot = *(m.retrieve_board_spot(m.board_, {8, 2}));
//     board_spot bruce_target_spot = *(m.retrieve_board_spot(m.board_, {8, 0}));
//
//     CHECK(rachel_previous_spot.get_state() == cell_state::empty);
//     CHECK(rachel_previous_spot.get_player() == Player::neither);
//     CHECK(bruce_target_spot.get_state() == cell_state::bruce);
//     CHECK(bruce_target_spot.get_player() == Player::bruce);
// }
// TEST_CASE("Test Bruce jumping over Rachel") //3
// {
//     Model m;
//     m.place_wall(*(m.retrieve_board_spot(m.board_, {8, 1})));
//     m.place_wall(*(m.retrieve_board_spot(m.board_, {9, 1})));
//     m.place_wall(*(m.retrieve_board_spot(m.board_, {9, 2})));
//     m.place_wall(*(m.retrieve_board_spot(m.board_,{8, 2})));
//
//     m.move_player(*(m.retrieve_board_spot(m.board_, {8, 3})));
//
//     std::vector<Pos> valid_moves = m.calc_next_moves();
//     bool jump_move_present = false;
//     for (const Pos& move : valid_moves) {
//         if (move == Pos{6, 3}) {
//             jump_move_present = true;
//             break;
//         }
//     }
//     CHECK(jump_move_present);
//
//     m.play_move({6, 3});
//
//     board_spot rachel_previous_spot = *(m.retrieve_board_spot(m.board_, {7, 2}));
//     board_spot bruce_target_spot = *(m.retrieve_board_spot(m.board_, {6, 3}));
//
//     CHECK(rachel_previous_spot.get_state() == cell_state::empty);
//     CHECK(rachel_previous_spot.get_player() == Player::neither);
//     CHECK(bruce_target_spot.get_state() == cell_state::bruce);
//     CHECK(bruce_target_spot.get_player() == Player::bruce);
// }