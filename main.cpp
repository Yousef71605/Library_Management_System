#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class Stack
{
private:
    string books[100];

    int top;

public:
    Stack()
    {
        top = -1;
    }

    void push(string book)
    {
        if (top < 99)
        {
            top++;

            books[top] = book;
        }
    }
};
class Queue
{
private:
    string books[100];

    int front;

    int rear;

public:
    Queue()
    {
        front = 0;

        rear = -1;
    }

    void enqueue(string book)
    {
        if (rear < 99)
        {
            rear++;

            books[rear] = book;
        }
    }
};
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
class LibraryUser
{
public:
    string username;
    string password;

    string borrowedBooks[10];

    int borrowedCount;

    LibraryUser()
    {
        borrowedCount = 0;
    }
};

class Library
{
private:
    BookNode* firstBook;
    BookTreeNode* bookTreeRoot;
    int totalBooks;

int sortedBookIDs[100];
LibraryUser users[100];

int totalUsers;

Stack recentlyAddedBooks;

Queue borrowedBooksQueue;

public:
    Library()
    {
        firstBook = NULL;
        bookTreeRoot = NULL;
        totalBooks=0;
        totalUsers = 0;
        loadUsersFromFile();


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
        recentlyAddedBooks.push(newBook->bookTitle);
        saveBooksToFile();
        cout << "Book Added Successfully.\n";
    }
void deleteBook()
{
    int id;

    cout << "Enter Book ID: ";

    cin >> id;

    if (firstBook == NULL)
    {
        cout << "No Books Found."
             << endl;

        return;
    }

    if (firstBook->bookID == id)
    {
        BookNode* del = firstBook;

        firstBook = firstBook->next;

        delete del;

        saveBooksToFile();

        cout << "Book Deleted Successfully."
             << endl;

        return;
    }

    BookNode* temp = firstBook;

    while (temp->next != NULL
           &&
           temp->next->bookID != id)
    {
        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        cout << "Book Not Found."
             << endl;

        return;
    }

    BookNode* del = temp->next;

    temp->next = temp->next->next;

    delete del;

    saveBooksToFile();

    cout << "Book Deleted Successfully."
         << endl;
}
void updateBook()
{
    int id;

    cout << "Enter Book ID: ";

    cin >> id;

    cin.ignore();

    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        if (temp->bookID == id)
        {
            cout << "Enter New Title: ";

            getline(cin,
                    temp->bookTitle);

            cout << "Enter New Author: ";

            getline(cin,
                    temp->authorName);

            saveBooksToFile();

            cout << "Book Updated Successfully."
                 << endl;

            return;
        }

        temp = temp->next;
    }

    cout << "Book Not Found."
         << endl;
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
            BookNode* temp = firstBook;

            while (temp != NULL)
            {
                if (temp->bookID == targetID)
                {
                    cout << "------------------"
                         << endl;

                    cout << "Book ID: "
                         << temp->bookID
                         << endl;

                    cout << "Title: "
                         << temp->bookTitle
                         << endl;

                    cout << "Author: "
                         << temp->authorName
                         << endl;

                    if (temp->isAvailable)
                    {
                        cout << "Status: Available"
                             << endl;
                    }
                    else
                    {
                        cout << "Status: Borrowed"
                             << endl;
                    }

                    return;
                }

                temp = temp->next;
            }
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

    cout << "Book not found."
         << endl;
}
void searchBookByTitle()
{
    string keyword;

    cin.ignore();

    cout << "Enter Book Title: ";

    getline(cin, keyword);

    keyword = convertToLower(keyword);

    bool found = false;

    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        string title =
        convertToLower(
        temp->bookTitle);

        if (title.find(keyword)
            != string::npos)
        {
            cout << "------------------"
                 << endl;

            cout << "Book ID: "
                 << temp->bookID
                 << endl;

            cout << "Title: "
                 << temp->bookTitle
                 << endl;

            cout << "Author: "
                 << temp->authorName
                 << endl;

            if (temp->isAvailable)
            {
                cout << "Status: Available"
                     << endl;
            }
            else
            {
                cout << "Status: Borrowed"
                     << endl;
            }

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
string convertToLower(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        text[i] = tolower(text[i]);
    }

    return text;
}
void createUserAccount()
{
    cout << "Enter Username: ";

    cin.ignore();

    getline(cin,
            users[totalUsers].username);

    cout << "Enter Password: ";

    getline(cin,
            users[totalUsers].password);

    totalUsers++;
    saveUsersToFile();

    cout << "Account Created Successfully."
         << endl;
}
int loginUser()
{
    string username;
    string password;

    cout << "Enter Username: ";

    cin >> username;

    cout << "Enter Password: ";

    cin >> password;

    for (int i = 0; i < totalUsers; i++)
    {
        if (users[i].username == username
            &&
            users[i].password == password)
        {
            cout << "Login Successful."
                 << endl;

            return i;
        }
    }

    cout << "Invalid Username or Password."
         << endl;

    return -1;
}
void borrowBook(int userIndex)
{
    int id;

    cout << "Enter Book ID: ";

    cin >> id;

    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        if (temp->bookID == id)
        {
            if (temp->isAvailable)
            {
                temp->isAvailable = false;
                saveBooksToFile();

                users[userIndex]
                .borrowedBooks[
                users[userIndex]
                .borrowedCount]
                = temp->bookTitle;

                users[userIndex]
                .borrowedCount++;

                borrowedBooksQueue.enqueue(
                temp->bookTitle);

                cout << "Book Borrowed Successfully."
                     << endl;
            }

            else
            {
                cout << "Book Already Borrowed."
                     << endl;
            }

            return;
        }

        temp = temp->next;
    }

    cout << "Book Not Found."
         << endl;
}void returnBook()
{
    int id;

    cout << "Enter Book ID: ";

    cin >> id;

    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        if (temp->bookID == id)
        {
            temp->isAvailable = true;
            saveBooksToFile();
            cout << "Book Returned Successfully."
                 << endl;

            return;
        }

        temp = temp->next;
    }

    cout << "Book Not Found."
         << endl;
}
void changeUserPassword(int userIndex)
{
    cout << "Enter New Password: ";

    cin >> users[userIndex].password;
    saveUsersToFile();

    cout << "Password Changed Successfully."
         << endl;
}
void saveBooksToFile()
{
    ofstream file("books.txt");

    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        file << temp->bookID << ",";
        file << temp->bookTitle << ",";
        file << temp->authorName << ",";
        file << temp->isAvailable
             << endl;

        temp = temp->next;
    }

    file.close();
}
void loadUsersFromFile()
{
    ifstream file("users.txt");

    if (!file)
    {
        return;
    }

    while (true)
    {
        getline(file,
                users[totalUsers].username,
                ',');

        if (file.fail())
        {
            break;
        }

        getline(file,
                users[totalUsers].password);

        totalUsers++;
    }

    file.close();
}
void saveUsersToFile()
{
    ofstream file("users.txt");

    for (int i = 0; i < totalUsers; i++)
    {
        file << users[i].username
             << ",";

        file << users[i].password
             << endl;
    }

    file.close();
}
};


int main()
{
    Library library;

    int mainChoice;

    do
    {
        cout << "========================"
             << endl;

        cout << "Library Management System"
             << endl;

        cout << "========================"
             << endl;

        cout << "1. Admin"
             << endl;

        cout << "2. User"
             << endl;

        cout << "3. Back"
             << endl;

        cout << "Enter Choice: ";

        cin >> mainChoice;

        // ================= ADMIN =================

        if (mainChoice == 1)
        {
            int adminChoice;

            do
            {
                cout << "========================"
                     << endl;

                cout << "Admin Menu"
                     << endl;

                cout << "========================"
                     << endl;

                cout << "1. Add Book"
                     << endl;

                cout << "2. Delete Book"
                     << endl;

                cout << "3. Update Book"
                     << endl;

                cout << "4. Display Books"
                     << endl;

                cout << "5. Back"
                     << endl;

                cout << "Enter Choice: ";

                cin >> adminChoice;

                if (adminChoice == 1)
                {
                    library.addBook();
                }

                else if (adminChoice == 2)
                {
                    library.deleteBook();
                }

                else if (adminChoice == 3)
                {
                    library.updateBook();
                }

                else if (adminChoice == 4)
                {
                    library.displayBooks();
                }

            } while (adminChoice != 5);
        }

        // ================= USER =================

        else if (mainChoice == 2)
        {
            int userMenuChoice;

            do
            {
                cout << "========================"
                     << endl;

                cout << "User Menu"
                     << endl;

                cout << "========================"
                     << endl;

                cout << "1. Create Account"
                     << endl;

                cout << "2. Login"
                     << endl;

                cout << "3. Back"
                     << endl;

                cout << "Enter Choice: ";

                cin >> userMenuChoice;

                // CREATE ACCOUNT

                if (userMenuChoice == 1)
                {
                    library.createUserAccount();
                }

                // LOGIN

                else if (userMenuChoice == 2)
                {
                    int userIndex =
                    library.loginUser();

                    if (userIndex != -1)
                    {
                        int userChoice;

                        do
                        {
                            cout << "========================"
                                 << endl;

                            cout << "User Options"
                                 << endl;

                            cout << "========================"
                                 << endl;

                            cout << "1. Display Books"
                                 << endl;

                            cout << "2. Search Book By ID"
                                 << endl;

                            cout << "3. Search Book By Title"
                                 << endl;

                            cout << "4. Borrow Book"
                                 << endl;

                            cout << "5. Return Book"
                                 << endl;

                            cout << "6. Change Password"
                                 << endl;

                            cout << "7. Logout"
                                 << endl;

                            cout << "Enter Choice: ";

                            cin >> userChoice;

                            if (userChoice == 1)
                            {
                                library.displayBooks();
                            }

                            else if (userChoice == 2)
                            {
                                library.searchBookByID();
                            }

                            else if (userChoice == 3)
                            {
                                library.searchBookByTitle();
                            }

                            else if (userChoice == 4)
                            {
                                library.borrowBook(userIndex);
                            }

                            else if (userChoice == 5)
                            {
                                library.returnBook();
                            }

                            else if (userChoice == 6)
                            {
                                library.changeUserPassword(userIndex);
                            }

                        } while (userChoice != 7);
                    }
                }

            } while (userMenuChoice != 3);
        }

    } while (mainChoice != 3);

    return 0;
}