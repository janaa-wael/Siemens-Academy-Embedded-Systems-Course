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

------------------------------------

![image-20250916134927401](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916134927401.png)

**How the Solution Works:**

The key is in `fileB.h`. It uses a **forward declaration** instead of including `fileA.h`.

- **Line 6 (Old):** `#include "fileA.h"` // This caused the problem
- **Line 6 (New):** `typedef struct AType AType;` // This is the forward declaration

**What is a Forward Declaration?**
It's a promise to the compiler. It says: *"There is a struct called `AType` that will be defined somewhere else. For now, just accept that the name `AType` is a valid type."*

**Why does this work?**
Because `fileB.h` only uses a **pointer** to `AType` (`AType* a;`). The compiler doesn't need to know the full definition of `AType` (like its size or what members it has) to work with a pointer to it. It just needs to know that the type exists.

**The Fixed Workflow:**

1. **`fileA.h`** includes `fileB.h` (as before) to get the full definition of `BType` for the member `BType b;`.
2. **`fileB.h`** does NOT include `fileA.h`. Instead, it forward declares `AType`. This breaks the circular include loop.
3. When the compiler processes `fileB.h`, it sees `AType* a;` and knows that `AType*` is a pointer to a struct. This is perfectly valid with just the forward declaration.
4. Later, when `fileA.h` is compiled, the full definition of `AType` is provided, satisfying the earlier promise.

-------------------------------------------------------



![image-20250916143552189](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916143552189.png)

#### 1. High-Level Logical Concepts (The "What")

These are abstract ways to group and think about functionality. They are independent of programming language.

- **Module:**
  - **What it is:** The largest unit of organization. A module is a collection of related code that performs a **major, distinct function** within the application.
  - **Analogy:** In a car, modules would be the **Engine**, the **Transmission**, the **Braking System**.
  - **Example:** In a web app, you might have an `AuthenticationModule`, a `PaymentModule`, and a `ReportingModule`.
- **Component:**
  - **What it is:** A smaller, reusable building block *within a module*. A component is a self-contained unit that encapsulates a specific piece of behavior or UI and has a well-defined interface.
  - **Analogy:** Within the Braking System module, components would be the **Brake Caliper**, the **Master Cylinder**, and the **ABS Sensor**.
  - **Example:** In a UI framework like React, a `Button`, a `ModalDialog`, or a `NavBar` are all components. In backend code, a `DatabaseConnector` or `Logger` could be a component.
- **Feature:**
  - **What it is:** This organizes code around a **user-facing capability** or a business requirement. A feature often cuts across multiple modules and components to deliver a complete piece of value to the user.
  - **Analogy:** The feature "Cruise Control" uses components from the Engine module (throttle control), the Braking module (to disengage), and the UI module (buttons on the steering wheel).
  - **Example:** A "User Profile" feature would involve the `AuthenticationModule` (for login), a `DatabaseModule` (to fetch user data), and several UI `Components` (forms, avatars, buttons).

#### 2. Low-Level Physical Organization (The "How")

This is how the logical concepts are actually implemented in the project's files and folders.

- **Folder Structure (Directory Layout):**
  - **What it is:** This is the high-level organization of the project's source code on the filesystem. It's the first thing you see when you open the project.
  - **How it maps:** The folder structure is how you choose to represent your **Modules** and **Features**.
  - **Common Patterns:**
    - **By Module:** `/src/AuthenticationModule`, `/src/PaymentModule`
    - **By Feature:** `/src/user-profile`, `/src/checkout-cart`
    - **By Layer:** `/src/models`, `/src/views`, `/src/controllers` (MVC pattern)
  - **Purpose:** A good folder structure makes the codebase **navigable and intuitive**. You should be able to guess where to find code for a specific functionality.
- **File Structure:**
  - **What it is:** This refers to the organization of code **within a single file**. It includes things like:
    - The order of imports/includes.
    - The placement of classes, functions, and constants.
    - The use of comments and documentation.
    - Adhering to a consistent style guide (e.g., naming conventions: `PascalCase` for classes, `camelCase` for variables).
  - **Purpose:** A consistent file structure makes individual files **readable and maintainable**. It allows any developer on the team to quickly understand a file's content

----------------------------------

Coding & Development Practices:
![image-20250916143847634](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916143847634.png)

![image-20250916162224772](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916162224772.png)

#### 1. Adherence to Standards: AUTOSAR

- **`Write your src code according to the AUTOSAR...`**
  - **What it means:** This is a non-negotiable requirement. AUTOSAR (AUTomotive Open System ARchitecture) is a global standard that defines how software for Electronic Control Units (ECUs) in cars is designed, written, and integrated.
  - **The Documents:**
    - **`AUTOSAR_SWS_BSWGeneral.pdf`** (Software Specification): This document defines the *how*. It's the detailed technical specification for implementing the Basic Software (BSW) modules. It specifies function names, parameters, behavior, and APIs. **Developers code against this document.**
    - **`AUTOSAR_SRS_BSWGeneral.pdf`** (System Requirements Specification): This document defines the *what*. It states the high-level requirements that the software must fulfill. **Testers validate against this document.**
  - **Why it's important:** Following the standard ensures that software from different teams and different companies will work together correctly. It ensures reliability, safety, and interoperability in a complex supply chain.

#### 2. Naming Conventions: Consistency is Key

- **`Define the naming convention`**
  - **What it means:** A strict naming convention is enforced for every element in the code. This is not a suggestion; it's a rule.
  - **The Pattern:** The pattern `[Module]_[Component][Name]_[Suffix]` is prescribed.
    - **`Os_` Prefix:** "Os" stands for Operating System. This indicates that these examples are for the OS module. Other modules would have their own prefix (e.g., `Com_` for Communication, `EcuM_` for ECU Management).
    - **`<ComponentName>`:** Specifies the sub-module or component within the OS (e.g., `Os_Task_` for task-related functions, `Os_Resource_` for resource management).
    - **Casing:** Functions and variables use `CamelCase`, Macros use `UPPER_CASE`, and Types use a `_Type` suffix.
  - **Why it's important:**
    - **Readability:** Just by looking at a name, you know what module it belongs to and what kind of element it is (function, macro, type).
    - **Avoids Conflicts:** Prevents name clashes in a large codebase with many contributors.
    - **Tooling:** Makes it easier to write scripts and tools that automatically analyze the code.

#### 3. Automated Documentation: Doxygen

- **`Write the API specification and extract it using... Doxygen`**

  - **What it means:** Developers don't just write code; they write **API documentation directly in the code** as special comments. A tool called **Doxygen** then scans the source code and automatically generates professional documentation (e.g., in HTML or PDF format) from those comments.

  - **How it works:** Developers use special comment tags like `@brief`, `@param`, `@return`.

    c

    ```
    /**
    * @brief Starts a specific operating system task.
    * @param[in] TaskId The unique identifier of the task to start.
    * @return Os_StatusType Returns OS_OK if successful, OS_ERROR otherwise.
    */
    Os_StatusType Os_TaskStart(Os_TaskType TaskId);
    ```

    

  - **Why it's important:**

    - **The documentation is always in sync with the code** because it lives right next to it.
    - It saves immense time and effort compared to manually writing and maintaining separate documents.
    - It provides a single source of truth for how to use the API.

#### 4. Build Automation: Make

- **`make is a build automation tool...`**
  - **What it means:** The `make` tool reads a configuration file (usually called `Makefile`) that defines the rules for compiling source files, linking object files, and producing the final executable. It automatically figures out what needs to be recompiled based on what files have changed, which is essential for large projects.
  - **Why it's important:**
    - **Automation:** Eliminates the error-prone process of manually typing long compilation commands.
    - **Efficiency:** Only rebuilds what is necessary, saving a huge amount of time.
    - **Reproducibility:** Ensures that every developer builds the software in exactly the same way.

---------------------------------------------

![image-20250916164632136](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250916164632136.png)