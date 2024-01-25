#ifndef character_hpp
#define character_hpp

#include "globals.hpp"

class Character {
private:
    // in game stuff
    std::string name;
    int hp;
    int spd;
    int atk;
    int def;

    // code stuff
    Texture2D sprite[6];
    Rectangle hitbox;
    Direction direction;
    
public:
    // constructors
    Character(); // Default constructor

    // getters
    std::string get_name();
    int get_hp();
    int get_spd();
    int get_atk();
    int get_def();

    Texture2D getSprite(int index); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    
    Vector2 getPos(); // returns the character position
    Vector2 getCenter(); // returns the character's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox
    Direction getDirection();

    // setters
    void set_name(std::string name_);
    void set_hp(int hp_);
    void set_spd(int spd_);
    void set_atk(int atk_);
    void set_def(int def_);

    void setSprite(Texture2D sprite_, int index); // sets sprite
    void setHitbox(Rectangle hitbox_); // sets hitbox

    void setPos(Vector2 pos_); // sets character position
    void setX(float x_); // sets x position (top left corner of hitbox)
    void setY(float y_); // sets y position (top left corner of hitbox)
    void setWidth(float width_); // sets width of hitbox
    void setHeight(float height_); // sets height of hitbox
    void setDirection(Direction direction_);

    //other
    void moveCharacter(); // moves the character based on input
    void drawCharacter(); // draws the character sprite
    void loadSprite();
};

#endif // character_hpp