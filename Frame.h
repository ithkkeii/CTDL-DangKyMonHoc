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
	gotoxy(35, 2); cout << "          CHUONG TRINH QUAN LY SINH VIEN          ";
	gotoxy(35, 3); cout << "                                                  ";
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
	cout << "\n         +-----------------------------------------------------------------------------+";

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

	gotoxy(4, 24);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(20, 24);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(36, 24);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

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

	gotoxy(70, 24);
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

	gotoxy(70, 26);
	SetColor(4);
	SetBGColor(14);
	cout << " VIEW ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F4";

	gotoxy(0, 27);
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
		gotoxy(70, 24);
		SetColor(15);
		SetBGColor(8);
		cout << " CHOOSE ";
		SetColor(1);
		SetBGColor(7);
		cout << ":UP-DOWN";

		//off enter
		gotoxy(25, 24);
		SetColor(15);
		SetBGColor(8);
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
		gotoxy(70, 24);
		SetColor(15);
		SetBGColor(6);
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
		gotoxy(70, 24);
		SetColor(15);
		SetBGColor(6);
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
	gotoxy(105, 1);
	cout << "                               ";
	gotoxy(105, 2);
	cout << "                               ";
	gotoxy(105, 3);
	cout << "                               ";
	gotoxy(110, 5);
	cout << "                               ";
	gotoxy(110, 6);
	cout << "                               ";
	gotoxy(110, 7);
	cout << "                               ";
	gotoxy(110, 8);
	cout << "                               ";
	gotoxy(110, 9);
	cout << "                               ";
	gotoxy(110, 10);
	cout << "                               ";
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


	gotoxy(4, 24);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(20, 24);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(36, 24);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(0, 27);
	return;
}

void KhungInDSDKCon() {
	gotoxy(0, 8);
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




	SetColor(1);
	gotoxy(6, 14);
	cout << "MA LOP";
	gotoxy(20, 14);
	cout << "MA SV";
	gotoxy(33, 14);
	cout << "HO SINH VIEN";
	gotoxy(50, 14);
	cout << "TEN SV";
	gotoxy(59, 14);
	cout << "PHAI";
	gotoxy(65, 14);
	cout << "N.HOC";
	gotoxy(76, 14);
	cout << "SDT";

	gotoxy(5, 32);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(25, 32);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(45, 32);
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
	/*gotoxy(4, 24);
	SetColor(15);
	SetBGColor(4);
	cout << " ESC ";
	SetColor(1);
	SetBGColor(7);
	cout << ":Exit";

	gotoxy(20, 24);
	SetColor(15);
	SetBGColor(2);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(36, 24);
	SetColor(15);
	SetBGColor(6);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(0, 27);*/
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

	return;
}
void ButtonXacNhanXoaSV(bool choice = false) {
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
void KhungDSMonHoc() {
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
//----------------------




