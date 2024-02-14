/**
 * Este fichero contiene la lógica de resolución de los puzzles, que por
 * consiguiente también tiene la lógica de reslución del mapa.
 * 
 * @author Javier Paz Sedano
 */

#include <string>
#include <map>
#include "objects.hpp"
#include "rooms.hpp"

#ifndef ADVENTURE_PUZZLES_H
#define ADVENTURE_PUZZLES_H

using namespace std;

// Este enum en relidad representa todos los tipos de acciones realiables en todo momento.
enum ActionType { USE, PICK, COMBINE, EXAMINE, OPEN, CLOSE, PUSH, PULL, TALK };

// Esto son básicamente todos los cambios en el juego que una acción puede desencadenar.
enum ReactionType {
  OPEN, SWITCH_PICKABLE, SPAWN, DESTROY, UPDATE_DESCRIPTION, UPDATE_TAKETEXT, FINISH_MAP
};

// Definición temprana de tipos.
typedef Action;
typedef Reaction;
typedef OpenCloseReaction;
typedef PickableReaction;
typedef SpawnReaction;
typedef DestroyReaction;
typedef UpdateReaction;
typedef FinishReaction;
typedef PuzzleManager;

/**
 * Esta clase se encarga de comprobar las acciones que se realizan en el juego para,
 * cuando sea necesario, realizar acciones sobre el mapa o los objetos.
 */
class PuzzleManager {
  public:
    Map* map;
    ObjectManager* objManager;

    // Esto representa el conjunto de acciones que tienen algún efecto sobre
    // el juego.
    Action* puzzleActions;

    /**
     * Esta función realiza una acción sobre el mapa y los objetos al
     * realizar una acción determinada.
     */
    string doAction(Action*);

    void loadPuzzles(ifstream);
};

/**
 * La clase Action se encarga de guardar una acción que desencadena una
 * reacción determinada. 'object2' está sólo para la acción 'COMBINE',
 * el resto de acciones se hacen con un sólo elemento.
 * Usar con y dar algo en realidad es una forma de COMBINE.
 */
class Action {
  public:
    Object object1;
    Object object2;
    ActionType type;
    // Puede haber múltiples reacciones.
    Reaction* reactions;

    bool compare(Action*);
};

/** TODO: A lo mejor esto se puede hacer de forma más limpia con herencia */
class Reaction {
  PuzzleManager* puzzles;
  public:
    string reactionDescription;

    virtual void applyAction();
};

/**
 * Función factory que construye reacciones.
 * @param ReactionType El tipo de reacción a construir.
 * @param map Las propiedades para la construcción de la reacción.
 * 
 * @returns La reacción construida.
 */
Reaction makeReaction(ReactionType, map<string, string>);

/** Reacción de que un camino se abra o se cierre. */
class OpenCloseReaction: public Reaction {
  bool newValue;
  int conectionToOpen;

  public:
    void applyAction();
};

/** Reacción de que un objeto sea recogible (o deje de serlo) */
class PickableReaction: public Reaction {
  bool newValue;
  int objectToChange;

  public:
    void applyAction();
};

/** Reacción de hacer aparecer un objeto en el mapa.*/
class SpawnReaction {
  int object;
  int position;

  public:
    void applyAction();
};

/** Reacción de destruir un objeto del mapa. */
class DestroyReaction {
  int object;
  
  public:
    void applyAction();
};

/** Esta reacción actualiza alguna de las propiedades de un objeto. */
class UpdateReaction {
  bool updateDescription;
  string newDescription;
  bool updateText;
  string newTakeText;

  public:
    void applyAction();
};

/** Esta reacción finaliza el mapa y pasamos al siguiente */
class FinishReaction {
  public:
    void applyAction();
};

#endif // ADVENTURE_PUZZLES_H
