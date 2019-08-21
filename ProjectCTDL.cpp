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
#include <algorithm>
#include <iomanip>

#include "Mylib.h"
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
void PhanTrangDSMonHoc(DS_MonHoc*, int&, string);
DS_MonHoc* CheckTrungMMH(DS_MonHoc* root, char maMonHoc[]);
//----------------------------------------------------NHAP,XUAT,HIEU CHINH LOP TIN CHI----------------------------------------------------

// Return 1->FULL, Return 0->!FULL
int IsFull(DS_LopTinChi& ds_ltc) {
	return (ds_ltc.soLuong == DSDKMAX) ? 1 : 0;
}

//Lưu File lớp tín chỉ
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
			<< ds_ltc.ds[n]->svMax << endl;  //Bỏ endl fix bug lúc đọc file (endl ở maloptinchi)
		n++;
	}
	f.close();
	return;
}

//Đọc File lớp tín chỉ
void DocFileLopTinChi(DS_LopTinChi& ds_ltc) {
	fstream f;
	string data;
	f.open("DSLOPTINCHI.txt", ios::in);
	while (!f.eof()) {
		getline(f, data);
		if (data.size() == 0)
			break;
		if (std::stoi(data) < 0)
			break;
		ds_ltc.soLuong++;
		ds_ltc.ds[ds_ltc.soLuong - 1] = new LopTinChi;
		ds_ltc.ds[ds_ltc.soLuong - 1]->maLopTinChi = std::stoi(data);  // std::stoi string->int

		for (int i = 0; i < randRage; i++) {
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

//Khởi tạo lớp tín chỉ
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
			Alert("Lop Tin Chi Trung!!! Tu Dong Thoat!!!", 34, 10, 4, 2000);
			return 1;
		}
	}
	return 0;
}

void ThemLopTinChi(DS_LopTinChi& ds_ltc) {
	KhungNhapLopTinChi();
	int trang = 0;
	PhanTrangDSMonHoc(tree, trang, "SORT");

	int key, vitri = 0, x = 10;
	LopTinChi lopTinChi;
	lopTinChi.maMonHoc[0] = '\0';
	lopTinChi.nienKhoa = 0;
	lopTinChi.hocKy = 0;
	lopTinChi.nhom = 0;
	lopTinChi.svMin = 0;
	lopTinChi.svMax = 0;
	lopTinChi.head = NULL;

	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';

	//Nhận 1 mã lớp tín chỉ không trùng tự sinh 
	for (int i = 0; i < randRage; i++) {
		if (randArr[i] != 0) {
			lopTinChi.maLopTinChi = randArr[i];
			randArr[i] = 0;
			break;
		}
	}

	//Kiểm tra danh sách lớp tín chỉ đầy trước khi in mã lớp tín ch
	if (IsFull(ds_ltc)) {
		Alert("Danh Sach Dang Ky Lop Tin Chi Da Day!!!", 34, 10, 4, 900);
		return;
	}

	//In mã lớp tín chỉ
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "  MA MON HOC: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 9 KI TU  ";
	gotoxy(18, 34);
	cout << "                                                           ";
	while (true) {
		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(25 + vitri, 8);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
			if (IsFull(ds_ltc)) {
				Alert("Danh Sach Dang Ky Lop Tin Chi Da Day!!!", 34, 10, 4, 900);
				return;
			}
			lopTinChi.maMonHoc[vitri] = toupper((char)key);
			cout << lopTinChi.maMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(25 + vitri, 8);
			cout << " ";
		}
		if (key == ESC) {
			system("cls");
			return;
		}
		if (key == RIGHT || key == ENTER) {
			/*if (IsFull(ds_ltc)) {
				Alert("Danh Sach Dang Ky Lop Tin Chi Da Day!!!", 34, 10, 4, 900);
				continue;
			}*/
			lopTinChi.maMonHoc[vitri] = '\0';
			if (lopTinChi.maMonHoc[0] == '\0') {
				Alert("Chua Nhap Ma Mon Hoc!!!", 34, 10, 4, 900);
				gotoxy(25, 8);
				goto MAMONHOC;
			}
			if (CheckTrungMMH(tree, lopTinChi.maMonHoc) == NULL) {
				Alert("Ma Mon Hoc Khong Ton Tai!!!", 34, 10, 4, 900);
				gotoxy(25, 8);
				goto MAMONHOC;
			}
			vitri = strlen(nienKhoa_ch);
			gotoxy(44 + vitri, 8);
			goto NIENKHOA;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3SORT");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2SORT");
		}
	}
NIENKHOA:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI THIEU: 4 KI TU     ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(44 + vitri, 8);
		key = GetKey();

		if (key >= '0' && key <= '9' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Nien Khoa Chua Nhap", 34, 10, 4, 900);
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
				Alert("Nien Khoa Chua Nhap", 34, 10, 4, 900);
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "        HOC KY: GOM CAC SO (0-9), TOI DA: 2 KI TU          ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(56 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Hoc Ky Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Hoc Ky Chua Nhap", 34, 10, 4, 900);
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
				Alert("Hoc Ky Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> lopTinChi.hocKy;
			//

			vitri = (lopTinChi.nhom > 9) ? 2 : (lopTinChi.nhom == 0) ? 0 : 1;
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "       NHOM: GOM CAC SO (0-9), TOI DA: 2 KI TU             ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(65 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Nhom Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Nhom Chua Nhap", 34, 10, 4, 900);
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
				Alert("Nhom Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> lopTinChi.nhom;
			//

			vitri = (lopTinChi.svMin >= 100) ? 3 : (lopTinChi.svMin >= 10) ? 2 : (lopTinChi.svMin == 0) ? 0 : 1;
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "      SINH VIEN MIN: GOM CAC SO (0-9), TOI DA: 3 KI TU     ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(73 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 3) {
			if (key == '0' && vitri == 0) {
				Alert("So SVMIN Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Sinh Vien Min Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char to int (Sinh Vien Min)
			string svMin_str(svMin_ch);
			stringstream geek(svMin_str);
			geek >> lopTinChi.svMin;
			//

			//Check SVMAX vs SVMIN
			if (lopTinChi.svMax < lopTinChi.svMin) {
				Alert("Sinh Vien Min Phai Nho Hon Sinh Vien Max", 34, 10, 4, 900);
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
				Alert("Sinh Vien Min Chua Nhap", 34, 10, 4, 900);
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
					Alert("Sinh Vien Min Phai Nho Hon Sinh Vien Max", 34, 10, 4, 900);
					continue;
				};
			//

			vitri = (lopTinChi.svMax >= 100) ? 3 : (lopTinChi.svMax >= 10) ? 2 : (lopTinChi.svMax == 0) ? 0 : 1;
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "      SINH VIEN MAX: GOM CAC SO (0-9), TOI DA: 3 KI TU     ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(81 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 3) {
			if (key == '0' && vitri == 0) {
				Alert("So SVMAX Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Sinh Vien Max Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char to int (Sinh Vien Max)
			string svMax_str(svMax_ch);
			stringstream geek(svMax_str);
			geek >> lopTinChi.svMax;

			//Check SVMAX vs SVMIN
			if (lopTinChi.svMax < lopTinChi.svMin) {
				Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 34, 10, 4, 900);
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
				Alert("Sinh Vien Max Chua Nhap", 34, 10, 4, 900);
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
				Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 34, 10, 4, 900);
				continue;
			};

			//Luu Lop Tin Chi Vao Mang Con Tro
			gotoxy(1, 1);
			ds_ltc.soLuong++;
			ds_ltc.ds[ds_ltc.soLuong - 1] = new LopTinChi;
			*(ds_ltc.ds[ds_ltc.soLuong - 1]) = lopTinChi;

			Alert("LUU LOP THANH CONG!!!", 34, 10, 2, 300);
			Sleep(100);
			Alert("LUU LOP THANH CONG!!!", 34, 10, 2, 300);
			Sleep(100);
			Alert("LUU LOP THANH CONG!!!", 34, 10, 2, 300);
			break;
		}

		if (key == ESC) {
			clrscr();
			return;
		}
	}
	return;
}

//Sử dụng trong chỉnh sửa lớp tín chỉ
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

				if (CheckTrungMMH(tree, maMonHoc_ch) == NULL) {
					Alert("Ma Mon Hoc Khong Ton Tai!!!", 105, 25, 4, 900);
					gotoxy(92 + vitri, y);
					goto MAMONHOC;
				}

				strcpy_s(lopTinChi.maMonHoc, maMonHoc_ch);
				vitri = strlen(nienKhoa_ch);
				gotoxy(114 + vitri, y);
				goto NIENKHOA;
			}
			if (key == ESC) {
				goto END;
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
				goto END;
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
				goto END;
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
				goto END;
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
				goto END;
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

				//Check SVMAX vs SVMIN
				if (lopTinChi.svMax < lopTinChi.svMin) {
					Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 105, 25, 4, 900);
					continue;
				};

				//Check MaMonHoc + NienKhoa + HocKy + Nhom
				for (int i = 0; i < ds_ltc.soLuong; i++) {
					bool flag = strcmp(ds_ltc.ds[i]->maMonHoc, lopTinChi.maMonHoc) == 0
						&& ds_ltc.ds[i]->nienKhoa == lopTinChi.nienKhoa
						&& ds_ltc.ds[i]->hocKy == lopTinChi.hocKy
						&& ds_ltc.ds[i]->nhom == lopTinChi.nhom;
					if (flag) {
						Alert("Lop Tin Chi Trung!!! Tu Dong Thoat!!!", 105, 25, 4, 900);
						goto END;
					}
				}

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
				goto END;
			}
		}
	}
END:
	return;
}

void ChinhSuaLopTinChiCoSinhVien(int position, DS_LopTinChi& ds_ltc) {
	char svMin_ch[4];
	char svMax_ch[4];
	svMin_ch[0] = '\0';
	svMax_ch[0] = '\0';
	int svMin_int = 0;
	int svMax_int = 0;
	int key;
	int vitri = 0;
	KhungConSuaLopTinChi();
	SetColor(4);
	gotoxy(92, 15);
	cout << ds_ltc.ds[position]->maMonHoc;
	gotoxy(105, 15);
	cout << ds_ltc.ds[position]->nienKhoa;
	gotoxy(116, 15);
	cout << ds_ltc.ds[position]->hocKy;
	gotoxy(122, 15);
	cout << ds_ltc.ds[position]->nhom;
	while (true) {
	SVMIN:
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
			gotoxy(128 + vitri, 15);
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
				gotoxy(128 + vitri, 15);
				cout << " ";
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
				geek >> svMin_int;
				//

				//Check SVMAX vs SVMIN
				if (svMax_int != 0)
					if (svMax_int < svMin_int) {
						Alert("Sinh Vien Min Phai Nho Hon Sinh Vien Max", 105, 25, 4, 900);
						continue;
					};
				//
				if (ds_ltc.ds[position]->svMin < svMin_int) {
					Alert("SV Min Moi Phai Nho Hon Hoac Bang SV Min Cu", 105, 25, 4, 900);
					continue;
				}

				vitri = (svMax_int >= 100) ? 3 : (svMax_int >= 10) ? 2 : (svMax_int == 0) ? 0 : 1;
				gotoxy(135 + vitri, 15);
				goto SVMAX;
			}
			if (key == ESC) {
				goto END;
			}
		}

	SVMAX:

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
			gotoxy(135 + vitri, 15);
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
				gotoxy(135 + vitri, 15);
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
				geek >> svMax_int;

				//Check SVMAX vs SVMIN
				if (svMax_int < svMin_int) {
					Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 105, 25, 4, 900);
					continue;
				};
				//

				vitri = (svMin_int >= 100) ? 3 : (svMin_int >= 10) ? 2 : (svMin_int == 0) ? 0 : 1;
				gotoxy(128 + vitri, 15);
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
				geek >> svMax_int;
				//

				//Check SVMAX vs SVMIN
				if (svMax_int < svMin_int) {
					Alert("Sinh Vien Max Phai Lon Hon Sinh Vien Min", 105, 25, 4, 900);
					continue;
				};
				if (ds_ltc.ds[position]->svMax > svMax_int) {
					Alert("SV Max Moi Phai Lon Hon SV Max Cu", 105, 25, 4, 900);
					continue;
				}

				ds_ltc.ds[position]->svMin = svMin_int;
				ds_ltc.ds[position]->svMax = svMax_int;
				Alert("Da Cap Nhat!!!", 105, 25, 2, 900);
				return;
			}

			if (key == ESC) {
				goto END;
			}
		}
	}
END:
	return;
}

void ChinhSuaLopTinChi(DS_LopTinChi& ds_ltc) {
	bool viewMode = true,
		editMode = false,
		deleteMode = false;
	int i = 0, move = 0;
	int key, trang = 0, tongTrang = 0;

	clrscr();
RESTART:
	tongTrang = ((ds_ltc.soLuong - 1) / 15 + 1); //Day thi qua trang khac
	if (ds_ltc.soLuong <= 15) { // 15 slot trong 1 bang
		tongTrang = 1;
		trang = 0;
	}
	if (ds_ltc.soLuong == 0) {
		clrscr();
		Alert("CHUA CO DANH SACH LOP!!!", 34, 5, 4, 900);
		return;
	}
	KhungChinhLopTinChi();
	move = 0;
	for (int i = trang * 15; i < 15 + trang * 15 && i < ds_ltc.soLuong; i++) {
		SetColor(4);
		SetBGColor(7);
		gotoxy(6, 8 + i - trang * 15);
		cout << (i + 1);
		SetColor(3);
		gotoxy(12, 8 + i - trang * 15);
		cout << ds_ltc.ds[i]->maLopTinChi;
		gotoxy(26, 8 + i - trang * 15);
		cout << ds_ltc.ds[i]->maMonHoc;
		gotoxy(42, 8 + i - trang * 15);
		cout << ds_ltc.ds[i]->nienKhoa;
		gotoxy(55, 8 + i - trang * 15);
		cout << ds_ltc.ds[i]->hocKy;
		gotoxy(64, 8 + i - trang * 15);
		cout << ds_ltc.ds[i]->nhom;
		gotoxy(71, 8 + i - trang * 15);
		cout << ds_ltc.ds[i]->svMin;
		gotoxy(80, 8 + i - trang * 15);
		cout << ds_ltc.ds[i]->svMax;
	}
	i = trang * 15 + move;
	if (ds_ltc.ds[i] != NULL) {
		SetBGColor(15);
		gotoxy(4, 8 + move);
		cout << "                                                                                   ";
		SetColor(4);
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
	}

	while (true) {
		if (ds_ltc.soLuong <= 15) { // 15 slot trong 1 bang
			tongTrang = 1;
			trang = 0;
		}
		SetMode(viewMode, editMode, deleteMode);
		key = GetKey();

		if (key == F3) {
			viewMode = false;
			editMode = false;
			deleteMode = true;
			SetMode(viewMode, editMode, deleteMode);

			int vitri = 0;
			int maLopTinChi_int = 0;
			char maLopTinChi_ch[5];
			KhungXoaLopTinChi();
			if (15 * trang + move < ds_ltc.soLuong && ds_ltc.ds[15 * trang + move] != NULL) {
				maLopTinChi_int = ds_ltc.ds[15 * trang + move]->maLopTinChi;
				strcpy_s(maLopTinChi_ch, std::to_string(ds_ltc.ds[15 * trang + move]->maLopTinChi).c_str());
				vitri = strlen(maLopTinChi_ch);
				gotoxy(117, 8);
				cout << maLopTinChi_ch;
			}
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

					if (ds_ltc.ds[index]->head != NULL) {
						Alert("Khong Duoc Xoa Lop Co Sinh Vien", 110, 14, 4, 900);
						ClearKhungXoaTinChi();
						key = 0;
						break;
					}

					bool choice = false;
					while (true) {
						ButtonXacNhanXoa(choice);
						key = GetKey();
						if (key == RIGHT)
							choice = !choice;
						if (key == LEFT)
							choice = !choice;
						if (key == ENTER)
							break;
					}
					if (choice) {
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
					}
					ClearKhungXoaTinChi();
					trang = 0;
					viewMode = true;
					editMode = false;
					deleteMode = false;
					SetMode(viewMode, editMode, deleteMode);
					goto RESTART;
				}
				if (key == ESC) {
					ClearKhungXoaTinChi();
					key = 0; //Tránh key == esc để nó thoát luôn bên ngoài
					break;
				}
			}

			viewMode = true;
			editMode = false;
			deleteMode = false;
			SetMode(viewMode, editMode, deleteMode);
		}
		if (key == F2) {
			viewMode = false;
			editMode = true;
			deleteMode = false;
			SetMode(viewMode, editMode, deleteMode);

			int vitri = 0;
			int maLopTinChi_int = 0;
			char maLopTinChi_ch[5];
			KhungSuaLopTinChi();
			if ((15 * trang + move) < ds_ltc.soLuong && ds_ltc.ds[15 * trang + move] != NULL) {
				maLopTinChi_int = ds_ltc.ds[15 * trang + move]->maLopTinChi;
				strcpy_s(maLopTinChi_ch, std::to_string(ds_ltc.ds[15 * trang + move]->maLopTinChi).c_str());
				vitri = strlen(maLopTinChi_ch);
				gotoxy(117, 8);
				cout << maLopTinChi_ch;
			}
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
					ClearKhungXoaTinChi();
					key = 0;
					break;
				}
				if (key == ENTER) {
					maLopTinChi_ch[vitri] = '\0';
					if (maLopTinChi_ch[0] == '\0') {
						Alert("Chua Nhap Ma Lop!!!", 105, 25, 4, 900);
						continue;
					}
					//Check ma lop tin chi
					string temp(maLopTinChi_ch);
					stringstream s(temp);
					s >> maLopTinChi_int;
					for (int i = 0; i < ds_ltc.soLuong; i++) {
						if (maLopTinChi_int == ds_ltc.ds[i]->maLopTinChi) {
							if (ds_ltc.ds[i]->head != NULL) {
								Alert("Chinh Sua Lop Co SV!!!", 105, 25, 4, 900);
								ChinhSuaLopTinChiCoSinhVien(i, ds_ltc);
							} else
								CheckRangBuoc(i, ds_ltc);
							key = 0;
							ClearKhungXoaTinChi();
							trang = 0;
							viewMode = true;
							editMode = false;
							deleteMode = false;
							SetMode(viewMode, editMode, deleteMode);
							goto RESTART;
						}
					}
				}
			}
			viewMode = true;
			editMode = false;
			deleteMode = false;
			SetMode(viewMode, editMode, deleteMode);
		}
		if ((key == RIGHT) && (trang < tongTrang - 1)) {
			trang++;
			goto RESTART;
		}
		if (key == LEFT && trang > 0) {
			trang--;
			goto RESTART;
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
			}
			SetBGColor(15);
			gotoxy(4, 8 + move);
			cout << "                                                                                   ";
			SetColor(4);
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
		}
		if (key == UP) {
			move--;
			if (move < 1) {
				move = 0;
			}
			i = 15 * trang + move;

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
				}
			}
			SetBGColor(15);
			gotoxy(4, 8 + move);
			cout << "                                                                                   ";

			SetColor(4);
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
		}
		if (key == ESC)
			break;
		if (key == F1) {
			LuuFileLopTinChi(ds_ltc);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 30, 2, 300);
			Sleep(100);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 30, 2, 300);
			Sleep(100);
			Alert("LUU FILE LOP THANH CONG!!!", 34, 30, 2, 300);
		}
	}
	return;
}

//----------------------------------------------------KET THUC NHAP,XUAT,HIEU CHINH LOP TIN CHI------------------------------------------

//------------------------------------------IN DANH SACH DANG KY LOP TIN CHI-----------------------------------------------
void LuuDSDK(DS_LopTinChi& ds_ltc) {
	std::ofstream fileOutput("E:/DevC/AAAAA/ProjectCTDL/DSDK.txt");
	string data;
	if (fileOutput.fail())
		cout << "Failed to open this file!" << endl;

	for (int i = 0; i < ds_ltc.soLuong; i++) {
		DS_DangKy* currentDangKy = ds_ltc.ds[i]->head;
		fileOutput << ds_ltc.ds[i]->maLopTinChi << endl;
		if (currentDangKy == NULL) {
			fileOutput << "end" << endl;
			continue;
		}
		while (currentDangKy != NULL) {
			fileOutput << currentDangKy->dangKy.maSV << endl
				<< currentDangKy->dangKy.diem << endl;
			currentDangKy = currentDangKy->next;
		}
		fileOutput << "end" << endl;
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
		getline(fileInput, data);
		if (data.size() == 0)
			return;

		int maLopTinChi = std::stoi(data);
		getline(fileInput, data);
		if (data == "end")
			continue;
		DS_DangKy* currentDangKy = new DS_DangKy;
		ds_ltc.ds[i]->head = currentDangKy;
		strcpy_s(currentDangKy->dangKy.maSV, data.c_str());
		getline(fileInput, data);
		currentDangKy->dangKy.diem = atof(data.c_str());
		while (true) {
			DS_DangKy* newDangKy = new DS_DangKy;

			getline(fileInput, data);
			if (data == "end") {
				currentDangKy->next = NULL;
				break;
			}

			strcpy_s(newDangKy->dangKy.maSV, data.c_str());
			getline(fileInput, data);
			newDangKy->dangKy.diem = atof(data.c_str());

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
	int soLuong = 0;

	//Dem so luong dsdk
	DS_DangKy* p = ds_ltc.ds[vitri]->head;
	while (p != NULL) {
		soLuong++;
		p = p->next;
	}

	DeleteKhungInDSDK();
	if (ds_ltc.ds[vitri]->head == NULL) {
		Alert("CHUA CO SINH VIEN DANG KY!!!", 34, 5, 4, 900, 15);
		return;
	}
	tongTrang = ((soLuong - 1) / 15 + 1); //Day thi qua trang khac
	if (soLuong < 15) { // 15 slot trong 1 bang
		tongTrang = 1;
		trang = 0;
	}

	while (true) {
		KhungInDSDKCon();
		p = ds_ltc.ds[vitri]->head;
		for (int i = 0; i < (trang - 1) * 15 + 15; i++) {
			p = p->next;
		}
		SinhVien sv;
		y = 14;
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

			gotoxy(80, 30);
			cout << trang + 1 << "/" << tongTrang;

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
	ButtonKhungInDSDK();
	int key, vitri = 0, x = 10, trang = 0;
	PhanTrangDSMonHoc(tree, trang, "SORT");
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << " MA MON HOC: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 9 KI TU   ";
	gotoxy(18, 34);
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
				//Alert("Chua Nhap Ma Mon Hoc!!!", 34, 10, 4, 900);
				Alert("Ma Mon Hoc Chua Nhap", 34, 10, 4, 900);
				gotoxy(25, 8);
				goto MAMONHOC;
			}
			if (CheckFieldTonTai(lopTinChi, ds_ltc, "mmh") == -1) {
				Alert("Ma Mon Hoc Khong Ton Tai", 34, 10, 4, 900);
				continue;
			}
			vitri = strlen(nienKhoa_ch);
			gotoxy(44 + vitri, 8);
			goto NIENKHOA;
		}
		if (key == F3) {
			PhanTrangDSMonHoc(tree, trang, "F3SORT");
		}
		if (key == F2) {
			PhanTrangDSMonHoc(tree, trang, "F2SORT");
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI THIEU: 4 KI TU     ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(44 + vitri, 8);
		key = GetKey();

		if (key >= '0' && key <= '9' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Nien Khoa Chua Nhap", 34, 10, 4, 900);
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
				Alert("Nien Khoa Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> lopTinChi.nienKhoa;
			//

			if (CheckFieldTonTai(lopTinChi, ds_ltc, "nk") == -1) {
				Alert("Nien Khoa Khong Ton Tai", 34, 10, 4, 900);
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "        HOC KY: GOM CAC SO (0-9), TOI DA: 2 KI TU          ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(56 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Hoc Ky Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Hoc Ky Chua Nhap", 34, 10, 4, 900);
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
				Alert("Hoc Ky Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> lopTinChi.hocKy;
			//

			if (CheckFieldTonTai(lopTinChi, ds_ltc, "hk") == -1) {
				Alert("Hoc Ky Khong Ton Tai", 34, 10, 4, 900);
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
	gotoxy(18, 32);
	cout << "                                                           ";
	gotoxy(18, 33);
	cout << "       NHOM: GOM CAC SO (0-9), TOI DA: 2 KI TU             ";
	gotoxy(18, 34);
	cout << "                                                           ";

	while (true) {

		SetColor(3);
		SetBGColor(7);
		gotoxy(65 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Nhom Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Nhom Chua Nhap", 34, 10, 4, 900);
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
				Alert("Nhom Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> lopTinChi.nhom;
			//

			int i = CheckFieldTonTai(lopTinChi, ds_ltc, "l");
			if (i == -1) {
				Alert("Lop Tin Chi Khong Ton Tai", 34, 10, 4, 900);
				continue;
			} else {
				InDSDKCon(ds_ltc, i);
				DeleteKhungInDSDK();
				ButtonKhungInDSDK();
				PhanTrangDSMonHoc(tree, trang, "SORT");
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

//Return số sinh viên của 1 lớp, 0-> không có sv
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

void PhanTrangLopSinhVien(char maLop[], int& trang, DS_SinhVien* start, string choice = "") {
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

	//while (true) { //Trỏ tới lớp cần tìm, con trỏ nằm ở sinh viên đầu tiên
	//	if (strcmp(p->sinhVien.maLop, maLop) == 0)
	//		break;
	//	p = p->next;
	//}
	p = start;
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

//Chắc chắn lớp có tồn tại
int AddIfNoneExist(SinhVien sv, DS_SinhVien*& start, DS_SinhVien*& bstart) {
	DS_SinhVien* p, * t = NULL, * s = NULL;
	p = new DS_SinhVien;
	p->sinhVien = sv;
	p->next = NULL;

	if (start == first) {
		p->next = first;
		first = p;
		bstart = first;
		start = first;
	} else {
		p->next = start;
		bstart->next = p;
		start = p;
	}
	return 1;
}

//Them sinh vien co thu tu theo malop + mssv
void Insert_Order(SinhVien sv, DS_SinhVien*& start, DS_SinhVien*& bstart) {
	DS_SinhVien* p, * t = NULL, * s = NULL;
	p = new DS_SinhVien;
	p->sinhVien = sv;
	p->next = NULL;

	if (start == NULL || strcmp(start->sinhVien.maLop, sv.maLop) != 0)
		if (AddIfNoneExist(sv, start, bstart)) {
			delete p;
			return;
		}
	for (s = start, t = bstart;
		s != NULL && strcmp(s->sinhVien.maSV, sv.maSV) < 0 && strcmp(s->sinhVien.maLop, sv.maLop) == 0;
		t = s, s = s->next);

	if (t == s) {
		p->next = s;
		first = p;
		start = first;
		bstart = first;
	} else {
		if (t == bstart && s == start) {
			p->next = start;
			bstart->next = p;
			start = p;
		} else {
			p->next = s;
			t->next = p;
		}
	}
	return;
}

//Choice == "0" && return 1->mssv trùng ở lớp khác, Choice == "1" && return 1->mssv trùng trong lớp 
int CheckTrungMSSV(char mssv[], char maLop[], DS_SinhVien* start, string choice = "0") {
	DS_SinhVien* p = first;
	/*while (p != NULL) {
		if (choice == "0") {
			if (strcmp(mssv, p->sinhVien.maSV) == 0)
				return 1;
		}
		if (choice == "1") {
			if (strcmp(maLop, p->sinhVien.maLop) == 0 && strcmp(mssv, p->sinhVien.maSV) == 0)
				return 1;
		}
		p = p->next;
	}*/
	if (choice == "0") {
		while (p != NULL) {
			if (strcmp(mssv, p->sinhVien.maSV) == 0)
				return 1;
			p = p->next;
		}
	}
	if (choice == "1") {
		while (start != NULL && strcmp(start->sinhVien.maLop, maLop) == 0) {
			if (strcmp(start->sinhVien.maSV, mssv) == 0)
				return 1;
			start = start->next;
		}
	}
	return 0;
}

void ThemSinhVienTheoLop(SinhVien& sv, DS_SinhVien*& start, DS_SinhVien*& bstart) {
	int trang = 0;
	int count = 0, vitri = 0, key;
	/*DS_SinhVien* p, * t = NULL, * s = NULL;
	p = new DS_SinhVien;
	p->sinhVien = sv;
	p->next = NULL;*/

	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';
	bool sex = true; //TRUE = nam; FALSE = nu

	PhanTrangLopSinhVien(sv.maLop, trang, start);
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
			if (CheckTrungMSSV(sv.maSV, sv.maLop, start, "0") == 1) {
				Alert("Ma Sinh Vien Trung!!!", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoxy(44 + vitri, 8);
			goto HO;
		}
		if (key == F3)
			PhanTrangLopSinhVien(sv.maLop, trang, start, "F3");
		if (key == F2)
			PhanTrangLopSinhVien(sv.maLop, trang, start, "F2");
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
			Insert_Order(sv, start, bstart);
			PhanTrangLopSinhVien(sv.maLop, trang, start);
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

void SuaSinhVienTheoLop(SinhVien& sv, DS_SinhVien* startClass) {
	int trang = 0;
	int count = 0, vitri = 0, key;

	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';
	bool sex = true; //TRUE = nam; FALSE = nu

	PhanTrangLopSinhVien(sv.maLop, trang, startClass);
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
			if (CheckTrungMSSV(sv.maSV, sv.maLop, startClass, "1") != 1) {
				Alert("Ma Sinh Vien Khong Co Trong Lop!!!", 34, 15, 4, 900);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoxy(44 + vitri, 8);
			goto HO;
		}
		if (key == F3)
			PhanTrangLopSinhVien(sv.maLop, trang, startClass, "F3");
		if (key == F2)
			PhanTrangLopSinhVien(sv.maLop, trang, startClass, "F2");
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
			DS_SinhVien* p = startClass;
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
			PhanTrangLopSinhVien(sv.maLop, trang, startClass);
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
				DS_SinhVien* p = first;
				DS_SinhVien* start = first, * bstart = first;
				while (p != NULL) {
					if (strcmp(p->sinhVien.maLop, sv.maLop) == 0) {
						break;
					}
					p = p->next;
				}
				for (start = first; start != NULL && strcmp(start->sinhVien.maLop, sv.maLop) < 0; bstart = start, start = start->next);
				if (choice == "them")
					ThemSinhVienTheoLop(sv, start, bstart);
				if (choice == "sua") {
					//Sử dụng luôn start trên kia cũng đc
					if (p != NULL)
						SuaSinhVienTheoLop(sv, p);
					else
						Alert("Lop Khong Ton Tai!!!", 34, 26, 4, 900);
				}
				break;
			}
		}
	}
	return;
}

//Kiểm tra lớp có tồn tại hay không, sẵn track start là sv đầu tiên lớp, bstart sau start.
int KiemTraLopCanXoa(DS_SinhVien*& bstart, DS_SinhVien*& start, SinhVien sv) {
	while (start != NULL) {
		if (strcmp(start->sinhVien.maLop, sv.maLop) == 0) {
			return 1;
		}
		bstart = start;
		start = start->next;
	}
	//Cho tới null vẫn không kiếm được lớp, reset giá trị bstart,start về == first
	bstart = first;
	start = first;
	return 0;
}

//Delete đc sv(trong lớp đc gửi kèm)-> 1, không tìm thấy-> không delete-> 0
int KiemTraSVCanXoa(DS_SinhVien*& bstart, DS_SinhVien*& start, SinhVien sv) {
	DS_SinhVien* t = bstart;
	DS_SinhVien* s = start;
	//Start track ở đầu lớp, để so sánh mã lớp tránh delete qua lớp khác, không có thì nó tiếp tục kiếm và delete sinh viên ở lớp khác(nếu ng sd gõ mã sv ở lớp khác).
	while (s != NULL && strcmp(s->sinhVien.maLop, sv.maLop) == 0) {
		if (strcmp(s->sinhVien.maSV, sv.maSV) == 0) {
			if (s == first) {
				first = s->next;

				//Gán lại bstart,start cho đúng
				bstart = first;
				start = first;
				//Vì vẫn sử dụng bstart và start cho lần delete tiếp theo

				delete s;
				return 1;
			} else {
				//Nếu delete ở khoảng đầu lớp thì thực hiện gán lại giá trị cho bstart,start vì 2 cái này sẽ đc sd lại
				if (t == bstart && s == start) {
					bstart->next = start->next;
					delete start;
					start = bstart->next;
					return 1;
				} else {
					//Nếu không delete khoảng đầu lớp (trùng, ảnh hưởng start,bstart thì không cần gán lại 2 con trỏ đó)
					t->next = s->next;
					delete s;
					return 1;
				}
			}
		}
		t = s;
		s = s->next;
	}
	return 0;
}

//Kiem Tra De khong xoa sinh vien da dk lop tin chi 1-> có đk, 0->không có
int KiemTraSvTrongLop(DS_LopTinChi& ds_ltc, SinhVien sv) {
	DS_DangKy* p = NULL;
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		p = ds_ltc.ds[i]->head;
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

	PhanTrangLopSinhVien(sv.maLop, trang, start);
	while (true) {
		//Kiểm tra lớp có tồn tại hay không, để ở dưới delete không cần check nữa.
		/*if (isExistClass(sv.maLop) == 0) { //Đã kiểm tra khi nhập lớp rồi
			return;
		}*/
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
				ButtonXacNhanXoa(choice);
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
							//Alert("Khong Duoc Xoa Sinh Vien Nay!!!", 34, 15, 4, 900);
							Alert("Khong Duoc Xoa Ma Sinh Vien Nay!!!", 34, 15, 4, 900);
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
							//Alert("Ma Sinh Vien Khong Co Trong Lop!!!", 34, 15, 4, 900);
							Alert("Khong Duoc Xoa Ma Sinh Vien Nay!!!", 34, 15, 4, 900);

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
							PhanTrangLopSinhVien(sv.maLop, trang, start);
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
							//Xóa hết thì out ra luôn
							if (start == NULL || strcmp(start->sinhVien.maLop, sv.maLop) != 0) {
								clrscr();
								return;
							}
							PhanTrangLopSinhVien(sv.maLop, trang, start);
							break;
						}
					}
				}
			}
		}
		if (key == F3)
			PhanTrangLopSinhVien(sv.maLop, trang, start, "F3");
		if (key == F2)
			PhanTrangLopSinhVien(sv.maLop, trang, start, "F2");
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
	DS_SinhVien* p = first;
	//Không cần p!=null vì sure lớp đã tồn tại ở InDSSV
	while (p != NULL) {
		if (strcmp(p->sinhVien.maLop, maLop) == 0)
			break;
		p = p->next;
	}
	PhanTrangLopSinhVien(maLop, trang, p);
	KhungHuongDanInDSSV();
	while (true) {
		key = GetKey();
		if (key == RIGHT) {
			PhanTrangLopSinhVien(maLop, trang, p, "F3");
			KhungHuongDanInDSSV();
		}
		if (key == LEFT) {
			PhanTrangLopSinhVien(maLop, trang, p, "F2");
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

void Luu_NLR(DS_MonHoc* p, ofstream& fileOutput) {

}

//cách lưu LNR làm biến đổi cây khi đọc
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

//Sử dụng Selection Sort cho danh sách môn học
void SelectionSortDSMH(MonHoc*& arr, int n) {         //Danh sách môn học có n môn học
	MonHoc min;
	int vitrimin;
	for (int i = 0; i < n - 1; i++) {
		min = arr[i];
		vitrimin = i;
		for (int j = i + 1; j < n; j++)
			if (strcmp(arr[j].tenMonHoc, min.tenMonHoc) < 0) {
				min = arr[j];
				vitrimin = j;
			}
		arr[vitrimin] = arr[i];
		arr[i] = min;
	}
}

void PhanTrangDSMonHoc(DS_MonHoc* p, int& trang, string choice = "") {
	KhungDSMonHoc();
	//Phan Trang
	int dem = 0, tongTrang = 0;
	int tongMonHoc = 0;
	DemInorder(tree, tongMonHoc);

	//con trỏ mảng chứa môn học có thứ tự theo cây nhị phân tìm kiếm
	MonHoc* mhArr = new MonHoc[tongMonHoc];

	//Con trỏ mảng chứa môn học có thứ tự theo tên môn học
	MonHoc* mhArrSort = new MonHoc[tongMonHoc];

	//Biến đệ quy (không reset mỗi lần đệ quy)
	int count = 0;
	TreeToArray(tree, count, mhArr);
	count = 0;
	TreeToArray(tree, count, mhArrSort);

	//Sắp xếp Selection Sort cho mảng
	SelectionSortDSMH(mhArrSort, tongMonHoc);

	if (tongMonHoc == 0) {
		delete[] mhArr;
		delete[] mhArrSort;
		return;
	}

	tongTrang = ((tongMonHoc - 1) / 15 + 1);
	if (choice == "F3" && trang < (tongTrang - 1)) {
		trang++;
	}
	if (choice == "F2" && trang > 0) {
		trang--;
	}
	if (choice == "F3SORT" && trang < (tongTrang - 1)) {
		trang++;
	}
	if (choice == "F2SORT" && trang > 0) {
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

	if (choice == "F2SORT" || choice == "F3SORT" || choice == "SORT") {
		for (int i = trang * 15; i < 15 + trang * 15 && i < tongMonHoc; i++) {
			SetBGColor(7);
			SetColor(1);
			gotoxy(12, 14 + (i - trang * 15));
			cout << mhArrSort[i].maMonHoc;
			gotoxy(25, 14 + (i - trang * 15));
			cout << mhArrSort[i].tenMonHoc;
			gotoxy(65, 14 + (i - trang * 15));
			cout << mhArrSort[i].soTCLT;
			gotoxy(74, 14 + (i - trang * 15));
			cout << mhArrSort[i].soTCTH;
		}
	} else
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


	delete[] mhArr;
	delete[] mhArrSort;
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
			gotoxy(63 + vitri, 7);
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

//Tìm giá trị của cực trái
DS_MonHoc* rp;
MonHoc LeftMostValue(DS_MonHoc* p) {
	if (p->left != NULL)
		LeftMostValue(p->left);
	else
		return p->monHoc;
}

DS_MonHoc* Remove(DS_MonHoc*& p, char maMonHoc[]) {
	if (p == NULL)
		return p;
	if (strcmp(maMonHoc, p->monHoc.maMonHoc) < 0) {
		p->left = Remove(p->left, maMonHoc);
	} else if (strcmp(maMonHoc, p->monHoc.maMonHoc) > 0) {
		p->right = Remove(p->right, maMonHoc);
	} else {			              //Tìm được key
		rp = p;
		if (rp->right == NULL) {
			p = rp->left;		      //p có thể là lá hoặc là nút có cây con bên trái
			delete rp;
			return p;
		}
		if (rp->left == NULL) {
			p = rp->right;
			delete rp;
			return p;
		}
		p->monHoc = LeftMostValue(p->right);
		p->right = Remove(p->right, p->monHoc.maMonHoc);
	}
	return p;
}

//Check có lớp tín chỉ sử dụng mã môn hay không
int IsUsed(DS_LopTinChi& ds_ltc, char maMonhoc[]) {
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (strcmp(ds_ltc.ds[i]->maMonHoc, maMonhoc) == 0)
			return 1;
	}
	return 0;
}

void XoaMonHoc(DS_LopTinChi& ds_ltc) {
	KhungXoaMonHoc();
	KhungDSMonHoc();
	HuongDanThemMonHoc();
	int key, vitri = 0, trang = 0;
	PhanTrangDSMonHoc(tree, trang);
	TurnOKButtonKhungXoaMonHoc(false);

	char maMonHoc[10];
	maMonHoc[0] = '\0';

MaMonHoc:
	while (true) {
		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(42 + vitri, 7);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
			maMonHoc[vitri] = toupper((char)key);
			cout << maMonHoc[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(42 + vitri, 7);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			maMonHoc[vitri] = '\0';
			if (maMonHoc[0] == '\0') {
				Alert("Chua Nhap Ma Mon Hoc", 30, 9, 4, 900);
				continue;
			}
			if (CheckTrungMMH(tree, maMonHoc) == NULL) {
				Alert("Ma Mon Hoc Khong Ton Tai!!!", 30, 9, 4, 900);
				continue;
			}
			goto OK;
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
OK:
	TurnOKButtonKhungXoaMonHoc(true);
	while (true) {
		key = GetKey();
		if (key == ENTER) {
			bool choice = false;
			while (true) {
				ButtonXacNhanXoa(choice);
				key = GetKey();
				if (key == RIGHT || key == LEFT)
					choice = !choice;
				if (key == ENTER) {
					if (choice == false) {
						//restart
						SetBGColor(7);
						gotoxy(38, 10);
						cout << "                      ";

						vitri = 0;
						maMonHoc[0] = '\0';
						KhungXoaMonHoc();
						KhungDSMonHoc();
						PhanTrangDSMonHoc(tree, trang);
						goto MaMonHoc;
					}
					if (choice == true) {
						if (IsUsed(ds_ltc, maMonHoc)) {
							Alert("Khong The Xoa!!!", 40, 9, 4, 900);
						} else {
							Remove(tree, maMonHoc);
							Alert("Da Xoa Mon Hoc Thanh Cong!!!", 40, 9, 2, 900);
						}
						//restart
						SetBGColor(7);
						gotoxy(38, 10);
						cout << "                      ";
						vitri = 0;
						maMonHoc[0] = '\0';
						KhungXoaMonHoc();
						KhungDSMonHoc();
						PhanTrangDSMonHoc(tree, trang);
						goto MaMonHoc;
					}
				}
			}
		}
		if (key == LEFT) {
			TurnOKButtonKhungXoaMonHoc(false);
			vitri = strlen(maMonHoc);
			gotoxy(42 + vitri, 7);
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
	return;
}

void InDSMH() {
	KhungDSMonHoc("IN");
	int key, trang = 0;
	PhanTrangDSMonHoc(tree, trang, "SORT");
	HuongDanInDSMH();
	while (true) {
		key = GetKey();
		if (key == LEFT) {
			PhanTrangDSMonHoc(tree, trang, "F2SORT");
		}
		if (key == RIGHT) {
			PhanTrangDSMonHoc(tree, trang, "F3SORT");
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
	return;
}

//Không dùng nữa
DS_MonHoc* Delete(DS_MonHoc* root, int value) {
	if (root == NULL)
		return root;
	if (value < root->monHoc.soTCLT)
		root->left = Delete(root->left, value);
	else if (value > root->monHoc.soTCLT)
		root->right = Delete(root->right, value);
	else {
		// root->data == value, delete this node
		if (root->left == NULL) {
			DS_MonHoc* newRoot = root->right;
			free(root);
			return newRoot;
		}
		if (root->right == NULL) {
			DS_MonHoc* newRoot = root->left;
			free(root);
			return newRoot;
		}
		//root->monHoc = LeftMostValue(root->right);
		root->right = Delete(root->right, root->monHoc.soTCTH);
	}
	return root;
}

//---------------------------------------------KET THUC QUAN LY MON HOC----------------------------------------------------

//-----------------------------------------------DANG KY MON HOC-----------------------------------------------------------

//Tìm Mã Môn Học dựa vào Mã Lớp Tín Chỉ
string TimMMH(DS_LopTinChi& ds_ltc, int maLopTinChi) {
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (ds_ltc.ds[i]->maLopTinChi == maLopTinChi)
			return string(ds_ltc.ds[i]->maMonHoc);
	}
	return "";
}

//Kiểm tra (int)x có tồn tại trong arr => 1:TRUE, 0:FALSE
int CheckExist(int arr[50], int x) {
	for (int i = 0; i < 50; i++) {
		if (arr[i] == 0)
			return 0;
		if (arr[i] == x)
			return 1;
	}
	return 0;
}

//Đếm số sinh viên của 1 lớp tín chỉ, choice == "TRACK" => Track vị trí của lớp tín chỉ trong danh sách lớp tín chỉ
int DemSoSinhVien1Lop(DS_LopTinChi& ds_ltc, int maLopTinChi, string choice = "") {
	int count = 0;
	DS_DangKy* p = NULL;
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (ds_ltc.ds[i]->maLopTinChi == maLopTinChi) {
			if (choice == "TRACK")
				return i;
			p = ds_ltc.ds[i]->head;
			break;
		}
	}
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}

//choice == "THEM" HOẶC choice == "XOA" mã lớp tín chỉ khỏi arr
void AddOrRemove(int arr[50], int maLopTinChi, string choice) {
	if (choice == "THEM") {
		for (int i = 0; i < 50; i++) {
			if (arr[i] == 0) {
				arr[i] = maLopTinChi;
				return;
			}
		}
	}
	if (choice == "XOA") {
		for (int i = 0; i < 50; i++) {
			if (arr[i] == maLopTinChi) {
				for (int k = i; k < 50; k++) {
					if (k == 49)
						arr[k] = 0;
					if (arr[k] == 0)
						return;
					arr[k] = arr[k + 1];
				}
			}
		}
	}
	return;
}

//choice == "THEM" HOẶC choice == "XOA" mã lớp tín chỉ khỏi arr
void LuuLuaChon(DS_LopTinChi& ds_ltc, char mssv[], int arrXacNhan[], int maLopTinChi, string choice) {
	if (choice == "THEM") {
		for (int i = 0; i < 50; i++) {
			if (arrXacNhan[i] == 0) {
				arrXacNhan[i] = maLopTinChi;
				return;
			}
		}
	}
	if (choice == "XOA") {
		for (int i = 0; i < 50; i++) {
			if (arrXacNhan[i] == maLopTinChi) {
				for (int k = i; k < 50; k++) {
					if (k == 49)
						arrXacNhan[k] = 0;
					if (arrXacNhan[k] == 0)
						return;
					arrXacNhan[k] = arrXacNhan[k + 1];
				}
			}
		}
	}
	return;
}

//Choice == "UPDATE" || choice == "CONTROL";
int LopTinChiDaChon(DS_LopTinChi& ds_ltc, int arrXacNhan[], int arrCam[], LopTinChi* arr, int soLuongLTC, int trang, char mssv[], string choice = "UPDATE") {
	KhungLuuLuaChon();
	ButtonKhungLuuLuaChon(true);
	int key, move = 0, tongTrang = 0;

	//Số lượng phần tử của arrXacNhan (phần tử != 0)
	int soLuong = 0;
	for (int i = 0; i < 50; i++) {
		if (arrXacNhan[i] == 0)
			break;
		soLuong++;
	}
	tongTrang = ((soLuong - 1) / 15 + 1);
	if (soLuong == 0) {
		return 0;
	}

	DS_MonHoc* p = NULL;
	char x[10];
	if (choice == "UPDATE") {
		if (soLuong < 15) {
			trang = 0;
			tongTrang = 1;
		}

		for (int i = 15 * trang; i < 15 + 15 * trang && i < soLuong; i++) {
			strcpy_s(x, TimMMH(ds_ltc, arrXacNhan[i]).c_str());
			p = CheckTrungMMH(tree, x);
			SetColor(1);
			SetBGColor(7);
			gotoxy(96, 16 + i - 15 * trang);      //i có giá trị 0~15 nên không dùng làm index
			cout << p->monHoc.maMonHoc;
			gotoxy(110, 16 + i - 15 * trang);
			cout << p->monHoc.tenMonHoc;
			gotoxy(149, 16 + i - 15 * trang);
			cout << p->monHoc.soTCLT;
			gotoxy(155, 16 + i - 15 * trang);
			cout << p->monHoc.soTCTH;
			gotoxy(161, 16 + i - 15 * trang);
			cout << arr[i].nhom;
			gotoxy(160, 32);
			cout << trang + 1 << "/" << tongTrang;
		}
	}

RELOAD:
	if (choice == "CONTROL") {
		int i = 0;
		LopTinChiDaChon(ds_ltc, arrXacNhan, arrCam, arr, soLuongLTC, trang, mssv, "UPDATE");

		if (soLuong < 15) {
			trang = 0;
			tongTrang = 1;
		}
		// Tính toán lại số lượng để lúc delete load lại cho đúng, không crash
		soLuong = 0;
		for (int i = 0; i < 50; i++) {
			if (arrXacNhan[i] == 0)
				break;
			soLuong++;
		}
		tongTrang = ((soLuong - 1) / 15 + 1);
		if (soLuong == 0) {
			return 0;
		}

		//Thanh sáng mặc định ở move 0
		{
			i = 15 * trang + move;
			strcpy_s(x, TimMMH(ds_ltc, arrXacNhan[i]).c_str());
			p = CheckTrungMMH(tree, x);
			SetBGColor(15);
			SetColor(3);
			gotoxy(95, 16 + move);
			cout << "                                                                       ";
			SetColor(4);
			gotoxy(96, 16 + move);
			cout << p->monHoc.maMonHoc;
			gotoxy(110, 16 + move);
			cout << p->monHoc.tenMonHoc;
			gotoxy(149, 16 + move);
			cout << p->monHoc.soTCLT;
			gotoxy(155, 16 + move);
			cout << p->monHoc.soTCTH;
			gotoxy(161, 16 + move);
			cout << arr[i].nhom;
		}

		while (true) {
			key = GetKey();
			if (key == DOWN) {
				move++;
				if (trang == tongTrang - 1) {
					if ((move > soLuong % 15 - 1) && (soLuong % 15 != 0)) {
						move = soLuong % 15 - 1;
					}
				}
				if (move > 14) {
					move = 14;
				}
				if (move > soLuong - 1) {
					move = soLuong - 1;
				}
				i = 15 * trang + move;
				strcpy_s(x, TimMMH(ds_ltc, arrXacNhan[i - 1]).c_str());
				p = CheckTrungMMH(tree, x);
				if (move - 1 >= 0) {
					SetColor(5);
					SetBGColor(7);
					gotoxy(95, 16 + move - 1);
					cout << "|          |                                        |     |     |     |";
					SetColor(1);
					gotoxy(96, 16 + move - 1);
					cout << p->monHoc.maMonHoc;
					gotoxy(110, 16 + move - 1);
					cout << p->monHoc.tenMonHoc;
					gotoxy(149, 16 + move - 1);
					cout << p->monHoc.soTCLT;
					gotoxy(155, 16 + move - 1);
					cout << p->monHoc.soTCTH;
					gotoxy(161, 16 + move - 1);
					cout << arr[i - 1].nhom;
				}
				strcpy_s(x, TimMMH(ds_ltc, arrXacNhan[i]).c_str());
				p = CheckTrungMMH(tree, x);
				SetBGColor(15);
				SetColor(3);
				gotoxy(95, 16 + move);
				cout << "                                                                       ";
				SetColor(4);
				gotoxy(96, 16 + move);
				cout << p->monHoc.maMonHoc;
				gotoxy(110, 16 + move);
				cout << p->monHoc.tenMonHoc;
				gotoxy(149, 16 + move);
				cout << p->monHoc.soTCLT;
				gotoxy(155, 16 + move);
				cout << p->monHoc.soTCTH;
				gotoxy(161, 16 + move);
				cout << arr[i].nhom;
			}
			if (key == UP) {
				move--;
				if (move < 1) {
					move = 0;
				}
				if (move > soLuong - 1) {
					move = soLuong - 1;
				}
				i = 15 * trang + move;

				if (i + 1 < soLuong) {           // i + 1 < count để UP 1 phần tử không bị lỗi vì không có phần tử sau nó
					strcpy_s(x, TimMMH(ds_ltc, arrXacNhan[i + 1]).c_str());
					p = CheckTrungMMH(tree, x);
				}

				if (move + 1 <= 15) {
					if (i + 1 < soLuong) {      //Ngan bug 1 slot o trang
						SetColor(5);
						SetBGColor(7);
						gotoxy(95, 16 + move + 1);
						cout << "|          |                                        |     |     |     |";
						SetColor(1);
						gotoxy(96, 16 + move + 1);
						cout << p->monHoc.maMonHoc;
						gotoxy(110, 16 + move + 1);
						cout << p->monHoc.tenMonHoc;
						gotoxy(149, 16 + move + 1);
						cout << p->monHoc.soTCLT;
						gotoxy(155, 16 + move + 1);
						cout << p->monHoc.soTCTH;
						gotoxy(161, 16 + move + 1);
						cout << arr[i + 1].nhom;
					}
				}
				strcpy_s(x, TimMMH(ds_ltc, arrXacNhan[i]).c_str());
				p = CheckTrungMMH(tree, x);
				SetBGColor(15);
				SetColor(3);
				gotoxy(95, 16 + move);
				cout << "                                                                       ";
				SetColor(4);
				gotoxy(96, 16 + move);
				cout << p->monHoc.maMonHoc;
				gotoxy(110, 16 + move);
				cout << p->monHoc.tenMonHoc;
				gotoxy(149, 16 + move);
				cout << p->monHoc.soTCLT;
				gotoxy(155, 16 + move);
				cout << p->monHoc.soTCTH;
				gotoxy(161, 16 + move);
				cout << arr[i].nhom;
			}
			if (key == LEFT && trang > 0) {
				trang--;
				move = 0;
				goto RELOAD;
			}
			if (key == RIGHT && trang < tongTrang - 1) {
				trang++;
				move = 0;
				goto RELOAD;
			}
			if (key == ENTER) {
				//int index = -1;
				////Check lớp cùng mã môn đã bị cấm để mở cấm cho lớp đó
				//for (int i = 0; i < soLuongLTC; i++) {
				//	if (arr[i].maLopTinChi == arrXacNhan[move + trang * 15]) {
				//		index = i;
				//	}
				//}
				//for (int i = 0; i < soLuongLTC; i++) {
				//	if (index != -1 && arr[i].nhom != arr[index].nhom
				//		&& strcmp(arr[i].maMonHoc, arr[index].maMonHoc) == 0) {
				//		AddOrRemove(arrCam, arr[i].maLopTinChi, "XOA");
				//	}
				//}
				LuuLuaChon(ds_ltc, mssv, arrXacNhan, arrXacNhan[move + trang * 15], "XOA");

				move = 0;
				trang = 0;
				goto RELOAD;
			}
			if (key == F1) {                      //Add đăng ký mới vào cuối ds liên kết đăng ký
				DS_DangKy* ptr = NULL;
				for (int i = 0; i < 50; i++) {
					if (arrXacNhan[i] == 0) {    //Hết giá trị
						break;
					}
					int viTriLopTinChi = DemSoSinhVien1Lop(ds_ltc, arrXacNhan[i], "TRACK");
					ptr = ds_ltc.ds[viTriLopTinChi]->head;
					if (ptr == NULL) {
						DS_DangKy* newDK = new DS_DangKy;
						newDK->dangKy.diem = 0;
						strcpy_s(newDK->dangKy.maSV, mssv);
						newDK->next = NULL;
						ds_ltc.ds[viTriLopTinChi]->head = newDK;
						//continue;
						ptr = NULL;
					}
					while (ptr != NULL) {
						if (ptr->next == NULL) {
							DS_DangKy* newDK = new DS_DangKy;
							newDK->dangKy.diem = 0;
							strcpy_s(newDK->dangKy.maSV, mssv);
							newDK->next = NULL;
							ptr->next = newDK;
							break;
						}
						ptr = ptr->next;
					}
				}
				LuuDSDK(ds_ltc);
				return 1;
			}
			if (key == ESC) {
				ButtonKhungLuuLuaChon(false);
				return 0;
			}
		}
	}
	return 0;
}

int ChonLopTinChi(DS_LopTinChi& ds_ltc, int hocKy, int nienKhoa, char mssv[], int arrXacNhan[], int arrCam[]) {
RESET:
	KhungLuuLuaChon();
	KhungChonLopTinChi();
	ButtonKhungLuuLuaChon(false);

	//Count là số lượng lớp tín chỉ phù hợp
	int count = 0, trang = 0, tongTrang = 0, key, soTinChiDangKy = 0;
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (ds_ltc.ds[i]->hocKy == hocKy && ds_ltc.ds[i]->nienKhoa == nienKhoa)
			count++;
	}
	tongTrang = ((count - 1) / 15 + 1);
	if (count == 0) {       //Không có lớp tín chỉ phù hợp
		//Alert
		return 2;
	}

	//Nếu sinh viên đã có mặt tại ít nhất 1 lớp nào đó trong niên khóa + học kỳ thì không đc đăng ký nữa
	DS_DangKy* s = NULL;
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (ds_ltc.ds[i]->nienKhoa == nienKhoa && ds_ltc.ds[i]->hocKy == hocKy) {
			s = ds_ltc.ds[i]->head;
			while (s != NULL) {
				if (strcmp(s->dangKy.maSV, mssv) == 0) {
					//Alert
					return 1;
				}
				s = s->next;
			}
		}
	}

	//Add vào arrCam những lớp tín chỉ có số sinh viên đầy
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (ds_ltc.ds[i]->nienKhoa == nienKhoa && ds_ltc.ds[i]->hocKy == hocKy) {
			int soLuongSinhVien = DemSoSinhVien1Lop(ds_ltc, ds_ltc.ds[i]->maLopTinChi);
			if (soLuongSinhVien == ds_ltc.ds[i]->svMax) {
				AddOrRemove(arrCam, ds_ltc.ds[i]->maLopTinChi, "THEM");
			}
		}
	}

	LopTinChi* arr = new LopTinChi[count];
	int k, i;
	for (i = 0, k = 0; i < ds_ltc.soLuong && k < count; i++) {               //Không k < count báo lỗi sẽ tràn
		if (ds_ltc.ds[i]->hocKy == hocKy && ds_ltc.ds[i]->nienKhoa == nienKhoa) {
			arr[k] = *(ds_ltc.ds[i]);
			k++;
		}
	}

	//Thanh Sáng, move là vị trí chọn thanh sáng, move bắt đầu từ 0
	int move = 0;
	//Tính lại tổng tín chỉ đã đăng ký
	for (int i = 0; i < 50; i++) {
		DS_MonHoc* temp = NULL;
		if (arrXacNhan[i] == 0)
			break;
		for (int k = 0; k < count; k++) {
			if (arrXacNhan[i] == arr[k].maLopTinChi) {
				temp = CheckTrungMMH(tree, arr[k].maMonHoc);
				soTinChiDangKy += (temp->monHoc.soTCLT + temp->monHoc.soTCTH);
				break;
			}
		}
	}
RELOAD:
	if (count < 15) {
		tongTrang = 1;
		trang = 0;
	}
	DS_MonHoc* p = NULL;      //p sẽ chứa địa chỉ của mã môn học trong cây
	for (int i = trang * 15; i < 15 + trang * 15 && i < count; i++) {
		p = CheckTrungMMH(tree, arr[i].maMonHoc);
		SetColor(1);
		SetBGColor(7);
		gotoxy(11, 16 + i - trang * 15);
		cout << arr[i].maMonHoc;
		gotoxy(22, 16 + i - trang * 15);
		cout << p->monHoc.tenMonHoc;
		gotoxy(64, 16 + i - trang * 15);
		cout << DemSoSinhVien1Lop(ds_ltc, arr[i].maLopTinChi) << "/" << arr[i].svMax;
		gotoxy(73, 16 + i - trang * 15);
		cout << p->monHoc.soTCLT;
		gotoxy(79, 16 + i - trang * 15);
		cout << p->monHoc.soTCTH;
		gotoxy(85, 16 + i - trang * 15);
		cout << arr[i].nhom;
		gotoxy(84, 32);
		cout << trang + 1 << "/" << tongTrang;

		if (CheckExist(arrXacNhan, arr[i].maLopTinChi)) {
			gotoxy(5, 16 + i - trang * 15);
			SetBGColor(2);
			cout << "   ";
		}
		if (CheckExist(arrCam, arr[i].maLopTinChi)) {
			gotoxy(5, 16 + i - trang * 15);
			SetBGColor(4);
			cout << "   ";
		}
		TongChi(soTinChiDangKy, 20);
	}

	//Thanh sáng mặc định ở move 0 
	{
		i = 15 * trang + move;
		p = CheckTrungMMH(tree, arr[i].maMonHoc);
		//if (move - 1 >= 0) {
		SetBGColor(15);
		SetColor(3);
		gotoxy(10, 16 + move);
		cout << "                                                                                ";
		SetColor(4);
		gotoxy(11, 16 + move);
		cout << arr[i].maMonHoc;
		gotoxy(22, 16 + move);
		cout << p->monHoc.tenMonHoc;
		gotoxy(64, 16 + move);
		cout << DemSoSinhVien1Lop(ds_ltc, arr[i].maLopTinChi) << "/" << arr[i].svMax;
		gotoxy(73, 16 + move);
		cout << p->monHoc.soTCLT;
		gotoxy(79, 16 + move);
		cout << p->monHoc.soTCTH;
		gotoxy(85, 16 + i - trang * 15);
		cout << arr[i].nhom;
		//}
	}

	p == NULL;
	while (true) {
		key = GetKey();
		if (key == DOWN) {
			move++;
			if (trang == tongTrang - 1) {
				if ((move > count % 15 - 1) && (count % 15 != 0)) {
					move = count % 15 - 1;
				}
			}
			if (move > 14) {
				move = 14;
			}
			if (move > count - 1) {
				move = count - 1;
			}
			i = 15 * trang + move;
			p = CheckTrungMMH(tree, arr[i - 1].maMonHoc);
			if (move - 1 >= 0) {
				SetColor(5);
				SetBGColor(7);
				gotoxy(10, 16 + move - 1);
				cout << "|          |                                        |        |     |     |     |";
				SetColor(1);
				gotoxy(11, 16 + move - 1);
				cout << arr[i - 1].maMonHoc;
				gotoxy(22, 16 + move - 1);
				cout << p->monHoc.tenMonHoc;
				gotoxy(64, 16 + move - 1);
				cout << DemSoSinhVien1Lop(ds_ltc, arr[i - 1].maLopTinChi) << "/" << arr[i - 1].svMax;
				gotoxy(73, 16 + move - 1);
				cout << p->monHoc.soTCLT;
				gotoxy(79, 16 + move - 1);
				cout << p->monHoc.soTCTH;
				gotoxy(85, 16 + move - 1);
				cout << arr[i - 1].nhom;

			}
			p = CheckTrungMMH(tree, arr[i].maMonHoc);
			SetBGColor(15);
			SetColor(3);
			gotoxy(10, 16 + move);
			cout << "                                                                                ";
			SetColor(4);
			gotoxy(11, 16 + move);
			cout << arr[i].maMonHoc;
			gotoxy(22, 16 + move);
			cout << p->monHoc.tenMonHoc;
			gotoxy(64, 16 + move);
			cout << DemSoSinhVien1Lop(ds_ltc, arr[i].maLopTinChi) << "/" << arr[i].svMax;
			gotoxy(73, 16 + move);
			cout << p->monHoc.soTCLT;
			gotoxy(79, 16 + move);
			cout << p->monHoc.soTCTH;
			gotoxy(85, 16 + move);
			cout << arr[i].nhom;
		}
		if (key == UP) {
			move--;
			if (move < 1) {
				move = 0;
			}
			if (move > count - 1) {
				move = count - 1;
			}
			i = 15 * trang + move;

			if (i + 1 < count) {           // i + 1 < count để UP 1 phần tử không bị lỗi vì không có phần tử sau nó
				p = CheckTrungMMH(tree, arr[i + 1].maMonHoc);
			}

			if (move + 1 <= 15) {
				if (i + 1 < count) {      //Ngan bug 1 slot o trang
					SetColor(5);
					SetBGColor(7);
					gotoxy(10, 16 + move + 1);
					cout << "|          |                                        |        |     |     |     |";

					SetColor(1);
					SetBGColor(7);
					gotoxy(11, 16 + move + 1);
					cout << arr[i + 1].maMonHoc;
					gotoxy(22, 16 + move + 1);
					cout << p->monHoc.tenMonHoc;
					gotoxy(64, 16 + move + 1);
					cout << DemSoSinhVien1Lop(ds_ltc, arr[i + 1].maLopTinChi) << "/" << arr[i + 1].svMax;
					gotoxy(73, 16 + move + 1);
					cout << p->monHoc.soTCLT;
					gotoxy(79, 16 + move + 1);
					cout << p->monHoc.soTCTH;
					gotoxy(85, 16 + move + 1);
					cout << arr[i + 1].nhom;
				}
			}
			p = CheckTrungMMH(tree, arr[i].maMonHoc);
			SetBGColor(15);
			SetColor(3);
			gotoxy(10, 16 + move);
			cout << "                                                                                ";
			SetColor(4);
			gotoxy(11, 16 + move);
			cout << arr[i].maMonHoc;
			gotoxy(22, 16 + move);
			cout << p->monHoc.tenMonHoc;
			gotoxy(64, 16 + move);
			cout << DemSoSinhVien1Lop(ds_ltc, arr[i].maLopTinChi) << "/" << arr[i].svMax;
			gotoxy(73, 16 + move);
			cout << p->monHoc.soTCLT;
			gotoxy(79, 16 + move);
			cout << p->monHoc.soTCTH;
			gotoxy(85, 16 + move);
			cout << arr[i].nhom;

		}
		if (key == ENTER && p != NULL) {
			int position = move + trang * 15;    //Vị trí nhấn enter
			DS_MonHoc* mh = CheckTrungMMH(tree, arr[position].maMonHoc);
			if (CheckExist(arrXacNhan, arr[position].maLopTinChi)) {          //Vì move chỉ từ 0~14
				//if (CheckExist(arrCam, arr[move + trang * 15].maLopTinChi) != 1)       //Check Lớp bị cấm đăng ký
				LuuLuaChon(ds_ltc, mssv, arrXacNhan, arr[position].maLopTinChi, "XOA");
				soTinChiDangKy -= mh->monHoc.soTCLT + mh->monHoc.soTCTH;
				TongChi(soTinChiDangKy, 20);

				//Check lớp cùng mã môn đã bị cấm để mở cấm cho lớp đó
				/*for (int i = 0; i < count; i++) {
					if (strcmp(arr[i].maMonHoc, arr[position].maMonHoc) == 0
						&& arr[i].nhom != arr[position].nhom) {
						AddOrRemove(arrCam, arr[i].maLopTinChi, "XOA");
					}
				}*/
			} else {
				if (CheckExist(arrCam, arr[position].maLopTinChi) != 1) {       //Check Lớp bị cấm đăng ký
					if (soTinChiDangKy + mh->monHoc.soTCLT + mh->monHoc.soTCTH <= 20) {
						LuuLuaChon(ds_ltc, mssv, arrXacNhan, arr[position].maLopTinChi, "THEM");
						soTinChiDangKy += mh->monHoc.soTCLT + mh->monHoc.soTCTH;
						TongChi(soTinChiDangKy, 20);
					}
					//Check lớp cùng mã môn để cấm (Vì danh sách lớp trong mảng arr đã là cùng niên khóa + học kỳ rồi)
					//for (int i = 0; i < count; i++) {
					//	if (strcmp(arr[i].maMonHoc, arr[position].maMonHoc) == 0     //Cùng mã môn
					//		&& arr[i].nhom != arr[position].nhom) {                  //Khác nhóm để tránh cấm chính nó 
					//		AddOrRemove(arrCam, arr[i].maLopTinChi, "THEM");
					//	}
					//}
				}
			}
			LopTinChiDaChon(ds_ltc, arrXacNhan, arrCam, arr, count, 0, mssv, "UPDATE");
			ButtonKhungLuuLuaChon(false);
			KhungChonLopTinChi();
			goto RELOAD;
		}
		if (key == LEFT && trang > 0) {
			trang--;
			move = 0;
			KhungChonLopTinChi();
			goto RELOAD;
		}
		if (key == RIGHT && trang < tongTrang - 1) {
			trang++;
			move = 0;
			KhungChonLopTinChi();
			goto RELOAD;
		}
		if (key == F4) {
			int style = LopTinChiDaChon(ds_ltc, arrXacNhan, arrCam, arr, count, 0, mssv, "CONTROL");
			LopTinChiDaChon(ds_ltc, arrXacNhan, arrCam, arr, count, 0, mssv, "UPDATE");
			ButtonKhungLuuLuaChon(false);
			if (style == 1) {
				delete[] arr;
				return 0;
			}
			goto RESET;
		}
		if (key == ESC) {
			KhungChonLopTinChi();   //không hiểu sao không có thì màu sai 
			KhungLuuLuaChon();
			clrscr();
			delete[] arr;
			return 0;
		}
	}
	delete[] arr;
	return 0;
}

void TimKiemLopTinChi(DS_LopTinChi& ds_ltc, char mssv[]) {
	KhungTimKiem();
	int key, vitri = 0;
	int hocKy = 0; int nienKhoa = 0;
	char nienKhoa_ch[5];
	nienKhoa_ch[0] = '\0';
	char hocKy_ch[3];
	hocKy_ch[0] = '\0';

NIENKHOA:
	TongleTimKiem(false);

	//Mảng chứa các mã lớp tín chỉ đã được click chọn đăng ký (chưa lưu vào csdl), 50 số 0 by default
	int arrXacNhan[50] = {};

	//Mảng chứa các mã lớp tín chỉ không được phép đăng ký do vi phạm các yếu tố, 50 số 0 by default
	int arrCam[50] = {};

	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI THIEU: 4 KI TU     ";
	gotoxy(18, 40);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(18 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Duoc Bat Dau Bang So 0 ", 15, 10, 4, 900);
				continue;
			}
			nienKhoa_ch[vitri] = (char)key;
			cout << nienKhoa_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(18 + vitri, 8);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 15, 10, 4, 900);
				continue;
			}

			//Convert char[] to int (Nien Khoa)
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> nienKhoa;
			//

			vitri = (hocKy > 9) ? 2 : (hocKy == 0) ? 0 : 1;
			gotoxy(40 + vitri, 8);
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
	gotoxy(18, 38);
	cout << "                                                           ";
	gotoxy(18, 39);
	cout << "        HOC KY: GOM CAC SO (0-9), TOI DA: 2 KI TU          ";
	gotoxy(18, 40);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(40 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Hoc Ky Khong Duoc Bat Dau Bang So 0 ", 15, 10, 4, 900);
				continue;
			}
			hocKy_ch[vitri] = (char)key;
			cout << hocKy_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(40 + vitri, 8);
			cout << " ";
		}
		if (key == LEFT) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 15, 10, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> hocKy;
			//

			vitri = strlen(nienKhoa_ch); //Nien Khoa Set Bat Buoc 4 So
			gotoxy(18 + vitri, 8);
			goto NIENKHOA;
		}

		if (key == RIGHT || key == ENTER) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 15, 10, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> hocKy;
			//

			goto OK;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
OK:
	bool choice = true;
	TongleTimKiem(choice);
	while (true) {
		key = GetKey();
		if (key == LEFT) {
			choice = !choice;
			TongleTimKiem(choice);
			vitri = (hocKy > 9) ? 2 : (hocKy == 0) ? 0 : 1;
			gotoxy(40 + vitri, 8);
			goto HOCKY;
		}
		if (key == ENTER) {
			int style = ChonLopTinChi(ds_ltc, hocKy, nienKhoa, mssv, arrXacNhan, arrCam);
			if (style == 1) {
				Alert("Da dang ky nien khoa + hoc ky nay roi!!!", 15, 10, 4, 900);
			}
			if (style == 2) {
				Alert("Khong Tim Thay Lop Thich Hop!!!", 15, 10, 4, 900);
			}
			//Restart
			nienKhoa = 0;
			nienKhoa_ch[0] = '\0';
			hocKy = 0;
			hocKy_ch[0] = '\0';
			vitri = 0;
			KhungTimKiem();
			goto NIENKHOA;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
	return;
}

void DangKyLopTinCHi(DS_LopTinChi& ds_ltc) {
	KhungDangNhap();
	TongleDangNhap();
	//KhungTimKiem();

	int key, vitri = 0;
	char maSV[12];
	maSV[0] = '\0';


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
		gotoxy(15 + vitri, 8);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 11)) {
			maSV[vitri] = toupper((char)key);
			cout << maSV[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(15 + vitri, 8);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			maSV[vitri] = '\0';
			if (maSV[0] == '\0') {
				continue;
			}
			goto OK;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
OK:
	TongleDangNhap(true);
	bool choice = true;
	while (true) {
		key = GetKey();
		if (key == LEFT) {
			choice = !choice;
			vitri = strlen(maSV);
			TongleDangNhap(choice);
			goto MASV;
		}
		if (key == ENTER) {
			//Tạo con trỏ fake vì hàm này cần có con trỏ nhưng mình không xài tới.
			DS_SinhVien* fake = NULL;
			if (CheckTrungMSSV(maSV, maSV, fake, "0") == 1) {      //Hàm phải bỏ vào mã lớp mặc dù không cần, vì hàm dùng mục đích câu khác
				TimKiemLopTinChi(ds_ltc, maSV);
			} else {
				Alert("Sai Ma So Sinh Vien", 10, 10, 4, 900);
				continue;
			}
			break;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
	return;
}

//-------------------------------------------KET THUC DANG KY MON HOC------------------------------------------------

//------------------------------------------------BANG DIEM------------------------------------------------------
void TimHoTen(char mssv[12], string& name) {
	DS_SinhVien* head = first;
	while (head != NULL) {
		if (strcmp(head->sinhVien.maSV, mssv) == 0) {
			name = string(head->sinhVien.ho);
			name += ".";
			name += string(head->sinhVien.ten);
			break;
		}
		head = head->next;
	}
	return;
}

void ChuanHoaDiem(char diem[5]) {
	int ptu = 0;
	//Xóa dot đầu mảng
	/*while (diem[0] == '.') {
		for (int i = 0; i < 4; i++) {
			diem[i] = diem[i + 1];
		}
	}*/
	//Xóa dot cuối mảng
	/*while (true) {
		char track = '\0';
		int i;
		for (i = 0; i < 5; i++) {
			if (diem[i] == '\0')
				break;
			track = diem[i];
		}
		if (track == '.') {
			if (i != 0)
				diem[i - 1] = '\0';
			else
				break;
		} else
			break;
	}*/
	for (int i = 0; i < 5; i++) {
		if (diem[i] == '\0')
			break;
		ptu++;
	}
	/*if (ptu == 0) {
		diem[0] = '0';
		diem[1] = '\0';
		return;
	}*/
	if (ptu == 1) {
		char tam = diem[0];
		diem[0] = '0';
		diem[1] = '.';
		diem[2] = tam;
		diem[3] = '\0';
		return;
	}
	if (ptu == 2) {    //80 -> 8.0
		char tam = diem[1];
		diem[1] = '.';
		diem[2] = tam;
		diem[3] = '\0';
		return;
	}
	if (ptu == 3) {
		if (diem[0] == '1' && diem[1] == '0' && diem[2] == '0') {
			diem[2] = '.';
			diem[3] = '0';
			diem[4] = '\0';
			return;
		}
		diem[0] = '0';
		diem[1] = '\0';
		return;
	}
	return;
}

void PhanTrangNhapDiem(DS_DangKy* head, string* arrName, float* arrMark, int count, int& trang, string choice = "") {
	KhungNhapDiem();
	DS_DangKy* pDK = head;
	int tongTrang = 0;
	tongTrang = (count - 1) / 15 + 1;


	if (choice == "LEFT" && trang > 0) {
		trang--;
	}
	if (choice == "RIGHT" && trang < tongTrang - 1) {
		trang++;
	}

	for (int i = trang * 15; i < 15 + trang * 15 && i < count && pDK != NULL; i++) {         //pDK !=null không cần cũng đc vì có count là số sv đk của lớp
		SetColor(4);
		SetBGColor(7);
		gotoxy(17, 15 + i - 15 * trang);
		cout << i + 1;
		SetColor(1);
		gotoxy(21, 15 + i - 15 * trang);
		cout << pDK->dangKy.maSV;
		int k;
		for (k = 0; k < arrName[i].find('.'); k++) {
			gotoxy(35 + k, 15 + i - 15 * trang);
			cout << arrName[i][k];
		}
		k++;
		for (int j = k; j < arrName[i].length(); j++) {
			gotoxy(68 + j - k, 15 + i - 15 * trang);
			cout << arrName[i][j];
		}
		k = 0;
		gotoxy(80, 15 + i - 15 * trang);
		//cout << pDK->dangKy.diem;
		//cout << arrMark[i];
		int diem_int = arrMark[i] * 10;
		char diem[5];
		strcpy_s(diem, std::to_string(diem_int).c_str());
		ChuanHoaDiem(diem);
		cout << diem;
		gotoxy(79, 31);
		cout << trang + 1 << "/" << tongTrang;
		pDK = pDK->next;
	}
	return;
}

void InTieuDe(char tenMonHoc[], int nienKhoa_int, int hocKy_int, int nhom_int) {
	KhungInTieuDe();

	SetBGColor(7);
	SetColor(4);
	gotoxy(75, 38);
	cout << "                                   ";
	gotoxy(47, 6);
	cout << tenMonHoc;
	gotoxy(40, 8);
	cout << nienKhoa_int;
	gotoxy(57, 8);
	cout << hocKy_int;
	gotoxy(67, 8);
	cout << nhom_int;
}

//Choice == "IN" -> In bảng điểm lớp tín chỉ, choice == "" -> nhập bảng điểm lớp tín chỉ
void InBangNhapDiem(DS_DangKy* head, DS_LopTinChi& ds_ltc, char tenMonHoc[], int nienKhoa_int, int hocKy_int, int nhom_int, string choice = "") {
	KhungNhapDiem();
	int trang = 0, move = 0, tongTrang = 0, vitri = 0, key;
	DS_SinhVien* headDSSV = first;
	DS_DangKy* p = head;
	int count = 0; //Số sv có trong lớp
	while (p != NULL) {
		count++;
		p = p->next;
	}
	p = head;
	tongTrang = (count - 1) / 15 + 1;

	//Mảng chứa điểm
	float* arrMark = new float[count] {};
	//Mảng chứa tên họ
	string* arrName = new string[count];

	for (int i = 0; i < count && p != NULL; i++) {
		arrMark[i] = p->dangKy.diem;
		TimHoTen(p->dangKy.maSV, arrName[i]);
		p = p->next;
	}


	move = 0;
RELOAD:
	if (choice == "IN") {
		PhanTrangNhapDiem(head, arrName, arrMark, count, trang);
		InTieuDe(tenMonHoc, nienKhoa_int, hocKy_int, nhom_int);
	}

	if (choice == "") {
		PhanTrangNhapDiem(head, arrName, arrMark, count, trang);
		vitri = (arrMark[move + trang * 15] == 10) ? 2 : 1;
		{
			int i = move + trang * 15;
			SetColor(4);
			SetBGColor(15);
			if (i < count) {
				gotoxy(78, 15 + move);
				cout << "      ";
				gotoxy(80, 15 + move);
				int diem_int = arrMark[i] * 10;
				char diem[5];
				strcpy_s(diem, std::to_string(diem_int).c_str());
				ChuanHoaDiem(diem);
				cout << diem;
			}
		}
	}

	while (true) {
		key = GetKey();
		if (key == LEFT && (choice == "" || choice == "IN")) {
			PhanTrangNhapDiem(head, arrName, arrMark, count, trang, "LEFT");
			move = 0;
			goto RELOAD;
		}
		if (key == RIGHT && (choice == "" || choice == "IN")) {
			PhanTrangNhapDiem(head, arrName, arrMark, count, trang, "RIGHT");
			move = 0;
			goto RELOAD;
		}
		if (key == DOWN && choice == "") {
			move++;
			int diem_int;
			char diem[5];
			if (trang == tongTrang - 1) {
				if ((move > count % 15 - 1) && (count % 15 != 0)) {
					move = count % 15 - 1;
				}
			}
			if (move > 14) {
				move = 14;
			}
			if (move > count - 1) {
				move = count - 1;
			}
			int i = move + trang * 15;
			if (move - 1 >= 0) {
				SetBGColor(7);
				SetColor(1);
				gotoxy(78, 15 + move - 1);
				//if (i < count)         //Để không báo lỗi tràn
				cout << "      ";
				gotoxy(80, 15 + move - 1);
				diem_int = arrMark[i - 1] * 10;
				strcpy_s(diem, std::to_string(diem_int).c_str());
				ChuanHoaDiem(diem);
				cout << diem;
			}
			SetBGColor(15);
			SetColor(4);
			gotoxy(78, 15 + move);
			//if (move + trang * 15 < count)         //Để không báo lỗi tràn
			cout << "      ";
			gotoxy(80, 15 + move);
			diem_int = arrMark[i] * 10;
			strcpy_s(diem, std::to_string(diem_int).c_str());
			ChuanHoaDiem(diem);
			cout << diem;
		}
		if (key == UP && choice == "") {
			move--;
			int diem_int;
			char diem[5];
			if (move < 1) {
				move = 0;
			}
			if (move > count - 1) {
				move = count - 1;
			}
			int i = 15 * trang + move;
			if (move + 1 <= 15) {
				if (i + 1 < count) {      //Ngan bug 1 slot o trang
					SetBGColor(7);
					SetColor(1);
					gotoxy(78, 15 + move + 1);
					//if (move + trang * 15 < count)         //Để không báo lỗi tràn
					cout << "      ";
					gotoxy(80, 15 + move + 1);
					diem_int = arrMark[i + 1] * 10;
					strcpy_s(diem, std::to_string(diem_int).c_str());
					ChuanHoaDiem(diem);
					cout << diem;
				}
			}
			SetBGColor(15);
			SetColor(4);
			gotoxy(78, 15 + move);
			//if (i < count)         //Để không báo lỗi tràn
			cout << "      ";
			gotoxy(80, 15 + move);
			diem_int = arrMark[i] * 10;
			strcpy_s(diem, std::to_string(diem_int).c_str());
			ChuanHoaDiem(diem);
			cout << diem;
		}
		if (key == ENTER && choice == "") {
			vitri = (arrMark[move + trang * 15] * 10 == 100) ? 4 : (arrMark[move + trang * 15] * 10 > 9) ? 3 : 3;

			/*std::ostringstream ss;
			ss << arrMark[move + trang * 15];
			std::string s(ss.str());*/

			int diem_int = arrMark[move + trang * 15] * 10;
			char diem[5];
			strcpy_s(diem, std::to_string(diem_int).c_str());
			(vitri == 4) ? diem[3] = '\0' : (vitri == 3) ? diem[2] = '\0' : diem[1] = '\0';
			ChuanHoaDiem(diem);
			SetColor(15);
			SetBGColor(4);
			gotoxy(78, 15 + move);
			cout << "      ";
			gotoxy(80, 15 + move);
			cout << diem;
			while (true) {
				key = GetKey();
				if (key == BACKSPACE && vitri > 0) {
					vitri--;
					gotoxy(80 + vitri, 15 + move);
					cout << " ";
				}
				if (key == ENTER) {
					diem[vitri] = '\0';       //3 vị trí còn 2 vị trí dem[vitri] là đúng vì vị trí trong mảng - 1

					string diem_str(diem);
					int diem_temp = atof(diem_str.c_str()) * 10;           //diem[5] khi vào ChuanHoa phải đc * 10
					//*10 sẽ có trường hợp lên 10000, lố ký tự
					if (diem_temp > 1000)
						diem_temp = 0;
					strcpy_s(diem, std::to_string(diem_temp).c_str());

					ChuanHoaDiem(diem);
					string s(diem);
					stringstream geek(s);
					geek >> arrMark[move + trang * 15];
					goto RELOAD;
				}
				if ((key == 46 || (key >= '0' && key <= '9')) && vitri < 4) {
					diem[vitri] = (char)key;
					gotoxy(80 + vitri, 15 + move);
					cout << diem[vitri];
					vitri++;
				}
			}
		}
		if (key == F1 && choice == "") {
			p = head;
			for (int i = 0; p != NULL; i++, p = p->next) {
				p->dangKy.diem = arrMark[i];
			}
			LuuDSDK(ds_ltc);
			Alert("LUU FILE THANH CONG", 37, 10, 2, 900);
		}
		if (key == ESC) {
			//Clear Khung Thông Tin In Bảng Điểm vì nó lệch size
			SetBGColor(7);
			gotoxy(26, 5);
			cout << "                                                         ";
			gotoxy(26, 6);
			cout << "                                                         ";
			gotoxy(26, 7);
			cout << "                                                         ";
			gotoxy(26, 8);
			cout << "                                                         ";
			gotoxy(26, 9);
			cout << "                                                         ";

			KhungNhapThongTinTimKiem();
			break;
		}
	}
	delete[] arrMark;
	delete[] arrName;
	return;
}

//Choice == "IN" -> In Bảng Điểm Lớp Tín Chỉ
void NhapDiem(DS_LopTinChi& ds_ltc, string choice = "") {
	KhungNhapDiem();
	ButtonNhapDiem();
	KhungNhapThongTinTimKiem();

	//Che vài button không cần thiết của In
	if (choice == "IN") {
		SetBGColor(7);
		gotoxy(75, 38);
		cout << "                                   ";
	}


	int nienKhoa_int = 0;
	int hocKy_int = 0;
	int nhom_int = 0;
	char maMonHoc_ch[10];
	char nienKhoa_ch[5];
	char hocKy_ch[3];
	char nhom_ch[3];
	maMonHoc_ch[0] = '\0';
	nienKhoa_ch[0] = '\0';
	hocKy_ch[0] = '\0';
	nhom_ch[0] = '\0';

	int key, trang = 0, vitri = 0;

MAMONHOC:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 34);
	cout << "                                                           ";
	gotoxy(18, 35);
	cout << "  MA MON HOC: GOM CAC KI TU (A-Z) & (0-9),TOI DA: 9 KI TU  ";
	gotoxy(18, 36);
	cout << "                                                           ";
	while (true) {
		//Nhap Ma Mon Hoc
		SetColor(3);
		SetBGColor(7);
		gotoxy(30 + vitri, 8);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 9)) {
			maMonHoc_ch[vitri] = toupper((char)key);
			cout << maMonHoc_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(30 + vitri, 8);
			cout << " ";
		}
		if (key == RIGHT || key == ENTER) {
			maMonHoc_ch[vitri] = '\0';
			if (maMonHoc_ch[0] == '\0') {
				Alert("Chua Nhap Ma Mon Hoc", 37, 10, 4, 900);
				continue;
			}
			if (CheckTrungMMH(tree, maMonHoc_ch) == NULL) {
				Alert("Ma Mon Hoc Khong Ton Tai", 37, 10, 4, 900);
				continue;
			}
			vitri = strlen(nienKhoa_ch);
			goto NIENKHOA;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
NIENKHOA:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 34);
	cout << "                                                           ";
	gotoxy(18, 35);
	cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI THIEU: 4 KI TU     ";
	gotoxy(18, 36);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(46 + vitri, 8);
		key = GetKey();

		if (key <= '9' && key >= '0' && vitri < 4) {
			if (key == '0' && vitri == 0) {
				Alert("Nien Khoa Khong Bat Dau Bang 0", 37, 10, 4, 900);
				continue;
			}
			nienKhoa_ch[vitri] = (char)key;
			gotoxy(46 + vitri, 8);
			cout << nienKhoa_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(46 + vitri, 8);
			cout << " ";
		}
		if (key == LEFT) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 37, 10, 4, 900);
				continue;
			}
			//nienKhoa_ch to nienKhoa_int
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> nienKhoa_int;
			//
			vitri = strlen(maMonHoc_ch);
			goto MAMONHOC;
		}
		if (key == RIGHT || key == ENTER) {
			nienKhoa_ch[vitri] = '\0';
			if (nienKhoa_ch[0] == '\0' || strlen(nienKhoa_ch) < 4) {
				Alert("Nien Khoa Chua Nhap", 37, 10, 4, 900);
				continue;
			}
			//nienKhoa_ch to nienKhoa_int
			string nienKhoa_str(nienKhoa_ch);
			stringstream geek(nienKhoa_str);
			geek >> nienKhoa_int;
			//
			vitri = (hocKy_int >= 10) ? 2 : (hocKy_int == 0) ? 0 : 1;
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
	gotoxy(18, 34);
	cout << "                                                           ";
	gotoxy(18, 35);
	cout << "        HOC KY: GOM CAC SO (0-9), TOI DA: 2 KI TU          ";
	gotoxy(18, 36);
	cout << "                                                           ";
	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(58 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Hoc Ky Khong Duoc Bat Dau Bang So 0 ", 37, 10, 4, 900);
				continue;
			}
			hocKy_ch[vitri] = (char)key;
			cout << hocKy_ch[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(58 + vitri, 8);
			cout << " ";
		}
		if (key == LEFT) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 37, 10, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> hocKy_int;
			//

			vitri = strlen(nienKhoa_ch);
			gotoxy(46 + vitri, 8);
			goto NIENKHOA;
		}
		if (key == RIGHT || key == ENTER) {
			hocKy_ch[vitri] = '\0';
			if (hocKy_ch[0] == '\0') {
				Alert("Hoc Ky Chua Nhap", 37, 10, 4, 900);
				continue;
			}

			//Convert char to int (Hoc Ky)
			string hocKy_str(hocKy_ch);
			stringstream geek(hocKy_str);
			geek >> hocKy_int;
			//

			vitri = (nhom_int > 9) ? 2 : (nhom_int == 0) ? 0 : 1;
			goto NHOM;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
NHOM:
	//Ghi chu
	SetColor(4);
	SetBGColor(15);
	gotoxy(18, 34);
	cout << "                                                           ";
	gotoxy(18, 35);
	cout << "       NHOM: GOM CAC SO (0-9), TOI DA: 2 KI TU             ";
	gotoxy(18, 36);
	cout << "                                                           ";

	while (true) {
		SetColor(3);
		SetBGColor(7);
		gotoxy(65 + vitri, 8);
		key = GetKey();
		if (key >= '0' && key <= '9' && vitri < 2) {
			if (key == '0' && vitri == 0) {
				Alert("So Nhom Khong Duoc Bat Dau Bang So 0 ", 34, 10, 4, 900);
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
				Alert("Nhom Chua Nhap", 34, 10, 4, 900);
				continue;
			}

			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> nhom_int;
			//

			vitri = (hocKy_int > 9) ? 2 : (hocKy_int == 0) ? 0 : 1;
			gotoxy(58 + vitri, 8);
			goto HOCKY;
		}
		if (key == ENTER) {
			nhom_ch[vitri] = '\0';
			if (nhom_ch[0] == '\0') {
				Alert("Nhom Chua Nhap", 34, 10, 4, 900);
				continue;
			}
			//Convert char to int (Nhom)
			string nhom_str(nhom_ch);
			stringstream geek(nhom_str);
			geek >> nhom_int;
			//
			//Tìm Lớp Tín Chỉ
			DS_DangKy* head = NULL;
			bool flag = false;
			for (int i = 0; i < ds_ltc.soLuong; i++) {
				flag = strcmp(ds_ltc.ds[i]->maMonHoc, maMonHoc_ch) == 0
					&& ds_ltc.ds[i]->nienKhoa == nienKhoa_int
					&& ds_ltc.ds[i]->hocKy == hocKy_int
					&& ds_ltc.ds[i]->nhom == nhom_int;
				if (flag) {
					head = ds_ltc.ds[i]->head;
					break;
				}
			}
			if (head == NULL && flag == true) {
				Alert("Lop Khong Co Sinh Vien Dang Ky!!!", 34, 10, 4, 900);
				continue;
			}
			if (head == NULL && flag == false) {
				Alert("Khong Tim Thay!!!", 34, 10, 4, 900);
				continue;
			}
			char tenMonHoc[40];
			if (choice == "IN") {
				DS_MonHoc* p = CheckTrungMMH(tree, maMonHoc_ch);
				if (p != NULL)
					strcpy_s(tenMonHoc, p->monHoc.tenMonHoc);
				InBangNhapDiem(head, ds_ltc, tenMonHoc, nienKhoa_int, hocKy_int, nhom_int, "IN");
			} else {
				InBangNhapDiem(head, ds_ltc, tenMonHoc, nienKhoa_int, hocKy_int, nhom_int);
			}
			KhungNhapDiem();
			nienKhoa_int = 0;
			hocKy_int = 0;
			nhom_int = 0;
			maMonHoc_ch[0] = '\0';
			nienKhoa_ch[0] = '\0';
			hocKy_ch[0] = '\0';
			nhom_ch[0] = '\0';
			vitri = 0;
			key = 0;
			goto MAMONHOC;
		}
		if (key == ESC) {
			clrscr();
			return;
		}
	}
}

//--------------------------------------------KET THUC BANG DIEM------------------------------------------------

//-------------------------------------------------IN BANG DIEM-------------------------------------------------

//Số sinh viên lớp (vd:d16cqcn02)
int DemSoSinhVien1LopHoc(DS_SinhVien* p) {
	int count = 0;
	char maLop[15];
	strcpy_s(maLop, p->sinhVien.maLop);
	while (p != NULL && strcmp(p->sinhVien.maLop, maLop) == 0) {
		count++;
		p = p->next;
	}
	return count;
}

int IsNumberExistInArray(int arr[], int  number, int arrLength) {
	for (int i = 0; i < arrLength; i++) {
		if (arr[i] == number)
			return 1;
	}
	return 0;
}

int IsStringExistInArray(string arr[], string str, int arrLength) {
	for (int i = 0; i < arrLength; i++) {
		if (arr[i] == str)
			return 1;
	}
	return 0;
}

void InBangDiemTB(char maLop[], int namNhapHoc, int soLuongSV, DS_SinhVien* p, string arrTB[]) {
	KhungTieuDeJ(maLop, namNhapHoc);
	int trang = 0, tongTrang = 0, key;
	tongTrang = (soLuongSV - 1) / 15 + 1;
	DS_SinhVien* point = NULL;
	do {
		KhungPhanTrangDiemTB();
		point = p;
		if (trang != 0) {
			for (int i = 0; i < trang * 15 && i < soLuongSV; i++) {
				point = point->next;
			}
		}
		for (int i = trang * 15; i < 15 + trang * 15 && i < soLuongSV; point = point->next, i++) {
			int index = i - trang * 15;
			SetColor(1);
			gotoxy(17, 15 + index);
			cout << i + 1;
			gotoxy(21, 15 + index);
			cout << point->sinhVien.maSV;
			gotoxy(35, 15 + index);
			cout << point->sinhVien.ho;
			gotoxy(68, 15 + index);
			cout << point->sinhVien.ten;
			gotoxy(79, 31);
			cout << trang + 1 << "/" << tongTrang;

			gotoxy(78, 15 + index);
			if (arrTB[i] == "X") {
				SetColor(4);
				cout << arrTB[i];
			} else {
				SetColor(3);
				cout << arrTB[i];
			}
		}
		key = GetKey();
		if (key == LEFT && trang > 0) {
			trang--;
		}
		if (key == RIGHT && trang < tongTrang - 1) {
			trang++;
		}
		if (key == ESC)
			break;
	} while (true);
	return;
}

void InBangDiemCaoNhat(char maLop[], int namNhapHoc, int soLuongSV, DS_SinhVien* p, float* arrMAX[], string arrMonHocQuyDinh[], int arrMHQDLength) {
	KhungTieuDeK(maLop);
	int trang = 0, tongTrang = 0, key;
	int trangDiem = 0, tongTrangDiem = 0;
	tongTrang = (soLuongSV - 1) / 15 + 1;
	tongTrangDiem = (arrMHQDLength - 1) / 3 + 1;
	DS_SinhVien* point = NULL;
	do {
		KhungPhanTrangDiemMAX();
		point = p;
		if (trang != 0) {
			for (int i = 0; i < trang * 15 && i < soLuongSV; i++) {
				point = point->next;
			}
		}
		for (int i = trang * 15; i < 15 + trang * 15 && i < soLuongSV; point = point->next, i++) {
			int index = i - trang * 15;
			SetColor(1);
			gotoxy(17, 15 + index);
			cout << i + 1;
			gotoxy(21, 15 + index);
			cout << point->sinhVien.maSV;
			gotoxy(35, 15 + index);
			cout << point->sinhVien.ho;
			gotoxy(68, 15 + index);
			cout << point->sinhVien.ten;
			gotoxy(72, 31);
			cout << trang + 1 << "/" << tongTrang;
			gotoxy(105, 31);
			cout << trangDiem + 1 << "/" << tongTrangDiem;
		}
		for (int k = trangDiem * 3; k < 3 + trangDiem * 3 && k < arrMHQDLength; k++) {
			SetColor(2);
			gotoxy(80 + (k - trangDiem * 3) * 10, 13);
			cout << arrMonHocQuyDinh[k];
			for (int j = trang * 15; j < 15 + trang * 15 && j < soLuongSV; j++) {
				gotoxy(80 + (k - trangDiem * 3) * 10, 15 + j - trang * 15);
				if (arrMAX[j][k] == -1) {
					SetColor(4);
					cout << "X";
				} else {
					SetColor(3);
					cout << arrMAX[j][k];
				}
			}
		}
		key = GetKey();
		if (key == LEFT && trang > 0) {
			trang--;
		}
		if (key == RIGHT && trang < tongTrang - 1) {
			trang++;
		}
		if (key == F2 && trangDiem > 0) {
			trangDiem--;
		}
		if (key == F3 && trangDiem < tongTrangDiem - 1) {
			trangDiem++;
		}
		if (key == ESC)
			break;
	} while (true);
	return;
}

//Tìm điểm của tất cả môn của ngành, choice == "TB", choice == "MAX"
void TimKiemDiem(DS_LopTinChi& ds_ltc, DS_SinhVien* p, char maLop[], string choice) {
	//Con trỏ truyền vào hàm InBangDiem
	DS_SinhVien* pIn = p;
	int soLuongMonHocQuyDinh = 4;
	string arrMonHocQuyDinh[4] = {
		"INT1329",
		"INT1330",
		"INT1331",
		"INT1332"
	};
	int tongChi = 0;
	//Tính tổng chỉ, các mã môn phải chắc đúng, vì là lịch trình học của khóa nên chắc chắn đúng
	for (int i = 0; i < soLuongMonHocQuyDinh; i++) {
		char maMonHoc[10];
		strcpy_s(maMonHoc, arrMonHocQuyDinh[i].c_str());
		DS_MonHoc* s = CheckTrungMMH(tree, maMonHoc);
		tongChi += (s->monHoc.soTCLT + s->monHoc.soTCTH);
	}
	int namNhapHoc = p->sinhVien.namNhapHoc;
	int arrNamhoc[4] = { namNhapHoc,namNhapHoc + 1,namNhapHoc + 2,namNhapHoc + 3 };
	int count = 0;
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (IsNumberExistInArray(arrNamhoc, ds_ltc.ds[i]->nienKhoa, sizeof(arrNamhoc) / sizeof(arrNamhoc[0]))
			&& IsStringExistInArray(arrMonHocQuyDinh, ds_ltc.ds[i]->maMonHoc, sizeof(arrMonHocQuyDinh) / sizeof(arrMonHocQuyDinh[0]))) {
			count++;
		}
	}
	//Arr chứa vị trí của các lớp tín chỉ phù hợp vs yêu cầu môn học quy định + năm nhập học (lớp mở sau năm nhập học->sai)
	int* arrLop = new int[count];
	std::fill_n(arrLop, count, -1);
	for (int i = 0; i < ds_ltc.soLuong; i++) {
		if (IsNumberExistInArray(arrNamhoc, ds_ltc.ds[i]->nienKhoa, sizeof(arrNamhoc) / sizeof(arrNamhoc[0]))
			&& IsStringExistInArray(arrMonHocQuyDinh, ds_ltc.ds[i]->maMonHoc, sizeof(arrMonHocQuyDinh) / sizeof(arrMonHocQuyDinh[0]))) {
			for (int k = 0; k < count; k++) {
				if (arrLop[k] == -1) {
					arrLop[k] = i;
					break;
				}
			}
		}
	}
	int soLuongSinhVien = DemSoSinhVien1LopHoc(p);
	float** arrDiem = new float* [soLuongSinhVien];
	for (int i = 0; i < soLuongSinhVien; ++i)
		arrDiem[i] = new float[soLuongMonHocQuyDinh];

	for (int i = 0; i < soLuongSinhVien; i++) {
		for (int k = 0; k < soLuongMonHocQuyDinh; k++) {
			arrDiem[i][k] = -1;
		}
	}

	//float arrDiem[100][4];
	//std::fill((int*)arrDiem, (int*)arrDiem + sizeof(arrDiem) / sizeof(int), -1);
	/*for (int i = 0; i < 100; i++) {
		for (int k = 0; k < 4; k++) {
			arrDiem[i][k] = -1;
		}
	}*/

	int sttSV = 0;
	//DS_SinhVien* p = NULL;
	//char maLop[12] = "D16CQCN02";
	//for (p = first; p != NULL && strcmp(p->sinhVien.maLop, maLop) != 0; p = p->next);
	while (p != NULL && strcmp(p->sinhVien.maLop, maLop) == 0) {
		for (int i = 0; i < soLuongMonHocQuyDinh; i++) {         //Những năm thuộc khóa XXXX
			for (int k = 0; k < count; k++) {
				if (strcmp(ds_ltc.ds[arrLop[k]]->maMonHoc, arrMonHocQuyDinh[i].c_str()) == 0) {
					DS_DangKy* head = ds_ltc.ds[arrLop[k]]->head;
					if (head == NULL)
						break;
					while (head != NULL) {
						if (strcmp(p->sinhVien.maSV, head->dangKy.maSV) == 0) {
							if (arrDiem[sttSV][i] < head->dangKy.diem) {
								arrDiem[sttSV][i] = head->dangKy.diem;
								break;
							}
						}
						head = head->next;
					}
				}
			}
		}
		sttSV++;
		p = p->next;
	}

	if (choice == "MAX")
		//In Bảng Điểm Cao Nhất, đem lên đây vì tính điểm tb * cho A,B,C,D rồi
		InBangDiemCaoNhat(maLop, namNhapHoc, soLuongSinhVien, pIn, arrDiem, arrMonHocQuyDinh, soLuongMonHocQuyDinh); //4 là số lương môn phải học của ngành, vì đứa mảng vào là thành con trỏ nên khó lấy length đc

	//Tính điểm trung bình khóa
	string* tb = new string[soLuongSinhVien];
	for (int i = 0; i < soLuongSinhVien; i++) {
		bool totNghiep = true;
		float diemTB = 0;
		char maMonHoc[10];
		int soChi = 0;
		DS_MonHoc* s = NULL;
		for (int k = 0; k < soLuongMonHocQuyDinh; k++) {
			strcpy_s(maMonHoc, arrMonHocQuyDinh[k].c_str());
			s = CheckTrungMMH(tree, maMonHoc);
			soChi = s->monHoc.soTCLT + s->monHoc.soTCTH;
			if (arrDiem[i][k] >= 8.5) {
				arrDiem[i][k] = soChi * 4;
				diemTB += arrDiem[i][k];
				continue;
			}
			if (arrDiem[i][k] >= 7) {
				arrDiem[i][k] = soChi * 3;
				diemTB += arrDiem[i][k];
				continue;
			}
			if (arrDiem[i][k] >= 5.5) {
				arrDiem[i][k] = soChi * 2;
				diemTB += arrDiem[i][k];
				continue;
			}
			if (arrDiem[i][k] >= 4) {
				arrDiem[i][k] = soChi * 1;
				diemTB += arrDiem[i][k];
				continue;
			}
			if (arrDiem[i][k] >= 0) {
				arrDiem[i][k] = soChi * 0;
				diemTB += arrDiem[i][k];
				continue;
			}
			totNghiep = false;
			break;
		}
		if (totNghiep) {
			//Float to String Stackoverflow
			std::ostringstream ss;
			ss << std::fixed << std::setprecision(2) << (diemTB / tongChi);
			std::string s(ss.str());
			tb[i] = s;
		} else {
			tb[i] = "X";
			totNghiep = true;
		}
	}

	if (choice == "TB")
		//In Bảng Điểm Trung Bình
		InBangDiemTB(maLop, namNhapHoc, soLuongSinhVien, pIn, tb);

	//Xóa các mảng dynamic
	delete[] arrLop;
	//Xóa dynamic 2d array
	for (int i = 0; i < soLuongSinhVien; ++i) {
		delete[] arrDiem[i];
	}
	delete[] arrDiem;
	delete[] tb;
	return;
}

//choice == "TB", choice == "MAX"
void InDiemTBKetThucKhoaHoc(DS_LopTinChi& ds_ltc, string choice) {
	KhungHeader();
	KhungNhapMaLop();

	int key, vitri = 0;
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
	while (true) {
		//Nhap Ma Lop
		SetColor(4);
		SetBGColor(7);
		gotoxy(41 + vitri, 8);
		key = GetKey();

		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key <= '9' && key >= '0')) && (vitri < 14)) {
			maLop[vitri] = toupper((char)key);
			cout << maLop[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0) {
			vitri--;
			gotoxy(41 + vitri, 8);
			cout << " ";
		}
		if (key == ESC) {
			clrscr();
			return;
		}
		if (key == ENTER) {
			maLop[vitri] = '\0';
			if (maLop[0] == '\0') {
				Alert("Chua Nhap Ma Lop!!!", 34, 26, 4, 900);
				continue;
			}

			//Track mã lớp bằng con trỏ p
			DS_SinhVien* p = NULL;
			for (p = first; p != NULL && strcmp(p->sinhVien.maLop, maLop) != 0; p = p->next);
			if (p == NULL) {             //Không có lớp nào có maLop
				Alert("Ma Lop Khong Ton Tai!!!", 34, 26, 4, 900);
				continue;
			}
			if (choice == "TB")
				TimKiemDiem(ds_ltc, p, maLop, "TB");
			if (choice == "MAX")
				TimKiemDiem(ds_ltc, p, maLop, "MAX");
			clrscr();
			KhungHeader();
			KhungNhapMaLop();
			vitri = 0;
			maLop[0] = '\0';
		}
	}
	return;
}



//---------------------------------------------KET THUC IN BANG DIEM--------------------------------------------

char thucdon[6][50] = { "  QUAN LY LOP TIN CHI   ",
						"  QUAN LY SINH VIEN     ",
						"  QUAN LY MON HOC       ",
						"  DANG KY LOP TIN CHI   ",
						"  BANG DIEM             ",
						"  THOAT                 " };
char MenuMoLopTinChi[4][50] = { " TAO LOP TIN CHI MOI    ",
								" CHINH SUA LOP TIN CHI  ",
								" IN DANH SACH DANG KY   ",
								" LUU FILE LOP           " };
char MenuQuanLySinhVien[5][50] = { " THEM SINH VIEN         ",
								   " CHINH SUA SINH VIEN    ",
								   " XOA SINH VIEN          ",
								   " IN DANH SACH SINH VIEN ",
								   " LUU FILE SINH VIEN     " };
char MenuQuanLyMonHoc[5][50] = { " THEM MON HOC           ",
								 " XOA MON HOC            ",
								 " SUA MON HOC            ",
								 " IN DANH SACH MON HOC   ",
								 " LUU DANH SACH MON HOC  " };
char MenuDiem[4][50] = { " NHAP DIEM              ",
						 " IN BANG DIEM CUA LTC   ",
						 " IN DIEM TB KHOA HOC    ",
						 " IN BANG DIEM TONG KET  " };


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
		if (key == ENTER || (key == RIGHT && vitri != 5)) // 6 === THOAT
			return vitri + 1;
		switch (key) {
		case DOWN:
			if (vitri == 5) {
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
				vitri = (6 - 1);
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
		for (int i = 0; i < 6; i++) {
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
			case 4:
				LuuFileLopTinChi(ds_ltc);
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
			for (int i = 0; i < 5; i++) {
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
			choiceMenuCon = MenuCon(5, MenuQuanLyMonHoc);     // item la so chuc nang cua lop con
			SetBGColor(7);
			clrscr();
			switch (choiceMenuCon) {
			case 1:
				ChinhSuaMonHoc("them");
				break;
			case 2:
				XoaMonHoc(ds_ltc);
				break;
			case 3:
				ChinhSuaMonHoc("sua");
				break;
			case 4:
				InDSMH();
				break;
			case 5:
				LuuDSMH();
				break;
			}
			break;
		case 4:
			clrscr();
			DangKyLopTinCHi(ds_ltc);
			break;
		case 5:
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					SetColor(4);
					SetBGColor(14);
				} else {
					SetColor(4);
					SetBGColor(11);
				}
				gotoxy(28, 5 + (i + 1) * 4);	cout << "                        ";
				gotoxy(28, 6 + (i + 1) * 4);	cout << MenuDiem[i];
				gotoxy(28, 7 + (i + 1) * 4);	cout << "                        ";
			}
			choiceMenuCon = MenuCon(4, MenuDiem);     // item la so chuc nang cua lop con
			SetBGColor(7);
			clrscr();
			switch (choiceMenuCon) {
			case 1:
				NhapDiem(ds_ltc);
				break;
			case 2:
				NhapDiem(ds_ltc, "IN");
				break;
			case 3:
				InDiemTBKetThucKhoaHoc(ds_ltc, "TB");
				break;
			case 4:
				InDiemTBKetThucKhoaHoc(ds_ltc, "MAX");
				break;
			}
			break;
		case 6:
			exit(0);
			break;
		}
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


