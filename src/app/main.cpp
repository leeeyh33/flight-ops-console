// src/app/main.cpp
#include "../adapters/memory/InMemoryFlightPlanRepository.hpp"
#include "../usecase/FlightPlanService.hpp"
#include "../adapters/cli/MenuCli.hpp"

int main() {
    adapters::memory::InMemoryFlightPlanRepository repo;
    usecase::FlightPlanService service(repo);

    adapters::cli::MenuCli cli(service);
    return cli.run();
}