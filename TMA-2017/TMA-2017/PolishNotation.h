#pragma once
#include "stdafx.h"
#include "LexAnalize.h"
#include "FST.h"

struct PN
{
	LT::Entry result[LT_MAXSIZE]; // ’ранит преобразованное выражение в польской нотации
	int size = 0;
	enum { LH = '(', RH = ')', PLUS = '+', MINUS = '-', MULT = '*', DEV = '/', EQUAL = '=' };

	int prior(char operation); // ѕриоритет операции
	int searchExpression(int number, Lexer::LEX *tables); // ѕоиск начала выражени€ в таблице лексем
	bool CreatePolishNotation(Lexer::LEX *tables);
};
