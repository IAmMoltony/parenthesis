#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void make_new_number(Token **current_token, Token *tokens, int *num_tokens, int *nsb_i, char num_str_buffer[], char ch)
{
	*current_token = &tokens[*num_tokens];
	*num_tokens += 1;
	*(*current_token) = token_new(Token_Number, 0);
	num_str_buffer[0] = ch;
	*nsb_i = 0;
}

Token *lex(const char *expression, int *num_tokens_out)
{
	Token *tokens = malloc(strlen(expression) * sizeof(Token));
	if (!tokens) {
		fprintf(stderr, "failed to allocate tokens array\n");
		return 0;
	}
	int num_tokens = 0;
	char num_str_buffer[16] = {0};
	int nsb_i = 0;
	Token *current_token = NULL;

	for (int i = 0; expression[i] != 0; i++) {
		char ch = expression[i];
		if (isspace(ch)) {
			if (current_token && current_token->type == Token_Number) {
				printf("sp; finish number. nsb: '%s'\n", num_str_buffer);
				current_token->value = atoi(num_str_buffer);
				nsb_i = 0;
				current_token = NULL;
			}
			continue;
		}
		printf("non-space char: %c\n", ch);
		if (isdigit(ch)) {
			printf("is digit\n");
			if (!current_token) {
				printf("no current token; making new number\n");
				make_new_number(&current_token, tokens, &num_tokens, &nsb_i, num_str_buffer, ch);
				continue;
			} else {
				if (current_token->type == Token_Number) {
					printf("yes current token, is num; adding ch to buf\n");
					num_str_buffer[++nsb_i] = ch;
					continue;
				} else {
					printf("yes current token, not num; making new number\n");
					num_tokens++;
					make_new_number(&current_token, tokens, &num_tokens, &nsb_i, num_str_buffer, ch);
					continue;
				}
			}
		} else {
			printf("isn't digit\n");
			if (current_token && current_token->type == Token_Number) {
				printf("finish number. nsb: '%s'\n", num_str_buffer);
				current_token->value = atoi(num_str_buffer);
				nsb_i = 0;
				memset(num_str_buffer, 0, 16);
				current_token = NULL;
			}

			bool is_known_char = true;
			switch (ch) {
				case '+':
					printf("plus token\n");
					tokens[num_tokens++] = token_new(Token_Plus, 0);
					break;
				case '-':
					printf("minus token\n");
					tokens[num_tokens++] = token_new(Token_Minus, 0);
					break;
				case '*':
					printf("multiply token\n");
					tokens[num_tokens++] = token_new(Token_Multiply, 0);
					break;
				case '/':
					printf("divide token\n");
					tokens[num_tokens++] = token_new(Token_Divide, 0);
					break;
				case '(':
					printf("parenthesis open token\n");
					tokens[num_tokens++] = token_new(Token_ParenthesisOpen, 0);
					break;
				case ')':
					printf("parenthesis close token\n");
					tokens[num_tokens++] = token_new(Token_ParenthesisClose, 0);
					break;
				default:
					is_known_char = false;
					break;
			}

			if (is_known_char) {
				continue;
			}
		}


		printf("unknown char\n");
	}

	if (current_token && current_token->type == Token_Number) {
		printf("eof; finish number. nsb: '%s'\n", num_str_buffer);
		current_token->value = atoi(num_str_buffer);
	}

	printf("done lexing; found %d tokens\n", num_tokens);

	for (int i = 0; i < num_tokens; i++) {
		token_print(&tokens[i]);
	}

	*num_tokens_out = num_tokens;

	return tokens;
}
