/**
 * Este módulo incluye el código para la gestión de habitaciones de la aventura,
 * incluyendo definiciones para cada una, 
 * 
 * @author Javier Paz Sedano
 */

#ifndef ADVENTURE_ROOMS_H
#define ADVENTURE_ROOMS_H

#include <string>
#include <list>
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
      list <Room*> rooms;
      // Referencia a las conexiones para búsqueda rápida.
      list <Connection*> connections;
    
      /// @brief Carga un mapa utilizando un loader.
      /// @param loader Carga el recurso de mapa y permite recuperar datos de él.
      void loadMap(MapLoader* loader);

      /// @brief Función que comprueba básicamente si todas las habitaciones tienen conexión
      /// y que no haya dead-ends (habitaciones de las que no se puede salir).
      /// @return Indica si el mapa tiene sentido.
      bool checkMapIntegrity();

      /// @brief Obtiene una habitación a partir de su ID
      /// @param id El ID de la habitación que se quiere obtener.
      /// @return La habitación. NULL si no existe
      Room* getRoomById(uint id);

      /// @brief Obtiene una conexión a partir de su ID.
      /// @param id El ID de la conexión a obtener.
      /// @return La conexión. NULL si no existe.
      Connection* getConnectionById(uint id);
};

/** 
 * Esta estructura representa una habitación de la aventura.
 */
struct Room {
  uint id;
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
  uint id;

  // Habitación de origen.
  Room* origin;
  // Habitación de destino
  Room* destination;
  // Dirección. ¿Esto va aquí?
  Direction direction;
  // La conexión en sentido contrario.
  Conection* opposite;

  bool open;
  // Este texto se muestra si se intenta pasar y está cerrado.
  string closedText;
};

#endif // ADVENTURE_ROOMS_H
