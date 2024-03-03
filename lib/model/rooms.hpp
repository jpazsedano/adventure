/**
 * Este módulo incluye el código para la gestión de habitaciones de la aventura,
 * incluyendo definiciones para cada una, 
 * 
 * @author Javier Paz Sedano
 */

#ifndef ADVENTURE_ROOMS_H
#define ADVENTURE_ROOMS_H

#include <string>
#include "loaders.hpp"

using namespace std;

enum Direction { north, south, east, west, up, down };

// Definiciones tempranas de los tipos.
typedef Map;
typedef Room;
typedef Connection;

/**
 * Esta clase representa el mapa y contiene las habitaciones y sus conexiones,
 * así como la habitación inicial y código para cargarlo desde datos YAML.
 */
class Map {
    public:
      Room* start;
      Room* rooms;
    
      void loadMap(MapLoader);

      /**
       * Función que comprueba básicamente si todas las habitaciones tienen conexión
       * y que no haya dead-ends (habitaciones de las que no se puede salir).
       */
      bool checkMapIntegrity();
};

/** Esta estructura representa una habitación de la aventura. */
struct Room {
  int id;
  string name;
  string description;
  Connection* connections;
};

/**
 * Esta estructura representa una conexión entre habitaciones.
 * Debe crearse una por cada habitación (es decir una para el origen y otra
 * para el destino) para poder soportar conexiones unidireccionales y
 * conexiones en las que el acceso esté bloqueado en una dirección.
 */
struct Conection {
  int id;

  Room* origin;
  Room* destination;
  Direction direction;
  bool open;
  // Este texto se muestra si se intenta pasar y está cerrado.
  string closedText;
};

#endif // ADVENTURE_ROOMS_H
