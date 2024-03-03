/**
 * Cargadores de recursos. Dado un recurso en un formato dado (en este caso YAML),
 * estos cargadores crean un formato unificado.
 * 
 * La lógica es que puedan cargar recursos de otras fuentes sin necesidad de modificar
 * el código del objeto que representa el recurso en sí. Además de eliminar dependencias,
 * en este caso contra la librería YAML, de las cabeceras de los recursos permitiendo
 * aún así una carga modular sin que cada clase de recurso tenga que abrir un fichero completo.
 * 
 * @author Javier Paz Sedano
 */

#ifndef ADVENTURE_LOADERS
#define ADVENTURE_LOADERS

// Los includes siempre dentro del condicional, que está ahí precisamente para que esto no pete
// si metemos una referencia cruzada entre dos ficheros.
#include "rooms.hpp"

/**
 * Esta clase representa un cargador de mapa que a partir de un fichero YAML
 * devulve las habitaciones y el inicio del mapa.
 */
class MapLoader {
    public:
        MapLoader();

        void loadMap();

        Room* getRooms();
        Room* getStart();
};

// OJO: Esta estructura implica que la carga tiene que ser por fases. Primero las
// habitaciones y después las conexiones, para poder rellenar todas las referencias
// de forma lógica y ordenada.

/**
 * Cargador de habitaciones que se encarga de recoger sus datos del fichero YAML.
 */
class RoomLoader {
    public:
        RoomLoader();

        int getId();
        string getName();
        string getDescription();

        Connection* getConnections();
};

/**
 * Cargador de conexiones entre habitaciones.
 */
class ConnectionLoader {
    public:
        ConnectionLoader();

        /* Devuelve el ID en lugar de la habitación porque en teoría la habitación
           tiene que estar ya cargada. */
        int getOriginId();
        int getDestinationId();

        Direction getDirection();
        bool getOpen();
        string getClosedText();
};

class ObjectLoader {
    
};

class PuzzleLoader {
    
};

#endif // ADVENTURE_LOADERS
