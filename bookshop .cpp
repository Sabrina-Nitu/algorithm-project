#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Book {
    string title;
    string author;
    int year;
    double price;
    string genre;
    int copiesSold;

    Book() : copiesSold(0) {}
};

struct Purchase {
    string title;
    double price;
};

// add a book to the library
void addBook(vector<Book>& library) {
    Book book;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, book.title);
    cout << "Enter author: ";
    getline(cin, book.author);
    cout << "Enter publication year: ";
    cin >> book.year;
    cout << "Enter book price: $";
    cin >> book.price;
    cout << "Enter genre: ";
    cin.ignore();
    getline(cin, book.genre);

    library.push_back(book); // Add the book to the vector
    cout << "Book added to the library.\n";
}

//  search for a book by title
void searchBook(const vector<Book>& library, const string& title) {
    bool found = false;//check
    for (const Book& book : library) {
        if (book.title == title) {
            cout << "Book found: " << book.title << " by " << book.author << " (" << book.year << "), Price: $" << book.price
                 << ", Genre: " << book.genre << ", Copies Sold: " << book.copiesSold << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Book not found in the library.\n";
    }
}
// display the entire book collection
void displayBookCollection(const vector<Book>& library) {
    cout << "Book Collection:\n";
    for (const Book& book : library) {
        cout << "Title: " << book.title << ", Author: " << book.author << " (" << book.year << "), Price: $" << book.price
             << ", Genre: " << book.genre << ", Copies Sold: " << book.copiesSold << "\n";
    }
}

// record a book purchase
void recordPurchase(vector<Purchase>& purchases, vector<Book>& library, const string& title) {
    for (Book& book : library) {
        if (book.title == title) {
            Purchase purchase;
            purchase.title = book.title;

            // Add an option for  to specify the number of copies purchased
            int numCopies;
            cout << "Enter the number of copies purchased: ";
            cin >> numCopies;

            purchase.price = book.price * numCopies; // Update the total price based on the number of copies
            purchases.push_back(purchase);
            cout << "Purchase recorded for " << book.title << " (" << numCopies << " copies) at $" << purchase.price << "\n";

            // Increment  for the Top Selling feature
            book.copiesSold += numCopies;

            return;
        }
    }
    cout << "Book not found in the library. Purchase not recorded.\n";
}

// display recorded purchases
void displayPurchases(const vector<Purchase>& purchases) {
    cout << "Recorded Purchases:\n";
    for (const Purchase& purchase : purchases) {
        cout << "Book: " << purchase.title << ", Price: $" << purchase.price << "\n";
    }
}

// display top-selling books
void displayTopSelling(const vector<Book>& library) {
    cout << "Top Selling Books:\n";
    vector<Book> topSelling = library;
    sort(topSelling.begin(), topSelling.end(), [](const Book& a, const Book& b) {
        return a.copiesSold > b.copiesSold;
    });

    for (const Book& book : topSelling) {
        if (book.copiesSold > 0) {
            cout << "Book: " << book.title << " by " << book.author << " (" << book.year << "), Genre: " << book.genre
                 << ", Copies Sold: " << book.copiesSold << "\n";
        }
    }
}

// heapify for heap sort by title
void heapify(vector<Book>& library, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && library[left].title > library[largest].title)
        largest = left;

    if (right < n && library[right].title > library[largest].title)
        largest = right;

    if (largest != i) {
        swap(library[i], library[largest]);
        heapify(library, n, largest);
    }
}

// Heap Sort
void heapSort(vector<Book>& library) {
    int n = library.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(library, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(library[0], library[i]);
        heapify(library, i, 0);
    }

    cout << "Books sorted by title using Heap Sort.\n";
}

// Quick Sort for sorting by genre
int partitionByGenre(vector<Book>& library, int low, int high);

void quickSortByGenre(vector<Book>& library, int low, int high) {
    if (low < high) {
        int pivot = partitionByGenre(library, low, high);

        quickSortByGenre(library, low, pivot - 1);
        quickSortByGenre(library, pivot + 1, high);
    }
}

int partitionByGenre(vector<Book>& library, int low, int high) {
    string pivot = library[high].genre;  // Book object at the high index
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {  // low to high - 1
        if (library[j].genre <= pivot) {
            i++;
            swap(library[i], library[j]);
        }
    }

    swap(library[i + 1], library[high]);
    return i + 1;
}

// Merge Sort for sorting by publishing year
void mergeByYear(vector<Book>& library, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Book> leftBooks(n1);
    vector<Book> rightBooks(n2);

    for (int i = 0; i < n1; i++) //copy
        leftBooks[i] = library[left + i];
    for (int j = 0; j < n2; j++)
        rightBooks[j] = library[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftBooks[i].year <= rightBooks[j].year) {
            library[k] = leftBooks[i];
            i++;
        } else {
            library[k] = rightBooks[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        library[k] = leftBooks[i];
        i++;
        k++;
    }

    while (j < n2) {
        library[k] = rightBooks[j];
        j++;
        k++;
    }
}

void mergeSortByYear(vector<Book>& library, int left, int right) {
    if (left < right) { //If left is not less than right, the function returns without doing anything
        int mid = left + (right - left) / 2; //middle

        mergeSortByYear(library, left, mid);
        mergeSortByYear(library, mid + 1, right);

        mergeByYear(library, left, mid, right);
    }
}

// Function declarations
void quickSort(vector<Book>& library, int low, int high);
void mergeSort(vector<Book>& library, int left, int right);

int main() {
    vector<Book> library;

    Book book1;
    book1.title = "The Great Gatsby";
    book1.author = "F. Scott Fitzgerald";
    book1.year = 1925;
    book1.price = 10.99;
    book1.genre = "Fiction";
    library.push_back(book1);

    Book book2;
    book2.title = "Bohubrihi";
    book2.author = "Humayun Ahmed";
    book2.year = 1990;
    book2.price = 8.50;
    book2.genre = "Drama";
    library.push_back(book2);

    vector<Purchase> purchases;
    int choice;
    string searchTitle;
    string purchaseTitle;
    char continueChoice;  // Add variable for continue/quit choice

    cout << "\t\t\t\t\t-----WELCOME TO OUR IIUC BOOK SHOP-----\n";


    do {
        cout << "\nBookshop Management System\n";
        cout << "1. Add a book\n";
        cout << "2. Search for a book by title\n";
        cout << "3. Display Book Collection\n";
        cout << "4. Record a book purchase\n";
        cout << "5. Display recorded purchases\n";
        cout << "6. Display top selling books\n";
        cout << "7. Sort books by Title (Heap Sort)\n";
        cout << "8. Sort books by Genre (Quick Sort)\n";
        cout << "9. Sort books by Publishing Year (Merge Sort)\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                cout << "Enter the title to search for: ";
                cin.ignore();
                getline(cin, searchTitle);
                searchBook(library, searchTitle);
                break;
            case 3:
                displayBookCollection(library);
                break;
            case 4:
                cout << "Enter the title of the purchased book: ";
                cin.ignore();
                getline(cin, purchaseTitle);
                recordPurchase(purchases, library, purchaseTitle);
                break;
            case 5:
                displayPurchases(purchases);
                break;
            case 6:
                displayTopSelling(library);
                break;

            case 7:
                heapSort(library);
                displayBookCollection(library); // Display sorted collection
                break;

            case 8:
                quickSortByGenre(library, 0, library.size() - 1);
                cout << "Books sorted by genre using Quick Sort.\n";
                displayBookCollection(library); // Display sorted collection
               break;
            case 9:
                mergeSortByYear(library, 0, library.size() - 1);
                cout << "Books sorted by year using Merge Sort.\n";
               displayBookCollection(library); // Display sorted collection
              break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << "Do you want to continue (C) or quit (Q)? ";
        cin >> continueChoice;

    } while (continueChoice == 'C' || continueChoice == 'c');

    cout << "Exiting the program.\n";
    return 0;

}
