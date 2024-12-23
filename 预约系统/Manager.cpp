#include "Manager.h"

void Manager::operMenu()
{
}

void Manager::reSetName(const std::string& name) {
    dao->reSetName(id, name);
}

void Manager::reSetPassward(const std::string& oldpassward, const std::string& newpassward) {
    dao->reSetPassward(id, oldpassward, newpassward);
}

void Manager::addManager(const ManagerDTO& managerDTO) {
    dao->addManager(managerDTO);
}

void Manager::removeManager(int id) {
    dao->removeManager(id);
}

ManagerDTO Manager::findManager(int id) {
    return dao->findManager(id);
}