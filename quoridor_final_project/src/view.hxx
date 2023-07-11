#pragma once

#include "model.hxx"




class View
{
public:
    using Dimensions = ge211::Dims<int>;

    explicit View(Model const& model, ge211::Mixer& mixer_);

    void draw(ge211::Sprite_set& set, Pos);

    Pos board_to_screen(Pos) const;
    Pos screen_to_board(Pos) const;
    Dimensions initial_window_dimensions() const;
    ge211::Music_track music_;
    Model const& model_;
     ge211::Mixer& mixer_;
    void resume_music_if_ended() const;
    bool title_displays_;
    double timer_;
    ge211::Text_sprite QUORIDOR_title_sprite;
    ge211::Text_sprite by_rhys_and_ellen_sprite;

private:
    void load_audio_();

    ge211::Font sans30{"sans.ttf",30};
    ge211::Font cool_font{"Academy Engraved LET Fonts.ttf",70};
    ge211::Font impact{"Impact.ttf",40};
    ge211::Rectangle_sprite const player_spot;
    ge211::Rectangle_sprite const rivulet;
    ge211::Rectangle_sprite const horizontal_wall;
    ge211::Rectangle_sprite const vertical_wall;
    ge211::Circle_sprite const bruce_sprite;
    ge211::Circle_sprite const rachel_sprite;
    ge211::Rectangle_sprite const potential_horizontal_wall;
    ge211::Rectangle_sprite const potential_vertical_wall;
    ge211::Rectangle_sprite const highlight_sprite;
    ge211::Rectangle_sprite const place_horizontal_wall;
    ge211::Rectangle_sprite const place_vertical_wall;
    ge211::Rectangle_sprite const place_rivulet_wall;
    ge211::Text_sprite label_sprite;
    ge211::Text_sprite moves_sprite;
    ge211::Text_sprite game_start_sprite;
    ge211::Text_sprite rachel_walls_remaining_sprite;
    ge211::Text_sprite batman_walls_remaining_sprite;


};
