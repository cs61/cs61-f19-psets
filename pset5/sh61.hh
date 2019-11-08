#ifndef SH61_HH
#define SH61_HH
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <fcntl.h>
#include <unistd.h>
#include <string>

#define TYPE_NORMAL        0   // normal command word
#define TYPE_REDIRECTION   1   // redirection operator (>, <, 2>)

// All other tokens are control operators that terminate the current command.
#define TYPE_SEQUENCE      2   // `;` sequence operator
#define TYPE_BACKGROUND    3   // `&` background operator
#define TYPE_PIPE          4   // `|` pipe operator
#define TYPE_AND           5   // `&&` operator
#define TYPE_OR            6   // `||` operator

// If you want to handle an extended shell syntax for extra credit, here are
// some other token types to get you started.
#define TYPE_LPAREN        7   // `(` operator
#define TYPE_RPAREN        8   // `)` operator
#define TYPE_OTHER         -1

// parse_shell_token(str, type, token)
//    Parse the next token from the shell command `str`. Stores the type of
//    the token in `*type`; this is one of the TYPE_ constants. Stores the
//    token itself in `*token`. Advances `str` to the next token and returns
//    that pointer.
//
//    At the end of the string, returns nullptr, sets `*type` to
//    TYPE_SEQUENCE, and sets `*token` to en empty string.
const char* parse_shell_token(const char* str, int* type, std::string* token);

// claim_foreground(pgid)
//    Mark `pgid` as the current foreground process group.
int claim_foreground(pid_t pgid);

// set_signal_handler(signo, handler)
//    Install handler `handler` for signal `signo`. `handler` can be SIG_DFL
//    to install the default handler, or SIG_IGN to ignore the signal. Return
//    0 on success, -1 on failure. See `man 2 sigaction` or `man 3 signal`.
inline int set_signal_handler(int signo, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    return sigaction(signo, &sa, NULL);
}

#endif
