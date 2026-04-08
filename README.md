# Test C Project

A C language project with two components:
1. Original example project
2. Snake Game - A terminal-based snake game for macOS

## Project Structure

```
test/
├── src/           # Source files (.c)
│   ├── main.c              # Snake game main entry
│   ├── snake.c             # Snake data structures
│   ├── game_logic.c        # Game logic and input
│   ├── ui.c                # User interface drawing
│   ├── main_backup.c       # Original main.c backup
│   ├── example.c           # Example module
│   └── tests/test_basic.c  # Unit tests
├── include/       # Header files (.h)
│   ├── snake.h            # Snake game header
│   └── example.h          # Example header
├── lib/           # Library files
├── tests/         # Test files
├── docs/          # Documentation
├── examples/      # Example code
└── build/         # Build output (generated)
```

## 🐍 Snake Game

A simple terminal-based snake game written in C using ncurses library.

### Features
- Terminal-based graphics using ncurses
- Snake movement with WASD or arrow keys
- Food collection and growth
- Collision detection (walls and self)
- Score tracking
- Game over screen with restart option

### Build and Run

```bash
# Clone the repository
git clone https://github.com/Lion2c/test.git
cd test

# Install dependencies (macOS)
brew install ncurses

# Build the snake game
make snake

# Run the snake game
make run
# or
./build/bin/snake_game

# Run the original example project
make run_example
```

### Game Controls
- **WASD** or **Arrow Keys** - Move the snake
- **R** - Restart game (when game over)
- **Q** or **ESC** - Quit game

### Game Rules
1. Control the snake to eat food ($)
2. Each food increases score by 10 and snake length by 1
3. Avoid hitting walls or the snake's own body
4. Game ends on collision
5. Press R to restart after game over

### Code Example

Here's a simple example of how to use the snake game API:

```c
#include "snake.h"
#include <stdio.h>

int main() {
    // Initialize game state
    GameState game;
    init_game(&game);
    
    printf("Snake Game Started!\n");
    printf("Initial length: %d\n", game.length);
    printf("Food position: (%d, %d)\n", game.food.x, game.food.y);
    
    // Start game loop (this will handle everything)
    game_loop(&game);
    
    // Cleanup
    cleanup_game(&game);
    
    return 0;
}
```

### Advanced Usage

You can extend the game by modifying the source code:

1. **Change game speed**: Modify the `usleep(150000)` in `game_loop()` function
2. **Add new features**: Extend the `GameState` structure
3. **Change appearance**: Modify drawing characters in `ui.c`
4. **Add difficulty levels**: Implement speed increase as score grows

## Original Example Project

The original example project is still available:

```bash
# Build the original example
make test_proj

# Run the original example
make run_example
```

## Dependencies

- GCC compiler
- Make
- ncurses library (for snake game)
  ```bash
  brew install ncurses  # macOS
  ```

## Testing

```bash
# Run the test script
./run_test.sh

# Run unit tests (basic)
cd tests
gcc test_basic.c ../src/example.c -I../include -o test_basic && ./test_basic
```

## License

MIT