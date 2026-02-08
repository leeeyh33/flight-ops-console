// src/usecase/FlightPlanService.cpp
#include "FlightPlanService.hpp"

namespace usecase {

FlightPlanService::FlightPlanService(ports::FlightPlanRepository& repo)
    : repo_(repo) {}

bool FlightPlanService::create(const domain::FlightPlan& plan) {
    if (!domain::isValidBasic(plan)) {
        return false;
    }
    return repo_.create(plan);
}

std::optional<domain::FlightPlan>
FlightPlanService::get(const std::string& flightNumber) {
    if (flightNumber.empty()) {
        return std::nullopt;
    }
    return repo_.get(flightNumber);
}

bool FlightPlanService::update(const domain::FlightPlan& plan) {
    if (!domain::isValidBasic(plan)) {
        return false;
    }
    return repo_.update(plan);
}

bool FlightPlanService::remove(const std::string& flightNumber) {
    if (flightNumber.empty()) {
        return false;
    }
    return repo_.remove(flightNumber);
}

std::vector<domain::FlightPlan> FlightPlanService::list() {
    return repo_.list();
}

} // namespace usecase