#include "viewoffrelocation.h"
#include "Core/locationmanager.h"

ViewOffreLocation::ViewOffreLocation(QWidget* parent) :
    QDialog(parent)
{
    this->setBaseSize(256, 256);
}

void ViewOffreLocation::OnAjouterOffre()
{
    // TODO: Get fields from text fields

    // Get the singelton and create the offer.
    LocationManager& loc_manager = LocationManager::GetInstance();
    // loc_manager.AjouterOffreLocation(Utilisateur(), OffreLocation());
}
