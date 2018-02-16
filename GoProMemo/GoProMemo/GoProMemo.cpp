#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "set_header.h"
#include <ctime>
using namespace std;

void show_Display() {
	system("mode con lines=22 cols=111");
	system("cls");
	noshowCursor(0);
	cout << "��������������������������������������������������������������������������������������������������������������\n";
	cout << "�� ������ ������    ������ ������ ������    ��      �� ������ ��      �� ������ ��\n";
	cout << "�� ��         ��      ��    ��      �� ��      �� ��      ��    ���  ��� ��         ���  ��� �� |  | �� ��\n";
	cout << "�� ��    ��� ��      ��    ������ ������ ��      ��    �� ��� �� ������ �� ��� �� ��  ��  �� ��\n";
	cout << "�� ��      �� ��      ��    ��         ��   ��    ��      ��    ��      �� ��         ��      �� �ᦦ������ ��\n";
	cout << "�� ������ ������    ��         ��      �� ������    ��      �� ������ ��      �� ������ ��\n";
	cout << "��������������������������������������������������������������������������������������������������������������\n" << endl;
	cout << "  �� ====== [����� �޸� ����] ====== ��\n\n";

}

class Memo
{
public:
	void input();
	void showMemo();
	void save();
	void partdelete();
	virtual void howToUse() {}
	vector<string> getMemo();

	Memo()      //memo���� ������ �ʱ�ȭ�ϴ� ������
	{
		ifstream fin("memo.txt");

		if (fin.fail())
		{
			cout << "memo.txt������ �����ϴ�." << endl;
			Sleep(1000);
			system("cls");
		}
		else
		{
			string tmp;
			while (fin)
			{
				getline(fin, tmp);
				memo.push_back(tmp);
			}
			memo.erase(memo.begin() + (memo.size() - 1));
			fin.close();
		}

	}
protected:
	vector<string> memo;
};

class D_DAY : public Memo {
public:
	void howToUse();
	void separate(vector<string> vs, string date_today);
	void printdDay(vector<string> temp);
	void cut(int delimeter_pos);
	void two_month(int pos);
	void one_month(int pos);
private:
	string s_date_month, s_date_day;                          // '/'�� �������� ���� �Ϸ� �����ϰ� ������ date_month�� day�� ��������
	string temp_vs;
	int date_month, date_day;
};

class Debt : public Memo {
public:
	void print(vector <string> memo);
	void howToUse();
};

class Sign : public Memo
{
private:
	vector<string> code;//Sign Code�� �����ϴ� ����
	vector<string> codeFunc;//�ش� code�� �־��� ��ɿ� ���� ������ ����
	vector<string> codeMemo;//sign code�� ���Ե� �޸� ����
public:
	Sign();//��ϵ� �����ڵ�� �ش��ϴ� ����� ������ �ҷ��´�
	void print();//Sign Code ���� �޴��� ���, Code �߰�, ���� ��� ����
	void check(string m);//�޸� �Է� ������ �ش� �޸� Code�� �����ϴ��� �˻��ϴ� �Լ�
	void deleteCode();
	void resetCodeMemo();
	void howToUse();
	void alarm();
	vector<string> getCodeMemo()
	{
		return codeMemo;
	}
	vector<string> getCode()
	{
		return code;
	}
	vector<string> getCodeFunc()
	{
		return codeFunc;
	}
};
int main()
{
	Memo memoInst;
	D_DAY d_dayInst;
	Debt debtInst;
	Sign signInst;
	Memo *memoptr;
	char num;
	vector<string> tmp = memoInst.getMemo();
	signInst.resetCodeMemo();
	for (int i = 0; i < tmp.size(); i++)//���� ����� �޸���� sign code�� ����ִ� �޸� ã�´�
	{
		signInst.check(tmp[i]);
	}
	signInst.alarm();
	while (true)
	{
		vector<string> tmp = memoInst.getMemo();
		signInst.resetCodeMemo();
		for (int i = 0; i < tmp.size(); i++)//���� ����� �޸���� sign code�� ����ִ� �޸� ã�´�
		{
			signInst.check(tmp[i]);
		}
		show_Display();
		memoInst.showMemo();

		cout << endl << endl << endl << endl;
		gotoxy(42, 15);
		cout << "  <<<< �� ~ �� ���� �Է��ϼ��� >>>>";
		gotoxy(66, 7);
		cout << "[��� �� �� ����� �Է� �� �������ּ��� ��]";
		gotoxy(34, 18);
		cout << "��.�޸��߰� ��.�޸�κл��� ��.D-DAY ��.ä�� ��.DIY code���� ��.���� (   )";
		gotoxy(105, 18); cin >> num;
		getchar();

		if (num == '1')
		{
			memoInst.input();
			Sleep(500);
			system("cls");
			continue;
		}
		else if (num == '2')
		{
			memoInst.partdelete();
			Sleep(500);
			system("cls");
			continue;
		}
		else if (num == '3')
		{
			int back;

			system("cls");
			while (true) {
				vector <string> memo = memoInst.getMemo();
				d_dayInst.printdDay(memo);
				gotoxy(70, 18);
				cout << "1 : HOME  //  2 : How To Use  ->  ";
				gotoxy(104, 18);
				int num;
				cin >> num;
				if (num == 1) {
					system("cls");
					break;
				}
				else if (num == 2) {
					system("cls");
					memoptr = &d_dayInst;
					memoptr->howToUse();
					cin >> back;
					if (back == 1)
					{
						system("cls");
						break;
					}
					else if (back == 2)
					{
						system("cls");
						continue;
					}
				}
			}
			memoInst.save();
			system("cls");
			continue;
		}
		else if (num == '4')
		{
			while (1)
			{
				system("cls");
				vector <string> memo = memoInst.getMemo();
				debtInst.print(memo);
				gotoxy(70, 18);
				cout << "1 : HOME  //  2 : How To Use  ->  ";
				gotoxy(104, 18);
				cin >> num;

				if (num == '1')
				{
					//system("cls");
					break;
				}
				else if (num == '2')
				{
					system("cls");
					memoptr = &debtInst;
					memoptr->howToUse();
					gotoxy(70, 18);
					cout << "1 : HOME  //  2 : Back  ->  ";
					gotoxy(104, 18);
					cin >> num;

					if (num == '1')
					{
						break;
					}
					else if (num == '2')
					{
						system("cls");
						continue;
					}
				}
			}
			memoInst.save();
			system("cls");
			continue;
		}
		else if (num == '5')
		{
			system("cls");
			signInst.print();
			system("cls");
			continue;
		}
		else if (num == '6')
		{
			system("cls");
			memoInst.save();
			cout << "�����մϴ�!" << endl;
			Sleep(500);
			break;
		}
		else
		{
			gotoxy(55, 19);
			cout << "============ �ٽ� �����ϼ���.============" << endl;
			Sleep(1000);
			system("cls");
			continue;
		}
	}

	return 0;
}
void Memo::showMemo()   // �ؽ�Ʈ���Ͽ� ����� �����͸� ǥ��
{
	for (int i = 0; i < memo.size(); i++)
	{
		cout << "         " << i + 1 << ".  " << memo[i] << "            " << endl;
	}
	cout << endl;
	cout << "  ���ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѦ�";

}

void Memo::input()      // �����͸� �Է¹޾� memo���Ϳ� ����
{
	system("cls");
	string str;
	cout << "�޸� �Է��Ͻÿ�" << endl;
	getline(cin, str);
	memo.push_back(str);
	system("cls");
}

void Memo::save()      // �Է¹��� �����͸� �ؽ�Ʈ���Ͽ� ����
{
	ofstream fout("memo.txt");
	for (int i = 0; i < memo.size(); i++)
		fout << memo[i] << endl;
	fout.close();
}

void Memo::partdelete()      //���ϴ� �޸� ���� �Լ�
{
	if (memo.size() == 0)
	{
		gotoxy(55, 20);
		cout << "  ===== ���� �޸� �����ϴ� =====";
	}
	else
	{
		gotoxy(55, 19);
		cout << "�� ������� �ϴ� �޸� ��ȣ�� �Է��ϼ��� (   ) ";
		int n;
		gotoxy(97, 19); cin >> n;

		while (n > memo.size() || n == 0)
		{
			gotoxy(55, 20);
			cout << "�� �ٽ� �����ϼ���." << endl;
			Sleep(500);
			gotoxy(55, 19);
			cout << "�� ������� �ϴ� �޸� ��ȣ�� �Է��ϼ��� (   ) ";
			gotoxy(97, 19); cin >> n;
		}

		memo.erase(memo.begin() + n - 1);
		gotoxy(55, 20);
		cout << n << " �� �޸� �����Ǿ����ϴ�." << endl << endl;
		system("cls");
	}
}

vector<string> Memo::getMemo()   // �ٸ� ��� Ŭ�������� ����ϱ� ���� getMemo�Լ��� ���� memo���� ��ȯ
{
	return memo;
}

const string currentDateTime() // ����ð� �Լ�
{
	time_t now = time(0); //���� �ð��� time_t Ÿ������ ����
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct); // YYYY-MM-DD ������ ��Ʈ��
	return buf;
}

void D_DAY::howToUse() {
	cout << "**************************************** [D-DAY] �޸� ���� ****************************************" << endl << endl;
	cout << "1. ��¥�� ������ ���� �޸���� D-Day�� �˷��ݴϴ�." << endl;
	cout << "2. D-Day�� �ڵ����� ���� �ϰ� �ʹٸ� ��¥�� 'mm/dd' �������� �޸� �Է��Ͻø� �˴ϴ�." << endl;
	cout << "3. ��¥�� �� �ڷ� ������ �������� �մϴ�." << endl;
	cout << "\n\t��) 7/15 ����, ���� ������Ʈ ���� 6/17";
	gotoxy(70, 18);
	cout << "1 : HOME  //  2 : Back  ->  ";
	gotoxy(100, 18);

}
void D_DAY::two_month(int pos) {
	int j = pos;

	if (temp_vs[j + 2] == ' ') {
		s_date_month.push_back(temp_vs[j - 2]); s_date_month.push_back(temp_vs[j - 1]);
		s_date_day.push_back(temp_vs[j + 1]);
		date_month = stoi(s_date_month); date_day = stoi(s_date_day);
	}
	else {
		s_date_month.push_back(temp_vs[j - 2]); s_date_month.push_back(temp_vs[j - 1]);
		s_date_day.push_back(temp_vs[j + 1]); s_date_day.push_back(temp_vs[j + 2]);
		date_month = stoi(s_date_month); date_day = stoi(s_date_day);
	}
}
void D_DAY::one_month(int pos) {
	int l = pos;

	if (temp_vs[l + 2] == ' ') {
		s_date_month.push_back(temp_vs[l - 1]);
		s_date_day.push_back(temp_vs[l + 1]);
		date_month = stoi(s_date_month); date_day = stoi(s_date_day);
	}
	else {
		s_date_month.push_back(temp_vs[l - 1]);
		s_date_day.push_back(temp_vs[l + 1]); s_date_day.push_back(temp_vs[l + 2]);
		date_month = stoi(s_date_month); date_day = stoi(s_date_day);
	}
}
void D_DAY::cut(int delimeter_pos) {
	int deli = delimeter_pos;

	if (deli == 2) {
		two_month(deli);
	}
	else if (deli == 1) {
		one_month(deli);
	}
	else if (temp_vs[deli - 2] == ' ') {
		two_month(deli);
	}
	else if (temp_vs[deli - 1] == ' ') {
		one_month(deli);
	}

}
void D_DAY::separate(vector<string> vs, string date_today) {
	for (int v = 0; v < vs.size(); v++) {
		if (vs[v].find("/") != string::npos) {
			temp_vs = vs[v];
			cut(temp_vs.find("/"));
			cout << temp_vs << " ";

			string s_today_month, s_today_day;
			int d_month = 0, d_day = 0;
			int today_month = 0, today_day = 0;                              //���� ���� �� ����

			s_today_month.push_back(date_today[5]); s_today_month.push_back(date_today[6]);
			today_month = stoi(s_today_month);

			s_today_day.push_back(date_today[8]); s_today_day.push_back(date_today[9]);
			today_day = stoi(s_today_day);

			if (date_month == today_month) {
				d_day = date_day - today_day;
			}
			else {
				d_month = date_month - today_month;
				if (d_month == 1 || d_month == 3 || d_month == 5 || d_month == 7 || d_month == 8 || d_month == 10 || d_month == 12) {
					d_day = date_day - today_day + d_month * 30;
				}
				else {
					d_day = date_day - today_day + d_month * 31;
				}
			}
			if (d_day == 0) {
				setcolor(12, 0);
				cout << "D-DAY";
				setcolor(15, 0);
			}
			else if (d_day < 5) {
				setcolor(12, 0);
				cout << "D-" << d_day;
				setcolor(15, 0);
			}
			else
				cout << "D-" << d_day;
			cout << endl;
			for (int e = 0; e < s_date_month.size(); e++) {
				s_date_month.erase(e);
			}
			for (int e = 0; e < s_date_day.size(); e++) {
				s_date_day.erase(e);
			}
			for (int e = 0; e < s_today_month.size(); e++) {
				s_today_month.erase(e);
			}
			for (int e = 0; e < s_today_day.size(); e++) {
				s_today_day.erase(e);
			}
			for (int e = 0; e < temp_vs.size(); e++) {
				temp_vs.erase(e);
			}
		}
	}
}
void D_DAY::printdDay(vector<string> temp) {
	vector <string> memo = temp;    //�ؽ�Ʈ���Ͽ��� �޾ƿͼ� ���Ϳ� ����
	string today;                   // ���ó�¥
	cout << "******************** [ D_DAY ] �޸� ********************" << endl << endl;

	cout << "���� ��¥\n20";
	today = currentDateTime();
	for (int t = 2; t < 10; t++) {
		if ((t % 3) != 1)
			cout << today[t];
		else
			cout << '/';
	}
	cout << "\n\n";
	//���� ��¥ ���
	separate(memo, today);
}
void Debt::print(vector <string> memo)
{
	vector <int> repay; //������ �迭
	vector <int> recieve; //������ �迭

	cout << "******************** [ ä�� ] �޸� ********************" << endl << endl;
	string a, b;
	int n, m;
	int sum1 = 0;
	int sum2 = 0;

	//�޸�� ���뿡�� '\'��� ���ڸ� ä�� �޸� ��ü�� ã�� ���
	for (int i = 0; i < memo.size(); i++)
	{

		if (memo[i].find("\\") != string::npos)
		{
			cout << memo[i] << endl;
		}

	}
	//ä�� �޸� �� '����' ���ڿ��� ã�� ���ںκи� �����Ͽ� ������ �迭�� �Ҵ�
	for (int i = 0; i < memo.size(); i++)
	{

		if (memo[i].find("\\") != string::npos)
		{
			int k = 0;
			int index = 0;
			for (k = 0; k < memo[i].length(); k++)
			{
				if (memo[i].at(k) == '\\')
					index = k;
			}

			if (memo[i].find("����") != string::npos)
			{

				for (int j = index; j < memo[i].length(); j++)
				{
					// 48 ~ 57�� �ƽ�Ű �ڵ�� 0~9�̴�. ���ںκ�(�ݾ�)�� ����
					if (48 <= memo[i].at(j) && memo[i].at(j) <= 57)
						a += memo[i].at(j);
				}

				n = std::stoi(a); //�ݾ׸� �����Ͽ� ������ int������ ��ȯ
				repay.push_back(n); //������ �迭
				a = '0'; //���� �ʱ�ȭ

			}
			else //�������� ��� ('�ޱ�' ���ڿ��� ã������)
			{

				for (int j = index; j < memo[i].length(); j++)
				{

					// 48 ~ 57�� �ƽ�Ű �ڵ�� 0~9�̴�.
					if (48 <= memo[i].at(j) && memo[i].at(j) <= 57)
						b += memo[i].at(j);
				}

				m = std::stoi(b); //�ݾ׸� �����Ͽ� ������ int������ ��ȯ
				recieve.push_back(m); //������ �迭
				b = '0'; //���� �ʱ�ȭ

			}

		}

	}

	for (int i = 0; i < repay.size(); i++)
	{
		sum1 += repay[i];
	}

	for (int i = 0; i < recieve.size(); i++)
	{
		sum2 += recieve[i];
	}
	cout << endl << "*** ���� �� : \\" << sum1 << "��   ���� �� : \\" << sum2 << "�� ***" << endl;

}
void Debt::howToUse()
{
	cout << "**************************************** [ ä�� ] �޸� ���� ****************************************" << endl << endl;
	cout << "1. HOME �޴����� �޸� �߰��� ��� �ÿ� �޸� ������ ���� �ݾ� ù�κп� '\\' ������ �Է��մϴ�.\n";
	cout << "2. '����'�� '�ޱ�'�� ������ �Է��Ͽ� �޸� ����� �մϴ�.\n";
	cout << "\tex)�����̿��� \\1500�� �ޱ�\n";
	cout << "3. ������ �ٿ��� '���� ��'�� '���� ��'�� ������ �� �հ踦 �����帳�ϴ�.\n";
}

Sign::Sign()
{
	//////////�ؽ�Ʈ ���Ͽ� ����� Sign Code�� �ҷ���
	ifstream fin_Signcode;
	fin_Signcode.open("SignCode.txt");
	if (fin_Signcode.fail())//���� ������� code �ؽ�Ʈ ������ ���� ��� �˸��� ���� ���� ������ �ҷ����̴� �۾��� �ǳʶڴ�
	{
		system("cls");
	}
	else
	{
		string tmpstr;//�ؽ�Ʈ���Ͽ��� ������ �о���϶� ���� �ӽ� ���ڿ�
		while (fin_Signcode)//fin�� ������ ��(0)�� ������ �ݺ��� Ż��
		{
			getline(fin_Signcode, tmpstr);
			code.push_back(tmpstr);
		}
		//�����ؽ�Ʈ ���Ͽ��� �о���� ������ ���๮�ڰ� code�� �νĵǹǷ� ������ ������ �ε����� ������
		code.erase(code.begin() + (code.size() - 1));
		fin_Signcode.close();
	}
	///////////�ؽ�Ʈ ���Ͽ� ����� code�� ��ɿ� ���� �����͸� �ҷ���
	ifstream fin_codeFunc;
	fin_codeFunc.open("codeFunc.txt");
	if (fin_codeFunc.fail())
	{
		system("cls");
	}
	else
	{
		string tmpstr;
		while (fin_codeFunc)
		{
			getline(fin_codeFunc, tmpstr);
			codeFunc.push_back(tmpstr);
		}
		codeFunc.erase(codeFunc.begin() + (codeFunc.size() - 1));
		fin_codeFunc.close();
	}
}
void Sign::howToUse()
{
	system("cls");
	cout << "**************************************** [DIY Sign Code] �޸� ���� ****************************************" << endl << endl;
	cout << "1. Code�߰� �޴����� ���ϴ� ��ȣ�� �߰��Ͻʽÿ�" << endl;
	cout << "2. ��ȣ�� �ش��ϴ� ����� �����Ͻʽÿ�" << endl;
	cout << "3. �˶������ ������ ��� ��ȣ�� ��¥�� �������� �޸� �ۼ��Ͻʽÿ� " << endl;
	cout << "e.g.) # 6/21 ������ȸ   ->   6��21�Ͽ� �޸𳻿��� ȭ�鿡 ��� �˶������ �Ѵ�.";

	gotoxy(70, 18);
	cout << "1 : HOME  //  2 : Back  ->  ";
	gotoxy(100, 18);
}
void Sign::deleteCode()
{
	int num;
	cout << "choose code to delete(0 to quit)" << endl;
	cin >> num;
	if (num == 0)
	{
		return;
	}
	code.erase(code.begin() + (num - 1));
	codeFunc.erase(codeFunc.begin() + (num - 1));
}
void Sign::alarm()
{
	int c = 0;
	string today = currentDateTime();
	vector<int> tday;
	tday.push_back(atoi(&today[5]));
	tday.push_back(atoi(&today[8]));

	vector<int> alarmday;
	for (int i = 0; i < codeMemo.size(); i++)
	{
		alarmday.clear();
		alarmday.push_back(atoi(&codeMemo[i][2]));
		if (codeMemo[i][4] == '/')
			alarmday.push_back(atoi(&codeMemo[i][5]));
		else
			alarmday.push_back(atoi(&codeMemo[i][4]));

		if (tday[0] == alarmday[0] && tday[1] == alarmday[1])
		{
			c++;
			cout << "������ " << codeMemo[i] << " �� �ִ� ���Դϴ�" << endl;

		}
		if (i == codeMemo.size() - 1 && c>0)
		{
			cout << endl << endl << endl << endl << "1���� ���� ����ȭ������";
			int n; cin >> n;
			if (n == 1)
				return;
		}

	}
}
void Sign::print()
{
	while (true)
	{
		system("cls");
		cout << "���� ������ Sign code" << endl;
		if (code.size() == 0)//code����ũ�Ⱑ 0�̸� ������ code�� ���� ����
			cout << "������ code�� �����ϴ�" << endl;
		for (int i = 0; i < code.size(); i++)//code������ ������ ��� ���
			cout << code[i] << " : " << codeFunc[i] << "���" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "1.Code�߰� 2.Code���� 3.Code�� ���Ե� �޸� 4.���� 5.���ư���" << endl;
		char num;//�޴��� �Է¹޴� ���� 1.�߰� 2.���� 3.�޸�ȭ��
		cin >> num; system("cls");
		if (num == '1')//////////////////////////code�߰�
		{
			cout << "�߰��� �ڵ� �Է� : ";
			string c; cin >> c;
			code.push_back(c);
			system("cls");
			while (true) {
				cout << "���ϴ� ����� ��ȣ�� �Է��Ͻÿ�(1.�˶� 2.����1 3.����2)" << endl << "e.x. �˶���� ->" << c << " 6/20 : 6/20�Ͽ� �ش� �޸� ���� �˶�" << endl;

				char n; cin >> n;
				if (n == '1') {
					codeFunc.push_back("�˶�");
				}
				else if (n == '2') {
					codeFunc.push_back("����1");
				}
				else if (n == '3') {
					codeFunc.push_back("����2");
				}
				else {
					cout << "1,2,3 �߿��� �Է��Ͻÿ�" << endl; Sleep(500); system("cls"); continue;
				}
				break;
			}
		}
		else if (num == '2')///////////////////////////////code����
		{
			for (int i = 0; i < code.size(); i++)
				cout << i + 1 << " : " << code[i] << endl;
			deleteCode();
		}
		else if (num == '3')
		{
			system("cls");
			for (int i = 0; i < codeMemo.size(); i++)
			{
				cout << codeMemo[i] << endl;
			}
			cout << endl << endl << endl;
			cout << "1�� ������ �ڷΰ���";
			int n; cin >> n;
			if (n == 1)
				continue;
		}
		else if (num == '4')
		{
			Memo *memoptr = &(*this);
			memoptr->howToUse();
			gotoxy(104, 18);
			int n; cin >> n;
			if (n == 1)
				break;
			if (n == 2)
				continue;
		}
		else if (num == '5')////////////////////////////////sign code�� �ؽ�Ʈ ���Ͽ� �����ϰ� �ʱ� �޸� ȭ������ ���ư���
		{
			///////////������ ����� Sign Code ���� �ؽ�Ʈ ���Ͽ� ����
			ofstream fout_Signcode;
			fout_Signcode.open("SignCode.txt");//���� ��ϵǾ� �ִ� code���� �ؽ�Ʈ ���Ͽ� �����Ѵ�.
			for (int i = 0; i < code.size(); i++)
				fout_Signcode << code[i] << endl;
			fout_Signcode.close();
			//////////������ ����� code �� ����� �ؽ�Ʈ ���Ͽ� ����
			ofstream fout_codeFunc;
			fout_codeFunc.open("codeFunc.txt");
			for (int i = 0; i < codeFunc.size(); i++)
				fout_codeFunc << codeFunc[i] << endl;
			fout_codeFunc.close();
			break;
		}

		else///////////////////////////����� 1�ʵ��� ��� �� �ٽ� ��ȣ�� �Է� ����
		{
			cout << "1~3�� �߿� �Է��Ͻÿ�" << endl;
			Sleep(1000);
			system("cls");
			continue;
		}
		system("cls");
	}
	system("cls");
}
void Sign::check(string m)
{
	string tmp;
	tmp = m[0];
	for (int i = 0; i < code.size(); i++)//�Ѱܹ��� ���ڿ��� �տ� ����� code�� ��ġ�ϴ� ���ڰ� �ִ��� Ȯ��
	{
		if (tmp == code[i])
		{
			codeMemo.push_back(m);
		}
	}
}
void Sign::resetCodeMemo()
{
	codeMemo.clear();
}