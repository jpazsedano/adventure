
#include "rooms.hpp"

/* El mapa realmente no necesita inicialización, ya que la única memoria que
 * hay que reservar es la del array de habitaciones y eso es trabajo del loader,
 * ya que es el que sabe cuántas habitaciones va a haber en el mapa.
 */

void Map::loadMap(MapLoader loader) {
    // Realmente la complicación está en el loader.
    this->rooms = loader.getRooms();
    this->start = loader.getStart();
}

bool Map::checkMapIntegrity() {
    // TODO: Implementar.
}
