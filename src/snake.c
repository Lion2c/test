/**
 * snake.c - 贪吃蛇数据结构与核心函数
 */

#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

// 初始化游戏状态
void init_game(GameState* game) {
    // 初始化随机数种子
    srand(time(NULL));
    
    // 清空游戏状态
    game->head = NULL;
    game->tail = NULL;
    game->score = 0;
    game->length = 0;
    game->direction = DIR_RIGHT;
    game->next_direction = DIR_RIGHT;
    game->game_over = false;
    game->game_running = true;
    
    // 初始化蛇身
    int start_x = GAME_WIDTH / 2;
    int start_y = GAME_HEIGHT / 2;
    
    for (int i = 0; i < INIT_SNAKE_LENGTH; i++) {
        SnakeNode* new_node = (SnakeNode*)malloc(sizeof(SnakeNode));
        if (!new_node) {
            // 内存分配失败，清理已分配的内存
            cleanup_game(game);
            return;
        }
        
        new_node->pos.x = start_x - i;
        new_node->pos.y = start_y;
        new_node->next = NULL;
        
        if (game->head == NULL) {
            game->head = new_node;
            game->tail = new_node;
        } else {
            game->tail->next = new_node;
            game->tail = new_node;
        }
        
        game->length++;
    }
    
    // 生成第一个食物
    generate_food(game);
}

// 清理游戏资源
void cleanup_game(GameState* game) {
    SnakeNode* current = game->head;
    while (current != NULL) {
        SnakeNode* next = current->next;
        free(current);
        current = next;
    }
    
    game->head = NULL;
    game->tail = NULL;
    game->length = 0;
}

// 生成食物位置
void generate_food(GameState* game) {
    bool valid_position = false;
    
    while (!valid_position) {
        // 生成随机位置
        game->food.x = rand() % GAME_WIDTH;
        game->food.y = rand() % GAME_HEIGHT;
        
        // 检查是否与蛇身重叠
        valid_position = true;
        SnakeNode* current = game->head;
        while (current != NULL) {
            if (current->pos.x == game->food.x && current->pos.y == game->food.y) {
                valid_position = false;
                break;
            }
            current = current->next;
        }
    }
}

// 检查碰撞
bool check_collision(GameState* game) {
    // 检查墙壁碰撞
    if (game->head->pos.x < 0 || game->head->pos.x >= GAME_WIDTH ||
        game->head->pos.y < 0 || game->head->pos.y >= GAME_HEIGHT) {
        return true;
    }
    
    // 检查自身碰撞（从第二个节点开始检查）
    SnakeNode* current = game->head->next;
    while (current != NULL) {
        if (current->pos.x == game->head->pos.x && current->pos.y == game->head->pos.y) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

// 移动蛇
bool move_snake(GameState* game) {
    // 更新方向
    game->direction = game->next_direction;
    
    // 计算新头部位置
    Position new_head_pos = game->head->pos;
    
    switch (game->direction) {
        case DIR_UP:
            new_head_pos.y--;
            break;
        case DIR_DOWN:
            new_head_pos.y++;
            break;
        case DIR_LEFT:
            new_head_pos.x--;
            break;
        case DIR_RIGHT:
            new_head_pos.x++;
            break;
        case DIR_NONE:
            return true; // 不移动
    }
    
    // 创建新的头部节点
    SnakeNode* new_head = (SnakeNode*)malloc(sizeof(SnakeNode));
    if (!new_head) {
        return false; // 内存分配失败
    }
    
    new_head->pos = new_head_pos;
    new_head->next = game->head;
    game->head = new_head;
    
    // 检查是否吃到食物
    bool ate_food = false;
    if (game->head->pos.x == game->food.x && game->head->pos.y == game->food.y) {
        ate_food = true;
        game->score += 10;
        game->length++;
        
        // 生成新食物
        generate_food(game);
    }
    
    // 如果没有吃到食物，移除尾部
    if (!ate_food) {
        // 找到倒数第二个节点
        SnakeNode* current = game->head;
        while (current->next != game->tail) {
            current = current->next;
        }
        
        // 移除尾部
        free(game->tail);
        current->next = NULL;
        game->tail = current;
    }
    
    // 检查碰撞
    if (check_collision(game)) {
        game->game_over = true;
        return false;
    }
    
    return true;
}