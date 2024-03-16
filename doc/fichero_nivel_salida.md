Fichero de salida de nivel
==========================

Aquí se describe el fichero de salida del script de conversión, que además luego será
el que el motor de juego deberá ingerir.

Primero decir que el formato del fichero para el motor puede ser `yaml` o `json`.
En general siempre será `yaml`, pero el script tiene la posiblidad de generar
también `json` porque consideramos que una posible versión web del juego se
beneficiará de este formato, y al tener una estructura semántica similar,
generar código en uno u otro es trivial.

La librería de carga C++ ocupa ella sola 3.6 MB. Si nos planteamos portear el
juego a sistemas con poca memoria (sistemas retro), se hará un pequeño programa
que convierta el fichero YAML en un binario que serialice las estructuras de
datos, y será este binario el que cargue el programa.

La estructura del fichero YAML sigue la de las clases C++ del motor. En la raíz
encontramos el elemento Nivel.

Las referencias se hacen por ID y ya en este fichero están incluidas, así que 
los IDs estarán definidos ya en el fichero, no se asignarán en tiempo de ejecución
porque en tiempo de ejecución en realidad no se creará ninguna entidad.

Nivel
-----

Este nodo se usará para rellenar la estructura `LevelManager` con un
nivel a gestionar. Incluirá.

- `levelName` <string>: El nombre del nivel.
- `nextLevel` <string>: El nombre del siguiente nivel. `END` si no hay siguiente nivel.
- `state` <LevelState>: El estado del nivel al inicio del mismo.
- `actions` <Action (lista)>: Lista de acciones que se pueden realizar en el nivel.
- `objects` <Object (lista)>: Lista de objetos del nivel.
- `map` <Map>: Representa el mapa del nivel.

LevelState
----------

Básicamente almacena el estado del nivel y los triggers de estado.

- `properties` <obj>: Guarda el estado inicial de las propiedades del estado. Básicamente
es un objeto que almacena una serie de booleans.
- `onceActions` <obj>: Guarda las acciones de estado. Es un objeto en las que las
propiedades son propiedades de estado y los valores son listas de tipo Action.
- `repeatActions` <obj>: Guarda las acciones que deben repetirse. Sigue el mismo
formato que `onceActions`.

Action
------

Representa una acción que se puede hacer sobre el juego y que tiene triggers.

- `actionId` <uint>: El ID de la acción.
- `actionType` <int>: Valor del enum que indica el tipo de acción.
- `actionText` <string>: El texto que se mostrará cuando la acción se lleve a cabo con éxito.
- `failedText` <string>: El texto que se mostrará cuando la acción fracase.
- `conditions` <string (lista)>: Condiciones que deben ser verdaderas para poder ejecutarse.
- `object1Id` <uint>: El ID del objeto sobre el que se realiza la acción.
- `object2Id` <uint>: El ID del segundo objeto sobre el que se realiza la acción. 0 si no hay
segundo objeto.
- `triggers` <Trigger (lista)>: Reacciones a hacer cuando la acción se ejecute.

Object
------

Un objeto del juego, esté en el inventario, en el escenario o en el limbo.

- `id` <uint>: ID de objeto.
- `roomId` <uint>: El ID de la habitación en la que se encuentra. Puede ser 0 para representar 
que el objeto no está en ninguna o -1 para indicar que está en el inventario.
- `objLocation` <string>: Descripción de la ubicación en la habitación del objeto.
- `name` <string>: El nombre del objeto.
- `description` <string>: La descripción del objeto cuando se examina de cerca.

Trigger
-------

El trigger puede ser de varios tipos. En la implementación básicamente vamos a poner
una propiedad `type`, y según el tipo el resto de propiedades variarán.

type: openclose

- `newValue` <bool>: El nuevo valor del flag isOpen.
- `connection` <uint>: La conexión sobre la que actuar.
- `reverseToo` <bool>: Si es true indica que se cambie también en sentido contrario.

type: switchstateflag

- `flag` <string>: El valor sobre el que actuar.
- `newValue` <bool>: El nuevo valor del flag.
- `justSwitch` <bool>: En lugar de `newValue` se puede usar este flag para indicar
que se invierta el valor actual.

type: spawn

- `objectId` <uint>: El ID del objeto.
- `roomId` <uint>: El ID de la habitación donde hacer spawn.
- `locationText` <string>: El texto que describe la posición en la habitación donde
está el objeto.

type: destroy

- `objectId` <uint>: El ID del objeto.

type: update

- `updateDescription` <bool>: Indica si hay que cambiar la descripción.
- `newDescription` <string>: La nueva descripción.
- `updateLocation` <bool>: Indica si hay que cambiar el string de ubicación.
- `newLocation` <string>: La nueva ubicación.
- `updatePosition` <bool>: Indica si hay que cambiar la habitación.
- `newPosition` <uint>: El ID de la nueva habitación

type: finish

Esta no tiene ninguna propiedad especial.

Map
---

Representa el mapa por el que el jugador se puede mover.

- `start` <uint>: ID de la habitación en la que empieza el juego.
- `rooms` <Room (lista)>: Lista de habitaciones del mapa.
- `connections` <Connection (lista)>: Lista de conexiones del mapa.

Room
----

Representa una habitación.

- `id` <uint>: El ID de la habitación.
- `name` <string>: El nombre de la habitación.
- `description` <string>: La descripción de la habitación.

Connection
----------

Conexión entre dos habitaciones.

- `id` <uint>: El ID de la conexión.
- `origin` <uint>: El ID de la habitación
- `destination` <uint>: El ID de la habitación 
- `direction` <uint>: Dirección de la conexión. Un enum que empieza en cero y puede
tener los valores north = 0, south = 1, east = 2, west = 3, up = 4 o down = 5.
- `isOpen` <bool>: Indica si la connexión está abierta.
- `closedText` <string>: Texto a mostrar si la conexión está cerrada.
