# RoadFighter

# Desarrollo

La creación de un juego involucró etapas fundamentales que abarcan desde
la definición de clases y objetos hasta la implementación de la lógica
de juego y la interacción del jugador. En esta sección, exploraremos en
detalle el proceso de desarrollo destacando los componentes clave y las
estrategias utilizadas en cada fase del proyecto.

El proyecto se inició con la formulación de un diagrama UML integral y
la realización de pruebas exhaustivas en el juego original. Estas
pruebas se centraron en la identificación de las acciones y detalles
específicos asociados con cada obstáculo en el juego, lo que resultó en
una lista detallada de elementos esenciales a considerar. A partir de
esta etapa, se procedió a la programación y diseño de las clases
correspondientes, siguiendo fielmente nuestro diseño previamente
establecido. El resultado de este proceso fue la creación de un juego
funcional que logró una notable similitud con el juego original en
términos de mecánica y apariencia. El código desarrollado se encuentra
documentado y se puede visualizar a través del diagrama UML representado
en la siguiente figura:

## Aclaraciones de código importantes 

-   **Algoritmo** ***GenerarObstaculosRandom()***:Este método se implementa
    en la clase Game, el cuál utiliza los métodos
    *random\_device*,*seed\_seq*,*mt19937* para generar una semilla y
    luego usarse dentro de una distribución uniforme generada por
    *uniform\_int\_distribution* y de esta forma obtener un número
    random dentro de los valores dados. Este método es implementado para
    obtener una posición en x aleatoria y luego también para la cantidad
    de tipos de objetos que se generar obteniendo de esta forma
    distintos obstáculos.

-   **Algoritmo *MovLateral()***:Implementado en la clase Game, utiliza
    el mismo algoritmo aleatorio que el método anteriormente explicado
    pero en este caso para mover el auto amarillo o los obstáculos de
    tipo Móvil hacia la izquierda o hacia la derecha. También se puede
    observar que todos las clases que heredan de obstáculo tienen
    implementado un *mov\_lateral* y la única clase que lo implementa es
    la clase Móvil, ésto se realizó de esta forma para poder evitar el
    chequeo de tipos en el algoritmo explicado.

-   **Algoritmo *timerOutEvent()***:Se implementa en los $slots$ de la
    clase MiWidget, donde con la ayuda de la librerías *QKeyEvent* y
    *QMap*, redefiniendo los métodos *keyReleaseEvent* y *keyPressEvent*
    (pertenecen a *QKeyEvent*) los cuáles detectan el pulsado de teclas
    de forma que nos almacenen en el *QMap* si son presionadas o no. Un
    *QMap* lo podemos interpretar como un diccionario de python, con lo
    cuál en el evento descripto se llama a cada \"llave\" de las teclas
    que necesitamos para ver si fueron pulsadas o no. Este evento esta
    conectado a un timer de 20ms(igual que el refresco de pantalla) para
    que se actualice el estado de cada tecla.

## Mejoras 

-   Para la creación de obstáculos se utiliza un algoritmo completamente
    aleatorio, el cual utilizar probabilidades para generarlos,
    existiendo una posibilidad de que los objetos se superpongan en
    algún momento. Es mejorable utilizando intervalos mayores para
    mejorar el aleatorio.

-   Tener un menú de inicio con mejores configuraciones y el inicio del
    juego sea más amigable.

-   Es posible también agregarle un soundtrack al juego, con efectos de
    sonido al chocar con autos, la explosión del jugador al perder o
    cuando el auto de desestabiliza.

-   Agregar distintos tipos de modos de juego, quizás algunos con
    niveles que tengan un fondo cambiante o nuevos obstáculos a los
    cuáles debe enfrentarse el jugador.

-   Podría haberse agregado más Labels para indicar qué tan roto está el
    auto a medida que va chocando y mejorar el texto para que sea más
    legible.

## Extensibilidad 

-   Es posible crear múltiples niveles aleatorios, dado al algoritmo
    utilizado para generar los obstáculos, es tan simple como aumentar
    el largo de la lista implementada(actualmente esta configurado a un
    máximo de 5).

-   Se pueden adicionar otros obstáculos con el fin de aumentar la
    dificultad.

-   La velocidad del juego se puede incrementar, incluso es posible
    hacerlo durante el juego. Por ejemplo, si se llega a una puntuación
    mayor a 10000.

-   Es posible cambiar la gráfica completamente.

## Problemas encontrados - Bugs

-   **Linea de Ruta - Arboles:** En el caso de las líneas de la ruta, se
    puede observar que al mantener apretado el acelerar muchas veces en
    pocos intervalos de tiempo, las líneas de la ruta comienzan a subir
    hacia arriba hasta perderse de la vista de la pantalla. Al mantener
    una velocidad constante o no hacer intervalos tan pequeños
    acelerando éste problema no afecta en lo más mínimo. De forma
    similar sucede con los árboles, solo que en el caso de estos al
    tener más espacio entre ellos no se nota tanto.

-   **Final llegando a cantidad máxima de choques:** Al impactar por
    séptima vez con alguno de los autos rojos o amarillos, el auto
    explota. El problema es que, cuando esto sucede y presionamos el
    botón de reiniciar, debemos hacerlo múltiples veces hasta que el
    auto se desplace a la posición final por haber chocado que le
    correspondía de no haber explotado. Una vez llegada a esta posición
    el juego se reinicia.

-   **Resize labels puntuación:** En el caso de este bug, al extender o
    reducir la pantalla del juego todos los elementos en éste se
    re-dimensionan a excepción de los labels de puntuación y nafta los
    cuáles quedan en un punto fijo de la pantalla y al aumentarla se
    dejan de visualizar.

-   **Superposición de Obstáculos** Al no avanzar de forma constante o
    quedarse quieto por un tiempo largo, hace que algunas veces los
    autos se superpongan unos con otros.

# Especificaciones de Uso

## Objetivo 

El juego consiste en intentar alcanzar la mayor cantidad de puntos antes
de que el auto se quede sin nafta o explote por las colisiones. Cada
nafta tomada suma 1000 puntos y por cada segundo que pasa se ganan 10
puntos.

## Teclas 

-   Movimiento horizontal: Con las teclas direccionales (flechitas) de
    derecha e izquierda podemos mover el auto violeta de derecha a
    izquierda respectivamente.

-   Acelerar: La tecla de "A" es la utilizada para acelerar el auto.

-   La tecla de "TAB" es la encargada de reiniciar el juego

## Obstáculos 

El juego cuenta con 3 principales obstáculos que deben intentar
esquivarse siempre que se pueda ya que desestabilizarán el auto
desviándolo hacia alguno de los lados.

-   **Auto Rojo**: El auto rojo será un auto que se moverá siempre hacia
    adelante y no tendrá ningún movimiento lateral.

-   **Auto Amarillo**: Este auto es igual que el rojo pero tiene la
    característica que se puede mover horizontalmente, siendo un peligro
    mayor para el jugador.

-   **Mancha de Agua**: La mancha de agua no aumenta el número de colisiones
    que tenga el auto pero lo desestabilizará.

## GAME OVER 

El juego terminara cuando sucedan alguna de la siguiente condiciones:

-   Se colisione con el borde de la ruta

-   Se acabe el combustible

-   Se acumule una cantidad de colisiones con los autos igual a 7.
