// Class implementation for Player

#include "character.hpp"
#include "globals.hpp"


// constructors
Character::Character() { // Default constructor
    this->name = "default";
    this->hp = 10;
    this->spd = 10;
    this->atk = 10;
    this->def = 10;
    this->loadSprite();
    this->hitbox = Rectangle {0, 0, 48, 48}; // Default hitbox is a 48x48 square at (0, 0)
}

// getters
std::string Character::get_name() {
    return this->name;
}

int Character::get_hp() {
    return this->hp;
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

Texture2D Character::getSprite(int index) { // returns sprite
    return this->sprite[index];
}

Rectangle Character::getHitbox() { // returns hitbox
    return this->hitbox;
}


Vector2 Character::getPos() { // returns the player position
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Character::getCenter() { // returns the player's center position
    Vector2 pos = {this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight()/2};
    return pos;
}

float Character::getWidth() { // returns width of hitbox
    return this->hitbox.width;
}

float Character::getHeight() { // returns height of hitbox
    return this->hitbox.height;
}

// setters
void Character::set_name(std::string name_) {
    this->name = name_;
}

void Character::set_hp(int hp_) {
    this->hp = hp_;
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

void Character::setSprite(Texture2D sprite_, int index) {
    this->sprite[index] = sprite_;
}

void Character::setHitbox(Rectangle hitbox_) {
    this->hitbox = hitbox_;
}


void Character::setPos(Vector2 pos_) { // sets player position
    this->hitbox.x = pos_.x;
    this->hitbox.y = pos_.y;
}

void Character::setX(float x_) { // sets x position (top left corner of hitbox)
    this->hitbox.x = x_;
}

void Character::setY(float y_) { // sets y position (top left corner of hitbox)
    this->hitbox.y = y_;
}

void Character::setWidth(float width_) { // sets width of hitbox
    this->hitbox.width = width_;
}

void Character::setHeight(float height_) { // sets height of hitbox
    this->hitbox.height = height_;
}

//other

void Character::movePlayer() { // moves the player based on input
    
}

void Character::drawPlayer() { // draws the player sprite
    
}

void Character::loadSprite() {
    this->sprite[0] = LoadTexture("assets/player.png");
    // this->sprite[LEFT] = LoadTexture("assets/charNoSword2.png");
    // this->sprite[RIGHT] = LoadTexture("assets/charNoSword1.png");
    // this->sprite[RIGHT_SWORD] = LoadTexture("assets/charRight.png");
    // this->sprite[LEFT_SWORD] = LoadTexture("assets/charLeft.png");
    // this->sprite[SWING] = LoadTexture("assets/swing.png");
    // this->sprite[SWING_RIGHT] = LoadTexture("assets/swing_right.png");
}