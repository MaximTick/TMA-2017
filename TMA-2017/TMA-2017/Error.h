#pragma once
#define ERROR_MAXSIZE_MESSAGE 200	
#define ERROR_MAX_ENTRY 1000		
#define ERROR_THROW(id)\
	Error::GetError(id);				
#define ERROR_THROW_IN(id, line, cells)\
	Error::GetError(id, line, cells);	
#define ERROR_ENTRY(id, message) {id, message}	//������� ������� ������

namespace Error
{
	struct ERROR								//��� ���������� ��� throw ERROR_THROW | ERROR_THROW_IN � catch(ERROR)
	{
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];
		struct
		{
			short line = 0;							//����� ������ (0, 1, 2, ...)
			short cells = 0;							//����� ������� � ������(0, 1, 2, ...)
		} position;
	};

	ERROR GetError(int id);							//������������ ERROR ��� ERROR_THROW
	ERROR GetError(int id, int line, int cells);	//������������ ERROR ��� ERROR_THROW_IN
}