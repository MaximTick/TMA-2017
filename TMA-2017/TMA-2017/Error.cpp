#include "stdafx.h"
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[System error] ������������ ��� ������"),
		ERROR_ENTRY(1, "[System error] ��������� ����"),
		ERROR_ENTRY(2, "[System error] �������� -in ������ ���� �����"),
		ERROR_ENTRY(3, "[System error] ��������� ����� �������� ���������"),
		ERROR_ENTRY(4, "[System error] ������ ��� �������� ����� � �������� �����(-in)"),
		ERROR_ENTRY(5, "[System error] ������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY(6, "[SMA] ���������� ������� �������"),
		ERROR_ENTRY(7, "[LA] ������� ���������������"),
		ERROR_ENTRY(8, "[LA] ���������� ��������������� �����������"),
		ERROR_ENTRY(9, "[LA] ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(10, "[SMA] ���������� ������ ������� �������"),
		ERROR_ENTRY(11, "[SMA] �������������� �����"),
		ERROR_ENTRY(12, "[SMA] ��������� ����������� �������� �������"),
		ERROR_ENTRY(13, "[SMA] str ������������� - �������� ������� ���������� math"),
		ERROR_ENTRY(14, "[LA] �������� ������ ������� ������"),
		ERROR_ENTRY(15, "[SA] �������� ��������� ���������"),
		ERROR_ENTRY(16, "[SA] ������ � ���������� ������� "),
		ERROR_ENTRY(17, "[SA] ��������� ��������"),
		ERROR_ENTRY(18, "[SA] ������ � ���������"),
		ERROR_ENTRY(19, "[SA] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(20, "[SA] ������ � ���������� ���������"),
		ERROR_ENTRY(21, "[SMA] ������������� ���������� ������� ��� ����������� ����������"),
		ERROR_ENTRY(22, "[SMA] ������� ������������� �������� ������������ ����� ����� ����������������"),
		ERROR_ENTRY(23, "[IN] ���������� ����������� �������"),
		ERROR_ENTRY(24, "[IN] ��������� ����� ���������� ��������"),
		ERROR_ENTRY(25, "[SMA] �������������� ���������� � �������"),
		ERROR_ENTRY(26, "[SMA] ���������� str �������������� � �������������� ���������"),
		ERROR_ENTRY(27, "[LEX] ������������ �������"),
		ERROR_ENTRY(28, "[SMA] �������� ���������� ���������� ��� ������ �������"),
		ERROR_ENTRY(29, "[LA]  ������� �� ���� ����������"),

	};



	ERROR GetError(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		else
			return errors[id];
	}

	ERROR GetError(int id, int line, int cells)
	{
		ERROR dopError = GetError(id);
		dopError.position.cells = cells;
		dopError.position.line = line;
		return dopError;
	}
}