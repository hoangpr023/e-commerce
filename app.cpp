#include "header.h"

// App 
App::App () {
    string temp, name, temp1;
    this->listKhachHang = new QuanLiKH();
    this->listSanPham = new QuanLiSP();
    int soLuongSP, soLuong;
    this->khach = -1;
    this->isAdmin = false;
    this->admin_user = "account";
    this->admin_password = "password";    
    ifstream file("lichsu.txt");
    for (int i = 0; i < this->listKhachHang->size(); i ++) {
        getline(file, temp);
        getline(file, temp);     soLuongSP = stoi(temp);
        for (int j = 0; j < soLuongSP; j ++) {
            getline(file, name);
            getline(file, temp1);        soLuong = stoi(temp1);
            for (int p = 0; p < this->listSanPham->getSize(); p ++) 
                if (name == (*listSanPham)[p].getName()) {
                    SanPham x = (*listSanPham)[p];
                    x.soLuong = soLuong;
                    (*this->listKhachHang)[i].history.push_back(x);
                }
            
        }
        getline(file, temp);
    }
    file.close();
    // (*(this->listKhachHang))[1].showHistory();
    // Sleep (55000);
}
void App::displayProduct () {
    Reference::clrscr ();
    this->listSanPham->display (1);
}
void App::showProduct (int idx) {
    this->listSanPham->show (idx);
}
void App::buy (int idx) {
    Back :
    Reference::clrscr ();
    this->displayProduct ();
    cout << "Type the number of product which you want to buy: ";
    int soLuong;
    cin >> soLuong;     cin.ignore ();
    SanPham sanPham = this->listSanPham->getSP (idx);
    if (sanPham.soLuong < soLuong) {
        cout << "We don't have enought product\n";
        cout << "Please type again";
        Sleep (2000);
        goto Back;
    } else sanPham.soLuong = soLuong;
    this->listSanPham->setSL (idx, this->listSanPham->getSL (idx) - sanPham.soLuong);
    this->listKhachHang->buy (this->khach, sanPham);
    cout << "Your require successed!\n";
    Sleep (2000);
}
void App::gioHang () {
    _start :
    int idx = this->khach;
    Reference::clrscr ();
    (*this->listKhachHang)[idx].gioHang.display (2);
    cout << "\n";
    cout << "Type the position of product which you want to change information: ";
    int pos;
    cin >> pos;     cin.ignore ();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _start;
    }
    if (pos > (*this->listKhachHang)[idx].gioHang.getSize() || pos < 0) {
        cout << "Wrong input";
        Sleep (2000);
        goto _start;
    }
    pos --;
    cout << "Type the number of product which you want to buy: ";
    int number;
    int vtri = (*(this->listSanPham)).getIndex((*(this->listKhachHang))[idx].gioHang.getName(pos));
    cin >> number;  cin.ignore ();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _start;
    }
    if (number > (*(this->listSanPham))[vtri].getSL() + (*(this->listKhachHang))[idx].gioHang.getSL(pos) || number < 0) {          // bug
        cout << "Wrong input";
        Sleep (2000);
        goto _start;
    }
    (*this->listKhachHang)[idx].gioHang.setSL (pos, number);
    if (number == 0) (*this->listKhachHang)[idx].gioHang.del (pos);
    cout << "Your require successed!\n";
}
void App::thanhToan () {
    string temp;
    string address;
    int idx= this->khach;
    Reference::clrscr ();
    cout << "User: " << (*this->listKhachHang)[this->khach].name << "\n";
    cout << "Here is your bill: \n";
    (*this->listKhachHang)[idx].gioHang.display (2);
    cout << "Total: " << (*this->listKhachHang)[idx].gioHang.tinhTien () << " $\n";
    (*this->listKhachHang)[this->khach].gioHang.clear ();
    cout << "\nDo you want to be delivered to the old address: ";
    getline (cin, temp);
    if (temp == "no") {
        cout << "Type new address: ";
        getline(cin, address);
    }
    cout << "\n\nSee you again\n";
    this->listSanPham->write ();
    Sleep (4000);
}
int App::login () {
    int idx;
    string account, password;
    Reference::clrscr ();
    Reference::draw (LOGIN_left, LOGIN_right, LOGIN_top, LOGIN_down);
    Reference::gotoXY (45, 14);
    cout << "Account:   ";
    getline (cin, account);    
    Reference::gotoXY (45, 16);
    cout << "Passsword: ";
    getline (cin,  password);
    idx = this->listKhachHang->login (account, password);
    Reference::gotoXY (45, 22);
    if (idx == -2) {
        if (account == this->admin_user && password == this->admin_password) {
            this->isAdmin = true;
            cout << "Login by admin :)";
            Sleep (2000);
            return -1;
        } else {
            cout << "Not true =))";
            Sleep (2000);
            return -2;
        }
    }
    else {
        this->khach = idx; 
        cout << "Hello " << (*this->listKhachHang)[idx].name << " :b\n";
        return idx;
    }
}

int App::forgetPassword () {
    string name, sdt, username;
    B :
    Reference::clrscr ();
    cout << "Type your name:        ";
    getline (cin, name);        
    cout << "Type your username:    ";
    getline (cin, username);     
    cout << "Type your tel:         ";
    getline (cin, sdt);        
    int idx = this->listKhachHang->checkForget (username, name, sdt);
    if (idx == -1) {
        cout << "Your information which was typed is not true!";
        Sleep (2000);
        goto B;
    } else {
        string pass1, pass2;
        A : 
        Reference::clrscr ();
        cout << "Type new password:     ";
        getline (cin, pass1);
        cout << "Confirm your password: ";
        getline (cin, pass2);      
        if (pass1 != pass2) {
            cout << "password not true";
            Sleep (2000);
            goto A;
        } else {
            (*this->listKhachHang)[idx].changePassword (pass1);
            cout << "Compeleted!";
            Sleep (2000);
        }
        
    }
    this->khach = idx;
    this->listKhachHang->write();
    return idx;

}

bool App::regist () {
    KhachHang x;
    Reference::clrscr ();
    cout << "Your name:         ";
    getline (cin, x.name);     
    cout << "Your username:     ";
    getline (cin, x.username); 
    cout << "Your password:     ";
    getline (cin, x.password); 
    cout << "Your address:      ";
    getline (cin, x.diaChi);   
    cout << "Your telephone:    ";
    getline (cin, x.sdt);       
    int idx = -1;
    for (int i = 0; i < this->listKhachHang->size (); i ++)
        if ((*this->listKhachHang)[i].getUsername () == x.username )  idx = i;
    if (idx != -1) {
        cout << "Username has been existed.\n";
        cout << "Please choose another name.";
        Sleep (2000);
        return false;
    } else {
        cout << "Successfull!";
        Sleep (2000);
        this->listKhachHang->add (x);
        this->khach = this->listKhachHang->size () - 1;
        return true;
    }
}
void App::adminWithKH () {
    string name;
    _menu : 
    Reference::clrscr ();
    Reference::gotoXY (50, 5);
    cout << "INTERFACE FOR ADMIN";
    int left = 35, right = 85, top = 9, down = 22;
    Reference::draw (left, right, top, down);
    Reference::gotoXY (40, 13);
    cout << "1. Show all guests";
    Reference::gotoXY (40, 16);
    cout << "2. Add guest";
    Reference::gotoXY (65, 13);
    cout << "3. Return back";
    Reference::gotoXY (65, 16);
    cout << "Choice: ";
    int choice;
    cin >> choice;      cin.ignore ();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _menu;
    }
    if (choice > 3 || choice < 1) {
        cout << "Wrong input";
        Sleep(2000);
        goto _menu;
    }
    Reference::clrscr ();
    switch (choice) {
        case 1 : {
        _case1 :
            Reference::clrscr();
            this->listKhachHang->display ();
            cout << "\n";
            cout << "1. FIND GUEST \n";
            cout << "2. DELETE GUEST\n";
            cout << "3. CHANGE INFORMATION OF GUEST\n";
            cout << "4. WATCH PROFILE\n";
            cout << "5. RETURN BACK\n";
            cout << "Choice: ";
            int choice;
            cin >> choice;      cin.ignore(); 
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                goto _case1;
            }
            if (choice > 5 || choice < 1) {
                cout << "Wrong input";
                Sleep(2000);
                goto _case1;
            }  
            switch (choice) {
                case 1 :
                    this->find_adG();
                    goto _case1;
                case 2 : {
                    int pos;
                    string temp;
                    _case1_2 :
                    Reference::clrscr();
                    this->listKhachHang->display();
                    cout << "Type position of guest: ";
                    cin >> pos;     cin.ignore();
                    pos --;
                    if (pos < 0 || pos >= this->listKhachHang->size()) {
                        cout << "We don't have this guest";
                        Sleep (2000);
                        goto _case1;
                    }
                    cout << "Are you sure: ";
                    getline(cin, temp);
                    if (temp == "yes") {
                        this->listKhachHang->del(pos);
                        this->listKhachHang->write();
                        cout << "Successfull!";
                        Sleep (2000);
                    
                    }
                    goto _case1;
                    break;
                }
                case 3 : {
                    int choice;
                _case1_3 :
                    Reference::clrscr();
                    this->listKhachHang->display();
                    cout << "1. CHANGE NAME\n";
                    cout << "2. CHANGE ADDRESS\n";
                    cout << "3. CHANGE TELEPHONE NUMBER\n";
                    cout << "4. CHANGE PASSWORD\n";
                    cout << "5. RETURN BACK\n";
                    cout << "Choice: ";
                    cin >> choice;      cin.ignore();
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        goto _case1_3;
                    }
                    if (choice < 1 || choice > 5) {
                        cout << "Wrong input";
                        Sleep(2000);
                        goto _case1_3;
                    }
                    switch (choice) {
                        case 1 : {
                            int pos;
                        _case1_3_1 :
                            Reference::clrscr();
                            this->listKhachHang->display();
                            cout << "Type position of guest: ";
                            cin >> pos;     cin.ignore();
                            pos --;
                            if (pos < 0 || pos >= this->listKhachHang->size()) {
                                cout << "We don't have this guest";
                                Sleep (2000);
                                goto _case1_3_1;
                            }
                            Reference::clrscr();
                            (*this->listKhachHang)[pos].show();
                            cout << "New name: ";
                            getline(cin, (*this->listKhachHang)[pos].name);
                            this->listKhachHang->write();
                            cout << "Successfull!";
                            Sleep (2000);
                            goto _case1_3;
                            break;
                        }
                        case 2 : {
                            int pos;
                        _case1_3_2 :
                            Reference::clrscr();
                            this->listKhachHang->display();
                            cout << "Type position of guest: ";
                            cin >> pos;     cin.ignore();
                            pos --;
                            if (pos < 0 || pos >= this->listKhachHang->size()) {
                                cout << "We don't have this guest";
                                Sleep (2000);
                                goto _case1_3_2;
                            }
                            Reference::clrscr();
                            (*this->listKhachHang)[pos].show();
                            cout << "New address: ";
                            getline(cin, (*this->listKhachHang)[pos].diaChi);
                            this->listKhachHang->write();
                            cout << "Successfull!";
                            Sleep (2000);
                            goto _case1_3;
                            break;
                        }
                        case 3 : {
                            int pos;
                        _case1_3_3 :
                            Reference::clrscr();
                            this->listKhachHang->display();
                            cout << "Type position of guest: ";
                            cin >> pos;     cin.ignore();
                            pos --;
                            if (pos < 0 || pos >= this->listKhachHang->size()) {
                                cout << "We don't have this guest";
                                Sleep (2000);
                                goto _case1_3_3;
                            }
                            Reference::clrscr();
                            (*this->listKhachHang)[pos].show();
                            cout << "New telephone number: ";
                            getline(cin, (*this->listKhachHang)[pos].sdt);
                            this->listKhachHang->write();
                            cout << "Successfull!";
                            Sleep (2000);
                            goto _case1_3;
                            break;
                        }
                        case 4 : {
                            int pos;
                        _case1_3_4 :
                            Reference::clrscr();
                            this->listKhachHang->display();
                            cout << "Type position of guest: ";
                            cin >> pos;     cin.ignore();
                            pos --;
                            if (pos < 0 || pos >= this->listKhachHang->size()) {
                                cout << "We don't have this guest";
                                Sleep (2000);
                                goto _case1_3_4;
                            }
                            Reference::clrscr();
                            (*this->listKhachHang)[pos].show();
                            cout << "New name: ";
                            getline(cin, (*this->listKhachHang)[pos].password);
                            this->listKhachHang->write();
                            cout << "Successfull!";
                            Sleep (2000);
                            goto _case1_3;
                            break;
                        }
                        case 5 : goto _case1;
                    }
                }
                case 4 : {
                    int pos;
                    int choice;
                _case1_4 :
                    Reference::clrscr();
                    this->listKhachHang->display();
                    cout << "Type position of guest: ";
                    cin >> pos;     cin.ignore();
                    pos --;
                    if (pos < 0 || pos >= this->listKhachHang->size()) {
                        cout << "We don't have this guest";
                        Sleep (2000);
                        goto _case1_4;
                    }   
                    _turnBack :
                    Reference::clrscr();
                    this->listKhachHang->show(pos);
                    cout << "1. RETURN BACK\n";
                    cout << "Choice: ";
                    cin >> choice;      cin.ignore();
                    if (choice != 1) {
                        cout << "Wrong input";
                        Sleep(2000);
                        goto _turnBack;
                    }
                    goto _case1;
                    break;
                }
                case 5 : goto _menu;

            }
            break;
        }
            
        case 2 : {
            bool check = this->regist ();
            while (check == false) check = this->regist ();
            this->listKhachHang->write();
            break;
        }
            
        case 3 : break;
            

    }
}
void App::adminWithSP () {
    int choice_1;
    _start :
    Reference::clrscr();
    cout << "1. SHOW PRODUCTS\n";
    cout << "2. ADD NEW PRODUCT\n";
    cout << "3. RETURN MENU\n";
    cout << "Choice: ";

    cin >> choice_1;        cin.ignore();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _start;
    }
    if (choice_1 < 1 || choice_1 > 3) {
        cout << "Wrong input";
        Sleep (2000);
        goto _start;
    }
    switch (choice_1) {
        case 1 : {
        _case_1 :
            Reference::clrscr();
            this->listSanPham->display(2);
            cout << "\n\n";
            cout << "1. FIND PRODUCTS\n";
            cout << "2. DELETE PRODUCTS\n";
            cout << "3. CHANGE INFORMATION OF PRODUCT\n";
            cout << "4. RETURN BACK\n";
            cout << "Choice: ";
            int choice;
            cin >> choice;      cin.ignore();
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                goto _case_1;
            }
            if (choice > 4 || choice < 1) {
                cout << "Wrong input";
                Sleep (2000);
                goto _case_1;
            }
            switch (choice) {
                case 1 : 
                    this->find_adP();
                    goto _case_1;
                    break;
                case 2 : {
                    int pos;
                    string temp;
                _case_2 :
                    Reference::clrscr();
                    this->listSanPham->display(2);
                    cout << "Type position of product: ";
                    cin >> pos;         cin.ignore();
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        goto _case_2;
                    }
                    if (pos < 0 || pos > this->listSanPham->getSize()) {
                        cout << "Please type position displayed!";
                        Sleep(2000);
                        goto _case_2;
                    }
                    pos -- ;
                    cout << "ARE YOU SURE: ";
                    getline(cin, temp);
                    if (temp == "yes") {
                        this->listSanPham->del(pos);
                        cout << "Successfull!";
                        this->listSanPham->write();
                    }
                    goto _case_1; 
                    break;                                      
                }
                case 3 : {
                    int pos, choice;
                _case_3 : 
                    Reference::clrscr();
                    this->listSanPham->display(2);
                    cout << "\n";
                    cout << "Type position of product: ";
                    cin >> pos;     cin.ignore();
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        goto _case_3;
                    }
                    if (pos < 0 || pos > this->listSanPham->getSize()) {
                        cout << "Please type position displayed!";
                        Sleep(2000);
                        goto _case_3;
                    }
                    pos -- ;
                    G1 :
                    Reference::clrscr();
                    this->listSanPham->show(pos);
                    cout << "\n";
                    cout << "1. CHANGE NAME\n";
                    cout << "2. CHANGE SPECIFICATIONS\n";
                    cout << "3. CHANGE PRICE\n";
                    cout << "4. CHANGE GROUP\n";
                    cout << "5. RETURN BACK\n";
                    cout << "Choice: ";
                    cin >> choice;      cin.ignore();
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        goto G1;
                    }
                    if (choice > 5 || choice < 1) {
                        cout << "Wrong input";  Sleep (2000);
                        goto G1;
                    }
                    switch (choice) {
                        case 1 : {
                            cout << "Type new name: ";
                            getline(cin, (*this->listSanPham)[pos].ten);
                            cout << "Successfull!";
                            Sleep(2000);
                            this->listSanPham->write();
                            goto G1;
                            break;
                        } 
                        case 2 : 
                            Reference::clrscr();
                            (*this->listSanPham)[pos].thongSo.changeInfo();
                            cout << "Successfull!";
                            Sleep(2000);
                            this->listSanPham->write();
                            goto G1;
                        case 3 :         
                            cout << "Type new price: ";
                            cin >> (*this->listSanPham)[pos].gia;      cin.ignore();
                            cout << "Successfull!";
                            Sleep(2000);
                            this->listSanPham->write();
                            goto G1;
                            break; 
                        case 4 :
                            cout << "Type new group: ";
                            getline(cin, (*this->listSanPham)[pos].group);
                            cout << "Successfull!";
                            Sleep(2000);
                            this->listSanPham->write();
                            goto G1;
                            break;     
                        case 5 :
                            goto _case_1;
                            break ;  
                    }
                    
                }
                case 4 : goto _start;

                
            }
        }
        case 2 : {
            SanPham x;
            Reference::clrscr();
            cout << "1. New name: ";    getline(cin, x.ten);
            x.thongSo.changeInfo();
            cout << "3. New price: ";   cin >> x.gia;       cin.ignore();
            cout << "4. New group: ";   getline(cin, x.group);
            cout << "Successfull!";
            Sleep (2000);
            x.setSL(50);
            x.soLuongKM = 0;
            x.contentKM = "None";
            this->listSanPham->add(x);
            this->listSanPham->write();
            goto _start;
            break;
        }
        case 3 : break;
    }
}
void App::operate () {
    Start :
    string temp;
    bool continous = true;
    int ans = 0;
    bool p = false;
    Reference::clrscr ();
    Reference::gotoXY (50, 8);     cout << "WELCOME TO HOANG'S STORE";
    Reference::draw (43, 78, 12, 20);
    Reference::gotoXY (48, 15);     cout << "1. Login";
    Reference::gotoXY (65, 15);     cout << "2. Regist";
    Reference::gotoXY (48, 17);     cout << "3. Exit";
    Reference::gotoXY (65, 17);     cout << "Choice: ";
    cin >> ans;     cin.ignore ();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto Start;
    }
    if (ans > 3 || ans < 1) {
        Reference::gotoXY(50, 22);
        cout << "Wrong input";  Sleep (2000);
        goto Start;
    }
    if (ans == 3) return;
    if (ans == 2) {
        while (! p) p = this->regist ();
    } else {
        
        string x;
        int idx = -2;
        int count = 0;
        while (idx == -2) {
            if (count == 3) {
                Reference::clrscr ();
                cout << "Do you forget your password: ";
                getline (cin, x);
                if (x == "yes") {
                    this->forgetPassword ();
                    idx = this->khach;
                }
            } else idx = this->login ();
            count ++;
        }
    } 
    
    Sleep (2000);
    string command;
    while (continous) {
        Reference::clrscr ();
        if (this->isAdmin == true) {
            Reference::draw (40, 85, 13, 23);
            Reference::gotoXY (44, 15); cout << "1. Handle product";
            Reference::gotoXY (66, 15); cout << "2. Handle guest";
            Reference::gotoXY (44, 18); cout << "4. Log out";
            Reference::gotoXY (66, 18); cout << "3. Revenues";
            Reference::gotoXY (58, 21); cout << "Choice: ";
            int choice = 0;
            cin >> choice;          cin.ignore ();
            if (cin.fail()) {
                Reference::clrscr();
                cin.clear();
                cin.ignore();
                continue;
            }
            if (choice < 1 || choice > 4) {
                Reference::clrscr ();
                cout << "Wrong input !\n";
                cout << "Please type again";
                Sleep (2000);
                continue;
            }
            switch (choice) {
                case 1 :
                    this->adminWithSP ();
                    break;
                case 2 :
                    this->adminWithKH ();
                    break;
                case 4 :
                    goto Start;
                case 3 : {
                    _case_3_dayNe :
                    Reference::clrscr();
                    cout << "       BANG DOANH THU\n\n";
                    this->listSanPham->thongKe();
                    cout << "\n\n1. RETURN BACK\n";
                    cout << "Choice: ";
                    int choice = 0;
                    cin >> choice;      cin.ignore();
                    if (cin.fail()) {
                        cin.clear();      
                        cin.ignore();
                        goto _case_3_dayNe;
                    }
                    if (choice != 1) {
                        cout << "Wrong input";
                        Sleep (2000);
                        goto _case_3_dayNe;
                    }
                    continue;
                    break;
                }
            }
        } else {
            Option :
            this->showMenu ();
            int choice;
            cin >> choice;      cin.ignore ();
            if (cin.fail ()) {
                cin.clear ();
                cin.ignore();
                goto Option;
            }
            if (choice < 1 || choice > 7) {
                Reference::clrscr ();
                cout << "Wrong input !\n";
                cout << "Please type again";
                Sleep (2000);
                continue;
            }
            // Choice_input :
            Reference::clrscr ();
            switch (choice) {
                case 1 : {
                    case_1 :
                    this->displayProduct ();
                    cout << "\n\n";
                    cout << "1. BUY PRODUCT\n";
                    cout << "2. RETURN BACK\n";
                    cout << "Choice: ";
                    int chon;
                    cin >> chon;        cin.ignore ();
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        goto case_1;
                    }
                    if (chon != 1 && chon != 2) {
                        cout << "Wrong input";
                        Sleep (2000);
                        goto case_1;
                    } 
                    if (chon == 1) this->muaHang ();
                    break;                    
                }
                case 2 : {
                    // cout << "User: " << (*this->listKhachHang)[this->khach].name << "\n";
                    // if (this->khach == -1)  this->anonymous.gioHang.display (2);
                    // else (*this->listKhachHang)[this->khach].gioHang.display (2);

                    // cout << "\n\n";
                    // cout << "Do you want to change number of product: ";
                    // getline (cin, temp);      
                    // if (temp == "yes") this->gioHang ();
                    // cout << "\n" << "Would you like to pay now: ";
                    // getline (cin, temp);   
                    // if (temp == "yes") this->thanhToan ();
                    this->cart ();
                    break;
                }
                    
                case 3 :
                    this->thanhToan ();
                    break;
                case 4 : {
                    this->find ();
                    break;
                }
                // case 5 : {
                //     Case_5 : 
                //     Reference::clrscr ();
                //     int vtri = -1;
                //     string temp;
                //     this->listSanPham->display (1);
                //     cout << "Type position of product: ";
                //     cin >> vtri;        cin.ignore ();
                //     if (vtri < 1 || vtri > this->listSanPham->getSize ()) {
                //         Reference::clrscr ();
                //         cout << "Wrong input\n";
                //         cout << "Please type again";
                //         Sleep (2000);
                //         goto Case_5;
                //     } else vtri --;
                //     Reference::clrscr ();
                //     this->listSanPham->show (vtri);
                //     Sleep (2000);
                //     cout << "\n\n";
                //     cout << "Do you want to buy it: ";
                //     getline (cin, temp);   
                //     if (temp == "yes") this->buy (vtri);
                //     cout << "Would you like to pay now: ";
                //     getline (cin, temp);       
                //     if (temp == "yes") this->thanhToan ();
                //     break;

                // }  
                case 5 :{
                    case_5 :
                    Reference::clrscr ();
                    string newPass1, newpass2;
                    Reference::draw (40, 80, 12, 18);
                    Reference::gotoXY (53, 9);  cout << "CHANGE PASSWORD";
                    Reference::gotoXY (43, 14); cout << "New password:  ";
                    getline (cin, newPass1); 
                    Reference::gotoXY (43, 16); cout << "Confirm:       ";
                    getline (cin, newpass2);       
                    if (newPass1 != newpass2) {
                        Reference::gotoXY (55, 21);
                        cout << "Wrong";
                        Sleep (2000);
                        goto case_5;
                    } else {
                        Reference::gotoXY (55, 21);
                        cout << "Successfull\n";
                        (*this->listKhachHang)[this->khach].changePassword (newPass1);
                        Sleep (2000);
                    }
                    this->listKhachHang->write ();
                    break;
                } 
                case 6 : {
                    Reference::clrscr ();
                    Reference::gotoXY (50, 14);
                    cout << "THANKS FOR USING :)";
                    Sleep (2000);
                    goto Start;
                    break;
                }      
                case 7 :
                    continous = false;
                    break;    

            }       
        
        }

    }
}

// void App::logout () {
    
// }
// void App::find (SanPham sanPham) {
//     Reference::clrscr ();
//     string name;
//     cout << "Type the name or group of product: ";
//     getline (cin, name);
//     this->listSanPham->find (name);
// }

// App::~App () {
//     ofstream file ("product.txt");
//     for (int i = 0; i < this->listSanPham->getSize (); i ++) {
//         file << this->listSanPham->
//     }
//     file.close ();
// }

void App::muaHang () {
    string mua;
    Choice_input :
    this->displayProduct ();
    cout << "Type the pos of product: ";
    int pos;
    cin >> pos;     cin.ignore ();
    if (cin.fail()) {
        Reference::clrscr();
        cin.clear();
        cin.ignore();
        goto Choice_input;
    }
    if (pos < 1 || pos > this->listSanPham->getSize ()) {
        Reference::clrscr ();
        cout << "Wrong input !\n";
        cout << "Please type again";
        Sleep (2000);
        goto Choice_input; 
    } else pos --;
    cout << "Type the number of product which you want to buy: ";
    int soLuong;
    cin >> soLuong;     cin.ignore ();
    SanPham sanPham = this->listSanPham->getSP (pos);
    if (sanPham.soLuong < soLuong) {
        cout << "We don't have enought product\n";
        cout << "Please type again";
        Sleep (2000);
        goto Choice_input;
    } else sanPham.soLuong = soLuong;
    this->listSanPham->setSL (pos, this->listSanPham->getSL (pos) - sanPham.soLuong);
    this->listKhachHang->buy (this->khach, sanPham);
    cout << "Your require successed!\n";
    Sleep (2000);
    
    cout << "Do you want to buy more: ";
    getline (cin, mua);
    if (mua == "yes") goto Choice_input;

}
void App::find () {
    _find :
    vector<int> list;
    int choice_1, choice_2;
    string name;
    string temp;
    float cost;
    float from, to;
    Reference::clrscr();
    cout << "1. FIND BY NAME\n";
    cout << "2. FIND BY GROUP\n";
    cout << "3. FIND BY COST\n";
    cout << "4. FIND BY RANGE OF COST\n";
    cout << "5. RETURN BACK\n";
    cout << "Choice: ";
    cin >> choice_1;      cin.ignore();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _find;
    }
    if (choice_1 > 5 || choice_1 < 1) {
        cout << "Wrong input";
        Sleep (2000);
        goto _find;
    }

    switch (choice_1) {
        case 1 :
            
            cout << "Type name: ";
            getline (cin, name);
            _case1_1 :
            list = this->listSanPham->findN (name);
            break;
        case 2 :
            
            cout << "Type group: ";
            getline (cin, name);
            _case2_1 :
            list = this->listSanPham->findG(name);
            break;
        case 3 :
            
            cout << "Type cost: ";
            cin >> cost;        cin.ignore();
            _case3_1 :
            list = this->listSanPham->find(cost);
            break;
        case 4 :
            
            cout << "From:  ";
            cin >> from;        cin.ignore();
            cout << "To:    ";
            cin >> to;          cin.ignore();
            _case4_1 :
            list = this->listSanPham->locSP(from, to);
            break;
        case 5 :
            return;
    }
    Again :
    if (list.size() == 0) {
        cout << "1. RETURN BACK\n";
        cout << "Choice: ";
        int input = 0;
        cin >> input;       cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            goto Again;
        }
        if (input != 1) {
            cout << "Wrong input";
            Sleep (2000);
            Reference::gotoXY(0, Reference::whereY() - 1);
            cout << "                                       \n";
            cout << "                                        ";
            Reference::gotoXY (0, Reference::whereY() - 2);
            goto Again;

        }
        goto _find;
    }
    cout << "1.BUY PRODUCT\n";
    cout << "2.SHOW DETAIL ABOUT PRODUCT\n";
    cout << "3.RETURN BACK\n";
    cout << "Choice: ";
    cin >> choice_2;      cin.ignore();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto Again;
    }
    if (choice_2 > 3 || choice_2 < 1) {
        cout << "Wrong input";
        Sleep (2000);
        Reference::gotoXY(0, Reference::whereY() - 1);
        cout << "                                       \n";
        cout << "                                        ";
        Reference::gotoXY (0, Reference::whereY() - 4);
        goto Again;
    }
    switch (choice_2) {
        case 1 : {
            int pos;
            bool check = false;
        _case1_2 :            
            check = false;
            Reference::clrscr();
            for (int i = 0; i < list.size(); i ++) {
                cout << "***********************************************\n";
                cout << list[i] + 1 << ". ";
                (*this->listSanPham)[list[i]].display ();
                cout << "\n";
            }

            cout << "\nType position of product: ";
            cin >> pos;     cin.ignore();
            pos --;
            for (int i = 0; i < list.size(); i ++)
                if (pos == list[i]) check = true;
            if (! check) {
                cout << "\nPlease type the position displayed";
                Sleep (2000);
                goto _case1_2;
            } 
            cout << "Type the number of product which you want to buy: ";
            int soLuong;
            cin >> soLuong;     cin.ignore ();
            SanPham sanPham = this->listSanPham->getSP (pos);
            if (sanPham.soLuong < soLuong) {
                cout << "We don't have enought product\n";
                cout << "Please type again";
                Sleep (2000);
                goto _case1_2;
            } else sanPham.soLuong = soLuong;
            this->listSanPham->setSL (pos, this->listSanPham->getSL (pos) - sanPham.soLuong);
            this->listKhachHang->buy (this->khach, sanPham);
            cout << "Your require successed!\n";
            Sleep (2000);
    
            cout << "Do you want to buy more: ";
            string mua;
            getline (cin, mua);
            if (mua == "yes") goto _case1_2;
            else goto _find;
            break;
        }
        case 2 : {
            int pos;
            bool check = false;
        _case2_2 :
            check = false;
            Reference::clrscr();
            for (int i = 0; i < list.size(); i ++) {
                cout << "***********************************************\n";
                cout << list[i] + 1 << ". ";
                (*this->listSanPham)[list[i]].display ();
                cout << "\n";
            }

            cout << "\nType position of product: ";
            cin >> pos;     cin.ignore();
            pos --;
            for (int i = 0; i < list.size(); i ++)
                if (pos == list[i]) check = true;
            if (! check) {
                cout << "\nPlease type the position displayed";
                Sleep (2000);
                goto _case2_2;
            }
            Reference::clrscr();
            this->listSanPham->show(pos);
            cout << "\n";
            cout << "1. BUY IT\n";
            cout << "2. RETURN BACK\n";
            cout << "Choice: ";
            int chon;
            cin >> chon;        cin.ignore();
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                goto _case2_2;
            }
            if (chon > 2 || chon < 1) {
                cout << "Wrong input";
                Sleep(2000);
                goto _case2_2;
            }
            switch (chon) {
                case 1 : {
                    Reference::clrscr();
                    this->listSanPham->show(pos);
                    cout << "Type the number of product which you want to buy: ";
                    int soLuong;
                    cin >> soLuong;     cin.ignore ();
                    SanPham sanPham = this->listSanPham->getSP (pos);
                    if (sanPham.soLuong < soLuong) {
                        cout << "We don't have enought product\n";
                        cout << "Please type again";
                        Sleep (2000);
                        goto _case2_2;
                    } else sanPham.soLuong = soLuong;
                    this->listSanPham->setSL (pos, this->listSanPham->getSL (pos) - sanPham.soLuong);
                    this->listKhachHang->buy (this->khach, sanPham);
                    cout << "Your require successed!\n";
                    Sleep (2000);

                    cout << "Do you want to buy more: ";
                    string mua;
                    getline (cin, mua);
                    if (mua == "yes") goto _case2_2;
                    else goto _find;
                }
                case 2 : 
                    switch (choice_1) {
                        case 1 :
                            goto _case1_1;
                        case 2 :
                            goto _case2_1;
                        case 3 :
                            goto _case3_1;
                        case 4 :
                            goto _case4_1;
                    }
            }
        }
        case 3 :
            goto _find;
    }
}
void App::cart () {
    _cart :
    Reference::clrscr ();
    int choice;
    cout << "User: " << (*this->listKhachHang)[this->khach].name << "\n";
    (*this->listKhachHang)[this->khach].gioHang.display (2);

    cout << "\n\n";
    cout << "1. CHANGE NUMBER OF PRODUCT\n";
    cout << "2. DELETE PRODUCT\n";
    cout << "3. PAY FOR THE BILL\n";
    cout << "4. RETURN MENU\n";
    cout << "\n\n";
    cout << "Choice: ";
    cin >> choice;      cin.ignore ();   
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _cart;
    }
    if (choice > 4 || choice < 1) {
        cout << "\nWrong input";
        Sleep (2000);
        goto _cart;
    }
    switch (choice) {
        case 1 :
            this->gioHang ();
            goto _cart;     
            break;
        case 2 : {
            case_2 :
            Reference::clrscr ();
            int pos;
            cout << "User: " << (*this->listKhachHang)[this->khach].name << "\n";
            (*this->listKhachHang)[this->khach].gioHang.display (2);
            cout << "\n\n";
            cout << "Type position of product which you want to delete: ";
            cin >> pos;     cin.ignore();
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                goto case_2;
            }
            if (pos < 1 || pos > (*this->listKhachHang)[this->khach].gioHang.getSize()) {
                cout << "Error!";
                Sleep (2000);
                goto case_2;
            } 
            pos --;
            (*this->listKhachHang)[this->khach].gioHang.del (pos);
            cout << "Successfull !";
            Sleep(2000);
            goto _cart;
            break;
            
        }

        case 3 :
            this->thanhToan ();
            break;
        case 4 :
            break;  
    }
}
void App::showMenu () {
    Reference::gotoXY (55, 6);
    cout << "MENU";
    Reference::gotoXY (40, 10);     cout << "1. Show product\n";
    Reference::gotoXY (70, 10);     cout << "2. Go to your cart\n";
    Reference::gotoXY (40, 12);     cout << "3. Pay for your bill\n";  
    Reference::gotoXY (70, 12);     cout << "4. Find product\n";
    Reference::gotoXY (40, 14);     cout << "5. Change password\n";
    Reference::gotoXY (70, 14);     cout << "6. Logout\n";
    Reference::gotoXY (40, 16);     cout << "7. Exit\n";
    Reference::gotoXY (70, 16);     cout << "Choice: ";
}
void App::find_adP() {
    _find :
    vector<int> list;
    int choice_1, choice_2;
    string name;
    string temp;
    float cost;
    float from, to;
    Reference::clrscr();
    cout << "1. FIND BY NAME\n";
    cout << "2. FIND BY GROUP\n";
    cout << "3. FIND BY COST\n";
    cout << "4. FIND BY RANGE OF COST\n";
    cout << "5. RETURN BACK\n";
    cout << "Choice: ";
    cin >> choice_1;      cin.ignore();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _find;
    }
    if (choice_1 > 5 || choice_1 < 1) {
        cout << "Wrong input";
        Sleep (2000);
        goto _find;
    }

    switch (choice_1) {
        case 1 :
            
            cout << "Type name: ";
            getline (cin, name);
            _case1_1 :
            list = this->listSanPham->findN (name);
            break;
        case 2 :
            
            cout << "Type group: ";
            getline (cin, name);
            _case2_1 :
            list = this->listSanPham->findG(name);
            break;
        case 3 :
            
            cout << "Type cost: ";
            cin >> cost;        cin.ignore();
            _case3_1 :
            list = this->listSanPham->find(cost);
            break;
        case 4 :
            
            cout << "From:  ";
            cin >> from;        cin.ignore();
            cout << "To:    ";
            cin >> to;          cin.ignore();
            _case4_1 :
            list = this->listSanPham->locSP(from, to);
            break;
        case 5 :
            return;
    }
    cout << "\n\n";
    Again :
    cout << "1. DELETE PRODUCT\n";
    cout << "2. CHANGE INFORMATION\n";
    cout << "3. RETURN BACK\n";
    cout << "Choice: ";
    cin >> choice_2;        cin.ignore();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto Again;
    }
    if (choice_2 > 3 || choice_2 < 1) {
        cout << "Wrong input";
        Sleep (2000);
        Reference::gotoXY(0, Reference::whereY() - 1);
        cout << "                                       \n";
        cout << "                                        ";
        Reference::gotoXY (0, Reference::whereY() - 4);
        goto Again;
    }
    switch (choice_2) {
        case 1 : {
            int pos;
            string temp;
            bool check = false;
        _case1_2 :            
            check = false;
            Reference::clrscr();
            for (int i = 0; i < list.size(); i ++) {
                cout << "***********************************************\n";
                cout << list[i] + 1 << ". ";
                (*this->listSanPham)[list[i]].display ();
                cout << "\n";
            }

            cout << "\nType position of product: ";
            cin >> pos;     cin.ignore();
            pos --;
            for (int i = 0; i < list.size(); i ++)
                if (pos == list[i]) check = true;
            if (! check) {
                cout << "\nPlease type the position displayed";
                Sleep (2000);
                goto _case1_2;
            }
            cout << "ARE YOU SURE: ";
            getline(cin, temp);
            if (temp == "yes") {
                this->listSanPham->del(pos);
                this->listSanPham->write();
                cout << "Successfull!";
                Sleep (2000);
            }
            switch (choice_1) {
                case 1 : goto _case1_1;
                case 2 : goto _case2_1;
                case 3 : goto _case3_1;
                case 4 : goto _case4_1;
            }
            break;
        }
        case 2 : {
            int pos;
            bool check = false;
            int choice;
        _case2_2 :            
            check = false;
            Reference::clrscr();
            for (int i = 0; i < list.size(); i ++) {
                cout << "***********************************************\n";
                cout << list[i] + 1 << ". ";
                (*this->listSanPham)[list[i]].display ();
                cout << "\n";
            }

            cout << "\nType position of product: ";
            cin >> pos;     cin.ignore();
            pos --;
            for (int i = 0; i < list.size(); i ++)
                if (pos == list[i]) check = true;
            if (! check) {
                cout << "\nPlease type the position displayed";
                Sleep (2000);
                goto _case2_2;
            }
            G1 :
            Reference::clrscr();
            this->listSanPham->show(pos);
            cout << "\n";
            cout << "1. CHANGE NAME\n";
            cout << "2. CHANGE SPECIFICATIONS\n";
            cout << "3. CHANGE PRICE\n";
            cout << "4. CHANGE GROUP\n";
            cout << "5. RETURN BACK\n";
            cout << "Choice: ";
            cin >> choice;      cin.ignore();
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                goto G1;
            }
            if (choice > 5 || choice < 1) {
                cout << "\nWrong input";
                Sleep (2000);
                goto G1;
            }
            switch (choice) {
                case 1 : {
                    cout << "Type new name: ";
                    getline(cin, (*this->listSanPham)[pos].ten);
                    cout << "Successfull!";
                    this->listSanPham->write();
                    Sleep(2000);
                    goto G1;
                    break;
                } 
                case 2 : 
                    Reference::clrscr();
                    (*this->listSanPham)[pos].thongSo.changeInfo();
                    cout << "Successfull!";
                    this->listSanPham->write();
                    Sleep(2000);
                    goto G1;
                case 3 :         
                    cout << "Type new price: ";
                    cin >> (*this->listSanPham)[pos].gia;      cin.ignore();
                    cout << "Successfull!";
                    this->listSanPham->write();
                    Sleep(2000);
                    goto G1;
                    break; 
                case 4 :
                    cout << "Type new group: ";
                    getline(cin, (*this->listSanPham)[pos].group);
                    cout << "Successfull!";
                    this->listSanPham->write();
                    Sleep(2000);
                    goto G1;
                    break;     
                case 5 :
                    switch (choice_1) {
                        case 1 : goto _case1_1;
                        case 2 : goto _case2_1;
                        case 3 : goto _case3_1;
                        case 4 : goto _case4_1;
                    }
                    break ;  
            }

        }
        case 3 :
            goto _find;
    }

}
void App::find_adG() {
    string name;
    int choice;
    vector<int> list;
    _start :
    Reference::clrscr();
    this->listKhachHang->display();
    cout << "Type name of guest: ";
    getline(cin, name);
    _back :
    list = this->listKhachHang->find(name);
    cout << "1. DELETE GUEST\n";
    cout << "2. CHANGE INFORMATION OF GUEST\n";
    cout << "3. RETURN BACK\n";
    cout << "Choice: ";
    cin >> choice;      cin.ignore();
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        goto _start;
    }
    if (choice < 1 || choice > 3) {
        cout << "Wrong input";
        Sleep(2000);
        goto _start;
    }
    switch (choice) {
        case 1 : {
            int pos;
            bool check = false;;
            string temp;
            _case1 :
            Reference::clrscr();
            check = false;
            for (int i = 0; i < list.size(); i ++) {
                cout << list[i] + 1<< ". ";
                (*this->listKhachHang)[list[i]].display();
            }
            cout << "Type position of guest: ";
            cin >> pos;     cin.ignore();
            pos --;
            for (int i = 0; i < list.size(); i ++) {
                if (pos == list[i]) check = true;
            }
            if (! check) {
                cout << "We don't have this guest";
                Sleep (2000);
                goto _case1;
            }
            cout << "Are you sure: ";
            getline(cin, temp);
            if (temp == "yes") {
                this->listKhachHang->del(pos);
                cout << "Successfull!";
                Sleep (2000);
               
            }
            goto _back;
            break;
        }
        case 2 : {
            int choice;
        _case2 :
            Reference::clrscr();
            for (int i = 0; i < list.size(); i ++) {
                cout << list[i] + 1 << ". ";
                (*this->listKhachHang)[list[i]].display();
            }
            cout << "1. CHANGE NAME\n";
            cout << "2. CHANGE ADDRESS\n";
            cout << "3. CHANGE TELEPHONE NUMBER\n";
            cout << "4. CHANGE PASSWORD\n";
            cout << "5. RETURN BACK\n";
            cout << "Choice: ";
            cin >> choice;      cin.ignore();
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                goto _case2;
    }
            if (choice < 1 || choice > 5) {
                cout << "Wrong input";
                Sleep(2000);
                goto _case2;
            }
            switch (choice) {
                case 1 : {
                    int pos;
                    bool check = false;
                _case2_1 :
                    check = false;
                    for (int i = 0; i < list.size(); i ++) {
                        cout << list[i] + 1<< ". ";
                        (*this->listKhachHang)[list[i]].display();
                    }
                    cout << "Type position of guest: ";
                    cin >> pos;     cin.ignore();
                    pos --;
                    for (int i = 0; i < list.size(); i ++) {
                        if (pos == list[i]) check = true;
                    }
                    if (! check) {
                        cout << "We don't have this guest";
                        Sleep (2000);
                        goto _case2_1;
                    }
                    Reference::clrscr();
                    (*this->listKhachHang)[pos].show();
                    cout << "New name: ";
                    getline(cin, (*this->listKhachHang)[pos].name);
                    cout << "Successfull!";
                    Sleep (2000);
                    goto _case2;
                    break;
                }
                case 2 : {
                    int pos;
                    bool check = false;
                _case2_2 :
                    check = false;
                    for (int i = 0; i < list.size(); i ++) {
                        cout << list[i] + 1<< ". ";
                        (*this->listKhachHang)[list[i]].display();
                    }
                    cout << "Type position of guest: ";
                    cin >> pos;     cin.ignore();
                    pos --;
                    for (int i = 0; i < list.size(); i ++) {
                        if (pos == list[i]) check = true;
                    }
                    if (! check) {
                        cout << "We don't have this guest";
                        Sleep (2000);
                        goto _case2_2;
                    }
                    Reference::clrscr();
                    (*this->listKhachHang)[pos].show();
                    cout << "New address: ";
                    getline(cin, (*this->listKhachHang)[pos].diaChi);
                    cout << "Successfull!";
                    Sleep (2000);
                    goto _case2;
                    break;
                }
                case 3 : {
                    int pos;
                    bool check = false;
                _case2_3 :
                    check = false;
                    for (int i = 0; i < list.size(); i ++) {
                        cout << list[i] + 1<< ". ";
                        (*this->listKhachHang)[list[i]].display();
                    }
                    cout << "Type position of guest: ";
                    cin >> pos;     cin.ignore();
                    pos --;
                    for (int i = 0; i < list.size(); i ++) {
                        if (pos == list[i]) check = true;
                    }
                    if (! check) {
                        cout << "We don't have this guest";
                        Sleep (2000);
                        goto _case2_3;
                    }
                    Reference::clrscr();
                    (*this->listKhachHang)[pos].show();
                    cout << "New telephone number: ";
                    getline(cin, (*this->listKhachHang)[pos].sdt);
                    cout << "Successfull!";
                    Sleep (2000);
                    goto _case2;
                    break;
                }
                case 4 : {
                    int pos;
                    bool check = false;
                _case2_4 :
                    check = false;
                    for (int i = 0; i < list.size(); i ++) {
                        cout << list[i] + 1<< ". ";
                        (*this->listKhachHang)[list[i]].display();
                    }
                    cout << "Type position of guest: ";
                    cin >> pos;     cin.ignore();
                    pos --;
                    for (int i = 0; i < list.size(); i ++) {
                        if (pos == list[i]) check = true;
                    }
                    if (! check) {
                        cout << "We don't have this guest";
                        Sleep (2000);
                        goto _case2_4;
                    }
                    Reference::clrscr();
                    (*this->listKhachHang)[pos].show();
                    cout << "New name: ";
                    getline(cin, (*this->listKhachHang)[pos].password);
                    cout << "Successfull!";
                    Sleep (2000);
                    goto _case2;
                    break;
                }
                case 5 : goto _back;
            }
        }
        case 3 : break;
    }

}
App::~App() {
    ofstream file("lichsu.txt");
    for (int i = 0; i < this->listKhachHang->size(); i ++) {
        if (i != 0) file << "\n";
        file << i + 1 << ". ";
        file << (*this->listKhachHang)[i].name << "\n";
        file << (*this->listKhachHang)[i].history.size() << "\n";
        for (int j = 0; j < (*this->listKhachHang)[i].history.size(); j ++) {
            file << (*this->listKhachHang)[i].history[j].ten << "\n";
            file << (*this->listKhachHang)[i].history[j].soLuong << "\n";
        }
    }
    file.close();
}

/*
cout << "1. Buy product\n";
            cout << "2. Go to your cart\n";
            cout << "3. Pay for your bill\n";        
            cout << "4. Find product\n";
            cout << "5. Detailed product\n";
            cout << "6. Change password\n";
            cout << "7. Logout\n";
            cout << "8. Exit\n";
            cout << "Choice: ";
             */




// sad,badad
// asdjasbdasd
// hhh
// sksdjsdo
// adajsdhadjsd