// src/adapters/memory/InMemoryFlightPlanRepository.hpp
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

#include "../../ports/FlightPlanRepository.hpp"

namespace adapters::memory {

// In-memory implementation of FlightPlanRepository.
// Data is stored in RAM and will be lost when the program exits.
class InMemoryFlightPlanRepository : public ports::FlightPlanRepository {
public:
    InMemoryFlightPlanRepository() = default;
    ~InMemoryFlightPlanRepository() override = default;

    bool create(const domain::FlightPlan& plan) override;

    std::optional<domain::FlightPlan>
    get(const std::string& flightNumber) override;

    bool update(const domain::FlightPlan& plan) override;

    bool remove(const std::string& flightNumber) override;

    std::vector<domain::FlightPlan> list() override;

private:
    // Key: flightNumber (v0)
    std::unordered_map<std::string, domain::FlightPlan> store_;
};

} // namespace adapters::memory