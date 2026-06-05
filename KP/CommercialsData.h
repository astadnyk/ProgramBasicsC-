#ifndef COMMERCIALS_DATA_H
#define COMMERCIALS_DATA_H

#include <string>

// Forward declaration of RadioStation class
class RadioStation;

// Helper function to seed 10 global advertising blocks into the radio library
void loadCommercialProposals(RadioStation& station) {
    // List of business advertising campaigns
    station.addCommercialToLibrary("Summer Refresh Promo", "Coca-Cola", 30);
    station.addCommercialToLibrary("Just Do It Campaign", "Nike", 15);
    station.addCommercialToLibrary("iPhone New Release", "Apple", 45);
    station.addCommercialToLibrary("Galaxy Unpacked Event", "Samsung", 30);
    station.addCommercialToLibrary("I'm Lovin It Menu", "McDonalds", 20);
    station.addCommercialToLibrary("Max Taste No Sugar", "PepsiCo", 15);
    station.addCommercialToLibrary("Impossible Is Nothing", "Adidas", 30);
    station.addCommercialToLibrary("Ultimate Driving Machine", "BMW", 45);
    station.addCommercialToLibrary("PlayStation 5 Gaming", "Sony", 30);
    station.addCommercialToLibrary("Energy Boost Block", "Red Bull", 20);
}

#endif
