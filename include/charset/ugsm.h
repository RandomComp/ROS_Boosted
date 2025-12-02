#ifndef _UGSM_H
#define _UGSM_H

#include "core/types.h"

#include "charset/glyph.h"

#define UGSMMaxSize 1024

#define UGSMMaxLoadableSize 128

#define UGSMGlyphWidth 8

#define UGSMGlyphHeight 16

typedef uint8 UGSMGlyph[UGSMGlyphHeight]; // width, height - 8, 16

typedef uint8 UGSMGlyphSet[UGSMMaxLoadableSize][UGSMGlyphHeight];

typedef uint8 IUGSM[UGSMMaxSize][UGSMGlyphHeight];

typedef uint16 IUGSMSize;

typedef uint16 UGSMGlyphSetSize;

typedef uint16 UGSMGlyphSetCode;

enum UGSMKeyCodes {
    UGSM_CHAR_NULL,                 // \0
    UGSM_CHAR_SPACE,                // 
    UGSM_CHAR_NEW_LINE,             // \n
    UGSM_CHAR_CARRIAGE_RETURN,      // \r
    UGSM_CHAR_TAB,                  // \t
    UGSM_CHAR_EXCLAMATION_MARK,     // !
    UGSM_CHAR_DOUBLE_QUOTES,        // "
    UGSM_CHAR_NUMBER_SIGN,          // #
    UGSM_CHAR_DOLLAR_SIGN,          // $
    UGSM_CHAR_PERCENT_SIGN,         // %
    UGSM_CHAR_AMPERSAND,            // &
    UGSM_CHAR_QUOTE,                // '
    UGSM_CHAR_LEFT_PAREN,           // (
    UGSM_CHAR_RIGHT_PAREN,          // )
    UGSM_CHAR_MULTIPLY_SIGN,        // *
    UGSM_CHAR_PLUS_SIGN,            // +
    UGSM_CHAR_COMMA,                // ,
    UGSM_CHAR_MINUS_SIGN,           // -
    UGSM_CHAR_DOT,                  // .
    UGSM_CHAR_SLASH,                // /
    UGSM_CHAR_ZERO,                 // 0
    UGSM_CHAR_ONE,                  // 1
    UGSM_CHAR_TWO,                  // 2
    UGSM_CHAR_THREE,                // 3
    UGSM_CHAR_FOUR,                 // 4
    UGSM_CHAR_FIVE,                 // 5
    UGSM_CHAR_SIX,                  // 6
    UGSM_CHAR_SEVEN,                // 7
    UGSM_CHAR_EIGHT,                // 8
    UGSM_CHAR_NINE,                 // 9
    UGSM_CHAR_COLON,                // :
    UGSM_CHAR_SEMICOLON,            // ;
    UGSM_CHAR_LESS_SIGN,            // <
    UGSM_CHAR_EQUAL,                // =
    UGSM_CHAR_BIG_SIGN,             // >
    UGSM_CHAR_QUESTION_MARK,        // ?
    UGSM_CHAR_AT_SIGN,              // @
    UGSM_CHAR_BIG_A,                // A
    UGSM_CHAR_BIG_B,                // B
    UGSM_CHAR_BIG_C,                // C
    UGSM_CHAR_BIG_D,                // D
    UGSM_CHAR_BIG_E,                // E
    UGSM_CHAR_BIG_F,                // F
    UGSM_CHAR_BIG_G,                // G
    UGSM_CHAR_BIG_H,                // H
    UGSM_CHAR_BIG_I,                // I
    UGSM_CHAR_BIG_J,                // J
    UGSM_CHAR_BIG_K,                // K
    UGSM_CHAR_BIG_L,                // L
    UGSM_CHAR_BIG_M,                // M
    UGSM_CHAR_BIG_N,                // N
    UGSM_CHAR_BIG_O,                // O
    UGSM_CHAR_BIG_P,                // P
    UGSM_CHAR_BIG_Q,                // Q
    UGSM_CHAR_BIG_R,                // R
    UGSM_CHAR_BIG_S,                // S
    UGSM_CHAR_BIG_T,                // T
    UGSM_CHAR_BIG_U,                // U
    UGSM_CHAR_BIG_V,                // V
    UGSM_CHAR_BIG_W,                // W
    UGSM_CHAR_BIG_X,                // X
    UGSM_CHAR_BIG_Y,                // Y
    UGSM_CHAR_BIG_Z,                // Z
    UGSM_CHAR_LEFT_BRACKET,         // [
    UGSM_CHAR_BACKSLASH,            /* \ */
    UGSM_CHAR_RIGHT_BRACKET,        // ]
    UGSM_CHAR_CIRCUMFLEX,           // ^
    UGSM_CHAR_UNDERSCORE,           // _
    UGSM_CHAR_BACK_QUOTE,           // `
    UGSM_CHAR_A,                    // a
    UGSM_CHAR_B,                    // b
    UGSM_CHAR_C,                    // c
    UGSM_CHAR_D,                    // d
    UGSM_CHAR_E,                    // e
    UGSM_CHAR_F,                    // f
    UGSM_CHAR_G,                    // g
    UGSM_CHAR_H,                    // h
    UGSM_CHAR_I,                    // i
    UGSM_CHAR_J,                    // j
    UGSM_CHAR_K,                    // k
    UGSM_CHAR_L,                    // l
    UGSM_CHAR_M,                    // m
    UGSM_CHAR_N,                    // n
    UGSM_CHAR_O,                    // o
    UGSM_CHAR_P,                    // p
    UGSM_CHAR_Q,                    // q
    UGSM_CHAR_R,                    // r
    UGSM_CHAR_S,                    // s
    UGSM_CHAR_T,                    // t
    UGSM_CHAR_U,                    // u
    UGSM_CHAR_V,                    // v
    UGSM_CHAR_W,                    // w
    UGSM_CHAR_X,                    // x
    UGSM_CHAR_Y,                    // y
    UGSM_CHAR_Z,                    // z
    UGSM_CHAR_LEFT_BRACE,           // {
    UGSM_CHAR_VERTICAL_LINE,        // |
    UGSM_CHAR_RIGHT_BRACE,          // }
    UGSM_CHAR_TILDE,                // ~
    UGSM_CHAR_RUS_A,                // а
    UGSM_CHAR_RUS_B,                // б
    UGSM_CHAR_RUS_V,                // в
    UGSM_CHAR_RUS_G,                // г
    UGSM_CHAR_RUS_D,                // д
    UGSM_CHAR_RUS_E,                // е
    UGSM_CHAR_RUS_YO,               // ё
    UGSM_CHAR_RUS_ZH,               // ж
    UGSM_CHAR_RUS_Z,                // з
    UGSM_CHAR_RUS_I,                // и
    UGSM_CHAR_RUS_I_BREVE,          // й
    UGSM_CHAR_RUS_K,                // к
    UGSM_CHAR_RUS_L,                // л
    UGSM_CHAR_RUS_M,                // м
    UGSM_CHAR_RUS_N,                // н
    UGSM_CHAR_RUS_O,                // о
    UGSM_CHAR_RUS_P,                // п
    UGSM_CHAR_RUS_R,                // р
    UGSM_CHAR_RUS_S,                // с
    UGSM_CHAR_RUS_T,                // т
    UGSM_CHAR_RUS_U,                // у
    UGSM_CHAR_RUS_F,                // ф
    UGSM_CHAR_RUS_KH,               // х
    UGSM_CHAR_RUS_TS,               // ц
    UGSM_CHAR_RUS_CH,               // ч
    UGSM_CHAR_RUS_SH,               // ш
    UGSM_CHAR_RUS_SHH,              // щ
    UGSM_CHAR_RUS_TVERDIJ_ZNAK,     // ъ
    UGSM_CHAR_RUS_bI,               // ы
    UGSM_CHAR_RUS_MYAKHKI_ZNAK,     // ь
    UGSM_CHAR_RUS_E_K,              // э
    UGSM_CHAR_RUS_YU,               // ю
    UGSM_CHAR_RUS_YA,               // я
    UGSM_CHAR_RUS_BIG_A,            // А
    UGSM_CHAR_RUS_BIG_B,            // Б
    UGSM_CHAR_RUS_BIG_V,            // В
    UGSM_CHAR_RUS_BIG_G,            // Г
    UGSM_CHAR_RUS_BIG_D,            // Д
    UGSM_CHAR_RUS_BIG_E,            // Е
    UGSM_CHAR_RUS_BIG_YO,           // Ё
    UGSM_CHAR_RUS_BIG_ZH,           // Ж
    UGSM_CHAR_RUS_BIG_Z,            // З
    UGSM_CHAR_RUS_BIG_I,            // И
    UGSM_CHAR_RUS_BIG_I_BREVE,      // Й
    UGSM_CHAR_RUS_BIG_K,            // К
    UGSM_CHAR_RUS_BIG_L,            // Л
    UGSM_CHAR_RUS_BIG_M,            // М
    UGSM_CHAR_RUS_BIG_N,            // Н
    UGSM_CHAR_RUS_BIG_O,            // О
    UGSM_CHAR_RUS_BIG_P,            // П
    UGSM_CHAR_RUS_BIG_R,            // Р
    UGSM_CHAR_RUS_BIG_S,            // С
    UGSM_CHAR_RUS_BIG_T,            // Т
    UGSM_CHAR_RUS_BIG_U,            // У
    UGSM_CHAR_RUS_BIG_F,            // Ф
    UGSM_CHAR_RUS_BIG_KH,           // Х
    UGSM_CHAR_RUS_BIG_TS,           // Ц
    UGSM_CHAR_RUS_BIG_CH,           // Ч
    UGSM_CHAR_RUS_BIG_SH,           // Ш
    UGSM_CHAR_RUS_BIG_SHH,          // Щ
    UGSM_CHAR_RUS_BIG_TVERDIJ_ZNAK, // Ъ
    UGSM_CHAR_RUS_BIG_bI,           // Ы
    UGSM_CHAR_RUS_BIG_MYAKHKI_ZNAK, // Ь
    UGSM_CHAR_RUS_BIG_E_K,          // Э
    UGSM_CHAR_RUS_BIG_YU,           // Ю
    UGSM_CHAR_RUS_BIG_YA,           // Я
};

enum ASCIIKeyCodes {
    ASCII_CHAR_NULL = 0,
    ASCII_CHAR_SPACE = 32,
    ASCII_CHAR_NEW_LINE = 10,
    ASCII_CHAR_CARRIAGE_RETURN = 13,
    ASCII_CHAR_TAB = 9,
    ASCII_CHAR_EXCLAMATION_MARK = 33,
    ASCII_CHAR_DOUBLE_QUOTES,
    ASCII_CHAR_NUMBER_SIGN,
    ASCII_CHAR_DOLLAR_SIGN,
    ASCII_CHAR_PERCENT_SIGN,
    ASCII_CHAR_AMPERSAND,
    ASCII_CHAR_QUOTE,
    ASCII_CHAR_LEFT_PAREN,
    ASCII_CHAR_RIGHT_PAREN,
    ASCII_CHAR_MULTIPLY_SIGN,
    ASCII_CHAR_PLUS_SIGN,
    ASCII_CHAR_COMMA,
    ASCII_CHAR_MINUS_SIGN,
    ASCII_CHAR_DOT,
    ASCII_CHAR_SLASH,
    ASCII_CHAR_ZERO,
    ASCII_CHAR_ONE,
    ASCII_CHAR_TWO,
    ASCII_CHAR_THREE,
    ASCII_CHAR_FOUR,
    ASCII_CHAR_FIVE,
    ASCII_CHAR_SIX,
    ASCII_CHAR_SEVEN,
    ASCII_CHAR_EIGHT,
    ASCII_CHAR_NINE,
    ASCII_CHAR_COLON,
    ASCII_CHAR_SEMICOLON,
    ASCII_CHAR_LESS_SIGN,
    ASCII_CHAR_EQUAL,
    ASCII_CHAR_BIG_SIGN,
    ASCII_CHAR_QUESTION_MARK,
    ASCII_CHAR_AT_SIGN,
    ASCII_CHAR_BIG_A,
    ASCII_CHAR_BIG_B,
    ASCII_CHAR_BIG_C,
    ASCII_CHAR_BIG_D,
    ASCII_CHAR_BIG_E,
    ASCII_CHAR_BIG_F,
    ASCII_CHAR_BIG_G,
    ASCII_CHAR_BIG_H,
    ASCII_CHAR_BIG_I,
    ASCII_CHAR_BIG_J,
    ASCII_CHAR_BIG_K,
    ASCII_CHAR_BIG_L,
    ASCII_CHAR_BIG_M,
    ASCII_CHAR_BIG_N,
    ASCII_CHAR_BIG_O,
    ASCII_CHAR_BIG_P,
    ASCII_CHAR_BIG_Q,
    ASCII_CHAR_BIG_R,
    ASCII_CHAR_BIG_S,
    ASCII_CHAR_BIG_T,
    ASCII_CHAR_BIG_U,
    ASCII_CHAR_BIG_V,
    ASCII_CHAR_BIG_W,
    ASCII_CHAR_BIG_X,
    ASCII_CHAR_BIG_Y,
    ASCII_CHAR_BIG_Z,
    ASCII_CHAR_LEFT_BRACKET,
    ASCII_CHAR_BACKSLASH,
    ASCII_CHAR_RIGHT_BRACKET,
    ASCII_CHAR_CIRCUMFLEX,
    ASCII_CHAR_UNDERSCORE,
    ASCII_CHAR_BACK_QUOTE,
    ASCII_CHAR_A,
    ASCII_CHAR_B,
    ASCII_CHAR_C,
    ASCII_CHAR_D,
    ASCII_CHAR_E,
    ASCII_CHAR_F,
    ASCII_CHAR_G,
    ASCII_CHAR_H,
    ASCII_CHAR_I,
    ASCII_CHAR_J,
    ASCII_CHAR_K,
    ASCII_CHAR_L,
    ASCII_CHAR_M,
    ASCII_CHAR_N,
    ASCII_CHAR_O,
    ASCII_CHAR_P,
    ASCII_CHAR_Q,
    ASCII_CHAR_R,
    ASCII_CHAR_S,
    ASCII_CHAR_T,
    ASCII_CHAR_U,
    ASCII_CHAR_V,
    ASCII_CHAR_W,
    ASCII_CHAR_X,
    ASCII_CHAR_Y,
    ASCII_CHAR_Z,
    ASCII_CHAR_LEFT_BRACE,
    ASCII_CHAR_VERTICAL_LINE,
    ASCII_CHAR_RIGHT_BRACE,
    ASCII_CHAR_TILDE,
};

UGSMGlyphSetCode UGSMloadGlyphSet(UGSMGlyphSet glyphSet, UGSMGlyphSetSize length);

UGSMGlyphCode UGSMloadGlyph(UGSMGlyph glyph);

void UGSMcheckGlyphCode(UGSMGlyphCode glyphCode);

UGSMGlyph* UGSMgetGlyph(UGSMGlyphCode glyphCode);

void UGSMASCIIputString(int8* str);

void UGSMASCIIputChar(int8 c);

UGSMGlyphCode ASCIICharToUGSM(int8 c);

void UGSMASCIIsetString(uint16 x, uint16 y, int8* str);

void UGSMASCIIsetChar(uint16 x, uint16 y, int8 c);

#endif