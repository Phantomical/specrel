CD /d %~pd0
..\..\dependencies\re2c lexer.rec -o lexer.cpp -i
..\..\dependencies\lemon parser.y -q -m
..\..\dependencies\makeheaders parser.c