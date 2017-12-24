#include "stdafx.h"
#include "Generation.h"

ofstream brow("E://Generation.html");
void Up()
{
	brow << "<html>" << endl;
	brow << "<head>" << endl;
	brow << "<style>" << endl;
	brow << "#b {font-family:" << '"' << "Consolas" << '"' << ";font-size: 16px;height: 565px;margin: 0;padding: 5px;}" << endl;
	brow << "#a {background-color: white;color: black;font-family:" << '"' << "Consolas" << '"' << ";font-size: 12px;border: 1px solid black;padding: 1px 2px 1px 10px;margin: 0;}" << endl;
	brow << "</style>" << endl;
	brow << "</head>" << endl;
	brow << "<body>" << endl;
	brow << "<div id=" << '"' << "a" << '"' << "><p>Результат выполнения </p>	</div> " << endl;
	brow << "<div id=" << '"' << "b" << '"' << ">" << endl;
	brow << "<script src=" << '"' << "E://math.js" << '"' << "></script>" << endl;
	brow << "<script>" << endl;
}


void Down()
{
	brow << "</script>" << endl;
	brow << "</div>" << endl;
	brow << "</body>" << endl;
	brow << "</html>" << endl;
	brow.close();
}


void Generation(LT::LexTable &Lextable, In::StToken *tokens, IT::IdTable & idtable)
{
	Up();
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_LEFTBRACE:
		{
			brow << "{" << endl;
			break;
		}
		case  LEX_DECLARE:
		{
			brow << "var";
			break;
		}
		case LEX_ID:
		{
			int y;
			y = Lextable.table[i].idxTI;
			if (Lextable.table[i - 2].lexema == LEX_OUT)
			{
				if (idtable.table[y].iddatatype == IT::INT)
					brow << "Math.floor(" << idtable.table[y].id << ")";
				else
					brow << idtable.table[y].id;
			}
			else if (idtable.table[y].iddatatype == IT::STR || IT::INT && Lextable.table[i - 2].lexema != LEX_OUT)
			{
				brow << idtable.table[y].id;
			}

			break;
		}
		case LEX_SEPARATOR:
		{
			brow << ";" << endl;
			break;
		}
		case  LEX_EQUAL:
		{
			brow << "=";
			break;
		}
		case LEX_LITERAL:
		{
			int toInt;
			toInt = atoi(tokens[i].token);
			if (toInt > INT_MAXSIZE)
			{
				toInt = INT_MAXSIZE;
				brow << toInt;
				break;
			}
			if (toInt < INT_MINUS_MAXSIZE)
			{
				toInt = INT_MINUS_MAXSIZE;
				brow << toInt;
				break;
			}
			brow << tokens[i].token;
			break;
		}
		case LEX_ID_TYPE:
		case SPACE:
		{
			brow << " ";
			break;
		}
		case LEX_LIBRARY:
		{
			brow << "document.write('<br />');" << endl;
			brow << "document.write('Подключена математическая библиотека')";
			break;
		}
		case LEX_OUT:
		{
			brow << "document.write('<br />');" << endl;
			brow << "document.write";
			break;
		}
		case LEX_LEFTHESIS:
		{
			brow << "(";
			break;
		}
		case LEX_RIGHTTHESIS:
		{
			brow << ")";
			break;
		}
		case LEX_END:
		{
			brow << "document.write('<br />');" << endl;
			brow << "document.write('Программа завершена.')";
			break;
		}
		case LEX_BRACELET:
		{
			brow << "}" << endl;
			break;
		}
		case tochka:
		{
			brow << endl;
			break;
		}
		case LEX_PLUS:
		{
			brow << "+";
			break;
		}
		case LEX_STAR:
		{
			brow << "*";
			break;
		}
		case LEX_MINUS:
		{
			brow << "-";
			break;
		}
		case LEX_DIRSLASH:
		{
			brow << "/";
			break;
		}
		case LEX_FUNCTION:
		{
			brow << "function ";
			break;
		}
		case LEX_COMMA:
		{
			brow << ",";
			break;
		}
		case LEX_RETURN:
		{
			brow << "return ";
			break;
		}

		case LEX_KOREN:
		{
			brow << "sqrt";
			break;
		}
		case LEX_POW:
		{
			brow << "pow";

			break;
		}
		case LEX_FACT:
		{
			brow << "fact";

			break;
		}
		}
	}
	Down();
}