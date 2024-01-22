#ifndef character_hpp
#define character_hpp

#include "globals.hpp"

class Character {
private:
    Texture2D sprite[6]; // sprite
    Rectangle hitbox; // hitbox
    float speed; // speed
    Vector2 direction; // direction
    Circle attackHitbox; // attackHitbox
    Rectangle attackSpriteBox;
    float attackRotation;
    float attackCooldown;
    float invulnTime;
    Enemy* enemyReference; // reference to the enemy the player is interacting with
    Vector2 projectileCollisionLocation; // location of the spot where the player collided with the projectile
    int combatTimer; // amount of frames the player has to attack in a combat sequence
    Vector2 directionAttacking; // direction the player is attacking in a combat sequence
    
public:
    // constructors
    Player(); // Default constructor
    Player(Rectangle); // Constructor with hitbox parameter

    // getters
    Texture2D getSprite(int); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    float getSpeed(); // returns speed
    Vector2 getDirection(); // returns direction unit vector
    Circle getAttackHitbox(); // returns attackHitbox
    Rectangle getAttackSpriteBox();
    float getAttackRotation();
    float getAttackCooldown(); // returs the number of attack cooldown frames
    float getInvulnTime(); // returns the number of invulnerability frames
    Enemy* getEnemyReference(); // returns the address of the enemy the player is interacting with
    Vector2 getProjectileCollisionLocation(); // returns location where the player collided with the projectile
    int getCombatTimer(); // gets the number of frames remaining for the player to attack in a combat sequence
    Vector2 getDirectionAttacking(); // gets users attack direction in a combat sequence
    
    Vector2 getPos(); // returns the player position
    Vector2 getCenter(); // returns the player's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D, int); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setSpeed(float); // sets speed
    void setDirection(Vector2); // sets direction
    void setAttackHitbox(Circle); // sets attackHitbox
    void setAttackSpriteBox(Rectangle);
    void setAttackCooldown(float); // sets the number of attack cooldown frames
    void setAttackRotation(float);
    void setInvulnTime(float); // sets the number of invulnerability frames
    void setEnemyReference(Enemy*); // sets the address of the enemy the player is interacting with
    void setProjectileCollisionLocation(Vector2); // sets the location where the player collided with the projectile
    void setCombatTimer(int); // sets the number of frames remaining for the player to attack in a combat sequence
    void setDirectionAttacking(Vector2); // sets the direction the player attacks in a combat sequence

    void setPos(Vector2); // sets player position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    //other
    void movePlayer(); // moves the player based on input
    void enemyKnockback(); // knocks the player away from an enemy (called when collision with an enemy is detected)
    void projectileKnockback(); // knocks the player away from a projectile (called when collision with a projectile is detected)
    void pollDirectionAttacking(); // polls user input to determine the direction of attack in a combat sequence
    void drawPlayer(); // draws the player sprite
    void loadSprite();
};

#endif // character_hpp