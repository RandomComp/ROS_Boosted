#ifndef _RL_LEXER_H
#define _RL_LEXER_H

#include "core/types/basic_types.h"

#include "charset/ugsm.h"

enum RLTokenType {
	RLNUMBER,
	
	RLWORD,
	
	// keyword
	
	RETURN,

	// parentheses

	LPAR, // (

	RPAR, // )

	LBRACE, // {

	RBRACE, // }

	RLCOMMA, // ,

	RLEOF // end of file
};

struct RLToken {
	enum RLTokenType type;

	UGSM_CharacterCode word[12];
};

void RLTokenize(UGSM_CharacterCode code[384]);

void RLTokensView(void);

#endif