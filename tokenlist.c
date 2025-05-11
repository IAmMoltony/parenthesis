#include "tokenlist.h"

bool next_token_is(int current_token_i, int num_tokens, Token *tokens, TokenType type)
{
	if (current_token_i == num_tokens - 1) {
		return false;
	}
	return tokens[current_token_i + 1].type == type;
}


bool next_token_is_op(int current_token_i, int num_tokens, Token *tokens)
{
	if (current_token_i == num_tokens - 1) {
		return false;
	}
	return token_is_op(tokens[current_token_i + 1].type);
}

bool prev_token_is(int current_token_i, int num_tokens, Token *tokens, TokenType type)
{
	if (current_token_i == 0) {
		return false;
	}
	return tokens[current_token_i - 1].type == type;
}
