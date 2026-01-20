#ifndef _RANDOM_OS_TOKENIZER_TOKENIZE_H
#define _RANDOM_OS_TOKENIZER_TOKENIZE_H

#include "core/basic_types.h"

uint32 sep_count(c_str text, c_char sep);

int32 find_next_ch_after(c_str text, c_char ch, uint32 after);

c_str sub_str(c_str text, uint32 start, uint32 end);

c_str* wc_split_for(c_str text, c_char sep);

#endif