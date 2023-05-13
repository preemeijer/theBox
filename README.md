# theBox

For the "story", rules and controls see https://reemeijer.nl/theBox

## Installation
 * Clone the git repository
 * Make sure you have ncurses lib on your machine
 * Go to src directory and execute:
     * "gcc theBox-ncurses.c -o theBox -lncurses"
 * Copy "theBox" where you want (or not) to start the mini game
 * Copy theBox.6x.gz to your manpage directory or beside your theBox binary"
     * You can read the manpage "man ./theBox.6x.gz"

## "Remote play"
Remote play through the same machine between two users is not implemented yet.

There is a solution with TMUX and / or SCREEN. Manual found at the following URL: https://www.howtoforge.com/sharing-terminal-sessions-with-tmux-and-screen#basic-sharing-with-screen
