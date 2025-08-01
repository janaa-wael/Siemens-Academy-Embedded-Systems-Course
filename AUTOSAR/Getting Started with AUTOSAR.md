# Getting Started with AUTOSAR

![image-20250801101817221](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801101817221.png)

- short for AUTomotive Open System ARchitecture

- It's a worldwide development partnership for car manufacturers, suppliers & other companies from the electronics, semiconductor and software industry.

  ![image-20250801102008424](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801102008424.png)

- Luxury: can reach more than 100 ECUs.

- Ordinary Cars: around 40 ECUs.

- SW standardized to reuse it.

- AUTOSAR Consortium: group of companies that maintain AUTOSAR standard.

  ![image-20250801102557354](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801102557354.png)

- OEM: original equipment manufacturer (the person who manufactures the product)

  e.g: Honda, Volvo, BMW

- Tier 1: has OEMs customers, develops application on the ECU & sells it to the OEM. (e.g.: ECU responsible for air bags)

  e.g.: Bosch, Valeo, Denso, ETAS, Magna

- Tier 2: develop the AUTOSAR BSW, develop the AUTOSAR modules based on AUTOSAR standard. There're another companies like semiconductors companies (Texas Instruments, ST). Also, Tools providers like Mathworks are tier 2.

  - AUTOSAR BSW Implementation

    (Vector, Siemens, Elektrobit)

  - Tools & Services

  - Semi-Conductors

- Why AUTOSAR?

  ![image-20250801103759953](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801103759953.png)

  1- Growing E/E (Electrical/Electronics) Complexity
  2- Reusabililty & Exchangeability between different partners.
  3- Standardization

![image-20250801104317604](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801104317604.png)

​	*New features are add every year

​	*We need to reuse them.

​	*So, Complexity increases.

- Standardization: 

  ![image-20250801104949324](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801104949324.png)

  - AUTOSAR consists of many smaller modules.
  - Where different interfaces between different layers are standardized so that we can integrate them together easily.
  - Workflow is also standardized (each company has a certain & constant responsibility)
  - Standardized Exchange Format: **A**utosa**R** **XML** (ARXML) 
  - Standardized: Interfaces, Workflow, Exchange Format

- AUTOSAR-Layered Architecture:

  ![image-20250801111317363](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801111317363.png)

  - Application Layer: contains the application software components.

  - Runtime Environment (RTE): 

    - provides interface between different SWCs
    - provides interface between RTE & BSW.

  - MCAL:

    ![image-20250801112239758](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801112239758.png)

    - Lowest layer of the AUTOSAR architecture.
    - Includes drivers with direct access to hardware.
      - Communication drivers
      - I/O drivers (ADC, PWM, DIO)
      - Memory drivers 
      - Microcontroller drivers
    - Microcontroller dependent
    - Siemens doesn't develop it
    - provides drivers and not services.

- BSW is divided into: 

  - Services Layer
  - ECU Abstraction Layer
  - MCAL

- ECU Abstraction Layer

  ![image-20250801113235278](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801113235278.png)

  - Interface to the drivers of Microcontroller Abstraction Layer
  - API to access peripherals & devices.
  - It abstracts the upper layers from the ECU hardware layout.

- Services Layer

  ![image-20250801114530642](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801114530642.png)

  - Highest layer, provides services for the application 
    - Operating System Functionality
    - Network Communication & Management
    - Memory Services
    - Diagnostic Services
    - ECU State Management
    - Error detection & handling services.

- Complex Device Drivers

  ![image-20250801115723028](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801115723028.png)

  - Layer between RTE & Microcontroller
  - Vertical layer because it implements microcontroller-dependent modules or drivers.
  - Complex Device Driver is a module implementing
    - non-standardized functionality
    - example: ISOBus

  ![image-20250801140957575](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801140957575.png)

- APIs are mainly static & they depend on the user configurations.

![image-20250801141943446](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801141943446.png)

- Module: component in any of the AUTOSAR Layers.
-  Each module has part of the code that is dynamic & static.
- If SWC1 & 2 are on the same ECU & need to communicate, they communicate through RTE.
- RTE is the only module that contains dynamic code only. It doesn't contain static code.
- Flash Driver: has APIs like Fls_Write(ID, Data);
  we configure blocks in it, RTE calls it in RTE_WriteBlock if needed.

![image-20250801145254849](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801145254849.png)

- Application Layer:

  - The AUTOSAR Application layer is the highest layer within AUTOSAR layered software architecture.
  - It consists of various set of interconnected SWCs
  - A SWC is the simplest form of an application that fulfills certain functionality.

- Libraries:

  ![image-20250801145441353](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801145441353.png)

  - Libraries are a collection of functions for related purposes.
  - They can be called by BSW modules (that including the RTE), SW-Cs, libraries or integration code.
  - Run in context of the caller.
  - Example: CRC Library

- Benefits of AUTOSAR:

  - Development can be decoupled (through abstraction) by horizontal layers, reducing development time and costs.
  - Harware & software - widely independent of each other
  - Reuse of software enhances quality & efficiency

  ![image-20250801150216225](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801150216225.png)

- RTE is the middleware software layer as all SWCs communicate with it if they need anything.

  ![image-20250801152249001](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801152249001.png)

- BSW Layer Overview

![image-20250801153651347](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801153651347.png)

- PduR: Protocol Data Unit Router
- CAN by default supports PDUs up to 8 bytes.
- CanTp: CAN transport protocol, does segmentation of PDUs & is responsible for the reassembly of the PDUs.
- SWC talks through standardized API to RTE.
- RTE translates this to signal and forwards it to COM.
- COM sends PDU to PduR. It has a routing table and sends the PDU to CanTp which is responsible for segmentation and assembles the PDUs into PDUs with maximum size of 8 bytes, then sends them to PduR
- PduR sends them to CanIf

AUTOSAR Workflow:
![image-20250801154534392](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250801154534392.png)

- In some cases, OEMs communicate directly with Tier 2 companies & not implement the application layer by themselves.
- Tier 1: develops the application layer and the ECU.
- OEM companies supply Tier 1 with the ECU extract.
- Engineers in 
  - Tier 1: application developper
  - OEM: network architecture design, integration
  - Tier 2: AUTOSAR stack developer & maintains them.
  - Services: helps OEM in developing the application (source out), or in integration