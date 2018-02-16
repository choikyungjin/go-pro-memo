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
	cout << "┌─────────────────────────────────────────────────────┐\n";
	cout << "│ ■■■■■ ■■■■■    ■■■■■ ■■■■■ ■■■■■    ■      ■ ■■■■■ ■      ■ ■■■■■ │\n";
	cout << "│ ■         ■      ■    ■      ■ ■      ■ ■      ■    ■■  ■■ ■         ■■  ■■ ■ |  | ■ │\n";
	cout << "│ ■    ■■ ■      ■    ■■■■■ ■■■■■ ■      ■    ■ ■■ ■ ■■■■■ ■ ■■ ■ ■  ㆍ  ■ │\n";
	cout << "│ ■      ■ ■      ■    ■         ■   ■    ■      ■    ■      ■ ■         ■      ■ ■└─┘■ │\n";
	cout << "│ ■■■■■ ■■■■■    ■         ■      ■ ■■■■■    ■      ■ ■■■■■ ■      ■ ■■■■■ │\n";
	cout << "└─────────────────────────────────────────────────────┘\n" << endl;
	cout << "  ┌ ====== [저장된 메모 내용] ====== ┐\n\n";

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

	Memo()      //memo벡터 변수를 초기화하는 생성자
	{
		ifstream fin("memo.txt");

		if (fin.fail())
		{
			cout << "memo.txt파일이 없습니다." << endl;
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
	string s_date_month, s_date_day;                          // '/'를 기준으로 월과 일로 구분하고 각각의 date_month와 day에 저장해줌
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
	vector<string> code;//Sign Code를 저장하는 변수
	vector<string> codeFunc;//해당 code에 주어진 기능에 대한 정보를 저장
	vector<string> codeMemo;//sign code가 포함된 메모를 저장
public:
	Sign();//등록된 사인코드와 해당하는 기능을 변수로 불러온다
	void print();//Sign Code 설정 메뉴를 출력, Code 추가, 삭제 기능 포함
	void check(string m);//메모를 입력 받으면 해당 메모에 Code가 존재하는지 검사하는 함수
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
	for (int i = 0; i < tmp.size(); i++)//현재 저장된 메모들중 sign code가 들어있는 메모를 찾는다
	{
		signInst.check(tmp[i]);
	}
	signInst.alarm();
	while (true)
	{
		vector<string> tmp = memoInst.getMemo();
		signInst.resetCodeMemo();
		for (int i = 0; i < tmp.size(); i++)//현재 저장된 메모들중 sign code가 들어있는 메모를 찾는다
		{
			signInst.check(tmp[i]);
		}
		show_Display();
		memoInst.showMemo();

		cout << endl << endl << endl << endl;
		gotoxy(42, 15);
		cout << "  <<<< ① ~ ⑥ 번을 입력하세요 >>>>";
		gotoxy(66, 7);
		cout << "[사용 후 꼭 ⑥번을 입력 후 종료해주세요 ♥]";
		gotoxy(34, 18);
		cout << "①.메모추가 ②.메모부분삭제 ③.D-DAY ④.채무 ⑤.DIY code설정 ⑥.종료 (   )";
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
			cout << "감사합니다!" << endl;
			Sleep(500);
			break;
		}
		else
		{
			gotoxy(55, 19);
			cout << "============ 다시 선택하세요.============" << endl;
			Sleep(1000);
			system("cls");
			continue;
		}
	}

	return 0;
}
void Memo::showMemo()   // 텍스트파일에 저장된 데이터를 표시
{
	for (int i = 0; i < memo.size(); i++)
	{
		cout << "         " << i + 1 << ".  " << memo[i] << "            " << endl;
	}
	cout << endl;
	cout << "  └ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┘";

}

void Memo::input()      // 데이터를 입력받아 memo벡터에 저장
{
	system("cls");
	string str;
	cout << "메모를 입력하시오" << endl;
	getline(cin, str);
	memo.push_back(str);
	system("cls");
}

void Memo::save()      // 입력받은 데이터를 텍스트파일에 저장
{
	ofstream fout("memo.txt");
	for (int i = 0; i < memo.size(); i++)
		fout << memo[i] << endl;
	fout.close();
}

void Memo::partdelete()      //원하는 메모 삭제 함수
{
	if (memo.size() == 0)
	{
		gotoxy(55, 20);
		cout << "  ===== 지울 메모가 없습니다 =====";
	}
	else
	{
		gotoxy(55, 19);
		cout << "※ 지우고자 하는 메모 번호를 입력하세요 (   ) ";
		int n;
		gotoxy(97, 19); cin >> n;

		while (n > memo.size() || n == 0)
		{
			gotoxy(55, 20);
			cout << "※ 다시 선택하세요." << endl;
			Sleep(500);
			gotoxy(55, 19);
			cout << "※ 지우고자 하는 메모 번호를 입력하세요 (   ) ";
			gotoxy(97, 19); cin >> n;
		}

		memo.erase(memo.begin() + n - 1);
		gotoxy(55, 20);
		cout << n << " 번 메모가 삭제되었습니다." << endl << endl;
		system("cls");
	}
}

vector<string> Memo::getMemo()   // 다른 기능 클래스에서 사용하기 위해 getMemo함수를 통해 memo벡터 반환
{
	return memo;
}

const string currentDateTime() // 현재시간 함수
{
	time_t now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct); // YYYY-MM-DD 형태의 스트링
	return buf;
}

void D_DAY::howToUse() {
	cout << "**************************************** [D-DAY] 메모 사용법 ****************************************" << endl << endl;
	cout << "1. 날짜를 지정해 놓은 메모들의 D-Day를 알려줍니다." << endl;
	cout << "2. D-Day를 자동으로 설정 하고 싶다면 날짜를 'mm/dd' 형식으로 메모를 입력하시면 됩니다." << endl;
	cout << "3. 날짜는 앞 뒤로 공백을 구분으로 합니다." << endl;
	cout << "\n\t예) 7/15 출장, 고프 프로젝트 제출 6/17";
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
			int today_month = 0, today_day = 0;                              //오늘 월과 달 변수

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
	vector <string> memo = temp;    //텍스트파일에서 받아와서 벡터에 저장
	string today;                   // 오늘날짜
	cout << "******************** [ D_DAY ] 메모 ********************" << endl << endl;

	cout << "오늘 날짜\n20";
	today = currentDateTime();
	for (int t = 2; t < 10; t++) {
		if ((t % 3) != 1)
			cout << today[t];
		else
			cout << '/';
	}
	cout << "\n\n";
	//오늘 날짜 출력
	separate(memo, today);
}
void Debt::print(vector <string> memo)
{
	vector <int> repay; //갚을돈 배열
	vector <int> recieve; //받을돈 배열

	cout << "******************** [ 채무 ] 메모 ********************" << endl << endl;
	string a, b;
	int n, m;
	int sum1 = 0;
	int sum2 = 0;

	//메모된 내용에서 '\'라는 문자를 채무 메모 전체를 찾아 출력
	for (int i = 0; i < memo.size(); i++)
	{

		if (memo[i].find("\\") != string::npos)
		{
			cout << memo[i] << endl;
		}

	}
	//채무 메모 중 '갚기' 문자열을 찾아 숫자부분만 추출하여 갚을돈 배열에 할당
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

			if (memo[i].find("갚기") != string::npos)
			{

				for (int j = index; j < memo[i].length(); j++)
				{
					// 48 ~ 57은 아스키 코드로 0~9이다. 숫자부분(금액)만 추출
					if (48 <= memo[i].at(j) && memo[i].at(j) <= 57)
						a += memo[i].at(j);
				}

				n = std::stoi(a); //금액만 추출하여 갚을돈 int변수로 변환
				repay.push_back(n); //갚을돈 배열
				a = '0'; //변수 초기화

			}
			else //나머지인 경우 ('받기' 문자열을 찾았을때)
			{

				for (int j = index; j < memo[i].length(); j++)
				{

					// 48 ~ 57은 아스키 코드로 0~9이다.
					if (48 <= memo[i].at(j) && memo[i].at(j) <= 57)
						b += memo[i].at(j);
				}

				m = std::stoi(b); //금액만 추출하여 받을돈 int변수로 변환
				recieve.push_back(m); //받을돈 배열
				b = '0'; //변수 초기화

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
	cout << endl << "*** 갚을 돈 : \\" << sum1 << "원   받을 돈 : \\" << sum2 << "원 ***" << endl;

}
void Debt::howToUse()
{
	cout << "**************************************** [ 채무 ] 메모 사용법 ****************************************" << endl << endl;
	cout << "1. HOME 메뉴에서 메모 추가로 등록 시에 메모 성격을 위해 금액 첫부분에 '\\' 문구를 입력합니다.\n";
	cout << "2. '갚기'와 '받기'의 문구를 입력하여 메모 등록을 합니다.\n";
	cout << "\tex)재인이에게 \\1500원 받기\n";
	cout << "3. 마지막 줄에는 '갚을 돈'과 '받을 돈'의 각각의 총 합계를 보여드립니다.\n";
}

Sign::Sign()
{
	//////////텍스트 파일에 저장된 Sign Code를 불러옴
	ifstream fin_Signcode;
	fin_Signcode.open("SignCode.txt");
	if (fin_Signcode.fail())//현재 만들어진 code 텍스트 파일이 없는 경우 알림을 띄우고 벡터 변수에 불러들이는 작업을 건너뛴다
	{
		system("cls");
	}
	else
	{
		string tmpstr;//텍스트파일에서 내용을 읽어들일때 쓰일 임시 문자열
		while (fin_Signcode)//fin이 파일의 끝(0)을 만나면 반복문 탈출
		{
			getline(fin_Signcode, tmpstr);
			code.push_back(tmpstr);
		}
		//↓↓↓텍스트 파일에서 읽어들인 마지막 개행문자가 code로 인식되므로 벡터의 마지막 인덱스를 지워줌
		code.erase(code.begin() + (code.size() - 1));
		fin_Signcode.close();
	}
	///////////텍스트 파일에 저장된 code의 기능에 대한 데이터를 불러옴
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
	cout << "**************************************** [DIY Sign Code] 메모 사용법 ****************************************" << endl << endl;
	cout << "1. Code추가 메뉴에서 원하는 기호를 추가하십시오" << endl;
	cout << "2. 기호에 해당하는 기능을 선택하십시오" << endl;
	cout << "3. 알람기능을 선택한 경우 기호와 날짜의 조합으로 메모를 작성하십시오 " << endl;
	cout << "e.g.) # 6/21 종강총회   ->   6월21일에 메모내용을 화면에 띄워 알람기능을 한다.";

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
			cout << "오늘은 " << codeMemo[i] << " 이 있는 날입니다" << endl;

		}
		if (i == codeMemo.size() - 1 && c>0)
		{
			cout << endl << endl << endl << endl << "1번을 눌러 메인화면으로";
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
		cout << "현재 설정된 Sign code" << endl;
		if (code.size() == 0)//code벡터크기가 0이면 설정된 code가 없는 상태
			cout << "설정된 code가 없습니다" << endl;
		for (int i = 0; i < code.size(); i++)//code벡터의 내용을 모두 출력
			cout << code[i] << " : " << codeFunc[i] << "기능" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "1.Code추가 2.Code삭제 3.Code가 포함된 메모 4.사용법 5.돌아가기" << endl;
		char num;//메뉴를 입력받는 변수 1.추가 2.삭제 3.메모화면
		cin >> num; system("cls");
		if (num == '1')//////////////////////////code추가
		{
			cout << "추가할 코드 입력 : ";
			string c; cin >> c;
			code.push_back(c);
			system("cls");
			while (true) {
				cout << "원하는 기능의 번호를 입력하시오(1.알람 2.미정1 3.미정2)" << endl << "e.x. 알람기능 ->" << c << " 6/20 : 6/20일에 해당 메모 내용 알람" << endl;

				char n; cin >> n;
				if (n == '1') {
					codeFunc.push_back("알람");
				}
				else if (n == '2') {
					codeFunc.push_back("미정1");
				}
				else if (n == '3') {
					codeFunc.push_back("미정2");
				}
				else {
					cout << "1,2,3 중에서 입력하시오" << endl; Sleep(500); system("cls"); continue;
				}
				break;
			}
		}
		else if (num == '2')///////////////////////////////code삭제
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
			cout << "1을 눌러서 뒤로가기";
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
		else if (num == '5')////////////////////////////////sign code를 텍스트 파일에 저장하고 초기 메모 화면으로 돌아간다
		{
			///////////변수에 저장된 Sign Code 들을 텍스트 파일에 저장
			ofstream fout_Signcode;
			fout_Signcode.open("SignCode.txt");//현재 등록되어 있는 code들을 텍스트 파일에 저장한다.
			for (int i = 0; i < code.size(); i++)
				fout_Signcode << code[i] << endl;
			fout_Signcode.close();
			//////////변수에 저장된 code 의 기능을 텍스트 파일에 저장
			ofstream fout_codeFunc;
			fout_codeFunc.open("codeFunc.txt");
			for (int i = 0; i < codeFunc.size(); i++)
				fout_codeFunc << codeFunc[i] << endl;
			fout_codeFunc.close();
			break;
		}

		else///////////////////////////경고문을 1초동안 띄운 후 다시 번호를 입력 받음
		{
			cout << "1~3번 중에 입력하시오" << endl;
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
	for (int i = 0; i < code.size(); i++)//넘겨받은 문자열의 앞에 저장된 code중 일치하는 문자가 있는지 확인
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