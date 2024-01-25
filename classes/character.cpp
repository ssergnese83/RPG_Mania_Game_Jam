// Class implementation for Character

#include "character.hpp"
#include "globals.hpp"


// constructors
Character::Character() { // Default constructor
    this->name = "default";
    this->level = 1;
    this->hp = 10;
    this->spd = 10;
    this->atk = 10;
    this->def = 10;
    this->loadSprite();
    this->hitbox = Rectangle {0, 0, 48, 48}; // Default hitbox is a 48x48 square at (0, 0)
    this->direction = NONE;
}

// getters
std::string Character::get_name() {
    return this->name;
}

int Character::get_level() {
    return this->level;
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


Vector2 Character::getPos() { // returns the character position
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Character::getCenter() { // returns the character's center position
    Vector2 pos = {this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight()/2};
    return pos;
}

float Character::getWidth() { // returns width of hitbox
    return this->hitbox.width;
}

float Character::getHeight() { // returns height of hitbox
    return this->hitbox.height;
}

Direction Character::getDirection() {
    return this->direction;
}

// setters
void Character::set_name(std::string name_) {
    name_.resize(NAME_BUFF_SIZE - 1);
    this->name = name_;
}

void Character::set_level(int level_) {
    this->level = level_;
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


void Character::setPos(Vector2 pos_) { // sets character position
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

void Character::setDirection(Direction direction_) {
    this->direction = direction_;
}

//other

void Character::moveCharacter() { // moves the character based on input
    
    Direction dir = this->getDirection();

    if (dir != NONE) 
    {
        if (dir == UP) 
        {
            this->setY((this->getPos()).y - (48/MOVEFRAMES));
        } else if (dir == DOWN) 
        {
            this->setY((this->getPos()).y + (48/MOVEFRAMES));
        } else if (dir == RIGHT) 
        {
            this->setX((this->getPos()).x + (48/MOVEFRAMES));
        } else if (dir == LEFT) 
        {
            this->setX((this->getPos()).x - (48/MOVEFRAMES));
        }
    }
}

void Character::drawCharacter() { // draws the character sprite
    DrawTexturePro(this->getSprite(0), {0,0,48,48}, this->getHitbox(), {0,0}, 0, WHITE);
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