#include "puzzles.hpp"

void PuzzleManager::loadPuzzles(PuzzleLoader* loader) {
    this->map = loader->loadMap();
    this->objManager = loader->loadObjectManager();
    this->puzzleActions = loader->loadActions();
}

string PuzzleManager::doAction(Action* action) {
    // Comparamos la acción realizada con todas aquellas que tienen reacción.
    for(Action* a : this->puzzleActions) {
        if(a->compare(action)) {
            for(Reaction* r : a->reactions) {
                // TODO: ¿Qué hacemos con el retorno?
                if(r->applyAction()) {
                    // FIXME: ¡Localiza el texto!
                    return r->reactionDescription;
                } else {
                    // FIXME: ¡Localiza el texto!
                    return "Eso no se puede hacer";
                }
            }
        }
    }
    // FIXME: Algo nos falla con el feedback al jugador. ¿Cómo lo obtenemos? Debe valer
    // también para acciones sin reacción.
}

bool Action::compare(Action* other) {
    return this->object1->id == other->object1->id
        // TODO: Comprobar la precedencia de esto y que no vaya a petar si object2 es nulo.
        && (this->object2 == NULL && other->object2 == NULL) || (this->object2->id == other->object2->id)
        && this->type == other->type;
}

bool OpenCloseReaction::applyAction() {
    Connection* c = this->puzzles->map->getConnectionById(this->conectionToOpen);
    // El valor de retorno depende de si ha habido cambio o no (hemos intentado abrir algo ya abierto)
    if(c->open != this->newValue){
        c->open = this->newValue;
        return true;
    } else {
        return false;
    }
}

// TODO: ¿Quizás esta lógica debería ir en la implementación de objeto u objectmanager?
bool SpawnReaction::applyAction() {
    // Más simple imposible.
    Object* o = this->puzzles->objManager->getObjectById(this->objectId);
    if(o->placeId == PLACE_NOWHERE) {
        o->placeId = this->position;
        return true;
    } else {
        return false;
    }
}

bool DestroyReaction::applyAction() {
    // De nuevo, más simple imposible.
    Object* o = this->puzzles->objManager->getObjectById(this->objectId);

    if(o->placeId != PLACE_NOWHERE) {
        o->placeId = PLACE_NOWHERE;
        return true;
    } else {
        return false;
    }
}

bool UpdateReaction::applyAction() {
    Object* o = this->puzzles->objManager->getObjectById(this->objectId);

    if(this->updateDescription) {
        o->description = this->newDescription;
    }
    if(this->updateTakeText) {
        o->takeText = this->newTakeText;
    }

    // Devolvemos True si ha habido alguna actualización
    return this->updateDescription || this->updateTakeText;
}

bool FinishReaction::applyAction() {
    // TODO: A implementar cuando tenga un dummy de juego.
}
