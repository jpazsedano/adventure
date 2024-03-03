/**
 * Este módulo contiene el código para 
 * 
 * @author Javier Paz Sedano
 */

#ifndef ADVENTURE_OBJECTS_H
#define ADVENTURE_OBJECTS_H

#include <string>
#include "loaders.hpp"

using namespace std;

// Definición temprana de tipos.
typedef Object;
typedef ObjectManager;

class ObjectManager {
    public:
        // FIXME: Inventario va a tener longitud variable, investigar si ya hay una implementación.
        Object* inventory;
        Object* gameObjects;

        void loadObject(ObjectLoader);
};

/**
 * 
 */
struct Object {
    unsigned int id;
    string name;
    string description;

    bool canTake;
    string takeText;
};

#endif // ADVENTURE_OBJECTS_H
