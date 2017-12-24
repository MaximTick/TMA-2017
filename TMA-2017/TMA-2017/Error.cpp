#include "stdafx.h"
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[System error] Недопустимый код ошибки"),
		ERROR_ENTRY(1, "[System error] Системный сбой"),
		ERROR_ENTRY(2, "[System error] Параметр -in должен быть задан"),
		ERROR_ENTRY(3, "[System error] Превышена длина входного параметра"),
		ERROR_ENTRY(4, "[System error] Ошибка при открытии файла с исходным кодом(-in)"),
		ERROR_ENTRY(5, "[System error] Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY(6, "[SMA] Отсутствие главной функции"),
		ERROR_ENTRY(7, "[LA] Попытка переопределения"),
		ERROR_ENTRY(8, "[LA] Отсуствует предварительное определение"),
		ERROR_ENTRY(9, "[LA] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(10, "[SMA] Обнаружена вторая главная функция"),
		ERROR_ENTRY(11, "[SMA] Несоответствие типов"),
		ERROR_ENTRY(12, "[SMA] Запрещено присваивать значение функции"),
		ERROR_ENTRY(13, "[SMA] str идентификатор - параметр функции библиотеки math"),
		ERROR_ENTRY(14, "[LA] Превышен размер таблицы лексем"),
		ERROR_ENTRY(15, "[SA] Неверная структура программы"),
		ERROR_ENTRY(16, "[SA] Ошибка в параметрах функции "),
		ERROR_ENTRY(17, "[SA] Ошибочный оператор"),
		ERROR_ENTRY(18, "[SA] Ошибка в выражении"),
		ERROR_ENTRY(19, "[SA] Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(20, "[SA] Ошибка в построении выражения"),
		ERROR_ENTRY(21, "[SMA] Использование встроенной функции без подключения библиотеки"),
		ERROR_ENTRY(22, "[SMA] Попытка использования операции присваивания между двумя идентификаторами"),
		ERROR_ENTRY(23, "[IN] Отсутствие закрывающей ковычки"),
		ERROR_ENTRY(24, "[IN] Превышена длина строкового литерала"),
		ERROR_ENTRY(25, "[SMA] Несоответствие параметров в функции"),
		ERROR_ENTRY(26, "[SMA] Обнаружены str идентификаторы в математическом выражении"),
		ERROR_ENTRY(27, "[LEX] Неопознанный элемент"),
		ERROR_ENTRY(28, "[SMA] Неверное количество параметров при вызове функции"),
		ERROR_ENTRY(29, "[LA]  Деление на ноль невозможно"),

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