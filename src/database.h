#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

class database {
public:
    database();
    ~database();

    bool init();
    bool writeUserPreferences(int userId, float speed, const std::vector<float>& color);
    bool readUserPreferences(int userId, float& speed, std::vector<float>& color);

private:
    std::string dbPath;
    sqlite3* db;

    bool executeSQL(const std::string& sql);
    std::string colorToString(const std::vector<float>& color);
    std::vector<float> stringToColor(const std::string& colorStr);
};

#endif // DATABASE_H
