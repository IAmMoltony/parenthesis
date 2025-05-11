#ifndef __lexer_h
#define __lexer_h

#include "token.h"

Token *lex(const char *expression, int *num_tokens_out);

#endif
