#ifndef __token_h
#define __token_h

typedef enum
{
	Token_Number,
	Token_Plus,
	Token_Minus,
	Token_Multiply,
	Token_Divide,
	Token_ParenthesisOpen,
	Token_ParenthesisClose
} TokenType;

typedef struct
{
	TokenType type;
	int value; // if number
} Token;

void token_print(Token *token);
Token token_new(TokenType type, int value);
bool token_is_op(TokenType type);

#endif
