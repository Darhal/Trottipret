#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

/*
* Une classe de gestionnaire de base de données (Design Pattern: Singelton) qui gérera les schémas
* de base de données et ses connexions facilitera également
* l'insertion de la mise à jour et la sélection dans la base de données.
*/

class DatabaseManager
{
public:
    // Fonction statique qui va retourner l'instance de notre singelton
    static DatabaseManager& GetInstance();

    // Fonction qui intiliaze notre base de donnees
    void InitilizeDatabase();

    // Fonction facilitant l'exécution de requêtes sqlite
    QSqlQuery Exec(const char* statment);

    // Fonction facilitant l'exécution de requêtes sqlite avec des arguments variables de type different
    // Ca sera utile pour les selects et les inserts
    template<typename... Args>
    QSqlQuery Exec(const char* statment, Args&&... args);

    void Save();
private:
    constexpr static const char* DB_PATH = "trottipret.sqlite"; // Nom de notre db
    static DatabaseManager* s_Instance; // Instance de notre DatabaseManager

    QSqlDatabase db; // Database
    QSqlQuery query; // Les querry on utilise le meme objet et on utilise clear
                     // chaque fois pour optimiser la performance
    DatabaseManager(); // constructeur privée parceque c'est une classe singelton
};

template<typename... Args>
QSqlQuery DatabaseManager::Exec(const char* statment, Args&&... args)
{
    char statment_buffer[2048]; // Un buffer de 2048 pour eviter l'allocation dynamique!
    sprintf(statment_buffer, statment, std::forward<Args>(args)...); // formatter notre requets
    query.clear(); // neotyer le query
    query.exec(statment_buffer); // executer la commande
    return query; // retourner le querry qui contient les resultats
}

#endif // DATABASEMANAGER_H
