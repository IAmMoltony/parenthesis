#include <stdio.h>
#include "lexer.h"
#include "validator.h"
#include "simplesolver.h"
#include "complexsolver.h"

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Please supply one argument\n");
		return 1;
	}
	int num_tokens = 0;
	Token *tokens = lex(argv[1], &num_tokens);
	if (num_tokens == 0) {
		fprintf(stderr, "No tokens found or lexer error occured.\n");
		return 1;
	}
	token_print(&tokens[0]);
	if (!validate(tokens, num_tokens)) {
		fprintf(stderr, "Invalid syntax\n");
		return 1;
	}

	simplify_complex_expr(tokens, &num_tokens);
	printf("%d\n", solve_simple_expr(tokens, num_tokens));

	return 0;
}
