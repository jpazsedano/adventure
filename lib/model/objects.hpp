/**
 * Este módulo contiene el código para 
 * 
 * @author Javier Paz Sedano
 */

#ifndef ADVENTURE_OBJECTS_H
#define ADVENTURE_OBJECTS_H

#include <string>
#include <list>
#include "loaders.hpp"

#define PLACE_INVENTORY -1
#define PLACE_NOWHERE 0

using namespace std;

// Definición temprana de tipos.
typedef Object;
typedef ObjectManager;

class ObjectManager {
    public:
        // Siempre mejor trabajar con punteros para no meter cosas tochas a la pila de llamadas.
        list <Object*> inventory;
        list <Object*> gameObjects;

        /**
         * Carga los objetos con un cargador de objetos.
         */
        void loadObjects(ObjectLoader*);

        /**
         * Pues eso, devuelve un objeto a partir de su ID
        */
        Object* getObjectById(uint);

        /**
         * Añade un objeto del juego al inventario.
         */
        bool placeObjectOnInventory(uint);

        /**
         * Verifica que el estado en el que están los objetos tiene sentido.
         */
        void checkObjectsIntegrity();
};

/**
 * Esta estructura representa un objeto del juego con sus propiedades y su
 * ubicación.
 */
struct Object {
    uint id;
    // Igual que en un espacio de coordenadas el objeto tiene X e Y, aquí tiene ID de posición.
    uint placeId;

    string name;
    string description;

    bool canTake;
    string takeText;
};

#endif // ADVENTURE_OBJECTS_H
