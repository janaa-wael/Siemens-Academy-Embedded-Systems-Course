![image-20250726110153970](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726110153970.png)

![image-20250726102357378](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726102357378.png)

- Flash APIs must execute from RAM.

- Flash APIs are copied to the RAM before any flash operation.

- Bootloader Code must execute from the RAM.

- Bootloader code is copied to the RAM during startup.

- Compiler has #pragma 

  ![image-20250726102708698](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726102708698.png)

![image-20250726103501320](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726103501320.png)

- Part of the binary of Bootloader code is found in the flash and the other is in the RAM.

- We do this using linker script.

- If MCU is powered off, the RAM contents are erased.

  ![image-20250726103728587](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726103728587.png)

- This offset allows us to copy this section of BL code from flash to RAM every time.
-  We can execute from a bank and erase/write from another bank at the same, but can't do that if both operations occur from the same bank.
- In startup, we copy the flash driver code that's bounded within the addresses : (0x80003000 to 0x80004000) to the region (0x60000000 to 0x60001000)
- Flash bank: 32 Kb (e.g.: 16 sector), bootloader takes (e.g.: 4 Kb)

![image-20250726110655985](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726110655985.png)

- The purpose of BL is constant, but it contains many different designs.

- Exception occurs when we attempt to erase and execute from the same flash bank at the same time. 

  > Solution: Copy the Flash Driver APIs from Flash to RAM, but during linking, in the linker script we resolve the addresses of the APIs of the flash,

- SW Reset: we use it to

- Search about LMA, DMA

- Not all compilers support copying data from section to section.