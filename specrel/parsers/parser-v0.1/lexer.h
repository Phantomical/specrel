#pragma once

#include <string>

struct Lexer
{
	std::string StrVal;
	const char* PrevCursor;
	const char* Cursor;
	int CurrentToken;

	Lexer(FILE*);
	Lexer(const std::string&);

	int NextToken();

	size_t TokenSize() const;
	const char* TokenText() const;
};
