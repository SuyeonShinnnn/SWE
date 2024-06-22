#include "Seller.h"
#include "OrderManager.h"
#include "PickUp.h"
#include <iostream>
#include <thread>

using namespace std;

Seller::Seller(string id, string password, Inventory& inv)
    : User(id, password), inventory(inv) {}

void Seller::showMenu() const
{
    cout << "===========Seller===========" << endl;
    cout << "1. 상품등록\n";
    cout << "2. 배송관리\n";
    cout << "3. 픽업관리\n";
    cout << "4. 경매관리\n";
    cout << "5. 로그아웃\n";
}

void Seller::handleMenu(Inventory& inventory)
{
    while (true) {
        showMenu();

        int choice;
        cout << ">> ";
        cin >> choice;

        //상품등록
        if (choice == 1) {
            string name;
            double price;
            int stock;
            string limitedFlag;

            system("cls");
            cout << "===========상품등록===========" << endl;
            cout << "상품명: ";
            cin >> name;
            cout << "가격: ";
            cin >> price;
            cout << "재고: ";
            cin >> stock;
            cout << "한정판 여부 (Y/N): ";
            cin >> limitedFlag;
            inventory.addProduct(name, price, stock, limitedFlag);

            system("cls");
            cout << "**상품 등록 완료**" << endl;
        }
        //배송관리
        else if (choice == 2) {
            system("cls");
            cout << "===========배송관리===========" << endl;
            manageDeliveries();
        }
        //픽업관리
        else if (choice == 3) {
            system("cls");
            cout << "===========픽업관리===========" << endl;
            managePickUp();
        }
        //경매관리
        else if (choice == 4) {
            system("cls");
            cout << "===========경매관리===========" << endl;
            int num;

            cout << "1. 경매시작 2. 경매종료" << endl << ">> ";
            cin >> num;

            if (num == 1)inventory.showLimitedProducts();
            else if (num == 2) {
                string product;
                a.showAuctionItems();
                cout << "종료하실 상품의 이름을 입력해주세요." << endl << ">> ";
                cin >> product;
                a.endAuction(product);
            }

        }
       
        //로그아웃
        else if (choice == 5)
        {
            break;
        }
    }
}

void Seller::manageDeliveries() {


    OrderManager orderManager;
    orderManager.loadOrders();
    orderManager.showPendingOrders();

    string orderId;
    cout << "배송 상태를 '배송중'으로 변경할 주문번호를 입력하세요" << endl;
    cout << ">> ";
    cin >> orderId;
    orderManager.updateOrderStatus(orderId, "배송중");


    for (int second = 1; second <= 5; second++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << second << endl;
    }
    orderManager.updateOrderStatus(orderId, "배송완료");
}

void Seller::managePickUp() {

    PickUp pickUp;
    pickUp.displayPickupReservations("seller");

    int orderId;
    cout << "픽업된 상품의 번호를 입력하세요" << endl;
    cout << ">> ";
    cin >> orderId;

    pickUp.updatePickUpStatus(orderId);
}
Inventory& Seller::getInventory()
{
    return inventory; 
}