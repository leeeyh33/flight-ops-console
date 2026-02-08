// src/adapters/cli/MenuCli.cpp
#include "MenuCli.hpp"

#include <iostream>
#include <string>
#include <optional>

#include "../../usecase/FlightPlanService.hpp"
#include "../../domain/FlightPlan.hpp"

namespace adapters::cli {

static void printMenu() {
    std::cout
        << "\n==== Flight Ops Console ====\n"
        << "1) Create flight\n"
        << "2) Get flight\n"
        << "3) Update flight\n"
        << "4) Delete flight\n"
        << "5) List flights\n"
        << "0) Exit\n"
        << "Select: ";
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static std::optional<std::string> readFlightNumber() {
    while (true) {
        std::string s = readLine("Please enter flight number (AA123/AA1234), or :q to cancel: ");
        if (s == ":q") {
            return std::nullopt;
        }
        if (domain::isValidFlightNumber(s)) {
            return s;
        }
        std::cout << "Invalid flight number format. Expected AA123 or AA1234.\n";
    }
}

static void printFlight(const domain::FlightPlan& p) {
    std::cout
        << "Flight: " << p.flightNumber << "\n"
        << "  Airline: " << p.airlineCode << "\n"
        << "  Aircraft: " << p.aircraftType << " (" << p.aircraftRegistration << ")\n"
        << "  From: " << p.departureAirport << "  To: " << p.arrivalAirport << "\n"
        << "  Dep: " << p.departureTime << "  Arr: " << p.arrivalTime << "\n";
}

static std::optional<domain::FlightPlan> inputFlightPlan() {
    domain::FlightPlan p;
    auto flightNo = readFlightNumber();
    if (!flightNo.has_value()) {
        return std::nullopt;
    }
    p.flightNumber = *flightNo;
    p.airlineCode = readLine("Please enter airline code: ");
    p.aircraftType = readLine("Please enter aircraft type: ");
    p.aircraftRegistration = readLine("Please enter aircraft registration: ");
    p.departureAirport = readLine("Please enter departure airport: ");
    p.arrivalAirport = readLine("Please enter arrival airport: ");
    p.departureTime = readLine("Please enter departure time: ");
    p.arrivalTime = readLine("Please enter arrival time: ");
    return p;
}

int MenuCli::run() {
    while (true) {
        printMenu();

        std::string choiceLine;
        std::getline(std::cin, choiceLine);
        if (choiceLine.empty()) continue;

        int choice = -1;
        try {
            choice = std::stoi(choiceLine);
        } catch (...) {
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Bye.\n";
            return 0;
        }

        if (choice == 1) {
            auto p = inputFlightPlan();
            if (!p.has_value()) {
                std::cout << "Canceled.\n";
                continue;
            }
            bool ok = service_.create(*p);
            std::cout << (ok ? "Created.\n" : "Failed (invalid input or duplicate).\n");
            continue;
        }

        if (choice == 2) {
            auto flightNo = readFlightNumber();
            if (!flightNo.has_value()) {
                std::cout << "Canceled.\n";
                continue;
            }
            auto res = service_.get(*flightNo);
            if (!res.has_value()) {
                std::cout << "NotFound.\n";
            } else {
                printFlight(*res);
            }
            continue;
        }

        if (choice == 3) {
            auto p = inputFlightPlan();
            if (!p.has_value()) {
                std::cout << "Canceled.\n";
                continue;
            }
            bool ok = service_.update(*p);
            std::cout << (ok ? "Updated.\n" : "Failed (invalid input or not found).\n");
            continue;
        }

        if (choice == 4) {
            auto flightNo = readFlightNumber();
            if (!flightNo.has_value()) {
                std::cout << "Canceled.\n";
                continue;
            }
            bool ok = service_.remove(*flightNo);
            std::cout << (ok ? "Deleted.\n" : "NotFound.\n");
            continue;
        }

        if (choice == 5) {
            auto all = service_.list();
            if (all.empty()) {
                std::cout << "(empty)\n";
            } else {
                for (const auto& p : all) {
                    std::cout << p.flightNumber << " "
                              << p.departureAirport << "->" << p.arrivalAirport
                              << " " << p.departureTime << "\n";
                }
            }
            continue;
        }

        std::cout << "Unknown option.\n";
    }
}

} // namespace adapters::cli
