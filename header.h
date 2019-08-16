#define LOGIN_left  40
#define LOGIN_right 80
#define LOGIN_top   10
#define LOGIN_down  20



#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include "reference.h"

class ThongSo {
public :
    string manHinh;
    string heDieuHanh;
    string cameraTruoc;
    string cameraSau;
    string ram;
    string boNhoTrong;
    string dungLuongPin;
public :
    void display ();
    void changeInfo();
    friend class QuanLiSP;
};

class SanPham {
    string ten;
    string group;
    ThongSo thongSo;
    float gia;
    float danhGia;
    int soLuong;
    int soLuongKM;
    string contentKM;
public :
    friend class QuanLiSP;
    friend class App;
    float tinhTien();
    void display ();
    bool checkExist(string name);
    bool checkPrice (float price);
    void show ();
    void setSL (int _soLuong);
    int getSL ();
    string getName ();
};

class DanhSach {
protected :
    vector<SanPham> listSP;
public :
    void display (int);
    void show (int idx);
    void del (int idx);
    void add (SanPham sanPham);
    int getSL (int idx);
    int getSize ();
    void setSL (int idx, int _soLuong);
};

class GioHang : public DanhSach {
public :
    void chuanHoa ();
    float tinhTien ();
    void clear ();
    string getName(int idx);
};

class QuanLiSP : public DanhSach {
public :
    QuanLiSP ();
    vector<int> findN (string name);
    vector<int> findG (string name);
    vector<int> find (float price);
    vector<int> locSP (float begin, float end);
    void changeInfo (int idx);
    float thongKe ();
    SanPham getSP (int idx);
    int getIndex (string name);
    void write ();
    SanPham& operator [] (int idx);
};

class KhachHang {
    string username;
    string password;
    string name;
    string diaChi;
    string sdt;
    GioHang gioHang;
    vector<SanPham> history;
public :
    friend class QuanLiKH;
    friend class App;
    void showHistory ();
    void display ();
    void show ();
    string getUsername ();
    bool checkExist (string name);
    bool changePassword (string newPass);
    bool checkLogin (string tk, string mk);
};

class QuanLiKH {
    vector<KhachHang> listKH;
public :
    QuanLiKH ();
    void show (int idx);
    void display ();
    void del (int idx);
    vector<int> find (string name);
    int checkForget (string tk, string name, string sdt);
    void changeInfo (int idx);
    void add (KhachHang khachHang);
    void buy (int idx, SanPham sanPham);
    KhachHang& operator [] (int idx);
    int login (string tk, string mk);
    int size ();
    void write ();
    
    // ~QuanLiKH ();
};

class App {
    QuanLiKH* listKhachHang;
    QuanLiSP* listSanPham;
    int khach;
    bool isAdmin;
    string admin_user;
    string admin_password;
public :
    App ();
    void displayProduct ();
    void showProduct (int idx);
    void buy (int idx);
    void gioHang ();
    void thanhToan ();
    int login ();
    int forgetPassword ();
    bool regist ();
    void adminWithSP ();
    void adminWithKH ();
    void operate ();
    void muaHang ();
    void find ();
    void cart ();
    void showMenu();
    void find_adP();
    void find_adG();
    ~App ();
};