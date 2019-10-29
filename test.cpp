#include<iostream>
#include<cstdio>
using namespace std;

// int main() {
//     // char s,ch[50] /*"-333x-2y+0z"*/;
//     // int c;
//     // cout<<"enter the number of the variables: ";
//     // cin>>c;
//     // int cj[c];
//     // cout<<"enter the expression: ";
//     // cin>>ch;
//     // for(int i=0, count=0; i<c; i++){

//     //     sscanf((ch+i), "%d%c", (cj+i), &s);

//     // }
//     // for(int i=0; i<c;i++)
//     //     cout<<cj[i];

//     // cin>>ch;
//     // int x,y,z;
//     // sscanf(ch, "%d%c%d%c%d%c", &x,&s,&y,&s,&z,&s);
//     // cout<<x<<" "<<y<<" "<<z<<endl;
//     int arr[10] = {1,2,3,4,5,6,7};
//     cout<<arr[0]<<endl;
//     return 0;
// }

class base{
    public: 
        virtual void print(int) = 0;
        virtual void print(char) = 0;
        void implement(){
            print(1);
            print('c');
        }
};

class d1 : public base{
    public:
        void print(int x){
            cout<<"derived1--->>" << x<< "\n";
        }
        void print(char c){
            cout<<"character in derived\n";
        }
};
class d2 : public base{
    public:
        void print(int x){
            cout<<"derived2\n";
        }
        void print(char c){
            cout<<"character in derived2\n";
        }
};

int main() {
    d1 p1;
    d2 p2;
    p1.implement();
    p2.implement();
    return 0;
}