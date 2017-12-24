#pragma once

#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "In.h"
#include "Log.h"
#include "FST.h"

namespace Lexer
{
	struct LEX
	{
		bool next = true;
		LT::LexTable Lextable;
		IT::IdTable	IDtable;
	};

	struct Graph
	{
		char lexema;
		FST::FST graph;
	};

	LEX Fill_LTIT(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm);
}
