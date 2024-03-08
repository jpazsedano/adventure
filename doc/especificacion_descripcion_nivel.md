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
- `nextLevel` <string>: Nombre del siguiente nivel. Se puede usar la palabra clave
`END` para indicar que no hay y que éste es el último nivel.

Mapa
----

Contiene el layout del nivel y los objetos almacenados en él.

- `rooms` <Habitacion (lista)>. Lista de habitaciones.
- `start` <string>. Nombre de la habitación

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
- `canTake` <bool>: Flag que indica si el objeto puede ser tomado. No hay TakeText ya que si hay un texto al tomarlo, es un evento.
- `canMove` <bool>: Flag que indica si el objeto puede ser desplazado.
- `canOpen` <bool>: Flag que indica si el objeto puede ser abierto o puede ser cerrado.
- `canActivate` <bool>: Flag que indica si el objeto puede ser activado o desactivado.
- `hidden` <bool>: Por defecto es `false`, pero si se especifica `true`, el objeto se almacenará
en la lista de objetos no spawneados. Básicamente es un shortcut para poner en un mismo sitio los
objetos que están en la sala y los que van a aparecer o hacerse visibles en la sala en algún momento.
- `onTake` <Trigger (lista)>: Triggers que se disparan al recoger el objeto. Ninguno si la
propiedad no existe.
- `onMove` <Trigger (lista)>: Ídem para la acción de mover.
- `onOpen` <Trigger (lista)>: Lo mismito para la acción de abrir.
- `onActivate` <Trigger (lista)>: También para la acción de activar.
- `onExamine` <Trigger (lista)>: E incluso para la acción de examinar. Útil para que el personaje se
de cuenta de la existencia de un objeto al examinar algo.
- `onCombine` <Trigger (lista)>: Otra posible acción que requiere de reacciones es combinar objetos.
OJO: Si se pone el evento en ambos objetos, los triggers deben ser idénticos. Si sólo está en uno, el
evento se aplicará igualmente aunque se haga al reves de cómo se define aquí.

> La omisión de cualquiera de los flags de acción dará por hecho que es `false`.

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

Triggers
--------

Disparadores de eventos, la propiedad `type` define el tipo y según éste las propiedades del objeto
pueden cambiar.

- `type` <string>. Puede ser `switch_open`, `switch_pick_flag`, `switch_open_flag`, `swtich_move_flag`, `switch_activate_flag`, `spawn`, `destroy` `update` o `finish`.
- `object_name` <string>. El nombre del objeto sobre el que actuar. Válido para todos los tipos excepto `switch_open` y `finish`.
- `other_object_name` <string>. Sólo para la acción `combine` que requiere dos objetos.
- `new_description` <string>. Válido para triggers de tipo `update`.
- `object_position` <string>. Nombre de la habitación en la que aparece el objeto. Válido para el tipo `spawn`.

