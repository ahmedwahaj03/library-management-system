#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool issued;
};

class Library {
private:
    vector<Book> books;

    int findBookIndex(int id) const {
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].id == id) return static_cast<int>(i);
        }
        return -1;
    }

    void clearInput() const {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    void addBook() {
        Book book{};
        cout << "\nEnter book ID: ";
        if (!(cin >> book.id)) {
            clearInput();
            cout << "Invalid ID.\n";
            return;
        }

        if (findBookIndex(book.id) != -1) {
            cout << "A book with this ID already exists.\n";
            return;
        }

        clearInput();
        cout << "Enter title: ";
        getline(cin, book.title);
        cout << "Enter author: ";
        getline(cin, book.author);

        if (book.title.empty() || book.author.empty()) {
            cout << "Title and author cannot be empty.\n";
            return;
        }

        book.issued = false;
        books.push_back(book);
        cout << "Book added successfully.\n";
    }

    void searchBook() const {
        clearInput();
        string keyword;
        cout << "\nEnter title/author keyword: ";
        getline(cin, keyword);

        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(keyword) != string::npos ||
                book.author.find(keyword) != string::npos) {
                cout << "\nID: " << book.id
                     << "\nTitle: " << book.title
                     << "\nAuthor: " << book.author
                     << "\nStatus: " << (book.issued ? "Issued" : "Available")
                     << "\n";
                found = true;
            }
        }

        if (!found) cout << "No matching books found.\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "\nNo books in the library.\n";
            return;
        }

        cout << "\n" << left
             << setw(8) << "ID"
             << setw(32) << "Title"
             << setw(25) << "Author"
             << "Status\n";
        cout << string(75, '-') << '\n';

        for (const auto& book : books) {
            cout << left
                 << setw(8) << book.id
                 << setw(32) << book.title.substr(0, 30)
                 << setw(25) << book.author.substr(0, 23)
                 << (book.issued ? "Issued" : "Available") << '\n';
        }
    }

    void updateBook() {
        int id;
        cout << "\nEnter book ID to update: ";
        if (!(cin >> id)) {
            clearInput();
            cout << "Invalid ID.\n";
            return;
        }

        int index = findBookIndex(id);
        if (index == -1) {
            cout << "Book not found.\n";
            return;
        }

        clearInput();
        string title, author;
        cout << "Enter new title: ";
        getline(cin, title);
        cout << "Enter new author: ";
        getline(cin, author);

        if (title.empty() || author.empty()) {
            cout << "Title and author cannot be empty.\n";
            return;
        }

        books[index].title = title;
        books[index].author = author;
        cout << "Book updated successfully.\n";
    }

    void issueBook() {
        int id;
        cout << "\nEnter book ID to issue: ";
        if (!(cin >> id)) {
            clearInput();
            cout << "Invalid ID.\n";
            return;
        }

        int index = findBookIndex(id);
        if (index == -1) {
            cout << "Book not found.\n";
        } else if (books[index].issued) {
            cout << "Book is already issued.\n";
        } else {
            books[index].issued = true;
            cout << "Book issued successfully.\n";
        }
    }

    void returnBook() {
        int id;
        cout << "\nEnter book ID to return: ";
        if (!(cin >> id)) {
            clearInput();
            cout << "Invalid ID.\n";
            return;
        }

        int index = findBookIndex(id);
        if (index == -1) {
            cout << "Book not found.\n";
        } else if (!books[index].issued) {
            cout << "Book is already available.\n";
        } else {
            books[index].issued = false;
            cout << "Book returned successfully.\n";
        }
    }

    void deleteBook() {
        int id;
        cout << "\nEnter book ID to delete: ";
        if (!(cin >> id)) {
            clearInput();
            cout << "Invalid ID.\n";
            return;
        }

        int index = findBookIndex(id);
        if (index == -1) {
            cout << "Book not found.\n";
            return;
        }

        books.erase(books.begin() + index);
        cout << "Book deleted successfully.\n";
    }
};

void showMenu() {
    cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n"
         << "1. Add Book\n"
         << "2. Display All Books\n"
         << "3. Search Book\n"
         << "4. Update Book\n"
         << "5. Issue Book\n"
         << "6. Return Book\n"
         << "7. Delete Book\n"
         << "0. Exit\n"
         << "===============================================\n"
         << "Enter choice: ";
}

int main() {
    Library library;
    int choice;

    do {
        showMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid menu option.\n";
            continue;
        }

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.displayBooks(); break;
            case 3: library.searchBook(); break;
            case 4: library.updateBook(); break;
            case 5: library.issueBook(); break;
            case 6: library.returnBook(); break;
            case 7: library.deleteBook(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
