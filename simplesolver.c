#include "simplesolver.h"
#include <stdlib.h>
#include <stdio.h>

void action_print(SSAction action)
{
	printf("Action(lhs=");
	if (action.has_lhs) {
		printf("%d", action.lhs);
	} else {
		printf("NULL");
	}
	printf(", rhs=%d, op=", action.rhs);
	Token op_token = token_new(action.op, 0);
	token_print(&op_token);
	printf(")\n");
}

int solve_action(SSAction *action, int lhs)
{
	switch (action->op) {
		case Token_Plus:
			if (!action->has_lhs) {
				return lhs + action->rhs;
			} else {
				return action->lhs + action->rhs;
			}
		case Token_Minus:
			if (!action->has_lhs) {
				return lhs - action->rhs;
			} else {
				return action->lhs - action->rhs;
			}
		case Token_Multiply:
			if (!action->has_lhs) {
				return lhs * action->rhs;
			} else {
				return action->lhs * action->rhs;
			}
		case Token_Divide:
			if (!action->has_lhs) {
				return lhs / action->rhs;
			} else {
				return action->lhs / action->rhs;
			}
	}
	return 0;
}

int solve_actions(SSAction *actions, int num_actions)
{
	for (int i = 0; i < num_actions; i++) {
		SSAction *action = &actions[i];
		printf("working with action: ");
		action_print(*action);
		printf("\n");
		if (action->has_lhs) {
			int answer = solve_action(action, 0);
			action->is_solved = true;
			action->answer = answer;
			printf(" = %d (has lhs)\n", answer);
		} else {
			if (i == 0) {
				fprintf(stderr, "action 0 has no lhs\n");
				return 0;
			} else {
				int lhs = actions[i - 1].answer;
				int answer = solve_action(action, lhs);
				action->is_solved = true;
				action->answer = answer;
				printf(" = %d \n (hasn't lhs)\n", answer);
			}
		}
	}

	return actions[num_actions - 1].answer;
}

int solve_simple_expr(Token *tokens, int num_tokens)
{
	SSAction *actions = malloc(sizeof(SSAction) * num_tokens);
	// Make sure it's a simple expr (no parentheses)
	for (int i = 0; i < num_tokens; i++) {
		Token token = tokens[i];
		if (token.type == Token_ParenthesisOpen || token.type == Token_ParenthesisClose) {
			fprintf(stderr, "not a simple expr\n");
			return 0;
		}
	}

	int action_i = 0;
	for (int i = 0; i < num_tokens;) {
		Token token = tokens[i];
		if (token.type == Token_Number) {
			int lhs = token.value;
			int rhs = tokens[i + 2].value;
			printf("action has lhs. lhs=%d rhs=%d op=", lhs, rhs);
			token_print(&tokens[i + 1]);
			printf("\n");
			SSAction action;
			action.has_lhs = true;
			action.lhs = lhs;
			action.rhs = rhs;
			action.op = tokens[i + 1].type;
			action.is_solved = false;
			action.answer = 0;
			actions[action_i++] = action;
			i += 2;
		} else if (token_is_op(token.type)) {
			int rhs = tokens[i + 1].value;
			printf("action hasn't lhs. rhs=%d op=", rhs);
			token_print(&token);
			printf("\n");
			SSAction action;
			action.has_lhs = false;
			action.lhs = 0;
			action.rhs = rhs;
			action.op = token.type;
			action.is_solved = false;
			action.answer = 0;
			actions[action_i++] = action;
			i++;
		}
		i++;
	}

	for (int i = 0; i < action_i; i++) {
		action_print(actions[i]);
	}
	printf("\n");

	return solve_actions(actions, action_i);
}
