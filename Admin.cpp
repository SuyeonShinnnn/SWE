#include "Admin.h"
#include "ReviewManager.h"
#include <iostream>

Admin::Admin(string id, string password) : User(id, password) {}

void Admin::showMenu() const
{
    cout << "==============Admin==============" << endl;
    cout << "1. 리뷰관리\n";
    cout << "2. 로그아웃\n";
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

        //리뷰관리
        if (choice == 1) {
            system("cls");
            cout << "==============Review==============" << endl;

            ReviewManager reviewManager;
            reviewManager.showReviews();
            cout << "==================================" << endl;
            cout << "==================================" << endl;
            cout << "삭제할 리뷰 번호(뒤로가기: 0)" << endl;
            cout << ">> ";

            int number;
            cin >> number;
            
            system("cls");

            if (number != 0)
            {
                reviewManager.deleteReview(number);
                cout << "**리뷰 삭제 완료**" << endl;
            }
        }
        //로그아웃
        else if (choice == 2) {
            system("cls");
            break;
        }
    }
}