#include "databasemanager.h"
#include <qdir.h>
#include <QDebug>

DatabaseManager* DatabaseManager::s_Instance = nullptr;

DatabaseManager& DatabaseManager::GetInstance()
{
    if (!s_Instance)
        s_Instance = new DatabaseManager();

    return *s_Instance;
}

void DatabaseManager::InitilizeDatabase()
{
    this->Exec(
        "CREATE TABLE IF NOT EXISTS utilisateurs"
        "(identifiant TEXT PRIMARY KEY, "
        "nom varchar(20), "
        "prenom varchar(20), "
        "email varchar(64),"
        "motdepass varchar(64)"
        ");"
    );
}

DatabaseManager::DatabaseManager() : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    db.setHostName("localhost");
    QFile file(DB_PATH);
    file.open(QIODevice::ReadWrite);
    file.close();

    db.setDatabaseName(DB_PATH);
    db.open();
    query = QSqlQuery(db);
    this->InitilizeDatabase();
}

QSqlQuery DatabaseManager::Exec(const char* statment)
{
    query.clear();
    query.exec(statment);
    return query;
}

void DatabaseManager::Save()
{
    db.commit();
}
