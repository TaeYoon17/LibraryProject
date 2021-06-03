#include <iostream>
#include <string>

using namespace std;

class DDC {
	int sectionID=0;
	string sectionName;
	void setDDCName() {
		int key = sectionID / 100;
		sectionName = key == 0 ? "General" : key == 1 ? "Philosophy" : key == 2 ? "Religion" :
			key == 3 ? "Social science" : key == 4 ? "Natural science" :
			key == 5 ? "Technology science" : key == 6 ? "Art" :
			key == 7 ? "Language" : key == 8 ? "Literature" :
			key == 9 ? "History" : "Error";
	}
public:
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
	void setDDC(int x) {
		sectionID = x * 100;
		setDDCName();
	}
};
class Book:public DDC {
	string bookName;
	bool isLoan=false;
public:
	void setBook() {
		setDDC();
		cout << "Book Name: ";
		getline(cin, bookName);
	}
	bool bookCanBorrow() {
		if (isLoan) {
			cout << "Already borrowed" << endl;
			return false;
		}
		return true;
	}
	bool getLoanStatus() { return isLoan; }
	string getBookName() { return bookName; }
	void showLoanStatus() {
		cout << "Loan status: " << (isLoan==false ? "This book is already loanded." :
			"This book can loan.") << endl;
	}
	void showBookInfo() {
		cout << bookName;
	}
	void UserBorrowBook() {
		isLoan = true;
	}
	void UserReturnBook() {
		isLoan = false;
	}
};
class BookShelf:public DDC{
	Book* bookArr=new Book[3];
	int top = -1;
public:
	Book* getBook(string bookName) {
		for (int i = 0; i <= top; i++)
			if (bookArr[i].getBookName() == bookName) return &bookArr[i];
	}
	void appendBook() {
		Book book;
	}
	void appendBook(Book book) {
		if (haveThisBook(book.getBookName())) {
			cout << "Already have this book!!" << endl;
			return;
		}
		if (top == 2) cout << "error" << endl;
		else bookArr[++top] = book;
	}
	void deleteBook(Book book) {
		if (!haveThisBook(book.getBookName())) {
			cout << "We don't have this book!!" << endl;
			return;
		}
		if (book.getLoanStatus() == true) {
			cout << "It loaned already... We can't delete this book..." << endl;
			return;
		}
		for (int i = 0; i <= top; i++) {
			if(book.getBookName()==bookArr[i].getBookName()){
				for (int j = i; j <= top-1; j++) bookArr[j] = bookArr[j + 1];
			}
		}
		top--;
	}
	void showShelfBooks() {
		cout << "This book Shelf CCD: " << getDDCName() << endl;
		if (top == -1) return;
		for (int i = 0; i <= top; i++) {
			cout << bookArr[i].getBookName()<<' ';
		}
		cout << "\n";
	}
	void searchBook(string bookName) {
		for (int i = 0; i <= top; i++) {
			if (bookName == bookArr[i].getBookName()) {
				cout << "Our library have this book!!"<<endl;
				bookArr[i].showBookInfo();
			}
		}
	}
	void UserBorrowBook(Book book) {
		for (int i = 0; i <= top; i++) {
			if (bookArr[i].getBookName() == book.getBookName())
				bookArr[i].UserBorrowBook();
		}
	}
	bool bookCanBorrow(string bookName) {
		for (int i = 0; i <= top; i++) 
			if (bookName == bookArr[i].getBookName()) return bookArr[i].bookCanBorrow();
		return false;
	}
	bool haveThisBook(string bookName) {
		for (int i = 0; i <= top; i++)
			if (bookName == bookArr[i].getBookName()) return true;
		return false;
	}
};
class BookShelfList{
	int top = -1;
protected:
	Book *getBook(string bookName) {
		if (!haveThisBook(bookName)) {
			cout << "We don't have this book!" << endl;
			return NULL;
		}
		for (int i = 0; i < 10; i++)
			if(bookshelf[i].haveThisBook(bookName))return bookshelf[i].getBook(bookName);
	}
	void showAllDDCBooks(int data) {
		bookshelf[data].showShelfBooks();
	}
	bool bookCanBorrow(string bookName) {
		for (int i = 0; i < 10; i++)
			if (bookshelf[i].bookCanBorrow(bookName)) return true;
		return false;
	}
	bool haveThisBook(string bookName) {
		for (int i = 0; i < 10; i++) 
			if (bookshelf[i].haveThisBook(bookName)) return true;
		return false;
	}
public:
	BookShelf bookshelf[10];
	BookShelfList() {
		for (int i = 0; i < 10; i++) bookshelf[i].setDDC(i);
	}
	void appendBook() {
		Book book;
		cout << "Enter the append book...\n";
		book.setBook();
		int bookID = book.getDDCID() / 100;
		bookshelf[bookID].appendBook(book);
	}
	void deleteBook() {
		string bookName;
		cout << "Enter the delete bookName: ";
		getline(cin, bookName);
		if (!haveThisBook(bookName)) {
			cout << "We don't have this book!!" << endl;
			return;
		}
		Book* book = getBook(bookName);
		for (int i = 0; i < 10; i++)
			if (bookshelf[i].getDDCName() == book->getDDCName())
				bookshelf[i].deleteBook(*book);
	}
	void showAllLibraryBooks() {
		for (int i = 0; i < 10; i++) {
			showAllDDCBooks(i);
		}
	}
	void showAllDDCBooks() {
		int data;
		cout << "Enter the DDC(0~9): ";
		cin >> data;
		if (data < 0 || 9 < data) {
			cout << "wrong data!!" << endl;
			return;
		}
		bookshelf[data].showShelfBooks();
	}
	bool haveThisBook() {
		string bookName;
		cout << "Enter the bookName: ";
		getline(cin, bookName);
		for (int i = 0; i < 10; i++)
			if (bookshelf[i].haveThisBook(bookName)) return true;
		return false;
	}
};

class User {
	string name;
	Book* loanList[3] = {NULL};
	int top = -1;
public:
	bool haveLoanBook() {
		return top==-1? false:true;
	}
	bool userCanBorrow() {
		if (top == 2) {
			cout << "You have already Full loan!!" << endl;
			return false;
		}
		return true;
	}
	void setName() {
		cout << "Enter the User Name: ";
		getline(cin, name);
	}
	string getName() {
		return name;
	}
	void borrowBook(Book *book) {
		if (top == 2) cout << "Your loanList is Full!!" << endl;
		else {
			book->UserBorrowBook();
			loanList[++top] = book;
		}
	}
	void returnBook(Book *book) {
		if (!book) {
			cout << "Wrong!!" << endl;
			return;
		}
		for (int i = 0; i <= top; i++) {
			if (loanList[i]->getBookName() == book->getBookName()) {
				int j;
				for (j=i; j <= top - 1; j++) loanList[j] = loanList[j + 1];
				loanList[j] = NULL;
			}
		}
		book->UserReturnBook();
		top--;
	}
	void showLoanList() {
		cout << "User " << name << " loanList:" << endl;
		for (int i = 0; i < top; i++)
			cout << loanList[i]->getBookName();
		cout << "\n";
	}
	void showUserInfo() {
		cout << "Name: " << name<<endl;
		cout << "Loaned Book List:" << endl;
		for (int i = 0; i <= top; i++) {
			loanList[i]->showBookInfo();
		}
		cout << "\n";
	}
};
class UserList{
	int top = -1;
protected:
	User getUser(string userName) {
		for (int i = 0; i <= top; i++)
			if (userName == userArr[i].getName()) return userArr[i];
	}
	void appendUser(User user) {
		if (top == 2) cout << "error" << endl;
		else userArr[++top] = user;
	}
	bool userCanBorrow(string userName) {
		for (int i = 0; i <= top; i++)
			if (userArr[i].getName() == userName) return userArr[i].userCanBorrow();
		return false;
	}
	bool haveThisUser(string userName) {
		for (int i = 0; i <= top; i++)
			if (userArr[i].getName() == userName) return true;
		return false;
	}
public:
	User userArr[3];
	void appendUser() {
		User user;
		cout << "Append User...\n";
		user.setName();
		if (haveThisUser(user.getName())) cout << "Overlap Name" << endl;
		if (top == 2) cout << "invalid Full UserList" << endl;
		else userArr[++top] = user;
	}
	void deleteUser(){
		cout << "Delete User name:";
		string username;
		getline(cin, username);
		if (!haveThisUser(username)) {
			cout << "Wrong name!!" << endl;
			return;
		}
		for (int i = 0; i <= top; i++) {
			if (username == userArr[i].getName()) {
				if (userArr[i].haveLoanBook()) {
					cout << "You have a book to return." << endl;
					return;
				}
				for (int j = i; j <= top; j++) userArr[j] = userArr[j + 1];
			}
		}
		top--;
	}
	void showUserList() {
		cout << "UserList: " << endl;
		for (int i = 0; i <= top; i++)
			cout << userArr[i].getName()<<" ";
		cout << "\n";
	}
	void showUserInfo() {
		string username;
		cout << "Who want? Enter the Username: ";
		getline(cin, username);
		if (!haveThisUser(username)) {
			cout << "You are wrong!!" << endl;
			return;
		}
		for (int i = 0; i <= top; i++) {
			if (userArr[i].getName() == username) userArr[i].showUserInfo();
		}
	}
	void UserBorrowBook(User user,Book *book) {
		for (int i = 0; i <= top; i++)
			if (userArr[i].getName()==user.getName()) {
				userArr[i].borrowBook(book);
				return;
			}
	}
	void UserReturnBook(User user,Book *book) {
		for(int i=0; i<=top; i++)
			if (userArr[i].getName() == user.getName()) {
				userArr[i].returnBook(book);
				return;
			}
	}
	bool userCanBorrow() {
		string userName;
		getline(cin, userName);
		for (int i = 0; i <= top; i++)
			if (userArr[i].getName() == userName) return userArr[i].userCanBorrow();
		return false;
	}
	bool haveThisUser() {
		string userName;
		getline(cin, userName);
		for (int i = 0; i <= top; i++)
			if (userArr[i].getName() == userName) return true;
		return false;
	}
};

class Library:public UserList,public BookShelfList {
	string libName;
public:
	Library() {
		cout << "Library Name: ";
		getline(cin, libName);
	}
	void UserBorrowBook() {
		string bookName;string userName;
		cout << "Please Enter BookName and UserName to borrow book"<<endl;
		cout << "BookName: "; getline(cin, bookName);
		cout << "UserName: "; getline(cin, userName);
		if (!bookCanBorrow(bookName)) return;
		if (!userCanBorrow(userName)) return;
		Book *book = getBook(bookName);
		User user = getUser(userName);
		UserList::UserBorrowBook(user, book);
	}
	void UserReturnBook() {
		string bookName; string userName;
		cout << "Please Enter BookName and UserName to return book" << endl;
		cout << "BookName: "; getline(cin, bookName);
		cout << "UserName: "; getline(cin, userName);
		if (!haveThisBook(bookName)) return;
		if (!haveThisUser(userName)) return;
		Book *book = getBook(bookName);
		User user = getUser(userName);
		UserList::UserReturnBook(user, book);
	}
};


class Menu {
public:
	void cmdMenu() {
		cout << "1: User Method" << endl;
		cout << "2: Book Method" << endl;
		cout << "3: Borrow and Return Method" << endl;
		cout << "0: Exit" << endl;
	}
	void cmdUser(Library &li) {
		int cmd2;
		cout << "1: Append User" << endl;
		cout << "2: Delete User" << endl;
		cout << "3: Show User List" << endl;
		cout << "4: Show User Info" << endl;
		cout << "0: Exit" << endl;
		cout << "Enter the cmd:";
		cin >> cmd2;
		getchar();
		switch (cmd2) {
		case 1:
			li.appendUser();
			break;
		case 2:
			li.deleteUser();
			break;
		case 3:
			li.showUserList();
			break;
		case 4:
			li.showUserInfo();
			break;
		case 5:
			exit(0);
			break;
		default:
			exit(1);
			break;
		}
	}
	void cmdBook(Library &li) {
		int cmd2;
		cout << "1: Append Book" << endl;
		cout << "2: Delete Book" << endl;
		cout << "3: Show All Library Books" << endl;
		cout << "4: Show All DDC Books" << endl;
		cout << "0: Exit" << endl;
		cout << "Enter the cmd:";
		cin >> cmd2;
		getchar();
		switch (cmd2) {
		case 1:
			li.appendBook();
			break;
		case 2:
			li.deleteBook();
			break;
		case 3:
			li.showAllLibraryBooks();
			break;
		case 4:
			li.showAllDDCBooks();
			break;
		case 5:
			exit(0);
			break;
		default:
			exit(1);
			break;
		}
	}
	void cmdBorrowReturn(Library& li) {
		int cmd2;
		cout << "1: User Borrow Book" << endl;
		cout << "2: User Return Book" << endl;
		cout << "0: Exit" << endl;
		cout << "Enter the cmd:";
		cin >> cmd2;
		getchar();
		switch (cmd2) {
		case 1:
			li.UserBorrowBook();
			break;
		case 2:
			li.UserReturnBook();
			break;
		case 0:
			exit(0);
			break;
		default:
			exit(1);
			break;
		}
	}
};
int main() {
	Library li; 
	Menu me;
	int cmd1;
	while (1) {
		me.cmdMenu();
		cout << "Enter the cmd:";
		cin >> cmd1;
		getchar();
		switch (cmd1) {
		case 1:
			me.cmdUser(li);
			break;
		case 2:
			me.cmdBook(li);
			break;
		case 3:
			me.cmdBorrowReturn(li);
			break;
		default:
			exit(1);
			break;
		}
	}
	return 0;
}