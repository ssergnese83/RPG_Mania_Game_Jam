// Class implementation for Character

#include "character.hpp"
#include "globals.hpp"


// constructors
Character::Character() { // Default constructor
    this->name = "default";
    this->level = -1;
    this->max_hp = 10;
    this->current_hp = 10;
    this->spd = 10;
    this->atk = 10;
    this->def = 10;
    this->fire = 10;
    this->air = 10;
    this->earth = 10;
    this->lightning = 10;
    this->water = 10;
    this->loadSprite();
    this->overworld_hitbox = Rectangle {0, 0, 48, 48}; // Default overworld_hitbox is a 48x48 square at (0, 0)
    this->direction = NONE;
    this->facing_wall = false;
    this->overworld_grid_x = get_overworld_grid_x();
    this->overworld_grid_y = get_overworld_grid_y();
    this->direction_facing = NONE;

    this->battle_hitbox = Rectangle {0, 0, 3*(48), 4*(48)}; // Default battle_hitbox is a 48x96 rectangle at (0, 0)
}

// getters
std::string Character::get_name() {
    return this->name;
}

int Character::get_level() {
    return this->level;
}

int Character::get_max_hp() {
    return this->max_hp;
}

int Character::get_current_hp() {
    return this->current_hp;
}

int Character::get_spd() {
    return this->spd;
}

int Character::get_atk() {
    return this->atk;
}

int Character::get_def() {
    return this->def;
}

int Character::get_fire() {
    return this->fire;
}

int Character::get_air() {
    return this->air;
}

int Character::get_earth() {
    return this->air;
}

int Character::get_lightning() {
    return this->lightning;
}

int Character::get_water() {
    return this->water;
}

Texture2D Character::get_overworld_sprite() { // returns sprite
    return this->overworld_sprite;
}

Rectangle Character::get_overworld_hitbox() { // returns overworld_hitbox
    return this->overworld_hitbox;
}


Vector2 Character::get_overworld_pos() { // returns the character position
    Vector2 pos = {this->get_overworld_hitbox().x, this->get_overworld_hitbox().y};
    return pos;
}

Vector2 Character::get_overworld_center() { // returns the character's center position
    Vector2 pos = {this->get_overworld_pos().x + this->get_overworld_width()/2, this->get_overworld_pos().y + this->get_overworld_height()/2};
    return pos;
}

float Character::get_overworld_width() { // returns width of hitbox
    return this->overworld_hitbox.width;
}

float Character::get_overworld_height() { // returns height of hitbox
    return this->overworld_hitbox.height;
}

Direction Character::get_direction() {
    return this->direction;
}

bool Character::get_facing_wall() {
    return this->facing_wall;
}

int Character::get_overworld_grid_x() {
    return this->overworld_grid_x;
}

int Character::get_overworld_grid_y() {
    return this->overworld_grid_y;
}

Direction Character::get_direction_facing() {
    return this->direction_facing;
}

int Character::get_looking_at_x() {
    return this->looking_at_x;
}

int Character::get_looking_at_y() {
    return this->looking_at_y;
}


Texture2D Character::get_battle_sprite(int index) { // returns sprite
    return this->battle_sprite[index];
}

Rectangle Character::get_battle_hitbox() { // returns overworld_hitbox
    return this->battle_hitbox;
}


Vector2 Character::get_battle_pos() { // returns the character position
    Vector2 pos = {this->get_battle_hitbox().x, this->get_battle_hitbox().y};
    return pos;
}

Vector2 Character::get_battle_center() { // returns the character's center position
    Vector2 pos = {this->get_battle_pos().x + this->get_battle_width()/2, this->get_battle_pos().y + this->get_battle_height()/2};
    return pos;
}

float Character::get_battle_width() { // returns width of hitbox
    return this->battle_hitbox.width;
}

float Character::get_battle_height() { // returns height of hitbox
    return this->battle_hitbox.height;
}



// setters
void Character::set_name(std::string name_) {
    name_.resize(NAME_BUFF_SIZE - 1);
    this->name = name_;
}

void Character::set_level(int level_) {
    this->level = level_;
}

void Character::set_max_hp(int max_hp_) {
    this->max_hp = max_hp_;
}

void Character::set_current_hp(int current_hp_) {
    this->max_hp = current_hp_;
}

void Character::set_spd(int spd_) {
    this->spd = spd_;
}

void Character::set_atk(int atk_) {
    this->atk = atk_;
}

void Character::set_def(int def_) {
    this->def = def_;
}

void Character::set_fire(int fire_) {
    this->fire = fire_;
}

void Character::set_air(int air_) {
    this->air = air_;
}

void Character::set_earth(int earth_) {
    this->earth = earth_;
}

void Character::set_lightning(int lightning_) {
    this->lightning = lightning_;
}

void Character::set_water(int water_) {
    this->water = water_;
}

void Character::set_overworld_sprite(Texture2D sprite_) {
    this->overworld_sprite = sprite_;
}

void Character::set_overworld_hitbox(Rectangle hitbox_) {
    this->overworld_hitbox = hitbox_;
}


void Character::set_overworld_pos(Vector2 pos_) { // sets character position
    this->overworld_hitbox.x = pos_.x;
    this->overworld_hitbox.y = pos_.y;
}

void Character::set_overworld_x(float x_) { // sets x position (top left corner of hitbox)
    this->overworld_hitbox.x = x_;
}

void Character::set_overworld_y(float y_) { // sets y position (top left corner of hitbox)
    this->overworld_hitbox.y = y_;
}

void Character::set_overworld_width(float width_) { // sets width of hitbox
    this->overworld_hitbox.width = width_;
}

void Character::set_overworld_height(float height_) { // sets height of hitbox
    this->overworld_hitbox.height = height_;
}

void Character::set_direction(Direction direction_) {
    this->direction = direction_;
}

void Character::set_facing_wall(bool facing_wall_) {
    this->facing_wall = facing_wall_;
}

void Character::set_direction_facing(Direction direction_facing_) {
    this->direction_facing = direction_facing_;
}


void Character::set_battle_sprite(Texture2D sprite_, int index) {
    this->battle_sprite[index] = sprite_;
}

void Character::set_battle_hitbox(Rectangle hitbox_) {
    this->battle_hitbox = hitbox_;
}

void Character::set_looking_at_x(int x_) {
    this->looking_at_x = x_;
}

void Character::set_looking_at_y(int y_) {
    this->looking_at_y = y_;
}


void Character::set_battle_pos(Vector2 pos_) { // sets character position
    this->battle_hitbox.x = pos_.x;
    this->battle_hitbox.y = pos_.y;
}

void Character::set_battle_x(float x_) { // sets x position (top left corner of hitbox)
    this->battle_hitbox.x = x_;
}

void Character::set_battle_y(float y_) { // sets y position (top left corner of hitbox)
    this->battle_hitbox.y = y_;
}

void Character::set_battle_width(float width_) { // sets width of hitbox
    this->battle_hitbox.width = width_;
}

void Character::set_battle_height(float height_) { // sets height of hitbox
    this->battle_hitbox.height = height_;
}

//other
void Character::updateCharacter() {
    // calculate grid coords
    this->overworld_grid_x = (int)((this->get_overworld_hitbox()).x/48);
    this->overworld_grid_y = (int)((this->get_overworld_hitbox()).y/48);

    // update the grid coord we are looking at
    Direction dirfacing = this->get_direction_facing();

    switch (dirfacing) 
    {
        case NONE:
            this->set_looking_at_x(this->overworld_grid_x);
            this->set_looking_at_y(this->overworld_grid_y);
            break;
        case UP:
            this->set_looking_at_x(this->overworld_grid_x);
            this->set_looking_at_y(this->overworld_grid_y - 1);
            break;
        case RIGHT:
            this->set_looking_at_x(this->overworld_grid_x + 1);
            this->set_looking_at_y(this->overworld_grid_y);
            break;
        case DOWN:
            this->set_looking_at_x(this->overworld_grid_x);
            this->set_looking_at_y(this->overworld_grid_y + 1);
            break;
        case LEFT:
            this->set_looking_at_x(this->overworld_grid_x - 1);
            this->set_looking_at_y(this->overworld_grid_y);
            break;
    }
    
}

void Character::moveCharacter() { // moves the character based on input
    
    Direction dir = this->get_direction();
    bool facingwall = this->get_facing_wall();

    if (dir != NONE && !facingwall) 
    {
        if (dir == UP) 
        {
            this->set_overworld_y((this->get_overworld_pos()).y - (48/MOVEFRAMES));
            this->set_direction_facing(UP);
        } else if (dir == DOWN) 
        {
            this->set_overworld_y((this->get_overworld_pos()).y + (48/MOVEFRAMES));
            this->set_direction_facing(DOWN);
        } else if (dir == RIGHT) 
        {
            this->set_overworld_x((this->get_overworld_pos()).x + (48/MOVEFRAMES));
            this->set_direction_facing(RIGHT);
        } else if (dir == LEFT) 
        {
            this->set_overworld_x((this->get_overworld_pos()).x - (48/MOVEFRAMES));
            this->set_direction_facing(LEFT);
        }
    }
}

void Character::drawCharacter() { // draws the character sprite
    
    Direction dirfacing = this->get_direction_facing();
    Rectangle source;

    switch (dirfacing) 
    {
        case NONE:
            source = {0,0,48,48};
            break;
        case UP:
            source = {48,0,48,48};
            break;
        case RIGHT:
            source = {96,0,48,48};
            break;
        case DOWN:
            source = {144,0,48,48};
            break;
        case LEFT:
            source = {192,0,48,48};
            break;
    }
    
    DrawTexturePro(this->get_overworld_sprite(), source, this->get_overworld_hitbox(), {0,0}, 0, WHITE);
}

void Character::loadSprite() {
    this->overworld_sprite = LoadTexture("assets/playersheet.png");
}