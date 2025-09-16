# Software Development Lifecycle

![image-20250915164341436](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915164341436.png)

![image-20250915164753198](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915164753198.png)

The SDLC is a framework that defines the steps, or phases, used to transform an idea into a software product. This visual emphasizes a flexible, cyclical approach rather than a rigid, one-way path.

#### Core Concept: Iterative & Incremental Development

The arrows forming a circle and the label "Iterative & Incremental" are the most important parts of this diagram. This means the software is built and improved in **repeated cycles (iterations)**. Each cycle produces a **new, usable version (increment)** of the product that adds more functionality. This is the basis for modern Agile and DevOps methodologies.

#### The Phases of the SDLC (Outer Circle):

The diagram shows these phases connected in a continuous cycle:

1. **INITIAL PLANNING / REQUIREMENTS:**
   - **What it is:** The starting point. This involves gathering and analyzing what the software must do, who will use it, and what resources are needed. Key questions are answered: *What is the problem we are solving? What do the users need?*
   - **Output:** A requirements specification document.
2. **ANALYSIS & DESIGN:**
   - **What it is:** Figuring out *how* the software will meet the requirements. Architects and designers plan the system's structure, UI/UX, databases, and APIs.
   - **Output:** Design documents, architectural diagrams, prototypes, and UI mockups.
3. **PLANNING:**
   - **What it is:** This phase focuses on the project management aspect. Teams create schedules, estimate costs, assign tasks, and plan the iterations. This ensures the project is feasible and sets expectations.
   - **Output:** Project plans, timelines, and budgets.
4. **IMPLEMENTATION (or Development):**
   - **What it is:** This is the actual **coding** phase. Developers write, unit test, and integrate code to build the functionalities defined in the design phase. This is where Version Control (like Git) is crucial.
   - **Output:** The source code and a working software build.
5. **TESTING:**
   - **What it is:** The built software is rigorously tested to find and fix bugs, ensure it meets all requirements, and performs as expected. This includes automated tests, manual testing, and user acceptance testing (UAT).
   - **Output:** Test reports, bug lists, and a stable, validated version of the software.
6. **DEPLOYMENT:**
   - **What it is:** Releasing the finished software to the end-users (e.g., publishing an app to an app store, deploying a website to a live server). This often involves coordination with operations teams.
   - **Output:** The software is live and operational in its intended environment.
7. **EVALUATION (The Feedback Loop):**
   - **What it is:** This is the phase that makes the model "iterative." After deployment, the team and users **evaluate** the software. They gather feedback on what works, what doesn't, and what new features are needed.
   - **Output:** New requirements, ideas for improvements, and bug reports. This feedback flows directly back into the **"REQUIREMENTS"** phase, starting the entire cycle again for the next version or iteration.

-----------------

Requirements Specification:
![image-20250915170708001](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915170708001.png)

![image-20250915174912804](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915174912804.png)

![image-20250915183249222](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915183249222.png)

![image-20250915183305763](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915183305763.png)

![image-20250915183412129](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915183412129.png)

![image-20250915183438927](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915183438927.png)

![image-20250915210545426](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915210545426.png)

----------------------------

![image-20250915231753398](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250915231753398.png)

Context Switching: Architecture
APIs: Core
Scheduling: Core
Interrupts: Core (depend on APIs) & Architecture (depend on hardware and CPU)
Event Handling:

- Alarm & Counter: Core
- Timer: Architecture (if timer is in the processor) or Platform (if timer is an external peripheral)

![image-20250916020658936](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916020658936.png)

![image-20250916024009455](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916024009455.png)

----------------------------------------

![image-20250916132421525](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916132421525.png)

### Part 1: The Danger of Circular Dependencies

The first part of the slide presents a critical warning and a classic problem:

**"Be careful in the file inclusion tree to prevent direct or indirect circular dependencies."**

- **What is a Circular Dependency?**
  It occurs when two or more modules depend on each other, either directly or through a chain of other modules.

  - **Direct:** Module `A` depends on (includes/uses) Module `B`, and Module `B` also depends on Module `A`.

    cpp

    ```
    // A.h
    #include "B.h"
    class A {
        void useB(B* b) { ... }
    };
    
    // B.h
    #include "A.h" // Circular Dependency!
    class B {
        void useA(A* a) { ... }
    };
    ```

    

  - **Indirect:** Module `A` depends on `B`, `B` depends on `C`, and `C` depends on `A`, creating a loop (`A` -> `B` -> `C` -> `A`).

- **Why is it a Problem?**

  1. **Compilation Errors:** It creates a "chicken and egg" problem for the compiler. Which class should it compile first? This often leads to errors about incomplete types.
  2. **Maintainability:** The modules become tightly coupled. Changing one module can force changes in the other, making the code brittle and hard to modify.
  3. **Testability:** Tightly coupled modules cannot be tested in isolation (unit testing). You can't test `A` without also having `B`, and vice versa.
  4. **Reusability:** The modules cannot be reused separately. If you want to use `A` in a new project, you are forced to also bring `B` along.

The diagram `A <-> B` with arrows pointing both ways is the visual representation of this unhealthy, direct circular dependency.

------

### Part 2: The Solution: Using Interfaces (Abstraction)

The second part of the slide shows the **solution** to the circular dependency problem by introducing an interface.

**`IMain` <- `AbstractMain` <- `ConcreteMain`**

**`IMainCallback` <- `Runner`**

Let's break down the components:

1. **`IMain` & `IMainCallback` (The Interfaces):**
   - These are abstract base classes (in C++) or interfaces (in languages like Java/C#). They define a *contract*—a set of pure virtual methods (e.g., `virtual void run() = 0;`) that a class must implement.
   - **Key Point:** Interfaces contain **no implementation details**, only method signatures. This makes them very lightweight and easy to include.
2. **`ConcreteMain` (The Implementation):**
   - This is a concrete class that inherits from `AbstractMain` (which likely implements `IMain`). It provides the actual implementation for the methods defined in the interface.
3. **`Runner` (The Client):**
   - This is a class that needs to use the functionality of `ConcreteMain`. However, instead of depending on `ConcreteMain` directly, it **depends only on the `IMain` and `IMainCallback` interfaces**.

#### How This Solves the Circular Dependency:

The dependency arrows now only go **one way**, breaking the cycle:

- **`Runner`** depends on **`IMain`** and **`IMainCallback`**.
- **`ConcreteMain`** depends on **`AbstractMain`** (and thus `IMain`).
- **There is no reverse dependency.** `ConcreteMain` knows nothing about `Runner`.

This is achieved through a technique called **Dependency Inversion** (the 'D' in SOLID principles), which states:

- *High-level modules should not depend on low-level modules. Both should depend on abstractions.*
- *Abstractions should not depend on details. Details should depend on abstractions.*

In this case:

- **`Runner` (high-level)** doesn't depend on `ConcreteMain` (low-level detail), both depend on `IMain` (abstraction).
- **`ConcreteMain` (detail)** depends on `IMain` (abstraction).

### Practical Example:

The `Runner` can call methods defined by the `IMain` interface. At runtime, we *inject* an instance of `ConcreteMain` (which is an `IMain`) into the `Runner`. The `Runner` can use the functionality without ever knowing the concrete implementation details.

This makes the system:

- **Decoupled:** `Runner` and `ConcreteMain` can be developed and changed independently.
- **Testable:** You can test `Runner` by injecting a *mock* or *fake* object that implements `IMain`.
- **Flexible:** You can easily swap out `ConcreteMain` for a different implementation (e.g., `TestMain`, `DifferentOSMain`) without changing the `Runner` code.

![image-20250916133600497](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916133600497.png)

![image-20250916134927401](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916134927401.png)