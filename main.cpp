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


protected:
    string title, publisher;
    unsigned int year, pages;
    vector<string> authors;
};

class cathalog_book: public book {
public:

private:
    unsigned int ID, Quantity, Instances;
    vector<reader> Picked;
};

int main() {
    book first;
    first.create_book("33  developers", "RussianGovernment", 1673, 321, "Me");
    vector<reader> readers;
    struct reader rdr;
    rdr.name = "Василий";
    rdr.date = "01.01.2020";
    readers.push_back(rdr);
    rdr.name = "Алёша";
    rdr.date = "05.02.2020";
    readers.push_back(rdr);
    return 0;
}
