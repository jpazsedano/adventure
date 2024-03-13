/**
 * Este fichero contiene la lógica de resolución de los puzzles, que por
 * consiguiente también tiene la lógica de reslución del mapa.
 * 
 * @author Javier Paz Sedano
 */

#ifndef ADVENTURE_PUZZLES_H
#define ADVENTURE_PUZZLES_H

#include <string>
#include <map>
#include <list>
#include "objects.hpp"
#include "rooms.hpp"
#include "loaders.hpp"

using namespace std;

// Este enum en relidad representa todos los tipos de acciones realiables en todo momento.
enum ActionType { PICK_UP, MOVE, OPEN, CLOSE, USE, EXAMINE, COMBINE, TALK};

// Esto son básicamente todos los cambios en el juego que una acción puede desencadenar.
enum ReactionType {
    SWITCH_OPEN, SPAWN, DESTROY, UPDATE_DESCRIPTION, UPDATE_TAKETEXT, FINISH_MAP
};

// Definición temprana de tipos.
typedef Action;
typedef Trigger;
typedef OpenCloseTrigger;
typedef SwitchStateFlagTrigger;
typedef SpawnTrigger;
typedef DestroyTrigger;
typedef UpdateTrigger;
typedef FinishTrigger;

typedef LevelManager;
typedef LevelState;


/// @brief Esta clase se encarga de comprobar las acciones que se realizan en el juego para,
/// cuando sea necesario, realizar acciones sobre el mapa o los objetos.
class LevelManager {
    public:
        Map* map;
        ObjectManager* objManager;

        // Variables de estado del nivel.
        std::map <string, bool> levelState;

        // Esto representa el conjunto de acciones que tienen algún efecto sobre
        // el juego.
        list <Action*> puzzleActions;

        string levelName;
        string nextLevel;

        /// @brief Realiza una acción sobre el mapa y los objetos.
        /// @param type El tipo de acción a realizar
        /// @param objectId El ID del objeto sobre el que realizarla.
        /// @return El mensaje de la acción.
        string doAction(ActionType type, uint objectId);
        
        /// @brief Carga un nivel desde la fuente indicada.
        /// @param loader El cargador que va a obtener los datos.
        void loadLevel(LevelLoader* loader);

        /// @brief Finaliza el nivel e inicia la secuencia de paso al siguiente.
        void endLevel();
};

/// @brief Representa el estado del nivel
class LevelState {
    LevelManager* levelManager;
    map <string, bool> state;

    // Triggers que se disparan con cambios en el state.
    map <string, list <Trigger>> onceTriggers;
    map <string, list <Trigger>> repeatTriggers;

    /// @brief Aplica los triggers para una clave específica (si los hay)
    /// @param key La clave para la que ejecutar los triggers.
    void applyTriggersFor(string key);

    public:
        LevelState(LevelManager* manager);
        /// @brief Obtiene el valor de un flag.
        /// @param flag El flag del que se quiere conocer el valor.
        /// @return El valor del flag.
        bool getValue(string flag);
        /// @brief Cambia el valor de un flag.
        /// @param flag El flag del que se quiere modificar el valor
        /// @param newValue El nuevo valor
        /// @return Si el nuevo valor cambia el viejo.
        bool setValue(string flag, bool newValue);
        /// @brief Cambia el valor de un flag, independientemente del que tuviera
        /// previamente.
        /// @param flag El flag del que se quiere cambiar el valor.
        void switchValue(string flag);
        /// @brief Registra un trigger para ser lanzado cuando el estado cambie.
        /// @param flag El flag a monitorear.
        /// @param trigger El trigger a lanzar.
        /// @param repeat Si quieres que se ejecute una única vez o repetidamente con cada cambio.
        void registerStateTrigger(string flag, Trigger trigger, bool repeat);
        /// @brief Elimina un trigger del registro.
        /// @param triggerId El ID del trigger a eliminar.
        /// @return bool indicando si ha podido ser eliminado o no.
        bool unregisterOnceStateTrigger(uint triggerId);
};

/// @brief La clase Action se encarga de guardar una acción que desencadena una
/// reacción determinada. 'object2' está sólo para la acción 'COMBINE',
/// el resto de acciones se hacen con un sólo elemento.
/// Usar con y dar algo en realidad es una forma de COMBINE.
class Action {
    public:
        // TODO: Quizás algunas de, o todos estos atributos deban ser privados.
        LevelManager* manager;
        ActionType type;
        // El o los objetos involucrados en la acción.
        Object* object1;
        Object* object2;
        // Flags que deben ser true.
        list <string> conditions;
        // Textos a mostrar cuando la acción funciona y cuando no.
        string actionText;
        string failedText;
        // Puede haber múltiples reacciones.
        list <Trigger*> reactions;

        /// @brief Devuelve si una acción es un tipo de acción sobre un objeto concreto.
        /// @param type El tipo de acción.
        /// @param objectId El objeto sobre el que se realiza la acción.
        /// @return Si en efecto esta acción es esa o no.
        bool isAction(ActionType type, uint objectId);

        /// @brief Comprueba las condiciones para ver si la acción se puede ejecutar.
        /// @return Indica si se puede ejecutar.
        bool canExecute();

        /// @brief Ejecuta los triggers de la acción.
        void runTriggers();
};

/** TODO: A lo mejor esto se puede hacer de forma más limpia con herencia */
class Trigger {
    protected:
        LevelManager* levelManager;
    public:
        uint id;
        virtual bool applyTrigger();
};

/// @brief Función factory que construye reacciones
/// @param ReactionType El tipo de reacción a construir.
/// @param map Las propiedades para la construcción de la reacción
///
/// @return La reacción construida.
Trigger makeReaction(ReactionType, map<string, string>);

/// @brief Reacción de que un camino se abra o se cierre.
class OpenCloseTrigger: public Trigger {
    bool newValue;
    // Las conexiones deberían tener un puntero a la conexión reversa, si existe.
    uint conectionToOpen;
    bool reverseToo;

    public:
        bool applyTrigger();
};

/// @brief Cambia el valor de un flag de estado del nivel
class SwitchStateFlagTrigger: public Trigger {
    string flag;
    bool newValue;
    bool justSwitch;

    public:
        bool applyTrigger();
};

/// @brief Hace aparecer un objeto en el mapa.
class SpawnTrigger: public Trigger {
    uint objectId;
    uint position;

    public:
        bool applyTrigger();
};

/// @brief Destruye un objeto del mapa o el inventario.
class DestroyTrigger: public Trigger {
    uint objectId;
    
    public:
        bool applyTrigger();
};

/// @brief Esta reacción actualiza alguna de las propiedades de un objeto.
/// @todo Hacer recopilación de todo lo que se debe poder actualizar para ver si esto está bien hecho.
class UpdateTrigger: public Trigger {
    uint objectId;

    bool updateDescription;
    string newDescription;
    bool updateTakeText;
    string newTakeText;

    public:
        bool applyTrigger();
};

/// @brief Esta reacción finaliza el mapa y pasamos al siguiente
class FinishTrigger: public Trigger {
    public:
        bool applyTrigger();
};

#endif // ADVENTURE_PUZZLES_H
