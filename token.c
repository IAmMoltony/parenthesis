#include "token.h"
#include <stdio.h>

void token_print(Token *token)
{
	switch (token->type) {
		case Token_Number:
			printf("<%d>", token->value);
			break;
		case Token_Plus:
			printf("<+>");
			break;
		case Token_Minus:
			printf("<->");
			break;
		case Token_Multiply:
			printf("<*>");
			break;
		case Token_Divide:
			printf("</>"); // bruh this reminds me of like every web dev icon istg the html lookin ahh
			break;
		case Token_ParenthesisOpen:
			printf("<(>");
			break;
		case Token_ParenthesisClose:
			printf("<)>");
			break;
		default:
			printf("girl what kinda token is this");
			break;
	}
}

Token token_new(TokenType type, int value)
{
	Token token;
	token.type = type;
	token.value = value;
	return token;
}

bool token_is_op(TokenType type)
{
	return
		(type == Token_Plus) ||
		(type == Token_Minus) ||
		(type == Token_Multiply) ||
		(type == Token_Divide);
}
