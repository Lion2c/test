/**
 * snake.h - 贪吃蛇游戏头文件
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

// 游戏配置
#define GAME_WIDTH 40
#define GAME_HEIGHT 20
#define INIT_SNAKE_LENGTH 3
#define MAX_SNAKE_LENGTH 100

// 方向枚举
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_NONE
} Direction;

// 坐标结构体
typedef struct {
    int x;
    int y;
} Position;

// 蛇身节点
typedef struct SnakeNode {
    Position pos;
    struct SnakeNode* next;
} SnakeNode;

// 游戏状态
typedef struct {
    SnakeNode* head;      // 蛇头
    SnakeNode* tail;      // 蛇尾
    Position food;        // 食物位置
    Direction direction;  // 当前移动方向
    Direction next_direction; // 下一帧方向
    int score;            // 得分
    int length;           // 蛇身长度
    bool game_over;       // 游戏结束标志
    bool game_running;    // 游戏运行标志
} GameState;

// 函数声明
void init_game(GameState* game);
void cleanup_game(GameState* game);
void generate_food(GameState* game);
bool move_snake(GameState* game);
bool check_collision(GameState* game);
void handle_input(GameState* game);
void draw_game(GameState* game);
void game_loop(GameState* game);

#endif // SNAKE_H