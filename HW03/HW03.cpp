#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// 定義圖書結構體
struct Book {
    string title;    // 書名
    string author;   // 作者
    string bookID;   // 圖書編號

    // 驗證圖書編號格式：第一個字母，後四個為數字
    static bool isValidID(const string& id) {
        return id.size() == 5 && isalpha(id[0]) && isdigit(id[1]) && isdigit(id[2]) && isdigit(id[3]) && isdigit(id[4]);
    }
};

// 定義借閱者結構體
struct Borrower {
    string name;                   // 借閱者姓名
    vector<string> borrowedBooks;  // 借閱的圖書編號列表
};

// 使用 list 容器管理圖書資訊
list<Book> books;

// 使用 forward_list 容器管理借閱者資訊
forward_list<Borrower> borrowers;

// 添加新圖書
void addBook() {
    Book newBook;
    cout << "輸入書名: ";
    cin.ignore();
    getline(cin, newBook.title);  // 輸入書名
    cout << "輸入作者: ";
    getline(cin, newBook.author); // 輸入作者

    // 圖書編號輸入與驗證
    do {
        cout << "輸入圖書編號（首字母+4位數字）: ";
        cin >> newBook.bookID;
		if (!Book::isValidID(newBook.bookID)) {  // 驗證圖書編號格式
            cout << "圖書編號格式錯誤！請重新輸入。\n";
        }
    } while (!Book::isValidID(newBook.bookID));

    books.push_back(newBook); // 將圖書添加到 list
    cout << "圖書已添加成功！\n";
}

// 刪除指定圖書編號的圖書
void deleteBook() {
    string bookID;
    cout << "輸入要刪除的圖書編號: ";
    cin >> bookID;

    // 使用 find_if 查找指定圖書
    auto it = find_if(books.begin(), books.end(), [&bookID](const Book& b) { return b.bookID == bookID; });

    if (it != books.end()) {
        books.erase(it); // 刪除圖書
        cout << "圖書已刪除。\n";
    }
    else {
        cout << "找不到該圖書編號！\n";
    }
}

// 搜尋指定圖書編號的圖書
void searchBook() {
    string bookID;
    cout << "輸入要查找的圖書編號: ";
    cin >> bookID;

    // 使用 find_if 查找圖書
    auto it = find_if(books.begin(), books.end(), [&bookID](const Book& b) { return b.bookID == bookID; });

    if (it != books.end()) {
		cout << "書名: " << it->title << ", 作者: " << it->author << ", 編號: " << it->bookID << endl;  // 輸出圖書資訊
    }
    else {
        cout << "找不到該圖書編號！\n";
    }
}

// 列出所有圖書，並依照圖書編號排序
void listBooks() {
    // 對 list 中的圖書按圖書編號進行排序
    books.sort([](const Book& a, const Book& b) { return a.bookID < b.bookID; });
    for (const auto& book : books) {
        cout << "書名: " << book.title << ", 作者: " << book.author << ", 編號: " << book.bookID << endl;
    }
}

// 添加新借閱者
void addBorrower() {
    Borrower newBorrower;
    cout << "輸入借閱者姓名: ";
    cin.ignore();
    getline(cin, newBorrower.name); // 輸入借閱者姓名

    int count;
    cout << "輸入借閱圖書的數量: ";
    cin >> count;

    // 輸入借閱圖書的圖書編號並存入 vector
    for (int i = 0; i < count; ++i) {
        string bookID;
        cout << "輸入圖書編號: ";
        cin >> bookID;
        newBorrower.borrowedBooks.push_back(bookID);
    }

    borrowers.push_front(newBorrower); // 將借閱者添加到 forward_list
    cout << "借閱者已添加成功！\n";
}

// 刪除指定姓名的借閱者
void deleteBorrower() {
    string name;
    cout << "輸入要刪除的借閱者姓名: ";
    cin.ignore();
    getline(cin, name);

    // 使用 remove_if 刪除指定借閱者
    borrowers.remove_if([&name](const Borrower& b) { return b.name == name; });
    cout << "借閱者已刪除（若存在）。\n";
}

// 搜尋指定姓名的借閱者
void searchBorrower() {
    string name;
    cout << "輸入要查找的借閱者姓名: ";
    cin.ignore();
    getline(cin, name);

    // 使用 find_if 查找借閱者
    auto it = find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& b) { return b.name == name; });

    if (it != borrowers.end()) {
        cout << "姓名: " << it->name << ", 借閱圖書編號: ";
		for (const auto& id : it->borrowedBooks) {  // 輸出借閱者資訊
            cout << id << " ";
        }
        cout << endl;
    }
    else {
        cout << "找不到該借閱者！\n";
    }
}

// 列出所有借閱者及其借閱的圖書
void listBorrowers() {
    for (const auto& borrower : borrowers) {
        cout << "姓名: " << borrower.name << ", 借閱圖書編號: ";
        for (const auto& id : borrower.borrowedBooks) {
            cout << id << " ";
        }
        cout << endl;
    }
}

// 主函式：提供圖書館管理系統的選單
int main() {
    int choice;
    do {
        cout << "\n=== 圖書館管理系統 ===\n";
        cout << "1. 添加新圖書\n";
        cout << "2. 刪除圖書\n";
        cout << "3. 搜索圖書\n";
        cout << "4. 列出所有圖書\n";
        cout << "5. 添加新借閱者\n";
        cout << "6. 刪除借閱者\n";
        cout << "7. 搜索借閱者\n";
        cout << "8. 列出所有借閱者\n";
        cout << "0. 退出\n";
        cout << "請選擇操作: ";
        cin >> choice;

		// 根據選擇執行相應操作
        switch (choice) {
        case 1: addBook(); break;
        case 2: deleteBook(); break;
        case 3: searchBook(); break;
        case 4: listBooks(); break;
        case 5: addBorrower(); break;
        case 6: deleteBorrower(); break;
        case 7: searchBorrower(); break;
        case 8: listBorrowers(); break;
        case 0: cout << "退出系統。\n"; break;
        default: cout << "無效的選項，請重試。\n"; break;
        }
    } while (choice != 0);

    return 0;
}
