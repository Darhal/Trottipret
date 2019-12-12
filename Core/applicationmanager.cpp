#include "applicationmanager.h"
#include <QDebug>

ApplicationManager* ApplicationManager::s_Instance = NULL;

ApplicationManager::ApplicationManager() :
    m_CurrentUser(NULL)// m_MainWindow()
{
}

ApplicationManager& ApplicationManager::GetInstance()
{
    if (!s_Instance){
        s_Instance = new ApplicationManager();
    }

    return *s_Instance;
}

void ApplicationManager::Free()
{
    if (!s_Instance)
        return;

    delete s_Instance;
}

void ApplicationManager::StartApplication()
{
}

void ApplicationManager::SetCurrentUser(Utilisateur* user)
{
    m_CurrentUser = user;
}
