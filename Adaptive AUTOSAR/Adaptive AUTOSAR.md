# Adaptive AUTOSAR

![image-20250918175556211](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918175556211.png)

![image-20250918175534316](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250918175534316.png)

Of course. Here is a detailed article on Adaptive AUTOSAR and its key differences from Classic AUTOSAR, based on the provided slide content.

---

### **Navigating the Evolution of Automotive Software: Classic AUTOSAR vs. Adaptive AUTOSAR**

The automotive industry is in the midst of a profound transformation, shifting from hardware-defined vehicles to software-defined platforms. At the heart of this revolution is the need for powerful, flexible, and updatable software architectures. The AUTOSAR (AUTomotive Open System ARchitecture) partnership, a global development partnership of automotive OEMs and suppliers, provides the standards to make this possible. However, as vehicle needs have diversified, AUTOSAR has evolved into two distinct but complementary standards: **Classic Platform (CP)** and **Adaptive Platform (AP)**.

This article breaks down the key differences between these two platforms, explaining why both are critical for the next generation of vehicles.

#### **The Original Foundation: Classic AUTOSAR (CP)**

Classic AUTOSAR was developed to address the needs of deeply embedded, safety-critical Electronic Control Units (ECUs) found in traditional vehicle functions. Think of powertrain, braking, steering, and body control modules. These systems require:

*   **Hard Real-Time Performance:** Deterministic responses where a missed deadline is a critical failure.
*   **High Reliability and Safety:** Certified to standards like ISO 26262 (ASIL-D).
*   **Efficiency:** They run on microcontrollers (MCUs) with limited computing resources.

As the provided slide illustrates, the Classic AUTOSAR architecture is layered:
*   **Application Software:** Contains the application-specific logic.
*   **Runtime Environment (RTE):** The central nervous system that enables communication between application components and the underlying base software.
*   **Basic Software (BSW):** A standardized set of services for hardware abstraction, system services, memory management, and communication (e.g., CAN, LIN).

This static, pre-configured architecture is perfect for functions that are defined at the time of vehicle manufacturing and rarely change.

#### **The Modern Evolution: Adaptive AUTOSAR (AP)**

The advent of connected, autonomous, and highly personalized vehicles created new challenges. Features like over-the-air (OTA) updates, advanced driver-assistance systems (ADAS), infotainment, and cloud connectivity require:
*   **High-Performance Computing:** They run on powerful multicore microprocessors (MPUs/SoCs) with gigabytes of RAM.
*   **Dynamic Updatability:** The ability to install new software features and updates throughout the vehicle's lifecycle.
*   **Flexible Communication:** Support for high-bandwidth, Ethernet-based networks (like SOME/IP) and connectivity to the cloud.
*   **Complex Software Ecosystems:** Often leveraging POSIX-based operating systems (e.g., Linux, QNX).

Adaptive AUTOSAR was designed specifically for these "high-performance" compute domains. Its architecture, as shown in the slide, is different:
*   **Adaptive Application Software:** Often more complex applications, which can be updated dynamically.
*   **AUTOSAR Runtime for Adaptive (ARA):** The adaptive equivalent to the RTE. It provides a set of C++ interfaces and services for communication, persistence, and execution management.
*   **Services & Basis:** The underlying operating system and core services that support the dynamic execution of adaptive applications.

#### **Key Differences at a Glance**

| Feature                   | Classic AUTOSAR (CP)                                         | Adaptive AUTOSAR (AP)                                        |
| :------------------------ | :----------------------------------------------------------- | :----------------------------------------------------------- |
| **Primary Use Case**      | Safety-critical, hard real-time control (e.g., engine, brakes) | High-performance, compute-intensive functions (e.g., ADAS, infotainment, OTA) |
| **Hardware**              | Microcontrollers (MCUs)                                      | High-Performance Microprocessors (MPUs/SoCs)                 |
| **Execution**             | Static, pre-scheduled at design time                         | Dynamic, event-driven execution                              |
| **Communication**         | CAN, LIN, FlexRay (static signals)                           | Ethernet-based (SOME/IP - dynamic services)                  |
| **Software Architecture** | Layered, static                                              | Service-Oriented Architecture (SOA)                          |
| **Runtime Environment**   | RTE (C-based)                                                | ARA (C++-based APIs)                                         |
| **Operating System**      | OSEK/VDX-based OS                                            | POSIX-based OS (e.g., Linux, QNX)                            |
| **Updatability**          | Difficult, often requiring a dealer visit                    | Designed for **Over-The-Air (OTA)** updates                  |

#### **Coexistence, Not Replacement**

It is a common misconception that Adaptive AUTOSAR is replacing Classic AUTOSAR. This is not the case. Instead, they are complementary technologies that coexist within the same vehicle.

A modern vehicle is a complex system of systems:
*   **Classic AUTOSAR domains** handle the critical, real-time vehicle dynamics—the "body and muscles" of the car.
*   **Adaptive AUTOSAR domains** handle the high-performance computing and connectivity—the "brain and senses" of the car.

These domains must communicate seamlessly. This is achieved through gateways that translate between the signal-based world of Classic platforms (CAN) and the service-oriented world of Adaptive platforms (SOME/IP over Ethernet).

#### **Conclusion: Where Today Meets Tomorrow**

As the concluding note on the slide from Siemens Digital Industries Software suggests, AUTOSAR is where the automotive industry's present meets its software-defined future.

**Classic AUTOSAR** remains the bedrock of vehicle safety and reliability, governing the fundamental operations that must never fail. **Adaptive AUTOSAR** is the platform for innovation and growth, enabling the new, connected, and updatable features that consumers demand.

Understanding the distinct roles and architectures of CP and AP is essential for anyone involved in developing the software that will power the vehicles of tomorrow. The future is not one or the other, but a smart, integrated combination of both.