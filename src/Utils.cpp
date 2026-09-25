#include "Utils.h"
#include "Library.h"
#include "Exceptions.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

bool is_blank(const string& str) {
    for (char c : str) {
        if (!isspace(c)) return false;
    }
    return true;
}

void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void validate_book_fields(string title, string author, int year, string type) {
    if (title.empty() || is_blank(title)) {
        throw InvalidBookDataException("название пустое");
    }
    if (author.empty() || is_blank(author)) {
        throw InvalidBookDataException("автор пустой");
    }
    if (year < 1452 || year > 2026) {
        throw InvalidYearException(year);
    }
    if (type != "учебник" && type != "методическое пособие" && type != "монография") {
        throw InvalidBookTypeException(type);
    }
}

void validate_reader_fields(string name, string phone) {
    if (name.empty() || is_blank(name)) {
        throw InvalidReaderNameException();
    }
    if (phone.length() < 5) {
        throw InvalidPhoneException();
    }
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
    vector<Reader>& readers = library.get_readers_mutable();
    for (const auto& reader : readers) {
        lines.push_back(reader.get_name() + " (ID: " + to_string(reader.get_id())
            + ", тел.: " + reader.get_phone() + ")");
    }
    int idx = select_from_list(lines, prompt);
    if (idx < 0) return nullptr;
    return &readers[static_cast<size_t>(idx)];
}

Book* select_any_book(Library& library, const string& prompt) {
    vector<Book*> all;
    for (auto& b : library.get_books_mutable()) {
        all.push_back(&b);
    }
    return select_book(all, prompt);
}