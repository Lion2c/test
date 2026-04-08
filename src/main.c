/**
 * main.c - 贪吃蛇游戏主程序入口
 * 
 * 一个简单的macOS终端贪吃蛇游戏
 * 使用ncurses库进行终端图形界面绘制
 */

#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 显示游戏说明
void show_instructions() {
    printf("\n");
    printf("========================================\n");
    printf("          贪吃蛇游戏 (Snake Game)        \n");
    printf("========================================\n");
    printf("\n");
    printf("游戏说明：\n");
    printf("1. 使用 WASD 或方向键控制蛇的移动\n");
    printf("2. 吃到食物($)可以增加长度和得分\n");
    printf("3. 撞到墙壁或自己的身体游戏结束\n");
    printf("4. 游戏结束后按 R 重新开始\n");
    printf("5. 按 Q 或 ESC 退出游戏\n");
    printf("\n");
    printf("游戏配置：\n");
    printf("- 游戏区域: %d x %d\n", GAME_WIDTH, GAME_HEIGHT);
    printf("- 初始长度: %d\n", INIT_SNAKE_LENGTH);
    printf("- 简单难度\n");
    printf("\n");
    printf("按任意键开始游戏...\n");
    printf("========================================\n");
    
    getchar();
}

// 显示退出信息
void show_exit_message(int score) {
    printf("\n");
    printf("========================================\n");
    printf("          游戏结束！\n");
    printf("          最终得分: %d\n", score);
    printf("========================================\n");
    printf("\n");
    printf("感谢游玩贪吃蛇游戏！\n");
    printf("\n");
}

int main(int argc, char* argv[]) {
    // 可以解析命令行参数（如果需要）
    (void)argc;  // 标记为未使用，避免警告
    (void)argv;  // 标记为未使用，避免警告
    
    // 显示游戏说明
    show_instructions();
    
    // 初始化游戏状态
    GameState game;
    init_game(&game);
    
    if (game.head == NULL) {
        fprintf(stderr, "错误：游戏初始化失败！\n");
        return 1;
    }
    
    printf("游戏初始化成功！\n");
    printf("正在启动游戏界面...\n");
    
    // 启动游戏主循环
    game_loop(&game);
    
    // 清理游戏资源
    cleanup_game(&game);
    
    // 显示退出信息
    show_exit_message(game.score);
    
    return 0;
}

// 简单的命令行参数处理（可选功能）
void parse_arguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("Usage: snake_game [options]\n");
            printf("Options:\n");
            printf("  -h, --help     Show this help message\n");
            printf("  -v, --version  Show version information\n");
            exit(0);
        }
        else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            printf("Snake Game v1.0.0\n");
            printf("A simple terminal-based snake game for macOS\n");
            exit(0);
        }
    }
}