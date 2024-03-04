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
#include "objects.hpp"
#include "puzzles.hpp"
#include <list>

/**
 * Esta clase representa un cargador genérico de mapa que a partir de una fuente
 * devulve las habitaciones y el inicio del mapa (normalmente un fichero).
 */
class MapLoader {
    public:
        MapLoader();

        void loadMap();

        list <Room*> getRooms();
        list <Connection*> getConnections();
        Room* getStart();
};

// OJO: Esta estructura implica que la carga tiene que ser por fases. Primero las
// habitaciones y después las conexiones, para poder rellenar todas las referencias
// de forma lógica y ordenada.

/**
 * Cargador genérico de habitaciones que se encarga de recoger los datos para una
 * habitación de una fuente (normalmente un fichero).
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
 * Cargador genérico de conexiones entre habitaciones.
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

/**
 * Esta clase representa un cargador genérico
 */
class ObjectLoader {
    public:
        list <Object*> loadObjects();
        list <Object*> loadInventory();
};

/**
 * Cargador genérico para la lógica de puzzles desde una fuente (generalmente un fichero).
 */
class PuzzleLoader {
    ObjectLoader *objLoader;
    RoomLoader *rLoader;

    public:
        list <Action*> loadActions();

        Map* loadMap();
        ObjectManager* loadObjectManager();
};

#endif // ADVENTURE_LOADERS
