#include "Library.h"
#include "Book.h"
#include "Magazine.h"
#include "Newspaper.h"
#include "Utils.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_BORROW_DAYS = 14;

Library::Library() : next_pub_id(1) {
    publications.push_back(new Book(next_pub_id++, "Высшая математика", "Иванов А.А.", 2020, 450, "учебник"));
    publications.push_back(new Book(next_pub_id++, "Дискретная математика", "Иванов А.А.", 2021, 380, "учебник"));
    publications.push_back(new Book(next_pub_id++, "Физика для инженеров", "Петров Б.В.", 2019, 520, "учебник"));
    publications.push_back(new Book(next_pub_id++, "Программирование на C++", "Сидоров В.Г.", 2021, 640, "учебник"));
    publications.push_back(new Book(next_pub_id++, "Основы баз данных", "Козлова Е.М.", 2022, 300, "учебник"));
    publications.push_back(new Book(next_pub_id++, "Теория вероятностей", "Козлова Е.М.", 2021, 420, "учебник"));
    publications.push_back(new Book(next_pub_id++, "Методика решения задач", "Смирнов Д.А.", 2020, 250, "методическое пособие"));
    publications.push_back(new Book(next_pub_id++, "Практикум по программированию", "Васильева О.И.", 2021, 280, "методическое пособие"));
    publications.push_back(new Magazine(next_pub_id++, "Наука и жизнь", "Наука", 2024, 120, 5));
    publications.push_back(new Magazine(next_pub_id++, "Вокруг света", "Путешествия", 2024, 100, 3));
    publications.push_back(new Newspaper(next_pub_id++, "Какой вред в пропусках ПнаЯВУ? Шок Никита Драбудько, главный отличник, оказался прогульщиком!!!", "Пресса", 24, "15.09.2026"));
    publications.push_back(new Newspaper(next_pub_id++, "Известия", "Пресса",  20, "20.09.2024"));

    borrow_dates.resize(publications.size(), 0);

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

Library::~Library() {
    for (auto* pub : publications) {
        delete pub;
    }
}

int Library::find_pub_index(const Publication* pub) const {
    for (size_t i = 0; i < publications.size(); i++) {
        if (publications[i] == pub) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int Library::get_days_left(const Publication* pub) const {
    int idx = find_pub_index(pub);
    if (idx == -1) return 0;
    if (borrow_dates[idx] == 0) return 0;

    time_t borrow = borrow_dates[idx];
    time_t now = time(0);
    int borrow_days = static_cast<int>(borrow / (24 * 60 * 60));
    int now_days = static_cast<int>(now / (24 * 60 * 60));
    int days_passed = now_days - borrow_days;

    return MAX_BORROW_DAYS - days_passed;
}

bool Library::is_overdue(const Publication* pub) const {
    if (pub->is_available()) return false;
    return get_days_left(pub) < 0;
}

Library& Library::operator+=(Publication* pub) {
    add_publication(pub);
    return *this;
}

Library& Library::operator-=(Publication* pub) {
    for (size_t i = 0; i < publications.size(); i++) {
        if (publications[i] == pub) {
            if (publications[i]->is_borrowed()) {
                throw BookIsBorrowedException(publications[i]->get_title());
            }
            publications.erase(publications.begin() + i);
            borrow_dates.erase(borrow_dates.begin() + i);
            cout << "[OK] Издание удалено через -=" << endl;
            delete pub;
            return *this;
        }
    }
    throw BookNotFoundException();
}

Library& Library::operator+=(const Reader& reader) {
    add_reader(reader);
    return *this;
}

Library& Library::operator-=(const Reader& reader) {
    for (size_t i = 0; i < readers.size(); i++) {
        if (readers[i] == reader) {
            readers.erase(readers.begin() + i);
            cout << "[OK] Читатель удалён через -=" << endl;
            return *this;
        }
    }
    throw ReaderNotFoundException();
}

void Library::add_publication(Publication* pub) {
    for (const auto* p : publications) {
        if (p->get_title() == pub->get_title() && p->get_author() == pub->get_author()) {
            throw DuplicateBookException("такое название и автор уже есть");
        }
    }
    publications.push_back(pub);
    borrow_dates.push_back(0);
    cout << "[OK] Издание \"" << pub->get_title() << "\" добавлено!" << endl;
}

void Library::add_reader(const Reader& reader) {
    for (const auto& r : readers) {
        if (r.get_name() == reader.get_name()) {
            throw DuplicateReaderException(reader.get_name());
        }
    }
    readers.push_back(reader);
    cout << "[OK] Читатель \"" << reader.get_name() << "\" зарегистрирован" << endl;
}

void Library::remove_publication(Publication* pub) {
    if (pub->is_borrowed()) {
        throw BookIsBorrowedException(pub->get_title());
    }
    for (size_t i = 0; i < publications.size(); i++) {
        if (publications[i] == pub) {
            publications.erase(publications.begin() + i);
            borrow_dates.erase(borrow_dates.begin() + i);
            delete pub;
            cout << "[OK] Издание удалено!" << endl;
            return;
        }
    }
    throw BookNotFoundException();
}

const vector<Publication*>& Library::get_publications() const { return publications; }
const vector<Reader>& Library::get_readers() const { return readers; }
vector<Reader>& Library::get_readers_mutable() { return readers; }

Publication* Library::find_publication_by_title(const string& title) {
    for (auto* pub : publications) {
        if (pub->get_title() == title) return pub;
    }
    return nullptr;
}

vector<Publication*> Library::find_available_publications() {
    vector<Publication*> result;
    for (auto* pub : publications) {
        if (pub->is_available()) result.push_back(pub);
    }
    return result;
}

vector<Publication*> Library::find_borrowed_publications() {
    vector<Publication*> result;
    for (auto* pub : publications) {
        if (pub->is_borrowed()) result.push_back(pub);
    }
    return result;
}

Reader* Library::find_reader_by_id(int id) {
    for (auto& reader : readers) {
        if (reader.get_id() == id) return &reader;
    }
    return nullptr;
}

void Library::borrow_publication(Publication* pub, Reader* reader) {
    try {
        pub->borrow_book(reader);
        int idx = find_pub_index(pub);
        if (idx == -1) throw BookNotFoundException();
        borrow_dates[idx] = time(0);

        cout << "[OK] Издание \"" << pub->get_title() << "\" выдано "
            << reader->get_name() << endl;
    }
    catch (const exception& e) {
        throw BorrowException(e.what());
    }
}

void Library::return_publication(Publication* pub) {
    try {
        Reader* reader = pub->get_borrowed_by();
        pub->return_book();
        int idx = find_pub_index(pub);
        if (idx != -1) borrow_dates[idx] = 0;

        cout << "[OK] Издание \"" << pub->get_title() << "\" возвращено";
        if (reader) cout << " (читатель " << reader->get_name() << ")";
        cout << endl;
    }
    catch (const exception& e) {
        throw ReturnException(e.what());
    }
}

void Library::display_all_publications() const {
    cout << "\nКАТАЛОГ ИЗДАНИЙ (" << publications.size() << " шт.)" << endl;
    cout << "-------------------------------------------" << endl;

    for (size_t i = 0; i < publications.size(); i++) {
        cout << "* " << publications[i]->short_line();

        if (publications[i]->is_borrowed()) {
            int days = get_days_left(publications[i]);
            if (days > 0) cout << " (осталось " << days << " дн.)";
            else if (days == 0) cout << " (последний день)";
            else cout << " (ПРОСРОЧЕНА на " << -days << " дн.!)";
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

void Library::display_overdue_publications() const {
    cout << "\nПРОСРОЧЕННЫЕ ИЗДАНИЯ:" << endl;
    cout << "-------------------------------------------" << endl;

    bool has_overdue = false;
    for (size_t i = 0; i < publications.size(); i++) {
        if (publications[i]->is_borrowed() && borrow_dates[i] != 0) {
            int days = get_days_left(publications[i]);
            if (days < 0) {
                cout << "* " << publications[i]->get_title()
                    << " (" << publications[i]->get_author() << ")" << endl;
                cout << "  Тип: " << publications[i]->get_type() << endl;
                cout << "  Просрочена на " << -days << " дн." << endl;
                has_overdue = true;
            }
        }
    }

    if (!has_overdue) cout << "Просроченных изданий нет" << endl;
    cout << "-------------------------------------------" << endl;
}

void Library::display_publication_info(Publication* pub) {
    pub->display_info();
}

void Library::display_reader_info(Reader* reader) {
    cout << *reader << endl;
    reader->display_info();
}

void Library::display_all_types_info() const {
    cout << "\n=== ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА ===" << endl;

    for (auto* pub : publications) {
        cout << "\n--- " << pub->get_type() << " ---" << endl;
        cout << "Название: " << pub->get_title() << endl;
        cout << "Автор: " << pub->get_author() << endl;
        cout << "Год: " << pub->get_year() << endl;
        cout << "Страниц: " << pub->get_pages() << endl;
        cout << pub->get_field_name() << ": " << pub->get_field() << endl;
        cout << "Стоимость: " << pub->calculate_price() << " руб." << endl;
    }
}

void Library::compare_two_publications() const {
    cout << "\n--- СРАВНЕНИЕ ДВУХ ИЗДАНИЙ ---" << endl;

    if (publications.size() < 2) {
        cout << "[ОШИБКА] В библиотеке меньше двух изданий." << endl;
        return;
    }

    vector<string> lines1;
    for (const auto* p : publications) lines1.push_back(p->short_line());
    int idx1 = select_from_list(lines1, "Выберите первое издание:");
    if (idx1 < 0) return;

    vector<string> lines2;
    for (const auto* p : publications) lines2.push_back(p->short_line());
    int idx2 = select_from_list(lines2, "Выберите второе издание:");
    if (idx2 < 0) return;

    const Publication* p1 = publications[idx1];
    const Publication* p2 = publications[idx2];

    cout << "\n--- ВЫБРАННЫЕ ИЗДАНИЯ ---" << endl;
    cout << "Издание 1: " << *p1 << endl;
    cout << "Издание 2: " << *p2 << endl;

    cout << "\n--- СРАВНЕНИЕ ПО СТРАНИЦАМ ---" << endl;
    cout << "p1 < p2 (по страницам)?  " << (*p1 < *p2 ? "ДА" : "НЕТ") << endl;
    cout << "p1 > p2 (по страницам)?  " << (*p1 > *p2 ? "ДА" : "НЕТ") << endl;

    cout << "\n--- СРАВНЕНИЕ ПО ГОДУ ---" << endl;
    cout << "p1 == p2 (по году)?  " << (*p1 == *p2 ? "ДА" : "НЕТ") << endl;
    cout << "p1 != p2 (по году)?  " << (*p1 != *p2 ? "ДА" : "НЕТ") << endl;
    cout << "p1 <= p2 (по году)?  " << (*p1 <= *p2 ? "ДА" : "НЕТ") << endl;
    cout << "p1 >= p2 (по году)?  " << (*p1 >= *p2 ? "ДА" : "НЕТ") << endl;
}

void Library::compare_two_readers() const {
    cout << "\n--- СРАВНЕНИЕ ДВУХ ЧИТАТЕЛЕЙ ---" << endl;

    if (readers.size() < 2) {
        cout << "[ОШИБКА] Меньше двух читателей." << endl;
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

    cout << "\nИздание 1: " << r1 << endl;
    cout << "Издание 2: " << r2 << endl;
    cout << "r1 < r2 (по ID)?    " << (r1 < r2 ? "ДА" : "НЕТ") << endl;
    cout << "r1 > r2 (по ID)?    " << (r1 > r2 ? "ДА" : "НЕТ") << endl;
    cout << "r1 == r2 (по имени)? " << (r1 == r2 ? "ДА" : "НЕТ") << endl;
    cout << "r1 != r2 (по имени)? " << (r1 != r2 ? "ДА" : "НЕТ") << endl;
}

void Library::change_reader_name(Reader* reader, string new_name) {
    if (new_name.empty() || is_blank(new_name)) {
        throw InvalidReaderNameException();
    }
    for (const auto& r : readers) {
        if (&r != reader && r.get_name() == new_name) {
            throw DuplicateReaderException(new_name);
        }
    }
    reader->set_name(new_name);
    cout << "[OK] ФИО изменено" << endl;
}

void Library::change_reader_phone(Reader* reader, string new_phone) {
    reader->set_phone(new_phone);
    cout << "[OK] Телефон изменён" << endl;
}

int Library::get_publication_count() const { return publications.size(); }
int Library::get_reader_count() const { return readers.size(); }