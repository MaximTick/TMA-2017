#include "stdafx.h" 
#include "Parm.h"
#include "Error.h"

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM param = { L"", L"" };

		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(3)
			else
			{
				if (wcsncmp(argv[i], PARM_IN, wcslen(PARM_IN)) == 0) //сравнение строки с подстрокой
				{
					wcscpy_s(param.in, argv[i] + wcslen(PARM_IN)); //начнет копировать после двоеточия
				}

				else if (wcsncmp(argv[i], PARM_LOG, wcslen(PARM_LOG)) == 0)
				{
					wcscpy_s(param.log, argv[i] + wcslen(PARM_LOG));
				}
			}
		}

		if (param.in[0] == NULL)
		{
			throw ERROR_THROW(2);

		}
		if (param.log[0] == NULL)
		{
			wcscpy_s(param.log, param.in);
			wcsncat_s(param.log, PARM_LOG_DEFAULT_EXT, sizeof(PARM_LOG_DEFAULT_EXT));
		};

		return param;
	};
}
