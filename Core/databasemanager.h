#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

/**
* @class DatabaseManager
* @brief Une classe de gestionnaire de base de données (Design Pattern: Singleton) qui gérera les schémas
* de base de données et ses connexions facilitera également
* l'insertion de la mise à jour et la sélection dans la base de données.
*/
class DatabaseManager
{
public:
    /**
     * @fn GetInstance
     * @brief Fonction statique qui va retourner l'instance de notre singleton
     * @return DatabaseManager&
    */
    static DatabaseManager& GetInstance();

    /**
     * @fn InitilizeDatabase
     * @brief Fonction qui initialise notre base de donnees
    */
    void InitilizeDatabase();

    /**
     * @fn Exec
     * @brief Fonction facilitant l'exécution des requêtes sqlite
     * @param const char* statment
     * @return QSqlQuery
    */
    QSqlQuery& Exec(const char* statment);

    /**
     * @fn Exec
     * @brief Fonction facilitant l'exécution des requêtes sqlite avec des arguments variables de type different
     * Ca sera utile pour les selects et les inserts
     * @param const char* statment
     * @param template Args&&... args
     * @return QSqlQuery
    */
    template<typename... Args>
    QSqlQuery& Exec(const char* statment, Args&&... args);

    /**
     * @fn save
     * @return void
    */
    void Save();
private:
    constexpr static const char* DB_PATH = "trottipret.sqlite"; // Nom de notre db
    static DatabaseManager* s_Instance; // Instance de notre DatabaseManager

    QSqlDatabase db; // Database
    QSqlQuery query; // Les querry on utilise le meme objet et on utilise clear
                     // chaque fois pour optimiser la performance

    /**
     * @fn DatabaseManager
     * @brief constructeur privée car c'est une classe singleton
    */              
    DatabaseManager();
};

template<typename... Args>
QSqlQuery& DatabaseManager::Exec(const char* statment, Args&&... args)
{
    char statment_buffer[2048]; // Un buffer de 2048 pour eviter l'allocation dynamique!
    sprintf(statment_buffer, statment, std::forward<Args>(args)...); // formatter notre requete
    query.clear(); // netoyer le query
    query.exec(statment_buffer); // executer la commande
    return query; // retourner le querry qui contient les resultats
}

#endif // DATABASEMANAGER_H
