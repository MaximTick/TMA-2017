#pragma once
#include "stdafx.h"
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "LT.h"
#include "IT.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE] = L" ";
		ofstream *stream = NULL;
	};
	bool static Eror = true;
	LOG getstream(wchar_t logfile[]);
	void writeLog(LOG &log);
	void writeParm(LOG &log, Parm::PARM &parm);
	void writeIn(LOG &log, In::IN &in);
	void writeError(ofstream *stream, Error::ERROR &error);
	void writeLexTable(LOG &log, LT::LexTable &lextable);
	void writeIDtable(LOG &log, IT::IdTable &IDtable);
	void writeIntermediateCode(LOG &log, LT::LexTable &lextable);
	void Close(LOG &log);
}