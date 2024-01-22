// Class implementation for Player

#include "character.hpp"
#include "globals.hpp"


// constructors
Player::Player() // Default constructor
{
    this->loadSprite();
    this->hitbox = Rectangle {0, 0, 50, 100}; // Default hitbox is a 50x100 square at (0, 0)
    this->speed = 10;
    this->direction = Vector2 {0, -1};
    this->attackHitbox = Circle {THE_VOID, 0};
    this->attackSpriteBox = Rectangle {0, 0, 0, 0};
    this->attackCooldown = 0;
    this->invulnTime = 0;
    this->enemyReference = NULL;
    this->projectileCollisionLocation = THE_VOID;
    this->combatTimer = 0;
    this->directionAttacking = Vector2 {0, 0};
}

Player::Player(Rectangle hitbox_) // Constructor with hitbox parameter
{
    this->loadSprite();
    this->hitbox = hitbox_;
    this->speed = 10;
    this->direction = {0, 1};
    this->attackHitbox = Circle{THE_VOID, 0};
    this->attackSpriteBox = Rectangle {0, 0, 0, 0};
    this->attackCooldown = 0;
    this->invulnTime = 0;
    this->enemyReference = NULL;
    this->projectileCollisionLocation = THE_VOID;
    this->combatTimer = 0;
    this->directionAttacking = Vector2 {0, 0};
}

// getters
Texture2D Player::getSprite(int index) // returns sprite
{
    return this->sprite[index];
}

Rectangle Player::getHitbox() // returns hitbox
{
    return this->hitbox;
}

float Player::getSpeed() // returns speed
{
    return this->speed;
}

Vector2 Player::getDirection() // returns direction unit vector
{
    return this->direction;
}

Circle Player::getAttackHitbox() // returns attackHitbox
{
    return this->attackHitbox;
}

Rectangle Player::getAttackSpriteBox()
{
    return this->attackSpriteBox;
}

float Player::getAttackRotation()
{
    return this->attackRotation;
}

float Player::getAttackCooldown() // returs the number of attack cooldown frames
{
    return this->attackCooldown;
}

float Player::getInvulnTime() // returns the number of invulnerability frames
{
    return this->invulnTime;
}

Enemy* Player::getEnemyReference() // returns the address of the enemy the player is interacting with
{
    return this->enemyReference;
}

Vector2 Player::getProjectileCollisionLocation() // returns location where the player collided with the projectile
{
    return this->projectileCollisionLocation;
}

int Player::getCombatTimer() // gets the number of frames remaining for the player to attack in a combat sequence
{
    return this->combatTimer;
}

Vector2 Player::getDirectionAttacking() // gets users attack direction in a combat sequence
{
    return this->directionAttacking;
}


Vector2 Player::getPos() // returns the player position
{
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Player::getCenter() // returns the player's center position
{
    Vector2 pos = {this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight()/2};
    return pos;
}

float Player::getWidth() // returns width of hitbox
{
    return this->hitbox.width;
}

float Player::getHeight() // returns height of hitbox
{
    return this->hitbox.height;
}

// setters
void Player::setSprite(Texture2D sprite_, int index)
{
    this->sprite[index] = sprite_;
}

void Player::setHitbox(Rectangle hitbox_) // sets hitbox
{
    this->hitbox = hitbox_;
}

void Player::setSpeed(float speed_) // sets speed
{
    this->speed = speed_;
}

void Player::setDirection(Vector2 direction_) // sets direction
{
    this->direction = Vector2Normalize(direction_);
}

void Player::setAttackHitbox(Circle attackHitbox_) // sets attackHitbox
{
    this->attackHitbox = attackHitbox_;
}

void Player::setAttackSpriteBox(Rectangle attackSpriteBox_)
{
    this->attackSpriteBox = attackSpriteBox_;
}

void Player::setAttackRotation(float attackRotation_)
{
    this->attackRotation = attackRotation_;
}

void Player::setAttackCooldown(float attackCooldown_) // sets the number of attack cooldown frames
{
    this->attackCooldown = attackCooldown_;
}

void Player::setInvulnTime(float invulnTime_) // sets the number of invulnerability frames
{
    this->invulnTime = invulnTime_;
}

void Player::setEnemyReference(Enemy* enemyReference_) // sets the address of the enemy the player is interacting with
{
    this->enemyReference = enemyReference_;
}

void Player::setProjectileCollisionLocation(Vector2 projectileCollisionLocation_) // sets the location where the player collided with the projectile
{
    this->projectileCollisionLocation = projectileCollisionLocation_;
}

void Player::setCombatTimer(int combatTimer_) // sets the number of frames remaining for the player to attack in a combat sequence
{
    this->combatTimer = combatTimer_;
}

void Player::setDirectionAttacking(Vector2 directionAttacking_) // polls for user attack direction
{
    this->directionAttacking = Vector2Normalize(directionAttacking_);
}


void Player::setPos(Vector2 pos_) // sets player position
{
    this->hitbox.x = pos_.x;
    this->hitbox.y = pos_.y;
}

void Player::setX(float x_) // sets x position (top left corner of hitbox)
{
    this->hitbox.x = x_;
}

void Player::setY(float y_) // sets y position (top left corner of hitbox)
{
    this->hitbox.y = y_;
}

void Player::setWidth(float width_) // sets width of hitbox
{
    this->hitbox.width = width_;
}

void Player::setHeight(float height_) // sets height of hitbox
{
    this->hitbox.height = height_;
}

//other

void Player::movePlayer() // moves the player based on input
{
    if (this->getAttackCooldown() > 0)
    {
        this->setAttackCooldown(this->getAttackCooldown() - 1);

    } else if (IsKeyPressed(KEY_J) && !this->getInvulnTime())
    {
        this->setAttackCooldown(ATTACK_COOLDOWN);

    }

    if (this->getInvulnTime() > 0) // invulnerable
    {
        if (this->getInvulnTime() > INVULN_FRAMES/2) // first half of invuln frames
        {
            if (this->enemyReference != NULL)
            {
                this->enemyKnockback();
            } else if (!Vector2Equals(this->getProjectileCollisionLocation(), THE_VOID))
            {
                this->projectileKnockback();
            }
        }

        this->setInvulnTime(this->getInvulnTime() - 1); // decrement invuln frames
    } else // not invulnerable
    {
        // reset references
        this->setEnemyReference(NULL);
        this->setProjectileCollisionLocation(THE_VOID);
    }

    bool shouldMove = true;
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        this->setDirection(Vector2 {1, -1});
        this->setAttackRotation(45);

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
    {
        this->setDirection(Vector2 {1, 1});
        this->setAttackRotation(135);

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
    {
        this->setDirection(Vector2 {-1, 1});
        this->setAttackRotation(225);

    } else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
    {
        this->setDirection(Vector2 {-1, -1});
        this->setAttackRotation(315);

    } else if (IsKeyDown(KEY_W))
    {
        this->setDirection(Vector2 {0, -1});
        this->setAttackRotation(0);

    } else if (IsKeyDown(KEY_D))
    {
        this->setDirection(Vector2 {1, 0});
        this->setAttackRotation(90);

    } else if (IsKeyDown(KEY_S))
    {
        this->setDirection(Vector2 {0, 1});
        this->setAttackRotation(180);

    } else if (IsKeyDown(KEY_A))
    {
        this->setDirection(Vector2 {-1, 0});
        this->setAttackRotation(270);

    } else
    {
        shouldMove = false;
    }

    if (shouldMove) // ensures player doesn't keep moving after a button is released
    {
        this->setPos(Vector2Add(this->getPos(), Vector2Scale(this->getDirection(), speed)));
    }

    if (this->getInvulnTime() <= 0) // if player is not invulnerable
    {
        Rectangle attackBox = {this->getCenter().x + (this->getDirection().x * ATTACK_OFFSET) - ATTACK_RADIUS, this->getCenter().y + (this->getDirection().y * ATTACK_OFFSET)  - ATTACK_RADIUS, 2*ATTACK_RADIUS, 2*ATTACK_RADIUS};
        this->setAttackSpriteBox(attackBox);
        
        if (this->getAttackCooldown() > (ATTACK_COOLDOWN - 4)) // First 4 frames of attack
        {
            Circle attack = {Vector2 {this->getCenter().x + (this->getDirection().x * ATTACK_OFFSET), this->getCenter().y + (this->getDirection().y * ATTACK_OFFSET)}, ATTACK_RADIUS/4}; // location of hitbox, radius of hitbox
            this->setAttackHitbox(attack);
            
        } else if (this->getAttackCooldown() > (ATTACK_COOLDOWN - 8)) // Next 4 frames of attack
        {
            Circle attack = {Vector2 {this->getCenter().x + (this->getDirection().x * ATTACK_OFFSET), this->getCenter().y + (this->getDirection().y * ATTACK_OFFSET)}, ATTACK_RADIUS}; // location of hitbox, radius of hitbox
            this->setAttackHitbox(attack);

        } else if (this->getAttackCooldown() > (ATTACK_COOLDOWN - 12)) // Next 4 frames of attack
        {
            Circle attack = {Vector2 {this->getCenter().x + (this->getDirection().x * ATTACK_OFFSET), this->getCenter().y + (this->getDirection().y * ATTACK_OFFSET)}, ATTACK_RADIUS}; // location of hitbox, radius of hitbox
            this->setAttackHitbox(attack);
        } else if (this->getAttackCooldown() > (ATTACK_COOLDOWN - 16)) // Next 4 frames of attack
        {
            Circle attack = {Vector2 {this->getCenter().x + (this->getDirection().x * ATTACK_OFFSET), this->getCenter().y + (this->getDirection().y * ATTACK_OFFSET)}, ATTACK_RADIUS}; // location of hitbox, radius of hitbox
            this->setAttackHitbox(attack);
        } else if (this->getAttackCooldown() > (ATTACK_COOLDOWN - 20)) // Next 4 frames of attack
        {
            Circle attack = {Vector2 {this->getCenter().x + (this->getDirection().x * ATTACK_OFFSET), this->getCenter().y + (this->getDirection().y * ATTACK_OFFSET)}, ATTACK_RADIUS/4}; // location of hitbox, radius of hitbox
            this->setAttackHitbox(attack);
        } else
        {
            this->setAttackHitbox(Circle {THE_VOID, 0});
        }
    }
}

void Player::enemyKnockback() // knocks the player away from an enemy (called when collision with an enemy is detected)
{
    Vector2 dist = Vector2Subtract(this->getCenter(), (*this->getEnemyReference()).getCenter());
    Vector2 normalDist = Vector2Normalize(dist);

    this->setPos(Vector2Add(this->getPos(), Vector2Scale(normalDist, (this->getInvulnTime()*this->getInvulnTime())/50)));

}

void Player::projectileKnockback() // knocks the player away from a projectile (called when collision with a projectile is detected)
{
    Vector2 dist = Vector2Subtract(this->getCenter(), this->getProjectileCollisionLocation());
    Vector2 normalDist = Vector2Normalize(dist);

    this->setPos(Vector2Add(this->getPos(), Vector2Scale(normalDist, (this->getInvulnTime()*this->getInvulnTime())/40)));
}

void Player::pollDirectionAttacking() // polls user input to determine the direction of attack in a combat sequence
{
    if (IsKeyDown(KEY_A) && IsKeyPressed(KEY_J)) // attacking to the left
    {
        this->setDirectionAttacking(Vector2 {1, 0}); // slash from the right
        this->setCombatTimer(0);

    } else if (IsKeyDown(KEY_S) && IsKeyPressed(KEY_J)) // attacking downwards
    {
        this->setDirectionAttacking(Vector2 {0, -1}); // slash from the top
        this->setCombatTimer(0);

    } else if (IsKeyDown(KEY_D) && IsKeyPressed(KEY_J)) // attacking to the right
    {
        this->setDirectionAttacking(Vector2 {-1, 0}); // slash from the left
        this->setCombatTimer(0);

    }
}

void Player::drawPlayer() // draws the player sprite
{
    

    Texture2D currentSprite;

    if (this->getDirection().x >= 0)
    {
        if (!Vector2Equals(this->getAttackHitbox().center, THE_VOID))
        {
            currentSprite = this->getSprite(RIGHT);
        } else
        {
            currentSprite = this->getSprite(RIGHT_SWORD);
        }
        
    } else
    {
        if (!Vector2Equals(this->getAttackHitbox().center, THE_VOID))
        {
            currentSprite = this->getSprite(LEFT);
        } else
        {
            currentSprite = this->getSprite(LEFT_SWORD);
        }
    }

    Rectangle spriteRect = {0, 0, 46, 64};
    Rectangle swingRect = {0, 0, 32, 32};

    if (((!this->getEnemyReference() == NULL) || (!Vector2Equals(this->getProjectileCollisionLocation(), THE_VOID))))
    {
        if (currentState == PLAYING)
        {
            DrawTexturePro(currentSprite, spriteRect, this->hitbox, Vector2 {0, 0}, 0, RED);
        } else
        {
            DrawTexturePro(currentSprite, spriteRect, this->hitbox, Vector2 {0, 0}, 0, WHITE);
        }
    } else
    {
        DrawTexturePro(currentSprite, spriteRect, this->hitbox, Vector2 {0, 0}, 0, WHITE);

        if (this->getAttackCooldown() > (ATTACK_COOLDOWN - ATTACK_FRAMES)) // 10
        {
            
            if (this->getAttackCooldown() < ATTACK_COOLDOWN - 6) // 14
            {
                swingRect.x = 32;
            } else if (this->getAttackCooldown() < ATTACK_COOLDOWN - 8) // 12
            {
                swingRect.x = 64;
            }

            // DrawCircle(this->getAttackHitbox().center.x, this->getAttackHitbox().center.y, this->getAttackHitbox().radius, Color {192, 192, 192, 255});
            // DrawRectangleRec(this->getAttackSpriteBox(), WHITE);
            Rectangle dest = {this->getAttackSpriteBox().x, this->getAttackSpriteBox().y, this->getAttackSpriteBox().width, this->getAttackSpriteBox().height};
            spriteType swing = SWING;
            if (this->getAttackRotation() == 45)
            {
                dest.x = dest.x + 55; // dest.width/2 + 5
                dest.y = dest.y - 32; // dest.height/3
                swing = SWING_RIGHT;
            } else if (this->getAttackRotation() == 90)
            {
                dest.x = dest.x + dest.width;
                swing = SWING_RIGHT;
                
            } else if (this->getAttackRotation() == 135)
            {
                dest.x = dest.x + 133; // 1.3 * dest.width + 3
                dest.y = dest.y + 60; // 0.6 * dest.height
                swing = SWING_RIGHT;
            } else if (this->getAttackRotation() == 180)
            {
                dest.x = dest.x + dest.width;
                dest.y = dest.y + dest.height;
                swing = SWING_RIGHT;
            } else if (this->getAttackRotation() == 225)
            {
                dest.x = dest.x + 43; // 0.5 * dest.width - 7
                dest.y = dest.y + 133; // 1.3 * dest.height + 3
            } else if (this->getAttackRotation() == 270)
            {
                dest.y = dest.y + dest.height;
            } else if (this->getAttackRotation() == 315)
            {
                dest.x = dest.x - 32;
                dest.y = dest.y + 43;
            }

            DrawTexturePro(this->getSprite(swing), swingRect, dest, Vector2 {0, 0}, this->getAttackRotation(), WHITE);
        }

    }
    // DrawTextureRec(this->sprite, this->hitbox, Vector2 {this->hitbox.x, this->hitbox.y}, WHITE);
    // DrawTexture(this->sprite, this->hitbox.x, this->hitbox.y, WHITE);
}

void Player::loadSprite() 
{
    this->sprite[LEFT] = LoadTexture("assets/charNoSword2.png");
    this->sprite[RIGHT] = LoadTexture("assets/charNoSword1.png");
    this->sprite[RIGHT_SWORD] = LoadTexture("assets/charRight.png");
    this->sprite[LEFT_SWORD] = LoadTexture("assets/charLeft.png");
    this->sprite[SWING] = LoadTexture("assets/swing.png");
    this->sprite[SWING_RIGHT] = LoadTexture("assets/swing_right.png");
}