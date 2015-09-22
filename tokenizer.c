/*
 * Rony Vargas
 * 155005725
 * CS214 Systems Programing
 * Spring 2014
 *
 * Assignment 1
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

/*
 * tokenState is of type enum which will be used to differentiate the states during token transitions
 */

typedef enum {
	state0,
	state1, state2, state3, state4, state5,state6, state7, state8, state9, state10, state11, state12, state13, state14, state15,
	state16, state17, state18, state19, state20,state21, state22, state23, state24, state25, state26, state27, state28, state29, state30,
	state31, state32, state33, state34, state35,state36, state37, state38, state39, state40, state41, state42, state43, state44, state45,
	state46, state47, state48, state49, state50,state51, state52, state53, state54, state55, state56, state57, state58, state59, state60,
	state61, state62, state63, state64, state65,state66, state67,

	undefined,
	malformed,
	malformed_integer, malformed_integer2, malformed_integer3,
	malformed_float, malformed_float2,
	malformed_stop,

	word,
	integer,
	integer_decimal,
	integer_octal,
	integer_hex,
	floating_point,

	operator,
	apostrophe, bit_comp, not_equal, negate, at_sign, octothorpe, dollar, assign_remain, modulus, assign_bitxor, bit_xor, logical_and,
	assign_bitand, bit_and, assign_prod, multiply, question, left_para, right_para, decrement, assign_dif, comp_sel, subtract, dash,
	equals_to, assign, increment, assign_sum, add, single_quote, colon, sem_colon, dub_quote, assign_left, shift_left, less_than,
	less_equal, assign_right, shift_right, greater_than, greater_equal, comma, ellipsis, full_stop, assign_quotient, divide, logical_or, assign_bitor,
	bit_or, left_brace, right_brace, left_brack, right_brack, escape

} tokenState;

/*
 * TokenizerT is a struct that contains a tokenState, a char *, and two integers.
 * TokenState may represent the current state of token creation during TkGetNextToken or
 * the state of the last token produced when accessed directly. tokenStream is a pointer to the
 * string that will be tokenized. The remaining integers are variables that will be used during token
 * creation that represent the start and end of a new token.
 *
 */

typedef struct TokenizerT_ TokenizerT;

struct TokenizerT_ {
	tokenState type;
	char *tokenStream;
	int j;
	int k;
};
/*
 * printState will take in a tokenState as an argument and print out the relative token type
 * on screen.
 */

void printState(tokenState token_state){
	switch (token_state){
		case word:
			printf("word "); break;
		case integer:
			printf("integer "); break;
		case integer_decimal:
			printf("decimal integer "); break;
		case integer_octal:
			printf("octal integer "); break;
		case integer_hex:
			printf("hexadecimal integer "); break;
		case floating_point:
			printf("float "); break;
		case apostrophe:
			printf("backtick "); break;
		case bit_comp:
			printf("bit compare "); break;
		case not_equal:
			printf("not equal "); break;
		case negate:
			printf("negate "); break;
		case at_sign:
			printf("at sign "); break;
		case octothorpe:
			printf("octothorpe "); break;
		case dollar:
			printf("dollar sign "); break;
		case assign_remain:
			printf("assign remainder "); break;
		case modulus:
			printf("modulus "); break;
		case assign_bitxor:
			printf("assign bit XOR "); break;
		case bit_xor:
			printf("bit XOR "); break;
		case logical_and:
			printf("logical AND "); break;
		case assign_bitand:
			printf("assign bit AND "); break;
		case bit_and:
			printf("bit AND "); break;
		case assign_prod:
			printf("assign product "); break;
		case multiply:
			printf("multiply/dereference "); break;
		case question:
			printf("question "); break;
		case left_para:
			printf("left paranthesis "); break;
		case right_para:
			printf("right paranthesis "); break;
		case decrement:
			printf("decrement "); break;
		case assign_dif:
			printf("assign difference "); break;
		case comp_sel:
			printf("component selector "); break;
		case subtract:
			printf("subtract "); break;
		case dash:
			printf("dash "); break;
		case equals_to:
			printf("equals to "); break;
		case assign:
			printf("assign "); break;
		case increment:
			printf("increment "); break;
		case assign_sum:
			printf("assign sum "); break;
		case add:
			printf("add "); break;
		case single_quote:
			printf("single quote "); break;
		case colon:
			printf("colon "); break;
		case sem_colon:
			printf("semi colon "); break;
		case dub_quote:
			printf("double quote "); break;
		case assign_left:
			printf("assign left-shift "); break;
		case shift_left:
			printf("shift left "); break;
		case less_equal:
			printf("less equal "); break;
		case less_than:
			printf("less than "); break;
		case assign_right:
			printf("assign right-shift "); break;
		case shift_right:
			printf("shift right "); break;
		case greater_than:
			printf("great than "); break;
		case greater_equal:
			printf("greater or equal "); break;
		case comma:
			printf("comma "); break;
		case ellipsis:
			printf("ellipsis "); break;
		case full_stop:
			printf("full stop "); break;
		case assign_quotient:
			printf("assign quotient "); break;
		case divide:
			printf("divide "); break;
		case logical_or:
			printf("logical or "); break;
		case assign_bitor:
			printf("assign bit OR "); break;
		case bit_or:
			printf("bit OR "); break;
		case left_brace:
			printf("left brace "); break;
		case right_brace:
			printf("right brace "); break;
		case left_brack:
			printf("left bracket "); break;
		case right_brack:
			printf("right bracket "); break;
		case escape:
			printf("error "); break;
		default:
			break;
	}
}

/*
 * nextState will take a a character and a tokenState pointer as arguments. The function
 * will use the character and the current state to determine the token's next state.
 */

void nextState(char c, tokenState *current){
	switch (*current){
		case state0:
			if (c == '0'){ *current = state1; break;}
			else if ((c >= '1') && (c <= '9')){ *current = state2; break;}
			else if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))){ *current = state3; break;}
			else if (c == '`'){ *current = state13; break;}
			else if (c == '~'){ *current = state14; break;}
			else if (c == '!'){ *current = state15; break;}
			else if (c == '@'){ *current = state17; break;}
			else if (c == '#'){ *current = state18; break;}
			else if (c == '$'){ *current = state19; break;}
			else if (c == '%'){ *current = state20; break;}
			else if (c == '^'){ *current = state22; break;}
			else if (c == '&'){ *current = state24; break;}
			else if (c == '*'){ *current = state27; break;}
			else if (c == '?'){ *current = state29; break;}
			else if (c == '('){ *current = state30; break;}
			else if (c == ')'){ *current = state31; break;}
			else if (c == '-'){ *current = state32; break;}
			else if (c == '_'){ *current = state36; break;}
			else if (c == '='){ *current = state37; break;}
			else if (c == '+'){ *current = state39; break;}
			else if (c == '\''){ *current = state42; break;}
			else if (c == ':'){ *current = state43; break;}
			else if (c == ';'){ *current = state44; break;}
			else if (c == '"'){ *current = state45; break;}
			else if (c == '<'){ *current = state46; break;}
			else if (c == '>'){ *current = state50; break;}
			else if (c == ','){ *current = state54; break;}
			else if (c == '.'){ *current = state55; break;}
			else if (c == '/'){ *current = state58; break;}
			else if (c == '|'){ *current = state60; break;}
			else if (c == '['){ *current = state63; break;}
			else if (c == ']'){ *current = state64; break;}
			else if (c == '{'){ *current = state65; break;}
			else if (c == '}'){ *current = state66; break;}
			else if (isspace(c) && c != ' '){*current = state67; break;}
			else {*current = undefined; break;}
		case state1:
			if ((c >= '0') && (c <= '7')){ *current = state4; break;}
			else if ((c == 'X') || (c == 'x')){ *current = state5; break;}
			else if (c == '.'){ *current = state6; break;}
			else {*current = integer; break;}
		case state2:
			if ((c >= '0') && (c <= '9')){ *current = state2; break;}
			else if (c == '.'){ *current = state6; break;}
			else if ((c == 'E') || (c == 'e')){printf("{2-10} - %c ~", c); *current = state10; break;}
			else {*current = integer; break;}
		case state3:
			if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))){ *current = state3; break;}
			else {*current = word; break;}
		case state4:
			if ((c >= '0') && (c <= '7')){ *current = state4; break;}
			else {*current = integer_octal; break;}
		case state5:
			if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'))){ *current = state5; break;}
			else {*current = integer_hex; break;}
		case state6:
			if ((c >= '0') && (c <= '9')){ *current = state7; break;}
			else {*current = malformed_integer; break;}
		case state7:
			if ((c >= '0') && (c <= '9')){ *current = state7; break;}
			else if ((c == 'E') || (c == 'e')){ *current = state8; break;}
			else {*current = floating_point; break;}
		case state8:
			if ((c >= '0') && (c <= '9')){ *current = state12; break;}
			else if ((c == '+') || (c == '-')){ *current = state9; break;}
			else {*current = malformed_float; break;}
		case state9:
			if ((c >= '0') && (c <= '9')){ *current = state12; break;}
			else {*current = malformed_float2; break;}
		case state10:
			printf("state10 - %c ~", c);
			if ((c >= '0') && (c <= '9')){ *current = state12; break;}
			else if ((c == '+') || (c == '-')){ *current = state11; break;}
			else {*current = malformed_integer2; break;}
		case state11:
			if ((c >= '0') && (c <= '9')){ *current = state12; break;}
			else {*current = malformed_integer3; break;}
		case state12:
			if ((c >= '0') && (c <= '9')){ *current = state12; break;}
			else {*current = floating_point; break;}
		case state13:
			{*current = apostrophe; break;}
		case state14:
			{*current = bit_comp; break;}
		case state15:
			if (c == '='){ *current = state16; break;}
			else {*current = negate; break;}
		case state16:
			{*current = not_equal; break;}
		case state17:
			{*current = at_sign; break;}
		case state18:
			{*current = octothorpe; break;}
		case state19:
			{*current = dollar; break;}
		case state20:
			if (c == '='){ *current = state21; break;}
			else {*current = modulus; break;}
		case state21:
			{*current = assign_remain; break;}
		case state22:
			if (c == '=') { *current = state23; break;}
			else {*current = bit_xor; break;}
		case state23:
			{*current = assign_bitand; break;}
		case state24:
			if (c == '&'){ *current = state25; break;}
			else if (c == '='){ *current = state26; break;}
			else {*current = bit_and; break;}
		case state25:
			{*current = logical_and; break;}
		case state26:
			{*current = assign_bitand; break;}
		case state27:
			if (c == '='){ *current = state28; break;}
			else {*current = multiply; break;}
		case state28:
			{*current = assign_prod; break;}
		case state29:
			{*current = question; break;}
		case state30:
			{*current = left_para; break;}
		case state31:
			{*current = right_para; break;}
		case state32:
			if (c == '-'){ *current = state33; break;}
			else if (c == '='){ *current = state34; break;}
			else if (c == '>'){ *current = state35; break;}
			else {*current = subtract; break;}
		case state33:
			{*current = decrement; break;}
		case state34:
			{*current = assign_dif; break;}
		case state35:
			{*current = comp_sel; break;}
		case state36:
			{*current = dash; break;}
		case state37:
			if (c == '='){ *current = state38; break;}
			else {*current = assign; break;}
		case state38:
			{*current = equals_to; break;}
		case state39:
			if (c == '+'){ *current = state40; break;}
			else if (c == '='){ *current = state41; break;}
			else {*current = add; break;}
		case state40:
			{*current = increment; break;}
		case state41:
			{*current = assign_sum; break;}
		case state42:
			{*current = single_quote; break;}
		case state43:
			{*current = colon; break;}
		case state44:
			{*current = sem_colon; break;}
		case state45:
			{*current = dub_quote; break;}
		case state46:
			if (c == '<'){ *current = state47; break;}
			else if (c == '='){ *current = state49; break;}
			else {*current = less_than; break;}
		case state47:
			if (c == '='){ *current = state48; break;}
			else {*current = shift_left; break;}
		case state48:
			{*current = assign_left; break;}
		case state49:
			{*current = less_equal; break;}
		case state50:
			if (c == '>'){ *current = state51; break;}
			else if (c == '='){ *current = state53; break;}
			else {*current = greater_than; break;}
		case state51:
			if (c == '='){ *current = state12; break;}
			else {*current = shift_right; break;}
		case state52:
			{*current = assign_right; break;}
		case state53:
			{*current = greater_equal; break;}
		case state54:
			{*current = comma; break;}
		case state55:
			if (c == '.'){ *current = state56; break;}
			else {*current = full_stop; break;}
		case state56:
			if (c == '.'){ *current = state57; break;}
			else {*current = malformed_stop; break;}
		case state57:
			{*current = ellipsis; break;}
		case state58:
			if (c == '='){ *current = state59; break;}
			else {*current = divide; break;}
		case state59:
			{*current = assign_quotient; break;}
		case state60:
			if (c == '|'){ *current = state62; break;}
			else if (c == '='){ *current = state63; break;}
			else {*current = bit_or; break;}
		case state61:
			{*current = logical_or; break;}
		case state62:
			{*current = assign_bitor; break;}
		case state63:
			{*current = left_brace; break;}
		case state64:
			{*current = right_brace; break;}
		case state65:
			{*current = left_brack; break;}
		case state66:
			{*current = right_brack; break;}
		case state67:
			{*current = escape; break;}
		default:
			break;
	}
}

/*
 * isEscChar will be take in a single character that followed a \. If it is of a
 * character that composes an escape character then the full escape character will be
 * returned as a single character.
 */

unsigned char isEscChar(char c){
	switch (c){
	case 'n':
		return '\n';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	case 'b':
		return '\b';
	case 'r':
		return '\r';
	case 'f':
		return '\f';
	case 'a':
		return '\a';
	case '\\':
		return '\\';
	case '"':
		return '\"';
	case '0':
		return '\0';
	default:
		return 0;
	}
}

/*
 * printToken will be used to print a token string (given as a string). It will
 * check each character individually and if it is an escape character it will print the
 * hex value. All other characters will print normally.
 */

void printToken(const char *token){
	char c;
	int i;
	for (i = 0; i < strlen(token); i++){
		c = token[i];
		switch(c){
		case '\n':
		case '\t':
		case '\v':
		case '\b':
		case '\r':
		case '\f':
		case '\a':
		case '\\':
		case '"':
			printf("[0x%02x]", c);
			break;
		default:
			printf("%c", c);
			break;
		}
	}
	printf("\n");
}

/*
 * stringParser will remove unwanted characters from a token string.
 * Any \ characters that are not followed by an escape character will be removed.
 *
 * The string is parsed in place, "i" is an index to each character being checked.
 * "k" index the current position available if the "i" index is valid. A memmove is
 * done if i index is valid. a reallocation of memory is done if the string length is
 * now shorter due to removed characters.
 */

void stringParser(char* myString){
	int stringLength = strlen(myString);
	int i, k = 0;

	for (i = 0; i < stringLength; i++){
		if (myString[i] == '\\'){
			if (i+1 < stringLength){
				char c = isEscChar(myString[i+1]);
				if (c != 0){
					memcpy(myString+k,&c,sizeof(char));
					i++;
					k++;
				}
			}
		}
		else{
			memmove (myString+k, myString+i,sizeof(char));
			k++;
		}
	}
	myString[k] = '\0';
	if (k < stringLength)
		myString = (char *)realloc(myString, (sizeof(char)* (k+1) ) );
}

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 *
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *ts) {

	TokenizerT *tokenPointer;
	tokenPointer = (TokenizerT*)malloc(sizeof(TokenizerT));
	if (tokenPointer == NULL){
		fprintf(stderr, "Error: No memory available to create pointer");
	}
	tokenPointer->j = 0;
	tokenPointer->k = 0;

	char *tsCopy = (char*)malloc((strlen(ts)+1)*(sizeof(char)));
	if (tsCopy == NULL){
		fprintf(stderr, "Error: No memory available. Could not create string.");
	}
	strcpy (tsCopy, ts);
	stringParser(tsCopy);
	tokenPointer->tokenStream = tsCopy;
	return tokenPointer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
	free(tk->tokenStream);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

	tk->type = state0;
	char end = '\0';
	int length = strlen(tk->tokenStream);

	while ((tk->j < length+1) && (tk->type < word)){
		if (tk->j <= length){
			nextState(tk->tokenStream[tk->j], &tk->type);
			if ((tk->type >= undefined) && (tk->type < word)){
				switch(tk->type) {
				case malformed_integer:
					{tk->j--; tk->type = integer; break;}
				case malformed_integer2:
					{tk->j--; tk->type = integer; break;}
				case malformed_integer3:
					{tk->j-= 2; tk->type = integer; break;}
				case malformed_float:
					{tk->j--; tk->type = floating_point; break;}
				case malformed_float2:
					{tk->j-= 2; tk->type = floating_point; break;}
				case malformed_stop:
					{tk->j--; tk->type = full_stop; break;}
				case undefined:
					{tk->k = tk->j+1; tk->type = state0; break;}
				default: break;
				}
			}
		tk->j++;
		}
	}
	if (tk->type >= word){
		char *tempToken;
		tk->j--;
		tempToken = (char *)malloc(sizeof(char)*(tk->j-tk->k+1));
		if (tempToken == NULL){
			fprintf(stderr, "Error: No memory available for token string");
		}
		memcpy(tempToken, tk->tokenStream+tk->k, sizeof(char)*(tk->j-tk->k));
		memcpy(tempToken+tk->j-tk->k,&end,sizeof(char));
		tk->k = tk->j;
		return tempToken;
	}
	return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main (int argc, char **argv){
	if (argc == 2){
		TokenizerT *tokenPTR;
		tokenPTR = TKCreate(argv[1]);
		char *tokenString;
		while ((tokenString = TKGetNextToken(tokenPTR)) != NULL){
			printState(tokenPTR->type);
			printToken(tokenString);
			free(tokenString);
		}
		TKDestroy(tokenPTR);
		return 0;
	}
	else{
		fprintf(stderr, "Error: Incorrect number of arguments");
		printf("\n %i arguments given", argc);
		exit(1);
		return -1;
	}
}
