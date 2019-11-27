#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DatabaseManager
{
public:
    static DatabaseManager& GetInstance();

    template<typename... Args>
    void Exec(const char* statment, Args&&... args);
private:
    constexpr static const char* DB_NAME = "trottipret";
    static DatabaseManager* s_Instance;

    QSqlDatabase db;

    DatabaseManager();
};

#endif // DATABASEMANAGER_H
