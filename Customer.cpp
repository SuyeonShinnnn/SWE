#include "Customer.h"
#include "Auction.h"
#include "PickUp.h"
#include <string>
#include <thread>
#include <iostream>
#include <conio.h >
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
                    cout << "**������ �Ϸ�Ǿ����ϴ�**" << endl;
                }
                else {
                    cout << "**������ �����߽��ϴ�**" << endl;
                }

                cout << "**3�� �� Customer �������� ���ư��ϴ�**" << endl;
                for (int second = 3; second >= 1; second--) {
                    cout << second << endl;
                    this_thread::sleep_for(chrono::seconds(1));
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
            system("cls");
            cout << "===========���ų���===========" << endl;
            OrderManager orderManager;
            orderManager.loadOrders();
            orderManager.showOrders(id);
        }
        //�Ⱦ�����
        else if (choice == 4) 
        {
            PickUp p;

            system("cls");
            cout << "===========PickUp===========" << endl;
            cout << "1. �Ⱦ���ȸ 2. �Ⱦ�����\n";
            int number;
            cin >> number;

            //�Ⱦ� ��ȸ
            if (number == 1) {
                system("cls");
                cout << "===========�Ⱦ���ȸ===========" << endl;

                p.setId(id);
                p.displayPickupReservations("customer");
            }
            //�Ⱦ� ����
            else if (number == 2) {

                string date, productName;
                int count;

                system("cls");
                cout << "==================Product==================" << endl;
                inventory.showProducts();
                cout << "===========================================" << endl << endl;

                cout << "==================�Ⱦ�����=================" << endl;
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
            system("cls");
            Auction a;
            cout << "==================���==================" << endl;
            cout << "1. ��� ���� ����\n2. ��� �����ϱ�\n";
            cout << ">> ";

            int number;
            cin >> number;

            if (number == 1) {

                a.showAuctionResults();
            }
            if (number == 2) {
                a.setId(id);
                bool hasitem = a.showAuctionItems();
                if (hasitem) { a.joinAuction(); }
            }

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
        cout << ">> ";
        int choice;
        cin >> choice;

        //���� �ۼ�
        if (choice == 1) {
            system("cls");
            cout << "================���ų���================" << endl;
            OrderManager orderManager;
            orderManager.loadOrders();
            orderManager.showOrders(id);

            cout << "=======================================" << endl;
            writeReview();
        }
        //���� ����
        else if (choice == 2) {
            cout << "---------------------------------------" << endl;
            reviewManager.showReviews();
            cout << "---------------------------------------" << endl;
            cout << "Ȯ���� �Ϸ��ϸ� ����Ű�� �����ּ���." << endl;
            _getch();
        }
        //���ư���
        else if (choice == 3) {
            system("cls");
            break;
        }
    }
}

void Customer::writeReview() {
    string orderId, product, content;
    int score;

    cout << "�ֹ���ȣ�� �Է��ϼ���";
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

    reviewManager.addReview(orderId, product, score, content, id);
    cout << "���䰡 �ۼ��Ǿ����ϴ�." << endl;
}