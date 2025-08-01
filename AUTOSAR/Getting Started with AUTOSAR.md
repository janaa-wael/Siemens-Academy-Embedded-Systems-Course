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

- 