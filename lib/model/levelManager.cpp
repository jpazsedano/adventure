#include "levelManager.hpp"

string LevelManager::doAction(ActionType type, uint objectId) {
    // Comparamos la acción realizada con todas aquellas que tienen reacción.
    for(Action* a : this->puzzleActions) {
        if(a->isAction(type, objectId) && a->canExecute()) {
            // Caso 1: Es la acción que buscamos y se puede ejecutar.
            a->runTriggers();
            return a->actionText;
        } else if (a->isAction(type, objectId) && !a->canExecute() ){
            // Caso 2: Es la acción que buscamos pero NO se puede ejecutar.
            return a->failedText;
        }
    }
    // Caso 3: La acción solicitada no está en la lista de acciones de puzzle.
    // TODO: Usar la localización para los mensajes multilengua.
    return "Eso no se puede.";
}

void LevelManager::loadLevel(LevelLoader* loader) {
    this->map = loader->loadMap();
    this->objManager = loader->loadObjectManager();
    this->puzzleActions = loader->loadActions();
}

void LevelManager::endLevel() {
    // TODO: Implementar. Seguramente haga falta una llamada a alguna clase superior que cambie
    // el nivel por otro o termine la ejecución, pero aún no hay definición de eso.
    if(this->nextLevel == "END") {
        return;
    } else {
        return;
    }
}

LevelState::LevelState(LevelManager* manager) {
    this->levelManager = manager;
}

bool LevelState::getValue(string key) {
    auto i = this->state.find(key);
    if(i != this->state.end()) {
        return i->second;
    } else {
        // Si la clave no se encuentra, se devuelve false.
        return false;
    }
}

void LevelState::applyTriggersFor(string key) {
    auto tIterator = this->onceTriggers.find(key);
    if(tIterator != this->onceTriggers.end()) {
        // Ejecutamos los triggers asignados al key.
        for( Trigger t : tIterator->second ) {
            // Ejecutamos los triggers asociados al cambio del flag.
            t.applyTrigger();
        }
        // Y los eliminamos porque éstos sólo se ejecutaon una vez.
        this->onceTriggers.erase(tIterator);
    }
    tIterator = this->repeatTriggers.find(key);
    if(tIterator != this->repeatTriggers.end()) {
        // Igual que el de antes, pero sin eliminarlo.
        for( Trigger t : tIterator->second ) {
            t.applyTrigger();
        }
    }
}

bool LevelState::setValue(string key, bool value) {
    // TODO: Quizás debamos guardar una lista de triggers a ejecutar para no tener
    // un ciclo de update demasiado largo. Aunque en modo texto eso tampoco importa mucho.
    auto i = this->state.find(key);
    if(i != this->state.end()) {
        // Comprobamos si hay cambio y si lo hay lo hacemos y buscamos a ver si hay triggers.
        if(i->second != value) {
            this->state[i->first] = value;
            this->applyTriggersFor(i->first);
        }
    } else if( value != false ){
        // El valor por defecto es false, así que sólo se crea si el nuevo valor es true.
        this->state[key] = value;
        this->applyTriggersFor(key);
    }
}

void LevelState::switchValue(string key) {
    auto i = this->state.find(key);
    if(i != this->state.end()) {
        // Encontrada.
        this->state[key] = !this->state[key];
    } else {
        // No encontrada, establecemos a true.
        this->state[key] = true;
    }
    this->applyTriggersFor(key);
}

void LevelState::registerStateTrigger(string key, Trigger trigger, bool repeat) {
    if(repeat) {
        this->repeatTriggers[key].push_back(trigger);
    } else {
        this->onceTriggers[key].push_back(trigger);
    }
}

// TODO: Hay que buscar una forma de declara esto inline.
class TriggerComparator {
    public:
        uint id;
        bool operator() (Trigger t) { return t.id == this->id; }
};

bool LevelState::unregisterOnceStateTrigger(uint triggerId) {
    TriggerComparator triggerCompare = {triggerId};

    for(pair <string, list<Trigger>> p : this->repeatTriggers) {
        p.second.remove_if(triggerCompare);
    }
    // Repetimos para los triggers de una sola ejecución.
    for(pair <string, list<Trigger>> p : this->onceTriggers ) {
        p.second.remove_if(triggerCompare);
    }
}

bool Action::isAction(ActionType type, uint objectId) {

}

bool Action::canExecute() {

}

void Action::runTriggers() {

}

bool OpenCloseTrigger::applyTrigger() {
    Connection* c = this->levelManager->map->getConnectionById(this->conectionToOpen);
    // El valor de retorno depende de si ha habido cambio o no (hemos intentado abrir algo ya abierto)
    if(c->open != this->newValue){
        c->open = this->newValue;
        return true;
    } else {
        return false;
    }
}

// TODO: ¿Quizás esta lógica debería ir en la implementación de objeto u objectmanager?
bool SpawnTrigger::applyTrigger() {
    // Más simple imposible.
    Object* o = this->levelManager->objManager->getObjectById(this->objectId);
    if(o->placeId == PLACE_NOWHERE) {
        o->placeId = this->position;
        return true;
    } else {
        return false;
    }
}

bool DestroyTrigger::applyTrigger() {
    // De nuevo, más simple imposible.
    Object* o = this->levelManager->objManager->getObjectById(this->objectId);

    if(o->placeId != PLACE_NOWHERE) {
        o->placeId = PLACE_NOWHERE;
        return true;
    } else {
        return false;
    }
}

bool UpdateTrigger::applyTrigger() {
    Object* o = this->levelManager->objManager->getObjectById(this->objectId);

    if(this->updateDescription) {
        o->description = this->newDescription;
    }
    if(this->updateTakeText) {
        o->takeText = this->newTakeText;
    }

    // Devolvemos True si ha habido alguna actualización
    return this->updateDescription || this->updateTakeText;
}

bool FinishTrigger::applyTrigger() {
    this->levelManager->endLevel();
    return true;
}
