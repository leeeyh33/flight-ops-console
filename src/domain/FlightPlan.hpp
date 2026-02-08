// src/domain/FlightPlan.hpp
#pragma once

#include <string>

namespace domain {

// FlightPlan is a simple domain data structure for v0.
// - No I/O (no cin/cout, no file operations)
// - No persistence logic
// - Keep fields as std::string for simplicity and easy CLI input
struct FlightPlan {
    // v0 primary key (can evolve to a composite key later, e.g., flightNumber + date)
    std::string flightNumber;          // e.g., NH001

    std::string airlineCode;           // e.g., NH
    std::string aircraftType;          // e.g., B788
    std::string aircraftRegistration;  // e.g., JA812A

    std::string departureAirport;      // e.g., HND
    std::string arrivalAirport;        // e.g., CTS

    // v0: store time as string (ISO-like text is recommended)
    std::string departureTime;         // e.g., 2026-02-07T10:00
    std::string arrivalTime;           // e.g., 2026-02-07T11:35
};

// Basic validation for v0.
// Keep it minimal; deeper validation rules can be added later.
inline bool isValidBasic(const FlightPlan& p) {
    return !p.flightNumber.empty()
        && !p.airlineCode.empty()
        && !p.aircraftType.empty()
        && !p.aircraftRegistration.empty()
        && !p.departureAirport.empty()
        && !p.arrivalAirport.empty()
        && !p.departureTime.empty()
        && !p.arrivalTime.empty();
}

} // namespace domain