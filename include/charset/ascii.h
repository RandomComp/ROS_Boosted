#ifndef _RANDOM_OS_ASCII_H
#define _RANDOM_OS_ASCII_H

#include "charset/ugsm.h"

typedef int8 ASCIIGlyphCode;

typedef enum ASCIIKeyCodes {
    ASCII_CHAR_NULL = 0,                // \0
    ASCII_CHAR_SPACE = 32,              // SPACE
    ASCII_CHAR_NEW_LINE = 10,           // \n
    ASCII_CHAR_CARRIAGE_RETURN = 13,    // \r
    ASCII_CHAR_BACKSPACE = 8,           // \b
    ASCII_CHAR_TAB = 9,                 // \t
    ASCII_CHAR_EXCLAMATION_MARK = 33,   // !
    ASCII_CHAR_DOUBLE_QUOTES,           // "
    ASCII_CHAR_NUMBER_SIGN,             // #
    ASCII_CHAR_DOLLAR_SIGN,             // $
    ASCII_CHAR_PERCENT_SIGN,            // %
    ASCII_CHAR_AMPERSAND,               // &
    ASCII_CHAR_QUOTE,                   // '
    ASCII_CHAR_LEFT_PAREN,              // (
    ASCII_CHAR_RIGHT_PAREN,             // )
    ASCII_CHAR_MULTIPLY_SIGN,           // *
    ASCII_CHAR_PLUS_SIGN,               // +
    ASCII_CHAR_COMMA,                   // ,
    ASCII_CHAR_MINUS_SIGN,              // -
    ASCII_CHAR_DOT,                     // .
    ASCII_CHAR_SLASH,                   // /
    ASCII_CHAR_0,                       // 0
    ASCII_CHAR_1,                       // 1
    ASCII_CHAR_2,                       // 2
    ASCII_CHAR_3,                       // 3
    ASCII_CHAR_4,                       // 4
    ASCII_CHAR_5,                       // 5
    ASCII_CHAR_6,                       // 6
    ASCII_CHAR_7,                       // 7
    ASCII_CHAR_8,                       // 8
    ASCII_CHAR_9,                       // 9
    ASCII_CHAR_COLON,                   // :
    ASCII_CHAR_SEMICOLON,               // ;
    ASCII_CHAR_LESS_SIGN,               // <
    ASCII_CHAR_EQUAL,                   // =
    ASCII_CHAR_BIG_SIGN,                // >
    ASCII_CHAR_QUESTION_MARK,           // ?
    ASCII_CHAR_AT_SIGN,                 // @
    ASCII_CHAR_BIG_A,                   // A
    ASCII_CHAR_BIG_B,                   // B
    ASCII_CHAR_BIG_C,                   // C
    ASCII_CHAR_BIG_D,                   // D
    ASCII_CHAR_BIG_E,                   // E
    ASCII_CHAR_BIG_F,                   // F
    ASCII_CHAR_BIG_G,                   // G
    ASCII_CHAR_BIG_H,                   // H
    ASCII_CHAR_BIG_I,                   // I
    ASCII_CHAR_BIG_J,                   // J
    ASCII_CHAR_BIG_K,                   // K
    ASCII_CHAR_BIG_L,                   // L
    ASCII_CHAR_BIG_M,                   // M
    ASCII_CHAR_BIG_N,                   // N
    ASCII_CHAR_BIG_O,                   // O
    ASCII_CHAR_BIG_P,                   // P
    ASCII_CHAR_BIG_Q,                   // Q
    ASCII_CHAR_BIG_R,                   // R
    ASCII_CHAR_BIG_S,                   // S
    ASCII_CHAR_BIG_T,                   // T
    ASCII_CHAR_BIG_U,                   // U
    ASCII_CHAR_BIG_V,                   // V
    ASCII_CHAR_BIG_W,                   // W
    ASCII_CHAR_BIG_X,                   // X
    ASCII_CHAR_BIG_Y,                   // Y
    ASCII_CHAR_BIG_Z,                   // Z
    ASCII_CHAR_LEFT_BRACKET,            // [
    ASCII_CHAR_BACKSLASH,               /* \ */
    ASCII_CHAR_RIGHT_BRACKET,           // ]
    ASCII_CHAR_CIRCUMFLEX,              // ^
    ASCII_CHAR_UNDERSCORE,              // _
    ASCII_CHAR_BACK_QUOTE,              // `
    ASCII_CHAR_A,                       // a
    ASCII_CHAR_B,                       // b
    ASCII_CHAR_C,                       // c
    ASCII_CHAR_D,                       // d
    ASCII_CHAR_E,                       // e
    ASCII_CHAR_F,                       // f
    ASCII_CHAR_G,                       // g
    ASCII_CHAR_H,                       // h
    ASCII_CHAR_I,                       // i
    ASCII_CHAR_J,                       // j
    ASCII_CHAR_K,                       // k
    ASCII_CHAR_L,                       // l
    ASCII_CHAR_M,                       // m
    ASCII_CHAR_N,                       // n
    ASCII_CHAR_O,                       // o
    ASCII_CHAR_P,                       // p
    ASCII_CHAR_Q,                       // q
    ASCII_CHAR_R,                       // r
    ASCII_CHAR_S,                       // s
    ASCII_CHAR_T,                       // t
    ASCII_CHAR_U,                       // u
    ASCII_CHAR_V,                       // v
    ASCII_CHAR_W,                       // w
    ASCII_CHAR_X,                       // x
    ASCII_CHAR_Y,                       // y
    ASCII_CHAR_Z,                       // z
    ASCII_CHAR_LEFT_BRACE,              // {
    ASCII_CHAR_VERTICAL_LINE,           // |
    ASCII_CHAR_RIGHT_BRACE,             // }
    ASCII_CHAR_TILDE                    // ~
} ASCIIKeyCodes;

void ASCIIloadToUGSM();

ASCIIGlyphCode ASCIIUGSMCharToASCII(UGSMGlyphCode c);

ASCIIGlyphCode ASCIIdigitToUGSM(uint8 digit);

#endif