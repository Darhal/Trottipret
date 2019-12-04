#include "databasemanager.h"
#include <qdir.h>
#include <QDebug>

// Initialisation de notre variable statique, il faut que ce soit obligatoirement dans le .cpp
// D'apres tous les standards C++
DatabaseManager* DatabaseManager::s_Instance = nullptr;

// Fonction statique qui va retourner l'instance de notre singleton
DatabaseManager& DatabaseManager::GetInstance()
{
    if (!s_Instance) //  si c'est null
        s_Instance = new DatabaseManager(); // cree une instance

    return *s_Instance; // retourne une reference, et pas un pointeur
}

void DatabaseManager::InitilizeDatabase()
{
    // pour le moment on va creer une table d'utilisateur si elle n'existe pas
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
    // Une database locale
    db.setHostName("localhost");
    QFile file(DB_PATH);
    file.open(QIODevice::ReadWrite); // creation du fichier sqlite s'il n'existe pas
    file.close();

    db.setDatabaseName(DB_PATH);
    db.open(); // ouverture de db
    query = QSqlQuery(db); //  intilialisation du query
    this->InitilizeDatabase(); // intitialisation de notre db
}

// Fonction qui execute une requete sans arguments
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
