# 贪吃蛇游戏 API 文档

## 概述

本文档描述了贪吃蛇游戏的C语言API接口，供开发者参考和使用。

## 数据结构

### Position
```c
typedef struct {
    int x;  // X坐标 (0 到 GAME_WIDTH-1)
    int y;  // Y坐标 (0 到 GAME_HEIGHT-1)
} Position;
```

### Direction
```c
typedef enum {
    DIR_UP,     // 向上
    DIR_DOWN,   // 向下
    DIR_LEFT,   // 向左
    DIR_RIGHT,  // 向右
    DIR_NONE    // 无方向
} Direction;
```

### SnakeNode
```c
typedef struct SnakeNode {
    Position pos;           // 节点位置
    struct SnakeNode* next; // 下一个节点
} SnakeNode;
```

### GameState
```c
typedef struct {
    SnakeNode* head;      // 蛇头指针
    SnakeNode* tail;      // 蛇尾指针
    Position food;        // 食物位置
    Direction direction;  // 当前移动方向
    Direction next_direction; // 下一帧方向
    int score;            // 当前得分
    int length;           // 蛇身长度
    bool game_over;       // 游戏结束标志
    bool game_running;    // 游戏运行标志
} GameState;
```

## 配置常量

```c
#define GAME_WIDTH 40           // 游戏区域宽度
#define GAME_HEIGHT 20          // 游戏区域高度
#define INIT_SNAKE_LENGTH 3     // 初始蛇身长度
#define MAX_SNAKE_LENGTH 100    // 最大蛇身长度
```

## 核心API函数

### 初始化函数

#### `void init_game(GameState* game)`
初始化游戏状态。

**参数：**
- `game`: 指向GameState结构的指针

**说明：**
- 初始化随机数种子
- 设置初始蛇身位置
- 生成第一个食物
- 重置分数和游戏状态

#### `void cleanup_game(GameState* game)`
清理游戏资源，释放内存。

**参数：**
- `game`: 指向GameState结构的指针

**说明：**
- 释放所有蛇身节点内存
- 重置指针为NULL

### 游戏逻辑函数

#### `void generate_food(GameState* game)`
生成新的食物位置。

**参数：**
- `game`: 指向GameState结构的指针

**说明：**
- 随机生成不与蛇身重叠的位置
- 更新game->food

#### `bool move_snake(GameState* game)`
移动蛇身。

**参数：**
- `game`: 指向GameState结构的指针

**返回值：**
- `true`: 移动成功
- `false`: 移动失败（碰撞或内存错误）

**说明：**
- 根据当前方向移动蛇头
- 检查是否吃到食物
- 更新蛇身长度和分数
- 检查碰撞

#### `bool check_collision(GameState* game)`
检查碰撞。

**参数：**
- `game`: 指向GameState结构的指针

**返回值：**
- `true`: 发生碰撞
- `false`: 无碰撞

**说明：**
- 检查墙壁碰撞
- 检查自身碰撞

### 输入处理函数

#### `void handle_input(GameState* game)`
处理用户输入。

**参数：**
- `game`: 指向GameState结构的指针

**支持的按键：**
- `W`, `A`, `S`, `D`: 移动方向
- 方向键: 移动方向
- `R`: 重新开始游戏
- `Q`, `ESC`: 退出游戏

### 界面绘制函数

#### `void draw_game(GameState* game)`
绘制游戏界面。

**参数：**
- `game`: 指向GameState结构的指针

**绘制内容：**
- 游戏边框
- 蛇身和食物
- 分数和长度信息
- 游戏结束画面（如果游戏结束）

### 游戏主循环

#### `void game_loop(GameState* game)`
游戏主循环。

**参数：**
- `game`: 指向GameState结构的指针

**流程：**
1. 初始化ncurses
2. 进入游戏循环
3. 处理输入
4. 更新游戏状态
5. 绘制界面
6. 控制游戏速度
7. 清理ncurses

## 使用示例

```c
#include "snake.h"

int main() {
    GameState game;
    
    // 初始化游戏
    init_game(&game);
    
    // 启动游戏主循环
    game_loop(&game);
    
    // 清理资源
    cleanup_game(&game);
    
    return 0;
}
```

## 编译选项

```makefile
# 使用ncurses库
CFLAGS = -Wall -Wextra -I./include -D_DARWIN_C_SOURCE
LDFLAGS = -lncurses
```

## 平台要求

- macOS (使用ncurses库)
- 终端支持ANSI转义序列
- GCC编译器

## 版本历史

- v1.0.0 (2026-04-08): 初始版本
  - 基础贪吃蛇游戏功能
  - ncurses终端界面
  - 简单难度设置

## 许可证

MIT License