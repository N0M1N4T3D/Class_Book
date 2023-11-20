#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#define SN 1000000007
using namespace std;
int id_counter=0;
struct reader {
    string name;
    int day, month, year, book_ID, returned_flag;

    void information_about_reader(reader reader){
        cout << "\nИмя: " << reader.name << "\nДата: " << reader.day << "." << reader.month+1 << "." << reader.year+1900 << "\n";
    }
};

class book{
public:
    void information_about_book() {
        cout << "Информация по книге:\nНазвание: " << title << "\nАвторы: ";
        for (auto el : authors) {
            cout << el << " ";
        }
        cout << "\nГод издания: " << year << "\nИздательство: " << publisher << "\nКоличество страниц: " << pages << "\n";
    }
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
    unsigned int get_instances()
    {
        return this->Instances;
    }
    unsigned int get_quantity()
    {
        return this->Quantity;
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
unsigned int validator_unsigned_int(string str);
int validator_int(string str, int more_then_zero_flag);
void print_menu()
{
    cout << "Приветствую\n"
        << "1. Создание книги" << endl
        << "2. Удаление книги" << endl
        << "3. Вывод списка книг" << endl
        << "4. Добавление книги в каталог" << endl
        << "5. Удаление книги из каталога" << endl
        << "6. Вывод каталога" << endl;
}
int main() {
    //setlocale(LC_ALL, "russian");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    vector<string> authors;
    vector<book> books;
    vector<cathalog_book> cathalog;
    vector<reader> readers;
    cathalog_book CATA;

    int sw_num;
    print_menu();
    while (1)
    {
        std::cin >> sw_num;
        switch (sw_num)
        {
        case 1://создание книги
        {
            system("cls");
            vector <string> auth_v;
            book b_new;
            cout << "Введите название книги\n";
            string name;
            cin.ignore();
            getline(cin, name);
            std::cout << "Укажите автора\n";
            string author;
            std::getline(cin, author);
            std::cout << "Укажите издательство\n";
            string publisher;
            std::getline(cin, publisher);
            std::cout << "Укажите год издания\n";
            string year;
            getline(cin, year);
            unsigned int _year;
            _year = validator_unsigned_int(year);
            if (_year == SN)
            {
                cout << "Не стоит меня ломать, я просто программа(\n";
                break;
            }
            std::cout << "Введите количество страниц\n";
            string pages;
            getline(cin, pages);
            unsigned int _pages;
            _pages = validator_unsigned_int(pages);
            if (_pages == SN)
            {
                cout << "Не стоит меня ломать, я просто программа(\n";
                break;
            }
            /*std::cout << "Введите ID для каталога\n";
            string cat_id;
            getline(cin, cat_id);
            unsigned int _cat_id;
            _cat_id = validator_unsigned_int(cat_id);
            if (_cat_id == SN)
            {
                cout << "Не стоит меня ломать, я просто программа(\n";
                break;
            }*/
            /*std::cout << "Введите количество экземпляров\n";
            string quant;
            getline(cin, quant);
            unsigned int _quant, _inst;
            _quant = validator_unsigned_int(quant);
            if (_quant == SN)
            {
                cout << "Не стоит меня ломать, я просто программа(\n";
                break;
            }
            else
            {
                _inst = _quant;
            }*/
            std::cout << "Введите количество авторов\n";
            string author_count;
            getline(cin, author_count);
            unsigned int _author_count;
            _author_count = validator_unsigned_int(author_count);
            if (_author_count == SN)
            {
                cout << "Не стоит меня ломать, я просто программа(\n";
                break;
            }
            for (int i = 0; i < _author_count; i++)
            {
                string auth;
                cout << "Введите автора " << i + 1 << '\n';
                getline(cin, auth);
                int flag = 0;
                for (int i = 0; i < authors.size(); i++)
                {
                    if (authors[i] == auth)
                    {
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    authors.push_back(auth);
                }
                auth_v.push_back(auth);
                }
            b_new.create_book(name, publisher, _year, _pages, auth_v);
            books.push_back(b_new);
            //CATA.add_book_to_cathalog(b_new,id_counter++,_quant,_inst);
            system("cls");
            //cout << "Успех! ID книги в каталоге: "<< id_counter-1<<" :";
            cout << "Успех!\n";
            system("pause");
            system("cls");
            print_menu();
            break;
        }
        case 2://удаление книги
        {
            system("cls");
            for (int i = 0; i < books.size(); i++)
            {
                cout << "----------------------------\n";
                books[i].information_about_book();
            }
            cout << "Введите НАЗВАНИЕ книги на удаление\n";
            string id;
            cin.ignore();
            getline(cin, id);
            int f = 0;
            for (int i = 0; i < books.size(); i++)
            {
                if (books[i].Get_title() == id)
                {
                    f = 1;
                    break;
                }
            }
            if (f==1)
                books = delete_book(books, id);
            else
            {
                cout << "Нет такой книжки(\n";
                break;
            }
            system("cls");
            cout << "Успех!\n";
            system("pause");
            system("cls");
            print_menu();
            break;
        }
        case 3://Вывод списка книг
        {
            system("cls");
            for (int i = 0; i < books.size(); i++)
            {
                cout << "----------------------------\n";
                books[i].information_about_book();
            }
            system("pause");
            system("cls");
            print_menu();
            break;
        }
        case 4://добавление книги в каталог
        {
            system("cls");
            for (int i = 0; i < books.size(); i++)
            {
                cout << "----------------------------\n";
                books[i].information_about_book();
            }
            cout << endl<<"Введите название книги для добавления\n";
            string book_name;
            cin.ignore();
            getline(cin, book_name);
            for (int i = 0; i < books.size(); i++)
            {
                if (books[i].Get_title() == book_name)
                {
                    std::cout << "Введите количество экземпляров\n";
                    string quant;
                    getline(cin, quant);
                    unsigned int _quant, _inst;
                    _quant = validator_unsigned_int(quant);
                    if (_quant == SN)
                    {
                        cout << "Не стоит меня ломать, я просто программа(\n";
                        break;
                    }
                    else
                    {
                        _inst = _quant;
                    }
                    cathalog_book example;
                    example.add_book_to_cathalog(books[i], id_counter++, _quant, _inst);
                    cathalog.push_back(example);
                    cout << "Успех! ID в каталоге " << id_counter - 1 << endl;
                    break;
                }
            }
            system("pause");
            system("cls");
            print_menu();
            break;
            
        }
        case 5://удаление книги из каталога
        {
            system("cls");
            for (int i = 0; i < cathalog.size(); i++)
            {
                cout << "----------------------------\n";
                cathalog[i].information_about_book();
                cout << "ID: " << cathalog[i].Get_ID() << '\n';
                cout << "Число экземпляров в наличии: " << cathalog[i].get_instances() << endl;
                cout << "Общее число экземпляров: " << cathalog[i].get_quantity() << endl;
            }
            cout << endl<<"Введите ID книги для удаления\n";
            string id_book_to_del;
            cin.ignore();
            getline(cin, id_book_to_del);
            unsigned int tmp1 = validator_unsigned_int(id_book_to_del);
            if (tmp1 == SN || tmp1>=cathalog.size())
            {
                cout << "Неверный ID\n";
                system("pause");
                system("cls");
                print_menu();
                break;
            }
            cathalog = delete_book_from_cathalog(cathalog, tmp1);

            cout << "Успех!\n";
            system("pause");
            system("cls");
            print_menu();
            break;
        }
        case 6:
        {
            system("cls");
            for (int i = 0; i < cathalog.size(); i++)
            {
                cout << "----------------------------\n";
                cathalog[i].information_about_book();
                cout << "ID: " << cathalog[i].Get_ID() << '\n';
                cout << "Число экземпляров в наличии: " << cathalog[i].get_instances() << endl;
                cout << "Общее число экземпляров: " << cathalog[i].get_quantity() << endl;
            }
            system("pause");
            system("cls");
            print_menu();
            break;
        }
        default:
            break;
        }
    }
    
    std::time_t rawtime = std::time({});
    std::time(&rawtime);
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
    std::time(&rawtime);
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
int validator_int(string str, int more_then_zero_flag)
{
    if (more_then_zero_flag == 1 && str[0] == '-')
        return SN;
    if (str.length() > 10)
        return SN;
    int result = 0;
    int minus_flag = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (i == 0 && str[i] == '-')
        {
            minus_flag = 1;
            continue;
        }
        if (!((int)str[i] >= 48 && (int)str[i] <= 57))
            return SN;
        else
        {
            result = 10 * result + (int)(str[i]) % 48;
        }
    }
    if (!minus_flag)
        return result;
    else
        return -result;
}
unsigned int validator_unsigned_int(string str)
{
    if (str[0] == '-' || str.length()==0)
        return SN;
    if (str.length() > 10)
        return SN;
    int result = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (!((int)str[i] >= 48 && (int)str[i] <= 57))
            return SN;
        else
        {
            result = 10 * result + (int)(str[i]) % 48;
        }
    }
    return result;
}