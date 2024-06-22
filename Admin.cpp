#include "Admin.h"
#include "ReviewManager.h"
#include <iostream>

Admin::Admin(string id, string password) : User(id, password) {}

void Admin::showMenu() const
{
    cout << "==============Admin==============" << endl;
    cout << "1. �������\n";
    cout << "2. �α׾ƿ�\n";
}
void Admin::handleMenu(Inventory& inventory)
{
    system("cls");
    while (true) 
    {
        showMenu();

        cout << ">> ";
        int choice;
        cin >> choice;

        //�������
        if (choice == 1) {
            system("cls");
            cout << "==============Review==============" << endl;

            ReviewManager reviewManager;
            reviewManager.showReviews();
            cout << "==================================" << endl;
            cout << "==================================" << endl;
            cout << "������ ���� ��ȣ(�ڷΰ���: 0)" << endl;
            cout << ">> ";

            int number;
            cin >> number;
            
            system("cls");

            if (number != 0)
            {
                reviewManager.deleteReview(number);
                cout << "**���� ���� �Ϸ�**" << endl;
            }
        }
        //�α׾ƿ�
        else if (choice == 2) {
            system("cls");
            break;
        }
    }
}