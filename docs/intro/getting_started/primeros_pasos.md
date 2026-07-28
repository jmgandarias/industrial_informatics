
Informática Industrial  
Grado en Ingeniería Electrónica Industrial  
Universidad de Málaga  
[Juan M. Gandarias](https://jmgandarias.com)  
[jmgandarias@uma.es](mailto:jmgandarias@uma.es)

# Primeros pasos

## 1. ¿Qué es un microcontrolador?

Un microcontrolador es un circuito integrado compacto diseñado para realizar tareas específicas dentro de un sistema embebido. A diferencia de los ordenadores de propósito general, los microcontroladores están optimizados para controlar dispositivos, sensores y actuadores en aplicaciones en tiempo real.
Características principales:

- Bajo consumo de energía
- Capacidades de procesamiento en tiempo real
- Integración de CPU, memoria y periféricos en un solo chip

Los microcontroladores se utilizan ampliamente en automatización, robótica, dispositivos IoT y sistemas de control industrial.

## 2. Hardware y herramientas del curso

En este curso, usaremos los siguientes componentes y herramientas:

### 2.1. Microcontrolador ESP32

El [ESP32](https://www.espressif.com/en/products/socs/esp32) es un microcontrolador potente y versátil que incluye:

- Procesador de doble núcleo
- Wi-Fi y Bluetooth integrados
- Múltiples pines GPIO para sensores y actuadores
- Soporte para varios protocolos de comunicación (I2C, SPI, UART)

### 2.2. Simulador Wokwi

[Wokwi](https://wokwi.com/) es un simulador en línea que te permite:

- Crear prototipos de circuitos sin hardware físico
- Probar y depurar proyectos de Arduino, ESP32 y otros microcontroladores
- Visualizar el comportamiento de sensores y actuadores en tiempo real simulado

### 2.3. Arduino IDE

El [Entorno de Desarrollo Integrado (IDE) de Arduino](https://docs.arduino.cc/software/ide/#ide-v2) será nuestra principal herramienta de programación. Proporciona:

- Una interfaz sencilla para escribir y cargar código
- Bibliotecas amplias para sensores, pantallas y comunicación
- Compatibilidad multiplataforma (Windows, macOS, Linux)

### 2.4. Kit de desarrollo M5Core2

El [M5Core2](https://docs.m5stack.com/en/core/core2) es un dispositivo basado en ESP32 con:

- Pantalla táctil
- Sensores integrados y puertos de expansión
- Un diseño modular para prototipado rápido

## 3. Material adicional de programación

Si no te sientes con la confianza suficiente para seguir el contenido de este curso por falta de conocimientos de programación, o quizá ya hiciste un curso de programación antes pero hace tiempo y no recuerdas bien cómo hacerlo, aquí tienes material extra que puede ayudarte.

En este curso programaremos microcontroladores basados en ESP32 en C/C++ usando Arduino IDE.

Hay varias fuentes de información gratuitas en internet que puedes usar. Estas son las que considero más útiles para el propósito de este curso:

### 3.1. Aprende C++

En [este sitio web](https://www.learncpp.com/) tienes toda la información necesaria sobre cómo programar en C++, incluyendo muchos elementos que van más allá del contenido de este curso.

### 3.2. Curso de introducción a la programación de Luis Llamas

[Este es un curso](https://www.luisllamas.es/en/development-course/) que cubre temas generales de programación (puedes encontrarlo en inglés y español). En muchas de las entradas encontrarás ejemplos en distintos lenguajes (no olvides seleccionar C/C++). La siguiente lista muestra:

1. Los **conceptos mínimos** que deberías conocer antes de tomar este curso. Sin estos conocimientos, te será difícil seguirlo.
2. Los **conceptos deseables** para tener antes de tomar este curso. Complementan la lista anterior y, si los tienes, podrás seguir el curso sin problema.
3. Los **conceptos avanzados**. Completan las dos listas anteriores. Si los dominas, tu conocimiento de programación supera lo requerido para este curso.

#### 3.2.1. Conceptos mínimos

1. Introducción
      - [Qué es la programación](https://www.luisllamas.es/en/what-is-programming/)
      - [Breve historia de la programación](https://www.luisllamas.es/en/brief-history-of-programming/)
      - [Evolución de los lenguajes](https://www.luisllamas.es/en/evolution-programming-languages/)
      - [Fases del desarrollo de software](https://www.luisllamas.es/en/programming-development-phases/)

2. Fundamentos
    - [Tipos de programas](https://www.luisllamas.es/en/programming-types-of-programs/)

3. Conceptos frecuentes
    - [Qué es una biblioteca](https://www.luisllamas.es/en/programming-what-is-a-library/)
    - [Qué son las dependencias](https://www.luisllamas.es/en/programming-what-are-dependencies/)
    - [Versionado semántico](https://www.luisllamas.es/en/programming-semantic-versioning/)
    - [Paquetes y gestores de paquetes](https://www.luisllamas.es/en/programming-package-managers/)

4. Herramientas
    - [Qué es un IDE](https://www.luisllamas.es/en/programming-what-is-an-ide/)

5. Estructura del programa
    - [Estructura de un programa](https://www.luisllamas.es/en/programming-program-structure/)
    - [Ciclo de vida de un programa](https://www.luisllamas.es/en/programming-program-life-cycle/)
    - [Sentencias y bloques](https://www.luisllamas.es/en/programming-statements-and-blocks/)
    - [Qué es la indentación](https://www.luisllamas.es/en/programming-indentation/)
    - [Qué son los comentarios](https://www.luisllamas.es/en/programming-comments/)

6. Expresiones y operadores
    - [Operadores y expresiones](https://www.luisllamas.es/en/programming-operators-and-expressions/)
    - [Precedencia de operadores](https://www.luisllamas.es/en/programming-operator-precedence/)
    - [Operadores de acceso](https://www.luisllamas.es/en/programming-access-operators/)
    - [Operadores de asignación](https://www.luisllamas.es/en/programming-assignment-operators/)
    - [Operadores aritméticos](https://www.luisllamas.es/en/programming-arithmetic-operators/)
    - [Operadores de comparación](https://www.luisllamas.es/en/programming-comparison-operators/)
    - [Operadores lógicos](https://www.luisllamas.es/en/programming-logical-operators/)

7. Variables
    - [Qué es una variable](https://www.luisllamas.es/en/programming-what-is-a-variable/)
    - [Qué es una constante](https://www.luisllamas.es/en/programming-what-is-a-constant/)

8. Tipos de datos
    - [Tipos de datos](https://www.luisllamas.es/en/programming-data-types/)
    - [Lenguajes tipados y no tipados](https://www.luisllamas.es/en/typed-vs-untyped-languages/)

9. Tipos comunes
    - [Booleano](https://www.luisllamas.es/en/programming-boolean-types/)
    - [Numérico](https://www.luisllamas.es/en/programming-numeric-types/)
    - [Texto](https://www.luisllamas.es/en/programming-text-types/)

10. Flujo de control
    - [Qué es el flujo de control](https://www.luisllamas.es/en/programming-flow-control/)
    - [Sentencia Go-to](https://www.luisllamas.es/en/programming-goto/)
    - [Qué es un condicional](https://www.luisllamas.es/en/programming-conditionals/)
    - [Qué es un bucle](https://www.luisllamas.es/en/programming-loops/)

11. Condicionales
    - [If](https://www.luisllamas.es/en/programming-if-statement/)
    - [If-else](https://www.luisllamas.es/en/programming-if-else-statement/)
    - [If-elseif](https://www.luisllamas.es/en/programming-if-elseif-statement/)
    - [Switch](https://www.luisllamas.es/en/programming-switch-statement/)

12. Bucles
    - [While](https://www.luisllamas.es/en/programming-while-loop/)
    - [Do-while](https://www.luisllamas.es/en/programming-do-while-loop/)
    - [For](https://www.luisllamas.es/en/programming-for-loop/)

13. Funciones
    - [Qué es una función](https://www.luisllamas.es/en/programming-what-is-a-function/)

#### 3.2.2. Conceptos deseables

1. Fundamentos
    - [Código máquina](https://www.luisllamas.es/en/programming-machine-code/)

2. Herramientas
    - [Mejores IDEs](https://www.luisllamas.es/en/programming-best-ides/)
    - [Control de código fuente](https://www.luisllamas.es/en/programming-what-is-source-code-control/)

3. Variables
    - [Alcance de variables](https://www.luisllamas.es/en/programming-scope-of-variables/)

4. Referencias
    - [Qué es una referencia](https://www.luisllamas.es/en/what-is-a-reference/)
    - [Tipo, valor y referencia](https://www.luisllamas.es/en/type-value-and-reference/)
    - [Parámetros por valor o por referencia](https://www.luisllamas.es/en/value-or-reference-parameters/)

5. Condicionales
    - [Condicionales anidados](https://www.luisllamas.es/en/nested-conditionals-programming/)

6. Bucles
    - [Bucles anidados](https://www.luisllamas.es/en/nesting-loops-programming/)

7. Funciones
    - [Parámetros de función](https://www.luisllamas.es/en/programming-function-parameters/)
    - [Valor de retorno de función](https://www.luisllamas.es/en/programming-function-returns/)
    - [Sobrecarga de funciones](https://www.luisllamas.es/en/function-overloading/)

8. Colecciones
    - [Arrays](https://www.luisllamas.es/en/what-is-an-array/)

9. Estructuras de datos
    - [Structs](https://www.luisllamas.es/en/what-is-a-struct/)

#### 3.2.3. Conceptos avanzados

1. Fundamentos
    - [Lenguaje ensamblador](https://www.luisllamas.es/en/programming-assembly-language/)

2. Herramientas
    - [Visual Studio Code](https://www.luisllamas.es/en/what-is-visual-studio-code/)
    - [Node.js](https://www.luisllamas.es/en/what-is-node-js/)
    - [NPM](https://www.luisllamas.es/en/what-is-and-how-to-use-npm/)

3. Variables
    - [Desestructuración](https://www.luisllamas.es/en/destructuring-programming/)

4. Tipos de datos
    - [Deducción de tipos](https://www.luisllamas.es/en/type-deduction-by-context-programming/)

5. Tipos comunes
    - [Tiempo](https://www.luisllamas.es/en/programming-time-types/)
    - [Enums](https://www.luisllamas.es/en/programming-enums/)
    - [Colecciones](https://www.luisllamas.es/en/programming-collections/)
    - [Agrupaciones](https://www.luisllamas.es/en/programming-groupings/)

6. Referencias
    - [Referencias a funciones](https://www.luisllamas.es/en/programming-references-to-functions/)

7. Flujo de control
    - [Excepciones y Try-Catch](https://www.luisllamas.es/en/exception-handling-try-catch/)

8. Condicionales
    - [Operador ternario](https://www.luisllamas.es/en/programming-ternary-operator/)

9. Bucles
    - [Foreach](https://www.luisllamas.es/en/programming-foreach-loop/)

10. Funciones
    - [Funciones lambda](https://www.luisllamas.es/en/programming-lambda-functions/)
    - [Funciones recursivas](https://www.luisllamas.es/en/recursive-functions-programming/)
    - [Pasar funciones como parámetros](https://www.luisllamas.es/en/passing-functions-as-parameters/)

11. Colecciones
    - [Arrays dinámicos](https://www.luisllamas.es/en/what-is-a-dynamic-array/)
    - [HashSet](https://www.luisllamas.es/en/what-is-a-hashset/)
    - [Diccionarios](https://www.luisllamas.es/en/what-is-a-dictionary/)
    - [Listas enlazadas](https://www.luisllamas.es/en/what-is-a-linked-list/)
    - [Pilas](https://www.luisllamas.es/en/what-is-a-stack/)
    - [Cola](https://www.luisllamas.es/en/what-is-a-queue/)
    - [Eficiencia de las colecciones](https://www.luisllamas.es/en/collection-efficiency-in-programming/)

12. Estructuras de datos
    - [Objetos](https://www.luisllamas.es/en/what-is-an-object/)
    - [Programación orientada a objetos](https://www.luisllamas.es/en/object-oriented-programming-course/)
    - [Tuplas](https://www.luisllamas.es/en/what-is-a-tuple/)
    - [Grafos](https://www.luisllamas.es/en/what-is-a-graph/)
    - [Árboles](https://www.luisllamas.es/en/what-is-a-tree/)

13. Asincronía
    - [Programación asíncrona (lo veremos en el Tema 6)](https://www.luisllamas.es/en/programming-asynchrony-concurrency/)
    - [Concurrencia y paralelismo (lo veremos en el Tema 6)](https://www.luisllamas.es/en/asynchrony-concurrency-parallelism/)

<!-- 1. Introduction
      - [What is programming](https://www.luisllamas.es/en/what-is-programming/)
      - [Brief history of programming](https://www.luisllamas.es/en/brief-history-of-programming/)
      - [Evolution of languages](https://www.luisllamas.es/en/evolution-programming-languages/)
      - [Software development phases](https://www.luisllamas.es/en/programming-development-phases/)

1. Fundamentals
    - [Types of programs](https://www.luisllamas.es/en/programming-types-of-programs/)
    - [Console applications](https://www.luisllamas.es/en/what-is-a-console-application/)
    - [Machine code](https://www.luisllamas.es/en/programming-machine-code/)
    - [Assembly language](https://www.luisllamas.es/en/programming-assembly-language/)

2. Frequent Concepts
    - [What is a library](https://www.luisllamas.es/en/programming-what-is-a-library/)
    - [What are dependencies](https://www.luisllamas.es/en/programming-what-are-dependencies/)
    - [Semantic versioning](https://www.luisllamas.es/en/programming-semantic-versioning/)
    - [Packages and package managers](https://www.luisllamas.es/en/programming-package-managers/)

3. Tools
    - [What is an IDE](https://www.luisllamas.es/en/programming-what-is-an-ide/)
    - [Top IDEs](https://www.luisllamas.es/en/programming-best-ides/)
    - [Source code control](https://www.luisllamas.es/en/programming-what-is-source-code-control/)
    - [Visual Studio](https://www.luisllamas.es/en/what-is-visual-studio/)
    - [Visual Studio Code](https://www.luisllamas.es/en/what-is-visual-studio-code/)
    - [Node.js](https://www.luisllamas.es/en/what-is-node-js/)
    - [NPM](https://www.luisllamas.es/en/what-is-and-how-to-use-npm/)

4. Program Structure
    - [Program structure](https://www.luisllamas.es/en/programming-program-structure/)
    - [Program lifecycle](https://www.luisllamas.es/en/programming-program-life-cycle/)
    - [Statements and blocks](https://www.luisllamas.es/en/programming-statements-and-blocks/)
    - [What is indentation](https://www.luisllamas.es/en/programming-indentation/)
    - [What are comments](https://www.luisllamas.es/en/programming-comments/)

5. Expressions and Operators
    - [Operators and expressions](https://www.luisllamas.es/en/programming-operators-and-expressions/)
    - [Operator precedence](https://www.luisllamas.es/en/programming-operator-precedence/)
    - [Access operators](https://www.luisllamas.es/en/programming-access-operators/)
    - [Assigment operators](https://www.luisllamas.es/en/programming-assignment-operators/)
    - [Arithmetic operators](https://www.luisllamas.es/en/programming-arithmetic-operators/)
    - [Comparison operators](https://www.luisllamas.es/en/programming-comparison-operators/)
    - [Logical operators](https://www.luisllamas.es/en/programming-logical-operators/)

6. Variables
    - [What is a variable](https://www.luisllamas.es/en/programming-what-is-a-variable/)
    - [What is a constant](https://www.luisllamas.es/en/programming-what-is-a-constant/)
    - [Variable scope](https://www.luisllamas.es/en/programming-scope-of-variables/)
    - [Destructuring](https://www.luisllamas.es/en/destructuring-programming/)

7. Data Types
    - [Data types](https://www.luisllamas.es/en/programming-data-types/)
    - [Typed and untyped languages](https://www.luisllamas.es/en/typed-vs-untyped-languages/)
    - [Type deduction](https://www.luisllamas.es/en/type-deduction-by-context-programming/)

8. Common types
    - [Boolean](https://www.luisllamas.es/en/programming-boolean-types/)
    - [Numeric](https://www.luisllamas.es/en/programming-numeric-types/)
    - [Text](https://www.luisllamas.es/en/programming-text-types/)
    - [Time](https://www.luisllamas.es/en/programming-time-types/)
    - [Enums](https://www.luisllamas.es/en/programming-enums/)
    - [Collection](https://www.luisllamas.es/en/programming-collections/)
    - [Grouping](https://www.luisllamas.es/en/programming-groupings/)

9.  References
    - [What is a reference](https://www.luisllamas.es/en/what-is-a-reference/)
    - [Type value and reference](https://www.luisllamas.es/en/type-value-and-reference/)
    - [Parameters by value or reference](https://www.luisllamas.es/en/value-or-reference-parameters/)
    - [Function references](https://www.luisllamas.es/en/programming-references-to-functions/)

10. Control Flow
    - [what is control flow](https://www.luisllamas.es/en/programming-flow-control/)
    - [Go-to statemet](https://www.luisllamas.es/en/programming-goto/)
    - [What is a conditional](https://www.luisllamas.es/en/programming-conditionals/)
    - [What is a loop](https://www.luisllamas.es/en/programming-loops/)
    - [Exceptions and Try-Catch](https://www.luisllamas.es/en/exception-handling-try-catch/)

11. Conditionals
    - [If](https://www.luisllamas.es/en/programming-if-statement/)
    - [If-else](https://www.luisllamas.es/en/programming-if-else-statement/)
    - [If-elseif](https://www.luisllamas.es/en/programming-if-elseif-statement/)
    - [Switch](https://www.luisllamas.es/en/programming-switch-statement/)
    - [Nested conditionals](https://www.luisllamas.es/en/nested-conditionals-programming/)
    - [Ternary operator](https://www.luisllamas.es/en/programming-ternary-operator/)

12. Loops
    - [While](https://www.luisllamas.es/en/programming-while-loop/)
    - [Do-while](https://www.luisllamas.es/en/programming-do-while-loop/)
    - [For](https://www.luisllamas.es/en/programming-for-loop/)
    - [Foreach](https://www.luisllamas.es/en/programming-foreach-loop/)
    - [Nested loops](https://www.luisllamas.es/en/nesting-loops-programming/)

13. Functions
    - [What is a function](https://www.luisllamas.es/en/programming-what-is-a-function/)
    - [Function Parameters](https://www.luisllamas.es/en/programming-function-parameters/)
    - [Function return value](https://www.luisllamas.es/en/programming-function-returns/)
    - [Function overloading](https://www.luisllamas.es/en/function-overloading/)
    - [Lambda functions](https://www.luisllamas.es/en/programming-lambda-functions/)
    - [Recursive functions](https://www.luisllamas.es/en/recursive-functions-programming/)
    - [Passing functions as parameters](https://www.luisllamas.es/en/passing-functions-as-parameters/)

14. Collections
    - [Arrays](https://www.luisllamas.es/en/what-is-an-array/)
    - [Dynamic arrays](https://www.luisllamas.es/en/what-is-a-dynamic-array/)
    - [HashSet](https://www.luisllamas.es/en/what-is-a-hashset/)
    - [Dictionaries](https://www.luisllamas.es/en/what-is-a-dictionary/)
    - [LinkedLists](https://www.luisllamas.es/en/what-is-a-linked-list/)
    - [Stacks](https://www.luisllamas.es/en/what-is-a-stack/)
    - [Queue](https://www.luisllamas.es/en/what-is-a-queue/)
    - [Efficiency of collections](https://www.luisllamas.es/en/collection-efficiency-in-programming/)

15. Data Structures
    - [Structs](https://www.luisllamas.es/en/what-is-a-struct/)
    - [Objects](https://www.luisllamas.es/en/what-is-an-object/)
    - [Object oriented programming](https://www.luisllamas.es/en/object-oriented-programming-course/)
    - [Tuples](https://www.luisllamas.es/en/what-is-a-tuple/)
    - [Graphs](https://www.luisllamas.es/en/what-is-a-graph/)
    - [Trees](https://www.luisllamas.es/en/what-is-a-tree/)

16. Asynchrony
    - [Asynchronous programming (we'll see it in Lecture 6)](https://www.luisllamas.es/en/programming-asynchrony-concurrency/)
    - [Concurrency and Paralellism (we'll see it in Lecture 6)](https://www.luisllamas.es/en/asynchrony-concurrency-parallelism/) -->

## 4. Material adicional sobre ESP32

Puedes encontrar más material sobre cómo programar microcontroladores (en particular, ESP32) en la web de Luis Llamas, [aquí](https://www.luisllamas.es/en/esp8266-esp32-course/) y [aquí](https://www.luisllamas.es/en/arduino-tutorials/). Parte de este material se cubrirá en nuestro curso.
