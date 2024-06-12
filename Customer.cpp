#include "Customer.h"
#include "Auction.h"
#include "PickUp.h"
#include <string>
#include <thread>
#include <iostream>
using namespace std;

Customer::Customer(string id, string password, Inventory& inv)
    : User(id, password), cart(inv) {}

void Customer::showMenu() const
{
    cout << "===========Customer===========" << endl;
    cout << "1. ��ǰ����\n";
    cout << "2. ��ٱ���\n";
    cout << "3. ���ų���\n";
    cout << "4. �Ⱦ�����\n";
    cout << "5. �������\n";
    cout << "6. �������\n";
    cout << "7. �α׾ƿ�\n";
}
void Customer::handleMenu(Inventory& inventory)
{
    while (true)
    {
        showMenu();
        int choice;
        cout << ">> ";
        cin >> choice;

        //��ǰ ����
        if (choice == 1) 
        {
            if(inventory.showProducts())
                addToCart(inventory);
        }
        //��ٱ���
        else if (choice == 2) 
        {

            system("cls");
            cout << "===========��ٱ���===========" << endl;
            cart.showCart();
            cout << "==============================" << endl;

            cout << "1. �����ϱ�" << endl;
            cout << "2. �ڷΰ���" << endl;
            cout << ">> ";
            int option;
            cin >> option;
            
            if (option == 1)
            {
                bool success = cart.checkout(id);

                if (success) {
                    cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
                }
                else {
                    cout << "������ �����߽��ϴ�." << endl;
                }

                cout << "���� �Ϸ�" << endl;
                cout << "3�� �� Customer �������� ���ư��ϴ�." << endl;
                for (int second = 3; second >= 1; second--) {
                    this_thread::sleep_for(chrono::seconds(1));
                    cout << second << endl;
                }
                system("cls");
            }
            else if (option == 2)
            {
                system("cls");
            }
        }
        //���ų���
        else if (choice == 3)
        {
            OrderManager orderManager;
            orderManager.loadOrders();
            showOrders();
        }
        //�Ⱦ�����
        else if (choice == 4) 
        {
            PickUp p;

            cout << "1. �Ⱦ���ȸ 2. �Ⱦ�����\n";
            int number;
            cin >> number;

            //�Ⱦ� ��ȸ
            if (number == 1) {
                p.setId(id);
                p.displayPickupReservations();
            }
            //�Ⱦ� ����
            else if (number == 2) {

                string date, productName;
                int count;

                inventory.showProducts();

                cout << "��ǰ���� �Է��ϼ���" << endl;
                cout << ">> ";
                cin >> productName;

                cout << "������ �Է��ϼ���" << endl;
                cout << ">> ";
                cin >> count;

                cout << "�Ⱦ���¥�� �Է��ϼ���" << endl;
                cout << ">> ";
                cin >> date;

                p.reservePickUp(date, productName, count, id);
            }
        }
        //�������
        else if (choice == 5)
        {
            manageReviews();
        }
        //�������
        else if (choice == 6) 
        {
            Auction auction;
            auction.joinAuction();
        }
        //�α׾ƿ�
        else if (choice == 7) 
        {
            system("cls");
            break;
        }
    }
}

ShoppingCart& Customer::getCart()
{
    return cart; 
}

void Customer::showOrders() const {
    orderManager.showOrders(id);
}

void Customer::addToCart(Inventory& inventory) {

    string productName;
    int quantity;

    cout << "��ǰ���� �Է��ϼ���: ";
    cin >> productName;

    //�Է��� ��ǰ ����
    double price = inventory.searchProductPrice(productName);


    if (price != 0)
    {
        cout << "������ �Է��ϼ���: ";
        cin >> quantity;

        double totalPrice = price * quantity;

        system("cls");
        cout << "================Prodcut================" << endl;
        cout << "��ǰ: " << productName;
        cout << " ����: " << quantity;
        cout << " �� ����: " << totalPrice << endl;
        cout << "=======================================" << endl;
        cout << "1. ��ٱ��Ͽ� �߰�\n";
        cout << "2. �ٷ� ����\n";

        int option;
        cout << ">> ";
        cin >> option;

        //��ٱ��� �߰�
        if (option == 1) {
            cart.addItem(CartItem(productName, quantity, totalPrice));

            system("cls");
            cout << "**��ٱ��Ͽ� ��ǰ�� �߰��Ǿ����ϴ�**" << endl;
        }
        //����
        else if (option == 2) {
            cart.addItem(CartItem(productName, quantity, totalPrice));
            bool success = cart.checkout(id);

            if (success) {
                system("cls");
                cout << "**������ �Ϸ�Ǿ����ϴ�**" << endl;
            }
            else {
                system("cls");
                cout << "**������ �����߽��ϴ�**" << endl;
            }
        }
    }
}

void Customer::manageReviews() {
    while (true) 
    {
        system("cls");
        cout << "================Review================" << endl;
        cout << "1. ���� �ۼ�\n";
        cout << "2. ���� ����\n";
        cout << "3. ���ư���\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            writeReview();
        }
        else if (choice == 2) {
            reviewManager.showReviews();
        }
        else if (choice == 3) {
            break;
        }
    }
}

void Customer::writeReview() {
    string orderId, product, content;
    int score;

    system("cls");
    cout << "================Reciept================" << endl;
    cout << "������ ��ȣ�� �Է��ϼ���";
    cout << ">> ";
    cin >> orderId;

    cout << "��ǰ���� �Է��ϼ���";
    cout << ">> ";
    cin >> product;

    cout << "������ �Է��ϼ��� (1-5)";
    cout << ">> ";
    cin >> score;

    cout << "������ �Է��ϼ���";
    cout << ">> ";
    cin.ignore();
    getline(cin, content);

    reviewManager.addReview(orderId, product, score, content);
    cout << "���䰡 �ۼ��Ǿ����ϴ�." << endl;
}