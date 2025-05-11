#include "validator.h"
#include <stdio.h>
#include "tokenlist.h"

bool validate(Token *tokens, int num_tokens)
{
	int parenthesis_depth = 0;
	
	for (int i = 0; i < num_tokens; i++) {
		Token token = tokens[i];
		if (i == 0 && token.type != Token_Number && token.type != Token_ParenthesisOpen) {
			fprintf(stderr, "expr begin with op\n");
			return false;
		}

		if (token.type == Token_ParenthesisOpen) {
			parenthesis_depth++;
			continue;
		}
		if (token.type == Token_ParenthesisClose) {
			parenthesis_depth--;
			continue;
		}

		if (token.type == Token_Number) {
			if (next_token_is(i, num_tokens, tokens, Token_Number)) {
				fprintf(stderr, "2 consecutive numbers\n");	
				return false;
			}
			if (prev_token_is(i, num_tokens, tokens, Token_ParenthesisClose)) {
				fprintf(stderr, "num after close paren\n");
				return false;
			}
			if (next_token_is(i, num_tokens, tokens, Token_ParenthesisOpen)) {
				fprintf(stderr, "num before open paren\n");
				return false;
			}
		} else {
			if (next_token_is_op(i, num_tokens, tokens)) {
				fprintf(stderr, "2 consecutive ops\n");
				return false;
			}

			if (token_is_op(token.type)) {
				if (prev_token_is(i, num_tokens, tokens, Token_ParenthesisOpen)) {
					fprintf(stderr, "op after open paren\n");
					return false;
				}
				if (next_token_is(i, num_tokens, tokens, Token_ParenthesisClose)) {
					fprintf(stderr, "op before close paren\n");
					return false;
				}
			}
		}
	}

	if (parenthesis_depth > 0) {
		fprintf(stderr, "unclosed parenthesis\n");
		return false;
	}
	if (parenthesis_depth < 0) {
		fprintf(stderr, "unopened parenthesis\n");
		return false;
	}

	printf("expr is a ok\n");

	return true;
}
