#include "MenuNetworkStats.h"

MenuNetworkStats::MenuNetworkStats(const FlightManagement &management): Menu(management) {}

bool MenuNetworkStats::start() {
    bool exit = false;
    string option;
    while (!exit) {
        cout << "-> NETWORK STATS\n\n";
        cout << "1 - GLOBAL STATS\n";
        cout << "2 - COUNTRY STATS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            exit = globalStatsMenu();
        if (option == "2")
            exit = countryStatsMenu();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
    return true;
}

bool MenuNetworkStats::globalStatsMenu() {
    string option;
    while (true) {
        cout << "-> GLOBAL STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            globalArticulationPoints();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
}

bool MenuNetworkStats::countryStatsMenu() {
    string option;
    while (true) {
        cout << "-> COUNTRY STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            countryArticulationPoints();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
}

void MenuNetworkStats::globalArticulationPoints() {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<int> aps = graph.getGlobalArticulationPoints();
    cout << "Number of global articulation points: " << aps.size() << "\n";
    for (int i : aps) {
        cout << map[i]->getName() << "\n";
    }
}

void MenuNetworkStats::countryArticulationPoints() {
    bool found = false;
    string country;
    cout << "Country: ";
    getline(cin, country);
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    for (int i=1;i<map.size();i++){
        if (map[i]->getCountry() == country)
            found = true;
    }
    if (!found) {
        cout << "No country with such name\n";
        return;
    }
    vector<int> aps = graph.getCountryArticulationPoints(map,country);

    cout << "Number of articulation points in " << country << ": " << aps.size() << "\n";
    for (int i : aps) {
        cout << map[i]->getName() << "\n";
    }
}