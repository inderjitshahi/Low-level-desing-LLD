#include<memory>
#include<iostream>
using namespace std;

// smart pointers are defined just because we want heap access but auto memory management right
int main(){

// ------------------------------------------- Unique Pointer ------------------------------------------------//
unique_ptr<int> up1=make_unique<int>(42);
cout<<up1.get()<<endl; // prints the address of the managed integer
cout<<*up1<<endl; // prints 42, the value of the managed integer
// unique_ptr<int> up2=up1; // Error: cannot copy unique_ptr
unique_ptr<int> up2=move(up1); // Transfer ownership from up1 to up2, valid
cout<<*up2<<"\n";
*up2=100;
cout<<*up2<<endl; // prints 100

// ------------------------------------------- Shared Pointer ------------------------------------------------//
shared_ptr<int> sp1=make_shared<int>(55);
cout<<sp1.get()<<endl; // prints the address of the managed integer
cout<<*sp1<<endl; // prints 55, the value of the managed integer
shared_ptr<int> sp2=sp1; // Valid: shared_ptr can be copied, both sp1 and sp2 share ownership
cout<<*sp2<<endl; // prints 55
*sp2=200;
cout<<*sp1<<endl; // prints 200, since both point to the same integer
cout<<"Reference Count: "<<sp1.use_count()<<endl; // prints 2


//     unique_ptr<Car> car = make_unique<Car>();
return 0;
}