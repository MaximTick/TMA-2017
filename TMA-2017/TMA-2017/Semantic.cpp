#include "stdafx.h"
#include "Semantic.h"

bool  SemanticAnalyze(LT::LexTable &Lextable, In::IN &InStruct, IT::IdTable &idtable, Log::LOG &log)
{
	bool stlib = false;
	int mainfunc = 0;
	bool choise = true;
	int nn = -1;
	int j = -1;
	bool mathNUM = true;

	for (int i = 0; i < Lextable.size; i++)
	{

		if (Lextable.table[i].lexema == LEX_ID) {

			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1)
			{
				nn = IT::IsId(idtable, InStruct.tokens[i].token);
				Lextable.table[i].idxTI = nn;
			}
			else
			{
				Lextable.table[i].idxTI = ++nn;

			}

		}

	}

	for (int i = 0; i < Lextable.size; i++)
	{

		switch (Lextable.table[i].lexema)
		{
		case LEX_LIBRARY:
		{
			stlib = true;
			break;
		}


		case LEX_START:
		{
			mainfunc++;
			break;
		}
		/*case LEX_RETURN:
		{
			if (Lextable.table[i + 1].lexema == LEX_ID && IT::IsId(idtable, InStruct.tokens[i + 1].token) == -1)
			{
				int y = IT::IsId(idtable, InStruct.tokens[i+1].token);
				if (idtable.table[y].idtype == IT::F)
				{
					Log::writeError(log.stream, Error::GetError(29, Lextable.table[i].sn, NULL));
					break;
				}
			}
			break;
		}*/
		


		case LEX_EQUAL:
		{
			if (Lextable.table[i + 1].lexema == LEX_ID && Lextable.table[i + 2].lexema != LEX_LEFTHESIS && Lextable.table[i + 2].lexema != LEX_SEPARATOR)
			{
				int  p = 0;

				while (Lextable.table[i].lexema != LEX_SEPARATOR)
				{
					if (Lextable.table[i].lexema == LEX_ID)
					{
						p = Lextable.table[i].idxTI;
						if (idtable.table[p].iddatatype != IT::INT)
						{
							mathNUM = false;
							break;
						}
					}
					i++;
				}

				if (mathNUM == false)
				{
					Log::writeError(log.stream, Error::GetError(26, Lextable.table[i].sn, NULL));
					choise = false;
				}

			}

			break;
		}

		case LEX_ID:
		{
			if (Lextable.table[i-1].lexema == LEX_EQUAL && Lextable.table[i].lexema == LEX_ID && Lextable.table[i + 1].lexema == LEX_LEFTHESIS)
			{
			int size1 = 0;
			int size2 = 0;
			int k1[5];
			int k2[5];
			int u = i;
			int checkin;
			int checkobparm;

			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1)
			checkobparm = IT::IsId(idtable, InStruct.tokens[i].token);




			while (Lextable.table[u].lexema != LEX_RIGHTTHESIS)
			{
			int checkparms ;
			if (Lextable.table[u].lexema == LEX_ID || Lextable.table[u].lexema == LEX_LITERAL)
			{
			if (IT::IsId(idtable, InStruct.tokens[u].token) != -1)
			{
			checkparms = IT::IsId(idtable, InStruct.tokens[u].token);
			if (idtable.table[checkparms].iddatatype == IT::INT)
			k1[size1++] = 1;
			else
			k1[size1++] = 0;
			}

			}
			u++;
			}

			int gg = checkobparm ;

			while (Lextable.table[gg].lexema != LEX_RIGHTTHESIS)
			{
			int checkin ;
			if (Lextable.table[gg].lexema == LEX_ID || Lextable.table[gg].lexema == LEX_LITERAL)
			{
			if (IT::IsId(idtable, InStruct.tokens[gg].token) != -1)
			{
			checkin = IT::IsId(idtable, InStruct.tokens[gg].token);
			if (idtable.table[checkin].iddatatype == IT::INT)
			k2[size2++] = 1;
			else
			k2[size2++] = 0;
			}

			}
			gg++;
			}

			bool flags = true;

			for (int i = 0; i < size1; i++)

			{
			//cout << k1[i];
			//cout << k2[i];
			if (k1[i] == k2[i])
			flags = true;
			else
			{
			flags = false;
			Log::writeError(log.stream, Error::GetError(25, Lextable.table[u].sn, NULL));
			}
			}



			}

			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F)
			{

				int kol2 = 0;
				int a = idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idxfirstLE;

				while (Lextable.table[a].lexema != LEX_RIGHTTHESIS)
				{
					if (Lextable.table[a].lexema == LEX_COMMA)
						kol2++;
					a++;
				}


				int kol = 0;
				while (Lextable.table[i].lexema != LEX_RIGHTTHESIS)
				{
					if (Lextable.table[i].lexema == LEX_COMMA)
						kol++;
					i++;
				}


				if (kol != kol2)
				{
					Log::writeError(log.stream, Error::GetError(28, Lextable.table[i].sn, NULL));
					choise = false;
				}

				break;
			}




			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && (Lextable.table[i - 2].lexema == LEX_KOREN || Lextable.table[i - 2].lexema == LEX_POW))
			{
				int check;
				check = IT::IsId(idtable, InStruct.tokens[i].token);
				if (idtable.table[check].iddatatype == IT::STR && (Lextable.table[i - 2].lexema == LEX_KOREN || Lextable.table[i - 2].lexema == LEX_POW))
				{
					Log::writeError(log.stream, Error::GetError(13, Lextable.table[i].sn, NULL));
					choise = false;
					break;
				}
				break;
			}

			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F && Lextable.table[i + 1].lexema == LEX_EQUAL)
			{
				Log::writeError(log.stream, Error::GetError(12, Lextable.table[i].sn, NULL));
				choise = false;
			}

			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].iddatatype == IT::INT && InStruct.tokens[i + 2].token[0] == char(39))
			{
				Log::writeError(log.stream, Error::GetError(11, Lextable.table[i].sn, NULL));
				choise = false;
			}

			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].iddatatype == IT::STR && Lextable.table[i - 1].lexema == LEX_SEPARATOR && InStruct.tokens[i + 2].token[0] != char(39))
			{
				Log::writeError(log.stream, Error::GetError(11, Lextable.table[i].sn, NULL));
				choise = false;
			}

			if (IT::IsId(idtable, InStruct.tokens[i].token) == -1 && Lextable.table[i - 1].lexema != LEX_ID_TYPE && Lextable.table[i - 1].lexema != LEX_FUNCTION)
			{
				Log::writeError(log.stream, Error::GetError(8, Lextable.table[i].sn, NULL));
				choise = false;
			}

			if ((IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && Lextable.table[i + 2].lexema == LEX_ID &&Lextable.table[i + 3].lexema == LEX_SEPARATOR))
			{
				Log::writeError(log.stream, Error::GetError(22, Lextable.table[i].sn, NULL));
				choise = false;
			}

			break;
		}

		case LEX_KOREN:
		case LEX_POW:
		case LEX_FACT:
		{
			/*if (idtable.table[Lextable.table[i + 2].idxTI].iddatatype != 1)
			{
				Log::writeError(log.stream, Error::GetError(19, Lextable.table[i].sn, NULL));
				choise = false;
			}*/

			if (stlib == false)
			{
				Log::writeError(log.stream, Error::GetError(21, Lextable.table[i].sn, NULL));
				choise = false;
			}
			break;
		}
		}
	}

	if (mainfunc == 0)
	{
		Log::writeError(log.stream, Error::GetError(21, NULL, NULL));
		choise = false;
	}
	else if (mainfunc > 1)
	{
		Log::writeError(log.stream, Error::GetError(10, NULL, NULL));
		choise = false;
	}

	return choise;
}