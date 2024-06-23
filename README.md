
# Sensor and Source Hierarchy

## Sensor Classes

The `Sensor` class serves as an abstract base class with three derived classes, including:

- `PA200`
- `PA3XX`
- `MTI_30_AHRS`

These sensor classes implement methods for initialization, sampling, and termination.

## Abstract Source Classes

The following abstract source classes provide interfaces for registering receivers and notifying sample updates:

- `AltimeterSource`
- `PressureSource`
- `TemperatureSource`
- `InertiaSource`

## Data Structures and Integration

Various data structures hold sensor data:

- `Altimeter`
- `Pressure`
- `Temperature`
- `Inertia`
- `FlightData`

The `DataBridge` class aggregates data from these sources and updates the `FlightController`.

## System Integration

The `FlightController` relies on the `DataBridge` to manage and utilize flight data effectively for controlling flight parameters.

## Diagnostic Reporting

A diagnostic system includes the following components:

- `DiagnosticReport` struct
- `ReportGenerator` class