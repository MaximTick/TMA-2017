#pragma once
#define ERROR_MAXSIZE_MESSAGE 200	
#define ERROR_MAX_ENTRY 1000		
#define ERROR_THROW(id)\
	Error::GetError(id);				
#define ERROR_THROW_IN(id, line, cells)\
	Error::GetError(id, line, cells);	
#define ERROR_ENTRY(id, message) {id, message}	//элемент таблицы ошибок

namespace Error
{
	struct ERROR								//тип исключения для throw ERROR_THROW | ERROR_THROW_IN в catch(ERROR)
	{
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];
		struct
		{
			short line = 0;							//номер строки (0, 1, 2, ...)
			short cells = 0;							//номер позиции в строке(0, 1, 2, ...)
		} position;
	};

	ERROR GetError(int id);							//сформировать ERROR для ERROR_THROW
	ERROR GetError(int id, int line, int cells);	//сформировать ERROR для ERROR_THROW_IN
}