#include "database.h"

//constructor and destructor
database::database() {
    this->db = nullptr;
    this->dbPath = "bin/visualizer.db";
}
database::~database() {
    if (db) {
        sqlite3_close(db);
    }
}

//initializer
bool database::init() {
    //opens database and retrieves a pointer
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    //sql code to create a new table if it doesnt exist
    std::string sql = "CREATE TABLE IF NOT EXISTS UserPreferences ("
                      "UserId INTEGER PRIMARY KEY, "
                      "Speed FLOAT, "
                      "Color TEXT);";
    
    
    //executes the sql code to create the table
    if (!executeSQL(sql)) {
        std::cerr << "Failed to create table: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    
    sql = "SELECT COUNT(*) FROM UserPreferences;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        std::cerr << "Failed to count rows in UserPreferences: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    // If the table is empty, insert initial values
    if (count == 0) {
        sql = "INSERT INTO UserPreferences (UserId, Speed, Color) "
              "VALUES (1, 0.0, '1.0,1.0,1.0');";
        
        if (!executeSQL(sql)) {
            std::cerr << "Failed to insert initial values: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
    }

    return true;
}

//read and write
bool database::writeUserPreferences(int userId, float speed, const std::vector<float>& color) {
    std::stringstream sql;
    sql << "INSERT OR REPLACE INTO UserPreferences (UserId, Speed, Color) VALUES ("
        << userId << ", "
        << speed << ", '"
        << colorToString(color) << "');";
    return executeSQL(sql.str());
}

bool database::readUserPreferences(int userId, float& speed, std::vector<float>& color) {
    std::string sql = "SELECT Speed, Color FROM UserPreferences WHERE UserId = " + std::to_string(userId) + ";";
    sqlite3_stmt* stmt;
    
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Execute the query and check if results are available
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Extract and set the speed
        speed = static_cast<float>(sqlite3_column_double(stmt, 0));

        // Extract and set the color
        std::string colorStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        color = stringToColor(colorStr);

    } else {
        std::cerr << "No user preference found for user ID " << userId << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    return true;
}


bool database::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

std::string database::colorToString(const std::vector<float>& color) {
    std::stringstream ss;
    for (const auto& value : color) {
        if (&value != &color[0]) {
            ss << ",";
        }
        ss << value;
    }
    return ss.str();
}

std::vector<float> database::stringToColor(const std::string& colorStr) {
    std::vector<float> color;
    std::stringstream ss(colorStr);
    std::string value;
    while (std::getline(ss, value, ',')) {
        color.push_back(std::stof(value));
    }
    return color;
}
