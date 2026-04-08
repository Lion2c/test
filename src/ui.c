/**
 * ui.c - 游戏界面绘制
 */

#include "snake.h"
#include <ncurses.h>
#include <string.h>

// 绘制游戏边框
void draw_border() {
    // 上边框
    for (int x = 0; x < GAME_WIDTH + 2; x++) {
        mvaddch(0, x, '#');
    }
    
    // 下边框
    for (int x = 0; x < GAME_WIDTH + 2; x++) {
        mvaddch(GAME_HEIGHT + 1, x, '#');
    }
    
    // 左边框
    for (int y = 1; y <= GAME_HEIGHT; y++) {
        mvaddch(y, 0, '#');
    }
    
    // 右边框
    for (int y = 1; y <= GAME_HEIGHT; y++) {
        mvaddch(y, GAME_WIDTH + 1, '#');
    }
}

// 绘制蛇身
void draw_snake(GameState* game) {
    SnakeNode* current = game->head;
    int index = 0;
    
    while (current != NULL) {
        if (index == 0) {
            // 蛇头用@表示
            mvaddch(current->pos.y + 1, current->pos.x + 1, '@');
        } else {
            // 蛇身用*表示
            mvaddch(current->pos.y + 1, current->pos.x + 1, '*');
        }
        
        current = current->next;
        index++;
    }
}

// 绘制食物
void draw_food(GameState* game) {
    mvaddch(game->food.y + 1, game->food.x + 1, '$');
}

// 绘制分数和游戏信息
void draw_info(GameState* game) {
    char score_str[50];
    snprintf(score_str, sizeof(score_str), "Score: %d", game->score);
    mvprintw(GAME_HEIGHT + 3, 2, score_str);
    
    char length_str[50];
    snprintf(length_str, sizeof(length_str), "Length: %d", game->length);
    mvprintw(GAME_HEIGHT + 4, 2, length_str);
    
    // 绘制控制说明
    mvprintw(GAME_HEIGHT + 6, 2, "Controls: WASD or Arrow Keys - Move");
    mvprintw(GAME_HEIGHT + 7, 2, "          R - Restart (when game over)");
    mvprintw(GAME_HEIGHT + 8, 2, "          Q or ESC - Quit");
}

// 绘制游戏结束画面
void draw_game_over(GameState* game) {
    int center_x = (GAME_WIDTH - 10) / 2;
    
    mvprintw(GAME_HEIGHT / 2, center_x, "GAME OVER!");
    
    char final_score[50];
    snprintf(final_score, sizeof(final_score), "Final Score: %d", game->score);
    mvprintw(GAME_HEIGHT / 2 + 1, center_x, final_score);
    
    mvprintw(GAME_HEIGHT / 2 + 3, center_x - 5, "Press R to Restart");
    mvprintw(GAME_HEIGHT / 2 + 4, center_x - 5, "Press Q to Quit");
}

// 绘制游戏标题
void draw_title() {
    int center_x = (GAME_WIDTH - 14) / 2;
    mvprintw(GAME_HEIGHT + 2, center_x, "SNAKE GAME");
}

// 主绘制函数
void draw_game(GameState* game) {
    // 清屏
    clear();
    
    // 绘制边框
    draw_border();
    
    // 绘制游戏元素
    draw_snake(game);
    draw_food(game);
    
    // 绘制游戏信息
    draw_title();
    draw_info(game);
    
    // 如果游戏结束，绘制结束画面
    if (game->game_over) {
        draw_game_over(game);
    }
    
    // 刷新屏幕
    refresh();
}

// 初始化颜色（如果需要彩色版本）
void init_colors() {
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);  // 蛇身
        init_pair(2, COLOR_RED, COLOR_BLACK);    // 食物
        init_pair(3, COLOR_YELLOW, COLOR_BLACK); // 蛇头
        init_pair(4, COLOR_CYAN, COLOR_BLACK);   // 边框
    }
}

// 使用颜色绘制（可选功能）
void draw_with_colors(GameState* game) {
    if (!has_colors()) {
        draw_game(game);
        return;
    }
    
    // 清屏
    clear();
    
    // 绘制彩色边框
    attron(COLOR_PAIR(4));
    draw_border();
    attroff(COLOR_PAIR(4));
    
    // 绘制彩色蛇身
    SnakeNode* current = game->head;
    int index = 0;
    
    while (current != NULL) {
        if (index == 0) {
            attron(COLOR_PAIR(3)); // 蛇头黄色
            mvaddch(current->pos.y + 1, current->pos.x + 1, '@');
            attroff(COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1)); // 蛇身绿色
            mvaddch(current->pos.y + 1, current->pos.x + 1, '*');
            attroff(COLOR_PAIR(1));
        }
        
        current = current->next;
        index++;
    }
    
    // 绘制彩色食物
    attron(COLOR_PAIR(2)); // 食物红色
    draw_food(game);
    attroff(COLOR_PAIR(2));
    
    // 绘制信息
    draw_title();
    draw_info(game);
    
    // 如果游戏结束，绘制结束画面
    if (game->game_over) {
        draw_game_over(game);
    }
    
    refresh();
}