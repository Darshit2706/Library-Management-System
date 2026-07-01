#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    bool issued;

    Book()
    {
        id = 0;
        title = "";
        author = "";
        issued = false;
    }

    Book(int i, string t, string a)
    {
        id = i;
        title = t;
        author = a;
        issued = false;
    }
};

vector<Book> library;
void saveBooks()
{
    ofstream file("books.txt");

    for(int i = 0; i < library.size(); i++)
    {
        file << library[i].id << endl;
        file << library[i].title << endl;
        file << library[i].author << endl;
        file << library[i].issued << endl;
    }

    file.close();
}

void loadBooks()
{
    ifstream file("books.txt");

    if(!file)
        return;

    library.clear();

    Book b;

    while(file >> b.id)
    {
        file.ignore();

        getline(file, b.title);
        getline(file, b.author);

        file >> b.issued;
        file.ignore();

        library.push_back(b);
    }

    file.close();
}
// ---------------- Add Book ----------------

void addBook()
{
    int id;
    string title, author;

    cout << "\nEnter Book ID : ";
    cin >> id;
    cin.ignore();

    cout << "Enter Book Title : ";
    getline(cin, title);

    cout << "Enter Author Name : ";
    getline(cin, author);

    library.push_back(Book(id, title, author));
    saveBooks();
  
    cout << "\nBook Added Successfully.\n";
}

// ---------------- Display Books ----------------

void displayBooks()
{
    if(library.empty())
    {
        cout << "\nNo Books Available.\n";
        return;
    }

    cout << "\n========== BOOK LIST ==========\n";

    for(int i=0;i<library.size();i++)
    {
        cout << "\nBook " << i+1 << endl;

        cout << "ID : " << library[i].id << endl;
        cout << "Title : " << library[i].title << endl;
        cout << "Author : " << library[i].author << endl;

        if(library[i].issued)
            cout << "Status : Issued\n";
        else
            cout << "Status : Available\n";
    }
}

// ---------------- Search Book ----------------

void searchBook()
{
    int id;
    bool found=false;

    cout<<"\nEnter Book ID : ";
    cin>>id;

    for(int i=0;i<library.size();i++)
    {
        if(library[i].id==id)
        {
            found=true;

            cout<<"\nBook Found\n";
            cout<<"ID : "<<library[i].id<<endl;
            cout<<"Title : "<<library[i].title<<endl;
            cout<<"Author : "<<library[i].author<<endl;

            if(library[i].issued)
                cout<<"Status : Issued\n";
            else
                cout<<"Status : Available\n";

            break;
        }
    }

    if(!found)
        cout<<"\nBook Not Found.\n";
}
// ---------------- Issue Book ----------------

void issueBook()
{
    int id;
    bool found = false;

    cout << "\nEnter Book ID : ";
    cin >> id;

    for(int i = 0; i < library.size(); i++)
    {
        if(library[i].id == id)
        {
            found = true;

            if(library[i].issued)
            {
                cout << "\nBook is already issued.\n";
            }
            else
            {
                library[i].issued = true;
                saveBooks();
                cout << "\nBook Issued Successfully.\n";
            }

            break;
        }
    }

    if(!found)
        cout << "\nBook Not Found.\n";
}

// ---------------- Return Book ----------------

void returnBook()
{
    int id;
    bool found = false;

    cout << "\nEnter Book ID : ";
    cin >> id;

    for(int i = 0; i < library.size(); i++)
    {
        if(library[i].id == id)
        {
            found = true;

            if(!library[i].issued)
            {
                cout << "\nBook is already available.\n";
            }
            else
            {
                library[i].issued = false;
                saveBooks();
                cout << "\nBook Returned Successfully.\n";
            }

            break;
        }
    }

    if(!found)
        cout << "\nBook Not Found.\n";
}

// ---------------- Delete Book ----------------

void deleteBook()
{
    int id;
    bool found = false;

    cout << "\nEnter Book ID : ";
    cin >> id;

    for(int i = 0; i < library.size(); i++)
    {
        if(library[i].id == id)
        {
            library.erase(library.begin() + i);
            saveBooks();

            cout << "\nBook Deleted Successfully.\n";

            found = true;

            break;
        }
    }

    if(!found)
        cout << "\nBook Not Found.\n";
}// ---------------- Main Function ----------------

// ---------------- Main Function ----------------

int main()
{
    loadBooks();   // Program start hote hi books.txt se data load hoga

    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n     LIBRARY MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Delete Book";
        cout << "\n7. Exit";

        cout << "\n\nEnter Your Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 6:
                deleteBook();
                break;

            case 7:
                saveBooks();   // Exit se pehle final save
                cout << "\nThank You For Using Library Management System.\n";
                break;

            default:
                cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while(choice != 7);

    return 0;
}