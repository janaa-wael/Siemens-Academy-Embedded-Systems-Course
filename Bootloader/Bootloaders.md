# Bootloaders

- Memories:

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