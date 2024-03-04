
#include "rooms.hpp"

/* El mapa realmente no necesita inicialización, ya que la única memoria que
 * hay que reservar es la del array de habitaciones y eso es trabajo del loader,
 * ya que es el que sabe cuántas habitaciones va a haber en el mapa.
 */

void Map::loadMap(MapLoader* loader) {
    // Realmente la complicación está en el loader.
    this->rooms = loader->getRooms();
    this->connections = loader->getConnections();
    this->start = loader->getStart();
}

bool Map::checkMapIntegrity() {
    // TODO: Implementar.
}

// Dos getters bastante simplones.
Room* Map::getRoomById(uint id) {
    for(Room* r : this->rooms) {
        if(r->id == id) {
            return r;
        }
    }
}

Connection* Map::getConnectionById(uint id) {
    for(Connection* c : this->connections) {
        if(c->id == id) {
            return c;
        }
    }
}
