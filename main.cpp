#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BookNode
{
public:
    int bookID;
    string bookTitle;
    string authorName;
    bool isAvailable;

    BookNode* next;

    BookNode()
    {
        bookID = 0;
        bookTitle = "";
        authorName = "";
        isAvailable = true;
        next = NULL;
    }
};

class Library
{
private:
    BookNode* firstBook;

public:
    Library()
    {
        firstBook = NULL;
    }

    void addBook()
    {
        BookNode* newBook = new BookNode();

        cout << "Enter Book ID: ";
        cin >> newBook->bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, newBook->bookTitle);

        cout << "Enter Author Name: ";
        getline(cin, newBook->authorName);

        if (firstBook == NULL)
        {
            firstBook = newBook;
        }
        else
        {
            BookNode* temp = firstBook;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newBook;
        }

        cout << "Book Added Successfully.\n";
    }

    void displayBooks()
    {
        BookNode* temp = firstBook;

        while (temp != NULL)
        {
            cout << "------------------\n";

            cout << "ID: "
                 << temp->bookID << endl;

            cout << "Title: "
                 << temp->bookTitle << endl;

            cout << "Author: "
                 << temp->authorName << endl;

            temp = temp->next;
        }
    }
};

int main()
{
    Library library;

    int choice;

    do
    {
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            library.addBook();
        }

        else if (choice == 2)
        {
            library.displayBooks();
        }

    } while (choice != 3);

    return 0;
}