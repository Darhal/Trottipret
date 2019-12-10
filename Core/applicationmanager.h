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
    static ApplicationManager& GetInstance();

    static void Free();

    void StartApplication();

    void SetCurrentUser(Utilisateur* user);

    Utilisateur* GetCurrentUser() { return m_CurrentUser; };
private:
    ApplicationManager();

    static ApplicationManager* s_Instance;

private:
    // MainWindow m_MainWindow; // Constructeur par défaut et alloue statiquement notre MainWindow
    Utilisateur* m_CurrentUser; // Utilisateur courrant
};

#endif // APPLICATIONMANAGER_H
