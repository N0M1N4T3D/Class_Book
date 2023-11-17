#include <iostream>
#include <vector>
using namespace std;

struct reader {
    string name, date;
};

class book{
public:
    void create_book(string title, string publisher, unsigned int year, unsigned int pages, string author){
        this->title = title;
        this->publisher = publisher;
        this->year = year;
        this->pages = pages;
        authors.push_back(author);
    }

    book(){
        this->title = "None";
        this->publisher = "None";
        this->year = 0;
        this->pages = 0;
    }
    book(string title, string publisher, unsigned int year, unsigned int pages, string author){
        this->title = title;
        this->publisher = publisher;
        this->year = year;
        this->pages = pages;
        authors.push_back(author);
    }
    ~book(){}

    string Get_title(){
        return title;
    }

    string Get_publisher(){
        return publisher;
    }

    unsigned int Get_year(){
        return year;
    }

    unsigned int Get_pages(){
        return pages;
    }
protected:
    string title, publisher;
    unsigned int year, pages;
    vector<string> authors;
};

class cathalog_book: public book {
public:
    void add_book_to_cathalog(book a, unsigned int ID, unsigned int Quantity, unsigned int Instances){
        this->title = a.Get_title();
        this->publisher = a.Get_publisher();
        this->year = a.Get_year();
        this->pages = a.Get_pages();
        this->ID = ID;
        this->Quantity = Quantity;
        this->Instances = Instances;
    }

    unsigned int Get_ID(){
        return ID;
    }
private:
    unsigned int ID, Quantity, Instances;
    vector<reader> Picked;
};


//Удаление внекласса так как необходимо удалить книгу из векторов (как я понял)
vector<book> delete_book(vector<book> books, string title) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].Get_title() == title) {
            books.erase(books.begin() + i);
        }
    }
    return books;
}

vector<cathalog_book> delete_book_from_cathalog(vector<cathalog_book> cathalog, unsigned int ID) {
    for (int i = 0; i < cathalog.size(); i++) {
        if (cathalog[i].Get_ID() == ID) {
            cathalog.erase(cathalog.begin() + i);
        }
    }
    return cathalog;
}


int main() {
    vector<book> books;
    vector<cathalog_book> cathalog;
    book first;
    cathalog_book element_of_cathalog;
    element_of_cathalog.add_book_to_cathalog(first, 0, 100, 100);
    cathalog.push_back(element_of_cathalog);
    first.create_book("33 developers", "RussianGovernment", 1673, 321, "Me");
    vector<reader> readers;
    books.push_back(first);
    struct reader rdr;
    cathalog = delete_book_from_cathalog(cathalog, 10);
    for (auto el : cathalog){
        cout << el.Get_ID() << " ";
    }
    rdr.name = "Василий";
    rdr.date = "01.01.2020";
    readers.push_back(rdr);
    rdr.name = "Алёша";
    rdr.date = "05.02.2020";
    readers.push_back(rdr);
    return 0;
}
