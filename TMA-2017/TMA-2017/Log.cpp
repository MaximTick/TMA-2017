#include "stdafx.h"
#include "Log.h"
#include "Error.h"
#include "In.h"

namespace Log
{

	LOG getstream(wchar_t  logfile[])
	{
		LOG stream;
		stream.stream = new std::ofstream;
		(*stream.stream).open(logfile);
		if (!(*stream.stream).is_open())
			throw ERROR_THROW(5);
		wcscpy_s(stream.logfile, logfile);
		return stream;
	}

	void writeLog(LOG &log) {
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%d.%m.%Y %H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		*log.stream << "\n----- �������� ------ ����: " << buffer << " -------- \n\n";
	}

	void writeParm(LOG &log, Parm::PARM &parm)
	{
		char inTxt[PARM_MAX_SIZE],
			logTxt[PARM_MAX_SIZE];
		wcstombs(inTxt, parm.in, wcslen(parm.in) + 1);
		wcstombs(logTxt, parm.log, wcslen(parm.log) + 1);
		*log.stream << "\n----- ��������� --------";
		*log.stream << "\n-in: " << inTxt
			<< "\n-log: " << logTxt
			<< "\n\n";
	}

	void writeIn(LOG &log, In::IN &in) {
		*log.stream << "\n---- �������� ������ ------";
		*log.stream << "\n���������� ��������: " << std::setw(3) << in.size
			<< "\n���������������: " << std::setw(3) << in.ignor
			<< "\n���������� �����: " << std::setw(3) << in.lines << "\n\n";
	}

	void writeError(std::ofstream *stream, Error::ERROR &e)

	{
		if (stream == NULL)  // ������ ���������
		{
			if (e.position.cells == -1 || e.position.line == -1)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message << std::endl;
			else if (e.position.cells == NULL)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line << std::endl;
			else
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line
				<< " ������� � ������: " << e.position.cells << std::endl;
			system("pause");
		}
		else
		{
			if (e.position.cells == -1 || e.position.line == -1)
				*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message;
			else if (e.position.cells == NULL)
				*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line;
			else
				*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line
				<< " ������� � ������: " << e.position.cells;
		}

		//if (stream == NULL)  // ������ ���������
		//{
		//	if (e.position.cells == -1 || e.position.line == -1)
		//		std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message << std::endl;
		//	system("pause");
		//}
		//else
		//{
		//	if (e.position.line == 0) *stream << "������  � " << e.id << " : " << e.message << endl;
		//	else *stream << "������ � " << e.id << " : " << e.message << "   ������  �" << e.position.line << endl;
		//}
	}

	void writeLexTable(LOG &log, LT::LexTable &Lextable)
	{
		*log.stream << "\n---------------������� ������--------------------------------\n" <<
			std::setw(8) << std::left << "������� " <<
			std::setw(9) << std::left << "� ������ " <<
			std::setw(15) << std::left << "� ����. ������ " <<
			std::setw(15) << std::left << "� ����. �����. " << std::endl;

		for (int i = 0; i < Lextable.size; i++)
		{
			*log.stream << std::setw(8) << std::left << Lextable.table[i].lexema <<
				std::setw(9) << std::left << Lextable.table[i].sn;
			*log.stream << std::setw(15) << std::left << i;
			*log.stream << std::setw(15) << std::left;
			if (Lextable.table[i].idxTI != -1)
				*log.stream << Lextable.table[i].idxTI;
			else
				*log.stream << '-';
			*log.stream << std::setw(8) << std::left;
			*log.stream << std::endl;
		}
		*log.stream << "\n\n";
	}

	void writeIDtable(LOG &log, IT::IdTable &IDtable)
	{
		*log.stream << "\n---------------������� ���������������-------------------------------\n" <<
			std::setw(10) << std::left << "��� ����� " <<
			std::setw(10) << std::left << "��� ����� " <<
			std::setw(11) << std::left << "��� �����. " <<
			std::setw(15) << std::left << "� ����. ����. " <<
			std::setw(8) << std::left << "��������" <<
			std::endl;

		for (int i = 0; i < IDtable.size; i++)
		{
			*log.stream << std::setw(10) << std::left <<
				std::setw(10) << std::left << IDtable.table[i].id <<
				std::setw(10) << std::left;

			if (IDtable.table[i].iddatatype == IT::INT)
				*log.stream << NUMBER;
			else
				*log.stream << WORD;

			*log.stream << std::setw(11) << std::left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:
				*log.stream << "Function"; break;
			case IT::V:
				*log.stream << "Variable"; break;
			case IT::P:
				*log.stream << "Parameter"; break;
			case IT::L:
				*log.stream << "Literal"; break;
			case IT::S:
				*log.stream << "Standart"; break;
			}
			*log.stream << std::setw(15) << std::left << IDtable.table[i].idxfirstLE;
			if (IDtable.table[i].iddatatype == IT::INT)
				*log.stream << IDtable.table[i].value.vINT;
			else
			{
				if (IDtable.table[i].value.vSTR.len != 0)
					*log.stream << IDtable.table[i].value.vSTR.str;
				else
					*log.stream << "NULL";
			}
			*log.stream << std::endl;
		}
		*log.stream << "\n\n";
	}

	void writeIntermediateCode(LOG &log, LT::LexTable &Lextable)
	{
		int pb = NULL;
		char*buffer = new char[1024];
		*log.stream << "\n---------������������� ���------------------------------\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
				{
					*log.stream << '0';
				}

				*log.stream << Lextable.table[i].sn << ' ';
				*log.stream << buffer << std::endl;
				pb = NULL;
			}
		}
	}

	void Close(LOG &log)
	{
		(*log.stream).close();
	};
}