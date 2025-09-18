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

The core of the Adaptive AUTOSAR stack is the **AUTOSAR Runtime for Adaptive (ARA)**, which is a collection of C++ APIs grouped into "service clusters." Applications access these APIs to communicate, manage execution, and interact with the vehicle.

Here is a breakdown of the key components in the Adaptive AUTOSAR stack, from the hardware up to the applications.

------

### **The Adaptive AUTOSAR Stack**

#### 1. **Hardware**

- **Type:** High-performance Microprocessors (MPUs) or Systems on a Chip (SoCs).
- **Features:** Multi-core processors (e.g., ARM Cortex-A series, x86), GPUs, NPUs, and often include integrated hardware security modules (HSMs).
- **Purpose:** Provides the substantial computing power required for complex algorithms and multiple concurrent applications.

#### 2. **Operating System (OS)**

- **Type:** POSIX-compliant Operating System.
- **Examples:** Linux (AGL, Ubuntu Auto), QNX OS for Safety, Integrity, etc.
- **Purpose:** Provides a standardized environment for process management, scheduling, memory management, and device drivers. It handles the dynamic execution of applications, which is a key difference from the static OS in Classic AUTOSAR.

#### 3. **AUTOSAR Adaptive Platform Foundation**

This is the core middleware that abstracts the hardware and OS. It consists of two main parts:

- **Adaptive AUTOSAR Services:** This is the "functional" part of the stack that applications interact with.
- **Adaptive AUTOSAR Basis:** This is the "foundational" layer that manages the platform itself.

Let's break down the Services and Basis into their functional clusters, which make up the actual "stack":

------

### **ARA :: API Service Clusters (The "Services")**

These are the interfaces that Adaptive Applications use to function.

- **ARA::COM (Communication API):**
  - **Purpose:** Manages service-oriented communication (SOA) between applications within the same machine or over the network.
  - **Key Technology:** Uses **SOME/IP** (Scalable service-Oriented MiddlewarE over IP) as the primary protocol over Ethernet.
- **ARA::EM (Execution Management API):**
  - **Purpose:** Responsible for starting, stopping, and monitoring the state of functional groups of applications (called "Execution Manifests").
  - **Key Function:** It is crucial for orchestrating the complex startup and shutdown sequences of high-level features.
- **ARA::SM (State Management API):**
  - **Purpose:** Manages the overall state of the machine and the functional groups within it (e.g., driving state, maintenance state, update state).
  - **Key Function:** Works closely with EM to trigger state-dependent actions.
- **ARA::IAM (Identity and Access Management API):**
  - **Purpose:** Provides security and access control. It authenticates and authorizes applications and their requests to access specific services or resources.
  - **Key Function:** Enforces security policies within the ECU.
- **ARA::PER (Persistence API):**
  - **Purpose:** Provides a standardized way for applications to store and retrieve data (e.g., configuration, cache, state information) in a persistent manner.
- **ARA::PHM (Platform Health Management API):**
  - **Purpose:** Monitors the health of applications and functional groups, similar to a watchdog manager in Classic AUTOSAR.
  - **Key Function:** Can report errors and trigger recovery actions.
- **ARA::DIAG (Diagnostics API):**
  - **Purpose:** Provides support for standardized diagnostics (e.g., UDS, DoIP) in the adaptive environment.
- **ARA::API (Other APIs):** Includes additional services for Logging (`ARA::LOG`), Network Management (`ARA::NM`), Time Synchronization (`ARA::TSYNC`), etc.

------

### **Adaptive AUTOSAR Basis (The "Basis")**

This layer provides the underlying functionality that enables the platform services to run. Applications typically do not interact with it directly.

- **Operating System Interface:** Abstracts the specific POSIX OS.
- **Communication Management:** Implements the underlying SOME/IP binding, service discovery, and serialization.
- **Restart and Update Management:** Handles the mechanics of updating application packages and restarting the system or individual functions.
- **Time Synchronization:** Keeps the local system clock in sync with a network-wide time master (e.g., via PTP).
- **Logging and Tracing:** Collects log messages and system traces for debugging and analysis.
- **Crypto Stack:** Provides cryptographic functions for secure communication (TLS) and data signing/verification.

------

### **How It All Fits Together: A Simplified View**

| Layer                   | Component                                  | Description                                                  |
| :---------------------- | :----------------------------------------- | :----------------------------------------------------------- |
| **Application Layer**   | **Adaptive Applications (AA)**             | C++ applications that implement vehicle functionality. They use the **ARA APIs** to communicate and access services. |
| **Runtime Environment** | **AUTOSAR Runtime for Adaptive (ARA)**     | The collection of all service APIs (`ARA::COM`, `ARA::EM`, `ARA::SM`, etc.) that applications call into. |
| **Platform Services**   | **Adaptive Foundation (Services + Basis)** | The middleware implementation that provides the actual functionality behind the ARA APIs. It handles communication, execution, security, etc. |
| **Operating System**    | **POSIX OS (e.g., Linux)**                 | Provides process management, scheduling, and hardware abstraction. |
| **Hardware**            | **High-Performance MPU/SoC**               | The physical processor running the entire stack.             |