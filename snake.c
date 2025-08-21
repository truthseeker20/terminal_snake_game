#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h> // <-- ADD THIS for bool type
#include <string.h>
#include <time.h>

// Structs and globals...
struct pos { int x, y; };
struct pos snake[100];
int snake_length;

int game_over(int rows, int cols, int score);

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));

    char user_choice = 'r';
    while (user_choice == 'r') {
        flushinp();
        
        // FIX: timeout() must be inside the restart loop
        timeout(100);

        snake_length = 1;
        char fruit = '*';
        int direction = KEY_RIGHT; // Start moving right is more traditional
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Reset snake position
        snake[0].x = cols / 2;
        snake[0].y = rows / 2;

        struct pos f;
        f.x = 1 + (rand() % (cols - 2));
        f.y = 1 + (rand() % (rows - 2));

        int score = 0;
        bool is_game_over = false; // Use a flag instead of goto

        while (!is_game_over) {
            // --- GET INPUT ---
            int ch = getch();

            // --- UPDATE STATE ---
            if ((ch == KEY_UP && direction != KEY_DOWN) ||
                (ch == KEY_DOWN && direction != KEY_UP) ||
                (ch == KEY_LEFT && direction != KEY_RIGHT) ||
                (ch == KEY_RIGHT && direction != KEY_LEFT)) {
                direction = ch;
            } else if (ch == 'q') {
                is_game_over = true;
                continue; // Skip the rest of the loop
            }

            // Move body
            for (int i = snake_length - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }

            // Move head
            switch (direction) {
                case KEY_UP: snake[0].y--; break;
                case KEY_DOWN: snake[0].y++; break;
                case KEY_RIGHT: snake[0].x++; break;
                case KEY_LEFT: snake[0].x--; break;
            }

            // --- CHECK COLLISIONS ---
            // Wall collision
            if (snake[0].x <= 0 || snake[0].x >= cols - 1 || snake[0].y <= 0 || snake[0].y >= rows - 1) {
                is_game_over = true;
            }

            // Self collision
            // FIX: Loop to snake_length, not snake_length - 1
            for (int i = 1; i < snake_length; i++) {
                if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                    is_game_over = true;
                }
            }
            
            // Fruit collision
            if (snake[0].x == f.x && snake[0].y == f.y) {
                score++;
                if (snake_length < 100) snake_length++;
                f.x = 1 + (rand() % (cols - 2));
                f.y = 1 + (rand() % (rows - 2));
            }

            // --- DRAW ---
            clear();
            box(stdscr, 0, 0);
            mvaddch(f.y, f.x, fruit);
            for (int i = 0; i < snake_length; i++) {
                mvaddch(snake[i].y, snake[i].x, (i == 0) ? '@' : '=');
            }
            mvprintw(0, 2, "Score: %d", score);
            refresh();
        }
        user_choice = game_over(rows, cols, score);
    }

    endwin();
    return 0;
}

int game_over(int rows, int cols, int score) {
    timeout(-1); // Make getch() blocking

    WINDOW *win = newwin(10, 40, (rows - 10) / 2, (cols - 40) / 2);
    box(win, 0, 0);
    mvwprintw(win, 2, 14, "GAME OVER");
    mvwprintw(win, 4, 14, "SCORE: %d", score);
    mvwprintw(win, 6, 7, "q for quit, r for restart");
    wrefresh(win);

    flushinp();
    
    // FIX: Removed the incorrect getchar() call
    int ch;
    while ((ch = getch()) != 'q' && ch != 'r') {
        // Wait
    }

    delwin(win);
    return ch;
}
