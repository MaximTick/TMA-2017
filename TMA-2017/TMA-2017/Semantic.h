#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include "In.h"
#include "Error.h"


bool SemanticAnalyze(LT::LexTable &Lextable, In::IN &InStruct, IT::IdTable &idtable, Log::LOG &log);