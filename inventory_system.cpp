#include<iostream>
#include<string.h>
using namespace std;


class Auth{
    int id;
    string password = "admin";
    public:
        Auth(int user, string pswd){
            id = user;
            password = pswd;
        }
        int login(int user, string pswd){
            if(id == user && password == pswd)return 1;
            else return 0;
        }
        int logout(){
            return 0;
        }
};

class Product{
    string name;
    string description;
    double price;
    int quantity;
    public:
        int prnum;
        static int count;
        Product(){}
        void product(string n, string d, double p, int q){
            name = n;
            description = d;
            price = p;
            quantity = q;
            count += 1;
            prnum = count;
        }
        void rename(string n){name = n;}
        void updateDescription(string d){description = d;}
        void updatePrice(double p){price = p;}
        void updateQty(int q){quantity += q;}
        void displaySummary(){
            cout<<"\tName : "<<name<<" Qty : "<<quantity<<endl;
        }
        
        void displayProduct(){
            cout<<"\n\t----------------------"<<endl;
            cout<<"\t  Name  : "<<name<<endl;
            cout<<"\t  Desc. : "<<description<<endl;
            cout<<"\t  Price : "<<price<<" Rupee/-"<<endl;
            cout<<"\t  Qty.  : "<<quantity<<endl;
            cout<<"\t  P.no. : "<<prnum<<endl;
        }
        int searchProduct(string n, int d = 0){
            if(name.find(n)<= name.length() || description.find(n) <= description.length()){
                if(d)displayProduct();
                return prnum;
            }
            else return 0;
        }
};
int Product::count=0;

Product inv[10];

class inventory{
    public:
        int list(int summary = 0){
            for(int i=0; i<Product::count; i++){
                if(summary)inv[i].displaySummary();
                else inv[i].displayProduct();
            }
        }
        void find(string n){
            int c=0;
            for(int i=0; i<Product::count; i++){
            int temp = inv[i].searchProduct(n, 1);
            if(temp)c++;
            }
            cout<<"\n\t"<<c<<" Results Found"<<endl;
        }
        void createProduct(){
            string n, d;
            double p;
            int q;
            cout<<"\tEnter Product Name: ";
            // getline(cin,n);
            cin>>n;
            cout<<"\tEnter Product Description: ";
            // getline(cin,d);
            cin>>d;
            cout<<"\tEnter Product Price in Rupee/-: ";
            cin>>p;
            cout<<"\tEnter Product Qty: ";
            cin>>q;  
            inv[Product::count].product(n,d,p,q);
            cout<<"\tProduct Added"<<endl;
        }
        void updateProduct(){
            string n, cg = "", name;
            double p;
            cout<<"\tEnter name Of Product which you want to Update: ";cin>>name;
            int q,f;
            find(name);
            cout<<"\tEnter Product No. to be Updated: ";cin>>f;
            f -= 1;
            cout<<"\tUpdate Product Name:(y/n) ";cin>>cg;
            if(cg == "y"){
                // getline(cin,n);
                cin>>n;
                inv[f].rename(n);
                }
            cout<<"\tEnter Product Description:(y/n) ";cin>>cg;
            if(cg == "y"){
                // getline(cin,n);
                cin>>n;
                inv[f].updateDescription(n);
                }
            cout<<"\tEnter Product Price in Rupee/-:(y/n) ";cin>>cg;
            if(cg == "y"){
                cin>>p;
                inv[f].updatePrice(p);
                }
            cout<<"\tEnter Product Qty:(y/n) ";cin>>cg;
            if(cg == "y"){
                cin>>q;
                inv[f].updateQty(q);
                } 
            cout<<"\tProduct Updated"<<endl;
        }
        void delProduct(int index){
            if(index!=Product::count){
                for(int i=index-1;i<Product::count;i++){
                    inv[i] = inv[i+1];
                    inv[i].prnum -= 1;
                }
                Product::count -= 1;
            }
            else Product::count -= 1;
        }
        void deleteProduct(){
            string n, cg = "";
            int p_no;
            cout<<"\tEnter name Of Product which you want to Delete: ";
            // getline(cin,n);
            cin>>n;
            if(n.length()>0){
            find(n);
            cout<<"\tEnter Product No. to be Deleted: ";cin>>p_no;
            if(p_no <= Product::count && p_no>0){
                cout<<"\tConfirm Delete (y/n): ";cin>>cg;
                if(cg=="y")delProduct(p_no);
                cout<<"\tProduct Deleted \\/"<<endl;
            }
            else cout<<"\tProduct Not Found \\/"<<endl;
            }
            else cout<<"\tProduct Not Found \\/"<<endl;
        }
};


int main(){
    int id, auth = 0;
    string pswd;
    cout<<"\t*** Welcome to Inventory Management System ***"<<endl;
    cout<<"\tCreate new Account to Continue :-"<<endl;
    cout<<"\tCreate ID ( 0 to 9 ) of length four: ";
    cin>>id;
    cout<<"\tCreate Password of Mininum 8 Letters like (A12b@i$1): ";
    cin>>pswd;
    cout<<"\tCreating Your ID"<<endl;
    Auth admin(id, pswd);
    auth = admin.login(id, pswd);
    cout<<"\tGreat!"<<endl<<"\t***** Get Started *****"<<endl<<endl;
    int x=1,w;
    inventory obj1;
    string name;
    while(x){
        if(auth){
            cout<<"\tEnter Your Choice: "<<endl;
            cout<<"\t\t- Add New Product <press 1>"<<endl;
            cout<<"\t\t- Search Product <press 2>"<<endl;
            cout<<"\t\t- Update Product <press 3>"<<endl;
            cout<<"\t\t- delete Product <press 4>"<<endl;
            cout<<"\t\t- Summary Report <press 5>"<<endl;
            cout<<"\t\t- Logout <press 6>"<<endl;
            cout<<"\t\t- Exit <press 0>"<<endl;
            cout<<"\t\t\t>> ";
            cin>>x;
            switch (x){
                case 0:
                    cout<<"Exit...."<<endl;
                    break;
                case 1:
                    obj1.createProduct();
                    break;
                case 2:
                    cout<<"\n\tEnter name of Product: ";
                    cin>>name;
                    obj1.find(name);
                    break;
                case 3:
                    obj1.updateProduct();
                    break;
                case 4:
                    obj1.deleteProduct();
                    break;
                case 5:
                    obj1.list(1);
                    break;
                case 6:
                    auth = admin.logout();
                    cout<<"\tLogout Successfully...."<<endl;
                    break;

                default:
                    cout<<"\n\t Invalid Choice !"<<endl;
                    break;
            }
    }
    else{
            cout<<"\n\t**** Login to Continue ****"<<endl;
            cout<<"\t\tEnter your id: ";
            cin>>id;
            cout<<"\t\tPassword: ";
            cin>>pswd;
            auth = admin.login(id, pswd);
            if(auth)cout<<"\tLogin Successful..."<<endl;
            else cout<<"\tInvalid Credentials..."<<endl<<endl;
        }
    }

    return 0;
}