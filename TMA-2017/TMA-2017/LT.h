#pragma once
#include "stdafx.h"

#define	LEXEMA_FIXSIZE   1	        //������ �������
#define	LT_MAXSIZE		 4096	    //������������ ���������� ����� � ������� ������
#define	LT_TI_NULLDX	 0xffffffff	//��� �������� ������� ���������������
#define LEX_SEPARATORS	 'S'
#define	LEX_ID_TYPE    	 'n'
#define LEX_APOS         '\''
#define	LEX_ID			 'i'			
#define	LEX_LITERAL		 'l'			
#define	LEX_FUNCTION     'f'			
#define	LEX_START		 's'			
#define	LEX_RETURN		 'r'			
#define	LEX_OUT		     'o'			
//#define LEX_CREATE       'c'
#define LEX_DECLARE		 'c'
#define	LEX_SEPARATOR	 ';'			
#define	LEX_COMMA		 ','			
#define	LEX_LEFTBRACE	 '{'			
#define	LEX_BRACELET	 '}'			
#define	LEX_LEFTHESIS	 '('			
#define	LEX_RIGHTTHESIS	 ')'			
#define	LEX_PLUS		 '+'			
#define	LEX_MINUS		 '-'	
#define LEX_KOREN		 'k'
#define LEX_POW			 'b'
#define LEX_FACT		 'a'
#define	LEX_STAR		 '*'			
#define	LEX_DIRSLASH	 '/'			
#define	LEX_EQUAL		 '='			
#define	LEX_OPERATION	 'v'
#define LEX_END			'e'
#define	NUMBER			 "int"		
#define	WORD			 "str"
#define	LTRL			 "ltrl"
#define LEX_LIBRARY      'm'
#define SPACE  ' '
#define tochka '.'

namespace LT	//������� ������
{
	struct Entry
	{
		char lexema;					
		int sn;					//����� ������ � �������� ������
		int idxTI;						
		Entry();
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);
	};
	struct LexTable																//��������� ������� ������
	{
		int maxsize;															//������� ������� ������
		int size;																//������� ������ ������� ������
		Entry* table;															//������ (Entity)����� ������� ������
	};

	LexTable Create(int size);		            //������� < LT_MAXSIZE
	void Add(LexTable &lextable, Entry entry);	//��������� ������� ������, ������ ������� ������
}