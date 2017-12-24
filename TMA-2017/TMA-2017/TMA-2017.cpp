#include "stdafx.h"
#include "In.h"
#include "LexAnalize.h"
#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include "IT.h"
#include "LT.h"
#include "FST.h"
#include "Generation.h"
#include "MFST.h"
#include "GRB.h"
#include "Semantic.h"
#include "PolishNotation.h"

bool gen = false;

bool variant = false;
int _tmain(int argc, wchar_t *argv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getstream(parm.log);
		Log::writeLog(log);
		Log::writeParm(log, parm);
		In::IN in = In::getin(log.stream, parm.in);
		in.tokens = In::parsOfToken(in.tokens, in.text, in.code);
		Lexer::LEX tables = Lexer::Fill_LTIT(in, log, parm);

		Log::writeIn(log, in);
		Log::writeLexTable(log, tables.Lextable);
		Log::writeIDtable(log, tables.IDtable);
		Log::writeIntermediateCode(log, tables.Lextable);

		if (tables.next == true)
		{
			MFST::Mfst mfst(tables, GRB::getGreibach());
			MFST_TRACE_START(log);
			gen = mfst.start(log);
			mfst.savededucation();
			mfst.printrules(log);
		}

		if (gen == true)
		{
			variant = SemanticAnalyze(tables.Lextable, in, tables.IDtable, log);
		}

		if (variant == true)
		{
			Generation(tables.Lextable, in.tokens, tables.IDtable);
			PN polishNatation;
			if (polishNatation.CreatePolishNotation(&tables))
			{
				*log.stream << "------------------Польская запись построена-------------------" << endl;
				Log::writeIntermediateCode(log, tables.Lextable);
			}
		}



		Log::Close(log);
	}

	catch (Error::ERROR e)
	{
		Log::writeError(log.stream, e);

	}
}