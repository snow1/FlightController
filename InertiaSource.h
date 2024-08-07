#ifndef INERTIA_SOURCE_H
#define INERTIA_SOURCE_H

#include <functional>
#include <iostream>
#include <vector>

struct InertiaSample {
    double x;
    double y;
    double z;
};

class InertiaSource {
private:
    void NotifySampleUpdate(const InertiaSample& new_sample) const;
    std::vector<std::function<void(const InertiaSample)>> callback_functions = {};

public:
    void RegisterInertiaReceiver(std::function<void(const InertiaSample&)> callback_function);
    const InertiaSample SampleInertia(); 

protected:
    virtual const InertiaSample OnSampleInertia() = 0;



};

#endif // INERTIA_SOURCE_H
