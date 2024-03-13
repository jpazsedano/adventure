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

        /// @brief Carga los objetos con un cargador de objetos
        /// @param loader El cargador de objetos.
        void loadObjects(ObjectLoader* loader);

        /// @brief Obtiene el ID de un objeto a partir de su nombre.
        /// @param name El nombre del objeto.
        /// @return El ID del objeto.
        uint getObjectByName(string name);

        /// @brief Pues eso, devuelve un objeto a partir de su ID
        /// @param id El ID del objeto que se quiere.
        /// @return Un puntero al objeto en cuestión.
        Object* getObjectById(uint id);

        /// @brief Añade un objeto del juego al inventario
        /// @param id El ID del objeto a añadir.
        /// @return Si se ha podido añadir o no.
        bool placeObjectOnInventory(uint id);

        /// @brief Verfica que el estado en el que están los objetos tiene sentido.
        void checkObjectsIntegrity();
};

/// @brief Esta estructura representa un objeto del juego con sus propiedades y su ubicación
struct Object {
    uint id;
    // Igual que en un espacio de coordenadas el objeto tiene X e Y, aquí tiene ID de posición.
    uint roomId;
    string objLocation;

    string name;
    string description;
};

#endif // ADVENTURE_OBJECTS_H
