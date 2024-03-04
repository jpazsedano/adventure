#include "objects.hpp"

void ObjectManager::loadObjects(ObjectLoader* loader) {
    this->gameObjects = loader->loadObjects();
    this->inventory = loader->loadInventory();
}

Object* ObjectManager::getObjectById(uint id) {
    // No va a ser una lista muy larga, simplemente busca.
    for (Object* obj : this->gameObjects) {
        if(obj->id == id) {
            return obj;
        }
    }

    // Si no lo encuentra, devuelve NULL.
    return NULL;
}

bool ObjectManager::placeObjectOnInventory(uint id) {
    // Primero comprobamos si no está ya en el inventario.
    for(Object *obj : this->inventory) {
        if(obj->id == id && obj->placeId == PLACE_INVENTORY) {
            // Devolvemos false porque ya está en el inventario.
            return false;
        }
    }

    for(Object *obj : this->gameObjects) {
        if(obj->id == id && obj->canTake) {
            this->inventory.push_back(obj);
            obj->placeId = PLACE_INVENTORY;
            return true;
        }
    }
    // Objeto no encontrado.
    return false;
}

void ObjectManager::checkObjectsIntegrity() {
    // TODO: Implmentar
}
