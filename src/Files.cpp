#include "Files.h"
#include "Book.h"
#include "Magazine.h"
#include "Newspaper.h"
#include "../Exceptions/AllExceptions.h"
#include <sstream>
#include <iostream>
#include <ctime>


string Files::trim(const string& str) {
    const size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) return "";
    const size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

vector<string> Files::split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}



void Files::save(const string& filename, const Library& library) {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw InvalidInputException("не удалось открыть файл для записи: " + filename);
    }

    saveReaders(ofs, library);
    savePublications(ofs, library);

    if (!ofs.good()) {
        throw InvalidInputException("ошибка записи в файл: " + filename);
    }

    ofs.close();
    cout << "[OK] Данные сохранены в " << filename << endl;
}

void Files::saveReaders(ofstream& ofs, const Library& library) {
    ofs << SEC_READERS << "\n";
    for (const Reader* r : library.get_readers()) {
        ofs << r->get_id() << "|" << r->get_name() << "|" << r->get_phone() << "\n";
    }
}

void Files::savePublications(ofstream& ofs, const Library& library) {
    ofs << SEC_PUBLICATIONS << "\n";
    const auto& pubs = library.get_publications();
    const auto& dates = library.get_borrow_dates();

    for (size_t i = 0; i < pubs.size(); ++i) {
        Publication* p = pubs[i];
        string type, field;

        if (auto* b = dynamic_cast<Book*>(p)) {
            type = TYPE_BOOK; field = b->get_field();
        }
        else if (auto* m = dynamic_cast<Magazine*>(p)) {
            type = TYPE_MAGAZINE; field = m->get_field();
        }
        else if (auto* n = dynamic_cast<Newspaper*>(p)) {
            type = TYPE_NEWSPAPER; field = n->get_field();
        }
        else {
            throw InvalidInputException("неизвестный тип издания при сохранении");
        }

        int borrower_id = p->get_borrowed_by() ? p->get_borrowed_by()->get_id() : -1;
        time_t bdate = (i < dates.size()) ? dates[i] : 0;

        ofs << type << "|" << p->get_id() << "|" << p->get_title() << "|"
            << p->get_author() << "|" << p->get_year() << "|" << p->get_pages() << "|"
            << field << "|" << borrower_id << "|" << static_cast<long long>(bdate) << "\n";
    }
}



void Files::load(const string& filename, Library& library) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw InvalidInputException("не удалось открыть файл для чтения: " + filename);
    }


    library.clear_all();

    string line, currentSection;
    while (getline(ifs, line)) {
        line = trim(line);
        if (line.empty()) continue;
        if (line[0] == '[') { currentSection = line; continue; }

        const auto tokens = split(line, '|');

        try {
            if (currentSection == SEC_READERS) loadReaderLine(library, tokens);
            else if (currentSection == SEC_PUBLICATIONS) loadPublicationLine(library, tokens);
        }
        catch (const exception& e) {
            cerr << "Ошибка при загрузке строки: " << line
                << "\nПричина: " << e.what() << endl;
            throw;
        }
    }

    cout << "[OK] Состояние загружено из " << filename << endl;
}

void Files::loadReaderLine(Library& library, const vector<string>& t) {
    if (t.size() != 3) throw InvalidInputException("неверное число полей у читателя");
    int id = stoi(t[0]);
    Reader* r = new Reader(t[1], t[2]);
    library.restore_reader_with_id(r, id);
}


void Files::loadPublicationLine(Library& library, const vector<string>& t) {
    if (t.size() != 9) throw InvalidInputException("неверное число полей у издания");

    string type = t[0];
    int id = stoi(t[1]);
    string title = t[2];
    string author = t[3];
    int year = stoi(t[4]);
    int pages = stoi(t[5]);
    string field = t[6];
    int borrower_id = stoi(t[7]);
    time_t bdate = static_cast<time_t>(stoll(t[8]));

    Publication* p = nullptr;
    if (type == TYPE_BOOK) {
        p = new Book(id, title, author, year, pages, field);
    }
    else if (type == TYPE_MAGAZINE) {
        p = new Magazine(id, title, author, year, pages, stoi(field));
    }
    else if (type == TYPE_NEWSPAPER) {
        p = new Newspaper(id, title, author, pages, field);
    }
    else {
        throw InvalidInputException("неизвестный тип издания: " + type);
    }

    if (borrower_id != -1) {
        Reader* r = library.find_reader_by_id(borrower_id);
        if (!r) {
            delete p;
            throw InvalidInputException("читатель с ID=" + to_string(borrower_id) + " не найден");
        }
        p->borrow_book(r);
    }

    library.restore_publication(p, bdate);
}



void Files::logAction(const string& logFilename, const string& action) {
    ofstream ofs(logFilename, ios::app);
    if (!ofs.is_open()) {
        cerr << "[ВНИМАНИЕ] не удалось открыть журнал: " << logFilename << endl;
        return;
    }

    time_t now = time(nullptr);
    tm timeInfo;
#ifdef _WIN32
    localtime_s(&timeInfo, &now);
#else
    localtime_r(&now, &timeInfo);
#endif
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeInfo);

    ofs << "[" << buf << "] " << action << "\n";
}



void Files::generateReport(const string& reportFilename, const Library& library) {
    ofstream ofs(reportFilename);
    if (!ofs.is_open()) {
        throw InvalidInputException("не удалось создать файл отчёта: " + reportFilename);
    }

    ofs << "=== ОТЧЁТ О СОСТОЯНИИ БИБЛИОТЕКИ ===\n\n";
    reportPublications(ofs, library);
    reportReaders(ofs, library);

    if (!ofs.good()) throw InvalidInputException("ошибка записи отчёта: " + reportFilename);
    ofs.close();
    cout << "[OK] Отчёт сохранён в " << reportFilename << endl;
}

void Files::reportPublications(ofstream& ofs, const Library& library) {
    ofs << "--- ИЗДАНИЯ ---\n";
    for (const Publication* p : library.get_publications()) {
        ofs << "Тип: " << p->get_type() << "\n";
        ofs << "  ID: " << p->get_id() << "\n";
        ofs << "  Название: " << p->get_title() << "\n";
        ofs << "  Автор: " << p->get_author() << "\n";
        ofs << "  Год: " << p->get_year() << "\n";
        ofs << "  Страниц: " << p->get_pages() << "\n";
        ofs << "  " << p->get_field_name() << ": " << p->get_field() << "\n";
        ofs << "  Стоимость: " << p->calculate_price() << " руб.\n";

        if (p->is_borrowed()) {
            ofs << "  Выдано: " << p->get_borrowed_by()->get_name() << "\n";
            int days = library.get_days_left(p);
            if (days < 0) ofs << "  ПРОСРОЧЕНО на " << -days << " дн.\n";
            else ofs << "  Осталось дней: " << days << "\n";
        }
        else {
            ofs << "  Статус: Доступно\n";
        }
        ofs << "\n";
    }
}

void Files::reportReaders(ofstream& ofs, const Library& library) {
    ofs << "--- ЧИТАТЕЛИ ---\n";
    for (const Reader* r : library.get_readers()) {
        ofs << "ID: " << r->get_id() << "\n";
        ofs << "  ФИО: " << r->get_name() << "\n";
        ofs << "  Телефон: " << r->get_phone() << "\n";

        bool has_books = false;
        for (const Publication* p : library.get_publications()) {
            if (p->get_borrowed_by() == r) {
                if (!has_books) {
                    ofs << "  Выданные издания:\n";
                    has_books = true;
                }
                ofs << "    - " << p->get_title() << "\n";
            }
        }
        ofs << "\n";
    }
}