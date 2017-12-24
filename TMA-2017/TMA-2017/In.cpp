#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include "Log.h"
#define MAX_STR_LTR 250

int In::StToken::tokensSize = NULL;

namespace In
{
	IN getin(std::ofstream *stream, wchar_t Infile[])
	{
		std::ifstream txtfile(Infile);

		if (!txtfile.is_open())
			throw ERROR_THROW(4);

		IN StrIn;
		StrIn.text = new unsigned char[IN_MAX_LEN_TEXT];
		bool literalFlag = false;
		unsigned char readSymbol = IN_CODE_NULL;
		int counter = 0;
	reload:
		while ((readSymbol = txtfile.get()) && (!txtfile.eof()))
		{

			if (StrIn.code[readSymbol] == IN::L)
			{
				StrIn.text[StrIn.size++] = readSymbol;
				char a = readSymbol;
				readSymbol = txtfile.get();

				while (StrIn.code[readSymbol] != IN::L)
				{

					if (StrIn.code[readSymbol] == IN::F)
					{
						Log::writeError(stream, Error::GetError(9, StrIn.lines, StrIn.size));
					}
					counter++;
					if (StrIn.code[readSymbol] == IN::SEP && StrIn.text[StrIn.size - 1] != IN::L)
					{
						Log::writeError(stream, Error::GetError(23, StrIn.lines, NULL));

						StrIn.text[StrIn.size++] = a;
						StrIn.text[StrIn.size++] = readSymbol;
						readSymbol = txtfile.get();

						goto reload;
						break;

					}
					if (counter >= MAX_STR_LTR)
					{
						throw ERROR_THROW(24);
					}

					StrIn.text[StrIn.size++] = readSymbol;
					readSymbol = txtfile.get();

				}
				StrIn.text[StrIn.size++] = readSymbol;
				continue;
			}

			switch (StrIn.code[readSymbol])
			{
			case IN::NS:
			{
				StrIn.text[StrIn.size++] = readSymbol;
				StrIn.lines++;
				break;
			}
			case IN::PR:
			{
				if (StrIn.text[StrIn.size - 1] == IN_CODE_SPACE)
					StrIn.ignor++;
				else
					StrIn.text[StrIn.size++] = readSymbol;
				break;
			}
			case IN::SEP:
			{
				if (StrIn.text[StrIn.size - 1] == IN_CODE_SPACE)
					StrIn.text[StrIn.size - 1] = readSymbol;
				else
					StrIn.text[StrIn.size++] = readSymbol;
				break;
			}
			case IN::F:
			{
				Log::writeError(stream, Error::GetError(9, StrIn.lines, StrIn.size));
				break;
			}
			case IN::I:
			{
				StrIn.ignor++;
				break;
			}
			case IN::T:
			{
				if (StrIn.code[StrIn.text[StrIn.size - 2]] == IN::SEP && StrIn.code[StrIn.text[StrIn.size - 1]] == IN::PR)
					StrIn.text[StrIn.size - 1] = readSymbol;
				else
					StrIn.text[StrIn.size++] = readSymbol;
				break;
			}
			}
		}


		StrIn.text[StrIn.size] = IN_CODE_NULL;

		return StrIn;
	}



	void addToken(StToken *tokens, char* &buf, int &posbuf, int line)
	{
		buf[posbuf++] = IN_CODE_NULL;
		strcpy_s((tokens[StToken::tokensSize].token), posbuf, buf);
		tokens[StToken::tokensSize].line = line;
		StToken::tokensSize++;
		buf[0] = IN_CODE_NULL;
		posbuf = NULL;
	}

	StToken* parsOfToken(StToken *tokens, unsigned char *text, int *code)
	{
		tokens = new StToken[IN_MAX_LEN_TEXT];
		char *buf = new char[IN_MAX_STRING_CODE];
		int posBuf = NULL;
		bool literalFlag = false;
		int line = NULL;

		for (int i = NULL; text[i] != IN_CODE_NULL; i++)
		{
			if (code[text[i]] == IN::L)
			{
				if (buf[NULL] != IN_CODE_NULL)
					addToken(tokens, buf, posBuf, line);

				buf[posBuf++] = text[i++];

				while (code[text[i]] != IN::L)
					buf[posBuf++] = text[i++];

				buf[posBuf++] = text[i];
				addToken(tokens, buf, posBuf, line);
				continue;
			}

			switch (code[text[i]])
			{
			case IN::NS:
				line++;
			case IN::PR:
			{
				if (buf[NULL] != IN_CODE_NULL)
					addToken(tokens, buf, posBuf, line);
				break;
			}
			case IN::SEP:
			{
				if (buf[NULL] != IN_CODE_NULL)
					addToken(tokens, buf, posBuf, line);

				buf[posBuf++] = text[i];
				addToken(tokens, buf, posBuf, line);
				break;
			}
			default:
			{
				buf[posBuf++] = text[i];
				break;
			}
			}
		}

		return tokens;
	}
}
