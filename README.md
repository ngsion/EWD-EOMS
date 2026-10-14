# EWD-EOMS: Automated Instrument Control and Electrical Characterisation for Electrowetting Devices

**A C-based research software prototype for multi-instrument control, automated electrical measurements, and experimental data acquisition using NI LabWindows/CVI.**

## Overview

EWD-EOMS (Electrowetting Display Electro-Optical Measurement System) is a research software project developed to support the automated characterisation of electrowetting display (EWD) devices.

The project aims to reduce repetitive manual instrument operations and provide a modular software framework for programmable experimental procedures, measurement acquisition, real-time visualisation, and data management.

The implemented system focuses on **electrical characterisation**, including current–voltage (I–V) and capacitance–voltage (C–V) measurements.

Although integration with CCD-based optical imaging was considered during development, camera acquisition and optical analysis were not implemented because of limitations in the available experimental instrumentation.

## Implemented Features

### Instrument Communication and Control

- Instrument discovery and connection through NI-VISA.
- Support for USB, GPIB, and serial instrument interfaces.
- SCPI-based command transmission and instrument identification.
- Device management through a modular software architecture.

### Automated Measurements

- Programmable bidirectional voltage sweeps.
- Configurable voltage range, step size, and measurement interval.
- Automated current acquisition using a picoammeter.
- Capacitance and dissipation-factor measurements using an LCR meter.
- Waveform-generator configuration, including frequency, voltage levels, and channel offsets.

### Data Acquisition and Management

- Background measurement execution using the LabWindows/CVI thread-pool interface.
- Data queues for transferring measurement results to the graphical interface.
- Real-time electrical measurement visualisation.
- Excel-based data export with measurement batch identifiers.
- Logging of instrument operations and software events.

## Software Architecture

The codebase is organised into functional modules:

| Directory / File | Responsibility |
|---|---|
| `EOMS/instruments/` | VISA resource discovery, instrument sessions, and identification |
| `EOMS/devices/` | Device-specific communication and control |
| `EOMS/measurement/` | Automated measurement procedures and data acquisition |
| `EOMS/setting/` | Instrument and measurement configuration |
| `EOMS/datasave/` | Excel data export and measurement record management |
| `EOMS/datastruct/` | Data queues, stacks, and supporting structures |
| `EOMS/ui/` | Graphical user interfaces and real-time plots |
| `EOMS/clogger/` | Logging functions |
| `EOMS/EOMSystem.c` | System initialisation and measurement workflow coordination |
| `EOMS/EOMS.prj` | NI LabWindows/CVI project file |

## Measurement Workflow

The implemented workflow follows these stages:

1. Discover available instruments through NI-VISA.
2. Select and establish connections to compatible instruments.
3. Configure measurement parameters through the graphical interface.
4. Execute automated voltage sweeps and acquire electrical measurements.
5. Transfer acquired data to real-time display components.
6. Save measurement results to Excel files for subsequent analysis.

The system provides automated measurement execution but does not implement autonomous experimental optimisation or AI-driven feedback control.

## Development Environment

- **Programming language:** C
- **Development platform:** NI LabWindows/CVI (project configured for CVI 2017)
- **Instrument communication:** NI-VISA and SCPI
- **User interface:** LabWindows/CVI GUI
- **Data export:** LabWindows/CVI Excel Report
- **Target operating system:** Windows

The repository includes the original CVI project file at `EOMS/EOMS.prj`.

Building and running the application requires the relevant NI software components, compatible instrument drivers, and appropriate laboratory hardware.

## Experimental Validation and Deployment

EWD-EOMS was developed and tested with physical laboratory instruments during electrowetting device characterisation.

The implemented instrument-control and automated electrical measurement functions were operated in a real experimental environment, including picoammeter measurements, LCR-based capacitance measurements, and waveform-generator control.

The application can be packaged as a Windows installer using the NI LabWindows/CVI development environment, enabling deployment on compatible laboratory computers with the required runtime components and instrument drivers.

Current Scope and Limitations

The released code primarily supports automated electrical characterisation.

Admesy optical instrument integration and CCD camera acquisition were considered but not completed.

The Korad module represents a later, partially implemented extension.

Optical spectroscopy, automated optical imaging, and autonomous experiment optimisation are not implemented in the released version.

The repository contains the original research implementation. Installation and instrument operation depend on compatible hardware, drivers, and the NI software environment.

## Research Significance

EWD-EOMS demonstrates the application of software engineering to experimental physics through programmable instrument control and automated measurement workflows.

The project provided practical experience in integrating laboratory instruments, designing modular measurement software, implementing experimental procedures, and organising quantitative measurement data.

These methods are transferable to the development of automated experimental platforms involving other types of scientific instrumentation.


## License

This project is distributed under the BSD 3-Clause License. See [LICENSE](LICENSE) for details.
