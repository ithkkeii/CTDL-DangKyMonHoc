// ProjectCTDL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream> 

#include "Mylib.h"
#include "Raw.h"
#include "Frame.h"

#define DOWN -80
#define UP -72
#define LEFT -75
#define RIGHT -77
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define SPACE 32
#define F1 -59
#define F2 -60
#define F3 -61
#define F4 -62
#define F5 -63
#define DELETE -83
#define F8 -66
#define DSDKMAX 5000
#define randRage 5000
using namespace std;

int randArr[randRage];
void RandomMLTC();
//Random ma lop tin chi
void RandomMLTC() {
	srand(time(NULL));
	randArr[0] = 1;
	int temp;
	int randNum;
	for (int i = 0; i < randRage; i++) {
		randArr[i] = i + 1000;
	}

	for (int i = 0; i < randRage; i++) {
		randNum = rand() % (randRage);					//Random khoang [0 - 4999] (rand() % (b-a+1)-a)
		temp = randArr[i];
		randArr[i] = randArr[randNum];
		randArr[randNum] = temp;
	}
	return;
}

//---------------------------------------------------------BAT DAU KHAI BAO STRUCT------------------------------------------------
//Danh sach mon hoc la cay nhi phan tim kiem
typedef struct MonHoc {
	char maMonHoc[10];
	char tenMonHoc[40];
	int soTCLT;
	int soTCTH;
};
typedef struct DS_MonHoc {
	MonHoc monHoc;
	DS_MonHoc* left, * right;
};
DS_MonHoc* tree;

//Danh sach dang ky
typedef struct DangKy {
	char maSV[12];
	float diem;
};
typedef struct DS_DangKy {
	DangKy dangKy;
	DS_DangKy* next;
};

//Danh sach sinh vien
typedef struct SinhVien {
	char maLop[15];
	char maSV[12];
	char ho[21];
	char ten[15];
	int phai;
	char sdt[10];
	int namNhapHoc;
};
typedef struct DS_SinhVien {
	SinhVien sinhVien;
	DS_SinhVien* next;
};
DS_SinhVien* first;


//Danh sach lop tin chi la mang con tro
typedef struct LopTinChi {
	int maLopTinChi;
	char maMonHoc[10];
	int nienKhoa;
	int hocKy;
	int nhom;
	int svMin;
	int svMax;
	//DS_SinhVien* head;
	DS_DangKy* head;
};
typedef struct DS_LopTinChi {
	int soLuong;
	LopTinChi* ds[DSDKMAX];
};

//---------------------------------------------------KET THUC KHAI BAO STRUCT------------------------------------------------------

//----------------------------------------------------NHAP,XUAT,HIEU CHINH LOP TIN CHI----------------------------------------------------
int IsFull(DS_LopTinChi& ds_ltc) {
	return (ds_ltc.soLuong == DSDKMAX - 1) ? 1 : 0;
}
//Luu File Lop Tin Chi
void LuuFileLopTinChi(DS_LopTinChi& ds_ltc) {
	int n = 0;
	fstream f;
	f.open("DSLOPTINCHI.txt", ios::out);
	while (n < ds_ltc.soLuong) {
		f << ds_ltc.ds[n]->maLopTinChi << endl
			<< ds_ltc.ds[n]->maMonHoc << endl
			<< ds_ltc.ds[n]->nienKhoa << endl
			<< ds_ltc.ds[n]->hocKy << endl
			<< ds_ltc.ds[n]->nhom << endl
			<< ds_ltc.ds[n]->svMin << endl
			<< ds_ltc.ds[n]->svMax << endl;  //Bo endl fix bug luc doc file (endl o maloptinchi)
		n++;
	}
	f.close();
	return;
}

//Them lop tin chi
void InitializeLopTinChi(DS_LopTinChi& ds_ltc) {
	ds_ltc.soLuong = 0;
	return;
}

//Check trung MaMonHoc + NienKhoa + HocKy + Nhom
int checkSentenceA(DS_LopTinChi& ds_ltc, LopTinChi lopTinChi) {
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		bool flag = strcmp(ds_ltc.ds[i]->maMonHoc, lopTinChi.maMonHoc) == 0
			&& ds_ltc.ds[i]->nienKhoa == lopTinChi.nienKhoa
			&& ds_ltc.ds[i]->hocKy == lopTinChi.hocKy
			&& ds_ltc.ds[i]->nhom == lopTinChi.nhom;
		if (flag) {
			//Alert("Lop Tin Chi Trung!!! Tu Dong Thoat!!!", 34, 16, 4, 2000);
			Alert("Lop Tin Chi Trung!!! Tu Dong Thoat!!!", 105, 25, 4, 2000);
			return 1;
		}
	}
	return 0;
}

void ThemLopTinChi(DS_LopTinChi& ds_ltc) {
	KhungNhapLopTinChi();

	int key, vitri = 0, x = 10/* soluongCheck = ds_ltc.soLuong*/;
	LopTinChi lopTinChi;
	lopTinChi.maMonHoc[0] = '\0';
	lopTinChi.nienKhoa = 0;
	lopTinChi.hocKy = 0;
	lopTinChi.nhom = 0;
	lopTinChi.svMin = 0;
	lopTinChi.svMax = 0;

	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';


	// Nhan 1 MA LOP TIN CHI KHONG TRUNG tu sinh
	for (int i = 0; i < randRage; i++) {
		if (randArr[i] != 0) {
			lopTinChi.maLopTinChi = randArr[i];
			randArr[i] = 0;
			break;
		}
	}

	//In Ma Lop Tin Chi tu sinh
	gotoxy(13, 8);
	SetColor(3);
	SetBGColor(7);
	cout << lopTinChi.maLopTinChi;

	//ma mon hoc : 25,8
	//nien khoa : 44,8
	//hoc ky : 56,8
	//nhom 65,8
	//svmax 73,8
	//svmin 81,8

MAMONHOC:

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << " MA MON HOC: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 9 KI TU  ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {

		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(25 + vitri, 8);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
			if (IsFull(ds_ltc)) {
				Alert("Danh Sach Dang Ky Lop Tin Chi Da Day!!!", 34, 26, 4, 900);
				continue;
			}
			/*if (soluongCheck != (y - 8)) {
				ds_ltc.ds[ds_ltc.soLuong] = new LopTinChi;
				ds_ltc.soLuong++;
				soluongCheck++;
			};*/
			/*ds_ltc.ds_ltc_ltc[ds_ltc.soLuong] = new LopTinChi;
			ds_ltc.ds_ltc_ltc[ds_ltc.soLuong]->maMH[vitri] = (char)key;*/
			lopTinChi.maMonHoc[vitri] = toupper((char)key);
			cout << lopTinChi.maMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(25 + vitri, 8);
			cout << " ";
		}
		/*if (key == ENTER && vitri != 0) {
			if (IsFull(ds_ltc)) {
				Alert("Danh Sach Dang Ky Lop Tin Chi Da Day!!!", 34, 26, 74, 900);
				continue;
			}
			tinChi.maMH[vitri] = '\0';
			gotoxy(44, y);
			goto NIENKHOA;
		}*/
		if (key == ESC) {
			system("cls");
			return;
		}
		if (key == RIGHT || key == ENTER) {
			if (IsFull(ds_ltc)) {
				Alert("Danh Sach Dang Ky Lop Tin Chi Da Day!!!", 34, 26, 4, 900);
				continue;
			}
			lopTinChi.maMonHoc[vitri] = '\0';
			if (lopTinChi.maMonHoc[0] == '\0') {
				Alert("Chua Nhap Ma Mon Hoc!!!", 34, 26, 4, 900);
				gotoxy(25, 8);
				goto MAMONHOC;
			}
			//vitri = strlen(lopTinChi.nienKhoa);
			vitri = strlen(nienKhoa_ch); //Nien Khoa Set Bat Buoc 4 So
			gotoxy(44 + vitri, 8);
			goto NIENKHOA;
		}
	}
NIENKHOA:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI THIEU: 4 KI TU     ";
	gotoxy(18, 30);
	cout << "                                                           ";

	/*if (tinChi.maMH[0] == '\0') {
		Alert("Chua Nhap Ma Mon Hoc!!!", 34, 26, 74, 900);
		gotoxy(25, y);
		goto MAMONHOC;
	}*/

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(44 + vitri, 8);
		key = GetKey();

		/*if (tinChi.maMH[0] == '\0') {
			Alert("Chua Nhap Ma Mon Hoc!!!", 34, 26, 74, 900);
			gotoxy(25, y);
			goto MAMONHOC;
		}*/
		if (key >= '0' && key <= '9' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			nienKhoa_ch[vitri] = (char)key;
			cout << nienKhoa_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(44 + vitri, 8);
			cout << " ";
		}
		/*if (key == ENTER && vitri != 0) {
			tinChi.nienKhoa[vitri] = '\0';
			ds.soLuong++;
			return;
		}*/
		if (key == LEFT) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> lopTinChi.nienKhoa;
			//

			vitri = strlen(lopTinChi.maMonHoc);
			gotoxy(25 + vitri, 8);
			goto MAMONHOC;
		}
		if (key == RIGHT || key == ENTER) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> lopTinChi.nienKhoa;
			//

			vitri = (lopTinChi.hocKy > 9) ? 2 : (lopTinChi.hocKy == 0) ? 0 : 1;
			gotoxy(56 + vitri, 8);
			goto HOCKY;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
HOCKY:
	char hocKy_ch[3];

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "        HOC KY: GOM CAC SO (0-9), TOI DA: 2 KI TU          ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(56 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Hoc Ky Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			hocKy_ch[vitri] = (char)key;
			cout << hocKy_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(56 + vitri, 8);
			cout << " ";
		}
		/*if (key == ENTER && vitri != 0) {
			hocKy_ch[vitri] = '\0';
			return;
		}*/
		if (key == LEFT) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> lopTinChi.hocKy;
			//

			vitri = strlen(nienKhoa_ch); //Nien Khoa Set Bat Buoc 4 So
			gotoxy(44 + vitri, 8);
			goto NIENKHOA;
		}

		if (key == RIGHT || key == ENTER) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> lopTinChi.hocKy;
			//

			vitri = (lopTinChi.nhom > 9) ? 2 : (lopTinChi.nhom == 0) ? 0 : 1;
			/*if (tinChi.nhom == 0)
				vitri = 0;*/
			gotoxy(56 + vitri, 8);
			goto NHOM;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
NHOM:
	char nhom_ch[3];

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "       NHOM: GOM CAC SO (0-9), TOI DA: 2 KI TU             ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(65 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Nhom Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			nhom_ch[vitri] = (char)key;
			cout << nhom_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(65 + vitri, 8);
			cout << " ";
		}

		if (key == LEFT) {
			nhom_ch[vitri] = '\0';
			if (nhom_ch[0] == '\0') {
				Alert("Nhom Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> lopTinChi.nhom;
			//

			vitri = (lopTinChi.hocKy > 9) ? 2 : (lopTinChi.hocKy == 0) ? 0 : 1;
			gotoxy(56 + vitri, 8);
			goto HOCKY;
		}
		if (key == RIGHT || key == ENTER) {
			nhom_ch[vitri] = '\0';
			if (nhom_ch[0] == '\0') {
				Alert("Nhom Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> lopTinChi.nhom;
			//

			vitri = (lopTinChi.svMin >= 100) ? 3 : (lopTinChi.svMin >= 10) ? 2 : (lopTinChi.svMin == 0) ? 0 : 1;
			/*if (tinChi.svMin == 0)
				vitri = 0;*/
			gotoxy(73 + vitri, 8);
			goto SVMIN;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}

SVMIN:
	char svMin_ch[4];

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "      SINH VIEN MIN: GOM CAC SO (0-9), TOI DA: 3 KI TU     ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(73 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 3) {
			if (key == '0' && vitri == 0) {
				Alert("So SVMIN Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			svMin_ch[vitri] = (char)key;
			cout << svMin_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(73 + vitri, 8);
			cout << " ";
		}

		if (key == LEFT) {
			svMin_ch[vitri] = '\0';
			if (svMin_ch[0] == '\0') {
				Alert("Sinh Vien Min Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Sinh Vien Min)
			string svMin_str(svMin_ch);
			stringstream geek(svMin_str);
			geek >> lopTinChi.svMin;
			//

			//Check SVMAX vs SVMIN
			if (lopTinChi.svMax < lopTinChi.svMin) {
				Alert("Sinh Vien Min Phai Nho Hon Sinh Vien Max", 34, 26, 4, 900);
				continue;
			};
			//

			vitri = (lopTinChi.nhom > 9) ? 2 : (lopTinChi.nhom == 0) ? 0 : 1;
			gotoxy(65 + vitri, 8);
			goto NHOM;
		}
		if (key == RIGHT || key == ENTER) {
			svMin_ch[vitri] = '\0';
			if (svMin_ch[0] == '\0') {
				Alert("Sinh Vien Min Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Sinh Vien Min)
			string svMin_str(svMin_ch);
			stringstream geek(svMin_str);
			geek >> lopTinChi.svMin;
			//

			//Check SVMAX vs SVMIN
			if (lopTinChi.svMax != 0)
				if (lopTinChi.svMax < lopTinChi.svMin) {
					Alert("Sinh Vien Min Phai Nho Hon Sinh Vien Max", 34, 26, 4, 900);
					continue;
				};
			//

			vitri = (lopTinChi.svMax >= 100) ? 3 : (lopTinChi.svMax >= 10) ? 2 : (lopTinChi.svMax == 0) ? 0 : 1;
			/*if (tinChi.svMin == 0)
				vitri = 0;*/
			gotoxy(81 + vitri, 8);
			goto SVMAX;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}

SVMAX:
	char svMax_ch[4];

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "      SINH VIEN MAX: GOM CAC SO (0-9), TOI DA: 3 KI TU     ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(81 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 3) {
			if (key == '0' && vitri == 0) {
				Alert("So SVMAX Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			svMax_ch[vitri] = (char)key;
			cout << svMax_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(81 + vitri, 8);
			cout << " ";
		}

		if (key == LEFT) {
			svMax_ch[vitri] = '\0';
			if (svMax_ch[0] == '\0') {
				Alert("Sinh Vien Max Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Sinh Vien Max)
			string svMax_str(svMax_ch);
			stringstream geek(svMax_str);
			geek >> lopTinChi.svMax;

			//Check SVMAX vs SVMIN
			if (lopTinChi.svMax < lopTinChi.svMin) {
				Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 34, 26, 4, 900);
				continue;
			};
			//

			vitri = (lopTinChi.svMin >= 100) ? 3 : (lopTinChi.svMin >= 10) ? 2 : (lopTinChi.svMin == 0) ? 0 : 1;
			gotoxy(73 + vitri, 8);
			goto SVMIN;
		}
		if (key == RIGHT || key == ENTER) {
			svMax_ch[vitri] = '\0';
			if (svMax_ch[0] == '\0') {
				Alert("Sinh Vien Max Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Sinh Vien Max)
			string svMax_str(svMax_ch);
			stringstream geek(svMax_str);
			geek >> lopTinChi.svMax;
			//

			//Check MaMonHoc + NienKhoa + HocKy + Nhom
			if (checkSentenceA(ds_ltc, lopTinChi))
				return;



			//Check SVMAX vs SVMIN
			if (lopTinChi.svMax < lopTinChi.svMin) {
				Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 34, 26, 4, 900);
				continue;
			};

			//Luu Sinh Vien Vao Mang Con Tro
			gotoxy(1, 1);
			ds_ltc.soLuong++;
			ds_ltc.ds[ds_ltc.soLuong - 1] = new LopTinChi;
			*(ds_ltc.ds[ds_ltc.soLuong - 1]) = lopTinChi;

			Alert("LUU SINH VIEN THANH CONG!!!", 34, 16, 2, 300);
			Sleep(100);
			Alert("LUU SINH VIEN THANH CONG!!!", 34, 16, 2, 300);
			Sleep(100);
			Alert("LUU SINH VIEN THANH CONG!!!", 34, 16, 2, 300);
			break;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
	//Turn on F1 and turn off sthing
	//turnoffButtonThemLop();
	/*while (true) {
		key = GetKey();
		if (key == ESC)
			return;
		if (key == F1) {
			LuuFileLopTinChi(ds_ltc);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 16, 2, 300);
			Sleep(100);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 16, 2, 300);
			Sleep(100);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 16, 2, 300);
			break;
		}
	}*/
	return;
}

void CheckRangBuoc(int position, DS_LopTinChi& ds_ltc) {
	int key;
	int y = 15;
	int vitri = 0;
	LopTinChi lopTinChi;
	lopTinChi.maMonHoc[0] = '\0';
	lopTinChi.nienKhoa = 0;
	lopTinChi.hocKy = 0;
	lopTinChi.nhom = 0;
	lopTinChi.svMin = 0;
	lopTinChi.svMax = 0;
	KhungConSuaLopTinChi();
	while (true) {
		char nienKhoa_ch[5];
		nienKhoa_ch[0] = '\0';
		char maMonHoc_ch[10];
		maMonHoc_ch[0] = '\0';
	MAMONHOC:
		//Ghi chu
		SetColor(4);
		SetBGColor(15);
		gotoxy(90, 20);
		cout << "                                                           ";
		gotoxy(90, 21);
		cout << "  MA MON HOC: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 9 KI TU  ";
		gotoxy(90, 22);
		cout << "                                                           ";

		while (true) {
			//Nhap Ma Mon Hoc
			SetColor(3);
			SetBGColor(7);
			gotoxy(92 + vitri, y);
			key = GetKey();
			if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
				maMonHoc_ch[vitri] = toupper((char)key);
				cout << maMonHoc_ch[vitri];
				vitri++;
			}
			if (key == BACKSPACE && vitri > 0) {
				vitri--;
				gotoxy(92 + vitri, y);
				cout << " ";
			}
			if (key == RIGHT || key == ENTER) {
				maMonHoc_ch[vitri] = '\0';
				if (maMonHoc_ch[0] == '\0') {
					Alert("Chua Nhap Ma Mon Hoc!!!", 105, 25, 4, 900);
					gotoxy(92, y);
					goto MAMONHOC;
				}

				strcpy_s(lopTinChi.maMonHoc, maMonHoc_ch);

				vitri = strlen(nienKhoa_ch); //Nien Khoa Set Bat Buoc 4 So
				gotoxy(114 + vitri, y);
				goto NIENKHOA;
			}
		}
	NIENKHOA:
		//Ghi chu
		SetColor(4);
		SetBGColor(15);
		gotoxy(90, 20);
		cout << "                                                           ";
		gotoxy(90, 21);
		cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI THIEU: 4 KI TU     ";
		gotoxy(90, 22);
		cout << "                                                           ";

		while (true) {
			SetColor(3);
			SetBGColor(7);
			gotoxy(103 + vitri, y);
			key = GetKey();

			if (key >= '0' && key <= '9' && vitri < 4) {
				if (key == '0' && vitri == 0) {
					Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 105, 25, 4, 900);
					continue;
				}
				nienKhoa_ch[vitri] = (char)key;
				cout << nienKhoa_ch[vitri];
				vitri++;
			}
			if (key == BACKSPACE && vitri > 0) {
				vitri--;
				gotoxy(103 + vitri, y);
				cout << " ";
			}
			if (key == LEFT) {
				nienKhoa_ch[vitri] = '\0';
				if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
					Alert("Nien Khoa Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char[] to int (Nien Khoa)
				string nienKhoa_str(nienKhoa_ch);
				stringstream geek(nienKhoa_str);
				geek >> lopTinChi.nienKhoa;
				//

				vitri = strlen(lopTinChi.maMonHoc);
				gotoxy(92 + vitri, y);
				goto MAMONHOC;
			}
			if (key == RIGHT || key == ENTER) {
				nienKhoa_ch[vitri] = '\0';
				if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
					Alert("Nien Khoa Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char[] to int (Nien Khoa)
				string nienKhoa_str(nienKhoa_ch);
				stringstream geek(nienKhoa_str);
				geek >> lopTinChi.nienKhoa;
				//

				vitri = (lopTinChi.hocKy > 9) ? 2 : (lopTinChi.hocKy == 0) ? 0 : 1;
				gotoxy(114 + vitri, y);
				goto HOCKY;
			}

			if (key == ESC) {
				clrscr();
				return;
			}
		}
	HOCKY:
		char hocKy_ch[3];
		//Ghi chu
		SetColor(4);
		SetBGColor(15);
		gotoxy(90, 20);
		cout << "                                                           ";
		gotoxy(90, 21);
		cout << "        HOC KY: GOM CAC SO (0-9), TOI DA: 2 KI TU          ";
		gotoxy(90, 22);
		cout << "                                                           ";

		while (true) {
			SetColor(3);
			SetBGColor(7);
			gotoxy(114 + vitri, y);
			key = GetKey();
			if (key >= '0' && key <= '9' && vitri < 2) {
				if (key == '0' && vitri == 0) {
					Alert("So Hoc Ky Khong Duoc Bat Dau Bang So 0 ", 105, 25, 4, 900);
					continue;
				}
				hocKy_ch[vitri] = (char)key;
				cout << hocKy_ch[vitri];
				vitri++;
			}
			if (key == BACKSPACE && vitri > 0) {
				vitri--;
				gotoxy(114 + vitri, y);
				cout << " ";
			}
			if (key == LEFT) {
				hocKy_ch[vitri] = '\0';
				if (hocKy_ch[0] == '\0') {
					Alert("Hoc Ky Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Hoc Ky)
				string hocKy_str(hocKy_ch);
				stringstream geek(hocKy_str);
				geek >> lopTinChi.hocKy;
				//

				vitri = strlen(nienKhoa_ch); //Nien Khoa Set Bat Buoc 4 So
				gotoxy(103 + vitri, y);
				goto NIENKHOA;
			}

			if (key == RIGHT || key == ENTER) {
				hocKy_ch[vitri] = '\0';
				if (hocKy_ch[0] == '\0') {
					Alert("Hoc Ky Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Hoc Ky)
				string hocKy_str(hocKy_ch);
				stringstream geek(hocKy_str);
				geek >> lopTinChi.hocKy;
				//

				vitri = (lopTinChi.nhom > 9) ? 2 : (lopTinChi.nhom == 0) ? 0 : 1;
				gotoxy(122 + vitri, y);
				goto NHOM;
			}

			if (key == ESC) {
				clrscr();
				return;
			}
		}
	NHOM:
		char nhom_ch[3];
		//Ghi chu
		SetColor(4);
		SetBGColor(15);
		gotoxy(90, 20);
		cout << "                                                           ";
		gotoxy(90, 21);
		cout << "       NHOM: GOM CAC SO (0-9), TOI DA: 2 KI TU             ";
		gotoxy(90, 22);
		cout << "                                                           ";

		while (true) {

			SetColor(3);
			SetBGColor(7);
			gotoxy(122 + vitri, y);
			key = GetKey();
			if (key >= '0' && key <= '9' && vitri < 2) {
				if (key == '0' && vitri == 0) {
					Alert("So Nhom Khong Duoc Bat Dau Bang So 0 ", 105, 25, 4, 900);
					continue;
				}
				nhom_ch[vitri] = (char)key;
				cout << nhom_ch[vitri];
				vitri++;
			}
			if (key == BACKSPACE && vitri > 0) {
				vitri--;
				gotoxy(122 + vitri, y);
				cout << " ";
			}

			if (key == LEFT) {
				nhom_ch[vitri] = '\0';
				if (nhom_ch[0] == '\0') {
					Alert("Nhom Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Nhom)
				string nhom_str(nhom_ch);
				stringstream geek(nhom_str);
				geek >> lopTinChi.nhom;
				//

				vitri = (lopTinChi.hocKy > 9) ? 2 : (lopTinChi.hocKy == 0) ? 0 : 1;
				gotoxy(114 + vitri, y);
				goto HOCKY;
			}
			if (key == RIGHT || key == ENTER) {
				nhom_ch[vitri] = '\0';
				if (nhom_ch[0] == '\0') {
					Alert("Nhom Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Nhom)
				string nhom_str(nhom_ch);
				stringstream geek(nhom_str);
				geek >> lopTinChi.nhom;
				//

				vitri = (lopTinChi.svMin >= 100) ? 3 : (lopTinChi.svMin >= 10) ? 2 : (lopTinChi.svMin == 0) ? 0 : 1;
				gotoxy(128 + vitri, y);
				goto SVMIN;
			}

			if (key == ESC) {
				clrscr();
				return;
			}
		}

	SVMIN:
		char svMin_ch[4];
		//Ghi chu
		SetColor(4);
		SetBGColor(15);
		gotoxy(90, 20);
		cout << "                                                           ";
		gotoxy(90, 21);
		cout << "      SINH VIEN MIN: GOM CAC SO (0-9), TOI DA: 3 KI TU     ";
		gotoxy(90, 22);
		cout << "                                                           ";

		while (true) {
			SetColor(3);
			SetBGColor(7);
			gotoxy(128 + vitri, y);
			key = GetKey();
			if (key >= '0' && key <= '9' && vitri < 3) {
				if (key == '0' && vitri == 0) {
					Alert("So SVMIN Khong Duoc Bat Dau Bang So 0 ", 105, 25, 4, 900);
					continue;
				}
				svMin_ch[vitri] = (char)key;
				cout << svMin_ch[vitri];
				vitri++;
			}
			if (key == BACKSPACE && vitri > 0) {
				vitri--;
				gotoxy(128 + vitri, y);
				cout << " ";
			}

			if (key == LEFT) {
				svMin_ch[vitri] = '\0';
				if (svMin_ch[0] == '\0') {
					Alert("Sinh Vien Min Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Sinh Vien Min)
				string svMin_str(svMin_ch);
				stringstream geek(svMin_str);
				geek >> lopTinChi.svMin;
				//

				//Check SVMAX vs SVMIN
				if (lopTinChi.svMax < lopTinChi.svMin) {
					Alert("Sinh Vien Min Phai Nho Hon Sinh Vien Max", 105, 25, 4, 900);
					continue;
				};
				//

				vitri = (lopTinChi.nhom > 9) ? 2 : (lopTinChi.nhom == 0) ? 0 : 1;
				gotoxy(122 + vitri, y);
				goto NHOM;
			}
			if (key == RIGHT || key == ENTER) {
				svMin_ch[vitri] = '\0';
				if (svMin_ch[0] == '\0') {
					Alert("Sinh Vien Min Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Sinh Vien Min)
				string svMin_str(svMin_ch);
				stringstream geek(svMin_str);
				geek >> lopTinChi.svMin;
				//

				//Check SVMAX vs SVMIN
				if (lopTinChi.svMax != 0)
					if (lopTinChi.svMax < lopTinChi.svMin) {
						Alert("Sinh Vien Min Phai Nho Hon Sinh Vien Max", 105, 25, 4, 900);
						continue;
					};
				//

				vitri = (lopTinChi.svMax >= 100) ? 3 : (lopTinChi.svMax >= 10) ? 2 : (lopTinChi.svMax == 0) ? 0 : 1;
				gotoxy(135 + vitri, y);
				goto SVMAX;
			}

			if (key == ESC) {
				clrscr();
				return;
			}
		}

	SVMAX:
		char svMax_ch[4];

		//Ghi chu
		SetColor(4);
		SetBGColor(15);
		gotoxy(90, 20);
		cout << "                                                           ";
		gotoxy(90, 21);
		cout << "      SINH VIEN MAX: GOM CAC SO (0-9), TOI DA: 3 KI TU     ";
		gotoxy(90, 22);
		cout << "                                                           ";

		while (true) {

			SetColor(3);
			SetBGColor(7);
			gotoxy(135 + vitri, y);
			key = GetKey();
			if (key >= '0' && key <= '9' && vitri < 3) {
				if (key == '0' && vitri == 0) {
					Alert("So SVMAX Khong Duoc Bat Dau Bang So 0 ", 105, 25, 4, 900);
					continue;
				}
				svMax_ch[vitri] = (char)key;
				cout << svMax_ch[vitri];
				vitri++;
			}
			if (key == BACKSPACE && vitri > 0) {
				vitri--;
				gotoxy(135 + vitri, y);
				cout << " ";
			}

			if (key == LEFT) {
				svMax_ch[vitri] = '\0';
				if (svMax_ch[0] == '\0') {
					Alert("Sinh Vien Max Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Sinh Vien Max)
				string svMax_str(svMax_ch);
				stringstream geek(svMax_str);
				geek >> lopTinChi.svMax;

				//Check SVMAX vs SVMIN
				if (lopTinChi.svMax < lopTinChi.svMin) {
					Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 105, 25, 4, 900);
					continue;
				};
				//

				vitri = (lopTinChi.svMin >= 100) ? 3 : (lopTinChi.svMin >= 10) ? 2 : (lopTinChi.svMin == 0) ? 0 : 1;
				gotoxy(128 + vitri, y);
				goto SVMIN;
			}
			if (key == RIGHT || key == ENTER) {
				svMax_ch[vitri] = '\0';
				if (svMax_ch[0] == '\0') {
					Alert("Sinh Vien Max Chua Nhap", 105, 25, 4, 900);
					continue;
				}

				//Convert char to int (Sinh Vien Max)
				string svMax_str(svMax_ch);
				stringstream geek(svMax_str);
				geek >> lopTinChi.svMax;
				//

				//Check MaMonHoc + NienKhoa + HocKy + Nhom
				if (checkSentenceA(ds_ltc, lopTinChi))
					goto END;

				//Check SVMAX vs SVMIN
				if (lopTinChi.svMax < lopTinChi.svMin) {
					Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 105, 25, 4, 900);
					continue;
				};

				//Sua Sinh Vien
				/*string maLopTinChi_str(maLopTinChi_ch);
				stringstream g(maLopTinChi_str);
				g >> lopTinChi.maLopTinChi;
				for (int i = 0; i < ds_ltc.soLuong; i++) {
					if (lopTinChi.maLopTinChi == ds_ltc.ds[i]->maLopTinChi) {
						strcpy_s(ds_ltc.ds[i]->maMonHoc, lopTinChi.maMonHoc);
						ds_ltc.ds[i]->nienKhoa = lopTinChi.nienKhoa;
						ds_ltc.ds[i]->hocKy = lopTinChi.hocKy;
						ds_ltc.ds[i]->nhom = lopTinChi.nhom;
						ds_ltc.ds[i]->svMin = lopTinChi.svMin;
						ds_ltc.ds[i]->svMax = lopTinChi.svMax;
						break;
					}
				}*/
				strcpy_s(ds_ltc.ds[position]->maMonHoc, lopTinChi.maMonHoc);
				ds_ltc.ds[position]->nienKhoa = lopTinChi.nienKhoa;
				ds_ltc.ds[position]->hocKy = lopTinChi.hocKy;
				ds_ltc.ds[position]->nhom = lopTinChi.nhom;
				ds_ltc.ds[position]->svMin = lopTinChi.svMin;
				ds_ltc.ds[position]->svMax = lopTinChi.svMax;
				Alert("Da Cap Nhat!!!", 105, 25, 4, 900);
				return;
			}

			if (key == ESC) {
				clrscr();
				return;
			}
		}
	}
END:
	return;
}

// Không dùng
void ChinhSuaLopTinChiBETA(DS_LopTinChi& ds_ltc) {

	int key = 0, dem = 0, trang = 0, tongTrang = 0, move = 0;
	while (true) {
		clrscr();
		if (ds_ltc.soLuong == 0) {
			Alert("CHUA CO DANH SACH LOP!!!", 34, 5, 4, 300, 15);
			return;
		} else {
			if (ds_ltc.soLuong < 15) { // 15 slot trong 1 bang
				tongTrang = 1;
				trang = 0;
			} else
				tongTrang = ((ds_ltc.soLuong - 1) / 15 + 1); //Day thi qua trang khac
		}
		KhungChinhLopTinChi();
		dem = 0;

		for (int i = trang * 15; i < 15 + trang * 15 && i < ds_ltc.soLuong; i++) {
			if (trang < tongTrang) {
				if (move > 14) {
					move = 0;
				}
			}
			/*SetColor(4);
			SetBGColor(7);
			gotoxy(6, 8 + dem);
			cout << (i + 1);
			SetColor(3);
			gotoxy(12, 8 + dem);
			cout << ds_ltc.ds[i]->maLopTinChi;
			gotoxy(26, 8 + dem);
			cout << ds_ltc.ds[i]->maMonHoc;
			gotoxy(42, 8 + dem);
			cout << ds_ltc.ds[i]->nienKhoa;
			gotoxy(55, 8 + dem);
			cout << ds_ltc.ds[i]->hocKy;
			gotoxy(64, 8 + dem);
			cout << ds_ltc.ds[i]->nhom;
			gotoxy(71, 8 + dem);
			cout << ds_ltc.ds[i]->svMin;
			gotoxy(80, 8 + dem);
			cout << ds_ltc.ds[i]->svMax;*/
			if (move == dem) {
				SetColor(2);
				//SetBGColor(8);
				gotoxy(6, 8 + dem);
				cout << (i + 1);
				//SetColor(3);
				//SetBGColor(8);
				gotoxy(12, 8 + dem);
				cout << ds_ltc.ds[i]->maLopTinChi;
				gotoxy(26, 8 + dem);
				cout << ds_ltc.ds[i]->maMonHoc;
				gotoxy(42, 8 + dem);
				cout << ds_ltc.ds[i]->nienKhoa;
				gotoxy(55, 8 + dem);
				cout << ds_ltc.ds[i]->hocKy;
				gotoxy(64, 8 + dem);
				cout << ds_ltc.ds[i]->nhom;
				gotoxy(71, 8 + dem);
				cout << ds_ltc.ds[i]->svMin;
				gotoxy(80, 8 + dem);
				cout << ds_ltc.ds[i]->svMax;
			} else {
				SetColor(4);
				SetBGColor(7);
				gotoxy(6, 8 + dem);
				cout << (i + 1);
				SetColor(3);
				SetBGColor(7);
				gotoxy(12, 8 + dem);
				cout << ds_ltc.ds[i]->maLopTinChi;
				gotoxy(26, 8 + dem);
				cout << ds_ltc.ds[i]->maMonHoc;
				gotoxy(42, 8 + dem);
				cout << ds_ltc.ds[i]->nienKhoa;
				gotoxy(55, 8 + dem);
				cout << ds_ltc.ds[i]->hocKy;
				gotoxy(64, 8 + dem);
				cout << ds_ltc.ds[i]->nhom;
				gotoxy(71, 8 + dem);
				cout << ds_ltc.ds[i]->svMin;
				gotoxy(80, 8 + dem);
				cout << ds_ltc.ds[i]->svMax;
			}
			dem++;
		}
		key = GetKey();
		if ((key == RIGHT) && (trang < tongTrang - 1)) {
			trang++;
		}
		if (key == LEFT && trang > 0) {
			trang--;
		}
		if (key == DOWN) {
			move++;
		}
		if (key == UP) {
			move--;
		}
	}
	Sleep(30000);
	system("pause");

	return;
}

void ChinhSuaLopTinChi(DS_LopTinChi& ds_ltc) {
	bool viewMode = true,
		editMode = false,
		deleteMode = false;
	int i = 0, move = 0;

	int key = 0, dem = 0, trang = 0, tongTrang = 0;

	clrscr();
	while (true) {
		if (ds_ltc.soLuong == 0) {
			Alert("CHUA CO DANH SACH LOP!!!", 34, 5, 4, 300, 15);
			return;
		} else {
			if (ds_ltc.soLuong < 15) { // 15 slot trong 1 bang
				tongTrang = 1;
				trang = 0;
			} else
				tongTrang = ((ds_ltc.soLuong - 1) / 15 + 1); //Day thi qua trang khac
		}

		if (key == 0) {
			KhungChinhLopTinChi();
			for (int i = trang * 15; i < 15 + trang * 15 && i < ds_ltc.soLuong; i++) {
				if (trang < tongTrang) {
					if (move > 14) {
						move = 0;
					}
				}
				SetColor(4);
				SetBGColor(7);
				gotoxy(6, 8 + dem);
				cout << (i + 1);
				SetColor(3);
				gotoxy(12, 8 + dem);
				cout << ds_ltc.ds[i]->maLopTinChi;
				gotoxy(26, 8 + dem);
				cout << ds_ltc.ds[i]->maMonHoc;
				gotoxy(42, 8 + dem);
				cout << ds_ltc.ds[i]->nienKhoa;
				gotoxy(55, 8 + dem);
				cout << ds_ltc.ds[i]->hocKy;
				gotoxy(64, 8 + dem);
				cout << ds_ltc.ds[i]->nhom;
				gotoxy(71, 8 + dem);
				cout << ds_ltc.ds[i]->svMin;
				gotoxy(80, 8 + dem);
				cout << ds_ltc.ds[i]->svMax;
				dem++;
			}
		}
		SetMode(viewMode, editMode, deleteMode);
		dem = 0;
		key = GetKey();

		if (key == F3) {
			int vitri = 0;
			int maLopTinChi_int = 0;
			char maLopTinChi_ch[5];
			KhungXoaLopTinChi();
			while (true) {
				gotoxy(117 + vitri, 8);
				key = GetKey();
				if (key >= '0' && key <= '9' && vitri < 4) {
					if (key == '0' && vitri == 0) {
						Alert("Ma Lop Khong Duoc Bat Dau Bang So 0 ", 105, 25, 4, 900);
						continue;
					}
					maLopTinChi_ch[vitri] = (char)key;
					cout << maLopTinChi_ch[vitri];
					vitri++;
				}
				if (key == BACKSPACE && vitri > 0) {
					vitri--;
					gotoxy(117 + vitri, 8);
					cout << " ";
				}
				if (key == ENTER) {
					int index = -1;
					maLopTinChi_ch[vitri] = '\0';

					//Convert char to int
					string maLopTinChi_str(maLopTinChi_ch);
					stringstream geek(maLopTinChi_str);
					geek >> maLopTinChi_int;
					//

					//Lay vi tri ma lop tin chi
					for (int i = 0; i < ds_ltc.soLuong; i++) {
						if (maLopTinChi_int == ds_ltc.ds[i]->maLopTinChi) {
							index = i;
							break;
						}
					}

					if (index == -1) {
						Alert("Ma Lop Khong Ton Tai", 110, 14, 4, 900);
						ClearKhungXoaTinChi();
						key = 0;
						break;
					}

					delete ds_ltc.ds[index];
					for (int i = index; i < ds_ltc.soLuong - 1; i++) {
						ds_ltc.ds[i] = ds_ltc.ds[i + 1];
					}
					ds_ltc.ds[ds_ltc.soLuong - 1] = NULL;
					ds_ltc.soLuong--;
					Alert("Xoa Thanh Cong!!!", 110, 14, 2, 900);

					//Add lai ma tin chi cho mang 
					for (int i = 0; i < DSDKMAX; i++) {
						if (randArr[i] == 0) {
							randArr[i] = maLopTinChi_int;
							break;
						}
					}


					ClearKhungXoaTinChi();
					key = 0;
					break;
				}
				if (key == ESC) {
					ClearKhungXoaTinChi();
					key = 0;
					break;
				}
			}
		}

		if (key == F2) {
			int vitri = 0;
			char maLopTinChi_ch[5];
			KhungSuaLopTinChi();
			while (true) {
				gotoxy(117 + vitri, 8);
				key = GetKey();
				if (key >= '0' && key <= '9' && vitri < 4) {
					if (key == '0' && vitri == 0) {
						Alert("Ma Lop Khong Duoc Bat Dau Bang So 0 ", 105, 25, 4, 900);
						continue;
					}
					maLopTinChi_ch[vitri] = (char)key;
					cout << maLopTinChi_ch[vitri];
					vitri++;
				}
				if (key == BACKSPACE && vitri > 0) {
					vitri--;
					gotoxy(117 + vitri, 8);
					cout << " ";
				}
				if (key == ESC) {
					clrscr();
					key = 0;
					break;
				}
				if (key == ENTER) {
					maLopTinChi_ch[vitri] = '\0';
					if (maLopTinChi_ch[0] == '\0') {
						Alert("Chua Nhap Ma Lop!!!", 105, 25, 4, 900);
					}
					//Check ma lop tin chi
					int maloptemp;
					string temp(maLopTinChi_ch);
					stringstream s(temp);
					s >> maloptemp;
					for (size_t i = 0; i < ds_ltc.soLuong; i++) {
						if (maloptemp == ds_ltc.ds[i]->maLopTinChi) {
							CheckRangBuoc(i, ds_ltc);
							break;
						}
					}
				}
			}
		}

		if ((key == RIGHT) && (trang < tongTrang - 1)) {
			move = 0; //reset chon ve dau
			trang++;
			KhungChinhLopTinChi();
			for (int i = trang * 15; i < 15 + trang * 15 && i < ds_ltc.soLuong; i++) {
				SetColor(4);
				SetBGColor(7);
				gotoxy(6, 8 + dem);
				cout << (i + 1);
				SetColor(3);
				gotoxy(12, 8 + dem);
				cout << ds_ltc.ds[i]->maLopTinChi;
				gotoxy(26, 8 + dem);
				cout << ds_ltc.ds[i]->maMonHoc;
				gotoxy(42, 8 + dem);
				cout << ds_ltc.ds[i]->nienKhoa;
				gotoxy(55, 8 + dem);
				cout << ds_ltc.ds[i]->hocKy;
				gotoxy(64, 8 + dem);
				cout << ds_ltc.ds[i]->nhom;
				gotoxy(71, 8 + dem);
				cout << ds_ltc.ds[i]->svMin;
				gotoxy(80, 8 + dem);
				cout << ds_ltc.ds[i]->svMax;
				dem++;
			}
		}
		if (key == LEFT && trang > 0) {
			move = 0; // reset chon ve dau
			trang--;
			KhungChinhLopTinChi();
			for (int i = trang * 15; i < 15 + trang * 15 && i < ds_ltc.soLuong; i++) {
				SetColor(4);
				SetBGColor(7);
				gotoxy(6, 8 + dem);
				cout << (i + 1);
				SetColor(3);
				gotoxy(12, 8 + dem);
				cout << ds_ltc.ds[i]->maLopTinChi;
				gotoxy(26, 8 + dem);
				cout << ds_ltc.ds[i]->maMonHoc;
				gotoxy(42, 8 + dem);
				cout << ds_ltc.ds[i]->nienKhoa;
				gotoxy(55, 8 + dem);
				cout << ds_ltc.ds[i]->hocKy;
				gotoxy(64, 8 + dem);
				cout << ds_ltc.ds[i]->nhom;
				gotoxy(71, 8 + dem);
				cout << ds_ltc.ds[i]->svMin;
				gotoxy(80, 8 + dem);
				cout << ds_ltc.ds[i]->svMax;
				dem++;
			}
		}
		if (key == DOWN) {
			move++;
			if (trang == tongTrang - 1) {
				if ((move > ds_ltc.soLuong % 15 - 1) && (ds_ltc.soLuong % 15 != 0)) {
					move = ds_ltc.soLuong % 15 - 1;
				}
			}


			if (move > 14) {
				move = 14;
			}
			i = 15 * trang + move;
			if (move - 1 >= 0) {
				SetBGColor(7);
				SetColor(5);
				gotoxy(4, 8 + move - 1);
				cout << "     |            |                |             |        |      |        |        |";
				//SetBGColor(7);
				SetColor(4);
				gotoxy(6, 8 + move - 1);
				cout << (i);
				SetColor(3);
				gotoxy(12, 8 + move - 1);
				cout << ds_ltc.ds[i - 1]->maLopTinChi;
				gotoxy(26, 8 + move - 1);
				cout << ds_ltc.ds[i - 1]->maMonHoc;
				gotoxy(42, 8 + move - 1);
				cout << ds_ltc.ds[i - 1]->nienKhoa;
				gotoxy(55, 8 + move - 1);
				cout << ds_ltc.ds[i - 1]->hocKy;
				gotoxy(64, 8 + move - 1);
				cout << ds_ltc.ds[i - 1]->nhom;
				gotoxy(71, 8 + move - 1);
				cout << ds_ltc.ds[i - 1]->svMin;
				gotoxy(80, 8 + move - 1);
				cout << ds_ltc.ds[i - 1]->svMax;

				gotoxy(1, 1);
				cout << i << "  " << move;
			}
			SetBGColor(15);
			gotoxy(4, 8 + move);
			cout << "                                                                                   ";
			SetColor(4);
			//SetBGColor(4);
			gotoxy(6, 8 + move);
			cout << (i + 1);
			SetColor(3);
			gotoxy(12, 8 + move);
			cout << ds_ltc.ds[i]->maLopTinChi;
			gotoxy(26, 8 + move);
			cout << ds_ltc.ds[i]->maMonHoc;
			gotoxy(42, 8 + move);
			cout << ds_ltc.ds[i]->nienKhoa;
			gotoxy(55, 8 + move);
			cout << ds_ltc.ds[i]->hocKy;
			gotoxy(64, 8 + move);
			cout << ds_ltc.ds[i]->nhom;
			gotoxy(71, 8 + move);
			cout << ds_ltc.ds[i]->svMin;
			gotoxy(80, 8 + move);
			cout << ds_ltc.ds[i]->svMax;
			gotoxy(1, 1);

			cout << i << "  " << move;
		}
		if (key == UP) {
			move--;
			if (move < 1) {
				move = 0;
			}
			i = 15 * trang + move;

			//if (i + 1 >= ds_ltc.soLuong) //Ngan bug 1 slot o trang
			//	continue;

			if (move + 1 <= 15) {
				if (i + 1 < ds_ltc.soLuong) {  //Ngan bug 1 slot o trang

					SetBGColor(7);
					SetColor(5);
					gotoxy(4, 8 + move + 1);
					cout << "     |            |                |             |        |      |        |        |";

					SetColor(4);
					SetBGColor(7);
					gotoxy(6, 8 + move + 1);
					cout << (i + 2);
					SetColor(3);
					gotoxy(12, 8 + move + 1);
					cout << ds_ltc.ds[i + 1]->maLopTinChi;
					gotoxy(26, 8 + move + 1);
					cout << ds_ltc.ds[i + 1]->maMonHoc;
					gotoxy(42, 8 + move + 1);
					cout << ds_ltc.ds[i + 1]->nienKhoa;
					gotoxy(55, 8 + move + 1);
					cout << ds_ltc.ds[i + 1]->hocKy;
					gotoxy(64, 8 + move + 1);
					cout << ds_ltc.ds[i + 1]->nhom;
					gotoxy(71, 8 + move + 1);
					cout << ds_ltc.ds[i + 1]->svMin;
					gotoxy(80, 8 + move + 1);
					cout << ds_ltc.ds[i + 1]->svMax;

					gotoxy(1, 1);
					cout << i << "  " << move;
				}
			}
			SetBGColor(15);
			gotoxy(4, 8 + move);
			cout << "                                                                                   ";

			SetColor(4);
			//SetBGColor(4);
			gotoxy(6, 8 + move);
			cout << (i + 1);
			SetColor(3);
			gotoxy(12, 8 + move);
			cout << ds_ltc.ds[i]->maLopTinChi;
			gotoxy(26, 8 + move);
			cout << ds_ltc.ds[i]->maMonHoc;
			gotoxy(42, 8 + move);
			cout << ds_ltc.ds[i]->nienKhoa;
			gotoxy(55, 8 + move);
			cout << ds_ltc.ds[i]->hocKy;
			gotoxy(64, 8 + move);
			cout << ds_ltc.ds[i]->nhom;
			gotoxy(71, 8 + move);
			cout << ds_ltc.ds[i]->svMin;
			gotoxy(80, 8 + move);
			cout << ds_ltc.ds[i]->svMax;

			gotoxy(1, 1);
			cout << i << "  " << move;
		}
		if (key == ESC)
			return;
		if (key == F1) {
			LuuFileLopTinChi(ds_ltc);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 30, 2, 300);
			Sleep(100);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 30, 2, 300);
			Sleep(100);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 30, 2, 300);
		}
	}

	//Sleep(30000);
	system("pause");
	return;
}

//----------------------------------------------------KET THUC NHAP,XUAT,HIEU CHINH LOP TIN CHI------------------------------------------

//------------------------------------------IN DANH SACH DANG KY LOP TIN CHI-----------------------------------------------
void LuuDSDK(DS_LopTinChi& ds_ltc, DS_DangKy& ds_dk) {
	std::ofstream fileOutput("E:/DevC/AAAAA/ProjectCTDL/DSDK.txt");
	string data;
	int i = 0;
	if (fileOutput.fail())
		cout << "Failed to open this file!" << endl;
	while (i < ds_ltc.soLuong) {
		DS_DangKy* currentDangKy = ds_ltc.ds[i]->head;
		fileOutput << ds_ltc.ds[i]->maLopTinChi << endl;
		while (true) {
			try {
				if (currentDangKy->next != NULL) {
					fileOutput << currentDangKy->dangKy.maSV << endl
						<< currentDangKy->dangKy.diem << endl;
					currentDangKy = currentDangKy->next;
				} else {
					fileOutput << "end" << endl;
					break;
				}
			} catch (...) {
				fileOutput << "end" << endl;
				break;
			}
		}
		i++;
	}
	return;
}

void DocDSDK(DS_LopTinChi& ds_ltc, DS_DangKy& ds_dk) {
	std::ifstream fileInput("E:/DevC/AAAAA/ProjectCTDL/DSDK.txt", std::ios::in);
	string data;
	if (fileInput.fail())
		cout << "Failed to open this file!" << endl;
	int i = 0;
	while (!fileInput.eof()) {
		//getline(fileInput, data);         //fileInput.getline(char,255);
		/*try {
			cout << std::stoi(data) << endl;
		} catch (...) {
			cout << "ERROR" << endl;

		}*/

		getline(fileInput, data);
		if (data.size() == 0)
			return;

		int maLopTinChi = std::stoi(data);
		DS_DangKy* currentDangKy = new DS_DangKy;
		ds_ltc.ds[i]->head = currentDangKy;
		getline(fileInput, data);
		strcpy_s(currentDangKy->dangKy.maSV, data.c_str());
		getline(fileInput, data);
		currentDangKy->dangKy.diem = std::stoi(data);
		while (true) {
			DS_DangKy* newDangKy = new DS_DangKy;

			getline(fileInput, data);
			if (data == "end") {
				currentDangKy->next = NULL;
				break;
			}

			strcpy_s(newDangKy->dangKy.maSV, data.c_str());
			getline(fileInput, data);
			newDangKy->dangKy.diem = std::stoi(data);

			currentDangKy->next = newDangKy;
			currentDangKy = newDangKy;
		}
		i++;
	}
	fileInput.close(); //Khong co cung khong sao, C++ tu dong
	return;
}

int CheckFieldTonTai(LopTinChi lopTinChi, DS_LopTinChi& ds_ltc, string choice) {
	if (choice == "mmh") {
		for (int i = 0; i < ds_ltc.soLuong; i++) {
			if (strcmp(ds_ltc.ds[i]->maMonHoc, lopTinChi.maMonHoc) == 0)
				return 1;  //Ma mon hoc ton tai
		}
	}
	if (choice == "nk") {
		for (int i = 0; i < ds_ltc.soLuong; i++) {
			if (lopTinChi.nienKhoa == ds_ltc.ds[i]->nienKhoa)
				return 1; //Nien khoa ton tai
		}
	}
	if (choice == "hk") {
		for (int i = 0; i < ds_ltc.soLuong; i++) {
			if (lopTinChi.hocKy == ds_ltc.ds[i]->hocKy)
				return 1; //Hoc ky ton tai
		}
	}
	if (choice == "l") {
		for (int i = 0; i < ds_ltc.soLuong; i++) {
			if (strcmp(ds_ltc.ds[i]->maMonHoc, lopTinChi.maMonHoc) == 0
				&& lopTinChi.nienKhoa == ds_ltc.ds[i]->nienKhoa
				&& lopTinChi.nhom == ds_ltc.ds[i]->nhom
				&& lopTinChi.hocKy == ds_ltc.ds[i]->hocKy)
				return i; //Lop tin chi ton tai
		}
	}
	return -1;
}

SinhVien TimSinhVien(char maSV[]) {
	SinhVien sv;
	DS_SinhVien* p = first;
	while (p != NULL) {
		if (strcmp(maSV, p->sinhVien.maSV) == 0) {
			sv = p->sinhVien;
			return sv;
		}
		p = p->next;
	}
}

void InDSDKCon(DS_LopTinChi& ds_ltc, int vitri) {
	int key = 0, dem = 0, trang = 0, tongTrang = 0, y = 0;

	//Dem so luong dsdk
	DS_DangKy* p = ds_ltc.ds[vitri]->head;
	int soLuong = 0;
	while (true) {
		if (p == NULL)
			break;
		soLuong++;
		p = p->next;
	}

	while (true) {
		//clrscr();
		KhungInDSDKCon();

		if (ds_ltc.ds[vitri]->head == NULL) {
			Alert("CHUA CO SINH VIEN DANG KY!!!", 34, 5, 4, 900, 15);
			return;
		} else {
			if (soLuong < 15) { // 15 slot trong 1 bang
				tongTrang = 1;
				trang = 0;
			} else
				tongTrang = ((soLuong - 1) / 15 + 1); //Day thi qua trang khac
		}

		DS_DangKy* p = ds_ltc.ds[vitri]->head;
		for (int i = 0; i < (trang - 1) * 15 + 15; i++) {
			p = p->next;
		}
		SinhVien sv;
		y = 16;
		for (int i = trang * 15; i < trang * 15 + 15; i++) {
			if (p == NULL)
				break;

			//Tim sinh vien
			sv = TimSinhVien(p->dangKy.maSV);

			gotoxy(5, y);
			SetColor(9);
			SetBGColor(7);
			cout << sv.maLop;

			gotoxy(18, y);
			cout << sv.maSV;

			gotoxy(31, y);
			cout << sv.ho;

			gotoxy(48, y);
			cout << sv.ten;

			gotoxy(59, y);
			cout << ((sv.phai) ? "NAM" : "NU");

			gotoxy(64, y);
			cout << sv.namNhapHoc;

			gotoxy(72, y);
			cout << sv.sdt;

			p = p->next;
			y++;
		}
		dem = 0;
		key = GetKey();
		if ((key == RIGHT) && (trang < tongTrang - 1)) {
			trang++;
		}
		if (key == LEFT && trang > 0) {
			trang--;
		}
		if (key == ESC) {
			for (int i = 0; i < 20; i++) {
				SetColor(7);
				gotoxy(1, i + 13);
				cout << "                                                                                        ";
			}
			return;
		}
	}
	return;
}

void InDSDK(DS_LopTinChi& ds_ltc, DS_DangKy& ds_dk) {
	KhungInDSDK();
	int key, vitri = 0, x = 10;
	LopTinChi lopTinChi;
	lopTinChi.maMonHoc[0] = '\0';
	lopTinChi.nienKhoa = 0;
	lopTinChi.hocKy = 0;
	lopTinChi.nhom = 0;

	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';
	char hocKy_ch[3];

	//ma mon hoc : 25,8
	//nien khoa : 44,8
	//hoc ky : 56,8
	//nhom 65,8
	//svmax 73,8
	//svmin 81,8

MAMONHOC:

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << " MA MON HOC: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 9 KI TU  ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {
		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(25 + vitri, 8);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
			lopTinChi.maMonHoc[vitri] = toupper((char)key);
			cout << lopTinChi.maMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(25 + vitri, 8);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			lopTinChi.maMonHoc[vitri] = '\0';
			if (lopTinChi.maMonHoc[0] == '\0') {
				//Alert("Chua Nhap Ma Mon Hoc!!!", 34, 26, 4, 900);
				Alert("Ma Mon Hoc Chua Nhap", 34, 26, 4, 900);
				gotoxy(25, 8);
				goto MAMONHOC;
			}
			if (CheckFieldTonTai(lopTinChi, ds_ltc, "mmh") == -1) {
				Alert("Ma Mon Hoc Khong Ton Tai", 34, 26, 4, 900);
				continue;
			}
			vitri = strlen(nienKhoa_ch);
			gotoxy(44 + vitri, 8);
			goto NIENKHOA;
		}
		if (key == ESC) {
			system("cls");
			return;
		}
	}
NIENKHOA:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI THIEU: 4 KI TU     ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(44 + vitri, 8);
		key = GetKey();

		if (key >= '0' && key <= '9' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			nienKhoa_ch[vitri] = (char)key;
			cout << nienKhoa_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(44 + vitri, 8);
			cout << " ";
		}
		if (key == LEFT) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> lopTinChi.nienKhoa;
			//

			vitri = strlen(lopTinChi.maMonHoc);
			gotoxy(25 + vitri, 8);
			goto MAMONHOC;
		}
		if (key == RIGHT || key == ENTER) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> lopTinChi.nienKhoa;
			//

			if (CheckFieldTonTai(lopTinChi, ds_ltc, "nk") == -1) {
				Alert("Nien Khoa Khong Ton Tai", 34, 26, 4, 900);
				continue;
			}

			vitri = (lopTinChi.hocKy > 9) ? 2 : (lopTinChi.hocKy == 0) ? 0 : 1;
			gotoxy(56 + vitri, 8);
			goto HOCKY;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
HOCKY:


	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "        HOC KY: GOM CAC SO (0-9), TOI DA: 2 KI TU          ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(56 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Hoc Ky Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			hocKy_ch[vitri] = (char)key;
			cout << hocKy_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(56 + vitri, 8);
			cout << " ";
		}
		if (key == LEFT) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> lopTinChi.hocKy;
			//

			vitri = strlen(nienKhoa_ch); //Nien Khoa Set Bat Buoc 4 So
			gotoxy(44 + vitri, 8);
			goto NIENKHOA;
		}

		if (key == RIGHT || key == ENTER) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> lopTinChi.hocKy;
			//

			if (CheckFieldTonTai(lopTinChi, ds_ltc, "hk") == -1) {
				Alert("Hoc Ky Khong Ton Tai", 34, 26, 4, 900);
				continue;
			}

			vitri = (lopTinChi.nhom > 9) ? 2 : (lopTinChi.nhom == 0) ? 0 : 1;
			/*if (tinChi.nhom == 0)
				vitri = 0;*/
			gotoxy(56 + vitri, 8);
			goto NHOM;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
NHOM:
	char nhom_ch[3];

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 28);
	cout << "                                                           ";
	gotoxy(18, 29);
	cout << "       NHOM: GOM CAC SO (0-9), TOI DA: 2 KI TU             ";
	gotoxy(18, 30);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(65 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Nhom Khong Duoc Bat Dau Bang So 0 ", 34, 26, 4, 900);
				continue;
			}
			nhom_ch[vitri] = (char)key;
			cout << nhom_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(65 + vitri, 8);
			cout << " ";
		}

		if (key == LEFT) {
			nhom_ch[vitri] = '\0';
			if (nhom_ch[0] == '\0') {
				Alert("Nhom Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> lopTinChi.nhom;
			//

			vitri = (lopTinChi.hocKy > 9) ? 2 : (lopTinChi.hocKy == 0) ? 0 : 1;
			gotoxy(56 + vitri, 8);
			goto HOCKY;
		}
		if (key == RIGHT || key == ENTER) {
			nhom_ch[vitri] = '\0';
			if (nhom_ch[0] == '\0') {
				Alert("Nhom Chua Nhap", 34, 26, 4, 900);
				continue;
			}

			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> lopTinChi.nhom;
			//

			int i = CheckFieldTonTai(lopTinChi, ds_ltc, "l");
			if (i == -1) {
				Alert("Lop Tin Chi Khong Ton Tai", 34, 26, 4, 900);
				continue;
			} else {
				InDSDKCon(ds_ltc, i);
			}
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
	if (key == ESC) {
		clrscr();
		return;
	}
}
//------------------------------------------KET THUC IN DANH SACH DANG KY LOP TIN CHI----------------------------------------

//-------------------------------------------------QUAN LY SINH VIEN-------------------------------------------------------
void InitializeDSSV(DS_SinhVien* first) {
	first = NULL;
	return;
}

void LuuFileLop() {
	std::ofstream fileOutput("E:/DevC/AAAAA/ProjectCTDL/DSLOP.txt");
	string data;
	if (fileOutput.fail()) {
		cout << "Failed to open this file!" << endl;
		return;
	}

	DS_SinhVien* p = first;
	while (p != NULL) {
		fileOutput << p->sinhVien.maLop << endl
			<< p->sinhVien.maSV << endl
			<< p->sinhVien.ho << endl
			<< p->sinhVien.ten << endl
			<< p->sinhVien.namNhapHoc << endl
			<< p->sinhVien.sdt << endl
			<< ((p->sinhVien.phai) ? "NAM" : "NU") << endl;
		p = p->next;
	}
	return;
}

void DocFileLop() {
	std::ifstream fileInput("E:/DevC/AAAAA/ProjectCTDL/DSLOP.txt", std::ios::in);
	string data;
	if (fileInput.fail())
		cout << "Failed to open this file!" << endl;
	getline(fileInput, data);
	if (data.size() == 0)
		return;

	DS_SinhVien* p = NULL;
	DS_SinhVien* currentSV = new DS_SinhVien;
	strcpy_s(currentSV->sinhVien.maLop, data.c_str());
	getline(fileInput, data);
	strcpy_s(currentSV->sinhVien.maSV, data.c_str());
	getline(fileInput, data);
	strcpy_s(currentSV->sinhVien.ho, data.c_str());
	getline(fileInput, data);
	strcpy_s(currentSV->sinhVien.ten, data.c_str());
	getline(fileInput, data);
	currentSV->sinhVien.namNhapHoc = std::stoi(data);
	getline(fileInput, data);
	strcpy_s(currentSV->sinhVien.sdt, data.c_str());
	getline(fileInput, data);
	currentSV->sinhVien.phai = (data == "NAM") ? 1 : 0;
	currentSV->next = NULL;

	first = currentSV;
	p = currentSV;

	while (!fileInput.eof()) {
		getline(fileInput, data);
		if (data.size() == 0)
			return;

		currentSV = new DS_SinhVien;
		strcpy_s(currentSV->sinhVien.maLop, data.c_str());
		getline(fileInput, data);
		strcpy_s(currentSV->sinhVien.maSV, data.c_str());
		getline(fileInput, data);
		strcpy_s(currentSV->sinhVien.ho, data.c_str());
		getline(fileInput, data);
		strcpy_s(currentSV->sinhVien.ten, data.c_str());
		getline(fileInput, data);
		currentSV->sinhVien.namNhapHoc = std::stoi(data);
		getline(fileInput, data);
		strcpy_s(currentSV->sinhVien.sdt, data.c_str());
		getline(fileInput, data);
		currentSV->sinhVien.phai = (data == "NAM") ? 1 : 0;
		currentSV->next = NULL;
		p->next = currentSV;
		p = currentSV;
	}
	return;
}

int isExistClass(char maLop[]) {
	DS_SinhVien* p = first;
	int count = 0;
	if (p == NULL)
		return count;
	while (p != NULL) {
		if (strcmp(maLop, p->sinhVien.maLop) == 0) {
			count++;
			if (p->next != NULL && strcmp(p->sinhVien.maLop, p->next->sinhVien.maLop) != 0) //Tranh duyet het dsach
				break;
		}
		p = p->next;
	}
	return count;
}

void PhanTrangLopSinhVien(char maLop[], int& trang, string choice = "") {
	//Phan Trang
	int dem = 0, tongTrang = 0;
	DS_SinhVien* p = first;
	int siSo = isExistClass(maLop);

	KhungDSachSV();
	SetColor(4);
	SetBGColor(7);
	gotoxy(14, 15);
	cout << maLop;
	if (siSo == 0)
		return;

	tongTrang = ((siSo - 1) / 15 + 1);
	if (choice == "F3" && trang < (tongTrang - 1)) {
		trang++;
	}
	if (choice == "F2" && trang > 0) {
		trang--;
	}
	if (siSo < 15) {
		tongTrang = 1;
		trang = 0;
	}

	SetColor(1);
	SetBGColor(7);
	gotoxy(84, 36);
	cout << trang + 1 << "/" << tongTrang;

	while (true) { //Tro toi lop can tim
		if (strcmp(p->sinhVien.maLop, maLop) == 0)
			break;
		p = p->next;
	}
	if (trang > 0) {
		for (int i = 0; i < 15 + (trang - 1) * 15; i++) //i = 1 vi p dang la sv 1
			p = p->next;
	}

	//for (int i = 0; i < 15 && p != NULL && strcmp(p->sinhVien.maLop, maLop) == 0; i++, p = p->next) {
	for (int i = trang * 15; i < 15 + trang * 15 && p != NULL && strcmp(p->sinhVien.maLop, maLop) == 0; i++, p = p->next) {
		int index = i - trang * 15;
		SetBGColor(7);
		SetColor(6);
		gotoxy(5, 20 + index);
		cout << (i + 1);
		SetColor(1);
		gotoxy(9, 20 + index);
		cout << p->sinhVien.maSV;
		gotoxy(23, 20 + index);
		cout << p->sinhVien.ho;
		gotoxy(46, 20 + index);
		cout << p->sinhVien.ten;
		gotoxy(64, 20 + index);
		cout << p->sinhVien.namNhapHoc;
		gotoxy(72, 20 + index);
		cout << p->sinhVien.sdt;
		gotoxy(85, 20 + index);
		cout << ((p->sinhVien.phai) ? "NAM" : "NU");
	}
	return;
}

int AddIfNoneExist(SinhVien sv) { //Chac chan lop co ton tai
	DS_SinhVien* p, * t = NULL, * s = NULL;
	p = new DS_SinhVien;
	p->sinhVien = sv;
	p->next = NULL;

	int count = 0;
	for (s = first; s != NULL; t = s, s = s->next) {
		if (strcmp(s->sinhVien.maLop, sv.maLop) == 0) {
			delete p;
			return 0;
		}
		//count++;
	}
	for (s = first; s != NULL && strcmp(s->sinhVien.maLop, sv.maLop) < 0; t = s, s = s->next);
	/*if (count == 0) {
		if (s == first) {
			p->next = first;
			first = p;
		} else {
			p->next = s;
			t->next = p;
		}
		return 1;
	}*/
	if (s == first) {
		p->next = first;
		first = p;
	} else {
		p->next = s;
		t->next = p;
	}
	return 1;
}

//Them sinh vien co thu tu theo malop + mssv
void Insert_Order(SinhVien sv) {
	DS_SinhVien* p, * t = NULL, * s = NULL;
	p = new DS_SinhVien;
	p->sinhVien = sv;
	p->next = NULL;

	DS_SinhVien* start = NULL, * bstart = NULL;
	bstart = first;
	start = first;

	if (AddIfNoneExist(sv)) {
		delete p;
		return;
	}
	//for (s = start; s != NULL && strcmp(s->sinhVien.maLop, sv.maLop) == 0 && strcmp(s->sinhVien.maSV, sv.maSV) < 0; t = s, bstart = t, s = s->next, start = s);
	for (start = first; start != NULL && strcmp(start->sinhVien.maLop, sv.maLop) < 0; bstart = start, start = start->next);
	for (s = start, t = bstart;
		s != NULL && strcmp(s->sinhVien.maSV, sv.maSV) < 0 && strcmp(s->sinhVien.maLop, sv.maLop) == 0;
		t = s, s = s->next);
	/*if (bstart == start) {
		p->next = start;
		first = p;
		start = p;
		bstart = p;
	} else {
		p->next = s;
		t->next = p;
	}*/
	if (t == s) {
		p->next = start;
		first = p;
		//start = p;
		//bstart = p;
	} else {
		p->next = s;
		t->next = p;
	}
	return;
}

int CheckTrungMSSV(char mssv[], char maLop[], string choice = "0") { // 0 - mssv   1 - mssv + malop
	DS_SinhVien* p = first;
	while (p != NULL) {
		if (choice == "0") {
			if (strcmp(mssv, p->sinhVien.maSV) == 0)
				return 1;
		}
		if (choice == "1") {
			if (strcmp(maLop, p->sinhVien.maLop) == 0 && strcmp(mssv, p->sinhVien.maSV) == 0)
				return 1;
		}
		p = p->next;
	}
	return 0;
}

void ThemSinhVienTheoLop(DS_SinhVien& ds_sv, SinhVien& sv) {
	int trang = 0;
	int count = 0, vitri = 0, key;
	/*DS_SinhVien* p, * t = NULL, * s = NULL;
	p = new DS_SinhVien;
	p->sinhVien = sv;
	p->next = NULL;*/

	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';
	bool sex = true; //TRUE = nam; FALSE = nu

	PhanTrangLopSinhVien(sv.maLop, trang);
MASV:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "    MA SV: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 11 KI TU    ";
	gotoxy(18, 40);
	cout << "                                                           ";

	while (true) {

		//Nhap Ma Sinh Vien
		SetColor(3);
		SetBGColor(7);
		gotoxy(10 + vitri, 12);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 11)) {
			sv.maSV[vitri] = toupper((char)key);
			cout << sv.maSV[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(10 + vitri, 12);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			sv.maSV[vitri] = '\0';
			if (sv.maSV[0] == '\0') {
				return; //Thoat Bang Cach Nhap Rong
			}
			if (CheckTrungMSSV(sv.maSV, sv.maLop) == 1) {
				Alert("Ma Sinh Vien Trung!!!", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoxy(44 + vitri, 8);
			goto HO;
		}
		if (key == F3)
			PhanTrangLopSinhVien(sv.maLop, trang, "F3");
		if (key == F2)
			PhanTrangLopSinhVien(sv.maLop, trang, "F2");
	}
HO:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "   HO SINH VIEN: GOM CAC KI TU (A-Z), TOI DA: 20 KI TU     ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(24 + vitri, 12);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 20)) {
			sv.ho[vitri] = toupper((char)key);
			cout << sv.ho[vitri];
			vitri++;
		}
		if (key == SPACE && vitri > 0 && vitri < 20 && sv.ho[vitri - 1] != ' ') {
			gotoxy(24 + vitri, 12);
			cout << " ";
			sv.ho[vitri] = ' ';
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(24 + vitri, 12);
			cout << " ";
			gotoxy(24 + vitri, 12);
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if ((key == ENTER || key == RIGHT) && vitri != 0) {
			if (sv.ho[vitri - 1] == ' ')
				vitri--;
			sv.ho[vitri] = '\0';
			vitri = strlen(sv.ten);
			gotoxy(47 + vitri, 12);
			goto TEN;
		}
		if (key == ENTER || key == RIGHT) {
			if (sv.ho[0] == '\0')
				Alert("Chua Nhap Ho", 34, 15, 4, 900);
		}
		if (key == LEFT) {
			sv.ho[vitri] = '\0';
			if (sv.ho[0] == '\0') {
				Alert("Chua Nhap Ho", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.maSV);
			gotoxy(10 + vitri, 12);
			goto MASV;
		}
	}
TEN:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "  TEN SINH VIEN: GOM CAC KI TU (A-Z), TOI DA: 14 KI TU     ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(47 + vitri, 12);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 14)) {
			sv.ten[vitri] = toupper((char)key);
			cout << sv.ten[vitri];
			vitri++;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if ((key == ENTER || key == RIGHT) && vitri != 0) {
			sv.ten[vitri] = '\0';
			vitri = strlen(nienKhoa_ch);
			gotoxy(64 + vitri, 12);
			goto NIENKHOA;
		}
		if (key == RIGHT || key == ENTER) {
			if (sv.ten[0] == '\0')
				Alert("Chua Nhap Ten", 34, 15, 4, 900);
		}
		if (key == LEFT) {
			sv.ten[vitri] = '\0';
			if (sv.ten[0] == '\0') {
				Alert("Chua Nhap Ten", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoxy(24 + vitri, 12);
			goto HO;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(47 + vitri, 12);
			cout << " ";
			gotoxy(47 + vitri, 12);
		}
	}
NIENKHOA:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "        NAM NHAP HOC: GOM CAC SO (0-9), GOM: 4 SO          ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(64 + vitri, 12);
		key = GetKey();

		if (key >= '0' && key <= '9' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 34, 15, 4, 900);
				continue;
			}
			nienKhoa_ch[vitri] = (char)key;
			cout << nienKhoa_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(64 + vitri, 12);
			cout << " ";
		}
		if (key == LEFT) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 15, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> sv.namNhapHoc;
			//

			vitri = strlen(sv.ten);
			gotoxy(64 + vitri, 12);
			goto TEN;
		}
		if (key == RIGHT || key == ENTER) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 15, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> sv.namNhapHoc;
			//

			vitri = strlen(sv.sdt);
			gotoxy(72 + vitri, 12);
			goto SDT;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
SDT:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "        SO DIEN THOAI: GOM CAC SO (0-9), GOM: 9 SO         ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(72 + vitri, 12);
		key = GetKey();

		if (key >= '0' && key <= '9' && vitri < 9) {
			sv.sdt[vitri] = (char)key;
			cout << sv.sdt[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(72 + vitri, 12);
			cout << " ";
		}
		if (key == LEFT) {
			sv.sdt[vitri] = '\0';
			if (sv.sdt[0] == '\0' || strlen(sv.sdt) < 3) {
				Alert("SDT Chua Nhap", 34, 15, 4, 900);
				continue;
			}

			vitri = strlen(nienKhoa_ch);
			gotoxy(64 + vitri, 12);
			goto NIENKHOA;
		}
		if (key == RIGHT || key == ENTER) {
			sv.sdt[vitri] = '\0';
			if (sv.sdt[0] == '\0' || strlen(sv.sdt) < 4) {
				Alert("SDT Chua Nhap", 34, 15, 4, 900);
				continue;
			}
			goto PHAI;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
PHAI:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "           GIOI TINH: NAM CHON NAM, NU CHON NU             ";
	gotoxy(18, 40);
	cout << "                                                           ";

	//bool sex = true; //TRUE = nam; FALSE = nu
	if (sex == true) {
		SetColor(1);
		SetBGColor(6);
		gotoxy(84, 10);
		cout << " NAM ";

		SetColor(1);
		SetBGColor(7);
		gotoxy(84, 12);
		cout << " NU  ";
	} else {
		SetColor(1);
		SetBGColor(7);
		gotoxy(84, 10);
		cout << " NAM ";

		SetColor(1);
		SetBGColor(6);
		gotoxy(84, 12);
		cout << " NU  ";
	}
	while (true) {
		key = GetKey();
		if (key == UP || key == DOWN) {
			sex = !sex;
			if (sex == true) {
				SetColor(1);
				SetBGColor(6);
				gotoxy(84, 10);
				cout << " NAM ";

				SetColor(1);
				SetBGColor(7);
				gotoxy(84, 12);
				cout << " NU  ";
			} else {
				SetColor(1);
				SetBGColor(7);
				gotoxy(84, 10);
				cout << " NAM ";

				SetColor(1);
				SetBGColor(6);
				gotoxy(84, 12);
				cout << " NU  ";
			}
			gotoxy(1, 1);
			cout << sex;
		}
		if (key == LEFT) {
			vitri = strlen(sv.sdt);
			gotoxy(72 + vitri, 12);
			goto SDT;
		}
		if (key == RIGHT || key == ENTER) {
			(sex) ? sv.phai = 1 : sv.phai = 0;
			TurnOKButton(true);
			goto OK;
		}
	}
OK:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "    NHAN OK DE DONG Y DU LIEU! (VUI LONG KIEM TRA LAI!!)   ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		key = GetKey();
		if (key == LEFT) {
			TurnOKButton(false);
			goto PHAI;
		}
		if (key == ENTER) {
			Insert_Order(sv);
			PhanTrangLopSinhVien(sv.maLop, trang);
			KhungThemSinhVien();

			sv.maSV[0] = '\0';
			sv.ho[0] = '\0';
			sv.ten[0] = '\0';
			sv.sdt[0] = '\0';
			sv.namNhapHoc = 0;
			sv.phai = 0;
			nienKhoa_ch[0] = '\0';
			vitri = 0;
			sex = true; //TRUE = nam; FALSE = nu
			goto MASV;
		}
	}
}

void SuaSinhVienTheoLop(SinhVien& sv) {
	int trang = 0;
	int count = 0, vitri = 0, key;

	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';
	bool sex = true; //TRUE = nam; FALSE = nu

	PhanTrangLopSinhVien(sv.maLop, trang);
MASV:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "    MA SV: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 11 KI TU    ";
	gotoxy(18, 40);
	cout << "                                                           ";

	while (true) {

		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(10 + vitri, 12);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 11)) {
			sv.maSV[vitri] = toupper((char)key);
			cout << sv.maSV[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(10 + vitri, 12);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			sv.maSV[vitri] = '\0';
			if (sv.maSV[0] == '\0') {
				return; //Thoat Bang Cach Nhap Rong
			}
			if (CheckTrungMSSV(sv.maSV, sv.maLop, "1") != 1) {
				Alert("Ma Sinh Vien Khong Co Trong Lop!!!", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoxy(44 + vitri, 8);
			goto HO;
		}
		if (key == F3)
			PhanTrangLopSinhVien(sv.maLop, trang, "F3");
		if (key == F2)
			PhanTrangLopSinhVien(sv.maLop, trang, "F2");
	}
HO:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "   HO SINH VIEN: GOM CAC KI TU (A-Z), TOI DA: 20 KI TU     ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(24 + vitri, 12);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 20)) {
			sv.ho[vitri] = toupper((char)key);
			cout << sv.ho[vitri];
			vitri++;
		}
		if (key == SPACE && vitri > 0 && vitri < 20 && sv.ho[vitri - 1] != ' ') {
			gotoxy(24 + vitri, 12);
			cout << " ";
			sv.ho[vitri] = ' ';
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(24 + vitri, 12);
			cout << " ";
			gotoxy(24 + vitri, 12);
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if ((key == ENTER || key == RIGHT) && vitri != 0) {
			if (sv.ho[vitri - 1] == ' ')
				vitri--;
			sv.ho[vitri] = '\0';
			vitri = strlen(sv.ten);
			gotoxy(47 + vitri, 12);
			goto TEN;
		}
		if (key == ENTER || key == RIGHT) {
			if (sv.ho[0] == '\0')
				Alert("Chua Nhap Ho", 34, 15, 4, 900);
		}
		if (key == LEFT) {
			sv.ho[vitri] = '\0';
			if (sv.ho[0] == '\0') {
				Alert("Chua Nhap Ho", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.maSV);
			gotoxy(10 + vitri, 12);
			goto MASV;
		}
	}
TEN:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "  TEN SINH VIEN: GOM CAC KI TU (A-Z), TOI DA: 14 KI TU     ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(47 + vitri, 12);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 14)) {
			sv.ten[vitri] = toupper((char)key);
			cout << sv.ten[vitri];
			vitri++;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if ((key == ENTER || key == RIGHT) && vitri != 0) {
			sv.ten[vitri] = '\0';
			vitri = strlen(nienKhoa_ch);
			gotoxy(64 + vitri, 12);
			goto NIENKHOA;
		}
		if (key == RIGHT || key == ENTER) {
			if (sv.ten[0] == '\0')
				Alert("Chua Nhap Ten", 34, 15, 4, 900);
		}
		if (key == LEFT) {
			sv.ten[vitri] = '\0';
			if (sv.ten[0] == '\0') {
				Alert("Chua Nhap Ten", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoxy(24 + vitri, 12);
			goto HO;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(47 + vitri, 12);
			cout << " ";
			gotoxy(47 + vitri, 12);
		}
	}
NIENKHOA:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "        NAM NHAP HOC: GOM CAC SO (0-9), GOM: 4 SO          ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(64 + vitri, 12);
		key = GetKey();

		if (key >= '0' && key <= '9' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 34, 15, 4, 900);
				continue;
			}
			nienKhoa_ch[vitri] = (char)key;
			cout << nienKhoa_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(64 + vitri, 12);
			cout << " ";
		}
		if (key == LEFT) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 15, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> sv.namNhapHoc;
			//

			vitri = strlen(sv.ten);
			gotoxy(64 + vitri, 12);
			goto TEN;
		}
		if (key == RIGHT || key == ENTER) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 34, 15, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> sv.namNhapHoc;
			//

			vitri = strlen(sv.sdt);
			gotoxy(72 + vitri, 12);
			goto SDT;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
SDT:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "        SO DIEN THOAI: GOM CAC SO (0-9), GOM: 9 SO         ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(72 + vitri, 12);
		key = GetKey();

		if (key >= '0' && key <= '9' && vitri < 9) {
			sv.sdt[vitri] = (char)key;
			cout << sv.sdt[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(72 + vitri, 12);
			cout << " ";
		}
		if (key == LEFT) {
			sv.sdt[vitri] = '\0';
			if (sv.sdt[0] == '\0' || strlen(sv.sdt) < 3) {
				Alert("SDT Chua Nhap", 34, 15, 4, 900);
				continue;
			}

			vitri = strlen(nienKhoa_ch);
			gotoxy(64 + vitri, 12);
			goto NIENKHOA;
		}
		if (key == RIGHT || key == ENTER) {
			sv.sdt[vitri] = '\0';
			if (sv.sdt[0] == '\0' || strlen(sv.sdt) < 4) {
				Alert("SDT Chua Nhap", 34, 15, 4, 900);
				continue;
			}
			goto PHAI;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
PHAI:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "           GIOI TINH: NAM CHON NAM, NU CHON NU             ";
	gotoxy(18, 40);
	cout << "                                                           ";

	//bool sex = true; //TRUE = nam; FALSE = nu
	if (sex == true) {
		SetColor(1);
		SetBGColor(6);
		gotoxy(84, 10);
		cout << " NAM ";

		SetColor(1);
		SetBGColor(7);
		gotoxy(84, 12);
		cout << " NU  ";
	} else {
		SetColor(1);
		SetBGColor(7);
		gotoxy(84, 10);
		cout << " NAM ";

		SetColor(1);
		SetBGColor(6);
		gotoxy(84, 12);
		cout << " NU  ";
	}
	while (true) {
		key = GetKey();
		if (key == UP || key == DOWN) {
			sex = !sex;
			if (sex == true) {
				SetColor(1);
				SetBGColor(6);
				gotoxy(84, 10);
				cout << " NAM ";

				SetColor(1);
				SetBGColor(7);
				gotoxy(84, 12);
				cout << " NU  ";
			} else {
				SetColor(1);
				SetBGColor(7);
				gotoxy(84, 10);
				cout << " NAM ";

				SetColor(1);
				SetBGColor(6);
				gotoxy(84, 12);
				cout << " NU  ";
			}
			gotoxy(1, 1);
			cout << sex;
		}
		if (key == LEFT) {
			vitri = strlen(sv.sdt);
			gotoxy(72 + vitri, 12);
			goto SDT;
		}
		if (key == RIGHT || key == ENTER) {
			(sex) ? sv.phai = 1 : sv.phai = 0;
			TurnOKButton(true);
			goto OK;
		}
	}
OK:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "    NHAN OK DE DONG Y DU LIEU! (VUI LONG KIEM TRA LAI!!)   ";
	gotoxy(18, 40);
	cout << "                                                           ";
	while (true) {
		key = GetKey();
		if (key == LEFT) {
			TurnOKButton(false);
			goto PHAI;
		}
		if (key == ENTER) {
			DS_SinhVien* p = first;
			while (p != NULL) {
				if (strcmp(p->sinhVien.maSV, sv.maSV) == 0) {
					strcpy_s(p->sinhVien.ho, sv.ho);
					strcpy_s(p->sinhVien.ten, sv.ten);
					p->sinhVien.namNhapHoc = sv.namNhapHoc;
					strcpy_s(p->sinhVien.sdt, sv.sdt);
					p->sinhVien.phai = sv.phai;
					break;
				}
				p = p->next;
			}
			PhanTrangLopSinhVien(sv.maLop, trang);
			KhungThemSinhVien();

			sv.maSV[0] = '\0';
			sv.ho[0] = '\0';
			sv.ten[0] = '\0';
			sv.sdt[0] = '\0';
			sv.namNhapHoc = 0;
			sv.phai = 0;
			nienKhoa_ch[0] = '\0';
			vitri = 0;
			sex = true; //TRUE = nam; FALSE = nu
			goto MASV;
		}
	}
	return;
}

void ThemSinhVien(DS_SinhVien& ds_sv, string choice = "them") {
	int key, vitri = 0;

	SinhVien sv;
	sv.maLop[0] = '\0';
	sv.maSV[0] = '\0';
	sv.ho[0] = '\0';
	sv.ten[0] = '\0';
	sv.sdt[0] = '\0';
	sv.namNhapHoc = 0;
	sv.phai = 0;


	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "   MA LOP: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 14 KI TU    ";
	gotoxy(18, 40);
	cout << "                                                           ";

	KhungThemSinhVien();
	while (true) {
		//Nhap Ma Lop
		SetColor(4);
		SetBGColor(7);
		gotoxy(41 + vitri, 7);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 14)) {
			sv.maLop[vitri] = toupper((char)key);
			cout << sv.maLop[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(41 + vitri, 7);
			cout << " ";
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if (key == ENTER) {
			sv.maLop[vitri] = '\0';
			if (sv.maLop[0] == '\0')
				Alert("Chua Nhap Ma Lop!!!", 34, 26, 4, 900);
			else {
				if (choice == "them")
					ThemSinhVienTheoLop(ds_sv, sv);
				if (choice == "sua")
					SuaSinhVienTheoLop(sv);
				break;
			}
		}
	}
	return;
}

int KiemTraLopCanXoa(DS_SinhVien* bstart, DS_SinhVien* start, SinhVien sv) {
	while (start != NULL) {
		if (strcmp(start->sinhVien.maLop, sv.maLop) == 0) {
			return 1;
		}
		bstart = start;
		start = start->next;
	}
	return 0;
}

int KiemTraSVCanXoa(DS_SinhVien* bstart, DS_SinhVien* start, SinhVien sv) {
	DS_SinhVien* t = bstart;
	DS_SinhVien* s = start;
	while (s != NULL) {
		if (strcmp(s->sinhVien.maSV, sv.maSV) == 0 && strcmp(s->sinhVien.maLop, sv.maLop) == 0) {
			if (s == first) {
				first = s->next;
				delete s;
				return 1;
			} else {
				t->next = s->next;
				delete s;
				return 1;
			}
		}
		t = s;
		s = s->next;
	}
	return 0;
}

int KiemTraSvTrongLop(DS_LopTinChi& ds_ltc, SinhVien sv) { //Khong xoa sinh vien da dk lop tin chi
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		DS_DangKy* p = ds_ltc.ds[i]->head;
		while (p != NULL) {
			if (strcmp(p->dangKy.maSV, sv.maSV) == 0)
				return 1;
			p = p->next;
		}
	}
	return 0;
}

void NhapMSSVDeXoa(DS_LopTinChi& ds_ltc, DS_SinhVien* bstart, DS_SinhVien* start, SinhVien& sv) {
	KhungXoaSinhVien();
	gotoxy(42, 5);
	cout << "MA SINH VIEN";

	int key, vitri = 0, trang = 0;

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "    MA SV: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 11 KI TU    ";
	gotoxy(18, 40);
	cout << "                                                           ";

	PhanTrangLopSinhVien(sv.maLop, trang);
	while (true) {
		if (isExistClass(sv.maLop) == 0) {
			return;
		}
		//Nhap Ma Sinh Vien
		SetColor(4);
		SetBGColor(7);
		gotoxy(41 + vitri, 7);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 11)) {
			sv.maSV[vitri] = toupper((char)key);
			cout << sv.maSV[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(41 + vitri, 7);
			cout << " ";
		}
		if (key == ENTER) {
			sv.maSV[vitri] = '\0';
			if (sv.maSV[0] == '\0') {
				return; //Thoat Bang Cach Nhap Rong
			}
			bool choice = false;
			while (true) {
				ButtonXacNhanXoaSV(choice);
				key = GetKey();
				if (key == RIGHT || key == LEFT) {
					choice = !choice;
				}
				if (key == ENTER) {
					if (choice == false) {
						SetBGColor(7);
						gotoxy(38, 10);
						cout << "                      ";
						gotoxy(38, 11);
						cout << "                      ";
						gotoxy(38, 12);
						cout << "                      ";
						gotoxy(38, 13);
						cout << "                      ";
						gotoxy(38, 14);
						cout << "                      ";
						break;
					}
					if (choice == true) {
						if (KiemTraSvTrongLop(ds_ltc, sv)) {
							Alert("Khong Duoc Xoa Sinh Vien Nay!!!", 34, 15, 4, 900);
							SetBGColor(7);
							gotoxy(38, 10);
							cout << "                      ";
							gotoxy(38, 11);
							cout << "                      ";
							gotoxy(38, 12);
							cout << "                      ";
							gotoxy(38, 13);
							cout << "                      ";
							gotoxy(38, 14);
							cout << "                      ";
							break;
						}
						if (KiemTraSVCanXoa(bstart, start, sv) == 0) {
							Alert("Ma Sinh Vien Khong Co Trong Lop!!!", 34, 15, 4, 900);

							SetBGColor(7);
							gotoxy(38, 10);
							cout << "                      ";
							gotoxy(38, 11);
							cout << "                      ";
							gotoxy(38, 12);
							cout << "                      ";
							gotoxy(38, 13);
							cout << "                      ";
							gotoxy(38, 14);
							cout << "                      ";
							break;
						} else {
							Alert("Da Xoa Sinh Vien!!!", 34, 15, 4, 900);

							SetBGColor(7);
							gotoxy(38, 10);
							cout << "                      ";
							gotoxy(38, 11);
							cout << "                      ";
							gotoxy(38, 12);
							cout << "                      ";
							gotoxy(38, 13);
							cout << "                      ";
							gotoxy(38, 14);
							cout << "                      ";
							PhanTrangLopSinhVien(sv.maLop, trang);
							break;
						}
					}
				}
			}
		}
		if (key == F3)
			PhanTrangLopSinhVien(sv.maLop, trang, "F3");
		if (key == F2)
			PhanTrangLopSinhVien(sv.maLop, trang, "F2");
	}
	return;
}

void XoaSinhVien(DS_LopTinChi& ds_ltc, DS_SinhVien& ds_sv) {
	int key, vitri = 0;
	SinhVien sv;
	DS_SinhVien* start = first, * bstart = first; //Con tro track lop can xoa
	sv.maLop[0] = '\0';
	sv.maSV[0] = '\0';
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "   MA LOP: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 14 KI TU    ";
	gotoxy(18, 40);
	cout << "                                                           ";
	KhungXoaSinhVien();
	while (true) {
		//Nhap Ma Lop
		SetColor(4);
		SetBGColor(7);
		gotoxy(41 + vitri, 7);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 14)) {
			sv.maLop[vitri] = toupper((char)key);
			cout << sv.maLop[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(41 + vitri, 7);
			cout << " ";
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if (key == ENTER) {
			sv.maLop[vitri] = '\0';
			if (sv.maLop[0] == '\0') {
				Alert("Chua Nhap Ma Lop!!!", 34, 26, 4, 900);
				continue;
			}
			if (KiemTraLopCanXoa(bstart, start, sv)) {
				NhapMSSVDeXoa(ds_ltc, bstart, start, sv);
				return;
			} else {
				Alert("Lop Khong Ton Tai!!!", 34, 26, 4, 900);
				continue;
			}
		}
	}
	return;
}

void LatTrangGoiYLop(int trang, int key = 1) {
	KhungGoiYLop();

	int tongTrang = 0;
	int tongLop = 0;
	DS_SinhVien* p = first;
	char temp_maLop[15];
	temp_maLop[0] = '\0';

	while (p != NULL) {
		if (strcmp(temp_maLop, p->sinhVien.maLop) != 0) {
			tongLop++;
			strcpy_s(temp_maLop, p->sinhVien.maLop);
		}
		p = p->next;
	}

	//Mang chua cac lop
	string* ds = new string[tongLop];
	p = first;
	temp_maLop[0] = '\0';
	int i = 0;
	while (p != NULL) {
		if (strcmp(temp_maLop, p->sinhVien.maLop) != 0) {
			ds[i] = string(p->sinhVien.maLop);
			strcpy_s(temp_maLop, p->sinhVien.maLop);
			i++;
		}
		p = p->next;
	}

	if (tongLop == 0)
		return;
	tongTrang = (tongLop - 1) / 8 + 1;


	if (key == LEFT && trang > 0) {
		trang--;
	}
	if (key == RIGHT && trang < (tongTrang - 1)) {
		trang++;
	}

	if (tongLop <= 8) {
		tongTrang = 1;
		trang = 0;
	}

	SetColor(1);
	SetBGColor(7);
	gotoxy(50, 24);
	cout << trang + 1 << "/" << tongTrang;
	SetColor(4);
	gotoxy(42, 13);
	cout << "CAC MA LOP";

	p = first;
	temp_maLop[0] = '\0';
	//Skip item lat trang
	for (int i = trang * 8; i < 8 + trang * 8 && i < tongLop; i++) {
		int index = i - trang * 8;
		SetColor(1);
		SetBGColor(7);
		gotoxy(41, 15 + index);
		cout << ds[i];
	}
	return;
}

void InDSSVCon(char maLop[]) {
	int key, trang = 0;

	gotoxy(38, 12);
	cout << "                   ";
	gotoxy(38, 13);
	cout << "                   ";
	gotoxy(38, 14);
	cout << "                   ";
	gotoxy(38, 15);
	cout << "                   ";
	gotoxy(38, 16);
	cout << "                   ";
	gotoxy(38, 17);
	cout << "                   ";
	gotoxy(38, 18);
	cout << "                   ";
	gotoxy(38, 19);
	cout << "                   ";
	gotoxy(38, 20);
	cout << "                   ";
	gotoxy(38, 21);
	cout << "                   ";
	gotoxy(38, 22);
	cout << "                   ";
	gotoxy(38, 23);
	cout << "                   ";
	gotoxy(38, 24);
	cout << "                   ";
	gotoxy(38, 25);
	cout << "                   ";
	PhanTrangLopSinhVien(maLop, trang);
	KhungHuongDanInDSSV();
	while (true) {
		key = GetKey();
		if (key == RIGHT) {
			PhanTrangLopSinhVien(maLop, trang, "F3");
			KhungHuongDanInDSSV();
		}
		if (key == LEFT) {
			PhanTrangLopSinhVien(maLop, trang, "F2");
			KhungHuongDanInDSSV();
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
	return;
}

void InDSSV() {
	KhungInDSSV();
	int key, vitri = 0, trang = 0;
	char maLop[15];
	maLop[0] = '\0';

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "   MA LOP: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 14 KI TU    ";
	gotoxy(18, 40);
	cout << "                                                           ";
	LatTrangGoiYLop(trang);
	while (true) {
		//Nhap Ma Lop
		SetColor(4);
		SetBGColor(7);
		gotoxy(41 + vitri, 7);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 14)) {
			maLop[vitri] = toupper((char)key);
			cout << maLop[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(41 + vitri, 7);
			cout << " ";
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if (key == ENTER) {
			maLop[vitri] = '\0';
			if (maLop[0] == '\0') {
				Alert("Chua Nhap Ma Lop!!!", 38, 10, 4, 900);
				continue;
			}
			if (isExistClass(maLop) == 0) {
				Alert("Lop Khong Ton Tai!!!", 38, 10, 4, 900);
				continue;
			}
			InDSSVCon(maLop);
			KhungInDSSV();
			maLop[0] = '\0';
			vitri = 0;
			LatTrangGoiYLop(trang, key);
		}
		if (key == LEFT || key == RIGHT) {
			LatTrangGoiYLop(trang, key);
		}
	}
	system("pause");
	return;
}
//--------------------------------------------KET THUC QUAN LY SINH VIEN---------------------------------------------------

//---------------------------------------------QUAN LY MON HOC-------------------------------------------------------------
void InitializeTree(DS_MonHoc* root) {
	root = NULL;
	return;
}

void Luu_LNR(DS_MonHoc* p, ofstream& fileOutput) {
	if (p != NULL) {
		Luu_LNR(p->left, fileOutput);
		fileOutput << p->monHoc.maMonHoc << endl
			<< p->monHoc.tenMonHoc << endl
			<< p->monHoc.soTCLT << endl
			<< p->monHoc.soTCTH << endl;
		Luu_LNR(p->right, fileOutput);
	}
	return;
}

void LuuDSMH() {
	std::ofstream fileOutput("E:/DevC/AAAAA/ProjectCTDL/DSMH.txt");
	if (fileOutput.fail()) {
		cout << "Failed to open this file!" << endl;
		return;
	}
	Luu_LNR(tree, fileOutput);
	return;
}

//Search Key
DS_MonHoc* CheckTrungMMH(DS_MonHoc* root, char maMonHoc[]) { // địa chỉ là trùng ,NULL là không trùng
	DS_MonHoc* p = root;
	if (p == NULL)
		return p;
	while (p != NULL && strcmp(p->monHoc.maMonHoc, maMonHoc) != 0) {
		if (strcmp(maMonHoc, p->monHoc.maMonHoc) < 0)
			p = p->left;
		else
			p = p->right;
	}
	return p;
}

void InsertNode(DS_MonHoc*& p, MonHoc monHoc) { //Không reference là phải set lại root của tree nó ms lưu
	if (p == NULL) {			//p la nut la
		p = new DS_MonHoc;
		p->monHoc = monHoc;
		p->left = NULL;
		p->right = NULL;
	} else {
		if (strcmp(monHoc.maMonHoc, p->monHoc.maMonHoc) < 0)
			InsertNode(p->left, monHoc);
		if (strcmp(monHoc.maMonHoc, p->monHoc.maMonHoc) > 0)
			InsertNode(p->right, monHoc);
	}
	return;
}

void DocDSMH() {
	std::ifstream fileInput("E:/DevC/AAAAA/ProjectCTDL/DSMH.txt", std::ios::in);
	string data;
	MonHoc mh;
	if (fileInput.fail()) {
		cout << "Failed to open this file!" << endl;
		return;
	}
	while (!fileInput.eof()) {
		getline(fileInput, data);
		if (data.size() == 0) {
			return;
		}
		strcpy_s(mh.maMonHoc, data.c_str());
		getline(fileInput, data);
		strcpy_s(mh.tenMonHoc, data.c_str());
		getline(fileInput, data);
		mh.soTCLT = std::stoi(data);
		getline(fileInput, data);
		mh.soTCTH = std::stoi(data);
		InsertNode(tree, mh);
	}
	return;
}

//Đếm số Môn Học có trong cây
void DemInorder(DS_MonHoc* p, int& count) {
	if (p != NULL) {
		DemInorder(p->left, count);
		count++;
		DemInorder(p->right, count);
	}
}

//Đổi cây Môn Học thành Mảng Môn Học
void TreeToArray(DS_MonHoc* p, int& count, MonHoc* mhArr) {
	if (p != NULL) {
		TreeToArray(p->left, count, mhArr);
		mhArr[count] = p->monHoc;
		count++;
		TreeToArray(p->right, count, mhArr);
	}
}

void PhanTrangDSMonHoc(DS_MonHoc* p, int& trang, string choice = "") {
	KhungDSMonHoc();
	//Phan Trang
	int dem = 0, tongTrang = 0;
	int tongMonHoc = 0;
	DemInorder(tree, tongMonHoc);

	//con trỏ mảng chứa môn học
	MonHoc* mhArr = new MonHoc[tongMonHoc];
	int count = 0; //Biến đệ quy (không reset mỗi lần đệ quy)
	TreeToArray(tree, count, mhArr);

	if (tongMonHoc == 0)
		return;

	tongTrang = ((tongMonHoc - 1) / 15 + 1);
	if (choice == "F3" && trang < (tongTrang - 1)) {
		trang++;
	}
	if (choice == "F2" && trang > 0) {
		trang--;
	}
	if (tongMonHoc < 15) {
		tongTrang = 1;
		trang = 0;
	}

	SetColor(1);
	SetBGColor(7);
	gotoxy(77, 30);
	cout << trang + 1 << "/" << tongTrang;

	for (int i = trang * 15; i < 15 + trang * 15 && i < tongMonHoc; i++) {
		SetBGColor(7);
		SetColor(1);
		gotoxy(12, 14 + (i - trang * 15));
		cout << mhArr[i].maMonHoc;
		gotoxy(25, 14 + (i - trang * 15));
		cout << mhArr[i].tenMonHoc;
		gotoxy(65, 14 + (i - trang * 15));
		cout << mhArr[i].soTCLT;
		gotoxy(74, 14 + (i - trang * 15));
		cout << mhArr[i].soTCTH;
	}
	return;
}

// Không dùng nữa
void ThemMonHoc() {
	KhungThemMonHoc();
	KhungDSMonHoc();
	HuongDanThemMonHoc();
	int key, vitri = 0, trang = 0;
	PhanTrangDSMonHoc(tree, trang);

	MonHoc monHoc;
	monHoc.maMonHoc[0] = '\0';
	monHoc.tenMonHoc[0] = '\0';
	monHoc.soTCLT = -1;
	monHoc.soTCTH = -1;
	char soTCLT_ch[3];
	soTCLT_ch[0] = '\0';
	char soTCTH_ch[3];
	soTCTH_ch[0] = '\0';

MaMonHoc:
	while (true) {

		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(13 + vitri, 7);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
			monHoc.maMonHoc[vitri] = toupper((char)key);
			cout << monHoc.maMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(13 + vitri, 7);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			monHoc.maMonHoc[vitri] = '\0';
			if (monHoc.maMonHoc[0] == '\0') {
				Alert("Chua Nhap Ma Mon Hoc", 30, 9, 4, 900);
				continue;
			}
			if (CheckTrungMMH(tree, monHoc.maMonHoc) != NULL) {
				Alert("Ma Mon Hoc Trung!!!", 30, 9, 4, 900);
				continue;
			}
			vitri = strlen(monHoc.tenMonHoc);
			gotoxy(25 + vitri, 7);
			goto TenMonHoc;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
	}
TenMonHoc:
	while (true) {
		//Nhap Ten Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(25 + vitri, 7);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 38)) {
			monHoc.tenMonHoc[vitri] = toupper((char)key);
			cout << monHoc.tenMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(25 + vitri, 7);
			cout << " ";
		}
		if (key == SPACE && vitri > 0 && vitri < 38 && monHoc.tenMonHoc[vitri - 1] != ' ') {
			gotoxy(25 + vitri, 7);
			cout << " ";
			monHoc.tenMonHoc[vitri] = ' ';
			vitri++;
		}
		if ((key == ENTER || key == RIGHT) && vitri != 0) {
			if (monHoc.tenMonHoc[vitri - 1] == ' ')
				vitri--;
			monHoc.tenMonHoc[vitri] = '\0';
			vitri = strlen(soTCLT_ch);
			gotoxy(66 + vitri, 7);
			goto TCLT;
		}
		if (key == ENTER || key == RIGHT) {
			monHoc.tenMonHoc[vitri] = '\0';
			if (monHoc.tenMonHoc[0] == '\0')
				Alert("Chua Nhap Ten Mon Hoc", 30, 9, 4, 900);
		}
		if (key == LEFT) {
			monHoc.tenMonHoc[vitri] = '\0';
			if (monHoc.tenMonHoc[0] == '\0') {
				Alert("Chua Nhap Ten Mon Hoc", 30, 9, 4, 900);
				continue;
			}
			vitri = strlen(monHoc.maMonHoc);
			gotoxy(13 + vitri, 7);
			goto MaMonHoc;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
TCLT:
	while (true) {
		//Nhap Ten Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(66 + vitri, 7);
		key = GetKey();

		if ((key <= '9' && key >= '0') && (vitri < 2)) {
			soTCLT_ch[vitri] = toupper((char)key);
			cout << soTCLT_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(66 + vitri, 7);
			cout << " ";
		}
		if (key == ENTER || key == RIGHT) {
			soTCLT_ch[vitri] = '\0';
			if (soTCLT_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Ly Thuyet", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCLT = std::stoi(string(soTCLT_ch));

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCLT phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(soTCTH_ch);
			gotoxy(75 + vitri, 7);
			goto TCTH;
		}
		if (key == LEFT) {
			soTCLT_ch[vitri] = '\0';
			if (soTCLT_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Ly Thuyet", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCLT = std::stoi(string(soTCLT_ch));
			gotoxy(1, 1);
			cout << monHoc.soTCLT;

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCLT phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(monHoc.tenMonHoc);
			gotoxy(25 + vitri, 7);
			goto TenMonHoc;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
TCTH:
	while (true) {
		//Nhap Ten Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(75 + vitri, 7);
		key = GetKey();

		if ((key <= '9' && key >= '0') && (vitri < 2)) {
			soTCTH_ch[vitri] = toupper((char)key);
			cout << soTCTH_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(75 + vitri, 7);
			cout << " ";
		}
		if (key == ENTER || key == RIGHT) {
			soTCTH_ch[vitri] = '\0';
			if (soTCTH_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Thuc Hanh", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCTH = std::stoi(string(soTCTH_ch));

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCTH phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(soTCTH_ch);
			gotoxy(85 + vitri, 7);
			goto OK;
		}
		if (key == LEFT) {
			soTCTH_ch[vitri] = '\0';
			if (soTCTH_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Thuc Hanh", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCTH = std::stoi(string(soTCTH_ch));
			gotoxy(1, 1);
			cout << monHoc.soTCTH;

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCTH phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(soTCLT_ch);
			gotoxy(66 + vitri, 7);
			goto TCLT;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
OK:
	TurnOKButtonKhungMonHoc(true);
	while (true) {
		key = GetKey();
		if (key == ENTER) {
			InsertNode(tree, monHoc);
			Alert("Them Mon Hoc Thanh Cong!!!", 30, 9, 2, 900);

			//restart
			vitri = 0;
			monHoc.maMonHoc[0] = '\0';
			monHoc.tenMonHoc[0] = '\0';
			monHoc.soTCLT = -1;
			monHoc.soTCTH = -1;
			soTCLT_ch[0] = '\0';
			soTCTH_ch[0] = '\0';
			KhungThemMonHoc();
			KhungDSMonHoc();
			PhanTrangDSMonHoc(tree, trang);
			goto MaMonHoc;
		}
		if (key == LEFT) {
			TurnOKButtonKhungMonHoc(false);
			vitri = strlen(soTCTH_ch);
			gotoxy(75 + vitri, 7);
			goto TCTH;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
}

void ChinhSuaMonHoc(string choice = "them") {
	KhungThemMonHoc(choice);
	KhungDSMonHoc();
	HuongDanThemMonHoc();
	int key, vitri = 0, trang = 0;
	PhanTrangDSMonHoc(tree, trang);

	MonHoc monHoc;
	monHoc.maMonHoc[0] = '\0';
	monHoc.tenMonHoc[0] = '\0';
	monHoc.soTCLT = -1;
	monHoc.soTCTH = -1;
	char soTCLT_ch[3];
	soTCLT_ch[0] = '\0';
	char soTCTH_ch[3];
	soTCTH_ch[0] = '\0';

MaMonHoc:
	while (true) {

		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(13 + vitri, 7);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
			monHoc.maMonHoc[vitri] = toupper((char)key);
			cout << monHoc.maMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(13 + vitri, 7);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			monHoc.maMonHoc[vitri] = '\0';
			if (monHoc.maMonHoc[0] == '\0') {
				Alert("Chua Nhap Ma Mon Hoc", 30, 9, 4, 900);
				continue;
			}
			if (choice == "them") {
				if (CheckTrungMMH(tree, monHoc.maMonHoc) != NULL) {
					Alert("Ma Mon Hoc Trung!!!", 30, 9, 4, 900);
					continue;
				}
			}
			if (choice == "sua") {
				if (CheckTrungMMH(tree, monHoc.maMonHoc) == NULL) {
					Alert("Ma Mon Hoc Khong Ton Tai!!!", 30, 9, 4, 900);
					continue;
				}
			}
			vitri = strlen(monHoc.tenMonHoc);
			gotoxy(25 + vitri, 7);
			goto TenMonHoc;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
	}
TenMonHoc:
	while (true) {
		//Nhap Ten Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(25 + vitri, 7);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 38)) {
			monHoc.tenMonHoc[vitri] = toupper((char)key);
			cout << monHoc.tenMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(25 + vitri, 7);
			cout << " ";
		}
		if (key == SPACE && vitri > 0 && vitri < 38 && monHoc.tenMonHoc[vitri - 1] != ' ') {
			gotoxy(25 + vitri, 7);
			cout << " ";
			monHoc.tenMonHoc[vitri] = ' ';
			vitri++;
		}
		if ((key == ENTER || key == RIGHT) && vitri != 0) {
			if (monHoc.tenMonHoc[vitri - 1] == ' ')
				vitri--;
			monHoc.tenMonHoc[vitri] = '\0';
			vitri = strlen(soTCLT_ch);
			gotoxy(66 + vitri, 7);
			goto TCLT;
		}
		if (key == ENTER || key == RIGHT) {
			monHoc.tenMonHoc[vitri] = '\0';
			if (monHoc.tenMonHoc[0] == '\0')
				Alert("Chua Nhap Ten Mon Hoc", 30, 9, 4, 900);
		}
		if (key == LEFT) {
			monHoc.tenMonHoc[vitri] = '\0';
			if (monHoc.tenMonHoc[0] == '\0') {
				Alert("Chua Nhap Ten Mon Hoc", 30, 9, 4, 900);
				continue;
			}
			vitri = strlen(monHoc.maMonHoc);
			gotoxy(13 + vitri, 7);
			goto MaMonHoc;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
TCLT:
	while (true) {
		//Nhap Ten Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(66 + vitri, 7);
		key = GetKey();

		if ((key <= '9' && key >= '0') && (vitri < 2)) {
			soTCLT_ch[vitri] = toupper((char)key);
			cout << soTCLT_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(66 + vitri, 7);
			cout << " ";
		}
		if (key == ENTER || key == RIGHT) {
			soTCLT_ch[vitri] = '\0';
			if (soTCLT_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Ly Thuyet", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCLT = std::stoi(string(soTCLT_ch));

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCLT phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(soTCTH_ch);
			gotoxy(75 + vitri, 7);
			goto TCTH;
		}
		if (key == LEFT) {
			soTCLT_ch[vitri] = '\0';
			if (soTCLT_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Ly Thuyet", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCLT = std::stoi(string(soTCLT_ch));
			gotoxy(1, 1);
			cout << monHoc.soTCLT;

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCLT phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(monHoc.tenMonHoc);
			gotoxy(25 + vitri, 7);
			goto TenMonHoc;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
TCTH:
	while (true) {
		//Nhap Ten Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(75 + vitri, 7);
		key = GetKey();

		if ((key <= '9' && key >= '0') && (vitri < 2)) {
			soTCTH_ch[vitri] = toupper((char)key);
			cout << soTCTH_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(75 + vitri, 7);
			cout << " ";
		}
		if (key == ENTER || key == RIGHT) {
			soTCTH_ch[vitri] = '\0';
			if (soTCTH_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Thuc Hanh", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCTH = std::stoi(string(soTCTH_ch));

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCTH phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(soTCTH_ch);
			gotoxy(85 + vitri, 7);
			goto OK;
		}
		if (key == LEFT) {
			soTCTH_ch[vitri] = '\0';
			if (soTCTH_ch[0] == '\0') {
				Alert("Chua Nhap So Tin Chi Thuc Hanh", 30, 9, 4, 900);
				continue;
			}

			//Đổi char sang int và lưu vào monHoc
			monHoc.soTCTH = std::stoi(string(soTCTH_ch));
			gotoxy(1, 1);
			cout << monHoc.soTCTH;

			//2 loại tín chỉ không đc cùng = 0
			if (monHoc.soTCLT == 0 && monHoc.soTCTH == 0) {
				Alert("So TCTH phai khac 0", 30, 9, 4, 900);
				continue;
			}

			vitri = strlen(soTCLT_ch);
			gotoxy(66 + vitri, 7);
			goto TCLT;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
OK:
	TurnOKButtonKhungMonHoc(true);
	while (true) {
		key = GetKey();
		if (key == ENTER) {
			if (choice == "them") {
				InsertNode(tree, monHoc);
				Alert("Them Mon Hoc Thanh Cong!!!", 30, 9, 2, 900);
			}
			if (choice == "sua") {
				DS_MonHoc* p = CheckTrungMMH(tree, monHoc.maMonHoc);
				strcpy_s(p->monHoc.maMonHoc, monHoc.maMonHoc);
				strcpy_s(p->monHoc.tenMonHoc, monHoc.tenMonHoc);
				p->monHoc.soTCLT = monHoc.soTCLT;
				p->monHoc.soTCTH = monHoc.soTCTH;
				Alert("Sua Mon Hoc Thanh Cong!!!", 30, 9, 2, 900);
			}

			//restart
			vitri = 0;
			monHoc.maMonHoc[0] = '\0';
			monHoc.tenMonHoc[0] = '\0';
			monHoc.soTCLT = -1;
			monHoc.soTCTH = -1;
			soTCLT_ch[0] = '\0';
			soTCTH_ch[0] = '\0';
			KhungThemMonHoc(choice);
			KhungDSMonHoc();
			PhanTrangDSMonHoc(tree, trang);
			goto MaMonHoc;
		}
		if (key == LEFT) {
			TurnOKButtonKhungMonHoc(false);
			vitri = strlen(soTCTH_ch);
			gotoxy(75 + vitri, 7);
			goto TCTH;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
	return;
}

void XoaMonHoc() {
	return;
}
//DS_MonHoc* rp;
//DS_MonHoc* remove(DS_MonHoc*& p, MonHoc monHoc, int x) {
//	if (p == NULL) {
//		cout << "Khong tim thay";
//	} else if (x < p->monHoc.soTCLT) {
//		p->left = remove(p->left, monHoc, x);
//	} else if (x > p->monHoc.soTCLT) {
//		p->right = remove(p->right, monHoc, x);
//	} else {             //Tìm được key
//		rp = p;
//		if (rp->right == NULL)
//			p = rp->left;       //p có thể là lá hoặc là nút có cây con bên trái
//		else if (rp->left == NULL)
//			p = rp->right;
//		else
//			remove_case_3(rp->right);
//		delete rp;
//		return p;
//	}
//}
//
//DS_MonHoc* Delete(DS_MonHoc* root, int value) {
//	if (root == NULL)
//		return root;
//	if (value < root->monHoc.soTCLT)
//		root->left = Delete(root->left, value);
//	else if (value > root->monHoc.soTCLT)
//		root->right = Delete(root->right, value);
//	else {
//		// root->data == value, delete this node
//		if (root->left == NULL) {
//			DS_MonHoc* newRoot = root->right;
//			free(root);
//			return newRoot;
//		}
//		if (root->right == NULL) {
//			DS_MonHoc* newRoot = root->left;
//			free(root);
//			return newRoot;
//		}
//		root->data = LeftMostValue(root->right);
//		root->right = Delete(root->right, root->data);
//	}
//	return root;
//}
//---------------------------------------------KET THUC QUAN LY MON HOC----------------------------------------------------






char thucdon[4][50] = { "  QUAN LY LOP TIN CHI   ",
						"  QUAN LY SINH VIEN     ",
						"  QUAN LY MON HOC       ",
						"    XXX                 " };
char MenuMoLopTinChi[5][50] = { " TAO LOP TIN CHI MOI    ",
								" CHINH SUA LOP TIN CHI  ",
								" IN DANH SACH DANG KY   ",
								" XXXXXXXXXXXXXXXXXXXX   ",
								"XXXXXXXXXXXXXXXXXXXXXXX " };
char MenuQuanLySinhVien[5][50] = { " THEM SINH VIEN         ",
								   " CHINH SUA SINH VIEN    ",
								   " XOA SINH VIEN          ",
								   " IN DANH SACH SINH VIEN ",
								   " LUU FILE SINH VIEN     " };
char MenuQuanLyMonHoc[5][50] = { " THEM MON HOC           ",
								 " XXXXXXXXXXXXXXXXXXX    ",
								 " XXXXXXXXXXXXXXXXXXX    ",
								 " LUU DANH SACH MON HOC  " };

void ToMauMenuChinh(int textColor, int bGColor, int vitri) {
	SetColor(textColor);
	SetBGColor(bGColor);
	gotoxy(0, 12 + vitri * 4); cout << "                        ";
	gotoxy(0, 13 + vitri * 4); cout << thucdon[vitri];
	gotoxy(0, 14 + vitri * 4); cout << "                        ";
}
void ToMauMenuCon(int textColor, int bGColor, char MenuCon[][50], int vitri) {
	SetColor(textColor);
	SetBGColor(bGColor);
	gotoxy(28, 5 + (vitri + 1) * 4);	cout << "                        ";
	gotoxy(28, 6 + (vitri + 1) * 4);	cout << MenuCon[vitri];
	gotoxy(28, 7 + (vitri + 1) * 4);	cout << "                        ";
}


//-----------------CHILDREN MENU-------------------------
int MenuCon(int item, char MenuCon[][50]) {
	char key;
	int vitri = 0;
	while (true) {
		ThongTin();
		key = GetKey();
		if (key == ENTER)
			return vitri + 1;
		if (key == ESC || key == LEFT)
			return 0;
		switch (key) {
		case DOWN:
			if (vitri == (item - 1)) {
				ToMauMenuCon(4, 11, MenuCon, vitri);
				vitri = 0;
				ToMauMenuCon(4, 14, MenuCon, vitri);
			} else {
				ToMauMenuCon(4, 11, MenuCon, vitri);
				vitri++;
				ToMauMenuCon(4, 14, MenuCon, vitri);
			}
			break;
		case UP:
			if (vitri == 0) {
				ToMauMenuCon(4, 11, MenuCon, vitri);
				vitri = item - 1;
				ToMauMenuCon(4, 14, MenuCon, vitri);
			} else {
				ToMauMenuCon(4, 11, MenuCon, vitri);
				vitri--;
				ToMauMenuCon(4, 14, MenuCon, vitri);
			}
			break;
		}
	}
	return 0;
}
//------------------DAD MENU--------------------------
int DadMenu() {
	int vitri = 0;
	while (true) {
		ThongTin();
		char key = GetKey();
		if (key == ENTER || (key == RIGHT && vitri != 4)) // 4 === THOAT
			return vitri + 1;
		switch (key) {
		case DOWN:
			if (vitri == 3) {
				ToMauMenuChinh(4, 11, vitri);
				vitri = 0;
				ToMauMenuChinh(4, 14, vitri);
			} else {
				ToMauMenuChinh(4, 11, vitri);
				vitri++;
				ToMauMenuChinh(4, 14, vitri);
			}
			break;
		case UP:
			if (vitri == 0) {
				ToMauMenuChinh(4, 11, vitri);
				vitri = (4 - 1);
				ToMauMenuChinh(4, 14, vitri);
			} else {
				ToMauMenuChinh(4, 11, vitri);
				vitri--;
				ToMauMenuChinh(4, 14, vitri);
			}
			break;
		}
	}
	return 0;
}
//---------------ROOT MENU------------------------
void RootMenu(DS_LopTinChi& ds_ltc, DS_DangKy& ds_dk, DS_SinhVien& ds_sv) {
	int choice;
	int choiceMenuCon;
	while (true) {
		clrscr();
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				SetColor(4);
				SetBGColor(14);
			} else {
				SetColor(4);
				SetBGColor(11);
			}
			gotoxy(0, 12 + i * 4); cout << "                        ";
			gotoxy(0, 13 + i * 4); cout << thucdon[i];
			gotoxy(0, 14 + i * 4); cout << "                        ";
		}
		gotoxy(24, 7);
		choice = DadMenu();
		switch (choice) {
		case 1:
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					SetColor(4);
					SetBGColor(14);
				} else {
					SetColor(4);
					SetBGColor(11);
				}
				gotoxy(28, 5 + (i + 1) * 4);	cout << "                        ";
				gotoxy(28, 6 + (i + 1) * 4);	cout << MenuMoLopTinChi[i];
				gotoxy(28, 7 + (i + 1) * 4);	cout << "                        ";
			}
			choiceMenuCon = MenuCon(4, MenuMoLopTinChi);     // item la so chuc nang cua lop con
			SetBGColor(7);
			clrscr();
			switch (choiceMenuCon) {
			case 1:
				ThemLopTinChi(ds_ltc);
				break;
			case 2:
				ChinhSuaLopTinChi(ds_ltc);
				break;
			case 3:
				InDSDK(ds_ltc, ds_dk);
				break;
			}
			break;
		case 2:
			for (int i = 0; i < 5; i++) {
				if (i == 0) {
					SetColor(4);
					SetBGColor(14);
				} else {
					SetColor(4);
					SetBGColor(11);
				}
				gotoxy(28, 5 + (i + 1) * 4);	cout << "                        ";
				gotoxy(28, 6 + (i + 1) * 4);	cout << MenuQuanLySinhVien[i];
				gotoxy(28, 7 + (i + 1) * 4);	cout << "                        ";
			}
			choiceMenuCon = MenuCon(5, MenuQuanLySinhVien);     // item la so chuc nang cua lop con
			SetBGColor(7);
			clrscr();
			switch (choiceMenuCon) {
			case 1:
				ThemSinhVien(ds_sv);
				break;
			case 2:
				ThemSinhVien(ds_sv, "sua");
				break;
			case 3:
				XoaSinhVien(ds_ltc, ds_sv);
				break;
			case 4:
				InDSSV();
				break;
			case 5:
				LuuFileLop();
				break;
			}
			break;
		case 3:
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					SetColor(4);
					SetBGColor(14);
				} else {
					SetColor(4);
					SetBGColor(11);
				}
				gotoxy(28, 5 + (i + 1) * 4);	cout << "                        ";
				gotoxy(28, 6 + (i + 1) * 4);	cout << MenuQuanLyMonHoc[i];
				gotoxy(28, 7 + (i + 1) * 4);	cout << "                        ";
			}
			choiceMenuCon = MenuCon(4, MenuQuanLyMonHoc);     // item la so chuc nang cua lop con
			SetBGColor(7);
			clrscr();
			switch (choiceMenuCon) {
			case 1:
				ChinhSuaMonHoc("them");
				break;
			case 2:
				ChinhSuaMonHoc("sua");
				break;
			case 3:
				break;
			case 4:
				LuuDSMH();
				break;
			}
			break;
		}
	}
	return;
}

void DocFileLopTinChi(DS_LopTinChi& ds_ltc) {
	system("cls");
	fstream f;
	string data;
	f.open("DSLOPTINCHI.txt", ios::in);
	/*if (f == NULL) {
		cout << "Doc File That Bai!!!" << endl;
	} else
		cout << "Doc File Thanh Cong!!!" << endl;*/
	while (!f.eof()) {
		getline(f, data);

		if (data.size() == 0)
			break;
		if (std::stoi(data) < 0)
			break;
		ds_ltc.soLuong++;
		ds_ltc.ds[ds_ltc.soLuong - 1] = new LopTinChi;
		ds_ltc.ds[ds_ltc.soLuong - 1]->maLopTinChi = std::stoi(data);  // std::stoi string->int

		for (int i = 0; i < 5000; i++) {
			if (randArr[i] == ds_ltc.ds[ds_ltc.soLuong - 1]->maLopTinChi) {
				randArr[i] == 0;
				break;
			}
		}

		getline(f, data);
		strcpy_s(ds_ltc.ds[ds_ltc.soLuong - 1]->maMonHoc, data.c_str());
		getline(f, data);
		ds_ltc.ds[ds_ltc.soLuong - 1]->nienKhoa = std::stoi(data);
		getline(f, data);
		ds_ltc.ds[ds_ltc.soLuong - 1]->hocKy = std::stoi(data);
		getline(f, data);
		ds_ltc.ds[ds_ltc.soLuong - 1]->nhom = std::stoi(data);
		getline(f, data);
		ds_ltc.ds[ds_ltc.soLuong - 1]->svMin = std::stoi(data);
		getline(f, data);
		ds_ltc.ds[ds_ltc.soLuong - 1]->svMax = std::stoi(data);

		//Gan head = NULL
		ds_ltc.ds[ds_ltc.soLuong - 1]->head = NULL;
	}
	return;
}
int main() {

	resizeConsole(1400, 800);
	RandomMLTC();
	SetBGColor(7);

	DS_LopTinChi ds_ltc;
	InitializeLopTinChi(ds_ltc);
	DocFileLopTinChi(ds_ltc);

	DS_DangKy ds_dk;
	DocDSDK(ds_ltc, ds_dk);

	DS_SinhVien ds_sv;
	InitializeDSSV(first);
	DocFileLop();

	DS_MonHoc ds_mh;
	InitializeTree(tree);
	DocDSMH();


	RootMenu(ds_ltc, ds_dk, ds_sv);
	return 0;
}















































































