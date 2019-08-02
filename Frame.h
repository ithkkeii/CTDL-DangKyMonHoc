#include <windows.h>
#include <stdio.h>	
#include <conio.h>	
#define LEFT -75	
#define RIGHT -77	
#define ENTER 13 
#define ESC 27
#define DELETE -83
#define DELETE -83

void ThongTin() {
	SetColor(5);
	SetBGColor(7);
	gotoxy(35, 1); cout << "                                                  ";
	gotoxy(35, 2); cout << "        CHUONG TRINH QUAN LY DIEM SINH VIEN       ";
	gotoxy(35, 3); cout << "                   THEO HE TIN CHI                ";

}

void KhungNhapLopTinChi() {
	gotoxy(0, 0);
	SetColor(5);
	SetBGColor(7);
	cout << "\n\n\n\n";
	cout << "\n         +-----------------------------------------------------------------------------+";
	cout << "\n         |	      |                |	     |        |      |        |        |";
	cout << "\n         +------------+----------------+-------------+--------+------+--------+--------|";
	cout << "\n         |            |                |             |        |      |        |        |";
	cout << "\n         |-----------------------------------------------------------------------------|";

	SetColor(1);
	gotoxy(33, 1);
	cout << "    ----------------------    ";
	gotoxy(33, 2);
	cout << "    | NHAP DANH SACH LOP |    ";
	gotoxy(33, 3);
	cout << "    ----------------------    ";

	gotoxy(11, 6);
	cout << "MA LOP TC";
	gotoxy(26, 6);
	cout << "MA MON HOC";
	gotoxy(42, 6);
	cout << "NIEN KHOA";
	gotoxy(55, 6);
	cout << "HOC KY";
	gotoxy(64, 6);
	cout << "NHOM";
	gotoxy(71, 6);
	cout << "SV MIN";
	gotoxy(80, 6);
	cout << "SV MAX";

	gotoxy(4, 36);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(20, 36);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(36, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(62, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F2-F3";

	//gotoxy(60, 24);
	//SetColor(15);
	//SetBGColor(8);
	//cout << " SAVEFILE ";
	//SetColor(1);
	//SetBGColor(7);
	//cout << ":F1";

	gotoxy(0, 27);
	return;
}
void KhungChinhLopTinChi() {
	gotoxy(0, 0);
	SetColor(5);
	SetBGColor(7);
	cout << "\n\n\n\n";
	cout << "\n   +-----------------------------------------------------------------------------------+";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |-----+------------+----------------+-------------+--------+------+--------+--------|";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |     |            |                |             |        |      |        |        |";
	cout << "\n   |-----------------------------------------------------------------------------------|";
	cout << "\n   |                                                                                   |";
	cout << "\n   |                                                                                   |";
	cout << "\n   |                                                                                   |";
	cout << "\n   +-----------------------------------------------------------------------------------+";

	SetColor(1);
	gotoxy(32, 1);
	cout << "    -----------------    ";
	gotoxy(32, 2);
	cout << "    | DANH SACH LOP |    ";
	gotoxy(32, 3);
	cout << "    -----------------    ";

	//Mode
	SetColor(4);
	SetBGColor(7);
	gotoxy(12, 1);
	cout << "    ---------------    ";
	gotoxy(12, 2);
	cout << "    |  VIEW MODE  |    ";
	gotoxy(12, 3);
	cout << "    ---------------    ";

	SetColor(4);
	SetBGColor(7);
	gotoxy(12, 1);
	cout << "    ---------------    ";
	gotoxy(12, 2);
	cout << "    |  EDIT MODE  |    ";
	gotoxy(12, 3);
	cout << "    ---------------    ";

	SetColor(4);
	SetBGColor(7);
	gotoxy(12, 1);
	cout << "    ---------------    ";
	gotoxy(12, 2);
	cout << "    | DELETE MODE |    ";
	gotoxy(12, 3);
	cout << "    ---------------    ";



	SetColor(1);
	gotoxy(11, 6);
	cout << "MA LOP TC";
	gotoxy(26, 6);
	cout << "MA MON HOC";
	gotoxy(42, 6);
	cout << "NIEN KHOA";
	gotoxy(55, 6);
	cout << "HOC KY";
	gotoxy(64, 6);
	cout << "NHOM";
	gotoxy(71, 6);
	cout << "SV MIN";
	gotoxy(80, 6);
	cout << "SV MAX";

	gotoxy(5, 24);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(25, 24);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(45, 24);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(70, 26);
	SetColor(15);
	SetBGColor(6);
	cout << " CHOOSE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":UP-DOWN";

	gotoxy(5, 26);
	SetColor(15);
	SetBGColor(9);
	cout << " SAVEFILE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F1";

	gotoxy(25, 26);
	SetColor(4);
	SetBGColor(14);
	cout << " EDIT ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F2";

	gotoxy(45, 26);
	SetColor(4);
	SetBGColor(14);
	cout << " DELETE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F3";
	return;
}

void SetMode(bool viewMode, bool editMode, bool deleteMode) {		//view 1, edit 2, delete 3
	int choice = (viewMode) ? 1 : (editMode) ? 2 : 3;
	switch (choice) {
	case 1:
		//set name
		SetColor(4);
		SetBGColor(7);
		gotoxy(12, 1);
		cout << "    ---------------    ";
		gotoxy(12, 2);
		cout << "    |  VIEW MODE  |    ";
		gotoxy(12, 3);
		cout << "    ---------------    ";

		//off up-down
		gotoxy(70, 26);
		SetColor(15);
		SetBGColor(6);
		cout << " CHOOSE ";
		SetColor(1);
		SetBGColor(7);
		cout << ":UP-DOWN";

		//off enter
		gotoxy(25, 24);
		SetColor(15);
		SetBGColor(2);
		cout << " ENTER ";
		SetColor(1);
		SetBGColor(7);
		cout << ":OK";

		break;
	case 2:

		//set name
		SetColor(4);
		SetBGColor(7);
		gotoxy(12, 1);
		cout << "    ---------------    ";
		gotoxy(12, 2);
		cout << "    |  EDIT MODE  |    ";
		gotoxy(12, 3);
		cout << "    ---------------    ";

		//on up down
		gotoxy(70, 26);
		SetColor(15);
		SetBGColor(8);
		cout << " CHOOSE ";
		SetColor(1);
		SetBGColor(7);
		cout << ":UP-DOWN";

		//on enter
		gotoxy(25, 24);
		SetColor(15);
		SetBGColor(2);
		cout << " ENTER ";
		SetColor(1);
		SetBGColor(7);
		cout << ":OK";

		break;
	case 3:

		//set name
		SetColor(4);
		SetBGColor(7);
		gotoxy(12, 1);
		cout << "    ---------------    ";
		gotoxy(12, 2);
		cout << "    | DELETE MODE |    ";
		gotoxy(12, 3);
		cout << "    ---------------    ";

		//on up down
		gotoxy(70, 26);
		SetColor(15);
		SetBGColor(8);
		cout << " CHOOSE ";
		SetColor(1);
		SetBGColor(7);
		cout << ":UP-DOWN";

		//on enter
		gotoxy(25, 24);
		SetColor(15);
		SetBGColor(2);
		cout << " ENTER ";
		SetColor(1);
		SetBGColor(7);
		cout << ":OK";

		break;
	}
	return;
}

//Khung Xoa Lop Tin Chi
void KhungXoaLopTinChi() {

	SetColor(1);
	SetBGColor(7);
	gotoxy(105, 1);
	cout << "    ---------------------    ";
	gotoxy(105, 2);
	cout << "    |  XOA LOP TIN CHI  |    ";
	gotoxy(105, 3);
	cout << "    ---------------------    ";

	SetColor(5);
	SetBGColor(7);
	gotoxy(110, 5);
	cout << "+------------------+";
	gotoxy(110, 6);
	cout << "|    Nhap Ma Lop   |";
	gotoxy(110, 7);
	cout << "+------------------|";
	gotoxy(110, 8);
	cout << "|                  |";
	gotoxy(110, 9);
	cout << "+------------------+";

	gotoxy(110, 10);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":XOA";

	gotoxy(122, 10);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":HUY";

}
//Khung Xoa Tin Chi Bien Mat
void ClearKhungXoaTinChi() {
	SetBGColor(7);
	gotoxy(90, 1);
	cout << "                                                                  ";
	gotoxy(90, 2);
	cout << "                                                                  ";
	gotoxy(90, 3);
	cout << "                                                                  ";
	gotoxy(90, 4);
	cout << "                                                                  ";
	gotoxy(90, 5);
	cout << "                                                                  ";
	gotoxy(90, 6);
	cout << "                                                                  ";
	gotoxy(90, 7);
	cout << "                                                                  ";
	gotoxy(90, 8);
	cout << "                                                                  ";
	gotoxy(90, 9);
	cout << "                                                                  ";
	gotoxy(90, 10);
	cout << "                                                                  ";
	gotoxy(90, 11);
	cout << "                                                                  ";
	gotoxy(90, 12);
	cout << "                                                                  ";
	gotoxy(90, 13);
	cout << "                                                                  ";
	gotoxy(90, 14);
	cout << "                                                                  ";
	gotoxy(90, 15);
	cout << "                                                                  ";
	gotoxy(90, 16);
	cout << "                                                                  ";
	gotoxy(90, 17);
	cout << "                                                                  ";
	gotoxy(90, 18);
	cout << "                                                                  ";
	gotoxy(90, 19);
	cout << "                                                                  ";
	gotoxy(90, 20);
	cout << "                                                                  ";
	gotoxy(90, 21);
	cout << "                                                                  ";
	gotoxy(90, 22);
	cout << "                                                                  ";
	gotoxy(90, 23);
	cout << "                                                                  ";
	gotoxy(90, 24);
	cout << "                                                                  ";
	gotoxy(90, 25);
	cout << "                                                                  ";
	gotoxy(90, 26);
	cout << "                                                                  ";
	gotoxy(90, 27);
	cout << "                                                                  ";
	return;
}
//

//Khung Sua Lop Tin Chi
void KhungSuaLopTinChi() {

	SetColor(1);
	SetBGColor(7);
	gotoxy(105, 1);
	cout << "    ---------------------    ";
	gotoxy(105, 2);
	cout << "    |  SUA LOP TIN CHI  |    ";
	gotoxy(105, 3);
	cout << "    ---------------------    ";

	SetColor(5);
	SetBGColor(7);
	gotoxy(110, 5);
	cout << "+------------------+";
	gotoxy(110, 6);
	cout << "|    Nhap Ma Lop   |";
	gotoxy(110, 7);
	cout << "+------------------|";
	gotoxy(110, 8);
	cout << "|                  |";
	gotoxy(110, 9);
	cout << "+------------------+";

	gotoxy(110, 10);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":SUA";

	gotoxy(122, 10);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":HUY";
	return;
}
void KhungConSuaLopTinChi() {
	gotoxy(90, 12);
	SetColor(5);
	SetBGColor(7);
	cout << "+--------------------------------------------------+";
	gotoxy(90, 13);
	cout << "|	      |          |      |      |      |      |";
	gotoxy(90, 14);
	cout << "+-----------+----------+------+------+------+------|";
	gotoxy(90, 15);
	cout << "|           |          |      |      |      |      |";
	gotoxy(90, 16);
	cout << "|--------------------------------------------------|";

	gotoxy(92, 13);
	cout << "MA MON HOC";
	gotoxy(103, 13);
	cout << "NIEN KHOA";
	gotoxy(114, 13);
	cout << "HOC KY";
	gotoxy(122, 13);
	cout << "NHOM";
	gotoxy(128, 13);
	cout << "SV MIN";
	gotoxy(135, 13);
	cout << "SV MAX";
	return;
}
//

void DeleteKhungInDSDK() {
	for (int i = 11; i < 37; i++) {
		gotoxy(4, i);
		cout << "                                                                                               ";
	}
	return;
}
//Khung in DSDK
void KhungInDSDK() {
	gotoxy(0, 0);
	SetColor(5);
	SetBGColor(7);
	cout << "\n\n\n\n";
	cout << "\n                      +----------------------------------------------+                  ";
	cout << "\n                      |                |	     |        |      |                  ";
	cout << "\n                      +----------------+-------------+--------+------+                  ";
	cout << "\n                      |                |             |        |      |                  ";
	cout << "\n                      |----------------------------------------------|                  ";

	SetColor(1);
	gotoxy(30, 1);
	cout << "    ------------------------------    ";
	gotoxy(30, 2);
	cout << "    | NHAP THONG TIN LOP TIN CHI |    ";
	gotoxy(30, 3);
	cout << "    ------------------------------    ";


	gotoxy(26, 6);
	cout << "MA MON HOC";
	gotoxy(42, 6);
	cout << "NIEN KHOA";
	gotoxy(55, 6);
	cout << "HOC KY";
	gotoxy(64, 6);
	cout << "NHOM";


	return;
}

void ButtonKhungInDSDK() {
	gotoxy(4, 36);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(20, 36);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(36, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(60, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F2-F3";
}

void KhungInDSDKCon() {
	gotoxy(0, 6);
	SetColor(5);
	SetBGColor(7);
	cout << "\n\n\n\n";
	cout << "\n   +--------------------------------------------------------------------------------+";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |------------+-------------+----------------+----------+----+-------+------------|";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |            |             |                |          |    |       |            |";
	cout << "\n   |--------------------------------------------------------------------------------|";
	cout << "\n                                                                              +     +";
	cout << "\n                                                                              +-----+";



	SetColor(1);
	gotoxy(6, 12);
	cout << "MA LOP";
	gotoxy(20, 12);
	cout << "MA SV";
	gotoxy(33, 12);
	cout << "HO SINH VIEN";
	gotoxy(50, 12);
	cout << "TEN SV";
	gotoxy(59, 12);
	cout << "PHAI";
	gotoxy(65, 12);
	cout << "N.HOC";
	gotoxy(76, 12);
	cout << "SDT";

	gotoxy(4, 36);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(25, 36);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(45, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";
	return;
}
//--------------------------------

//Khung Quan Ly Sinh Vien
void KhungThemSinhVien() {
	gotoxy(8, 4);
	SetColor(5);
	SetBGColor(7);
	cout << "                              +------------------+";
	gotoxy(8, 5);
	cout << "                              |                  |";
	gotoxy(8, 6);
	cout << "                              +------------------+";
	gotoxy(8, 7);
	cout << "                              |                  |";
	gotoxy(8, 8);

	gotoxy(0, 4);
	SetColor(5);
	SetBGColor(7);
	cout << "\n\n\n\n";
	cout << "\n        +--------------------------------------------------------------------------------+";
	cout << "\n        |             |                      |                |       |            |     |   ------";
	cout << "\n        +-------------+----------------------+----------------+-------+------------+-----|   |    |";
	cout << "\n        |             |                      |                |       |            |     |   ------";
	cout << "\n        |--------------------------------------------------------------------------------|";

	SetColor(1);
	gotoxy(33, 1);
	cout << "    ----------------------    ";
	gotoxy(33, 2);
	cout << "    | NHAP LOP SINH VIEN |    ";
	gotoxy(33, 3);
	cout << "    ----------------------    ";
	gotoxy(45, 5);
	cout << "MA LOP";

	gotoxy(9, 10);
	cout << "MA SINH VIEN";
	gotoxy(28, 10);
	cout << "HO SINH VIEN";
	gotoxy(47, 10);
	cout << "TEN SINH VIEN";
	gotoxy(64, 10);
	cout << "N.HOC";
	gotoxy(75, 10);
	cout << "SDT";

	gotoxy(85, 10);
	cout << "NAM";
	gotoxy(85, 12);
	cout << "NU";

	SetColor(15);
	SetBGColor(8);
	gotoxy(94, 11);
	cout << " OK ";

	gotoxy(2, 41);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(18, 41);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(34, 41);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(58, 41);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F2-F3";

	return;
}

void TurnOKButton(bool state) {
	if (state) {
		SetColor(4);
		SetBGColor(2);
		gotoxy(94, 11);
		cout << " OK ";
	} else {
		SetColor(15);
		SetBGColor(8);
		gotoxy(94, 11);
		cout << " OK ";
	}
	return;
}

void KhungDSachSV() {
	gotoxy(0, 12);
	SetColor(5);
	SetBGColor(7);
	cout << "\n";
	cout << "\n   +-------------------------+";
	cout << "\n   | MA LOP:                 |";
	cout << "\n   +-------------------------+";
	cout << "\n   +-------------------------------------------------------------------------------------+";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   +----+-------------+----------------------+----------------+-------+------------+-----|";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |    |             |                      |                |       |            |     |";
	cout << "\n   |-------------------------------------------------------------------------------------|";
	cout << "\n                                                                                 +       +";
	cout << "\n                                                                                 +-------+";
	SetColor(1);
	gotoxy(4, 18);
	cout << "STT";
	gotoxy(9, 18);
	cout << "MA SINH VIEN";
	gotoxy(28, 18);
	cout << "HO SINH VIEN";
	gotoxy(47, 18);
	cout << "TEN SINH VIEN";
	gotoxy(64, 18);
	cout << "N.HOC";
	gotoxy(75, 18);
	cout << "SDT";
	gotoxy(84, 18);
	cout << "GIOI";
}

void KhungXoaSinhVien() {
	gotoxy(8, 4);
	SetColor(5);
	SetBGColor(7);
	cout << "                               +---------------+";
	gotoxy(8, 5);
	cout << "                               |               |";
	gotoxy(8, 6);
	cout << "                               +---------------+";
	gotoxy(8, 7);
	cout << "                               |               |";
	gotoxy(8, 8);
	cout << "                               +---------------+";

	SetColor(1);
	gotoxy(33, 1);
	cout << "    ----------------------    ";
	gotoxy(33, 2);
	cout << "    |    XOA SINH VIEN   |    ";
	gotoxy(33, 3);
	cout << "    ----------------------    ";

	gotoxy(44, 5);
	cout << "MA LOP";

	gotoxy(2, 41);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(18, 41);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(34, 41);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(58, 41);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F2-F3";
	return;
}

void ButtonXacNhanXoa(bool choice = false) {
	SetBGColor(6);
	SetColor(15);
	gotoxy(38, 10);
	cout << "+-----------------+";
	gotoxy(38, 11);
	cout << "|  BAN MUON XOA?  |";
	gotoxy(38, 12);
	cout << "|-----------------|";
	gotoxy(38, 13);
	cout << "|        |        |";
	gotoxy(38, 14);
	cout << "+-----------------+";
	if (choice == true) {
		SetBGColor(4);
		SetColor(15);
		gotoxy(39, 13);
		cout << " [YES]  ";

		SetBGColor(8);
		SetColor(15);
		gotoxy(48, 13);
		cout << "  [NO]  ";
	}
	if (choice == false) {
		SetBGColor(8);
		SetColor(15);
		gotoxy(39, 13);
		cout << " [YES]  ";

		SetBGColor(4);
		SetColor(15);
		gotoxy(48, 13);
		cout << "  [NO]  ";
	}
	return;
}

void KhungHuongDanInDSSV() {
	gotoxy(20, 36);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(35, 36);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(50, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";
	return;
}

void KhungInDSSV() {
	gotoxy(8, 4);
	SetColor(5);
	SetBGColor(7);
	cout << "                               +---------------+";
	gotoxy(8, 5);
	cout << "                               |               |";
	gotoxy(8, 6);
	cout << "                               +---------------+";
	gotoxy(8, 7);
	cout << "                               |               |";
	gotoxy(8, 8);
	cout << "                               +---------------+";

	SetColor(1);
	gotoxy(33, 1);
	cout << "    ------------------------    ";
	gotoxy(33, 2);
	cout << "    |IN DANH SACH SINH VIEN|    ";
	gotoxy(33, 3);
	cout << "    ------------------------    ";

	gotoxy(44, 5);
	cout << "MA LOP";

	KhungHuongDanInDSSV();
	return;
}

void KhungGoiYLop() {
	SetColor(5);
	SetBGColor(7);
	gotoxy(38, 12);
	cout << "+-----------------+";
	gotoxy(38, 13);
	cout << "|                 |";
	gotoxy(38, 14);
	cout << "+-----------------|";
	gotoxy(38, 15);
	cout << "|                 |";
	gotoxy(38, 16);
	cout << "|                 |";
	gotoxy(38, 17);
	cout << "|                 |";
	gotoxy(38, 18);
	cout << "|                 |";
	gotoxy(38, 19);
	cout << "|                 |";
	gotoxy(38, 20);
	cout << "|                 |";
	gotoxy(38, 21);
	cout << "|                 |";
	gotoxy(38, 22);
	cout << "|                 |";
	gotoxy(38, 23);
	cout << "+-----------------+";
	gotoxy(38, 24);
	cout << "          +       +";
	gotoxy(38, 25);
	cout << "          +-------+";
	return;
}
//---------------------------------


//Khung Quan Ly Mon Hoc
void KhungThemMonHoc(string choice = "them") {
	SetColor(5);
	SetBGColor(7);
	gotoxy(10, 4);
	cout << "+-----------------------------------------------------------------------+";
	gotoxy(10, 5);
	cout << "|             |                                       |        |        |   ------";
	gotoxy(10, 6);
	cout << "+-------------+---------------------------------------+--------+--------|   |    |";
	gotoxy(10, 7);
	cout << "|             |                                       |        |        |   ------";
	gotoxy(10, 8);
	cout << "|-----------------------------------------------------------------------|";

	if (choice == "them") {
		SetColor(4);
		gotoxy(33, 1);
		cout << "    ----------------------    ";
		gotoxy(33, 2);
		cout << "    |    THEM MON HOC    |    ";
		gotoxy(33, 3);
		cout << "    ----------------------    ";
	}
	if (choice == "sua") {
		SetColor(4);
		gotoxy(33, 1);
		cout << "    ----------------------    ";
		gotoxy(33, 2);
		cout << "    |    SUA MON HOC     |    ";
		gotoxy(33, 3);
		cout << "    ----------------------    ";
	}

	SetColor(1);
	SetBGColor(7);
	gotoxy(12, 5);
	cout << "MA MON HOC";
	gotoxy(41, 5);
	cout << "TEM MON HOC";

	gotoxy(65, 5);
	cout << "T.CHI LT";

	gotoxy(74, 5);
	cout << "T.CHI TH";

	SetColor(15);
	SetBGColor(8);
	gotoxy(87, 6);
	cout << " OK ";
	return;
}

void KhungDSMonHoc(string choice = "") {
	gotoxy(0, 10);
	SetColor(5);
	SetBGColor(7);
	cout << "\n          +-----------------------------------------------------------------------+";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          +-------------+---------------------------------------+-----------------|";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |             |                                       |        |        |";
	cout << "\n          |-----------------------------------------------------------------------|";
	cout << "\n                                                                          +       +";
	cout << "\n                                                                          +-------+";
	SetColor(2);
	gotoxy(12, 12);
	cout << "MA MON HOC";
	gotoxy(41, 12);
	cout << "TEN MON HOC";
	gotoxy(65, 12);
	cout << "T.CHI LT";
	gotoxy(74, 12);
	cout << "T.CHI TH";

	if (choice == "IN") {
		SetColor(4);
		gotoxy(33, 1);
		cout << "    ----------------------    ";
		gotoxy(33, 2);
		cout << "    |IN DANH SACH MON HOC|    ";
		gotoxy(33, 3);
		cout << "    ----------------------    ";
	}

	return;
}

void HuongDanThemMonHoc() {
	gotoxy(12, 36);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(27, 36);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(41, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F2-F3";

	gotoxy(64, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";
	return;
}

void TurnOKButtonKhungMonHoc(bool state) {
	if (state) {
		SetColor(4);
		SetBGColor(2);
		gotoxy(87, 6);
		cout << " OK ";
	} else {
		SetColor(15);
		SetBGColor(8);
		gotoxy(87, 6);
		cout << " OK ";
	}
	return;
}

void TurnOKButtonKhungXoaMonHoc(bool state) {
	if (state) {
		SetColor(4);
		SetBGColor(2);
		gotoxy(63, 6);
		cout << " OK ";
	} else {
		SetColor(15);
		SetBGColor(8);
		gotoxy(63, 6);
		cout << " OK ";
	}
	return;
}

void KhungXoaMonHoc() {
	SetColor(5);
	SetBGColor(7);
	gotoxy(10, 4);
	cout << "                           +--------------------+";
	gotoxy(10, 5);
	cout << "                           |                    |   ------";
	gotoxy(10, 6);
	cout << "                           +--------------------+   |    |";
	gotoxy(10, 7);
	cout << "                           |                    |   ------";
	gotoxy(10, 8);
	cout << "                           |--------------------|";

	SetColor(4);
	gotoxy(33, 1);
	cout << "    ----------------------    ";
	gotoxy(33, 2);
	cout << "    |    XOA MON HOC     |    ";
	gotoxy(33, 3);
	cout << "    ----------------------    ";

	SetColor(1);
	SetBGColor(7);
	gotoxy(42, 5);
	cout << "MA MON HOC";

	SetColor(15);
	SetBGColor(8);
	gotoxy(63, 6);
	cout << " OK ";
	return;
}

void HuongDanInDSMH() {
	gotoxy(12, 36);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(27, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";
	return;
}
//----------------------

//Khung đăng ký môn học
void KhungDangNhap() {
	SetBGColor(7);
	SetColor(4);
	gotoxy(33, 1);
	cout << "    ----------------------    ";
	gotoxy(33, 2);
	cout << "    |  DANG KY MON HOC   |    ";
	gotoxy(33, 3);
	cout << "    ----------------------    ";

	SetColor(3);
	gotoxy(10, 5);
	cout << "+--------------------+";
	gotoxy(10, 6);
	cout << "|                    |     +-----------+";
	gotoxy(10, 7);
	cout << "+--------------------+     |           |";
	gotoxy(10, 8);
	cout << "|                    |     +-----------+";
	gotoxy(10, 9);
	cout << "+--------------------+";

	SetColor(5);
	gotoxy(15, 6);
	cout << "MA SINH VIEN";
	gotoxy(39, 7);
	cout << "DANG NHAP";

	return;
}

void KhungTimKiem() {
	SetColor(4);
	SetBGColor(7);
	gotoxy(33, 1);
	cout << "    ----------------------    ";
	gotoxy(33, 2);
	cout << "    |  DANG KY MON HOC   |    ";
	gotoxy(33, 3);
	cout << "    ----------------------    ";

	SetBGColor(7);
	SetColor(3);
	gotoxy(10, 5);
	cout << "+--------------------+--------------------+";
	gotoxy(10, 6);
	cout << "|                    |                    |     +-----------+";
	gotoxy(10, 7);
	cout << "+--------------------+--------------------+     |           |";
	gotoxy(10, 8);
	cout << "|                    |                    |     +-----------+";
	gotoxy(10, 9);
	cout << "+--------------------+--------------------+";

	SetColor(5);
	gotoxy(16, 6);
	cout << "NIEN KHOA";
	gotoxy(39, 6);
	cout << "HOC KY";
	gotoxy(60, 7);
	cout << "TIM KIEM";

	return;
}

void TongleDangNhap(bool choice = false) {
	if (choice) {
		SetColor(15);
		SetBGColor(2);
		gotoxy(38, 7);
		cout << " DANG NHAP ";
	}
	if (!choice) {
		SetColor(15);
		SetBGColor(8);
		gotoxy(38, 7);
		cout << " DANG NHAP ";
	}
}

void TongleTimKiem(bool choice = false) {
	if (choice) {
		SetColor(15);
		SetBGColor(2);
		gotoxy(59, 7);
		cout << " TIM KIEM  ";
	}
	if (!choice) {
		SetColor(15);
		SetBGColor(8);
		gotoxy(59, 7);
		cout << " TIM KIEM  ";
	}
	return;
}

void KhungChonLopTinChi() {
	gotoxy(0, 12);
	SetColor(5);
	SetBGColor(7);
	cout << "\n          +------------------------------------------------------------------------------+";
	cout << "\n          |          |                                        |        |     |     |     |";
	cout << "\n    +---+ +----------+----------------------------------------+--------+-----+-----+-----|";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    |   | |          |                                        |        |     |     |     |";
	cout << "\n    +---+ |----------|----------------------------------------|--------|-----|-----|-----|";
	cout << "\n                                                                                 +       +";
	cout << "\n                                                                                 +-------+";

	SetColor(6);
	gotoxy(11, 14);
	cout << "MA MON HOC";
	gotoxy(30, 14);
	cout << "TEN MON HOC";
	gotoxy(65, 14);
	cout << "SVMAX";
	gotoxy(72, 14);
	cout << "TCLT";
	gotoxy(78, 14);
	cout << "TCTH";
	gotoxy(84, 14);
	cout << "NHOM";

	return;
}

void KhungLuuLuaChon() {
	int x = 95;
	int y = 13;
	SetColor(5);
	SetBGColor(7);
	gotoxy(x, y);
	cout << "+---------------------------------------------------------------------+";
	gotoxy(x, y + 1);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 2);
	cout << "+----------+----------------------------------------+-----+-----+-----|";
	gotoxy(x, y + 3);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 4);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 5);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 6);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 7);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 8);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 9);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 10);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 11);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 12);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 13);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 14);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 15);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 16);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 17);
	cout << "|          |                                        |     |     |     |";
	gotoxy(x, y + 18);
	cout << "|----------|----------------------------------------|-----|-----|-----|";
	gotoxy(x, y + 19);
	cout << "                                                              +       +";
	gotoxy(x, y + 20);
	cout << "                                                              +-------+";

	SetColor(6);
	gotoxy(96, 14);
	cout << "MA MON HOC";
	gotoxy(120, 14);
	cout << "TEN MON HOC";
	gotoxy(148, 14);
	cout << "TCLT";
	gotoxy(154, 14);
	cout << "TCTH";
	gotoxy(160, 14);
	cout << "NHOM";
}

void ButtonKhungLuuLuaChon(bool choice = false) {
	if (choice) {
		gotoxy(96, 34);
		SetColor(15);
		SetBGColor(2);
		cout << " ENTER ";
		SetColor(1);
		SetBGColor(7);
		cout << ":XOA";

		gotoxy(115, 34);
		SetColor(15);
		SetBGColor(1);
		cout << " F1 ";
		SetColor(1);
		SetBGColor(7);
		cout << ":DANG KY";

		gotoxy(132, 34);
		SetColor(15);
		SetBGColor(4);
		cout << " ESC ";
		SetColor(1);
		SetBGColor(7);
		cout << ":THOAT";


		//Nút bên trái
		gotoxy(26, 34);
		SetColor(15);
		SetBGColor(8);
		cout << " ENTER ";
		SetColor(1);
		SetBGColor(7);
		cout << ":XOA";

		gotoxy(45, 34);
		SetColor(15);
		SetBGColor(8);
		cout << " F4 ";
		SetColor(1);
		SetBGColor(7);
		cout << ":CHUYEN";

		gotoxy(62, 34);
		SetColor(15);
		SetBGColor(8);
		cout << " ESC ";
		SetColor(1);
		SetBGColor(7);
		cout << ":THOAT";
	} else {
		gotoxy(96, 34);
		SetColor(15);
		SetBGColor(8);
		cout << " ENTER ";
		SetColor(1);
		SetBGColor(7);
		cout << ":XOA";

		gotoxy(115, 34);
		SetColor(15);
		SetBGColor(8);
		cout << " F1 ";
		SetColor(1);
		SetBGColor(7);
		cout << ":DANG KY";

		gotoxy(132, 34);
		SetColor(15);
		SetBGColor(8);
		cout << " ESC ";
		SetColor(1);
		SetBGColor(7);
		cout << ":THOAT";


		//Nút bên trái
		gotoxy(26, 34);
		SetColor(15);
		SetBGColor(2);
		cout << " ENTER ";
		SetColor(1);
		SetBGColor(7);
		cout << ":XOA";

		gotoxy(45, 34);
		SetColor(15);
		SetBGColor(1);
		cout << " F4 ";
		SetColor(1);
		SetBGColor(7);
		cout << ":CHUYEN";

		gotoxy(62, 34);
		SetColor(15);
		SetBGColor(4);
		cout << " ESC ";
		SetColor(1);
		SetBGColor(7);
		cout << ":THOAT";
	}

}

void TongChi(int tinChi, int tinChiMax) {
	gotoxy(70, 12);
	SetColor(2);
	SetBGColor(7);
	cout << "                       ";
	gotoxy(70, 12);
	cout << "Tong Tin Chi: " << tinChi << "/";
	SetColor(4);
	cout << tinChiMax;
	return;
}
//---------------------

//Khung Nhập Điểm
void KhungNhapDiem() {
	int x = 15;
	int y = 12;
	SetColor(5);
	SetBGColor(7);
	gotoxy(x, y);
	cout << "+--------------------------------------------------------------------+";
	gotoxy(x, y + 1);
	cout << "|STT |MA SINH VIEN |          HO SINH VIEN          | TEN SV  | DIEM |";
	gotoxy(x, y + 2);
	cout << "+----+-------------+--------------------------------+---------+------|";
	gotoxy(x, y + 3);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 4);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 5);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 6);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 7);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 8);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 9);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 10);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 11);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 12);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 13);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 14);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 15);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 16);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 17);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 18);
	cout << "|----|-------------|--------------------------------|---------|------|";
	gotoxy(x, y + 19);
	cout << "                                                             +       +";
	gotoxy(x, y + 20);
	cout << "                                                             +-------+";
	return;
}

void KhungNhapThongTinTimKiem() {
	SetColor(4);
	SetBGColor(7);
	gotoxy(33, 1);
	cout << "    ---------------------    ";
	gotoxy(33, 2);
	cout << "    |  NHAP THONG TIN   |    ";
	gotoxy(33, 3);
	cout << "    ---------------------    ";


	SetColor(5);
	SetBGColor(7);
	gotoxy(26, 5);
	cout << "+--------------------------------------------+";
	gotoxy(26, 6);
	cout << "|  MA MON HOC   | NIEN KHOA | HOC KY | NHOM  |";
	gotoxy(26, 7);
	cout << "+--------------------------------------------+";
	gotoxy(26, 8);
	cout << "|               |           |        |       |";
	gotoxy(26, 9);
	cout << "+--------------------------------------------+";
	return;
}

void ButtonNhapDiem() {
	gotoxy(12, 38);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(27, 38);
	SetColor(15);
	SetBGColor(2);
	cout << " CHOOSE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":ENTER";

	gotoxy(50, 38);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(75, 38);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":UP-DOWN";

	gotoxy(100, 38);
	SetColor(15);
	SetBGColor(1);
	cout << " SAVE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F1";
	return;
}

void KhungInTieuDe() {
	SetColor(4);
	SetBGColor(7);
	gotoxy(33, 1);
	cout << "                             ";
	gotoxy(33, 2);
	cout << "                             ";
	gotoxy(33, 3);
	cout << "                             ";

	SetColor(5);
	SetBGColor(7);
	gotoxy(26, 5);
	cout << "+-------------------------------------------------------+";
	gotoxy(26, 6);
	cout << "| BANG DIEM MON HOC:                                    |";
	gotoxy(26, 7);
	cout << "|                                                       |";
	gotoxy(26, 8);
	cout << "| NIEN KHOA:          HOC KY:      NHOM:                |";
	gotoxy(26, 9);
	cout << "+-------------------------------------------------------+";
	return;
}


//Khung In điểm trung bình khóa
void KhungHeader() {
	SetColor(4);
	SetBGColor(7);
	gotoxy(33, 1);
	cout << "    ---------------------    ";
	gotoxy(33, 2);
	cout << "    |  NHAP THONG TIN   |    ";
	gotoxy(33, 3);
	cout << "    ---------------------    ";
}

void KhungNhapMaLop() {
	SetColor(5);
	SetBGColor(7);
	gotoxy(39, 5);
	cout << "+---------------+";
	gotoxy(39, 6);
	cout << "|    MA LOP     |";
	gotoxy(39, 7);
	cout << "+---------------+";
	gotoxy(39, 8);
	cout << "|               |";
	gotoxy(39, 9);
	cout << "+---------------+";
}

void KhungPhanTrangDiemTB() {
	int x = 15;
	int y = 12;
	SetColor(5);
	SetBGColor(7);
	gotoxy(x, y);
	cout << "+--------------------------------------------------------------------+";
	gotoxy(x, y + 1);
	cout << "|STT |MA SINH VIEN |          HO SINH VIEN          | TEN SV  | DIEM |";
	gotoxy(x, y + 2);
	cout << "+----+-------------+--------------------------------+---------+------|";
	gotoxy(x, y + 3);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 4);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 5);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 6);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 7);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 8);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 9);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 10);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 11);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 12);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 13);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 14);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 15);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 16);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 17);
	cout << "|    |             |                                |         |      |";
	gotoxy(x, y + 18);
	cout << "|----|-------------|--------------------------------|---------|------|";
	gotoxy(x, y + 19);
	cout << "                                                             +       +";
	gotoxy(x, y + 20);
	cout << "                                                             +-------+";
	return;
}

void KhungTieuDeJ(char maLop[], int namNhapHoc) {
	SetColor(5);
	SetBGColor(7);
	gotoxy(26, 5);
	cout << "+-------------------------------------------------------+";
	gotoxy(26, 6);
	cout << "|       BANG THONG KE DIEM TRUNG BINH KHOA HOC          |";
	gotoxy(26, 7);
	cout << "|                                                       |";
	gotoxy(26, 8);
	cout << "|       LOP:                 NAM NHAP HOC:              |";
	gotoxy(26, 9);
	cout << "+-------------------------------------------------------+";

	SetColor(4);
	gotoxy(38, 8);
	cout << maLop;
	gotoxy(68, 8);
	cout << namNhapHoc;
}

void KhungTieuDeK(char maLop[]) {
	SetColor(5);
	SetBGColor(7);
	gotoxy(26, 5);
	cout << "+-------------------------------------------------------+";
	gotoxy(26, 6);
	cout << "|                 BANG DIEM TONG KET                    |";
	gotoxy(26, 7);
	cout << "|                                                       |";
	gotoxy(26, 8);
	cout << "|                 LOP:                                  |";
	gotoxy(26, 9);
	cout << "+-------------------------------------------------------+";

	SetColor(4);
	gotoxy(49, 8);
	cout << maLop;
}

void KhungPhanTrangDiemMAX() {
	int x = 15;
	int y = 12;
	SetColor(5);
	SetBGColor(7);
	gotoxy(x, y);
	cout << "+----------------------------------------------------------------------------------------------+";
	gotoxy(x, y + 1);
	cout << "|STT |MA SINH VIEN |          HO SINH VIEN          | TEN SV  |          |          |          |";
	gotoxy(x, y + 2);
	cout << "+----+-------------+--------------------------------+---------+----------+----------+----------|";
	gotoxy(x, y + 3);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 4);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 5);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 6);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 7);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 8);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 9);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 10);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 11);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 12);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 13);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 14);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 15);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 16);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 17);
	cout << "|    |             |                                |         |          |          |          |";
	gotoxy(x, y + 18);
	cout << "|----|-------------|--------------------------------|---------|----------|----------|----------|";
	gotoxy(x, y + 19);
	cout << "                                                      +       +                        +       +";
	gotoxy(x, y + 20);
	cout << "                                                      +-------+                        +-------+";


	gotoxy(20, 36);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(36, 36);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(52, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(78, 36);
	SetColor(15);
	SetBGColor(6);
	cout << " SWITCHPAGE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F2-F3";



	return;
}

