#ifndef __tokenlist_h
#define __tokenlist_h

#include <stdbool.h>
#include "token.h"

bool next_token_is(int current_token_i, int num_tokens, Token *tokens, TokenType type);
bool next_token_is_op(int current_token_i, int num_tokens, Token *tokens);
bool prev_token_is(int current_token_i, int num_tokens, Token *tokens, TokenType type);

#endif
