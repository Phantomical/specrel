/* Generated by re2c 0.16 on Tue May 17 21:45:14 2016 */
#include <string>
#include <cassert>
#include "lexer.h"
#include "parser.h"

#define YYCTYPE char

Lexer::Lexer(const std::string& str) :
	StrVal(str),
	PrevCursor(StrVal.data()),
	Cursor(StrVal.data()),
	CurrentToken(-1)
{

}
Lexer::Lexer(FILE* f) :
	CurrentToken(-1)
{
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	rewind(f);
	
	char* string = new char[fsize + 1];
	fread(string, fsize, 1, f);
	string[fsize] = '\0';

	StrVal = string;
	delete[] string;
	PrevCursor = StrVal.data();
	Cursor = StrVal.data();
}

size_t Lexer::TokenSize() const
{
	return (size_t)(Cursor - PrevCursor);
}
const char* Lexer::TokenText() const
{
	return PrevCursor;
}

int Lexer::NextToken()
{
	const YYCTYPE* YYMARKER;
	PrevCursor = Cursor;
	CurrentToken = -1;

start:
	{
#define YYMAXFILL 3

		
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	yych = *Cursor;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case '\n':
	case '\r':
	case ' ':	goto yy6;
	case '"':	goto yy8;
	case '+':
	case '-':	goto yy9;
	case ',':	goto yy10;
	case '/':	goto yy12;
	case '0':	goto yy13;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy15;
	case ':':	goto yy17;
	case ';':	goto yy19;
	case '<':	goto yy21;
	case '>':	goto yy23;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy25;
	case '{':	goto yy28;
	case '}':	goto yy30;
	default:	goto yy4;
	}
yy2:
	++Cursor;
	{ CurrentToken = 0;                goto end; }
yy4:
	++Cursor;
yy5:
	{ CurrentToken = 0xFF;             goto end; }
yy6:
	++Cursor;
	{ PrevCursor = Cursor; goto start; }
yy8:
	yyaccept = 0;
	yych = *(YYMARKER = ++Cursor);
	goto yy33;
yy9:
	yych = *++Cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy36;
	default:	goto yy5;
	}
yy10:
	++Cursor;
	{ CurrentToken = TOKEN_COMMA;      goto end; }
yy12:
	yych = *++Cursor;
	switch (yych) {
	case '/':	goto yy38;
	default:	goto yy5;
	}
yy13:
	yyaccept = 1;
	yych = *(YYMARKER = ++Cursor);
	switch (yych) {
	case 'X':
	case 'x':	goto yy43;
	default:	goto yy16;
	}
yy14:
	{ CurrentToken = TOKEN_NUMBER;     goto end; }
yy15:
	yyaccept = 1;
	YYMARKER = ++Cursor;
	yych = *Cursor;
yy16:
	switch (yych) {
	case '.':	goto yy41;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy15;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy25;
	default:	goto yy14;
	}
yy17:
	++Cursor;
	{ CurrentToken = TOKEN_COLON;      goto end; }
yy19:
	++Cursor;
	{ CurrentToken = TOKEN_SEMICOLON;  goto end; }
yy21:
	++Cursor;
	{ CurrentToken = TOKEN_LESSER;     goto end; }
yy23:
	++Cursor;
	{ CurrentToken = TOKEN_GREATER;    goto end; }
yy25:
	++Cursor;
	yych = *Cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy25;
	default:	goto yy27;
	}
yy27:
	{ CurrentToken = TOKEN_IDENTIFIER; goto end; }
yy28:
	++Cursor;
	{ CurrentToken = TOKEN_LBRACE;     goto end; }
yy30:
	++Cursor;
	{ CurrentToken = TOKEN_RBRACE;     goto end; }
yy32:
	++Cursor;
	yych = *Cursor;
yy33:
	switch (yych) {
	case '"':	goto yy34;
	default:	goto yy32;
	}
yy34:
	++Cursor;
	{ CurrentToken = TOKEN_STRING;     goto end; }
yy36:
	yyaccept = 1;
	YYMARKER = ++Cursor;
	yych = *Cursor;
	switch (yych) {
	case '.':	goto yy41;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy36;
	default:	goto yy14;
	}
yy38:
	++Cursor;
	yych = *Cursor;
	switch (yych) {
	case '\n':	goto yy40;
	default:	goto yy38;
	}
yy40:
	{ PrevCursor = Cursor; goto start; }
yy41:
	yych = *++Cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy44;
	default:	goto yy42;
	}
yy42:
	Cursor = YYMARKER;
	if (yyaccept == 0) {
		goto yy5;
	} else {
		goto yy14;
	}
yy43:
	yych = *++Cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy47;
	default:	goto yy27;
	}
yy44:
	++Cursor;
	yych = *Cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy44;
	default:	goto yy14;
	}
yy46:
	++Cursor;
	yych = *Cursor;
yy47:
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy46;
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy25;
	default:	goto yy48;
	}
yy48:
	{ CurrentToken = TOKEN_HEXVAL;     goto end; }
}

	}

end:
	return CurrentToken;
}
