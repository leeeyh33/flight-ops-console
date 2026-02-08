// src/ports/FlightPlanRepository.hpp
#pragma once

#include <string>
#include <vector>
#include <optional>

#include "../domain/FlightPlan.hpp"

namespace ports {

// FlightPlanRepository defines the required storage capabilities.
// It does NOT define how data is stored (memory, file, database, etc.).
class FlightPlanRepository {
public:
    virtual ~FlightPlanRepository() = default;

    // Create a new flight.
    // Return false if the flightNumber already exists.
    virtual bool create(const domain::FlightPlan& plan) = 0;

    // Get a flight by flightNumber.
    // Return std::nullopt if not found.
    virtual std::optional<domain::FlightPlan>
    get(const std::string& flightNumber) = 0;

    // Update an existing flight.
    // Return false if flight does not exist.
    virtual bool update(const domain::FlightPlan& plan) = 0;

    // Remove a flight by flightNumber.
    // Return false if not found.
    virtual bool remove(const std::string& flightNumber) = 0;

    // Return all stored flights (for list command).
    virtual std::vector<domain::FlightPlan> list() = 0;
};

} // namespace ports