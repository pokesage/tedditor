#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct termios termios_orig;

void disableRawMode() {
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &termios_orig);
}

void enableRawMode() {
    tcgetattr(STDERR_FILENO, &termios_orig);
    atexit(disableRawMode);
    
    struct termios raw = termios_orig;
    raw.c_iflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);

    tcsetattr(STDERR_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();
    char c;
    // comes from unistd.h we're asking to read one byte
    // from the standard input into the variable c, loop
    // until there are no more bytes left to read
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n", c, c);
        }
    }
    return 0;
}
