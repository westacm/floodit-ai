# floodit-ai
C++ implementation of FloodIt, used for writing AI to play the game - might be used in competition in the future.

## Players

### Human Player
Very simply asks the user to enter a move through the console and plays that if possible.

### "Basic AI"
(needs a better name...)

Looks from left-right, top-down for the first colour that is different to the top-left colour, then plays row: 0, col: 0, colour: the new found colour.
