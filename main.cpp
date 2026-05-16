#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class BookTreeNode
{
public:
    int bookID;
    string bookTitle;

    BookTreeNode* left;
    BookTreeNode* right;

    BookTreeNode(int id, string title)
    {
        bookID = id;
        bookTitle = title;

        left = NULL;
        right = NULL;
    }
};
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
    BookTreeNode* bookTreeRoot;
    int totalBooks;

int sortedBookIDs[100];

public:
    Library()
    {
        firstBook = NULL;
        bookTreeRoot = NULL;
        totalBooks=0;
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
sortedBookIDs[totalBooks] = newBook->bookID;

totalBooks++;
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
    BookTreeNode* insertIntoBST(BookTreeNode* node,
                            int id,
                            string title)
{
    if (node == NULL)
    {
        return new BookTreeNode(id, title);
    }

    if (id < node->bookID)
    {
        node->left =
        insertIntoBST(node->left,
                      id,
                      title);
    }
    else
    {
        node->right =
        insertIntoBST(node->right,
                      id,
                      title);
    }

    return node;
}
void selectionSortIDs()
{
    for (int i = 0; i < totalBooks - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < totalBooks; j++)
        {
            if (sortedBookIDs[j] <
                sortedBookIDs[minIndex])
            {
                minIndex = j;
            }
        }

        swap(sortedBookIDs[i],
             sortedBookIDs[minIndex]);
    }
}
void searchBookByID()
{
    selectionSortIDs();

    int targetID;

    cout << "Enter Book ID: ";

    cin >> targetID;

    int left = 0;
    int right = totalBooks - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (sortedBookIDs[middle] == targetID)
        {
            cout << "Book Found." << endl;

            return;
        }

        else if (sortedBookIDs[middle] < targetID)
        {
            left = middle + 1;
        }

        else
        {
            right = middle - 1;
        }
    }

    cout << "Book not found." << endl;
}
void searchBookByTitle()
{
    string keyword;

    cin.ignore();

    cout << "Enter Book Title: ";

    getline(cin, keyword);

    bool found = false;

    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        if (temp->bookTitle.find(keyword)
            != string::npos)
        {
            cout << temp->bookTitle
                 << endl;

            found = true;
        }

        temp = temp->next;
    }

    if (!found)
    {
        cout << "Book not found."
             << endl;
    }
}
};

int main()
{
    Library library;

    int choice;

    do
    {
        cout << "====================" << endl;
        cout << "Library Management System" << endl;
        cout << "====================" << endl;

        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Search Book By ID" << endl;
        cout << "4. Search Book By Title" << endl;
        cout << "5. Exit" << endl;

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

        else if (choice == 3)
        {
            library.searchBookByID();
        }

        else if (choice == 4)
        {
            library.searchBookByTitle();
        }

        else if (choice == 5)
        {
            cout << "Exiting Program..." << endl;
        }

        else
        {
            cout << "Invalid Choice." << endl;
        }

    } while (choice != 5);

    return 0;
}