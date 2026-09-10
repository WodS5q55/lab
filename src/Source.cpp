/*#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>

using namespace std;

class Reader {
private:
    string full_name;
    string phone;
    int reader_id;
    static int next_id;

public:
    Reader(string name, string phone_num) {
        if (name.empty()) {
            throw invalid_argument("Имя читателя не может быть пустым");
        }
        full_name = name;
        phone = phone_num;
        reader_id = next_id++;
    }

    string get_name() const { return full_name; }
    string get_phone() const { return phone; }
    int get_id() const { return reader_id; }

    void set_phone(string new_phone) {
        if (new_phone.length() < 5) {
            throw invalid_argument("Номер телефона слишком короткий");
        }
        phone = new_phone;
    }

    void display_info() const {
        cout << "-------------------------------------------" << endl;
        cout << "ЧИТАТЕЛЬ" << endl;
        cout << "ID: " << reader_id << endl;
        cout << "ФИО: " << full_name << endl;
        cout << "Телефон: " << phone << endl;
        cout << "-------------------------------------------" << endl;
    }
};

int Reader::next_id = 1;

enum BookStatus {
    AVAILABLE,
    BORROWED
};

string status_to_string(BookStatus status, int days_left) {
    switch (status) {
    case AVAILABLE:
        return "Доступна";
    case BORROWED:
        if (days_left > 0) {
            return "Выдана (осталось " + to_string(days_left) + " дн.)";
        }
        return "Выдана ПРОСРОЧЕНА!";
    }
    return "Неизвестно";
}

class Book {
private:
    string title;
    string author;
    int year;
    string type;
    BookStatus status;
    int borrowed_by;
    int days_left;

public:
    Book(string book_title, string book_author, int pub_year, string book_type) {
        if (book_title.empty() || book_author.empty()) {
            throw invalid_argument("Название и автор книги не могут быть пустыми");
        }
        if (pub_year < 0 || pub_year > 2026) {
            throw invalid_argument("Некорректный год издания");
        }
        if (book_type != "учебник" && book_type != "методическое пособие" && book_type != "монография") {
            throw invalid_argument("Тип книги должен быть: учебник, методическое пособие или монография");
        }
        title = book_title;
        author = book_author;
        year = pub_year;
        type = book_type;
        status = AVAILABLE;
        borrowed_by = -1;
        days_left = 0;
    }

    string get_title() const { return title; }
    string get_author() const { return author; }
    int get_year() const { return year; }
    string get_type() const { return type; }
    BookStatus get_status() const { return status; }
    int get_borrowed_by() const { return borrowed_by; }
    int get_days_left() const { return days_left; }

    void borrow_book(int reader_id, int days = 14) {
        if (status != AVAILABLE) {
            throw logic_error("Книга недоступна для выдачи");
        }
        status = BORROWED;
        borrowed_by = reader_id;
        days_left = days;
    }

    void return_book() {
        if (status != BORROWED) {
            throw logic_error("Книга не была выдана");
        }
        status = AVAILABLE;
        borrowed_by = -1;
        days_left = 0;
    }

    void decrease_days() {
        if (status == BORROWED && days_left > 0) {
            days_left--;
        }
    }

    bool is_overdue() const {
        return (status == BORROWED && days_left <= 0);
    }

    string short_line() const {
        return title + " - " + author + " [" + type + "] - " + status_to_string(status, days_left);
    }

    void display_info() const {
        cout << "-------------------------------------------" << endl;
        cout << "КНИГА" << endl;
        cout << "Название: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "Год издания: " << year << endl;
        cout << "Тип: " << type << endl;
        cout << "Статус: " << status_to_string(status, days_left) << endl;
        if (status == BORROWED) {
            cout << "Выдана читателю ID: " << borrowed_by << endl;
            if (is_overdue()) {
                cout << "[ВНИМАНИЕ] КНИГА ПРОСРОЧЕНА!" << endl;
            }
        }
        cout << "-------------------------------------------" << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Reader> readers;
    int day_counter;

    void print_book_line(const Book& book, bool with_author) const {
        cout << "* " << book.get_title();
        if (with_author) {
            cout << " (" << book.get_author() << ", " << book.get_year() << " г.)";
        }
        else {
            cout << " (" << book.get_year() << " г.) [" << book.get_type() << "]";
        }
        cout << " - " << status_to_string(book.get_status(), book.get_days_left()) << endl;
    }

public:
    Library() {
        day_counter = 1;

        books.push_back(Book("Высшая математика", "Иванов А.А.", 2020, "учебник"));
        books.push_back(Book("Дискретная математика", "Иванов А.А.", 2021, "учебник"));
        books.push_back(Book("Физика для инженеров", "Петров Б.В.", 2019, "учебник"));
        books.push_back(Book("Программирование на C++", "Сидоров В.Г.", 2021, "учебник"));
        books.push_back(Book("Основы баз данных", "Козлова Е.М.", 2022, "учебник"));
        books.push_back(Book("Теория вероятностей", "Козлова Е.М.", 2021, "учебник"));
        books.push_back(Book("Методика решения задач по физике", "Смирнов Д.А.", 2020, "методическое пособие"));
        books.push_back(Book("Практикум по программированию", "Васильева О.И.", 2021, "методическое пособие"));
        books.push_back(Book("Современные алгоритмы машинного обучения", "Новиков С.П.", 2023, "монография"));
        books.push_back(Book("Искусственный интеллект и нейросети", "Михайлов А.Н.", 2022, "монография"));

        readers.push_back(Reader("Алексей Иванов", "+375292245423"));
        readers.push_back(Reader("Никита Драбудько", "+375684539212"));
        readers.push_back(Reader("Дмитрий Сидоров", "+375197652934"));
        readers.push_back(Reader("Елена Смирнова", "+375451783256"));
        readers.push_back(Reader("Ольга Кузнецова", "+375998563341"));
        readers.push_back(Reader("Сергей Новиков", "+375872114598"));
        readers.push_back(Reader("Анна Васильева", "+375759938782"));
        readers.push_back(Reader("Игорь Михайлов", "+375344436121"));
        readers.push_back(Reader("Наталья Морозова", "+375875596214"));
        readers.push_back(Reader("Павел Козлов", "+375859967546"));

        books[2].borrow_book(readers[0].get_id(), 14);
        books[6].borrow_book(readers[1].get_id(), 1);

        for (int i = 0; i < 2; i++) {
            for (auto& book : books) {
                if (book.get_status() == BORROWED && book.get_days_left() > 0) {
                    book.decrease_days();
                }
            }
        }

    }

    void add_reader(const Reader& reader) {
        for (const auto& r : readers) {
            if (r.get_name() == reader.get_name()) {
                throw invalid_argument("Читатель с таким именем уже зарегистрирован");
            }
        }
        readers.push_back(reader);
        cout << "[OK] Читатель \"" << reader.get_name() << "\" зарегистрирован (ID: " << reader.get_id() << ")" << endl;
    }

    const vector<Book>& get_books() const { return books; }
    const vector<Reader>& get_readers() const { return readers; }

    Book* find_book_by_title(const string& title) {
        for (auto& book : books) {
            if (book.get_title() == title) {
                return &book;
            }
        }
        return nullptr;
    }

    vector<Book*> find_books_by_author(const string& author) {
        vector<Book*> result;
        for (auto& book : books) {
            if (book.get_author() == author) {
                result.push_back(&book);
            }
        }
        return result;
    }

    vector<Book*> find_books_by_type(const string& type) {
        vector<Book*> result;
        for (auto& book : books) {
            if (book.get_type() == type) {
                result.push_back(&book);
            }
        }
        return result;
    }

    vector<Book*> find_available_books() {
        vector<Book*> result;
        for (auto& book : books) {
            if (book.get_status() == AVAILABLE) {
                result.push_back(&book);
            }
        }
        return result;
    }

    vector<Book*> find_borrowed_books() {
        vector<Book*> result;
        for (auto& book : books) {
            if (book.get_status() == BORROWED) {
                result.push_back(&book);
            }
        }
        return result;
    }

    vector<string> get_distinct_authors() const {
        vector<string> authors;
        for (const auto& book : books) {
            if (find(authors.begin(), authors.end(), book.get_author()) == authors.end()) {
                authors.push_back(book.get_author());
            }
        }
        return authors;
    }

    Reader* find_reader_by_id(int id) {
        for (auto& reader : readers) {
            if (reader.get_id() == id) {
                return &reader;
            }
        }
        return nullptr;
    }

    void borrow_book(Book* book, Reader* reader) {
        try {
            book->borrow_book(reader->get_id());
            cout << "[OK] Книга \"" << book->get_title() << "\" выдана студенту "
                << reader->get_name() << " (ID: " << reader->get_id() << ")" << endl;
            cout << "     Срок возврата: через 14 дней" << endl;
        }
        catch (const exception& e) {
            throw runtime_error(string("Ошибка выдачи: ") + e.what());
        }
    }

    void return_book(Book* book) {
        try {
            int reader_id = book->get_borrowed_by();
            book->return_book();
            cout << "[OK] Книга \"" << book->get_title() << "\" возвращена в библиотеку";
            if (reader_id != -1) {
                Reader* reader = find_reader_by_id(reader_id);
                if (reader) {
                    cout << " (читатель " << reader->get_name() << ")";
                }
            }
            cout << endl;
        }
        catch (const exception& e) {
            throw runtime_error(string("Ошибка возврата: ") + e.what());
        }
    }

    void pass_day() {
        day_counter++;
        cout << "\n[ДЕНЬ " << day_counter << "]" << endl;
        cout << "-------------------------------------------" << endl;

        bool has_changes = false;
        for (auto& book : books) {
            if (book.get_status() == BORROWED && book.get_days_left() > 0) {
                book.decrease_days();
                has_changes = true;
            }
        }
        if (has_changes) {
            cout << "Прошёл один день. Сроки возврата уменьшены." << endl;
        }
        else {
            cout << "Нет активных выдач." << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    void display_all_books() const {
        cout << "\nБИБЛИОТЕЧНЫЙ КАТАЛОГ (" << books.size() << " книг)" << endl;
        cout << "-------------------------------------------" << endl;
        for (const auto& book : books) {
            cout << "* " << book.get_title() << " (" << book.get_author() << ", "
                << book.get_year() << " г.) [" << book.get_type() << "] - "
                << status_to_string(book.get_status(), book.get_days_left()) << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    void display_all_readers() const {
        cout << "\nСПИСОК ЧИТАТЕЛЕЙ (" << readers.size() << " чел.)" << endl;
        cout << "-------------------------------------------" << endl;
        for (const auto& reader : readers) {
            cout << "ID " << reader.get_id() << ": " << reader.get_name()
                << " (тел.: " << reader.get_phone() << ")" << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    void display_overdue_books() const {
        cout << "\nПРОСРОЧЕННЫЕ КНИГИ:" << endl;
        cout << "-------------------------------------------" << endl;
        bool has_overdue = false;
        for (const auto& book : books) {
            if (book.is_overdue()) {
                cout << "* " << book.get_title() << " (" << book.get_author() << ")" << endl;
                cout << "  Выдана читателю ID: " << book.get_borrowed_by() << endl;
                has_overdue = true;
            }
        }
        if (!has_overdue) {
            cout << "Просроченных книг нет" << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    void display_book_info(Book* book) {
        book->display_info();
    }

    void display_reader_info(Reader* reader) {
        reader->display_info();
    }

    void change_reader_phone(Reader* reader, string new_phone) {
        reader->set_phone(new_phone);
        cout << "[OK] Телефон читателя ID " << reader->get_id() << " изменён на: " << new_phone << endl;
    }

    void print_books_by_author(const string& author) {
        vector<Book*> found = find_books_by_author(author);
        cout << "\nКНИГИ АВТОРА \"" << author << "\":" << endl;
        cout << "-------------------------------------------" << endl;
        if (found.empty()) {
            cout << "Книг этого автора не найдено" << endl;
            return;
        }
        for (const auto& book : found) {
            print_book_line(*book, false);
        }
        cout << "-------------------------------------------" << endl;
    }

    void print_books_by_type(const string& type) {
        vector<Book*> found = find_books_by_type(type);
        cout << "\nКНИГИ ТИПА \"" << type << "\":" << endl;
        cout << "-------------------------------------------" << endl;
        if (found.empty()) {
            cout << "Книг этого типа не найдено" << endl;
            return;
        }
        for (const auto& book : found) {
            print_book_line(*book, true);
        }
        cout << "-------------------------------------------" << endl;
    }

    int get_book_count() const { return books.size(); }
    int get_reader_count() const { return readers.size(); }
    int get_day_counter() const { return day_counter; }
};

void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int select_from_list(const vector<string>& items, const string& prompt) {
    if (items.empty()) {
        cout << "Список пуст." << endl;
        return -1;
    }
    cout << "\n" << prompt << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << "  " << (i + 1) << ". " << items[i] << endl;
    }
    cout << "  0. Отмена" << endl;
    cout << "Выберите номер: ";

    int choice;
    cin >> choice;
    if (cin.fail()) {
        clear_input();
        cout << "[ОШИБКА] Введите число." << endl;
        return -1;
    }
    if (choice == 0) {
        cout << "Отменено." << endl;
        return -1;
    }
    if (choice < 1 || static_cast<size_t>(choice) > items.size()) {
        cout << "[ОШИБКА] Неверный номер." << endl;
        return -1;
    }
    return choice - 1;
}

Book* select_book(vector<Book*>& candidates, const string& prompt) {
    vector<string> lines;
    for (auto* book : candidates) {
        lines.push_back(book->short_line());
    }
    int idx = select_from_list(lines, prompt);
    if (idx < 0) return nullptr;
    return candidates[static_cast<size_t>(idx)];
}

Reader* select_reader(Library& library, const string& prompt) {
    vector<string> lines;
    const vector<Reader>& readers = library.get_readers();
    for (const auto& reader : readers) {
        lines.push_back(reader.get_name() + " (ID: " + to_string(reader.get_id())
            + ", тел.: " + reader.get_phone() + ")");
    }
    int idx = select_from_list(lines, prompt);
    if (idx < 0) return nullptr;
    return library.find_reader_by_id(readers[static_cast<size_t>(idx)].get_id());
}

Book* select_any_book(Library& library, const string& prompt) {
    vector<Book*> all;
    for (const auto& b : library.get_books()) {
        all.push_back(library.find_book_by_title(b.get_title()));
    }
    return select_book(all, prompt);
}

void show_menu(const Library& library) {
    cout << "\n===========================================" << endl;
    cout << "       УНИВЕРСИТЕТСКАЯ БИБЛИОТЕКА" << endl;
    cout << "===========================================" << endl;
    cout << "1. Зарегистрировать читателя" << endl;
    cout << "2. Выдать книгу" << endl;
    cout << "3. Вернуть книгу" << endl;
    cout << "4. Показать все книги" << endl;
    cout << "5. Показать всех читателей" << endl;
    cout << "6. Показать информацию о книге" << endl;
    cout << "7. Показать информацию о читателе" << endl;
    cout << "8. Изменить телефон читателя" << endl;
    cout << "9. Показать просроченные книги" << endl;
    cout << "10. Найти книги по автору" << endl;
    cout << "11. Найти книги по типу" << endl;
    cout << "12. Пропустить день (уменьшить сроки)" << endl;
    cout << "0. Выход" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Текущий день: " << library.get_day_counter() << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Выберите действие: ";
}

int main() {
#ifdef _WIN32
    setlocale(LC_ALL, "Russian");
#else
    setlocale(LC_ALL, "");
#endif

    Library library;
    int choice;

    cout << "\n===========================================" << endl;
    cout << "   ДОБРО ПОЖАЛОВАТЬ В УНИВЕРСИТЕТСКУЮ БИБЛИОТЕКУ!" << endl;
    cout << "===========================================" << endl;

    do {
        show_menu(library);
        cin >> choice;

        if (cin.fail()) {
            clear_input();
            cout << "[ОШИБКА] Введите число!" << endl;
            continue;
        }

        try {
            switch (choice) {
            case 1: {
                string name, phone;
                cout << "Введите ФИО читателя: ";
                clear_input();
                getline(cin, name);
                cout << "Введите номер телефона: ";
                getline(cin, phone);
                Reader reader(name, phone);
                library.add_reader(reader);
                break;
            }
            case 2: {
                vector<Book*> available = library.find_available_books();
                if (available.empty()) {
                    cout << "[ОШИБКА] Нет доступных книг для выдачи." << endl;
                    break;
                }
                Book* book = select_book(available, "Выберите книгу для выдачи:");
                if (!book) break;

                Reader* reader = select_reader(library, "Выберите читателя:");
                if (!reader) break;

                library.borrow_book(book, reader);
                break;
            }
            case 3: {
                vector<Book*> borrowed = library.find_borrowed_books();
                if (borrowed.empty()) {
                    cout << "[ОШИБКА] Нет выданных книг для возврата." << endl;
                    break;
                }
                Book* book = select_book(borrowed, "Выберите книгу для возврата:");
                if (!book) break;

                library.return_book(book);
                break;
            }
            case 4:
                library.display_all_books();
                break;
            case 5:
                library.display_all_readers();
                break;
            case 6: {
                Book* book = select_any_book(library, "Выберите книгу для просмотра информации:");
                if (!book) break;
                library.display_book_info(book);
                break;
            }
            case 7: {
                Reader* reader = select_reader(library, "Выберите читателя для просмотра информации:");
                if (!reader) break;
                library.display_reader_info(reader);
                break;
            }
            case 8: {
                Reader* reader = select_reader(library, "Выберите читателя для изменения телефона:");
                if (!reader) break;

                string phone;
                cout << "Введите новый номер телефона: ";
                clear_input();
                getline(cin, phone);
                library.change_reader_phone(reader, phone);
                break;
            }
            case 9:
                library.display_overdue_books();
                break;
            case 10: {
                vector<string> authors = library.get_distinct_authors();
                if (authors.empty()) {
                    cout << "[ОШИБКА] Нет авторов в каталоге." << endl;
                    break;
                }
                int idx = select_from_list(authors, "Выберите автора:");
                if (idx < 0) break;
                library.print_books_by_author(authors[static_cast<size_t>(idx)]);
                break;
            }
            case 11: {
                vector<string> types = { "учебник", "методическое пособие", "монография" };
                int idx = select_from_list(types, "Выберите тип книги:");
                if (idx < 0) break;
                library.print_books_by_type(types[static_cast<size_t>(idx)]);
                break;
            }
            case 12:
                library.pass_day();
                break;
            case 0:
                cout << "\nДо свидания!" << endl;
                break;
            default:
                cout << "[ОШИБКА] Неверный выбор. Попробуйте снова." << endl;
            }
        }
        catch (const exception& e) {
            cout << "[ОШИБКА] " << e.what() << endl;
            clear_input();
        }

    } while (choice != 0);

    return 0;
}*/