#ifndef character_hpp
#define character_hpp

#include "globals.hpp"

class Character {
private:
    // stats stuff
    std::string name;
    int level;
    int hp;
    int spd;
    int atk;
    int def;
    int fire;
    int air;
    int earth;
    int lightning;
    int water;

    // overworld stuff
    Texture2D overworld_sprite[6];
    Rectangle overworld_hitbox;
    Direction direction;
    bool facing_wall;
    int overworld_grid_x;
    int overworld_grid_y;

    // battle stuff
    Texture2D battle_sprite[6];
    Rectangle battle_hitbox;
    
public:
    // constructors
    Character(); // Default constructor

    // getters
    std::string get_name();
    int get_level();
    int get_hp();
    int get_spd();
    int get_atk();
    int get_def();
    int get_fire();
    int get_air();
    int get_earth();
    int get_lightning();
    int get_water();

    Texture2D get_overworld_sprite(int index); // returns overworld_sprite
    Rectangle get_overworld_hitbox(); // returns overworld_hitbox
    
    Vector2 get_overworld_pos(); // returns the character position
    Vector2 get_overworld_center(); // returns the character's center position
    float get_overworld_width(); // returns width of overworld_hitbox
    float get_overworld_height(); // returns height of overworld_hitbox
    Direction get_direction();
    bool get_facing_wall();
    int get_overworld_grid_x();
    int get_overworld_grid_y();

    Texture2D get_battle_sprite(int index);
    Rectangle get_battle_hitbox();

    Vector2 get_battle_pos();
    Vector2 get_battle_center();
    float get_battle_width(); // returns width of battle_hitbox
    float get_battle_height(); // returns height of battle_hitbox

    // setters
    void set_name(std::string name_);
    void set_level(int level_);
    void set_hp(int hp_);
    void set_spd(int spd_);
    void set_atk(int atk_);
    void set_def(int def_);
    void set_fire(int fire_);
    void set_air(int air_);
    void set_earth(int earth_);
    void set_lightning(int lightning_);
    void set_water(int water_);

    void set_overworld_sprite(Texture2D sprite_, int index); // sets sprite
    void set_overworld_hitbox(Rectangle overworld_hitbox_); // sets overworld_hitbox

    void set_overworld_pos(Vector2 pos_); // sets character position
    void set_overworld_x(float x_); // sets x position (top left corner of overworld_hitbox)
    void set_overworld_y(float y_); // sets y position (top left corner of overworld_hitbox)
    void set_overworld_width(float width_); // sets width of overworld_hitbox
    void set_overworld_height(float height_); // sets height of overworld_hitbox
    void set_direction(Direction direction_);
    void set_facing_wall(bool facing_wall_);

    void set_battle_sprite(Texture2D sprite_, int index);
    void set_battle_hitbox(Rectangle battle_hitbox_);

    void set_battle_pos(Vector2 pos_);
    void set_battle_x(float x_); // sets x position (top left corner of battle_hitbox)
    void set_battle_y(float y_); // sets y position (top left corner of battle_hitbox)
    void set_battle_width(float width_); // sets width of battle_hitbox
    void set_battle_height(float height_); // sets height of battle_hitbox

    //other
    void updateCharacter();
    void moveCharacter(); // moves the character based on input
    void drawCharacter(); // draws the character sprite
    void loadSprite();
};

#endif // character_hpp