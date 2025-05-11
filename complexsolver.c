#include "complexsolver.h"
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include "simplesolver.h"

void simplify_complex_expr(Token *tokens, int *num_tokens)
{
	for (int i = 0; i < *num_tokens; i++) {
		Token token = tokens[i];
		if (token.type == Token_ParenthesisOpen) {
			int parenthesis_depth = 1;
			for (int j = i + 1; j < *num_tokens; j++) {
				if (tokens[j].type == Token_ParenthesisClose) {
					parenthesis_depth--;
				} else if (tokens[j].type == Token_ParenthesisOpen) {
					parenthesis_depth++;
				}

				if (parenthesis_depth == 0) {
					int inner_len = j - i - 1;
					Token *inner_tokens = malloc(sizeof(Token) * inner_len);
					memcpy(inner_tokens, &tokens[i+1], sizeof(Token) * inner_len);
					simplify_complex_expr(inner_tokens, &inner_len);
					int result = solve_simple_expr(inner_tokens, inner_len);
					tokens[i] = token_new(Token_Number, result);
					memmove(&tokens[i + 1], &tokens[j + 1], sizeof(Token) * (*num_tokens - j - 1));
					*num_tokens -= (j - i);

					i = -1;
					break;
				}
			}
		}
	}
}
