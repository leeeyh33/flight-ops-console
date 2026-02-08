// src/usecase/FlightPlanService.hpp
#pragma once

#include <string>
#include <vector>
#include <optional>

#include "../domain/FlightPlan.hpp"
#include "../ports/FlightPlanRepository.hpp"

namespace usecase {

// FlightPlanService contains application logic for CRUD.
// - No I/O (no cin/cout, no file operations)
// - Depends only on the repository interface (port)
class FlightPlanService {
public:
    explicit FlightPlanService(ports::FlightPlanRepository& repo);

    // Return false if invalid input or already exists.
    bool create(const domain::FlightPlan& plan);

    // Return nullopt if invalid input or not found.
    std::optional<domain::FlightPlan> get(const std::string& flightNumber);

    // Return false if invalid input or not found.
    bool update(const domain::FlightPlan& plan);

    // Return false if invalid input or not found.
    bool remove(const std::string& flightNumber);

    // List all flights.
    std::vector<domain::FlightPlan> list();

private:
    ports::FlightPlanRepository& repo_;
};

} // namespace usecase