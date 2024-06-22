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
    cout << "1. 상품보기\n";
    cout << "2. 장바구니\n";
    cout << "3. 구매내역\n";
    cout << "4. 픽업예약\n";
    cout << "5. 리뷰관리\n";
    cout << "6. 경매참여\n";
    cout << "7. 로그아웃\n";
}
void Customer::handleMenu(Inventory& inventory)
{
    while (true)
    {
        showMenu();
        int choice;
        cout << ">> ";
        cin >> choice;

        //상품 보기
        if (choice == 1) 
        {
            if(inventory.showProducts())
                addToCart(inventory);
        }
        //장바구니
        else if (choice == 2) 
        {

            system("cls");
            cout << "===========장바구니===========" << endl;
            cart.showCart();
            cout << "==============================" << endl;

            cout << "1. 구매하기" << endl;
            cout << "2. 뒤로가기" << endl;
            cout << ">> ";
            int option;
            cin >> option;
            
            if (option == 1)
            {
                bool success = cart.checkout(id);

                if (success) {
                    cout << "**결제가 완료되었습니다**" << endl;
                }
                else {
                    cout << "**결제에 실패했습니다**" << endl;
                }

                cout << "**3초 후 Customer 페이지로 돌아갑니다**" << endl;
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
        //구매내역
        else if (choice == 3)
        {
            system("cls");
            cout << "===========구매내역===========" << endl;
            OrderManager orderManager;
            orderManager.loadOrders();
            orderManager.showOrders(id);
        }
        //픽업예약
        else if (choice == 4) 
        {
            PickUp p;

            system("cls");
            cout << "===========PickUp===========" << endl;
            cout << "1. 픽업조회 2. 픽업예약\n";
            int number;
            cin >> number;

            //픽업 조회
            if (number == 1) {
                system("cls");
                cout << "===========픽업조회===========" << endl;

                p.setId(id);
                p.displayPickupReservations("customer");
            }
            //픽업 예약
            else if (number == 2) {

                string date, productName;
                int count;

                system("cls");
                cout << "==================Product==================" << endl;
                inventory.showProducts();
                cout << "===========================================" << endl << endl;

                cout << "==================픽업예약=================" << endl;
                cout << "상품명을 입력하세요" << endl;
                cout << ">> ";
                cin >> productName;

                cout << "수량을 입력하세요" << endl;
                cout << ">> ";
                cin >> count;

                cout << "픽업날짜를 입력하세요" << endl;
                cout << ">> ";
                cin >> date;

                p.reservePickUp(date, productName, count, id);
            }
        }
        //리뷰관리
        else if (choice == 5)
        {
            manageReviews();
        }
        //경매참여
        else if (choice == 6) 
        {
            system("cls");
            Auction a;
            cout << "==================경매==================" << endl;
            cout << "1. 경매 내역 보기\n2. 경매 참여하기\n";
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
        //로그아웃
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

    cout << "상품명을 입력하세요: ";
    cin >> productName;

    //입력한 상품 가격
    double price = inventory.searchProductPrice(productName);


    if (price != 0)
    {
        cout << "수량을 입력하세요: ";
        cin >> quantity;

        double totalPrice = price * quantity;

        system("cls");
        cout << "================Prodcut================" << endl;
        cout << "상품: " << productName;
        cout << " 수량: " << quantity;
        cout << " 총 가격: " << totalPrice << endl;
        cout << "=======================================" << endl;
        cout << "1. 장바구니에 추가\n";
        cout << "2. 바로 결제\n";

        int option;
        cout << ">> ";
        cin >> option;

        //장바구니 추가
        if (option == 1) {
            cart.addItem(CartItem(productName, quantity, totalPrice));

            system("cls");
            cout << "**장바구니에 상품이 추가되었습니다**" << endl;
        }
        //결제
        else if (option == 2) {
            cart.addItem(CartItem(productName, quantity, totalPrice));
            bool success = cart.checkout(id);

            if (success) {
                system("cls");
                cout << "**결제가 완료되었습니다**" << endl;
            }
            else {
                system("cls");
                cout << "**결제에 실패했습니다**" << endl;
            }
        }
    }
}

void Customer::manageReviews() {
    while (true) 
    {
        system("cls");
        cout << "================Review================" << endl;
        cout << "1. 리뷰 작성\n";
        cout << "2. 리뷰 보기\n";
        cout << "3. 돌아가기\n";
        cout << ">> ";
        int choice;
        cin >> choice;

        //리뷰 작성
        if (choice == 1) {
            system("cls");
            cout << "================구매내역================" << endl;
            OrderManager orderManager;
            orderManager.loadOrders();
            orderManager.showOrders(id);

            cout << "=======================================" << endl;
            writeReview();
        }
        //리뷰 보기
        else if (choice == 2) {
            cout << "---------------------------------------" << endl;
            reviewManager.showReviews();
            cout << "---------------------------------------" << endl;
            cout << "확인을 완료하면 엔터키를 눌러주세요." << endl;
            _getch();
        }
        //돌아가기
        else if (choice == 3) {
            system("cls");
            break;
        }
    }
}

void Customer::writeReview() {
    string orderId, product, content;
    int score;

    cout << "주문번호를 입력하세요";
    cout << ">> ";
    cin >> orderId;

    cout << "상품명을 입력하세요";
    cout << ">> ";
    cin >> product;

    cout << "별점을 입력하세요 (1-5)";
    cout << ">> ";
    cin >> score;

    cout << "내용을 입력하세요";
    cout << ">> ";
    cin.ignore();
    getline(cin, content);

    reviewManager.addReview(orderId, product, score, content, id);
    cout << "리뷰가 작성되었습니다." << endl;
}