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

        cout << "============�ø�Pick============" << endl;
        cout << "1. �α���  2. ȸ������  3. ����" << endl;
        cout << ">> ";

        int choice;
        cin >> choice;

        system("cls");

        //�α���
        if (choice == 1) {
            signIn();
        }
        //ȸ������
        else if (choice == 2) {

            signUp();
        }
        //����
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

    cout << "===========�α���===========" << endl;

    string id, password;
    cout << "���̵�: ";
    cin >> id;
    cout << "��й�ȣ: ";
    cin >> password;

    User* user = userManager.findUser(id, password);
    if (user) {
        system("cls");
        user->handleMenu(inventory);
    }
    else {
        system("cls");
        cout << "**�α��� ����**\n";
    }
}
void signUp()
{
    Inventory inventory;
    UserManager userManager(inventory);

    string id, password;
    int role;

    cout << "================ȸ������================" << endl;
    cout << "���� (1. customer | 2. seller | 3. admin): ";
    cin >> role;
    
    cout << "���̵�: ";
    cin >> id;

  
    //���̵� �ߺ� üũ
    if (userManager.isUserIdTaken(id)) {
        system("cls");
        cout << "**�̹� �����ϴ� ���̵��Դϴ�**\n";
        signUp();
    }
    else
    {
        cout << "��й�ȣ: ";
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