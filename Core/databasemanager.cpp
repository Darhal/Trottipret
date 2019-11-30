#include "databasemanager.h"
#include <qdir.h>
#include <QDebug>

// Intilization de notre variable statique, il faut que ce soit obligatoirement dans le .cpp
// D'apres touts les standards C++!
DatabaseManager* DatabaseManager::s_Instance = nullptr;

// Fonction statique qui va retourner l'instance de notre singelton
DatabaseManager& DatabaseManager::GetInstance()
{
    if (!s_Instance) //  si c'est null
        s_Instance = new DatabaseManager(); // cree une instance

    return *s_Instance; // retourne une reference, et pas un pointeur
}

void DatabaseManager::InitilizeDatabase()
{
    // pour le moment on va cree un table d'utilisateur si ca n'existe pas!
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
    // Une databse local
    db.setHostName("localhost");
    QFile file(DB_PATH);
    file.open(QIODevice::ReadWrite); // creation du fichier sqlite si ca n'existe pas!
    file.close();

    db.setDatabaseName(DB_PATH);
    db.open(); // ouverture de db
    query = QSqlQuery(db); //  intilization du query une foix pour toute
    this->InitilizeDatabase(); // intilization de notre db
}

// FOnction qui execute une requetes sans arguments
QSqlQuery DatabaseManager::Exec(const char* statment)
{
    query.clear();
    query.exec(statment);
    return query;
}

// fonction qui commit la db
void DatabaseManager::Save()
{
    db.commit();
}
