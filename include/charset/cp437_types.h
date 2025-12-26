#ifndef _RANDOM_OS_CP437_TYPES_H
#define _RANDOM_OS_CP437_TYPES_H

#include "core/types.h"

typedef int8 CP437_CharacterCode;

typedef enum CP437_CharactersEnum {
    CP437_CHAR_NULL = 0,                // \0
    CP437_CHAR_SPACE = 32,              // SPACE
    CP437_CHAR_NEW_LINE = 10,           // \n
    CP437_CHAR_CARRIAGE_RETURN = 13,    // \r
    CP437_CHAR_BACKSPACE = 8,           // \b
    CP437_CHAR_TAB = 9,                 // \t
    CP437_CHAR_EXCLAMATION_MARK = 33,   // !
    CP437_CHAR_DOUBLE_QUOTES,           // "
    CP437_CHAR_NUMBER_SIGN,             // #
    CP437_CHAR_DOLLAR_SIGN,             // $
    CP437_CHAR_PERCENT_SIGN,            // %
    CP437_CHAR_AMPERSAND,               // &
    CP437_CHAR_QUOTE,                   // '
    CP437_CHAR_LEFT_PAREN,              // (
    CP437_CHAR_RIGHT_PAREN,             // )
    CP437_CHAR_MULTIPLY_SIGN,           // *
    CP437_CHAR_PLUS_SIGN,               // +
    CP437_CHAR_COMMA,                   // ,
    CP437_CHAR_MINUS_SIGN,              // -
    CP437_CHAR_DOT,                     // .
    CP437_CHAR_SLASH,                   // /
    CP437_CHAR_0,                       // 0
    CP437_CHAR_1,                       // 1
    CP437_CHAR_2,                       // 2
    CP437_CHAR_3,                       // 3
    CP437_CHAR_4,                       // 4
    CP437_CHAR_5,                       // 5
    CP437_CHAR_6,                       // 6
    CP437_CHAR_7,                       // 7
    CP437_CHAR_8,                       // 8
    CP437_CHAR_9,                       // 9
    CP437_CHAR_COLON,                   // :
    CP437_CHAR_SEMICOLON,               // ;
    CP437_CHAR_LESS_SIGN,               // <
    CP437_CHAR_EQUAL,                   // =
    CP437_CHAR_BIG_SIGN,                // >
    CP437_CHAR_QUESTION_MARK,           // ?
    CP437_CHAR_AT_SIGN,                 // @
    CP437_CHAR_BIG_A,                   // A
    CP437_CHAR_BIG_B,                   // B
    CP437_CHAR_BIG_C,                   // C
    CP437_CHAR_BIG_D,                   // D
    CP437_CHAR_BIG_E,                   // E
    CP437_CHAR_BIG_F,                   // F
    CP437_CHAR_BIG_G,                   // G
    CP437_CHAR_BIG_H,                   // H
    CP437_CHAR_BIG_I,                   // I
    CP437_CHAR_BIG_J,                   // J
    CP437_CHAR_BIG_K,                   // K
    CP437_CHAR_BIG_L,                   // L
    CP437_CHAR_BIG_M,                   // M
    CP437_CHAR_BIG_N,                   // N
    CP437_CHAR_BIG_O,                   // O
    CP437_CHAR_BIG_P,                   // P
    CP437_CHAR_BIG_Q,                   // Q
    CP437_CHAR_BIG_R,                   // R
    CP437_CHAR_BIG_S,                   // S
    CP437_CHAR_BIG_T,                   // T
    CP437_CHAR_BIG_U,                   // U
    CP437_CHAR_BIG_V,                   // V
    CP437_CHAR_BIG_W,                   // W
    CP437_CHAR_BIG_X,                   // X
    CP437_CHAR_BIG_Y,                   // Y
    CP437_CHAR_BIG_Z,                   // Z
    CP437_CHAR_LEFT_BRACKET,            // [
    CP437_CHAR_BACKSLASH,               /* \ */
    CP437_CHAR_RIGHT_BRACKET,           // ]
    CP437_CHAR_CIRCUMFLEX,              // ^
    CP437_CHAR_UNDERSCORE,              // _
    CP437_CHAR_BACK_QUOTE,              // `
    CP437_CHAR_A,                       // a
    CP437_CHAR_B,                       // b
    CP437_CHAR_C,                       // c
    CP437_CHAR_D,                       // d
    CP437_CHAR_E,                       // e
    CP437_CHAR_F,                       // f
    CP437_CHAR_G,                       // g
    CP437_CHAR_H,                       // h
    CP437_CHAR_I,                       // i
    CP437_CHAR_J,                       // j
    CP437_CHAR_K,                       // k
    CP437_CHAR_L,                       // l
    CP437_CHAR_M,                       // m
    CP437_CHAR_N,                       // n
    CP437_CHAR_O,                       // o
    CP437_CHAR_P,                       // p
    CP437_CHAR_Q,                       // q
    CP437_CHAR_R,                       // r
    CP437_CHAR_S,                       // s
    CP437_CHAR_T,                       // t
    CP437_CHAR_U,                       // u
    CP437_CHAR_V,                       // v
    CP437_CHAR_W,                       // w
    CP437_CHAR_X,                       // x
    CP437_CHAR_Y,                       // y
    CP437_CHAR_Z,                       // z
    CP437_CHAR_LEFT_BRACE,              // {
    CP437_CHAR_VERTICAL_LINE,           // |
    CP437_CHAR_RIGHT_BRACE,             // }
    CP437_CHAR_TILDE                    // ~
} CP437_CharactersEnum;

#endif