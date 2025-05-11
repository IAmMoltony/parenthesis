#ifndef __simplesolver_h
#define __simplesolver_h

#include <stdbool.h>
#include "token.h"

typedef struct
{
	TokenType op;
	int lhs;
	int rhs;
	bool has_lhs;
	bool has_rhs;
	bool is_solved;
	int answer;
} SSAction;

int solve_action(SSAction *action, int lhs);
int solve_simple_expr(Token *tokens, int num_tokens);

#endif
