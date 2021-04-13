#include <unistd.h>

int main() {
    char c;
    // comes from unistd.h we're asking to read one byte
    // from the standard input into the variable c, loop
    // until there are no more bytes left to read
    while (read(STDIN_FILENO, &c, 1) == 1);
    return 0;
}
