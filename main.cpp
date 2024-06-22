#include "Inventory.h"
#include "UserManager.h"
#include "Customer.h"
#include "Seller.h"
#include "Admin.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void signIn();
void signUp();

int main() {

    while (true) {

        cout << "============올림Pick============" << endl;
        cout << "1. 로그인  2. 회원가입  3. 종료" << endl;
        cout << ">> ";

        int choice;
        cin >> choice;

        system("cls");

        //로그인
        if (choice == 1) {
            signIn();
        }
        //회원가입
        else if (choice == 2) {

            signUp();
        }
        //종료
        else if (choice == 3) {
            break;
        }
    }

    return 0;
}
void signIn()
{
    Inventory inventory;
    UserManager userManager(inventory);

    cout << "===========로그인===========" << endl;

    string id, password;
    cout << "아이디: ";
    cin >> id;
    cout << "비밀번호: ";
    cin >> password;

    User* user = userManager.findUser(id, password);
    if (user) {
        system("cls");
        user->handleMenu(inventory);
    }
    else {
        system("cls");
        cout << "**로그인 실패**\n";
    }
}
void signUp()
{
    Inventory inventory;
    UserManager userManager(inventory);

    string id, password;
    int role;

    cout << "================회원가입================" << endl;
    cout << "권한 (1. customer | 2. seller | 3. admin): ";
    cin >> role;
    
    cout << "아이디: ";
    cin >> id;

  
    //아이디 중복 체크
    if (userManager.isUserIdTaken(id)) {
        system("cls");
        cout << "**이미 존재하는 아이디입니다**\n";
        signUp();
    }
    else
    {
        cout << "비밀번호: ";
        cin >> password;

        if (role == 1) {
            userManager.addUser(new Customer(id, password, inventory));
        }
        else if (role == 2) {
            userManager.addUser(new Seller(id, password, inventory));
        }
        else if (role == 3) {
            userManager.addUser(new Admin(id, password));
        }
        system("cls");
    }
}