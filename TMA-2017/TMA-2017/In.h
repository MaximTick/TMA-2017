#pragma once
#include "stdafx.h"
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_MAX_STRING_CODE 1024
#define IN_CODE_ENDL '\n'
#define IN_CODE_SPACE ' '
#define IN_CODE_NULL '\0'

/*
SEP - ( ) * + - = , / { } ;
PR - ������
NS - ����� ������
F - �����������
T - �����������
I - ������������
L - '
*/

#define IN_CODE_TABLE {\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::NS,   IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
	IN::PR, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::L, IN::SEP, IN::SEP, IN::SEP,  IN::SEP, IN::SEP, IN::SEP, IN::T, IN::SEP,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::SEP, IN::T,   IN::SEP, IN::T, IN::T,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::SEP, IN::T,   IN::SEP, IN::T, IN::T,\
	\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F\
}  

namespace In
{
	struct StToken
	{
		static int tokensSize;  // ���������� ����
		int  line; // ������ � ������� ��������� �����
		char token[1024];
	};

	struct IN
	{
		enum { T = 1, F, I, NS, SEP, L, PR };
		int code[256] = IN_CODE_TABLE;
		int size = NULL;
		int lines = NULL;
		int ignor = NULL;
		unsigned char *text;
		StToken *tokens;
	};

	IN getin(std::ofstream *stream, wchar_t Infile[]);
	StToken* parsOfToken(StToken *tokens, unsigned char *text, int *code);
	void addToken(StToken *tokens, char* &buffer, int &posbuf, int line);
}