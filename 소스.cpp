#include <iostream>
#include <string>

using namespace std;

typedef struct DDCbookself {
	struct DDCbookself* next, * before;
	Book book;
}DDCbookself;


class Library{
	string name;
	BookShelf bookshelf[10];
public:
	Library( ) {

	}
	void appendBook() {
		Book book;
		int bookID = book.getDDCID() / 100;
		bookshelf[bookID].appendBook(book);
	}
	void showLibraryBooks() {
		for (int i = 0; i < 10; i++) {
			bookshelf[i].showShelfBooks();
		}
	}
};

class BookShelf {
	Book* bookArr=new Book[10];
public:
	void appendBook() {

	}
	void appendBook(Book book) {
		bookArr.push(book);
	}
};

class DDC {
	int sectionID;
	string sectionName;
	void setDDCName() {
		int key = sectionID / 100;
		sectionName = key == 0 ? "general" : key == 1 ? "philosophy" : key == 2 ? "religion" :
			key == 3 ? "social science" : key == 4 ? "natural science" :
			key == 5 ? "technology science" : key == 6 ? "art" :
			key == 7 ? "language" : key == 8 ? "literature" :
			key == 9 ? "history" : "error";
	}
public:
	DDC() {
		setDDC();
	}
	int getDDCID() {
		return sectionID;
	}
	string getDDCName() {
		return sectionName;
	}
	void setDDC() {
		cout << "DDC ID(000~999):";
		cin >> sectionID;
		getchar();
		setDDCName();
	}
};
class Book:public DDC {
	string bookName;
public:
	Book() {
		setBook();
	}
	void setBook() {
		cout << "Book Name: ";
		getline(cin, bookName);
	}
};

class User {
	string id;
	Book* arrowList = new Book[3];
public:
	User(string id) {
		this->id = id;
	}
	void borrow(){}
	void search(){}
};

int main() {
}