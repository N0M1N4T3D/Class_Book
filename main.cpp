#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <string>
using namespace std;

struct reader {
    string name;
    int day, month, year, book_ID, returned_flag;

    void information_about_reader(reader reader){
        cout << "\nИмя: " << reader.name << "\nДата: " << reader.day << "." << reader.month+1 << "." << reader.year+1900 << "\n";
    }
};

class book{
public:
    void create_book(string title, string publisher, unsigned int year, unsigned int pages, vector<string> authors){
        this->title = title;
        this->publisher = publisher;
        this->year = year;
        this->pages = pages;
        this->authors = authors;
    }

    book(){
        this->title = "None";
        this->publisher = "None";
        this->year = 0;
        this->pages = 0;
    }
    book(string title, string publisher, unsigned int year, unsigned int pages, vector<string> authors){
        this->title = title;
        this->publisher = publisher;
        this->year = year;
        this->pages = pages;
        this->authors = authors;
    }
    ~book(){}

    string Get_title(){
        return title;
    }

    string Get_publisher(){
        return publisher;
    }

    vector<string> Get_authors(){
        return authors;
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
        this->authors = a.Get_authors();
        this->Quantity = Quantity;
        this->Instances = Instances;
    }
    unsigned int Get_ID(){
        return ID;
    }
    void get_book_to_reader(reader r)
    {
        
        this->Instances--;
        Picked.push_back(r);
    }
    int find_index_of_picker_using_name(string name, int ret_flag = 0)
    {
        for (int i=0;i<Picked.size();i++)
        {
            if (Picked[i].name == name && Picked[i].returned_flag == ret_flag)
            {
                return i;
            }
        }
        return -1;
    }
    void set_returned_state(int index)
    {
        Picked[index].returned_flag = 1;
    }
    void set_Instance(int num) {
        Instances += num;
    }

    void information_about_book(){
        cout << "Информация по книге:\nНазвание: " << title << "\nАвторы: ";
        for (auto el : authors){
            cout << el << " ";
        }
        cout << "\nГод издания: " << year << "\nИздательство: " << publisher << "\nКоличество страниц: " << pages << "\n";
    }
    
private:
    unsigned int ID, Quantity, Instances;
    vector<reader> Picked;
};

void Get_information_about_book_and_readers(vector<cathalog_book> catalog, vector<reader> readers, unsigned int ID){
    for (int i = 0; i < catalog.size(); i++){
        if (catalog[i].Get_ID() == ID){
            catalog[i].information_about_book();
            cout << "Информация о читателе: ";
            for (int j = 0; j < readers.size(); j++) {
                int index = catalog[i].find_index_of_picker_using_name(readers[j].name);
                if (index != -1) {
                    readers[j].information_about_reader(readers[j]);
                }
            }
        }
    }
}

void Find_book_by_name(vector<cathalog_book> catalog, string title){
    for (int i = 0; i < catalog.size(); i++){
        if (catalog[i].Get_title() == title){
            catalog[i].information_about_book();
            cout << "ID: " << catalog[i].Get_ID() << "\n";
        }
    }
}

void Find_book_by_author(vector<cathalog_book> catalog, vector<string> authors){
    for (int i = 0; i < catalog.size(); i++){
        if (catalog[i].Get_authors() == authors){
            catalog[i].information_about_book();
            cout << "ID: " << catalog[i].Get_ID() << "\n";
        }
    }
}

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
void return_book(int ID, string name, vector <cathalog_book> &catalog);
vector <reader> readers_with_more_one_year_storing_book(vector <reader> r);

int main() {
    //setlocale(LC_ALL, "russian");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    vector<string> authors = {"First author", "Second author", "Third author"};
    vector<book> books;
    vector<cathalog_book> cathalog;

    int sw_num;
    while (1)
    {
        std::cin >> sw_num;
        switch (sw_num)
        {
        case 1://создание книги
        {
            book b_new;
            std::cout << "Укажите автора\n";
            string author;
            std::getline(cin, author);
            std::cout << "Укажите издательство\n";
            string publisher;
            std::getline(cin, publisher);
            std::cout << "Укажите год издания\n";
            unsigned int year;
            std::cin >> year;
            std::cout << "Введите количество страниц\n";
            unsigned int pages;
            std::cin >> pages;
            std::cout << "Введите количество авторов\n";
            unsigned int author_count;
            std::cin >> author_count;
            for (int i = 0; i < author_count; i++)
            {
                string auth;
                getline(cin, auth);
                authors.push_back(auth);
            }
        }
        case 2://удаление книги
        {

        }
        default:
            break;
        }
    }
    book first, second;
    first.create_book("33 developers", "RussianGovernment", 1673, 321, authors);
    second.create_book("44 developers", "PrussianGovernment", 1673, 321, authors);
    cathalog_book element_of_cathalog;
    element_of_cathalog.add_book_to_cathalog(first, 0, 100, 100);
    cathalog.push_back(element_of_cathalog);
    element_of_cathalog.add_book_to_cathalog(second, 1, 100, 100);
    cathalog.push_back(element_of_cathalog);
    vector<string> test = first.Get_authors();
    vector<reader> readers;
    books.push_back(first);
    struct reader rdr;
    //cathalog = delete_book_from_cathalog(cathalog, 10);
    for (auto el : cathalog){
        cout << el.Get_ID() << " ";
    }
    cout << endl;
    std::time_t rawtime = std::time({});
    time(&rawtime);
    struct tm* timeinfo;
    timeinfo = localtime(&rawtime);
    //создание тут говорит о том, что он сегодня берет...
    reader r;
    r.name = "Vasya";
    r.day = timeinfo->tm_mday;
    r.month = timeinfo->tm_mon;
    r.year = timeinfo->tm_year;
    r.book_ID = 0;
    r.returned_flag = 0;
    readers.push_back(r);
    cathalog[0].get_book_to_reader(r);
    Get_information_about_book_and_readers(cathalog, readers,0);
    // Find_book_by_name(cathalog, "44 developers");
    Find_book_by_author(cathalog, authors);
    return_book(r.book_ID, r.name, cathalog);
    readers_with_more_one_year_storing_book(readers);
    return 0;
}
vector <reader> readers_with_more_one_year_storing_book(vector <reader> r)
{
    vector <reader> black;
    std::time_t rawtime = std::time({});
    time(&rawtime);
    struct tm* timeinfo;
    timeinfo = localtime(&rawtime);
    int year = timeinfo->tm_year;
    int month = timeinfo->tm_mon;
    int day = timeinfo->tm_mday;
    for (int i = 0; i < r.size(); i++)
    {
        if (abs(r[i].year - year) > 1)
        {
            black.push_back(r[i]);
            continue;
        }
        else if (abs(r[i].year - year) ==1) {
            if (month - r[i].month > 0)
            {
                black.push_back(r[i]);
                continue;
            }
            else if (month - r[i].month ==0 && day - r[i].day > 0)
            {
                black.push_back(r[i]);
                continue;
            }
        }
    }
    return black;
}
void return_book(int ID, string name, vector <cathalog_book>& catalog)
{
    for (int i = 0; i < catalog.size(); i++)
    {
        if (catalog[i].Get_ID() == ID)
        {
            int index = catalog[i].find_index_of_picker_using_name(name);
            if (index != -1) {
                catalog[i].set_returned_state(index);
                catalog[i].set_Instance(1);
            }
        }
    }
}