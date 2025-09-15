# Getting Started

## 1. What is a Microcontroller?

A microcontroller is a compact integrated circuit designed to perform specific tasks within an embedded system. Unlike general-purpose computers, microcontrollers are optimized for controlling devices, sensors, and actuators in real-time applications.
Key characteristics:

- Low power consumption
- Real-time processing capabilities
- Integration of CPU, memory, and peripherals on a single chip

Microcontrollers are widely used in automation, robotics, IoT devices, and industrial control systems.

## 2. Course Hardware and Tools

In this course, we will use the following components and tools:

### 2.1. ESP32 Microcontroller

The [ESP32](https://www.espressif.com/en/products/socs/esp32) is a powerful and versatile microcontroller featuring:

- Dual-core processor
- Built-in Wi-Fi and Bluetooth
- Multiple GPIO pins for sensors and actuators
- Support for various communication protocols (I2C, SPI, UART)

### 2.2. Wokwi Simulator

[Wokwi](https://wokwi.com/) is an online simulator that allows you to:

- Prototype circuits without physical hardware
- Test and debug Arduino, ESP32, and other microcontrollers projects
- Visualize sensor and actuator behavior in simulated real-time
  
### 2.3. Arduino IDE

The [Arduino Integrated Development Environment (IDE)](https://docs.arduino.cc/software/ide/#ide-v2) will be our main programming tool. It provides:

- A simple interface for writing and uploading code
- Extensive libraries for sensors, displays, and communication
- Cross-platform compatibility (Windows, macOS, Linux)

### 2.4. M5Core2 Development Kit

The [M5Core2](https://docs.m5stack.com/en/core/core2) is an ESP32-based device with:

- A touchscreen display
- Built-in sensors and expansion ports
- A modular design for rapid prototyping

## 3. Additional Programming Material

If you don't feel confident enough to follow the content of this course due to lack of programming knowledge, or maybe you've taken a course on coding before but it's been a while since since then and don't remember well how to do it, here you have some extra material that could help you.

In this course we'll code ESP32-based microcontrollers in C/C++ usign the Arduino IDE.

There are several sources of information in the internet you could use for free. Here are the ones I find the most useful for the purpose of this course:

### 3.1. Learn C++

In [this website](https://www.learncpp.com/) you have all the necessary information on how to program in C++. Including many elements that go beyond the content of this course.

### 3.2. Luis Llamas' Introduction to Programming Course

[This is a course](https://www.luisllamas.es/en/development-course/) that covers general topics of programming (you can find it in Engish and Spanish). In many of the entries you can find examples in different languages (don't forget to select C/C++). The list below shows:

1. The **Minimum concepts** you should know before taking this course. Without this knowledge, it'd be hard for you to follow this course.
2. The **Desired concepts** to have before taking this course. It completes the previous list and if you have them, you'll be able to follow the course without any problem.
3. The **Advanced concepts**. It completes the two preivious lists. If you have the, your code knowdlege exceedes the required for this course.

#### 3.2.1. Minimum concepts

1. Introduction
      - [What is programming](https://www.luisllamas.es/en/what-is-programming/)
      - [Brief history of programming](https://www.luisllamas.es/en/brief-history-of-programming/)
      - [Evolution of languages](https://www.luisllamas.es/en/evolution-programming-languages/)
      - [Software development phases](https://www.luisllamas.es/en/programming-development-phases/)

2. Fundamentals
    - [Types of programs](https://www.luisllamas.es/en/programming-types-of-programs/)

3. Frequent Concepts
    - [What is a library](https://www.luisllamas.es/en/programming-what-is-a-library/)
    - [What are dependencies](https://www.luisllamas.es/en/programming-what-are-dependencies/)
    - [Semantic versioning](https://www.luisllamas.es/en/programming-semantic-versioning/)
    - [Packages and package managers](https://www.luisllamas.es/en/programming-package-managers/)

4. Tools
    - [What is an IDE](https://www.luisllamas.es/en/programming-what-is-an-ide/)

5. Program Structure
    - [Program structure](https://www.luisllamas.es/en/programming-program-structure/)
    - [Program lifecycle](https://www.luisllamas.es/en/programming-program-life-cycle/)
    - [Statements and blocks](https://www.luisllamas.es/en/programming-statements-and-blocks/)
    - [What is indentation](https://www.luisllamas.es/en/programming-indentation/)
    - [What are comments](https://www.luisllamas.es/en/programming-comments/)

6. Expressions and Operators
    - [Operators and expressions](https://www.luisllamas.es/en/programming-operators-and-expressions/)
    - [Operator precedence](https://www.luisllamas.es/en/programming-operator-precedence/)
    - [Access operators](https://www.luisllamas.es/en/programming-access-operators/)
    - [Assigment operators](https://www.luisllamas.es/en/programming-assignment-operators/)
    - [Arithmetic operators](https://www.luisllamas.es/en/programming-arithmetic-operators/)
    - [Comparison operators](https://www.luisllamas.es/en/programming-comparison-operators/)
    - [Logical operators](https://www.luisllamas.es/en/programming-logical-operators/)

7. Variables
    - [What is a variable](https://www.luisllamas.es/en/programming-what-is-a-variable/)
    - [What is a constant](https://www.luisllamas.es/en/programming-what-is-a-constant/)

8. Data Types
    - [Data types](https://www.luisllamas.es/en/programming-data-types/)
    - [Typed and untyped languages](https://www.luisllamas.es/en/typed-vs-untyped-languages/)
  
9. Common types
    - [Boolean](https://www.luisllamas.es/en/programming-boolean-types/)
    - [Numeric](https://www.luisllamas.es/en/programming-numeric-types/)
    - [Text](https://www.luisllamas.es/en/programming-text-types/)

10. Control Flow
    - [what is control flow](https://www.luisllamas.es/en/programming-flow-control/)
    - [Go-to statemet](https://www.luisllamas.es/en/programming-goto/)
    - [What is a conditional](https://www.luisllamas.es/en/programming-conditionals/)
    - [What is a loop](https://www.luisllamas.es/en/programming-loops/)
  
11. Conditionals
    - [If](https://www.luisllamas.es/en/programming-if-statement/)
    - [If-else](https://www.luisllamas.es/en/programming-if-else-statement/)
    - [If-elseif](https://www.luisllamas.es/en/programming-if-elseif-statement/)
    - [Switch](https://www.luisllamas.es/en/programming-switch-statement/)

12. Loops
    - [While](https://www.luisllamas.es/en/programming-while-loop/)
    - [Do-while](https://www.luisllamas.es/en/programming-do-while-loop/)
    - [For](https://www.luisllamas.es/en/programming-for-loop/)

13. Functions
    - [What is a function](https://www.luisllamas.es/en/programming-what-is-a-function/)

#### 3.2.2. Desired concepts

1. Fundamentals
    - [Machine code](https://www.luisllamas.es/en/programming-machine-code/)

2. Tools
    - [Top IDEs](https://www.luisllamas.es/en/programming-best-ides/)
    - [Source code control](https://www.luisllamas.es/en/programming-what-is-source-code-control/)

3. Variables
    - [Variable scope](https://www.luisllamas.es/en/programming-scope-of-variables/)

4. References
    - [What is a reference](https://www.luisllamas.es/en/what-is-a-reference/)
    - [Type value and reference](https://www.luisllamas.es/en/type-value-and-reference/)
    - [Parameters by value or reference](https://www.luisllamas.es/en/value-or-reference-parameters/)
  
5. Conditionals
    - [Nested conditionals](https://www.luisllamas.es/en/nested-conditionals-programming/)

6. Loops
    - [Nested loops](https://www.luisllamas.es/en/nesting-loops-programming/)

7. Functions
    - [Function Parameters](https://www.luisllamas.es/en/programming-function-parameters/)
    - [Function return value](https://www.luisllamas.es/en/programming-function-returns/)
    - [Function overloading](https://www.luisllamas.es/en/function-overloading/)

8. Collections
    - [Arrays](https://www.luisllamas.es/en/what-is-an-array/)
  
9. Data Structures
    - [Structs](https://www.luisllamas.es/en/what-is-a-struct/)

#### 3.2.3. Advanced concepts

1. Fundamentals
    - [Assembly language](https://www.luisllamas.es/en/programming-assembly-language/)

2. Tools
    - [Visual Studio Code](https://www.luisllamas.es/en/what-is-visual-studio-code/)
    - [Node.js](https://www.luisllamas.es/en/what-is-node-js/)
    - [NPM](https://www.luisllamas.es/en/what-is-and-how-to-use-npm/)

3. Variables
    - [Destructuring](https://www.luisllamas.es/en/destructuring-programming/)

4. Data Types
    - [Type deduction](https://www.luisllamas.es/en/type-deduction-by-context-programming/)
  
5. Common types
    - [Time](https://www.luisllamas.es/en/programming-time-types/)
    - [Enums](https://www.luisllamas.es/en/programming-enums/)
    - [Collection](https://www.luisllamas.es/en/programming-collections/)
    - [Grouping](https://www.luisllamas.es/en/programming-groupings/)
  
6. References
    - [Function references](https://www.luisllamas.es/en/programming-references-to-functions/)

7. Control Flow
    - [Exceptions and Try-Catch](https://www.luisllamas.es/en/exception-handling-try-catch/)
  
8. Conditionals
    - [Ternary operator](https://www.luisllamas.es/en/programming-ternary-operator/)

9. Loops
    - [Foreach](https://www.luisllamas.es/en/programming-foreach-loop/)

10. Functions
    - [Lambda functions](https://www.luisllamas.es/en/programming-lambda-functions/)
    - [Recursive functions](https://www.luisllamas.es/en/recursive-functions-programming/)
    - [Passing functions as parameters](https://www.luisllamas.es/en/passing-functions-as-parameters/)

11. Collections
    - [Dynamic arrays](https://www.luisllamas.es/en/what-is-a-dynamic-array/)
    - [HashSet](https://www.luisllamas.es/en/what-is-a-hashset/)
    - [Dictionaries](https://www.luisllamas.es/en/what-is-a-dictionary/)
    - [LinkedLists](https://www.luisllamas.es/en/what-is-a-linked-list/)
    - [Stacks](https://www.luisllamas.es/en/what-is-a-stack/)
    - [Queue](https://www.luisllamas.es/en/what-is-a-queue/)
    - [Efficiency of collections](https://www.luisllamas.es/en/collection-efficiency-in-programming/)

12. Data Structures
    - [Objects](https://www.luisllamas.es/en/what-is-an-object/)
    - [Object oriented programming](https://www.luisllamas.es/en/object-oriented-programming-course/)
    - [Tuples](https://www.luisllamas.es/en/what-is-a-tuple/)
    - [Graphs](https://www.luisllamas.es/en/what-is-a-graph/)
    - [Trees](https://www.luisllamas.es/en/what-is-a-tree/)

13. Asynchrony
    - [Asynchronous programming (we'll see it in Lecture 6)](https://www.luisllamas.es/en/programming-asynchrony-concurrency/)
    - [Concurrency and Paralellism (we'll see it in Lecture 6)](https://www.luisllamas.es/en/asynchrony-concurrency-parallelism/)
  
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

## 4. Additional ESP32 Material