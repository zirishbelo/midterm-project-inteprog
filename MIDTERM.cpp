#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_BOOKS = 100; 
const string CATEGORIES[] = {"Fiction", "Non-fiction"};

class Book
{
private:
  string ID, ISBN, title, author, edition, publication, category;

public:
  Book() {} 

  Book(string id, string isbn, string t, string a, string e, string p, string c)
      : ID(id), ISBN(isbn), title(t), author(a), edition(e), publication(p), category(c) {}

  string getID() const { return ID; }
  string getCategory() const { return category; }

  void editBook(string isbn, string t, string a, string e, string p, string c)
  {
    ISBN = isbn;
    title = t;
    author = a;
    edition = e;
    publication = p;
    category = c;
  }

  void displayBook() const
  {
    cout << left << setw(10) << ID << setw(15) << ISBN << setw(25) << title
         << setw(20) << author << setw(15) << edition << setw(25) << publication
         << setw(15) << category << endl;
  }
};

class Library
{
private:
  Book books[MAX_BOOKS];
  int bookCount = 0;

  bool isCategoryValid(string cat)
  {
    for (char &c : cat)
      c = tolower(c); // Convert input to lowercase manually
    for (string validCat : CATEGORIES)
    {
      string lowerValidCat = validCat;
      for (char &c : lowerValidCat)
        c = tolower(c); // Convert valid category to lowercase manually
      if (lowerValidCat == cat || (cat == "nonfiction" && lowerValidCat == "non-fiction"))
        return true;
    }
    return false;
  }

  int findBookID(string id)
  {
    for (char &c : id)
      c = toupper(c); // Convert to uppercase manually
    for (int i = 0; i < bookCount; i++)
    {
      string bookID = books[i].getID();
      for (char &c : bookID)
        c = toupper(c); // Convert to uppercase manually
      if (bookID == id)
        return i;
    }
    return -1;
  }

  bool isValidISBN(const string &isbn)
  {
    int digitCount = 0;
    for (char c : isbn)
    {
      if (isdigit(c))
        digitCount++;
      else if (c != '-')
        return false;
    }
    return digitCount == 13;
  }

  void trim(string &input)
  {
    input.erase(0, input.find_first_not_of(" \t"));
    input.erase(input.find_last_not_of(" \t") + 1); 
  }

  bool isNonEmpty(const string &input)
  {
    return !input.empty();
  }

public:
  static bool isValidMenuChoice(int choice)
  {
    return choice >= 1 && choice <= 7;
  }

  void addBook()
  {
    if (bookCount >= MAX_BOOKS)
    {
      cout << "Library is full!\n";
      return;
    }

    string category;
    do
    {
      cout << "Enter Category (Fiction/Non-fiction): ";
      cin >> category;
      trim(category);
      for (char &c : category)
        c = tolower(c); 

      if (category == "nonfiction")
        category = "Non-fiction";

      if (!isCategoryValid(category))
      {
        cout << "Category not found! Please try again.\n";
      }
    } while (!isCategoryValid(category));

    string id, isbn, title, author, edition, publication;
    do
    {
      cout << "Enter Book ID: ";
      cin >> id;
      for (char &c : id)
        c = toupper(c); // Convert to uppercase manually

      if (findBookID(id) != -1)
      {
        cout << "Duplicate ID! Please enter a different ID.\n";
      }
    } while (findBookID(id) != -1);

    do
    {
      cout << "Enter ISBN (13 digits):";
      cin >> isbn;
      trim(isbn); // Trim spaces
      if (!isValidISBN(isbn))
      {
        cout << "Invalid ISBN! Must contain exactly 13 numeric digits.\n";
      }
    } while (!isValidISBN(isbn));

    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, title);
    if (!isNonEmpty(title))
    {
      cout << "Title cannot be empty!\n";
      return;
    }

    cout << "Enter Author: ";
    getline(cin, author);
    if (!isNonEmpty(author))
    {
      cout << "Author cannot be empty!\n";
      return;
    }

    cout << "Enter Edition: ";
    getline(cin, edition);
    if (!isNonEmpty(edition))
    {
      cout << "Edition cannot be empty!\n";
      return;
    }

    cout << "Enter Publication: ";
    getline(cin, publication);
    if (!isNonEmpty(publication))
    {
      cout << "Publication cannot be empty!\n";
      return;
    }

    books[bookCount++] = Book(id, isbn, title, author, edition, publication, category);
    cout << "Book added successfully!\n";
    system("pause");
  }

  void editBook()
  {
    if (bookCount == 0)
    {
      cout << "There are no books in the inventory!\n";
      system("pause");
      return;
    }

    string id;
    cout << "Enter Book ID to Edit: ";
    cin >> id;
    for (char &c : id)
      c = toupper(c); // Convert to uppercase manually

    int index = findBookID(id);
    if (index == -1)
    {
      cout << "Book not found!\n";
      system("pause");
      return;
    }

    string isbn, title, author, edition, publication, category;
    do
    {
      cout << "Enter New ISBN (13 digits, hyphens allowed): ";
      cin >> isbn;
      trim(isbn); // Trim spaces
      if (!isValidISBN(isbn))
      {
        cout << "Invalid ISBN! Must contain exactly 13 numeric digits (hyphens allowed).\n";
      }
    } while (!isValidISBN(isbn));

    cout << "Enter New Title: ";
    cin.ignore();
    getline(cin, title);
    if (!isNonEmpty(title))
    {
      cout << "Title cannot be empty!\n";
      system("pause");
      return;
    }

    cout << "Enter New Author: ";
    getline(cin, author);
    if (!isNonEmpty(author))
    {
      cout << "Author cannot be empty!\n";
      system("pause");
      return;
    }

    cout << "Enter New Edition: ";
    getline(cin, edition);
    if (!isNonEmpty(edition))
    {
      cout << "Edition cannot be empty!\n";
      system("pause");
      return;
    }

    cout << "Enter New Publication: ";
    getline(cin, publication);
    if (!isNonEmpty(publication))
    {
      cout << "Publication cannot be empty!\n";
      system("pause");
      return;
    }

    cout << "Enter New Category (Fiction/Non-fiction): ";
    cin >> category;
    for (char &c : category)
      c = tolower(c);

    if (category == "nonfiction")
      category = "Non-fiction";

    if (!isCategoryValid(category))
    {
      cout << "Category not found!\n";
      system("pause");
      return;
    }

    books[index].editBook(isbn, title, author, edition, publication, category);
    cout << "Book edited successfully!\n";
    system("pause");
  }

  void searchBook()
  {
    if (bookCount == 0)
    {
      cout << "There are no books in the inventory!\n";
      system("pause");
      return;
    }

    string id;
    cout << "Enter Book ID to Search: ";
    cin >> id;
    for (char &c : id)
      c = toupper(c); 

    int index = findBookID(id);
    if (index == -1)
    {
      cout << "Book not found!\n";
    }
    else
    {
      cout << left << setw(10) << "ID" << setw(15) << "ISBN" << setw(25) << "Title"
           << setw(20) << "Author" << setw(15) << "Edition" << setw(25) << "Publication"
           << setw(15) << "Category" << endl;
      cout << string(125, '-') << endl;
      books[index].displayBook();
    }
    system("pause");
  }

  void deleteBook()
  {
    string id;
    cout << "Enter Book ID to Delete: ";
    cin >> id;
    for (char &c : id)
      c = toupper(c);

    int index = findBookID(id);
    if (index == -1)
    {
      cout << "Book not found!\n";
      system("pause");
      return;
    }

    books[index].displayBook();
    cout << "Do you want to delete this book? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y')
    {
      for (int i = index; i < bookCount - 1; i++)
      {
        books[i] = books[i + 1];
      }
      bookCount--;
      cout << "Book deleted successfully!\n";
    }
    system("pause");
  }

  void viewBooksByCategory()
  {
    string category;
    do
    {
      cout << "Enter Category (Fiction/Non-fiction): ";
      cin >> category;
      for (char &c : category)
        c = tolower(c); 

      if (category == "nonfiction")
        category = "Non-fiction"; 

      if (!isCategoryValid(category))
      {
        cout << "Category not found! Please try again.\n";
      }
    } while (!isCategoryValid(category));

    cout << left << setw(10) << "ID" << setw(15) << "ISBN" << setw(25) << "Title"
         << setw(20) << "Author" << setw(15) << "Edition" << setw(25) << "Publication"
         << setw(15) << "Category" << endl;
    cout << string(125, '-') << endl;

    bool found = false;
    for (int i = 0; i < bookCount; i++)
    {
      if (books[i].getCategory() == category)
      {
        books[i].displayBook();
        found = true;
      }
    }

    if (!found)
    {
      cout << "No books yet in this category.\n";
    }
    system("pause");
  }

  void viewAllBooks()
  {
    if (bookCount == 0)
    {
      cout << "No books available!\n";
    }
    else
    {
      cout << left << setw(10) << "ID" << setw(15) << "ISBN" << setw(25) << "Title"
           << setw(20) << "Author" << setw(15) << "Edition" << setw(25) << "Publication"
           << setw(15) << "Category" << endl;
      cout << string(125, '-') << endl;
      for (int i = 0; i < bookCount; i++)
      {
        books[i].displayBook();
      }
    }
    system("pause");
  }
};

int main()
{
  Library library;
  int choice;
  string input;

  do
  {
    cout << "\nMENU\n"
         << "1 - Add Book\n"
         << "2 - Edit Book\n"
         << "3 - Search Book\n"
         << "4 - Delete Book\n"
         << "5 - View Books by Category\n"
         << "6 - View All Books\n"
         << "7 - Exit\n"
         << "Enter your choice: ";
    cin >> input;

    if (input.length() != 1 || !isdigit(input[0]))
    {
      cout << "Invalid input. Please enter a number between 1 and 7.\n";
      continue;
    }

    choice = input[0] - '0'; // Convert char to int
    if (!Library::isValidMenuChoice(choice))
    {
      cout << "Invalid input. Please enter a number between 1 and 7.\n";
      continue;
    }

    switch (choice)
    {
    case 1: library.addBook();
      break;
    case 2: library.editBook();
      break;
    case 3: library.searchBook();
      break;
    case 4: library.deleteBook();
      break;
    case 5: library.viewBooksByCategory();
      break;
    case 6: library.viewAllBooks();
      break;
    case 7: cout << "Exiting...\n";
      break;
    default: cout << "Invalid input. Please try again.\n";
    }
  } while (choice != 7);

  return 0;
}
