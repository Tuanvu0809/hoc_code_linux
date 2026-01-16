#ifndef STRUTILS_H
#define STRUTILS_H

// o str_reverse: Reverses a string in-place.
// o str_trim: Removes leading and trailing whitespace from a string.
// o str_to_int: Safely converts a string to an integer.

enum Check_string{
    text = 0,
    number,
};

void str_reverse(char *str);
void str_trim(char *str);
int str_to_int(char *str, int *integer_convert);

#endif