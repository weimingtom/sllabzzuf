#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "unit.h"
#include "particlesystem.h"

class Player: public Unit{
    private:
    int frame;
    int framebuffer;
    int max_hp;
    int mp;
    int spell_bonus;
    int spells_known;
    int active_spell;
    bool faceing_left;
    bool frame_dir_left;
    int jump_timer;
    int dash_timer;
    int dash_direction;
    int user_x_acc;
    int user_y_acc;
    int x_velocity;
    int y_velocity;
    int x_acceleration;
    int y_acceleration;
    std::list<ParticleSystem> systems;
    std::string map_filename;
    SDL_Rect fuzzRIGHT[3];
    SDL_Rect fuzzLEFT[3];

    public:
    Player();
    void load_profile();
    void save_profile();
    void load_sprite();
    void clip_fuzzy();
    void display_player(SDL_Surface *screen, int camera_x, int camera_y);
    void display_all_particles(SDL_Surface *screen, int camera_x, int camera_y, int mapw, int maph);
    void setFrame(int framenum);
    void nextFrame();
    int get_active_spell();
    int get_max_hp();
    int get_mp();
    int get_spell_bonus();
    int get_spells_known();
    std::string get_map_filename();
    void set_map_filename(std::string filename);
    void add_spell_bonus(int amount);
    void add_max_hp(int amount);
    void add_mp(int amount);
    void add_spells_known(int amount);
    void set_faceing_left(bool face);
    void set_user_x_move(int amount);
    void set_user_y_move(int amount);
    void move_player(Stage stage);
    void jump(Stage stage);
    void dash(int direction);
    void manage_particle_systems();
};

#endif // PLAYER_H_INCLUDED
