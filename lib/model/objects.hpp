/**
 * Este módulo contiene el código para 
 * 
 * @author Javier Paz Sedano
 */

#include <string>

#ifndef ADVENTURE_OBJECTS_H
#define ADVENTURE_OBJECTS_H

using namespace std;

// Definición temprana de tipos.
typedef Object;
typedef ObjectManager;

class ObjectManager {
    public:
      Object* inventory;
      Object* gameObjects;
};

/**
 * 
 */
class Object {
    public:
      unsigned int id;
      string name;
      string description;

      bool canTake;
      string takeText;
};

#endif // ADVENTURE_OBJECTS_H
