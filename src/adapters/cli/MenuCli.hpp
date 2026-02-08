// src/adapters/cli/MenuCli.hpp
#pragma once

namespace usecase { class FlightPlanService; }

namespace adapters::cli {

// A minimal menu-driven CLI UI for demo.
// This layer does I/O (cin/cout) and calls the service.
class MenuCli {
public:
    explicit MenuCli(usecase::FlightPlanService& service) : service_(service) {}

    int run();

private:
    usecase::FlightPlanService& service_;
};

} // namespace adapters::cli