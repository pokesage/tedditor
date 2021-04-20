#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct termios termios_orig;

//error handling
void die(const char *s) {
    perror(s);
    exit(1);
}

void disableRawMode() {
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &termios_orig);
}

void enableRawMode() {
    tcgetattr(STDERR_FILENO, &termios_orig);
    atexit(disableRawMode);
    
    struct termios raw = termios_orig;
    raw.c_iflag &= ~(BRKINT | ICRNL | IXON | INPCK | ISTRIP);
    raw.c_iflag &= ~(OPOST);
    raw.c_iflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDERR_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();
    char c;
    // comes from unistd.h we're asking to read one byte
    // from the standard input into the variable c, loop
    // until there are no more bytes left to read
    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q') break;
    }
    return 0;
}
