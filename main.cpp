#include <iostream>
#include <cctype>
#include <fstream>
#include <string>

using namespace std;
class Stack
{
public:
    string books[100];

    int top;

    Stack()
    {
        top = -1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == 99;
    }

    void push(string book)
    {
        if (isFull())
        {
            cout << "Stack Overflow!"
                 << endl;

            return;
        }

        top++;

        books[top] = book;
    }

    string pop()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty."
                 << endl;

            return "";
        }

        string value = books[top];

        top--;

        return value;
    }

    void displayStack()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty."
                 << endl;

            return;
        }

        for (int i = top; i >= 0; i--)
        {
            cout << books[i]
                 << endl;
        }
    }
};
class Queue
{
public:
    string books[100];

    int front;

    int rear;

    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isEmpty()
    {
        return front == -1 || front > rear;
    }

    bool isFull()
    {
        return rear == 99;
    }

    void enqueue(string book)
    {
        if (isFull())
        {
            cout << "Queue Overflow."
                 << endl;

            return;
        }

        if (front == -1)
        {
            front = 0;
        }

        rear++;

        books[rear] = book;
    }

    string deQueue()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow."
                 << endl;

            return "";
        }

        string val = books[front];

        front++;

        if (front > rear)
        {
            front = rear = -1;
        }

        return val;
    }

    void displayQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty."
                 << endl;

            return;
        }

        for (int i = front; i <= rear; i++)
        {
            cout << books[i]
                 << endl;
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
string sortedTitles[100];
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
        loadBooksFromFile();


    }
    bool isBookIDFound(int id)
{
    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        if (temp->bookID == id)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}
bool isBookTitleFound(string title)
{
    BookNode* temp = firstBook;

    while (temp != NULL)
    {
        if (convertToLower(temp->bookTitle)
            ==
            convertToLower(title))
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}
bool containsNumber(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (isdigit(text[i]))
        {
            return true;
        }
    }

    return false;
}
bool searchInBST(BookTreeNode* node,int id)
                 
{
    if (node == NULL)
    {
        return false;
    }

    if (node->bookID == id)
    {
        return true;
    }

    if (id < node->bookID)
    {
        return searchInBST(
               node->left,
               id);
    }

    return searchInBST(
           node->right,
           id);
}
  void addBook()
{
    BookNode* newBook =
    new BookNode();
   if (totalBooks >= 100)
{
    cout << "Library is full."
         << endl;

    delete newBook;

    return;
}
    cout << "Enter Book ID: ";

    cin >> newBook->bookID;

    if (isBookIDFound(newBook->bookID))
    {
        cout << "Book ID Already Exists."
             << endl;

        delete newBook;

        return;
    }

    cin.ignore();

    cout << "Enter Book Title: ";

    getline(cin,
            newBook->bookTitle);

    if (containsNumber(
        newBook->bookTitle))
    {
        cout << "Enter Text Only."
             << endl;

        delete newBook;

        return;
    }

    if (isBookTitleFound(
        newBook->bookTitle))
    {
        cout << "Book Title Already Exists."
             << endl;

        delete newBook;

        return;
    }

    cout << "Enter Author Name: ";

    getline(cin,
            newBook->authorName);

    if (containsNumber(
        newBook->authorName))
    {
        cout << "Enter Text Only."
             << endl;

        delete newBook;

        return;
    }

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

    sortedBookIDs[totalBooks] =
    newBook->bookID;
     sortedTitles[totalBooks] =
    newBook->bookTitle;
    totalBooks++;

    recentlyAddedBooks.push(
    newBook->bookTitle);

    bookTreeRoot =
    insertIntoBST(bookTreeRoot,
                  newBook->bookID,
                  newBook->bookTitle);

    saveBooksToFile();

    cout << "Book Added Successfully."
         << endl;
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

        totalBooks--;

       
        for (int i = 0; i < totalBooks; i++)
        {
            if (sortedBookIDs[i] == id)
            {
                for (int j = i; j < totalBooks; j++)
                {
                    sortedBookIDs[j] =
                    sortedBookIDs[j + 1];
                     sortedTitles[j] =
                    sortedTitles[j + 1];
                }

                break;
            }
        }

       
        bookTreeRoot =
        deleteFromBST(bookTreeRoot, id);

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

    totalBooks--;

    
    for (int i = 0; i < totalBooks; i++)
    {
        if (sortedBookIDs[i] == id)
        {
            for (int j = i; j < totalBooks; j++)
            {
                sortedBookIDs[j] =
                sortedBookIDs[j + 1];
                sortedTitles[j] =
                    sortedTitles[j + 1];
            }

            break;
        }
    }

   
    bookTreeRoot =
    deleteFromBST(bookTreeRoot, id);

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
        updateBSTTitle(bookTreeRoot,
               id,
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
void updateBSTTitle(BookTreeNode* node,
                    int id,
                    string newTitle)
{
    if (node == NULL)
    {
        return;
    }

    if (node->bookID == id)
    {
        node->bookTitle = newTitle;
        return;
    }

    if (id < node->bookID)
    {
        updateBSTTitle(node->left,
                       id,
                       newTitle);
    }
    else
    {
        updateBSTTitle(node->right,
                       id,
                       newTitle);
    }
}
    void displayBooks()
    {
        if (firstBook == NULL)
    {
        cout << "No Books Found."
             << endl;

        return;
    }
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
void displayRecentlyAddedBooks()
{
    cout << "Recently Added Books:"
         << endl;
     if (recentlyAddedBooks.isEmpty())
    {
        cout << "No books added."
             << endl;

        return;
    }

    recentlyAddedBooks.displayStack();
}
void displayBorrowedBooks()
{
    cout << "Borrowed Books Queue:"
         << endl;
 if (borrowedBooksQueue.isEmpty())
    {
        cout << "No books borrowed."
             << endl;

        return;
    }
    borrowedBooksQueue.displayQueue();
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

     
        int temp = sortedBookIDs[i];
        sortedBookIDs[i] = sortedBookIDs[minIndex];
        sortedBookIDs[minIndex] = temp;
    }
    cout<<"Book Sorted Successfully. "<<endl;
}
void searchBookByID()
{
    int targetID;

    cout << "Enter Book ID: ";

    cin >> targetID;

    if (!searchInBST(bookTreeRoot,
                     targetID))
    {
        cout << "Book not found."
             << endl;

        return;
    }

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
void bubbleSortTitles()
{
    for (int i = 0;
         i < totalBooks - 1;
         i++)
    {
        for (int j = 0;
             j < totalBooks - i - 1;
             j++)
        {
            if (convertToLower(sortedTitles[j])
                >
                convertToLower(sortedTitles[j + 1]))
            {
                string temp =
                sortedTitles[j];

                sortedTitles[j] =
                sortedTitles[j + 1];

                sortedTitles[j + 1] =
                temp;
            }
        }
    }
}
void searchBookByTitle()
{
     bubbleSortTitles();
    string target;

    cin.ignore();

    cout << "Enter Book Title: ";

    getline(cin, target);

    target = convertToLower(target);

    int left = 0;
    int right = totalBooks - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        string middleTitle =
        convertToLower(
        sortedTitles[middle]);

        if (middleTitle == target)
        {
            BookNode* temp = firstBook;

            while (temp != NULL)
            {
                if (convertToLower(
                    temp->bookTitle)
                    == target)
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

        else if (middleTitle < target)
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
    if (totalUsers >= 100)
{
    cout << "User limit reached."
         << endl;

    return;
}
    cout << "Enter Username: ";

    cin.ignore();

    getline(cin,
            users[totalUsers].username);
            if (containsNumber(users[totalUsers].username))
{
    cout << "Enter Text Only."
         << endl;

    return;
}
if (isUsernameFound(
    users[totalUsers].username))
{
    cout << "Username Already Exists."
         << endl;

    return;
}

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
               
          if (users[userIndex].borrowedCount >= 10)
           {
          cout << "Borrow limit reached."
             << endl;

         return;
           }
              temp->isAvailable = false;
                saveBooksToFile();   
                users[userIndex]
                .borrowedBooks[
                users[userIndex]
                .borrowedCount]
                = temp->bookTitle;

                users[userIndex]
                .borrowedCount++;
               saveUsersToFile();
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
}
void returnBook(int userIndex)
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
                cout << "Book is already available."
                     << endl;

                return;
            }
        
            bool found = false;
            
            for (int i = 0; i < users[userIndex].borrowedCount; i++)
            {
                if (users[userIndex].borrowedBooks[i]
                    == temp->bookTitle)
                {
                    found = true;

                    
                    for (int j = i;
                         j < users[userIndex].borrowedCount - 1;
                         j++)
                    {
                        users[userIndex].borrowedBooks[j]
                        =
                        users[userIndex].borrowedBooks[j + 1];
                    }

                    users[userIndex].borrowedCount--;
                    saveUsersToFile();
                    break;
                }
            }

            if (!found)
            {
                cout << "This user did not borrow this book."
                     << endl;

                return;
            }
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
bool isUsernameFound(string username)
{
    for (int i = 0; i < totalUsers; i++)
    {
        if (convertToLower(users[i].username)
            ==
            convertToLower(username))
        {
            return true;
        }
    }

    return false;
}
void loadBooksFromFile()
{
    ifstream file("books.txt");

    if (!file)
    {
        return;
    }

    while (true)
    {
        BookNode* newBook =
        new BookNode();

        string availability;

        file >> newBook->bookID;

        if (file.fail())
        {
            delete newBook;

            break;
        }

        file.ignore();

        getline(file,
                newBook->bookTitle,
                ',');

        getline(file,
                newBook->authorName,
                ',');

        getline(file,
                availability);

        newBook->isAvailable =
        stoi(availability);

        sortedBookIDs[totalBooks] =
        newBook->bookID;
        sortedTitles [totalBooks] =
        newBook->bookTitle;

        totalBooks++;
        bookTreeRoot=insertIntoBST(bookTreeRoot,newBook->bookID,newBook->bookTitle);
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
    }

    file.close();
}
BookTreeNode* deleteFromBST(BookTreeNode* node, int id)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (id < node->bookID)
    {
        node->left =
        deleteFromBST(node->left, id);
    }

    else if (id > node->bookID)
    {
        node->right =
        deleteFromBST(node->right, id);
    }

    else
    {
        
        if (node->left == NULL
            &&
            node->right == NULL)
        {
            delete node;

            return NULL;
        }

       
        else if (node->left == NULL)
        {
            BookTreeNode* temp =
            node->right;

            delete node;

            return temp;
        }

        else if (node->right == NULL)
        {
            BookTreeNode* temp =
            node->left;

            delete node;

            return temp;
        }

        
        else
        {
            BookTreeNode* successor =
            node->right;

            while (successor->left != NULL)
            {
                successor =
                successor->left;
            }

            node->bookID =
            successor->bookID;

            node->bookTitle =
            successor->bookTitle;

            node->right =
            deleteFromBST(
            node->right,
            successor->bookID);
        }
    }

    return node;
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

        cout << "3. Exit"
             << endl;

        cout << "Enter Choice: ";

        cin >> mainChoice;

        // ================= ADMIN =================

        if (mainChoice == 1)
        {
            string adminPassword;

            cout << "Enter Admin Password: ";

            cin >> adminPassword;

            if (adminPassword != "library")
            {
                cout << "Wrong Password."
                     << endl;

                continue;
            }

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

                cout << "5. Sort Books By ID"
                     << endl;

                cout << "6. Display Recently Added Books"
                     << endl;

                cout << "7. Display Borrowed Books"
                     << endl;

                cout << "8. Back"
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

                else if (adminChoice == 5)
                {
                    library.selectionSortIDs();
                }

                else if (adminChoice == 6)
                {
                    library.displayRecentlyAddedBooks();
                }

                else if (adminChoice == 7)
                {
                    library.displayBorrowedBooks();
                }

            } while (adminChoice != 8);
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

                if (userMenuChoice == 1)
                {
                    library.createUserAccount();
                }

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
                                library.returnBook(userIndex);
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
