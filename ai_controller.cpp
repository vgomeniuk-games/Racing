#include "ai_controller.h"
#include "globals.h"

AIController::AIController(int competitors) {
    for(int i = 0; i < competitors; ++i) {
        cars.push_back(std::unique_ptr<Car>(new Car(
                Globals::Width / 2 + (i + 1) * 50,
                Globals::Height / 2 + (i + 1) * 50,
                colors[i % colors.size()]
        )));
    }
}
