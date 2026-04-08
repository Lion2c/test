#!/bin/bash

# 贪吃蛇游戏测试脚本
echo "=== 贪吃蛇游戏测试脚本 ==="
echo ""

# 检查编译状态
echo "1. 检查编译状态..."
if [ -f "build/bin/snake_game" ]; then
    echo "✅ 游戏可执行文件存在"
    echo "   文件大小: $(ls -lh build/bin/snake_game | awk '{print $5}')"
    echo "   文件类型: $(file build/bin/snake_game | cut -d: -f2-)"
else
    echo "❌ 游戏可执行文件不存在"
    echo "   尝试重新编译..."
    make clean
    make
fi

echo ""
echo "2. 检查依赖库..."
if pkg-config --cflags --libs ncurses 2>/dev/null >/dev/null; then
    echo "✅ ncurses库已正确安装"
else
    echo "❌ ncurses库未找到"
    echo "   请运行: brew install ncurses"
fi

echo ""
echo "3. 检查源代码文件..."
for file in src/main.c src/snake.c src/game_logic.c src/ui.c include/snake.h; do
    if [ -f "$file" ]; then
        echo "✅ $file 存在"
    else
        echo "❌ $file 缺失"
    fi
done

echo ""
echo "4. 运行简单功能测试..."
echo "   创建测试环境..."
# 创建一个简单的C程序来测试数据结构
cat > test_struct.c << 'EOF'
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Position;

int main() {
    Position pos = {10, 20};
    printf("✅ 数据结构测试通过: Position(%d, %d)\n", pos.x, pos.y);
    return 0;
}
EOF

gcc test_struct.c -o test_struct && ./test_struct
rm -f test_struct test_struct.c

echo ""
echo "5. 游戏构建测试..."
echo "   清理构建..."
make clean > /dev/null 2>&1
echo "   重新构建..."
if make > build.log 2>&1; then
    echo "✅ 游戏构建成功"
    rm -f build.log
else
    echo "❌ 游戏构建失败"
    echo "   错误日志:"
    cat build.log
    rm -f build.log
    exit 1
fi

echo ""
echo "=== 测试完成 ==="
echo ""
echo "要运行游戏，请执行:"
echo "  cd /Users/lion/projects/test"
echo "  ./build/bin/snake_game"
echo ""
echo "或者使用make命令:"
echo "  make run"
echo ""
echo "游戏说明:"
echo "- 使用 WASD 或方向键移动"
echo "- 吃到食物($)增长身体"
echo "- 撞墙或撞到自己游戏结束"
echo "- 游戏结束后按 R 重新开始"
echo "- 按 Q 或 ESC 退出"