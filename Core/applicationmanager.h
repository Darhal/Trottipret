#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H
#include <mainwindow.h>
#include <Core/utilisateur.h>

/**
 * @brief The ApplicationManager class
 * DP: Singelton
*/
class ApplicationManager
{
public:
    /**
     * @brief Function to get the instance of the app manager
     * @return ApplicationManager&
    */
    static ApplicationManager& GetInstance();

    /**
     * @brief Function to free the data used by the application manager
    */
    static void Free();

    /**
     * @brief Function boot up the application
    */
    void StartApplication();

    /**
     * @brief Used to set the current connected user
     * @arg Utilisateur*
    */
    void SetCurrentUser(Utilisateur* user);

    Utilisateur* GetCurrentUser() { return m_CurrentUser; }
private:
    ApplicationManager();

    static ApplicationManager* s_Instance;

private:
    // MainWindow m_MainWindow; // Constructeur par défaut et alloue statiquement notre MainWindow
    Utilisateur* m_CurrentUser; // Utilisateur courrant
};

#endif // APPLICATIONMANAGER_H
