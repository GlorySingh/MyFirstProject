/* Program displays a menu using queue data structure, asks for the items to be ordered, asks for the mode of dining (i.e. dine-in/takeaway),
lets the customer make changes in the bill (like deleting an item, changing the quantity, changing the dining mode) calculates the total bill,
and also offers discount on bulk orders. */
#include <iostream>
#include <string.h>
using namespace std;
 
class food_item_queue
{
public:
    char item[20];
    int sno;
    float price;
    food_item_queue* next;
    food_item_queue(char name[], int serial_no, float pr)
    {
        strcpy(item, name);
        sno = serial_no;
        price = pr;
        next = nullptr;
    }   
}*rear;
 
typedef food_item_queue menu;
 
menu *menu_insert(menu *Mfront, char name[], int sno, float pr)
{
    menu *newItem = new menu(name, sno, pr);
    if (Mfront == nullptr)
    {
        Mfront = newItem;
        rear = newItem;
        return Mfront;
    }
    rear->next = newItem;
    rear = newItem;
    return Mfront;
}
 
void display(menu *Mhead)
{
    menu *temp = Mhead;
 
    while (temp != nullptr)
    {
        cout << "\n"
             << temp->sno << ". ";
        puts(temp->item);
        cout<<"Price: Rs. "<<temp->price;
 
        temp = temp->next;
    }
}
 
class order_queue
{
public:
    int ser_no;
    int qty;
    float price;
    order_queue *next;
    order_queue(int sno, int quantity, float pr)
    {
        ser_no = sno;
        qty = quantity;
        price = pr; 
        next = nullptr;
    }
}*orear;
 
typedef order_queue orders;
 
orders* order_ins(orders* front, int ino, int quant, float pr) {
    orders* newOrder = new orders(ino, quant, pr);
    if(front == nullptr) {
        front = newOrder;
        orear = newOrder;
        return front;
    }
    orear->next = newOrder;
    orear = newOrder;
    return front;
}
 
float totalBill(orders* front) {
    float total = 0.0;
    while(front) {
                
                total += front->price*front->qty;
                
        front = front->next;
    }
    return total;
}
 
void order_display(orders* front) {
    while(front) {
        cout<<"\n"<<front->ser_no<<" "<<front->qty;
        front = front->next;
    }
}
 
orders* del_order(orders* front, int sno) {
    orders* ptr1 = front, *ptr2 = nullptr;
    if(front->ser_no == sno) {
        front = front->next;
        delete ptr1;
        return front;
    }
   
    while(ptr2) {
        ptr1 = ptr2;
        ptr2 = ptr2->next;
        if(ptr2->ser_no == sno)
            break;
    }
    orders* temp = ptr1->next;
    ptr1->next = ptr1->next->next;
    if(temp == orear)
        orear = ptr1;
    delete temp;
    return front;
}
 
int main()
{
    char mode;
    int sno, dno, quantity;
    float pric, total, gst, disc = 0.05;
    int c;
    char ch;
    orders* Ofront = nullptr;
    menu *MFront = nullptr;
    //creation of menu:
    MFront = menu_insert(MFront, "Chilli Potato", 1, 200.50);
    MFront = menu_insert(MFront, "Chicken noodles", 2, 250.00);
    MFront = menu_insert(MFront, "Dum aloo", 3, 180.66);
    MFront = menu_insert(MFront, "Kimchi fried rice", 4, 300.00);
    MFront = menu_insert(MFront, "Pepperoni pizza", 5, 340.00);
    MFront = menu_insert(MFront, "Manchurian fried rice", 6, 200.55);
    MFront = menu_insert(MFront, "Hamburger", 7, 150.65);
    MFront = menu_insert(MFront, "Chicken momos", 8, 150.67);
 
    
    do
    {
        cout << "\n*********|||||||||||MENU|||||||||||*********";
        display(MFront);
        do {
            cout<<"\nenter the item no. to be ordered: ";
            cin>>sno;
            cout<<"\nenter quantity: ";
            cin>>quantity;
            cout<<"\nenter price: Rs.";
            cin>>pric;
            Ofront = order_ins(Ofront, sno, quantity, pric);
            choice:
            cout<<"\ndo you want to add/delete ?(enter 1 to add, 2 to delete, 3 for none): ";
            cin>>c;
            if(c != 1 && c != 2 && c != 3) {
                cout<<"\nwrong choice.";
                goto choice;
            }
            if(c == 1)
                continue;
            if(c == 3)
                goto skip;
            while(c == 2) {
                cout<<"\nenter item no. to be deleted: ";
                cin>>dno;
                Ofront = del_order(Ofront, dno);
                cout<<"\n"<<dno<<" item no. deleted.";
                cout<<"\nYour order list : \n";
                order_display(Ofront);
                again:
                cout<<"\ndo you want to delete more?(1-no, 2-yes): ";
                cin>>c;
                if(c != 1 && c != 2) {
                cout<<"\nwrong choice.";
                goto again;
                }
            }
            cout<<"\ndo you want to continue?(1-yes/3-no): ";
            cin>>c;
           
        }while(c == 1);
        skip:
        cout<<"\nyour order: \n";
        order_display(Ofront);
        total = totalBill(Ofront);
        cout<<"\ntotal bill amount: Rs."<<total;
        cout<<"\nmode of dining(d=dine-in, t=takeaway, h=home delivery): ";
        cin>>mode;
        gst = 0.05*total; 
        total += gst;
        if(mode == 'h') {
            total += 50;
            cout<<"\nDelivery charges= Rs.50";
        }
        if(total >= 500) {
            total -= disc*total;
            cout<<"\ndiscount applied= 10%";
        } 
        cout<<"\nGST = Rs."<<gst;
        cout<<"\nTotal bill: Rs."<<total;
        cout << "\nenter choice to continue(y/n) : ";
         
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    return 0;
}
