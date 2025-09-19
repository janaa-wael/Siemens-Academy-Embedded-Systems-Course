# CAN Protocol

### **The Controller Area Network (CAN) Protocol: A Comprehensive Guide**

The Controller Area Network (CAN) is a robust vehicle bus standard designed to allow microcontrollers and devices to communicate with each other's applications without a host computer. Originally developed by Bosch in the 1980s for the automotive industry, its reliability, simplicity, and cost-effectiveness have made it a de facto standard in various industries, including industrial automation, medical equipment, and maritime electronics.

#### **1. The Problem CAN Solves: The Wiring Harness Nightmare**

Before CAN, complex systems like a car relied on point-to-point wiring.

- **Before CAN:** Each electronic control unit (ECU)—like the engine control, anti-lock brakes, lighting, and air conditioning—required its own dedicated set of wires to communicate with other units. This resulted in **huge, heavy, expensive, and unreliable wiring harnesses** that were difficult to install and maintain.
- **After CAN:** CAN replaces this complex wiring with a simple, **two-wire bus**. Every ECU (or "node") connects to this common bus, drastically reducing the number of wires, weight, cost, and potential points of failure.

#### **2. Key Features of CAN**

CAN possesses several defining characteristics that make it ideal for critical, real-time systems:

- **Serial & Event-Triggered:** Data is sent **one bit at a time** over the two-wire bus. It is **event-triggered**, meaning messages are transmitted to signal the occurrence of a significant event (e.g., a button press, a sensor reading), rather than being sent at fixed time intervals.
- **Differential Signaling:** The two wires are called CAN_H and CAN_L. Data is transmitted as a **differential voltage** between these two lines. This design offers **high immunity to electrical interference** because noise affects both wires equally and is effectively canceled out at the receiver.
- **Broadcast Communication:** Every message sent on the bus is received by **every node**. It is up to each node to decide, based on the message identifier, whether the message is "interesting" and should be processed or ignored.
- **Prioritized, Collision-Resistant Communication:** CAN uses a method called **CSMA/CA-AMP**:
  - **Carrier Sense Multiple Access (CSMA):** A node listens to the bus and only starts transmitting if the bus is idle.
  - **Collision Avoidance by Arbitration on Message Priority (CA-AMP):** If two nodes start transmitting simultaneously, a non-destructive **bit-wise arbitration** process decides which message wins. The message with the **higher priority (lower numerical ID value)** continues uninterrupted, while the lower-priority message stops and retries later. **No data or time is lost** during arbitration.

#### **3. Message Prioritization and Arbitration**

- **Priority:** Every message has a unique identifier. The **lower the identifier number, the higher its priority** (e.g., a message with ID `0x070` has higher priority than `0x080`). This ensures critical messages (e.g., airbag deployment) always get through before less critical ones (e.g., window movement).
- **Arbitration:** During the arbitration field of a message, all transmitting nodes simultaneously send their ID and listen to the bus. A dominant bit (0) overwrites a recessive bit (1) on the bus. If a node transmits a recessive bit but reads a dominant bit, it immediately loses arbitration and becomes a receiver. The winner of the arbitration proceeds to send the rest of its frame.

#### **4. CAN Frame Structure**

A CAN message is called a "frame." There are two main formats:

**A. Standard Frame (CAN 2.0A)**
Uses an 11-bit identifier, allowing for 2,048 different message IDs.

| Field                 | Length    | Description                                                  |
| :-------------------- | :-------- | :----------------------------------------------------------- |
| **SOF**               | 1 bit     | Start of Frame. A dominant bit that synchronizes all nodes.  |
| **Arbitration Field** | 12 bits   | Contains the 11-bit **Identifier** (message priority) and the 1-bit **RTR** (Remote Transmission Request). |
| **Control Field**     | 6 bits    | Contains the **IDE** bit (Identifier Extension, dominant for standard frames), a reserved bit, and the 4-bit **DLC** (Data Length Code, 0-8 bytes). |
| **Data Field**        | 0-8 Bytes | The actual payload data to be transmitted.                   |
| **CRC Field**         | 16 bits   | Contains a 15-bit **Cyclic Redundancy Check** value for error detection and a recessive CRC Delimiter bit. |
| **ACK Field**         | 2 bits    | Acknowledgement Slot. Transmitters send recessive; any receiver that gets the message correctly overwrites it with a dominant bit. Followed by a recessive ACK Delimiter. |
| **EOF**               | 7 bits    | End of Frame. Seven recessive bits that mark the end of the message and disable bit-stuffing. |

**B. Extended Frame (CAN 2.0B)**
Uses a 29-bit identifier for a vastly larger address space. Its structure is modified to ensure **backward compatibility** with standard frames. Key differences:

- The Arbitration Field includes an **SRR** (Substitute Remote Request) bit and an **IDE** bit, both set to recessive. This ensures that if a Standard Frame and an Extended Frame with the same base 11-bit ID arbitrate, the Standard Frame will always win.
- It adds 18 additional ID bits and an extra reserved bit (R1).

#### **5. Types of Frames**

There are four frame types in the CAN protocol:

1. **Data Frame:** The most common frame, used to transmit data. The RTR bit is **dominant**.
2. **Remote Frame:** Used by a node to **request data** from another node. It has the same structure as a Data Frame but **no Data Field** and its RTR bit is **recessive**. The corresponding Data Frame that answers the request must have the same identifier.
3. **Error Frame:** A special frame used to **signal that an error has been detected**. It consists of an Error Flag (6 dominant or recessive bits, depending on the node's error state) and an Error Delimiter (8 recessive bits). This forces the original transmitter to retransmit the corrupted message.
4. **Overload Frame:** Sent by a node that is **too busy to process messages**. It is used to inject a delay between Data/Remote frames. It is structured similarly to an Error Frame.

**Inter-frame Space (IFS):** A period of 3 recessive bits that separates Data/Remote frames, allowing nodes time to process the received message before the next one begins. Error and Overload frames are not separated by IFS.

#### **6. Robust Error Detection and Handling**

CAN is renowned for its robust error-handling mechanisms, which include:

- **Bit Monitoring:** A transmitter constantly compares the bit it is sending with the bit it sees on the bus. If there is a **mismatch** (unless during arbitration), it interprets this as an error and initiates retransmission.
- **Bit Stuffing:** To ensure synchronization, the protocol requires a bit edge transition at least every five bits. After **five consecutive bits of the same polarity**, the transmitter **inserts a complementary (stuff) bit** into the bit stream. Receivers destuff this bit. If a node detects **six consecutive bits of the same polarity** between the SOF and the CRC Delimiter, it signals a **Bit Stuffing Error**.
- **Cyclic Redundancy Check (CRC):** A 15-bit checksum is calculated and sent by the transmitter. Receivers recalculate the CRC. If their calculation doesn't match the received value, a **CRC Error** is signaled.
- **Acknowledgement Check (ACK):** The transmitter sends a recessive bit in the ACK slot. If no receiver acknowledges the message by overwriting this bit to dominant, the transmitter detects an **ACK Error**.
- **Automatic Retransmission:** When an error is detected and signaled via an Error Frame, the original transmitter **automatically retransmits the message** as soon as the bus is idle again.

![image-20250918214222419](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918214222419.png)

![image-20250918214238117](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918214238117.png)

![image-20250918214417650](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918214417650.png)

![image-20250918225413440](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918225413440.png)

![image-20250918233218574](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918233218574.png)

![image-20250918235137598](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918235137598.png)

![image-20250919000347253](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919000347253.png)

![image-20250919001425134](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919001425134.png)

![image-20250919141900026](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919141900026.png)

![image-20250919141914395](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919141914395.png)

![image-20250919141833885](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919141833885.png)

![image-20250919141941417](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919141941417.png)

![image-20250919142223251](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919142223251.png)

![image-20250919143111287](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919143111287.png)

![image-20250919143247452](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919143247452.png)

![image-20250919144412090](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919144412090.png)

![image-20250919144816704](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919144816704.png)

![image-20250919144845961](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919144845961.png) 

![image-20250919145431649](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919145431649.png)

![image-20250919145549275](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919145549275.png)

![image-20250919150142311](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919150142311.png)

![image-20250919150241054](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919150241054.png)

![image-20250919151053229](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919151053229.png)

![image-20250919151732991](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919151732991.png)

![image-20250919151745986](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919151745986.png)

![image-20250919151847135](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919151847135.png)

![image-20250919154959678](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919154959678.png)

![image-20250919161600076](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919161600076.png)

![image-20250919161835241](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919161835241.png)

![image-20250919163100688](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919163100688.png)

![image-20250919163850496](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919163850496.png)

![image-20250919163835363](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250919163835363.png)