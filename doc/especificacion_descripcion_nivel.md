Fichero de descripción de nivel
===============================

Un fichero de descripción de nivel es un fichero en formato YAML que contiene la descripción del
mapa de un capítulo, sus objetos y los triggers de los puzzles.

Este fichero YAML podrá ser preprocesado por un script hacia un formato más amigable con la implementación
del juego. Por ejemplo, quizás queramos un formato JSON para una versión de navegador o binaria para
plataformas retro de pocos recursos.

Nivel
-----

Elemento base de la descripción y contenedor del resto de elementos.

- `map` <Mapa>: El layout del nivel.
- `inventory` <Inventario>: El inventario inicial.
- `levelName` <string>: Nombre del nivel.
- `nextLevel` <string>: Nombre del siguiente nivel. Se puede usar la palabra clave `ENDGAME`
para indicar que no hay y que éste es el último nivel.
- `state` <map string-bool>: Estado del juego, básicamente es una serie de flags que se
pueden utilizar para condicionar acciones.
- `stateTriggers` <StateTrigger (lista)>: Se verifican cada vez que hay una actualización
en el estado del nivel, puede comprobar el mismo y si cumple las condiciones, desencadenar
un trigger.

Mapa
----

Contiene el layout del nivel y los objetos almacenados en él.

- `rooms` <Habitacion (lista)>: Lista de habitaciones.
- `start` <string>: Nombre de la habitación

Habitacion
----------

Descripción de una habitación con sus objetos y conexiones.

- `name` <string>: Nombre de la habitación. Debe ser único del nivel.
- `description` <string>: Descripción larga de la habitación.
- `objects` <Objecto (lista)>: Lista de objetos con los que se puede interactuar.
- `connections` <ListaConexiones>: Objeto con las diferentes conexiones a otras habitaciones.

Objeto
------

Representa un objeto con el que se puede interactuar. Tiene flags para todas las acciones posibles sobre
el objeto. Open y Activate indican la acción en ambos sentidos.

- `name` <string>: Nombre único del objeto.
- `description` <string>: Descripción del objeto cuando es examinado.
- `location` <string>: Texto descriptivo que se utilizará para la descripción de objetos en la sala.
- `actions` <Action (lista)>: Acciones que se pueden realizar sobre el objeto. La omisión de una
acción implica que no se puede hacer y mostrará un mensaje genérico para ella.
- `hidden` <bool>: Por defecto es `false`, pero si se especifica `true`, el objeto se almacenará
en la lista de objetos no spawneados. Básicamente es un shortcut para poner en un mismo sitio los
objetos que están en la sala y los que van a aparecer o hacerse visibles en la sala en algún momento.

> La omisión de cualquiera de una acción en la lista de acciones implica que no se puede
hacer y se mostrará un texto de negación genérico si se intenta. Única excepción, la acción de
tipo Examinar, que simplemente mosrará la descripción del objeto.

Action
------

Representa una acción que se puede realizar sobre un objeto.

- `actionType` <string>: Posibles valores: `take`, `move`, `open`, `use`, `examine`
y `combine`. La acción open también sirve para cerrar si el objeto está abierto.
- `doWith` <string>: Parámetroo especial para acciones de tipo `combine`. Especifica con 
qué se combina.
- `conditions` <string (lista)>: Lista de condiciones a cumplir para poder hacer la acción.
Las condiciones pueden ser nombres de variables a verificar o las palabras clave `true` o `false`
que siempre tienen el valor de su nombre. Para la condición final se usa una operación AND sobre
todas las condiciones de lla lista.
- `actionText` <string>: Texto a mostrar cuando se realiza esta acción.
Si se usa con `examine`, se mostrará primero la descripción del objeto y después este texto.
- `failedText` <string>: Texto a mostrar cuando se intenta realizar una acción y no cumple las
condiciones para poder realizarse.
- `triggers` <Trigger (lista)> La lista de modificaciones a hacer sobre el estado del nivel.

> Si `allowed` se omite, la presencia de la acción en la lista se tomará como que implica que
es `true`. Si `allowed` es `false` y no hay texto de acción, se mostrará un mensaje genérico
diciendo que eso no es posible.

ListaConexiones
---------------

Contiene las conexiones en diferentes direcciones de una habitación. Todas las propiedades direccionales
son opcionales, si se omiten, se considerará que en esa dirección no hay nada.

- `north` <Conexion>
- `south` <Conexion>
- `east` <Conexion>
- `west` <Conexion>
- `up` <Conexion>
- `down` <Conexion>

Conexion
--------

Representa una conexión de una habitación con otra y sus propiedades.

- `destination` <string>: El nombre de la habitación a la que se conecta.
- `open` <bool>: Indicador de si la conexión está inicialmente abierta.
- `closedText` <string>: Mensaje a mostrar si el jugador intenta pasar estando cerrada. Si se
omite se mostrará un mensaje genérico.

Inventario
----------

Contiene el inventario inicial del jugador al comienzo del nivel.

- `items` <Objecto (lista)>: Lista de objetos que tiene el usuario.

Trigger
-------

Disparadores de eventos, la propiedad `type` define el tipo y según éste las propiedades del objeto
pueden cambiar.

- `type` <string>: Puede ser `switch_open`, `switch_state_flag`, `spawn`, `destroy`,
`update` o `finish`.
- `flagName` <bool>: El nombre del flag a cambiar.
- `flagValue` <bool>: Nuevo valor para el flag. Si se omite, simplemente se le invierte el valor.
- `connection` <string>: Formato: `origen-destino` u `origen>destino`. Donde el origen y
el destino son los nombres de las habitaciones conectadas. Si se usa '-' se abre en
ambas direcciones, si se usa '>' se abre sólo en una.
- `objectName` <string>: El nombre del objeto sobre el que actuar. Válido para todos los tipos
excepto `switch_open` y `finish`.
- `newDescription` <string>: Válido para triggers de tipo `update`.
- `newLocation` <string>: Cambia el texto de ubicación del objeto en la sala.
- `newPosition` <string>: Cambia la ubicación en el juego del objeto. Puede servir para sacar
un objeto del inventario y ponerlo en la habitación.
- `objectPosition` <string>: Nombre de la habitación en la que aparece el objeto. Válido para
el tipo `spawn`.

StateTrigger
------------

Básicamente define unas condiciones del estado y, cuando se cumplen, se ejecuta.

- `positiveConditions` <string (lista)>: Flags que tienen que ser positivas para que se ejecute
- `negativeConditions` <string (lista)>: Flags que tienen que ser negativas para que se ejecute
- `mode` <string>: Puede ser `once` o `repeat`. No estoy seguro de para qué puede usarse el modo
repeat, pero lo pongo por si acaso. Si se omite, se presupone `once`. Básicamente en modo once,
cuando se alcancen las condiciones la primera vez, se lanzarán los triggers y se desactivará. En
modo `repeat`, los triggers se ejecutarán cada vez que las condiciones se cumplan. ¡Si se usa el
modo `repeat`, mucho cuidado de no provocar un bucle infinito!
- `eventText` <string>: Texto a mostrar cuando se cumple la condición.
- `triggers` <Trigger (list)>: Disparadores que se ejecutarán cuando la condición se cumpla
