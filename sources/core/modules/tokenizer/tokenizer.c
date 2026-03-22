#include "tokenizer/tokenize.h"

#include "core/basic_types.h"

#include "builtins/mem.h"

#include "drivers/memory/ram.h"

uint32 sep_count(c_str text, size_t text_len, c_char sep) {
	uint32 result = 1;

	for (uint32 i = 0; i < text_len; i++) {
		c_char cur_ch = text[i];

		if (cur_ch == sep) result++;
	}

	return result;
}

int32 find_next_ch_after(c_str text, size_t text_len, c_char ch, uint32 after) {
	for (uint32 i = after; i < text_len; i++) {
		if (text[i] == ch) return i;
	}

	return -1;
}

c_str sub_str(c_str text, uint32 start, uint32 end) {
	uint32 len = end - start;

	c_str result = malloc(len + 1);

	memcpy(result, text + start, len);

	result[len] = '\0';

	return result;
}

size_t* get_sub_strs_len_splitted_for(const char* text, size_t text_len, char sep) {
	size_t str_sep_cnt = sep_count(text, text_len, sep);

	size_t* result = (size_t*)malloc(str_sep_cnt * sizeof(size_t));

	int start = 0, end = 0, sub_str_num = 0;

	while (sub_str_num < str_sep_cnt) {
		end = find_next_ch_after(text, text_len, sep, start);

		result[sub_str_num] = end - start;

		sub_str_num++;

		start = end + 1;
	}

	return result;
}

// With out copy
c_str* wc_split_for(c_str text, size_t text_len, c_char sep) {
	uint32 str_sep_cnt = sep_count(text, text_len, sep);

	c_str* result = malloc(str_sep_cnt * sizeof(c_str));

	uint32 start = 0;

	for (uint32 i = 0; i < str_sep_cnt; i++) {
		result[i] = text + start;

		start = find_next_ch_after(text, text_len, sep, start) + 1;
	}

	return result;
}