#include "databasemanager.h"

DatabaseManager* DatabaseManager::s_Instance = nullptr;

DatabaseManager::DatabaseManager() : db(QSqlDatabase::addDatabase(DB_NAME))
{
    db.open();
}

template<typename... Args>
void DatabaseManager::Exec(const char* statment, Args&&... args)
{
    char statment_buffer[2048];
    sprintf(statment_buffer, statment, std::forward<Args>(args)...);
    QSqlQuery query;
    query.exec(statment_buffer);
}
