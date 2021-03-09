//Jose Gabriel Valenzuela
//CSE 310
#include <iostream>
#include <cstring>
#include "defn.h"
#include <iomanip>
using namespace std;
 void inOrderPrint(bst *tree) {
     if (tree == nullptr) {
         cout << "no apps found" << endl;
         return;
     }
     inOrderPrint(tree->left);
     cout << tree->record.app_name<< endl;
     inOrderPrint(tree->right);
 }
 void insert(categories T, bst z ) {
     //data variables
     bst *parent;
     bst *y = nullptr;
     bst *x = T.root;
     //traverses the list until x is null
     while (x != nullptr) {

         y = x;
         //comp = key.keyComp(curr.data);
         //comp is 0 then it exits the loop
         if (z.record.app_name < x->record.app_name) {
         x = x->left;
        }else{ x = x->right;}
         z = *y;
     }
     if (y == nullptr){
         T.root = &z; //Tree T was empty
     }else if(z.record.app_name < y->record.app_name){
         y->left = &z;
     }else{
         y->right = &z;
     }
 }
int main ()  {
    char *input;
    string i;

    int lineNum = 0;
    int n,m; // n = cate , m = apps
    int q; // number of queries and/or updates to process
    float s,p;
    string qCommand; //query command
    //while(getline(cin, input)) {
    getline(cin,i);

    //if (!input.empty()) {
    //  if(linecount = 0) {
    n = stoi(i) * 1;
    struct categories *app_categories = (struct categories *) malloc( n * sizeof( struct categories ) );


    //allocate
    for(int x = 0; x < n; x++){
        bst *newRoot = new bst();
        getline(cin,i);
        //initializes char pointer input to address of i[0] string
        input = &i[0];
        //copys string input to app_categories
        strcpy(app_categories[x].category, input);
        app_categories[x].root = newRoot;
    }
    getline(cin,i);
    m = stoi(i) * 1;



    //intalize apps
    for(int ix = 0; ix < m; ix++) {
        //bst *node = new bst();
        app_info *rec = new app_info();
        getline(cin, i);
        //initializes char pointer input to address of i[0] string
        input = &i[0];
        strcpy(rec->category, input);
        getline(cin, i);
        //initializes char pointer input to address of i[0] string
        input = &i[0];
        strcpy(rec->app_name, input);

        getline(cin, i);
        //initializes char pointer input to address of i[0] string
        input = &i[0];
        strcpy(rec->version, input);
        getline(cin, i);
        //initializes char pointer input to address of i[0] string
        s = stof(i); //converts string to int type
        rec->size = s;
        //char units
        getline(cin, i);
        //initializes char pointer input to address of i[0] string
        input = &i[0];
        strcpy(rec->units, input);
        getline(cin, i);
        //initializes char pointer input to address of i[0] string
        p = stof(i); //converts string to int type
        rec->price = p;
    }
    //get number of queries
    getline(cin, i);
    //initializes char pointer input to address of i[0] string
    q = stof(i) * 1; //converts string to int type
    for(int j = 0 ; j < q; j++) {
        cout << "Command : " << j << endl;
        getline(cin, qCommand);
        cout << qCommand.substr(0, qCommand.find(" ")) << endl;

        if ((qCommand.substr(0, qCommand.find(" "))).compare("print-apps")){
        inOrderPrint(app_categories->root);
        }else if ((qCommand.substr(0, qCommand.find(" "))).compare("find")){
            cout << "Find max heap" << endl;

        }else{
            cout << "report" << endl;
        }
    }
    return 0;

 }
