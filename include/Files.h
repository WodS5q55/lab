#ifndef FILES_H
#define FILES_H

#include "Library.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Files {
private:
    static constexpr const char* SEC_READERS = "[READERS]";
    static constexpr const char* SEC_PUBLICATIONS = "[PUBLICATIONS]";

    static constexpr const char* TYPE_BOOK = "Book";
    static constexpr const char* TYPE_MAGAZINE = "Magazine";
    static constexpr const char* TYPE_NEWSPAPER = "Newspaper";

    static string trim(const string& str);
    static vector<string> split(const string& str, char delimiter);

    static void saveReaders(ofstream& ofs, const Library& library);
    static void savePublications(ofstream& ofs, const Library& library);

    static void loadReaderLine(Library& library, const vector<string>& t);
    static void loadPublicationLine(Library& library, const vector<string>& t);

    static void reportPublications(ofstream& ofs, const Library& library);
    static void reportReaders(ofstream& ofs, const Library& library);

public:
    static void save(const string& filename, const Library& library);
    static void load(const string& filename, Library& library);
    static void logAction(const string& logFilename, const string& action);
    static void generateReport(const string& reportFilename, const Library& library);
};

#endif