# Embedded Data Logger (C)

## Overview

This project implements a simple embedded data logging system in C.

It demonstrates how sensor data can be buffered using a ring buffer and processed using a logger module, following a producer–consumer architecture.

---

## Architecture

```
Sensor (Producer)
        ↓
Ring Buffer
        ↓
Logger (Consumer)
        ↓
Output (printf)
```

---

## Features

* Ring buffer (circular queue) implementation
* Producer–consumer data flow
* Modular design (data structure / system logic separation)
* Pluggable output interface using function pointers
* Independent test for core module

---

## Project Structure

```
embedded-data-logger/
├── src/
│   ├── core/
│   │   ├── ring_buffer.c
│   │   ├── logger.c
│   ├── main.c
│
├── include/
│   ├── ring_buffer.h
│   ├── logger.h
│   ├── sensor_data.h
│
├── test/
│   ├── test_ring_buffer.c
│
├── Makefile
└── README.md
```

---

## Build & Run

### Run main application

```bash
make run
```

### Run test

```bash
make run_test
```

---

## Example Output

```
[0 ms] temp=25.00
[100 ms] temp=26.00
[200 ms] temp=27.00
```

---

## Key Design Concepts

* **Ring Buffer (FIFO)**
  Decouples data production and consumption.

* **Producer–Consumer Model**
  Separates data generation and processing.

* **Modular Design**
  Keeps data structure and system logic independent.

* **Output Abstraction**
  Uses function pointers to support different output methods.

---

## Future Work

* Integrate real sensor (I2C)

