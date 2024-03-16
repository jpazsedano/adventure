0.1.0-alpha
===========

Tenemos un modelo bastante avanzado, al que todavía le quedan algunas
funcionalidades importantes por ser implementadas, las cuales se pueden
ver en la especificación de descripción de nivel.

Notablemente, el modelo no tiene en cuenta todas las acciones que el jugador
puede hacer sobre los objetos y al sistema de eventos y triggers le falta una
capa y poder realizar actualizaciones más complejas. Sobre todo actualizaciones
sobre las acciones que se pueden hacer sobre los objetos.

Otra cosa que le falta al modelo es la posibilidad de almacenar en los objetos
información sobre dónde están ubicados. El objetivo es poder hacer un listing de
objetos de forma programática, sin tener que escribirlo en la descripción de
la habitación.

También necesitamos la funcionalidad necesaria para cargar los niveles. Esto es,
necesitamos definir un formato nativo para el motor (seguramente sea YAML, JSON o
alguno ya hecho), escribir el código para cargar dicho formato y hacer el script
de conversión de assets.

Aparte del modelo, aún no tenemos ningún tipo de interfaz. Si queremos empezar a
realizar pruebas del código hay que tener al menos una provisional, aunque sea
puramente CLI y no pueda mostrar imágenes ni estructurar la pantalla.

El próximo milestone debería ser tener una versión con interfaz simplificada que
sea capaz de cargar y jugar un nivel sencillo.

> NOTA: Me acabo de dar cuenta de otro problema. Tal y como está planteado, no
estamos teniendo en cuenta las dependencias de las acciones, cosa que es clave
para el desarrollo de la aventura. Ejemplo: la puerta no se puede abrir, si no
has quitado el cepo. He parcheado en el diseño un sistema simple de variables
y condiciones. Hay que mirar a ver qué tal funciona. A ver si puedo meter
descripciones alternativas según una variable de alguna forma...

TODO
----

+ Actualizar las cabeceras del modelo a las funcionalidades nuevas (sin probar)
+ Actualizar las implementciones del modelo a las funcionalidades nuevas (sin probar)
- Establecer formato de ficheros para ser cargados por el motor.
- Programar el cargador de niveles del motor.
- Programar el script de conversión de descripción de nivel.
- Programar interfaz CLI sencilla para el bucle principal.
- Hacer un makefile simple.
+ Terminar nivel de prueba. (Hecho)
