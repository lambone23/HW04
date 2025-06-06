#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book;
class BookManager;
class BorrowManager;
const int g_MAX_QUANTITY = 3; // 재고

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }

    bool operator==(const Book& other) const
    {
        return title == other.title && author == other.author;
    }
};

namespace std
{
    template <>
    struct hash<Book>
    {
        size_t operator()(const Book& book) const
        {
            return hash<string>()(book.title) ^ (hash<string>()(book.author) << 1);
        }
    };
}

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // 책 제목으로 검색
    void searchByTitle(const string& title)
    {
        bool isFind = false;
        for (const auto& book : books)
        {
            if (title == book.title)
            {
                cout << "찾았습니다! -> " << book.title << " by " << book.author << endl;
                isFind = true;
            }
        }

        if (!isFind)
        {
            cout << "책을 찾을 수 없습니다. 책 제목을 다시 확인하세요." << endl;
        }
    }

    // 작가로 검색
    void searchByAuthor(const string& author)
    {
        bool isFind = false;
        for (const auto& book : books)
        {
            if (author == book.author)
            {
                cout << "찾았습니다! -> " << book.title << " by " << book.author << endl;
                isFind = true;
            }
        }

        if (!isFind)
        {
            cout << "책을 찾을 수 없습니다. 작가를 다시 확인하세요." << endl;
        }
    }
};

class BorrowManager
{
public:

    // 대여 목록 등록
    void initializeStock(Book book, int quantity = g_MAX_QUANTITY)
    {
        //books.insert({ book, quantity }); // {key, Value} : pair<key, value>
        books[book] = quantity;
    }

    // 대여
    void borrowBook(const string& str)
    {
        cout << endl;
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        bool isfind = false;
        for (auto& it : books)
        {
            const Book& book = it.first;
            int& quantity = it.second;

            if (book.title == str)
            {
                isfind = true;
            }
            else if (book.author == str)
            {
                isfind = true;
            }

            if (isfind)
            {
                if (0 < quantity)
                {
                    --quantity; // quantity 감소
                    cout << "대여 처리 완료! -> " << book.title << " by " << book.author << endl;
                }
                else
                {
                    cout << "대여 불가 [재고 전체 대여중]" << endl;
                }
                break;
            }
        }

        if (!isfind)
        {
            cout << "책을 찾을 수 없습니다. 책 제목 또는 작가를 다시 확인하세요." << endl;
        }
    }

    // 반납
    void returnBook(const string& str)
    {
        cout << endl;
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        bool isfind = false;
        for (auto& it : books)
        {
            const Book& book = it.first;
            int& quantity = it.second;

            if (book.title == str)
            {
                isfind = true;
            }
            else if (book.author == str)
            {
                isfind = true;
            }

            if (isfind)
            {
                if (g_MAX_QUANTITY > quantity)
                {
                    ++quantity; // quantity 증가
                    cout << "반납 처리 완료! -> " << book.title << " by " << book.author << endl;
                }
                else
                {
                    cout << "이미 재고량이 충분합니다!" << endl;
                }
                break;
            }
        }

        if (!isfind)
        {
            cout << "책을 찾을 수 없습니다. 책 제목 또는 작가를 다시 확인하세요." << endl;
        }
    }

    // 대여 현황 확인
    void displayStock()
    {
        cout << endl;
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }
        cout << "대여 현황" << endl;
        for (auto& it : books)
        {
            const Book& book = it.first;
            int& quantity = it.second;

            cout << "- " << book.title << " by " << book.author;

            if (0 == quantity)
            {
                cout << " / 대여 불가 / 재고 없음" << endl;
            }
            else
            {
                cout << " / 대여 가능 / 재고 [" << quantity << " / 3]" << endl;
            }
        }
        cout << endl;
    }

private:
    unordered_map <Book, int> books; // 책 목록
};



int main() {
    BookManager manager;
    BorrowManager borrowManager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력

        cout << "3. 검색 By 책 제목" << endl;
        cout << "4. 검색 By 작가" << endl;
        cout << "5. 대여" << endl;
        cout << "6. 반납" << endl;
        cout << "7. 현재 도서 대여 현황" << endl;

        cout << "8. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        cin.ignore(); // 이전 입력의 잔여 버퍼를 제거

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            borrowManager.initializeStock(Book(title, author));
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        //================================================================
        else if (3 == choice)
        { // 3번 선택: 검색 By 책 제목
            string title;
            cout << "책 제목: ";

            getline(cin, title);
            manager.searchByTitle(title);
        }
        else if (4 == choice)
        { // 4번 선택: 검색 By 작가
            string author;
            cout << "책 저자: ";
            
            getline(cin, author);
            manager.searchByAuthor(author);
        }
        else if (5 == choice)
        { // 5번 선택: 대여
            string str;
            cout << "입력(책 제목 또는 저자): ";
 
            getline(cin, str);
            borrowManager.borrowBook(str);
        }
        else if (6 == choice)
        { // 6번 선택: 반납
            string str;
            cout << "입력(책 제목 또는 저자): ";

            getline(cin, str);
            borrowManager.returnBook(str);
        }
        else if (7 == choice)
        { // 7번 선택: 현재 도서 대여 현황
            borrowManager.displayStock();
        }
        //================================================================
        else if (choice == 8) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
