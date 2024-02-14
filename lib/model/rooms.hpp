/**
 * Este módulo incluye el código para la gestión de habitaciones de la aventura,
 * incluyendo definiciones para cada una, 
 * 
 * @author Javier Paz Sedano
 */

#include <string>

#ifndef ADVENTURE_ROOMS_H
#define ADVENTURE_ROOMS_H

using namespace std;

enum Direction { nort, south, east, west, up, down };

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
    
      /** TODO: Buscar una librería de mapeo de YAML y que esto reciba un nodo. */
      void loadMap();
};

/** Esta estructura representa una habitación de la aventura. */
struct Room {
  int id;
  string name;
  string description;
  Connection* connections;
};

/** Esta estructura representa una conexión entre habitaciones. */
struct Conection {
  int id;

  Room* destination;
  Direction direction;
  bool open;
  // Este texto se muestra si se intenta pasar y está cerrado.
  string closedText;
};

#endif // ADVENTURE_ROOMS_H
