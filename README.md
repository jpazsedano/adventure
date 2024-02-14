Motor Adventure
===============

El objetivo del motor adventure es dar la posibilidad de crear aventuras de texto con
ilustraciones. Sin embargo, para poder reutiliarlo (o evolucionarlo si al final cambio de
idea y decido hacer una aventura gráfica) el motor va a ser modular.

Se programará en C++ ya que es el lenguaje más versátil para poder ser utilizado en
cualquier plataforma. Incluso puedo hacer una versión de DOS si me da la gana.

Modelo de aventuras
-------------------

Este módulo básicamente contendrá la lógica del juego. Definirá las habitaciones, objetos que
contienen, inventario, descripciones de todos los objetos (recogibles o no), conexiones y
condiciones para abrirlas, posibilidad de utilización de objetos entre sí... Si metemos
esto en un intérprete de código debería poder jugarse el juego con él llamando a las
funciones.

Requisitos:

- Gestión de habitaciones. Qué habitaciones hay y cómo están conectadas y qué caminos
están bloqueados.
- Gestión de objetos. Objetos, su descripción, imagen, si son inamovibles o no, etc. Así
como su ubicación, que puede ser una habitación, el inventario o fuera del juego (si aún
no han hecho spawn). La ubicación del objeto debe ser independiente del modelo de mundo, así
que el gestor de habitaciones gererará los "puntos" con un ID asociado y el gestor de objetos
sólo se encargará de usar estos IDs.
- Gestión de puzzles. Los puzzles son una responsabilidad un poco distribuida. Básicamente
consiste en revisar las acciones que se realizan para, si fuera necesario, desbloquear
caminos, cambiar la posibilidad de recoger o no un objeto y hacer aparecer o desaparecer
objetos del escenario o inventario.

Por supuesto esto son tres responsabilidades diferentes y deben estar bien separadas.
> **Nota**: Las acciones que el jugador realiza sobre el entorno no sé si entrarían dentro
de la gestión de habitaciones o en la gestión de puzzles. Algo me dice que más bien en la
segunda. O quizás debería ser un módulo separado que se comunique con ambos (los verbos de
movimiento irían la gestión de habitaciones y el resto a la de puzzles).

La idea es que si quiero utilizar este mismo motor para una aventura gráfica o incluso para
una aventura con plataformas y combate, se pueda reutilizar el código. En el caso de la
aventura gráfica debería poder reutilizar todo el modelo y cambiar únicamente la interfaz y en
el caso de un juego de plataformas, acción y aventuras sólo tendría que reescribir la gestión
de habitaciones (ya que el jugador ahora podría explorar de forma más abierta).

Interfaz conversacional
-----------------------

Dentro de la interfaz se incluye la vista y el controlador necesario para que el jugador
pueda interactuar con el juego. No habrá acción en tiempo real, por lo que el ciclo
dependerá enteramente de las entradas del jugador y no de un ciclo de actualización de
pantalla.
