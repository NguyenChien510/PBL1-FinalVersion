#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sstream>
#include <conio.h>
#include <chrono>
#include <thread>
using namespace std;
struct Date {
    int day;
    int month;
    int year;
};
typedef struct Date DATE;
struct Account {
    string username;
    string pass;
};
typedef struct Account ACCOUNT;
struct NodeAccount {
    ACCOUNT data;
    NodeAccount* next;
};
typedef struct NodeAccount* NODEACCOUNT;
struct ListAccounts {
    NodeAccount* head;
    NodeAccount* tail;
};
typedef struct ListAccounts LISTACCOUNTS;
struct Employee {
    string area;
    string shipper;
};
typedef struct Employee EMPLOYEE;
struct NodeEmployee {
    EMPLOYEE data;
    NodeEmployee* next;
};
typedef struct NodeEmployee* NODEEMPLOYEE;
struct ListEmployees {
    NodeEmployee* head;
    NodeEmployee* tail;
};
typedef struct ListEmployees LISTEMPLOYEES;
struct Package {
    int code;
    string item;
    string receiver;
    string sender;
    string address;
    int price;
    int mass;
    DATE time;
    int dongia;
    int status;
    string receiver_number;
    string sender_number;
    string shipper;
};
typedef struct Package PACKAGE;
struct NodePackage {
    PACKAGE data;
    NodePackage* next;
};
typedef struct NodePackage* NODEPACKAGE;
struct ListPackages {
    NODEPACKAGE head;
    NODEPACKAGE tail;
};
typedef struct ListPackages LISTPACKAGES;
void Read_Account(ifstream& filein, ACCOUNT& x);  
void InsertAccount(LISTACCOUNTS& l, NODEACCOUNT x); 
NODEACCOUNT createAccount(ACCOUNT x); 
void InitListAccounts(LISTACCOUNTS& l); 
void Read_All_Accounts(ifstream& filein, LISTACCOUNTS& l); 
void Read_Date(ifstream& filein, DATE& x); 
void Read_Employee(ifstream& filein, EMPLOYEE& x); 
void InsertEmployee(LISTEMPLOYEES& l, NODEEMPLOYEE x); 
NODEEMPLOYEE createEmployee(EMPLOYEE x); 
void InitListEmployees(LISTEMPLOYEES& l); 
void Read_All_Employees(ifstream& filein, LISTEMPLOYEES& l); 
bool Read_Package(ifstream& filein, PACKAGE& x, LISTEMPLOYEES& ld); 
void Read_All_Packages(ifstream& filein, LISTPACKAGES& l, LISTEMPLOYEES& ld); 
NODEPACKAGE createPackage(PACKAGE x); 
void InitListPackages(LISTPACKAGES& l); 
void InsertPackage(LISTPACKAGES& l, NODEPACKAGE x); 
void Display(LISTPACKAGES l); 
void DisplayOne(NODEPACKAGE temp); 
void interFace(); 
string Address(PACKAGE x); 
string LoaiBoXuongDongODau(string& s); 
string NguoiGiao(PACKAGE& x, string s, LISTEMPLOYEES ld); 
void Save(LISTPACKAGES& l, string user);  
bool check_empty(LISTPACKAGES& l); 
void Classify(LISTPACKAGES l, int x); 
void ChinhSua(LISTPACKAGES& l, int x); 
void UpdateStatus(LISTPACKAGES& l, int xy); 
void Summary(LISTPACKAGES& l); 
bool login(string user, string pass);
string GetPassword();
void loginoutput();
void Option(string user);
void logo();
int main() {
    system("color 3");
    logo();
    loginoutput();
    return 0;
}
void Read_Account(ifstream &filein,ACCOUNT &x){
	getline(filein,x.username,',');
	getline(filein,x.pass,',');
}
void InsertAccount(LISTACCOUNTS &l,NODEACCOUNT x){
	if(l.head == NULL) l.head = l.tail = x;
	else{
		l.tail->next = x;
		l.tail = x;
	}
}
NODEACCOUNT createAccount(ACCOUNT x){
	NODEACCOUNT newnode = new NodeAccount;
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
void InitListAccounts(LISTACCOUNTS &l){
	l.head = NULL;
	l.tail = NULL;
}
void Read_All_Accounts(ifstream &filein,LISTACCOUNTS &l){
	while(!filein.fail()){
		ACCOUNT x;
		Read_Account(filein,x);
		if (filein.fail())
        break;
		NODEACCOUNT newnode = createAccount(x);
		InsertAccount(l,newnode);
	}
}
void Read_Date(ifstream &filein,DATE &x){
	filein >> x.day;filein.ignore();
	filein >> x.month;filein.ignore();
	filein >> x.year;filein.ignore();
}
void Read_Employee(ifstream &filein,EMPLOYEE &x){
	getline(filein,x.area,',');
	getline(filein,x.shipper,',');
}
void InsertEmployee(LISTEMPLOYEES &l, NODEEMPLOYEE x){
	if(l.head == NULL) l.head = l.tail = x;
	else{
		l.tail->next = x;
		l.tail = x;
	}
}
NODEEMPLOYEE createEmployee(EMPLOYEE x){
	NODEEMPLOYEE newnode = new NodeEmployee;
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
void InitListEmployees(LISTEMPLOYEES &l){
	l.head = NULL;
	l.tail = NULL;
}
void Read_All_Employees(ifstream &filein,LISTEMPLOYEES &l){
	while(!filein.fail()){
		EMPLOYEE x;
		Read_Employee(filein,x);
		if (filein.fail())
        break;
		NODEEMPLOYEE newnode = createEmployee(x);
		InsertEmployee(l,newnode);
	}
}
bool Read_Package(ifstream &filein,PACKAGE &x,LISTEMPLOYEES &ld) {
    if (!(filein >> x.code)) return false;
    filein.ignore();
    getline(filein, x.item, ',');
    getline(filein, x.sender, ',');
    getline(filein, x.sender_number, ',');
    getline(filein, x.receiver, ',');
    getline(filein, x.receiver_number, ',');
    getline(filein, x.address, ',');
    filein >> x.price;filein.ignore();
    filein >> x.mass;filein.ignore();
    Read_Date(filein, x.time);
    filein >> x.status;filein.ignore();
    x.shipper=NguoiGiao(x,x.address,ld);
	return true;
}
void Read_All_Packages(ifstream &filein,LISTPACKAGES &l,LISTEMPLOYEES &ld){
	PACKAGE x;
	while(Read_Package(filein,x,ld)){
		NODEPACKAGE newnode = createPackage(x);
		InsertPackage(l,newnode);
	}
}
NODEPACKAGE createPackage(PACKAGE x){
	NODEPACKAGE newnode = new NodePackage;
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
void InitListPackages(LISTPACKAGES &l){
	l.head = NULL;
	l.tail = NULL;
}
void InsertPackage(LISTPACKAGES &l,NODEPACKAGE x) {
	if (l.head == NULL) { 
        l.head = l.tail = x; 
    } else {
        l.tail->next = x; 
        l.tail = x;
    }
}
void Display(LISTPACKAGES l){
	if (l.head == NULL) cout << "DANH SACH RONG!" <<endl;
	else{
	NODEPACKAGE temp = l.head;
		while(temp!=NULL){
		cout <<endl<< "       		Thong tin don hang:  "<<endl;
		cout << "Ma buu kien   : " << temp->data.code <<endl;
		cout << "Ten hang      : " << temp->data.item<<endl;
		cout << "Ten nguoi gui : " << temp->data.sender<<endl;
		cout << "SDT           : " << temp->data.sender_number<<endl;
		cout << "Ten nguoi nhan: " << temp->data.receiver<<endl;cout << "SDT           : "<< temp->data.receiver_number<<endl;
		cout << "Dia diem giao : " << temp->data.address<<endl;
		cout << "Thanh tien    : " << temp->data.price<<" VND"<<endl;
		cout << "Khoi luong    : " <<temp->data.mass<<" kg"<<endl;
		cout << "Ngay gui      : " << setw(2)<<setfill('0')	<<temp->data.time.day<<"/"<< setw(2)<<setfill('0')<<temp->data.time.month<<"/"<<temp->data.time.year<< endl;
		cout << "Shipper       : " << temp->data.shipper<<endl;
		if(temp->data.status == 0) cout << "Tinh trang    : Dang giao!"<<endl;
		else if(temp->data.status == 1) cout << "Tinh trang    : Da giao!"<<endl;
		temp = temp->next;
	}
 }
}
void DisplayOne(NODEPACKAGE temp){
					cout <<endl<< "       		Thong tin don hang:  "<<endl;
			cout << "Ma buu kien   : " << temp->data.code <<endl;
			cout << "Ten hang      : " << temp->data.item<<endl;
			cout << "Ten nguoi gui : " << temp->data.sender<<endl;
			cout << "SDT           : " << temp->data.sender_number<<endl;
			cout << "Ten nguoi nhan: " << temp->data.receiver<<endl;cout << "SDT           : "<< temp->data.receiver_number<<endl;
			cout << "Dia diem giao : " << temp->data.address<<endl;
			cout << "Thanh tien    : " << temp->data.price<<" VND"<<endl;
			cout << "Khoi luong    : " <<temp->data.mass<<" kg"<<endl;
			cout << "Ngay gui      : " << setw(2)<<setfill('0')	<<temp->data.time.day<<"/"<< setw(2)<<setfill('0')<<temp->data.time.month<<"/"<<temp->data.time.year<< endl;
			cout << "Shipper       : " << temp->data.shipper<<endl;
			if(temp->data.status == 0) cout << "Tinh trang    : Dang giao!"<<endl;
			else if(temp->data.status == 1) cout << "Tinh trang    : Da giao!"<<endl<<endl;
}
void interFace(){
	cout << endl;
	cout << "------------- QUAN LI BUU KIEN TAI BUU CUC -------------"<<endl;
	cout << "*               1.Nhap buu kien                        *"<<endl;cout<<endl;
	cout << "*               2.Xem buu kien                         *"<<endl;cout<<endl;
	cout << "*               3.Thong ke buu kien o cac quan,huyen   *"<<endl;cout<<endl;
	cout << "*       	4.Chinh sua buu kien                   *"<<endl;cout<<endl;
	cout << "*       	5.Cap nhat trang thai buu kien         *"<<endl;cout<<endl;
	cout << "*       	6.Save                                 *"<<endl;cout<<endl;
	cout << "*       	7.Dang Xuat                            *"<<endl;cout<<endl;
	cout << "*       	0.Thoat                                *"<<endl;cout<<endl;
	cout << "--------------------------------------------------------"<<endl;
	cout << "Nhap lua chon : ";
}
string Address(PACKAGE x){int luachon;
	cout << "-------- Khu vuc giao hang --------"<<endl;
	cout << "              QUAN:            "<<endl;
	cout << "          1.Hai Chau"<<endl;
	cout << "          2.Lien Chieu"<<endl;
	cout << "          3.Thanh Khe"<<endl;
	cout << "          4.Cam Le"<<endl;
	cout << "          5.Son Tra"<<endl;
	cout << "          6.Ngu Hanh Son"<<endl;
	cout << "              HUYEN:        "<<endl;
	cout << "          7.Hoa Vang"<<endl;
	cout << "          8.Hoang Sa"<<endl;
	cout << "Chon khu vuc : ";cin>>luachon;
	switch(luachon){
		case 1: x.address="Hai Chau";break;
		case 2: x.address="Lien Chieu";break;
		case 3: x.address="Thanh Khe";break;
		case 4: x.address="Cam Le";break;
		case 5: x.address="Son Tra";break;
		case 6: x.address="Ngu Hanh Son";break;
		case 7: x.address="Hoa Vang";break;
		case 8: x.address="Hoang Sa";break;
		default:cout<<"Vui long nhap dung STT!"<<endl;x.address = Address(x);
	}
	return x.address;
}
string LoaiBoXuongDongODau(string &s) {
    while (!s.empty() && s.front() == '\n') s.erase(0, 1); 
    return s;
}
string NguoiGiao(PACKAGE &x,string s,LISTEMPLOYEES ld){
	ifstream filein;
	filein.open("danhsachnhanviengiaohang.txt",ios::in);
	Read_All_Employees(filein,ld);
	NODEEMPLOYEE temp = ld.head;
	while(temp!=NULL){
		if(LoaiBoXuongDongODau(temp->data.area)==s){
		x.shipper=temp->data.shipper;break;
		}
		temp=temp->next;
	}
	return x.shipper;
}
void Save(LISTPACKAGES &l,string user){
	cin.ignore();
	time_t currentTime = time(nullptr);
	tm *timeInfo = localtime(&currentTime);
	ofstream fileout; int demdagiao=0,demdanggiao=0,tongtien=0;
	fileout.open((user + ".txt").c_str(), ios::out); 
	NODEPACKAGE temp = l.head;
	    		   fileout << setw(5) << "Ma Buu Kien" << " | "
                    << setw(10) << "Ten Hang" << " | "
                    << setw(20) << "Ten Nguoi Gui" << " | "
                    << setw(12) << "SDT " << " | "
                    << setw(20) << "Ten Nguoi Nhan" << " | "
                    << setw(12) << "SDT " << " | "
                    << setw(18) << "Dia Diem Giao Hang" << " | "
                    << setw(10) << "Thanh Tien" << " | "
                    << setw(11) << "Khoi Luong" << " | "
                    << setw(10) << "Ngay Gui" << " | "
                    << setw(16) << "Shipper" << " | "
                    << setw(10) << "Tinh Trang" << endl;
    fileout << setfill('-') << setw(196) << "-" << setfill(' ') << endl;
	while(temp != NULL){
 	fileout << right << setw(11) << temp->data.code << " | "
		    << setw(10) << temp->data.item << " | "
		 	<< setw(20) << temp->data.sender << " | "
		 	<< setw(12) << temp->data.sender_number << " | "
		 	<< setw(20) << temp->data.receiver << " | "
		 	<< setw(12) << temp->data.receiver_number << " | "
		 	<< setw(18) << temp->data.address << " | "
 		 	<< setw(6) << temp->data.price<<" VND" << " | "
		 	<< setw(8) << temp->data.mass<<" kg" << " | "
		 	<< setfill('0') << setw(2) << temp->data.time.day << "/" << setw(2) << temp->data.time.month << "/" << temp->data.time.year << " | ";
         	fileout << setfill(' ');
         	fileout << setw(16) << temp->data.shipper << " | ";
			if(temp->data.status==1){
				fileout<< setw(9) << "Da Giao!" << endl;demdagiao++;tongtien+= temp->data.price;}
	   	 	else if(temp->data.status==0) {
				fileout<< setw(9) << "Dang Giao!" << endl;demdanggiao++;
				}
		temp = temp->next;
	}
	fileout <<endl<< "THONG KE"<<endl;
	fileout<< "Da giao  : "<<demdagiao<<endl<<endl;
	fileout <<"Dang giao: "<<demdanggiao<<endl<<endl;
	fileout<< "Tong so tien da nhan : "<<tongtien<<" VND"<<endl;
	fileout << "DATE : " << timeInfo->tm_mday<<"/"<<timeInfo->tm_mon + 1<<"/"<<timeInfo->tm_year + 1900<<"  "<<timeInfo->tm_hour<<":"<<timeInfo->tm_min<<":"<<timeInfo->tm_sec;
	fileout.close();
}
bool check_empty(LISTPACKAGES &l){
	bool check = true;
	if(l.head==NULL){
		check = false;
	 	cout << "DANH SANH RONG!"<<endl;
	 }
}
void Classify(LISTPACKAGES l, int x){
	NODEPACKAGE temp = l.head;bool find=false;
	switch(x){
		case 1:
    			cout << "                                                                         DANH SACH CAC BUU KIEN : DA GIAO "<<endl<<endl;
				while(temp!=NULL){
    			if(temp->data.status==1){
					DisplayOne(temp);
					find=true;
				}
				temp=temp->next;
    			}
			if(!find) cout << "Khong tim thay buu kien co TRANG THAI : Da Giao!"<<endl;
			break;
		case 2:
    		cout << "                                                                        DANH SACH CAC BUU KIEN : DANG GIAO "<<endl<<endl;
   			while(temp!=NULL){
    			if(temp->data.status==0){
					DisplayOne(temp);
					find=true;
			}
			temp=temp->next;
    	}
			if(!find) cout << "Khong tim thay buu kien co TRANG THAI : Dang Giao!"<<endl;
			break;
	}
}
void ChinhSua(LISTPACKAGES &l,int x){
	NODEPACKAGE temp=l.head;LISTEMPLOYEES ld;
	while(temp!=NULL && temp->data.code!=x) temp=temp->next;
	if(temp==NULL) cout << "Khong tim thay ma buu kien can sua!"<<endl;
	else{
		int luaChon;
        cout <<endl<< "Chon thong tin can chinh sua:" << endl;
        cout << "1. Ten hang" << endl;
        cout << "2. Nguoi gui" << endl;
        cout << "3. Nguoi nhan" << endl;
        cout << "4. Dia chi giao hang" << endl;
        cout << "5. Khoi luong" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;
        cin.ignore(); 
        switch(luaChon){
            case 1:
                cout << "Nhap ten hang moi: ";
                getline(cin, temp->data.item);
                break;
            case 2:
                cout << "Nhap ten nguoi gui moi: ";
                getline(cin, temp->data.sender);
                break;
            case 3:
                cout << "Nhap ten nguoi nhan moi: ";
                getline(cin, temp->data.receiver);
                break;
            case 4:
                temp->data.address = Address(temp->data);
                break;
            case 5:
                cout << "Nhap khoi luong moi: ";
                cin >> temp->data.mass;
                temp->data.price = (temp->data.mass * 250)+temp->data.dongia;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
       cout << "Cap Nhat Thanh Cong!" << endl;
	}
}	
void UpdateStatus(LISTPACKAGES &l,int xy){
	PACKAGE x;
	NODEPACKAGE temp=l.head;
	while(temp!=NULL && temp->data.code!=xy) temp = temp->next;
	if(temp == NULL ) cout << "Khong tim thay ma buu kien can thay doi!"<<endl;
	else{ 
		int thay;
		cout << "-----------Lua chon-----------"<<endl;
		cout << "         0.Dang Giao!"<<endl;
		cout << "         1.Da Giao!"<<endl;
		cout << "Nhap lua chon : ";cin>>thay;
		switch(thay){
			case 0:temp->data.status=0;cout<<"Cap Nhat Thanh Cong!"<<endl;break;
			case 1:temp->data.status=1;cout<<"Cap Nhat Thanh Cong!"<<endl;break;
			default:cout<<"Vui long nhap 0 hoac 1!"<<endl;break;
		}
	}
}
void Summary(LISTPACKAGES &l){
	NODEPACKAGE temp = l.head;int demHC=0,demLC=0,demTK=0,demCL=0,demST=0,demNHS=0,demHV=0,demHS=0,option;string address;
	while(temp!=NULL){
		if     (temp->data.address=="Hai Chau") demHC++;
		else if(temp->data.address=="Lien Chieu") demLC++;
		else if(temp->data.address=="Thanh Khe") demTK++;
		else if(temp->data.address=="Cam Le") demCL++;
		else if(temp->data.address=="Son Tra") demST++;
		else if(temp->data.address=="Ngu Hanh Son") demNHS++;
		else if(temp->data.address=="Hoa Vang") demHV++;
		else if(temp->data.address=="Hoang Sa") demHS++;
		temp=temp->next;
	}
		cout << "Danh sach cac buu kien o cac QUAN , HUYEN : "<<endl;
		cout << "1. Hai Chau     : " << demHC << " buu kien"<<endl<<endl;
		cout << "2. Lien Chieu   : " << demLC << " buu kien"<<endl<<endl;
		cout << "3. Thanh Khe    : " << demTK << " buu kien"<<endl<<endl;
		cout << "4. Cam Le       : " << demCL << " buu kien"<<endl<<endl;
		cout << "5. Son Tra      : " << demST << " buu kien"<<endl<<endl;
		cout << "6. Ngu Hanh Son : " << demNHS << " buu kien"<<endl<<endl;
		cout << "7. Hoa Vang     : " << demHV << " buu kien"<<endl<<endl;
		cout << "8. Hoang Sa     : " << demHS << " buu kien"<<endl<<endl;
		bool check =false;
		while(!check){
		cout <<endl<< "Nhap STT de xem chi tiet cac don hang : ";cin>>option;
		switch(option){
		case 1: address="Hai Chau";check=true;break;
		case 2: address="Lien Chieu";check=true;break;
		case 3: address="Thanh Khe";check=true;break;
		case 4: address="Cam Le";check=true;break;
		case 5: address="Son Tra";check=true;break;
		case 6: address="Ngu Hanh Son";check=true;break;
		case 7: address="Hoa Vang";check=true;break;
		case 8: address="Hoang Sa";check=true;break;
		default:cout<<"Vui long nhap dung STT!"<<endl;
		}
	}
	if((option==1 && demHC==0) || (option==2 && demLC==0) || (option==3 && demTK==0) || (option==4 && demCL==0) || (option==5 && demST==0) || (option==6 && demNHS==0) || (option==7 && demHV==0) || (option==8 && demHS==0))
	cout << "Khong co buu kien nao o khu vuc nay!!"<<endl<<endl;
	else{
		temp=l.head;
		while(temp!=NULL){
			if(temp->data.address==address){
			cout <<endl<< "       		Thong tin don hang:  "<<endl;
			cout << "Ma buu kien   : " << temp->data.code <<endl;
			cout << "Ten hang      : " << temp->data.item<<endl;
			cout << "Ten nguoi gui : " << temp->data.sender<<endl;
			cout << "SDT           : " << temp->data.sender_number<<endl;
			cout << "Ten nguoi nhan: " << temp->data.receiver<<endl;cout << "SDT           : "<< temp->data.receiver_number<<endl;
			cout << "Dia diem giao : " << temp->data.address<<endl;
			cout << "Thanh tien    : " << temp->data.price<<" VND"<<endl;
			cout << "Khoi luong    : " <<temp->data.mass<<" kg"<<endl;
			cout << "Ngay gui      : " << setw(2)<<setfill('0')	<<temp->data.time.day<<"/"<< setw(2)<<setfill('0')<<temp->data.time.month<<"/"<<temp->data.time.year<< endl;
			cout << "Shipper       : " << temp->data.shipper<<endl;
			if(temp->data.status == 0) cout << "Tinh trang    : Dang giao!"<<endl;
			else if(temp->data.status == 1) cout << "Tinh trang    : Da giao!"<<endl<<endl;
			}
		temp=temp->next;
		}
	}
}
bool login(string user,string pass){
	LISTACCOUNTS l;
	ifstream filein;
	filein.open("taikhoan.txt",ios::in);
	Read_All_Accounts(filein,l);
	NODEACCOUNT temp = l.head;
	while(temp!=NULL){
		if(LoaiBoXuongDongODau(temp->data.username)==user && temp->data.pass==pass ){
			return true;break;
		}
		temp=temp->next;
	}
	if(temp==NULL) return false;
}
string GetPassword() {
    string pass = "";
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' là ki tu Enter
        if (ch == '\b' && !pass.empty()) { // Xoa ki tu neu nhin Backspace
            pass.pop_back();
            cout << "\b \b"; // Xoa ki tu hien thi tren man hinh
        } else if (ch != '\b') { // Neu khong phai ki tu Backspace
            pass.push_back(ch);
            cout << '*'; // Hien thi '' thay vi ki tu thuc te
        }
    }
    cout << endl;
    return pass;
}
void loginoutput() {
    string user, pass;
    bool loggedIn = false;
    do {
        cout << "Dang nhap tai khoan cho nhan vien!!" << endl << endl;
        cout << "Username : ";
        getline(cin, user);
        cout << "Password : ";
        pass =GetPassword();
        if (login(user, pass)){
            cout << "LOGIN SUCCESS!" << endl;
            loggedIn = true;
            break;
        } 
		else{
        	cout << "Tai khoan hoac mat khau khong dung. Vui long nhap lai!" << endl << endl;
            char cont = _getch();system("cls");
        }
    }while(true);
	if (loggedIn){
		cout << "Dang dang nhap";
		for(int i =0;i<10;i++){
			cout<<".";
			this_thread::sleep_for(chrono::milliseconds(150));
		}
		system("cls");
        Option(user);
    }
}
void logo(){
	ifstream filein;
	filein.open("logo.txt");
	string line;
	while(getline(filein,line)){
		cout << line << endl;
	}
	filein.close();
}
void Option(string user){
	LISTPACKAGES l;InitListPackages(l);
	LISTEMPLOYEES ld;InitListEmployees(ld);
	int option;
	ifstream filein;filein.open("danhsachbuukien.txt",ios::in);Read_All_Packages(filein,l,ld);
	while(1){
		system("cls");
		interFace();
    	cin >> option;
		system("cls");
		switch(option){
			case 1:
				if(!filein.is_open()) cout << "Khong the doc du lieu!";
				else cout << "Nhap thanh cong!"<<endl;
				cout <<endl <<"BAM PHIM BAT KI DE QUAY TRO LAI.....";
				_getch();
				break;
			case 2:
				int option3;
				cout << "--------------- Lua chon ------------"<<endl;
				cout << "     1 Xem toan bo danh sach. "<<endl;
				cout << "     2 Xem buu kien theo phan loai."<<endl;
				cout << "Nhap lua chon : ";cin>>option3;
				if(option3 == 1) Display(l);
				else if(option3==2){
				int option33;
				cout << "---------------- Lua chon ---------------------" <<endl;
				cout << "     1 Phan loai theo TINH TRANG: Da giao!"  << endl;
				cout << "     2 Phan loai theo TINH TRANG: Dang giao!"  << endl;
				cout << "-----------------------------------------------"<<endl;
				cout << "Nhap lua chon : ";cin>>option33;
				if(check_empty(l)==true) {
					Classify(l,option33);}
				}
				cout <<endl <<"BAM PHIM BAT KI DE QUAY TRO LAI.....";
				_getch();
				break;
			case 3:
				if(check_empty(l)==true){
					Summary(l);
				}
				cout <<endl <<"BAM PHIM BAT KI DE QUAY TRO LAI.....";
				_getch();
				break;
			case 4:
				if(check_empty(l)==true){
				Display(l);
				cout << "Nhap ma buu kien can chinh sua : ";int x;cin>>x;
				ChinhSua(l,x);}
				cout <<endl <<"BAM PHIM BAT KI DE QUAY TRO LAI.....";
				_getch();
				break;
			case 5:
				if(check_empty(l)==true) {
				Display(l);
				int xy;cout <<"Nhap ma buu kien can thay doi trang thai : ";cin>>xy;
				UpdateStatus(l,xy);}
				cout <<endl <<"BAM PHIM BAT KI DE QUAY TRO LAI.....";
				_getch();
				break;
			case 6:
				if(l.head == NULL) cout << "DANH SACH CON TRONG!" <<endl;
				else {
				Save(l,user);
				cout << "Luu Thanh Cong!"<<endl;}
				cout <<endl <<"BAM PHIM BAT KI DE QUAY TRO LAI.....";
				_getch();
				break;
			case 7:
				char confirm;
				do{
				cout << "Ban chac chan muon dang xuat ?"<<endl;
				cout << "Y : Dang xuat!"<<endl;
				cout << "N : Quay lai!"<<endl;
				cout << "Nhap lua chon cua ban (Y/N): ";
      			cin >> confirm;
      			if(confirm=='Y' || confirm=='y'){
      				cout << "Dang dang xuat";
					for(int i =0;i<10;i++){
					cout << ".";
					this_thread::sleep_for(chrono::milliseconds(150));
					}
					system("cls");
      				cin.ignore();loginoutput();break;
				}
				else if(confirm=='N' || confirm=='n'){
					system("cls");Option(user);break;
				}
				else cout << "Lua chon khong hop le! Vui long nhap lai." << endl;
			}while(confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');
				break;
			case 0:
				exit(0);
		}
	}
}

