/**
 * game_logic.c - 游戏逻辑与输入处理
 */

#include "snake.h"
#include <ncurses.h>
#include <unistd.h>

// 处理用户输入
void handle_input(GameState* game) {
    int ch = getch();
    
    if (ch != ERR) {
        switch (ch) {
            case 'w':
            case 'W':
            case KEY_UP:
                if (game->direction != DIR_DOWN) {
                    game->next_direction = DIR_UP;
                }
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                if (game->direction != DIR_UP) {
                    game->next_direction = DIR_DOWN;
                }
                break;
            case 'a':
            case 'A':
            case KEY_LEFT:
                if (game->direction != DIR_RIGHT) {
                    game->next_direction = DIR_LEFT;
                }
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                if (game->direction != DIR_LEFT) {
                    game->next_direction = DIR_RIGHT;
                }
                break;
            case 'r':
            case 'R':
                if (game->game_over) {
                    // 重新开始游戏
                    cleanup_game(game);
                    init_game(game);
                    game->game_over = false;
                }
                break;
            case 'q':
            case 'Q':
            case 27: // ESC键
                game->game_running = false;
                break;
            case ' ': // 空格键 - 暂停/继续
                // 简单难度不需要暂停功能
                break;
        }
    }
}

// 游戏主循环
void game_loop(GameState* game) {
    // 初始化ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    // 游戏主循环
    while (game->game_running) {
        // 处理输入
        handle_input(game);
        
        // 如果游戏没有结束，移动蛇
        if (!game->game_over) {
            if (!move_snake(game)) {
                // 移动失败（可能是碰撞）
                game->game_over = true;
            }
        }
        
        // 绘制游戏界面
        draw_game(game);
        
        // 控制游戏速度
        usleep(150000); // 150ms，简单难度
        
        // 刷新屏幕
        refresh();
    }
    
    // 清理ncurses
    endwin();
}

// 简单的碰撞检测辅助函数
bool is_position_occupied(GameState* game, Position pos) {
    SnakeNode* current = game->head;
    while (current != NULL) {
        if (current->pos.x == pos.x && current->pos.y == pos.y) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// 获取蛇身长度
int get_snake_length(GameState* game) {
    return game->length;
}

// 获取当前得分
int get_current_score(GameState* game) {
    return game->score;
}

// 检查游戏是否结束
bool is_game_over(GameState* game) {
    return game->game_over;
}

// 检查游戏是否运行中
bool is_game_running(GameState* game) {
    return game->game_running;
}