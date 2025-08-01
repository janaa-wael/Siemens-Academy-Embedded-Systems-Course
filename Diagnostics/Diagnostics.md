# Diagnostics

![image-20250726112722446](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726112722446.png)

- UDS: is a communication protocol used in automotive ECUs to enable diagnostics. firmware updates, routine testing and more.

- The UDS protocol (ISO 14229) is standardized across both manufacturers and standards (such as CAN, KWP 2000, Ethernet, LIN)

- In practice, UDS communication is performed in a client-server relationship - with the client bein a tester-tool and the server being a vehicle ECU. For example, you can conenct a CAN bus interface to the OBD2 conenctor of a car and UDS requests into the vehicle. Aassuming the targeted ECU supports UDS services, it'll respond accordingly.

- In turn, this enables various use cases:

  - Read/Clear diagnostic trouble codes (DTC) for troubleshooting vehicle issues.
  - Extract parameter data values such as temperatures, VIN, etc.
  - Modify ECU behavior via software update.

- UDS Message Structure:

  ![image-20250726113213901](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726113213901.png)

  - UDS is a request-based protocol. Its frame consists of:

    - CAN ID
    - Protocol Control Information (PCI)
    - Service Identifier (SID)
    - Sub Function Byte
    - Request Data Parameters
    - Padding

  - PCI & CAN ID: are CAN-related, won't be found if we're using another protocol other than CAN.

  - PCI: tells us whether the message fits in one frame or not, to know whether we need segmentation or not.

  - Normal CAN is 8 bytes.

  - If we want to send a msg more than 8 bytes,  it won't fit in a single framd and we'll need to segment the message

  - UDS Service ID (SID)

    -  defined in ISO 14229

    - Each service has its own ID and depending on it the the vehicle ECU knows what's required from it.

    - If the response is positive, the response will be the SID+0x40

      e.g.: if SID = 0x22, positive response: 0x62

  - UDS Sub-Function Byte:

    - The sub-function byte is used in some UDS request. However, that in some UDS services, like in service 0x22 (Read Data by Identifier), the sub function byte is not used.
    - The higher nibble shows if the response should be suppressed or not and the lower nibbles contains the service subfunction.

  - UDS Request Data Paremeters:

    - Various types of the request data parameters are used to provide further configuration of a request beyong the SID and optional sub function byte.

      e.g.: service 0x22 is read data by identifier

      ![image-20250726114047662](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726114047662.png)

- UDS is a group of standard services that can be sent on communication protocols. Identifies message communication.

- UDS Services used by the BL:

  ![image-20250726114216843](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726114216843.png)

- TesterPresent: periodic message sent by tester to notify the vehicle ECU that it's still present.

- SecurityAccess: tester asks the ecu for security grant to access some secured parts or services in the vehicle.

- ReadDataByIdentifier: to check whether the vehicle's SW needs update or not.

- UDS has around 29 services

- Those are the services BL is interested in.

- We don't have access to ISO 14229 as it is not free and needs license.

- UDS Responses:

  ![image-20250726115144247](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726115144247.png) 

  - +ve response: service is successfully handled, the response is SID+ 0x40
  - -ve response: a problem occurred and the service request couldn't be handled
  - PCI: single frame
  - Response SID: negative
  - NRC (Negative Response Code): reason for negative response.

- UDS & CAN bus: Standards & OSI Model

  ![image-20250726122737955](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726122737955.png)

  - CAN serves as a base for communication. Specifically, CAN is described by a data-link layers & physical layer in the OSI model.
  - In contrast to CAN, UDS is a higher layer protocol and utilizes both the session layer and application layer in the OSI model as shown.
  - Multiple standards other than CAN may be used as the basis for UDS communication - including FlexRay, Ethernet and LIN.

- As per OSI Layers:

  ![image-20250726122954473](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726122954473.png)

  - Application: this is described by ISO 14229-1. Further, separate ISO standards describe the UDS application layer for the various lower layer protocols
  - Presentation: this is the vehicle manufacturer specific.
  - Session: this is described in ISO 14229-2
  - Transport + Network
  - Data Link:
  - Physical

- DoCAN

  ![image-20250726123559953](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726123559953.png)

  - ISO 15765-2 was published to solve the challenge of large payloads for CAN based vehicle diagnostics.

  - The standard specifies a transport protocol and network layer services for use in CAN based vehicle networks.

  - The ISO-TP standard outlines how to communicated CAN data payloads up to 4095 bytes through segmentation, flow control and reassembly.

  - No frame holds more than 7 bytes.

  - If data is more than the size of one frame, we do segmentation.

  - We send the first frame with the number of messages.

  - Receiver responds with the FlowControl frame to tell the sender how the communication proceeds.

    | Frame Type            | Abbreviation | Purpose                                      |
    | --------------------- | ------------ | -------------------------------------------- |
    | **Single Frame**      | SF           | For short messages (≤ 7 data bytes)          |
    | **First Frame**       | FF           | Starts a multi-frame message (> 7 bytes)     |
    | **Consecutive Frame** | CF           | Follows the first frame to continue the data |
    | **Flow Control**      | FC           | Sent by receiver to manage flow (wait/send)  |

![image-20250726124204675](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726124204675.png)

- ISO TP Frame Types:

  ![image-20250726124311014](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726124311014.png)

  EACH DATAX is 1 byte/

  - Single Frame (SF)

    ![image-20250726124248226](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726124248226.png)

    - Code (0): represents the protocol control information
    - Size: number of bytes in the frame (0-->7) (not 8 because there's another byte for the PCI)
    - means the message fits one frame.
    - half nibble for size

  - First Frame (FF):

    - code: 1 determines it's the first frame
    - first frame informs the receiver that it needs to segment the data
    - the receiver needs to be informed of the number of bytes to be segmented so that if the receiver's buffer won't be able to accomodate this number, it'll respond with number of block size, ST, flag, etc.
    - Communication supports up to 4k size message.
    - code + size = 1.5 bytes (12 bits)
    - data = 6 bits

- Consecutive Frames:

  ![image-20250726125453254](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726125453254.png)

  - index: index or order of the consecutive frame, when we reach 15, overflow occurs.
  - data frame: 8 bytes

- Flow Control:

  ![image-20250726131648989](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726131648989.png)

  - sent by the receiver to sender

  - code: half nibble

  - flag: (0-2) 

    - 0: continue to send
    - 1: wait  (this means you have a busy buffer for example)
    - 2: abort communication (e.g.: overflow ocurred)

  - block size: 

    - maximum number of bytes (frames) can be received by sender to receiver before waiting for an authorization to continue transmission of the following N_PDUs/

  - Separation Time (ST): 

    - time between each consecutive frame and another.
    - unit: (0-127)ms or (128-255)microsec

    ![image-20250726132414917](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726132414917.png)

- what happens if sender sent the first frame and the buffer of receiver isn't full?

![image-20250726135428650](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726135428650.png)

- Software Download Example:

  ![image-20250726142812682](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726142812682.png)

- Logs of UDS are monitored using CANoe or CAN Analyzer or any spying tool

- ECU Test is any ecu that communicates with the tester tool.

- CAN is a communication protocol while UDS is a message protocol.

- TP constructs the frame and calculates the number of bytes in First Frame.

  ![image-20250726150458709](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726150458709.png)

- Functional Request: request the tester/client wants to send to all ECUs.

- Physical Request: request from tester/client tool sent to a certain ECU.

![image-20250726150857434](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726150857434.png) 

- Programming Session:

  - bootloader executes during the programming session.

- Default Session:

  - application executes during the default session.

- Security Access:

  - steps by tester to grant security access and be able to access the ECU's services.

    ![image-20250726151151749](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726151151749.png)

  - tester sends the seed to the server and the server calculate the key and then the tester sends the key to tester and if it's correct then the server responds that access is granted.
  - Security Access algorithms is OEM-dependent, depends on the requirement of the customer.

- Single-Level vs Two-Level Bootloader

  ![image-20250726152618352](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726152618352.png)

  - Flash: has primary bootloader whose capabilities are limited (DIDs, secure booting, software download in RAM, can't manipulate the flash)
  - Secondary Bootloader:
    - superset of primary bootloader because it contains the flash driver and contains more functionalities thaan the primary bootloader
    - tester tool connects to the secondary bootloader

- Bootloader Updater (BLU): 

  - We need it to modify the bl software whether single-level or 2-level.
  - BLU is on the PC and we built it to produce the binary file.
  - New PBL doesn't relate to the application address, to make it relate to it we need to offset it.

  ![image-20250726160229901](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726160229901.png)

  ![image-20250726160238368](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726160238368.png)

- FOTA (Dual Banking/ Dual Image)

  ![image-20250726162817161](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726162817161.png)

  - Firmware Over The Air
  - Technology allows us to do wireless updates.
  - technique used to provide us with some sort of mitigation action
  - we've 2 memory banks; Bank A & Banl B. Each is independent of the other.
  - When there's a SW update, we have an active partition (has code running) and inactive (has backup of the updated software)
  - We switch between them, Bank B becomes actives and A becomes inactive.
  - We swap between them so that the newer application version run, we don't copy them in sw, swapping occurs in SW.

- Secure Boot:

  ![image-20250726163107882](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726163107882.png)

  - to check the applicaiton confidentiality.

  - Root of Trust: the entity that we trust & verify many things with.

    e.g.: HSM, OTP Memory (because it never changes as it

    s one-time-programmable!)

  - Chain of trust: 

    - HSM verifies the bootloader or boot manager or PBL or application, if qanything in the middle had its verification fail the whole process fails.
    - After verification finishes, application is verified.
    - We need verification to check upon the integrity.
    - HSM: hardware security module that has its own core, sw executes on it using bridge communication to do cryptographic operations on it and after it finishes the control returns back to the host core.
    - Bootloader used HSM.

- Data Encryption & Decryption

  ![image-20250726163316915](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726163316915.png)

- CMAC:
  - Cipher-based Message Authentication Code

- Signature Verification: (Tester Tool, ECU)

![image-20250726163508515](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250726163508515.png)

- Software Download Example:
  - 