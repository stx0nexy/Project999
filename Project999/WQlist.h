#ifndef WQlistH
#define WQlistH
#define InputError cout<<"���� ���� �� ���, �������� ��������, �� �� ����� �� ��������� �� ���."<<endl
const int maxWords = 60;
#define slovar {"#����#","#����#","#�����#","#������#","#������#",\
		"#�����#","#��������#","#�������������#","#�����#","#���������#","#����#",\
		"#������#","#������#","#������#","#���������#","#�������#","#������#","#����'�#",\
		"#������#","#������#","#�����#","#������#","#������#","#�������#","#�������#","#������#",\
		"#��������#","#�����#","#�����#","#������#","#�������#","#����#","#�����#","#�������#","#�������#",\
		"#�����#","#��������#","#������#","#�������#","#������#","#������#", "#����#", "#����#", "#�������#",\
		"#���#", "#����#", "#�����#", "#�����#", "#�����#", "#�����#", "#�����#", "#�����#", "#�����#", "#����#",\
		"#�����#", "#������#", "#���#","#����#", "#�������#","#���#" } ;
#define qtoslovar {"�������� ��������, �� ����� ������� ������ ���� ��� ������",\
		"������������ ������-����","���� �������","������� ����","������, ��� ���������� ������ ��������",\
		"�������� ����� ��� ���� � ����'� ���������", \
		" ������������� ������ ��� �������� �� ������������� �� ���������� ����������","���� �����'� �� �����",\
		"����� ���� ���������","˳������ ������, ���������� ��볺�","������� ���, ��� ����� �� ��� ���� ����",\
		"�������, � ��� ����������� �����","�������� ������� ���","��������, �� �������� ����� �� ������ �� ����� ����",\
		"���������� ��������, �� ����� �����","��������� ������� �� �����","8-� ������� ������� �������",\
		"����� �������� ����","��� �������� ������ ��������?"," 9-� ������� ������� �������","�� ������","� ����� �� ����, �������� ������� �����","�����������",\
		"������� ����� �������� ������ ������.","������ ������� ������� ������� ������. ³� ���� ������ ������� � ������ ����������",\
		"���� ������ ��� �� ������","������� �����","�������, ��� �� �������� ���","�������� ����, �� ���� ����",\
		"���� � ������ �� ����� ������ �� �������� �������� � ������ ���.","��������� ������� ���","������� �������",\
		"����� ������� � ������ ����?","������� ����","������������� �������","�������, ���� ������ ����� ϳ�����",\
		"������ ����� ����","�������, �� ������ ���� � ��� ���������","������ � ���� (�����) ������","������� ���",\
		"��������� ��� ����� ������� ����� �� ��������� �����",\
		"�������� � ������� �������, � ��� ����������� ������� �������� ��� ������� �����������",\
		"����� ������� ������� �������","...������������(�������������� �������)",\
		"����� ����������� ��������� ���������� � ����������� ��������� ������",\
		"�������� ����-����������� � ������ � �������, ������� �� ������ ����� ����������������� ������ ",\
		"�����, ���� ������ ���� � ����� *������*(�������������)","������ ������� ������ ��� ������ ����, ������� ������",\
		"�������� �������","� ����������� ������ �� ������������� ��� - ������ � ������� �������������","Ƴ���� ��'�",\
		"������������ ��������� ��� ��������� ������ �����",\
		"��-������ �����������, ��������� �� ����-������ �� �������� ������� ���������,��������,�����",\
		"���������(� ���������� �� �������� �����������)� ����������� �����",\
		"����� ��� ...(����� ������� ������� ��������, ���� ����������)","�������� ����� �� ������ ������� ������",\
		"������������ ������ � �������,�� ������ �������� ����������� � ����������� � �������� ��� ���������� ��������� ������� ��� � �����",\
		"... �������(��������� ����������)","Գ���������� �����, �� ������ ����, ��������� ������, �� �� �������","������� ������"};
#endif