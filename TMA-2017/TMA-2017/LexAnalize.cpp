#include "stdafx.h"
#include "Graphs.h"
#include "FST.h"
#include "LexAnalize.h"
#include "Error.h"

static int funcnum = 0;

namespace Lexer
{
	Graph graph[N_GRAPHS] =
	{
		{ LEX_LITERAL, FST::FST(GRAPH_NUMBER_LITERAL) },
		{ LEX_SEPARATORS, FST::FST(GRAPH_SEPARATORS) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_FORWARD_SLASH) },
		//{ LEX_CREATE, FST::FST(GRAPH_CREATE) },
		{LEX_DECLARE, FST::FST(GRAPH_DECLARE)},
		{ LEX_KOREN, FST::FST(GRAPH_KOREN) },
		{ LEX_POW, FST::FST(GRAPH_POW) },
		{ 'a',  FST::FST(GRAPH_FACT) },
		{ LEX_LITERAL, FST::FST(GRAPH_WORD_LITERAL) },
		{ LEX_START, FST::FST(GRAPH_START) },
		{ LEX_ID_TYPE, FST::FST(GRAPH_NUMBER) },
		{ LEX_ID_TYPE, FST::FST(GRAPH_WORD) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_OUT, FST::FST(GRAPH_OUT) },
		{ LEX_LIBRARY, FST::FST(GRAPH_LIBRARY) },
		{ LEX_END, FST::FST(GRAPH_END) },
		{ LEX_ID, FST::FST(GRAPH_ID) }
	};

	LEX Fill_LTIT(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm)
	{
		LEX Tables;
		Tables.Lextable = LT::Create(LT_MAXSIZE);
		Tables.IDtable = IT::Create(TI_MAXSIZE);

		int rez;
		bool isParam = false;
		int funcBody = NULL;
		bool standartlib = false;
		char tempTokenFunction[ID_MAXSIZE] = "";
		char tempToken[ID_MAXSIZE] = "";
		char bufferr[10] = "-";
		int maincount = 0;
		IT::IDDATATYPE idType;

		for (int i = 0; i < In::StToken::tokensSize; i++)
			for (int j = 0; j < N_GRAPHS; j++)
			{
				FST::FST fstex(InStruct.tokens[i].token, graph[j].graph);


				if (FST::execute(fstex))
				{
					switch (graph[j].lexema)
					{

					case LEX_START:
					{
						maincount++;
						if (maincount > 1)
						{
							throw ERROR_THROW_IN(10, Tables.Lextable.table[i - 2].sn, NULL);
						}
						funcBody++;
						strncpy_s(tempTokenFunction, "", 1);
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}

					case LEX_LIBRARY:
					{
						standartlib = true;
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
						
					}

					case LEX_FUNCTION:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}

					case LEX_END:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}

					case LEX_ID:
					{
						strncpy_s(tempToken, InStruct.tokens[i].token, ID_MAXSIZE - 1);
						if (Tables.Lextable.table[i - 1].lexema != LEX_FUNCTION)
							strcat_s(InStruct.tokens[i].token, tempTokenFunction);

						if (Tables.Lextable.table[i - 2].lexema == LEX_DECLARE && IT::IsId(Tables.IDtable, InStruct.tokens[i].token) != -1)
						{

							Log::writeError(log.stream, Error::GetError(7, InStruct.tokens[i].line, NULL));
							Tables.next = false;

						}
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_SEPARATOR || Tables.Lextable.table[i - 1].lexema == LEX_LEFTHESIS || Tables.Lextable.table[i - 1].lexema == LEX_COMMA || Tables.Lextable.table[i - 1].lexema == LEX_RETURN)
							{
								Log::writeError(log.stream, Error::GetError(8, InStruct.tokens[i].line, NULL));
								Tables.next = false;
								break;
							}

							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION)
							{
								strncpy_s(tempTokenFunction, tempToken, ID_MAXSIZE - 1);
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
								LT::Add(Tables.Lextable, entrylt);

								IT::Entry entryit(tempTokenFunction, i, IT::INT, IT::F);
								IT::Add(Tables.IDtable, entryit);
								isParam = true;
								break;

							}

							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE)
							{
								if (isParam == false)
								{
									LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
									LT::Add(Tables.Lextable, entrylt);

									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::V);
									IT::Add(Tables.IDtable, entryit);
								}
								else if (isParam == true)
								{

									LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
									LT::Add(Tables.Lextable, entrylt);

									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::P);
									IT::Add(Tables.IDtable, entryit);
									if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTTHESIS)
										isParam = false;
								}

								break;
							}
						}
						else
						{
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
						break;
					}
					case LEX_LITERAL:
					{
						switch (Tables.Lextable.table[i - 1].lexema)
						{

						case LEX_EQUAL:
						{
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
							LT::Add(Tables.Lextable, entrylt);

							if (IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token) != -1)
								if ((Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::V ||
									Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::P))
								{

									IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token), InStruct.tokens[i].token);

								}
							break;
						}

						case LEX_MINUS:
						{

							if (Tables.Lextable.table[i - 2].lexema == LEX_EQUAL)
							{
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
								LT::Add(Tables.Lextable, entrylt);
								strcat_s(bufferr, InStruct.tokens[i].token);
								IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 3].token), bufferr);
								strncpy_s(bufferr, "", 1);
							}

							else
							{
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
								LT::Add(Tables.Lextable, entrylt);
								IT::Entry entryit("ltrl", i, idType, IT::L);
								IT::Add(Tables.IDtable, entryit);
								IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token);
							}
							break;
						}


						case LEX_PLUS:
						case LEX_STAR:
						case LEX_DIRSLASH:
						{
							if (InStruct.tokens[i].token[0]=='0')
								Log::writeError(log.stream, Error::GetError(29, InStruct.tokens[i].line, NULL));
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
							LT::Add(Tables.Lextable, entrylt);
							IT::Entry entryit("ltrl", i, idType, IT::L);
							IT::Add(Tables.IDtable, entryit);
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token);
							break;
						}

						case LEX_LEFTHESIS:
						case LEX_COMMA:
						case LEX_KOREN:
						case LEX_POW:
						case LEX_OUT:
						case LEX_RETURN:
						{
							IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L);
							IT::Add(Tables.IDtable, entryit);
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token);
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
						default: break;
						}
						break;
					}

					case LEX_SEPARATORS:
					{
						LT::Entry entrylt(InStruct.tokens[i].token[0], InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_ID_TYPE:
						idType = graph[j].graph.type;

					default:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					}
					break;
				}
			}
		return Tables;
	}
}