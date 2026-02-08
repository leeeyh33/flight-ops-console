// src/adapters/memory/InMemoryFlightPlanRepository.cpp
#include "InMemoryFlightPlanRepository.hpp"

namespace adapters::memory {

bool InMemoryFlightPlanRepository::create(const domain::FlightPlan& plan) {
    const std::string& key = plan.flightNumber;
    if (store_.find(key) != store_.end()) {
        return false; // already exists
    }
    store_.emplace(key, plan);
    return true;
}

std::optional<domain::FlightPlan>
InMemoryFlightPlanRepository::get(const std::string& flightNumber) {
    auto it = store_.find(flightNumber);
    if (it == store_.end()) {
        return std::nullopt;
    }
    return it->second;
}

bool InMemoryFlightPlanRepository::update(const domain::FlightPlan& plan) {
    const std::string& key = plan.flightNumber;
    auto it = store_.find(key);
    if (it == store_.end()) {
        return false; // not found
    }
    it->second = plan;
    return true;
}

bool InMemoryFlightPlanRepository::remove(const std::string& flightNumber) {
    auto it = store_.find(flightNumber);
    if (it == store_.end()) {
        return false; // not found
    }
    store_.erase(it);
    return true;
}

std::vector<domain::FlightPlan> InMemoryFlightPlanRepository::list() {
    std::vector<domain::FlightPlan> out;
    out.reserve(store_.size());
    for (const auto& kv : store_) {
        out.push_back(kv.second);
    }
    return out;
}

} // namespace adapters::memory