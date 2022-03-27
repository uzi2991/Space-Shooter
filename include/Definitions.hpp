#define SCREEN_WIDTH (256 * 2)
#define SCREEN_HEIGHT (272 * 2)

#define FONT_FILEPATH "res/Fonts/ThaleahFat.ttf"

#define BACKGROUND_FILEPATH "res/Graphics/backgrounds/desert-background.png"
#define PLAYER_FILEPATH "res/Graphics/spritesheets/ship.png"
#define LASER_FILEPATH "res/Graphics/spritesheets/laser.png"
#define BOLTS_FILEPATH "res/Graphics/spritesheets/bolts.png"
#define BIG_ENEMY_FILEPATH "res/Graphics/spritesheets/enemy-big.png"
#define MEDIUM_ENEMY_FILEPATH "res/Graphics/spritesheets/enemy-medium.png"
#define SMALL_ENEMY_FILEPATH "res/Graphics/spritesheets/enemy-small.png"
#define HEART_FILEPATH "res/Graphics/spritesheets/heart.png"

#define BACKGROUND_MOVE_SPEED 50.f

#define PLAYER_NUM_FRAMES 2
#define PLAYER_FRAMES_TIME (1.f/12.f)
#define PLAYER_SCALE 3.f
#define PLAYER_MOVE_SPEED 300.f
#define PLAYER_HEALTH 3

#define ENEMY_NUM_FRAMES 2
#define ENEMY_FRAMES_TIME (1.f/12.f)
#define ENEMY_SCALE 3.f
#define BIG_ENEMY_MOVE_SPEED 200.f
#define BIG_ENEMY_SHOOTING_COOLDOWN 0.6f
#define MEDIUM_ENEMY_MOVE_SPEED 150.f
#define MEDIUM_ENEMY_SHOOTING_COOLDOWN 1.f
#define SMALL_ENEMY_MOVE_SPEED 100.f
#define ENEMY_SPAWN_COOLDOWN 0.5f

#define BULLET_MOVE_SPEED 600.f
#define BULLET_SHOOTING_COOLDOWN 0.3f
#define BULLET_SCALE 4.f
#define BULLET_NUM_FRAMES 2
#define BULLET_FRAMES_TIMES (1.f/12.f)

#define TEXT_OUTLINE_THICKNESS 3.f

#define GAME_OVER_DELAY_TIME 3.f