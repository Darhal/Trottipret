#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DatabaseManager
{
public:
    static DatabaseManager& GetInstance();

    QSqlQuery Exec(const char* statment);

    template<typename... Args>
    QSqlQuery Exec(const char* statment, Args&&... args);

    void Save();
private:
    constexpr static const char* DB_PATH = "trottipret.sqlite";
    static DatabaseManager* s_Instance;

    QSqlDatabase db;
    QSqlQuery query;
    DatabaseManager();
};

template<typename... Args>
QSqlQuery DatabaseManager::Exec(const char* statment, Args&&... args)
{
    char statment_buffer[2048];
    sprintf(statment_buffer, statment, std::forward<Args>(args)...);
    query.clear();
    query.exec(statment_buffer);
    return query;
}

#endif // DATABASEMANAGER_H
