// DataBridge.cpp
#include "DataBridge.h"
#include <iostream>

using namespace std;

DataBridge::DataBridge(mutex& m, shared_ptr<InertiaSource> inertia, shared_ptr<AltimeterSource> altimeter, shared_ptr<PressureSource> pressure)
    : m(m), inertia_source(inertia), altimeter_source(altimeter), pressure_source(pressure) {
    std::cout << "DataBridge Constructor" << endl;

    inertia_source->RegisterInertiaReceiver(
        bind(&DataBridge::On_InertiaUpdate, this, placeholders::_1)
    );

    altimeter_source->RegisterAltimeterReceiver(
        bind(&DataBridge::On_HeightUpdate, this, placeholders::_1)
    );

    pressure_source->RegisterPressureReceiver(
        bind(&DataBridge::On_PressureUpdate, this, placeholders::_1)
    );


}

const FlightData DataBridge::GetFlightData() {

    std::lock_guard<std::mutex> lock(m);
    flight_data.water_column_depth = flight_data.system_depth + flight_data.system_height;
    cout << "System: { " << flight_data.system_depth << ", " << flight_data.system_height << ", " << flight_data.water_column_depth << ", " << flight_data.roll << ", " << flight_data.pitch << ", " << flight_data.heading << " }" << endl;

    return flight_data;
}

void DataBridge::On_HeightUpdate(const AltimeterSample &sample) {
    std::lock_guard<std::mutex> lock(m);
    flight_data.system_height = sample.distance;
    cout << "Height Update: " << sample.distance << endl;
}

void DataBridge::On_PressureUpdate(const PressureSample &sample) {
    std::lock_guard<std::mutex> lock(m);
    flight_data.system_depth = sample.pressure;
    cout << "Pressure Update: " << sample.pressure << endl;
}

void DataBridge::On_InertiaUpdate(const InertiaSample &sample) {
    std::lock_guard<std::mutex> lock(m);
    flight_data.roll = sample.x;
    flight_data.pitch = sample.y;
    flight_data.heading = sample.z;
    cout << "Inertia Update -- Roll: " << flight_data.roll << ", Pitch: " << flight_data.pitch << ", Heading: "<<flight_data.heading<< endl;
}
