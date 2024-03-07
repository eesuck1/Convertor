#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

static const string punctuation = { "!#$%&'()*+,-/:;<=>?@[\\]^`{|}~", 30 };
static const string whitespace = { " \t\n\r\v\f", 7 };
static const string latin_lower_alphabet = { "abcdefghijklmnopqrstuvwxyz", 27 };
static const string latin_upper_alphabet = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 27 };
static const string cyrillic_lower_alphabet = { "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ", 34 };
static const string cyrillic_upper_alphabet = { "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя", 34 };
static const string comment_string = { "--", 2 };

#endif // !CONSTANTS_H

