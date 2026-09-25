#include "Library.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

const int MAX_BORROW_DAYS = 14;

Library::Library() : next_book_id(1) {
    books.push_back(Book(next_book_id++, "Высшая математика", "Иванов А.А.", 2020, "учебник"));
    books.push_back(Book(next_book_id++, "Дискретная математика", "Иванов А.А.", 2021, "учебник"));
    books.push_back(Book(next_book_id++, "Физика для инженеров", "Петров Б.В.", 2019, "учебник"));
    books.push_back(Book(next_book_id++, "Программирование на C++", "Сидоров В.Г.", 2021, "учебник"));
    books.push_back(Book(next_book_id++, "Основы баз данных", "Козлова Е.М.", 2022, "учебник"));
    books.push_back(Book(next_book_id++, "Теория вероятностей", "Козлова Е.М.", 2021, "учебник"));
    books.push_back(Book(next_book_id++, "Методика решения задач по физике", "Смирнов Д.А.", 2020, "методическое пособие"));
    books.push_back(Book(next_book_id++, "Практикум по программированию", "Васильева О.И.", 2021, "методическое пособие"));
    books.push_back(Book(next_book_id++, "Современные алгоритмы машинного обучения", "Новиков С.П.", 2023, "монография"));
    books.push_back(Book(next_book_id++, "Искусственный интеллект и нейросети", "Михайлов А.Н.", 2022, "монография"));

    borrow_dates.resize(books.size(), 0);

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

}

int Library::find_book_index(const Book* book) const {
    for (size_t i = 0; i < books.size(); i++) {
        if (&books[i] == book) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int Library::get_days_left(const Book* book) const {
    int idx = find_book_index(book);
    if (idx == -1) return 0;
    if (borrow_dates[idx] == 0) return 0;

    time_t borrow = borrow_dates[idx];
    time_t now = time(0);

    int borrow_days = static_cast<int>(borrow / (24 * 60 * 60));
    int now_days = static_cast<int>(now / (24 * 60 * 60));

    int days_passed = now_days - borrow_days;

    return MAX_BORROW_DAYS - days_passed;
}

bool Library::is_overdue(const Book* book) const {
    if (book->is_available()) return false;
    return get_days_left(book) < 0;
}

time_t Library::get_borrow_date(const Book* book) const {
    int idx = find_book_index(book);
    return (idx != -1) ? borrow_dates[idx] : 0;
}

Library& Library::operator+=(const Book& book) {
    add_book(book);
    return *this;
}

Library& Library::operator-=(const Book& book) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i] == book) {
            if (books[i].is_borrowed()) {
                throw logic_error("Нельзя удалить выданную книгу: \"" + books[i].get_title() + "\"");
            }
            books.erase(books.begin() + i);
            borrow_dates.erase(borrow_dates.begin() + i);
            cout << "[OK] Книга \"" << book.get_title() << "\" удалена через -=" << endl;
            return *this;
        }
    }
    throw invalid_argument("Книга не найдена");
}

Library& Library::operator+=(const Reader& reader) {
    add_reader(reader);
    return *this;
}

Library& Library::operator-=(const Reader& reader) {
    for (size_t i = 0; i < readers.size(); i++) {
        if (readers[i] == reader) {
            readers.erase(readers.begin() + i);
            cout << "[OK] Читатель \"" << reader.get_name() << "\" удалён через -=" << endl;
            return *this;
        }
    }
    throw invalid_argument("Читатель не найден");
}

void Library::add_book(const Book& book) {
    if (book.get_title().empty() || is_blank(book.get_title())) {
        throw invalid_argument("Название книги не может быть пустым");
    }
    if (book.get_author().empty() || is_blank(book.get_author())) {
        throw invalid_argument("Автор книги не может быть пустым");
    }
    if (book.get_year() < 1452 || book.get_year() > 2026) {
        throw invalid_argument("Год издания должен быть от 1452 до 2026");
    }
    string type = book.get_type();
    if (type != "учебник" && type != "методическое пособие" && type != "монография") {
        throw invalid_argument("Тип книги должен быть: учебник, методическое пособие или монография");
    }
    for (const auto& b : books) {
        if (b == book) {
            throw invalid_argument("Книга с таким ID уже существует");
        }
    }
    for (const auto& b : books) {
        if (b.get_title() == book.get_title() && b.get_author() == book.get_author()) {
            throw invalid_argument("Книга с таким названием и автором уже существует");
        }
    }
    books.push_back(book);
    borrow_dates.push_back(0);
    cout << "[OK] Книга \"" << book.get_title() << "\" добавлена в библиотеку!" << endl;
}

void Library::add_reader(const Reader& reader) {
    for (const auto& r : readers) {
        if (r.get_name() == reader.get_name()) {
            throw invalid_argument("Читатель с таким именем уже зарегистрирован");
        }
    }
    readers.push_back(reader);
    cout << "[OK] Читатель \"" << reader.get_name() << "\" зарегистрирован" << endl;
}

void Library::remove_book(Book* book) {
    if (book->is_borrowed()) {
        throw logic_error("Нельзя удалить книгу, которая выдана читателю");
    }

    for (size_t i = 0; i < books.size(); i++) {
        if (&books[i] == book) {
            books.erase(books.begin() + i);
            borrow_dates.erase(borrow_dates.begin() + i);
            cout << "[OK] Книга \"" << book->get_title() << "\" удалена из библиотеки!" << endl;
            return;
        }
    }
    throw invalid_argument("Книга не найдена");
}

const vector<Book>& Library::get_books() const { return books; }
const vector<Reader>& Library::get_readers() const { return readers; }
vector<Book>& Library::get_books_mutable() { return books; }
vector<Reader>& Library::get_readers_mutable() { return readers; }

Book* Library::find_book_by_title(const string& title) {
    for (auto& book : books) {
        if (book.get_title() == title) {
            return &book;
        }
    }
    return nullptr;
}

vector<Book*> Library::find_available_books() {
    vector<Book*> result;
    for (auto& book : books) {
        if (book.is_available()) {
            result.push_back(&book);
        }
    }
    return result;
}

vector<Book*> Library::find_borrowed_books() {
    vector<Book*> result;
    for (auto& book : books) {
        if (book.is_borrowed()) {
            result.push_back(&book);
        }
    }
    return result;
}

Reader* Library::find_reader_by_id(int id) {
    for (auto& reader : readers) {
        if (reader.get_id() == id) {
            return &reader;
        }
    }
    return nullptr;
}

void Library::borrow_book(Book* book, Reader* reader) {
    book->borrow_book(reader);

    int idx = find_book_index(book);
    if (idx == -1) {
        throw runtime_error("Книга не найдена в каталоге");
    }
    borrow_dates[idx] = time(0);

    cout << "[OK] Книга \"" << book->get_title() << "\" выдана студенту "
        << reader->get_name() << " (ID: " << reader->get_id() << ")" << endl;
    cout << "     Срок возврата: " << MAX_BORROW_DAYS << " дней" << endl;
}

void Library::return_book(Book* book) {
    Reader* reader = book->get_borrowed_by();
    book->return_book();

    int idx = find_book_index(book);
    if (idx != -1) {
        borrow_dates[idx] = 0;
    }

    cout << "[OK] Книга \"" << book->get_title() << "\" возвращена в библиотеку";
    if (reader != nullptr) {
        cout << " (читатель " << reader->get_name() << ")";
    }
    cout << endl;
}

void Library::display_all_books() const {
    cout << "\nБИБЛИОТЕЧНЫЙ КАТАЛОГ (" << books.size() << " книг)" << endl;
    cout << "-------------------------------------------" << endl;

    for (size_t i = 0; i < books.size(); i++) {
        cout << "* ID: " << books[i].get_id() << " | ";   
        cout << books[i].get_title()
            << " (" << books[i].get_author() << ", " << books[i].get_year() << " г.) "
            << "[" << books[i].get_type() << "] - ";

        if (books[i].is_available()) {
            cout << "Доступна";
        }
        else {
            int days = get_days_left(&books[i]);
            if (days > 0) {
                cout << "Выдана (осталось " << days << " дн.)";
            }
            else if (days == 0) {
                cout << "Выдана (последний день)";
            }
            else {
                cout << "ПРОСРОЧЕНА на " << -days << " дн.!";
            }
        }
        cout << endl;
    }
    cout << "-------------------------------------------" << endl;
}

void Library::display_all_readers() const {
    cout << "\nСПИСОК ЧИТАТЕЛЕЙ (" << readers.size() << " чел.)" << endl;
    cout << "-------------------------------------------" << endl;
    for (const auto& reader : readers) {
        cout << reader << endl;
    }
    cout << "-------------------------------------------" << endl;
}

void Library::display_overdue_books() const {
    cout << "\nПРОСРОЧЕННЫЕ КНИГИ:" << endl;
    cout << "-------------------------------------------" << endl;

    bool has_overdue = false;
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].is_borrowed() && borrow_dates[i] != 0) {
            int days = get_days_left(&books[i]);
            if (days < 0) {
                cout << "* " << books[i].get_title()
                    << " (" << books[i].get_author() << ")" << endl;
                cout << "  Просрочена на " << -days << " дн." << endl;
                cout << "  Выдана читателю: " << books[i].get_borrowed_by()->get_name()
                    << " (ID: " << books[i].get_borrowed_by()->get_id() << ")" << endl;
                has_overdue = true;
            }
        }
    }

    if (!has_overdue) {
        cout << "Просроченных книг нет" << endl;
    }
    cout << "-------------------------------------------" << endl;
}

void Library::display_book_info(Book* book) {
    cout << *book << endl;

    book->display_info();

    int idx = find_book_index(book);
    if (idx == -1) return;

    if (book->is_borrowed() && borrow_dates[idx] != 0) {
        tm ltm;
        localtime_s(&ltm, &borrow_dates[idx]);
        char buffer[11];
        strftime(buffer, 11, "%d.%m.%Y", &ltm);
        cout << "Дата выдачи: " << buffer << endl;

        int days = get_days_left(book);
        if (days > 0) {
            cout << "Осталось дней: " << days << endl;
        }
        else if (days == 0) {
            cout << "Последний день возврата!" << endl;
        }
        else {
            cout << "[ВНИМАНИЕ] Просрочена на " << -days << " дн.!" << endl;
        }
    }
}

void Library::display_reader_info(Reader* reader) {
    cout << *reader << endl;
    reader->display_info();
}

void Library::compare_two_books() const {
    cout << "\n--- СРАВНЕНИЕ ДВУХ КНИГ ---" << endl;

    if (books.size() < 2) {
        cout << "[ОШИБКА] В библиотеке меньше двух книг." << endl;
        return;
    }

    vector<const Book*> all;
    for (const auto& b : books) {
        all.push_back(&b);
    }

    vector<string> lines1;
    for (const auto* b : all) {
        lines1.push_back(b->short_line());
    }
    int idx1 = select_from_list(lines1, "Выберите первую книгу:");
    if (idx1 < 0) return;

    vector<string> lines2;
    for (const auto* b : all) {
        lines2.push_back(b->short_line());
    }
    int idx2 = select_from_list(lines2, "Выберите вторую книгу:");
    if (idx2 < 0) return;

    const Book* b1 = all[static_cast<size_t>(idx1)];
    const Book* b2 = all[static_cast<size_t>(idx2)];

    cout << "\n--- ВЫБРАННЫЕ КНИГИ ---" << endl;
    cout << "Книга 1: " << *b1 << endl;
    cout << "Книга 2: " << *b2 << endl;

    cout << "\n--- СРАВНЕНИЕ ПО ID (уникальный идентификатор) ---" << endl;
    cout << "b1 < b2 (по ID)?    " << (*b1 < *b2 ? "ДА" : "НЕТ") << endl;
    cout << "b1 > b2 (по ID)?    " << (*b1 > *b2 ? "ДА" : "НЕТ") << endl;

    cout << "\n--- СРАВНЕНИЕ ПО ГОДУ ИЗДАНИЯ ---" << endl;
    cout << "b1 == b2 (по году)? " << (*b1 == *b2 ? "ДА" : "НЕТ") << endl;
    cout << "b1 != b2 (по году)? " << (*b1 != *b2 ? "ДА" : "НЕТ") << endl;
    cout << "b1 <= b2 (по году)? " << (*b1 <= *b2 ? "ДА" : "НЕТ") << endl;
    cout << "b1 >= b2 (по году)? " << (*b1 >= *b2 ? "ДА" : "НЕТ") << endl;

}

void Library::compare_two_readers() const {
    cout << "\n--- СРАВНЕНИЕ ДВУХ ЧИТАТЕЛЕЙ ---" << endl;

    if (readers.size() < 2) {
        cout << "[ОШИБКА] В библиотеке меньше двух читателей." << endl;
        return;
    }

    vector<string> lines1;
    for (const auto& r : readers) {
        lines1.push_back(r.get_name() + " (ID: " + to_string(r.get_id()) + ")");
    }
    int idx1 = select_from_list(lines1, "Выберите первого читателя:");
    if (idx1 < 0) return;

    vector<string> lines2;
    for (const auto& r : readers) {
        lines2.push_back(r.get_name() + " (ID: " + to_string(r.get_id()) + ")");
    }
    int idx2 = select_from_list(lines2, "Выберите второго читателя:");
    if (idx2 < 0) return;

    const Reader& r1 = readers[idx1];
    const Reader& r2 = readers[idx2];

    cout << "\n--- ВЫБРАННЫЕ ЧИТАТЕЛИ ---" << endl;
    cout << "Читатель 1: " << r1 << endl;
    cout << "Читатель 2: " << r2 << endl;

    cout << "\n--- СРАВНЕНИЕ ПО ID (уникальный идентификатор) ---" << endl;
    cout << "r1 < r2 (по ID)?    " << (r1 < r2 ? "ДА" : "НЕТ") << endl;
    cout << "r1 > r2 (по ID)?    " << (r1 > r2 ? "ДА" : "НЕТ") << endl;

    cout << "\n--- СРАВНЕНИЕ ПО ИМЕНИ ---" << endl;
    cout << "r1 == r2 (по имени)? " << (r1 == r2 ? "ДА" : "НЕТ") << endl;
    cout << "r1 != r2 (по имени)? " << (r1 != r2 ? "ДА" : "НЕТ") << endl;
    cout << "r1 <= r2 (по имени)? " << (r1 <= r2 ? "ДА" : "НЕТ") << endl;
    cout << "r1 >= r2 (по имени)? " << (r1 >= r2 ? "ДА" : "НЕТ") << endl;

}

void Library::change_reader_name(Reader* reader, string new_name) {
    for (const auto& r : readers) {
        if (&r != reader && r.get_name() == new_name) {
            throw invalid_argument("Читатель с таким именем уже зарегистрирован");
        }
    }
    reader->set_name(new_name);
    cout << "[OK] ФИО читателя ID " << reader->get_id() << " изменено на: " << new_name << endl;
}

void Library::change_reader_phone(Reader* reader, string new_phone) {
    reader->set_phone(new_phone);
    cout << "[OK] Телефон читателя ID " << reader->get_id() << " изменён на: " << new_phone << endl;
}

void Library::print_book_line(const Book& book, bool with_author) const {
    cout << "* " << book.get_title();
    if (with_author) {
        cout << " (" << book.get_author() << ", " << book.get_year() << " г.)";
    }
    else {
        cout << " (" << book.get_year() << " г.) [" << book.get_type() << "]";
    }
    cout << " - " << (book.is_available() ? "Доступна" : "Выдана") << endl;
}

int Library::get_book_count() const { return books.size(); }
int Library::get_reader_count() const { return readers.size(); }