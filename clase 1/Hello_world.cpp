#include <iostream>
#include <string>
using namespace std;

int main(){
    string nombre;
    cout<<"Dame tu nombre: "<<endl;
    cin>>nombre;
    cout<<"Hi! "<<nombre<<", your name has "<<nombre.length()<<" characters";
    return 0;
}


