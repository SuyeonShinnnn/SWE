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
    cout << "1. ��ǰ���\n";
    cout << "2. ��۰���\n";
    cout << "3. �Ⱦ�����\n";
    cout << "4. ��Ű���\n";
    cout << "5. �α׾ƿ�\n";
}

void Seller::handleMenu(Inventory& inventory)
{
    while (true) {
        showMenu();

        int choice;
        cout << ">> ";
        cin >> choice;

        //��ǰ���
        if (choice == 1) {
            string name;
            double price;
            int stock;
            string limitedFlag;

            system("cls");
            cout << "===========��ǰ���===========" << endl;
            cout << "��ǰ��: ";
            cin >> name;
            cout << "����: ";
            cin >> price;
            cout << "���: ";
            cin >> stock;
            cout << "������ ���� (Y/N): ";
            cin >> limitedFlag;
            inventory.addProduct(name, price, stock, limitedFlag);

            system("cls");
            cout << "**��ǰ ��� �Ϸ�**" << endl;
        }
        //��۰���
        else if (choice == 2) {
            system("cls");
            cout << "===========��۰���===========" << endl;
            manageDeliveries();
        }
        //�Ⱦ�����
        else if (choice == 3) {
            system("cls");
            cout << "===========�Ⱦ�����===========" << endl;
            managePickUp();
        }
        //��Ű���
        else if (choice == 4) {
            system("cls");
            cout << "===========��Ű���===========" << endl;
            int num;

            cout << "1. ��Ž��� 2. �������" << endl << ">> ";
            cin >> num;

            if (num == 1)inventory.showLimitedProducts();
            else if (num == 2) {
                string product;
                a.showAuctionItems();
                cout << "�����Ͻ� ��ǰ�� �̸��� �Է����ּ���." << endl << ">> ";
                cin >> product;
                a.endAuction(product);
            }

        }
       
        //�α׾ƿ�
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
    cout << "��� ���¸� '�����'���� ������ �ֹ���ȣ�� �Է��ϼ���" << endl;
    cout << ">> ";
    cin >> orderId;
    orderManager.updateOrderStatus(orderId, "�����");


    for (int second = 1; second <= 5; second++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << second << endl;
    }
    orderManager.updateOrderStatus(orderId, "��ۿϷ�");
}

void Seller::managePickUp() {

    PickUp pickUp;
    pickUp.displayPickupReservations("seller");

    int orderId;
    cout << "�Ⱦ��� ��ǰ�� ��ȣ�� �Է��ϼ���" << endl;
    cout << ">> ";
    cin >> orderId;

    pickUp.updatePickUpStatus(orderId);
}
Inventory& Seller::getInventory()
{
    return inventory; 
}