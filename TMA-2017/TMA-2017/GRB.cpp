#include "stdafx.h"
#include "GRB.h"
#define GRB_ERROR_SERIES 0

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 6,
		Rule(NS('S'), GRB_ERROR_SERIES + 15, 3,   //  ��������� ���������
			Rule::Chain(9, TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(4, TS('s'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(3, TS('m'), TS(';'), NS('S'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 16, 2,
			Rule::Chain(2, TS('n'), TS('i')),   // ��������� �-��
			Rule::Chain(4, TS('n'), TS('i'), TS(','), NS('F'))

		),
		Rule(NS('N'), GRB_ERROR_SERIES + 17, 8,  // ��������� ����������� � �-���
			Rule::Chain(5, TS('c'), TS('n'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('m'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(3, TS('e'), TS(';'), TS(']'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 18, 18, // ���������
			Rule::Chain(1, TS('i')),
			Rule::Chain(2, TS('-'), TS('l')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('k'), TS('('), TS('l'), TS(')')),
			Rule::Chain(5, TS('k'), TS('('), TS('-'), TS('l'), TS(')')),
			Rule::Chain(4, TS('k'), TS('('), TS('i'), TS(')')),
			Rule::Chain(4, TS('a'), TS('('), TS('l'), TS(')')),
			Rule::Chain(5, TS('a'), TS('('), TS('-'), TS('l'), TS(')')),
			Rule::Chain(4, TS('a'), TS('('), TS('i'), TS(')')),
			Rule::Chain(6, TS('b'), TS('('), TS('i'),TS(','), TS('i'), TS(')')),
			Rule::Chain(5, TS('b'), TS('('), TS('-'), TS('l'), TS(')')),
			Rule::Chain(4, TS('b'), TS('('), TS('l'), TS(')')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 19, 6, // ����������� ��������� �-��
			Rule::Chain(2, TS('-'), TS('l')),
			Rule::Chain(4, TS('-'), TS('l'), TS(','), NS('W')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 20, 8, // �����
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M'))
		)
	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)  //����������� ������� - ������ ����� �������(���-�� �������� � �������, �������� ��� ����������...)
	{
		nt = new GRBALPHABET[size = psize];    //������� ����������
		int*p = (int*)&s;                      //����������� ������ ��������� �
		for (short i = 0; i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i]; //��������� ������� ����������
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) //����������� �������
	{															//(����������, ������������� ���������������� ���������, ���������� �������(������ ������ �������), ��������� ������� (������ ������ �������)
		nn = pnn;    //����������
		iderror = piderror; //�������������
		chains = new Chain[size = psize]; //����� ��� �������
		Chain*p = &c;
		for (int i = 0; i < size; i++)
			chains[i] = p[i]; //��������� ��������� �������
	};

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)//����������� ���������� ��������(��������� ������, ��� �����, ���������� ������, �������...)
	{
		startN = pstartN; //��������� ������
		stbottomT = pstbottom;//��� �����
		rules = new Rule[size = psize];//�������� ������
		Rule*p = &r;
		for (int i = 0; i < size; i++) rules[i] = p[i];//��������� �������
	};
	Greibach getGreibach() { return greibach; }; //�������� ����������

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) //�������� ������� (����� ������ �������, ������������ ������� ����������)
	{
		short rc = -1;
		short k = 0;
		while (k < size&&rules[k].nn != pnn)
			k++;   //���� � ������ ���������� ������ � ���� ����� ������ ������� �� ����� �������� �-���
		if (k < size)
			prule = rules[rc = k];    //������������ ������� ��������� ����� ������� � �������� �
		return rc; //������������ ����� ������� ��� -1
	};

	Rule Greibach::getRule(short n) //�������� ������� �� ������
	{
		Rule rc;      //������ ������� ��
		if (n < size)rc = rules[n];  //����������� ������� �� ������� �
		return rc; //���������� ��������� �������
	};

	char*Rule::getCRule(char*b, short nchain) //�������� ������� � ���� N->������� (�����, ����� �������(������ �����) � �������)
	{
		char bchain[200]; //������
		b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00; //�������� -> 
		chains[nchain].getCChain(bchain); //�������� ������ ������� �������
		strcat_s(b, sizeof(bchain) + 5, bchain);//��������� ������ (����, � ������ ��������, ������)
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) //�������� ��������� �� j ���������� �������, ������� � ����� ��� -1 
	{                                                                //(������ ������ �������, ������������ �������, ����� �������)
		short rc = -1;
		while (j < size&&chains[j].nt[0] != t)++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)pchain = chains[rc];
		return rc;
	};

	char*Rule::Chain::getCChain(char*b) //�������� ������ ������� �������
	{
		for (int i = 0; i < size; i++)b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};
};