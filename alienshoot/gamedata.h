#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#define FRAME_RATE 10
#define RESET_TIME 4000
#define BACK_W 1250
#define BACK_H 900
#define MUSIC_PLAY 0 // play backgound  music? <1 or 0 >

#define LIVES_INIT 5
#define SCORE_FONT 40 
#define SCORE_LOST 100

// gunner/bullet data
#define GUNNER_SPEED 40
#define BULLET_SPEED -20
#define FIRE_RATE 5

// alien data
#define ALIEN_INIT 1
#define ALIEN_TERMINAL 10
#define MAX_ALIEN_POS 10
#define MIN_ALIEN_POS 5
#define DX_TRAVEL 1    // travel sideways? <1 or 0 >
#define ALIEN_SPAWN_RATE 50
#define SPAWN_CHANGE_RATE 10 //update speeds after this num spawned
#define SPAWN_CHANGE_SIZE 5
#define SPEED_CHANGE_SIZE 1
#define SPAWN_INIT_CHANGE 1


//  image names
#define BACK "imgs/back/back.jpg"
#define ALIEN1 "imgs/aliens/alien"
#define ALIEN_NUM 18
#define FONT "imgs/font/font.ttf"
#define GUNNER "imgs/gunner/gunner"
#define GUNNER_NUM 18
#define BULLET "imgs/bullet/bullet"
#define BULLET_NUM 14
#define BACK_MUSIC "sounds/back/back.mp3"

// sound names
#define SHOT_SOUND "sounds/shot/shot"
#define SHOT_NUM 1
#define SPAWN_SOUND "sounds/spawn/spawn" 
#define SPAWN_NUM 1
#define HIT_SOUND "sounds/fart/fart"
#define HIT_NUM 2
#define LOST_SOUND "sounds/lost/lost"
#define LOST_NUM 1
#define POP_SOUND "sounds/pop/pop"
#define POP_NUM 1


#endif
