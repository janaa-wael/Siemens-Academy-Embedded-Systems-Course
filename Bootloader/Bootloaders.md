# Bootloaders

![image-20250725111905599](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725111905599.png)

- Memories:

  ![image-20250725141845756](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725141845756.png)

  ![image-20250725141936237](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725141936237.png)

  - Volatile Memory:

    - Memory whose content is deleted if power is turned off.
    - Example: SRAM, DRAM

  - Non-Volatile Memory:

    - Memory which retains its contents even after power is turned off.
    - Example: PROM, OTP Memory, Flash, EPROM, EEPROM

  - Concept of Read-Only Memories --> Memories that process that write on them.

    i.e.: Processor can't directly write on Flash Memory ---> This is because it's made of Floating-Gate Mosfet Transistors --> they need high power to change their state (whether writing or erasing the memory) and the processor can't produce enough power to write on them. SO, it can't write on the FLASH MEMORY!

  - Processor needs a circuit that generates enough power to use on the Flash, this circuit is called Flash Memory Interface.

  - What if microcontroller doesn't have flash interface?

    > We use external circuit that has a flash interface and connect it to the mcu which communicated with the flash interface to write/erase its contents. This case isn't common because almost all MCUs contain flash interface. This is called **Off-Circuit Programming (OCP)**.

  - What if the MCU contains a flash driver/interface?

    > The MCU communicates with the flash driver directly and orders it to program the flash memory, after which  the processor is switched off. This is called **In-Circuit Programming (ICP)**.

  - Example: 

    MC1 -> Flashed through SPI 
    MC2 -> Flashed through UART
    MC3 -> Flashed through CAN

    This makes a problem arise because different targets need different sockets that support different protocols to be able to flash the source code on it.

    > Solution: We use a **simple piece of code** called ***Bootloader Code*** that updates the Application region code before it runs if there's an update pending.

- If the target doesn't contain a flash driver, then we can't use Bootloader Software Code to upadate the application code!

- When aren't we in need of using bootloader?

  > 1- if the code is too simple to be updated again later on.

- If the Bootloader receives the software code, it sends it to the flash driver to flash it and tells it which sectors it should write these data upon.

- Debugger translates data sent by usb to protocol the flash interface understands.

- We have 2 types of Bootloaders:

  - Primary Bootloader:

    - First code/program executed when the device is powered on.
    - Written by the vendor, not the developers.
    - It does HW initialization, minimal perihperals needed to execute the bootloader code.
    - It's stored in ROM.
    - It's also called System Bootloader.
    - Examples: 
      - Boot/ROM responsible for booting in most MCUs such as STM32
      - BIOS on Personal Computers that is used to load the OS that runs on the PC.

  - Secondary Bootloader:

    - Also known as Custom Bootloader (designed by developer and contains advanced features)

    - Written by the Primary Bootloader & runs after it.

    - It's not necessary to have primary bootloaders in order to the secondary bootloaders to exist!

    - Stored in flash, the addresses it's allocated to are determined by the developer using linker scripts! *(most common case)*

    - Contains more functionalities 

      1- Firmware Validation
      2- Decryption

    - Examples:

      - Placed by user in STM32
      - Android Bootloader (used in mobile devices to load OS and verify its integrity)

  - Bootloader is a stand-alone application that has its own startup code that initializes the HW needed by the bootloader code and then the application of the bootloader is executed (its main function)

  - Bootloader is a gateway for all software updates & the first guard to the ECU & vehicle integrity.
  
  ![image-20250725103137895](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725103137895.png)
  
  - Software Update:
  
    - History:
  
      - In the past,t he focus was on Hw components as the main role player in embedded systems. 
  
        - Each HW shall come with its basic and simple software that does its specific job.
        - Over years, software became more and more complex which leads to continuous enhancements and maintenance procedures for each software part.
        - Software update concept became a critical topic to embedded systems suppliers.
        - This triggered the need to have a robust solution to perform this job.
  
      - Traditional Flashing:
  
        - Normal flashing sequence using debuggers can be categorized into 2 parts:
  
          - In-Circuit Debuggers
          - External Debuggers
          - Binary Burners
  
        - An in-circuit debugger (ICD) is a hw device connected between an opponent (PC) and the target microcontroller test system and is used to debug real-time applications faster and easier. (It's mounted on the MCU)
  
        - External Debugger is a standalone device which has its on-board systems that can be connected directly to the microcontroller's debug port interface (i.e.: JTAG)
  
        - External debuggers are widely used in embedded systems production line such as:
  
          - Lauterbach (one of the strongest and mostly used debuggers)
          - UDE (one of the strongest and mostly used debuggers)
  
        - ICD is only used in development boards.
  
        - A well known example for traditional flashing is the AVR ATmega32 flashing sequency
  
          - ATmega microcontrollers are flashed using ISP (In-system Programming) feature supported by the chip vendor.
  
          - It's connected through ISP/SPI from the microcontroller side and through serial port from the PC side.
  
          - The flashing is based on an external tool.
  
            ![image-20250725103351731](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725103351731.png)
  
        - Software Update Example:
  
          - Arduino Development board can be the simplest example for an easy software update.
          - With a simple connection to PC with UART communication makes it feasible to download all your applications on it.
          - No external hardware is required here like ISP in AVR programming, but  a complete software solution is present inside the microcontroller.
          - This software solution is called Bootloader.
  
    - Automotive World with Bootloader:
  
      - ECUs are flashed using debuggers.
      - Debug ports are enabled during the whole life cycle of the ECU to enable software updates.
      - Service centers environment required to parallelize flashing procedures.
      - Accordingly, a bulk of debuggers shall be present with technicians.
      - An example to use debugger with air-conditioner ECU for SW update:
        - Unpack the vehicle components till reaching the target ECU.
        - Get the target off the vehicle.
        - Connect the debugger into the ECU and start flashing.
  
    - Bootloader Definition:
  
      - Bootloader is a standalone software which all the needed components to build and execute indepent of any other software.
  
      - It's the first piece of code to run on the microcontroller on the startup sequence.
  
      - It includes all the BSWs modules needed such as MCU, PORT, WDG, communication, ...
  
      - It's the responsible software to start the application execution.
  
      - Application software is updated through the bootloader, so it provides the ease of memory update without using the debugger.
  
      - It gives you a universal and compact solution for reprogramming ECUs quickly, efficiently and securely.
  
        ![image-20250725104439498](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725104439498.png)
  
  - Why Bootloader?
  
    > - Bootloader is a software solution that is based on major factors of Business decision.
    >
    > - Original equipment manufacturers (OEMs) observed the urgent need of having a Bootloader for the following main factors:
    >
    >   - Cost
    >
    >     - Avoid additional flashing using debugging/programming protocols like JTAG & ISP.
    >
    >     - Debugging/Programming protocols means that every technician needs to have a debugger or external tool to perform update.
    >
    >     - Debuggers are too expensive to eb affordable for each service center.
    >
    >     - Mitigate the need for high technical knowledge people in the service centers.
    >
    >       ![image-20250725105001079](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725105001079.png)
    >
    >   - Security
    >
    >     - Debugging/Programming protocols shall be avoided in production (after sales)
    >     - It's forbidden to have the debugging port enabled
    >       - Prevent the access to the code binary, data, configurations which are considered confidential information for each OEM
    >       - Prevent unauthorized access to the vehicle using a simple debugger that can lead to an attack to the vehicle's software image.
    >       - Accordingly, unauthorized access to the vehicle using a simple debugger that can lead to an attack to the vehicle's software image.
    >
    >   - Accessibility
    >
    >     - Each ECU on the vehicle shall be accessed easily.
    >     - It's not logical to have each part of the vehicle off to reach a specific component that's need to update its software image.

- Without a debugger, we can't use a bootloader.  

- Vehicle Network Topology (Edge Node, Internal Node, Opponent)

  - Vehicle Network Topology

    ![image-20250725114427885](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725114427885.png)

    - Each vehicle architecture includes a network topology that describes the whole connections between ECUs.

    - To describe the network topology, 3 main components shall be defined as follows:

      - Edge Node (Gateway Master)

        - An ECU that communicates with the external hardware connection using diagnostic tools.
        - OBD is connected to the gateway master.
        - Takes all the responsibility

        ![image-20250725113242539](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725113242539.png)

        - ECU A is the edge node and supports the addresses of all nodes in the network.
        - ECU B's supports their own addresses only.
        - ECU B3 supports its own address and that of C's
        - All the nodes except the ECU A & B3 are internal nodes.
        - ECU B3 is a middle layer node.
        - Edge nodes are seen because they're connected to the OBD while the internal nodes aren't visible.
        - B2, B1, C1, C2 are target ECUs.
        - Diagnostic tool has an address.
        - CAN has a HW filtering by default.
        - 

      - Internal Node

        - are target nodes that aren't connected to another sub-layer.

          ![image-20250725114237813](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725114237813.png)

      - Opponent (Tester Tool)
        (زي جهاز كشف الاعطال) 

        - An external device that is implemented to communicate with the vehicle through an external interface.

          ![image-20250725114258341](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725114258341.png)

        - This tool is standardized per each OEM to support all the sequency and SWDL mechanism

    - OBD is short for On-board Diagnostics.

- Domain Architecture: 
  - each ecu has a specific functionality e.g.: infotainment, engine control, connectivity, drivetrain, ADAS, body & comfort braking, etc.
  - Each domain has its own dedicated ECUs and its specific tasks (under the same umbrellas e.g.: powertrain, chassis, ABS, Steering, Infotainment, telematics, autonomous driving (LiDar, Radar), ).
    ![image-20250725120350397](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725120350397.png)
- Zonal Architecture: 
  - trendy and is recent, ecu components depends on the components in each zone, not related in functionality. It's better because it saves wiring and cost and power consumption, also ecus are more powerful.
  - group ecus based on its physical location.
  - Cables are shortest and sensors are connected to the nearest ECUs.
- Hyper-Architectures: some of the OEMs use a mixed architecture of Domain Architecture and Centralized & Zonal Architecture.

![image-20250725115814568](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725115814568.png)

- A **boot manager** is a piece of software responsible for **deciding which software image or operating system to load and run** after system power-up or reset — especially when **multiple boot options** exist.

- We can't write in an unerased unit in the flash memory (or any device that's flash-based).

![image-20250725142520282](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725142520282.png)

- Flash Cell:

  - erased state: 1
  - unerased state: 0
  - you can read more about NAND and NOR Flash Cells to understand why.

- Flash is divided into a group of banks (consists of a certain number of sectors that depends on the manufacturer)

- Flash Sector consists of a group of words.

- Flash Word consists of a group of byted.

- Flash Byte consists of a group of 8 bits.

- Changin the contents of a flash memory requires speific operations:

  - Flash Erase:

    - occurs on sector level, a sector is the smallest erasable unit for the flash (Sector size differs from flash to another)
    - Erased state is considered to be value 1b;
    - Changing a value from 0b to 1b is called erasing memory.

  - Flash Write:

    - occurs on page level, a page iss the smallest writable unit for the flash. (Page size differs from flash to another, can occur on bit level "EEPROM")
    - Programmed state is considered to be value 0b.
    - Changing a value from 1b to 0b is called programming the memory.
    - Special Case when the data inside a sector are 0s is considered.

  - Flash id erased by **sector** and programmed by **page**.

    ![image-20250725143910421](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725143910421.png)
    ![image-20250725144158362](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725144158362.png)

- Page size is manufacturer-dependent. In this example, page size is 1 byte.

- Search about ***Bus Stalling***

- ACC (Access) Exception occurs when we attempt to read from an erased flash memory.

- Memory Map
  ![image-20250725152501901](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725152501901.png)

  - The code region contains the final output of the program (.hex, .bin, etc.)

  - SRAM will contain the stack, heap, global variables and the static variables, etc.

    ![image-20250725152726178](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725152726178.png)

    - 1- Copy the Stack Pointer to MSP from the location 0x000000000. So, the value will be the starting of the stack.
    - 20 Loads the PC from address 0x4 to move the reset handler.
    - The reset handler will perform the below operations:
      - Initialize the hardware system, then copy the initialized data to SRAM
      - Then copy the uninitialized data to SRAM and initialize them with 0
      - Finally, it calls main function.

  - ![image-20250725153634177](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725153634177.png)

- How does the BL know that the application is valid?
  - Check whether there's an application is written or not.
  - Apply security & authenticity techniques
- First entry in the vector table is the starting value of the Stack Pointer.

![image-20250725154559415](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725154559415.png)

- Contents: *Bootloader Behavior, System Components, Bootloader Requirements, Application Requirements*
- ![image-20250725160525914](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725160525914.png)
- Bootloader Behaviour:
  - Self Conained Bootloader (SD Card or USB Flash can be used)
    - Manual: by holding a certain push buttonn for example for a specific period of time.
    - Automated: automatically detects the new firmware and manages its update process.
    - No communication interface is required.
  - Instructed Bootloader:
    - Awaits for instructions from outside sours (Tester)
    - Firmware update is based on receiving a specific packet.
    - Communication interface is required.

![image-20250725160607690](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725160607690.png)

![image-20250725160621801](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725160621801.png)

- Flag is stored in RAM, to reduce the minimum number of erases needed and to be able to rewrite 

- What is Software Reset? 

  > type of reset doesn't disconnect power source so the RAM data isn't deleted but the peripherals need to be initalized again

![image-20250725161328730](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725161328730.png)

- Boot Manager = Preloader = Branching Code 

- Its design is dependent on the customer requirements.

- Bootloader Requirements
  ![image-20250725161736093](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725161736093.png)

  - Initialize needed peripherals
  - Select the operating mode (App or BL)
  - Communication interface
  - Parsing supported extensions
  - Flash interfacing

  Extra Features should be supported if needed:

  - Application integrity , can be supported using any cryptographic algorithms (CMAC, Checksum, CRC, etc.)
  - Bootloader Updater (Erase, Write, Read)

![image-20250725162032153](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725162032153.png)

![image-20250725162042521](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250725162042521.png)

- Backdoor: Concept that allows me to enter the bootloader without executing the application code.
- When you change the configurations of JTAG pins, you won't be able to flash your code. Texas Instruments has a document that shows how to recover the Tiva C.