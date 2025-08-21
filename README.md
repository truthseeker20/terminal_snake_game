g C Terminal Based Snake and Fruit Game

=> I was learning linux commands on wsl ubuntu terminal, I enjoyed the feel of using terminal and terminal based text editors and writing gcc commands to make the executables very much, then thought to make a terminal based game: and here we are.

=> Gemini helped along the way, and i tried to use it minimally.

=> I used ncurses library for this project, because it is the standard for C applications on Unix-like systems.

=> ncurses is a programming library that provides an API for creating text based user interfaces (TUI)

=> how it helped?

    1. I had to draw characters (snake-head and body, fruit, score, game over text etc,.) on specific points on the screen, and it allows us to treat the entire terminal screen as a grid of characters.

    2. it provides getchar() which is a blocking function, which I used when game over window display, and user has to press q or r for quit or restart respectively, so getchar() blocks the program until user presses any of the key.

    3. along with getchar(), it also provides timeout() which makes the getchar() wait for only defined time, after then code runs - so making it non blocking, I used it for continuous snake movement and not waiting for user input (up/left/right/down)

    4. it has special support for handling arrow keys using keypad(stdscr, TRUE), now getchar() identifies them simply by KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT.

    5. it allows us to create windows inside window, like making a game over pop up window

    6. and many more!!!

=> documentation on how to use ncurses funtions can be found here: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html

=> How to compile?

1. download source code
2. gcc src/*.c -lncurses -o snake
3. ./snake
