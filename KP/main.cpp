#include <iostream>
#include <string>

// Global constants for array limits
const int MAX_LIBRARY = 150;
const int MAX_SCHEDULE = 30;
const int MAX_REQUESTS = 50;

// ============================================================================
// MODULE 1: DOMAIN CLASSES
// ============================================================================

// ABSTRACТION: Base abstract class for any audio content on the radio
class AudioItem {
protected:
    // ENCAPSULATION: Protected fields, accessible only via inheritance/methods
    std::string title;
    int duration; // in seconds

public:
    AudioItem(std::string t, int d) : title(t), duration(d) {}
    
    // Virtual destructor is mandatory for polymorphism clean-up
    virtual ~AudioItem() {}

    // Pure virtual function making this class Abstract
    virtual std::string getType() const = 0; 
    
    // Virtual method for polymorphic data display description
    virtual std::string getDescription() const {
        return "[" + getType() + "] " + title + " (" + std::to_string(duration) + "s)";
    }

    std::string getTitle() const { return title; }
    int getDuration() const { return duration; }
};

// INHERITANCE: Derived class representing a regular Music Song
class Song : public AudioItem {
private:
    std::string artist; // Encapsulated specific field

public:
    Song(std::string t, std::string a, int d) : AudioItem(t, d), artist(a) {}

    // POLYMORPHISM: Overriding virtual methods
    std::string getType() const override { return "Song"; }
    
    std::string getDescription() const override {
        return "[Song] " + artist + " - " + title + " (" + std::to_string(duration) + "s)";
    }

    std::string getArtist() const { return artist; }
};

// INHERITANCE: Derived class representing a Radio Commercial (Advertisement)
class Commercial : public AudioItem {
private:
    std::string sponsor; // Encapsulated specific field

public:
    Commercial(std::string t, std::string s, int d) : AudioItem(t, d), sponsor(s) {}

    // POLYMORPHISM: Overriding virtual methods
    std::string getType() const override { return "Commercial"; }
    
    std::string getDescription() const override {
        return "[Commercial] " + title + " (Sponsor: " + sponsor + ", " + std::to_string(duration) + "s)";
    }

    std::string getSponsor() const { return sponsor; }
};


// ============================================================================
// MODULE 2: ORDER LOGIC MODULE
// ============================================================================

// Separate class responsible solely for managing listener request queue logic
class OrderManager {
private:
    int requests[MAX_REQUESTS]; // Stores indices of AudioItems from global library
    int requestsSize;

public:
    OrderManager() : requestsSize(0) {}

    bool addRequest(int itemIndex, int librarySize) {
        if (itemIndex < 0 || itemIndex >= librarySize) return false;
        if (requestsSize >= MAX_REQUESTS) return false;
        
        requests[requestsSize] = itemIndex;
        requestsSize++;
        return true;
    }

    // Fetches the first request index and shifts the array (FIFO queue logic)
    int popNextRequest() {
        if (requestsSize == 0) return -1;
        
        int nextIndex = requests[0];
        for (int i = 0; i < requestsSize - 1; i++) {
            requests[i] = requests[i + 1];
        }
        requestsSize--;
        return nextIndex;
    }

    int getCount() const { return requestsSize; }
    int getRequestIndex(int position) const { return requests[position]; }
};


// Core domain aggregator representing the Radio Station state and schedule
class RadioStation {
private:
    AudioItem* library[MAX_LIBRARY]; // Array of polymorphic pointers
    int librarySize;

    int schedule[7][MAX_SCHEDULE]; // 7 days, stores library indices
    int scheduleSizes[7];

    OrderManager orderModule; // Embedding the Order Logic Module (Composition)

public:
    RadioStation() {
        librarySize = 0;
        for (int i = 0; i < 7; i++) scheduleSizes[i] = 0;
    }

    // Destructor to free dynamically allocated polymorphic objects safely
    ~RadioStation() {
        for (int i = 0; i < librarySize; i++) {
            delete library[i];
        }
    }

    bool addSongToLibrary(std::string title, std::string artist, int duration) {
        if (librarySize >= MAX_LIBRARY) return false;
        library[librarySize] = new Song(title, artist, duration);
        librarySize++;
        return true;
    }

    bool addCommercialToLibrary(std::string title, std::string sponsor, int duration) {
        if (librarySize >= MAX_LIBRARY) return false;
        library[librarySize] = new Commercial(title, sponsor, duration);
        librarySize++;
        return true;
    }

    bool addTrackToSchedule(int day, int itemIndex) {
        if (day < 0 || day > 6 || itemIndex < 0 || itemIndex >= librarySize) return false;
        if (scheduleSizes[day] >= MAX_SCHEDULE) return false;

        schedule[day][scheduleSizes[day]] = itemIndex;
        scheduleSizes[day]++;
        return true;
    }

    bool requestTrack(int itemIndex) {
        // Only "Song" types can be requested by listeners, commercials cannot
        if (itemIndex < 0 || itemIndex >= librarySize) return false;
        if (library[itemIndex]->getType() != "Song") return false; 

        return orderModule.addRequest(itemIndex, librarySize);
    }

    int playNext(int currentDay, bool& outIsRequest) {
        // Order Module takes priority
        if (orderModule.getCount() > 0) {
            outIsRequest = true;
            return orderModule.popNextRequest();
        }
        // Schedule takes next turn
        outIsRequest = false;
        if (currentDay >= 0 && currentDay <= 6 && scheduleSizes[currentDay] > 0) {
            return schedule[currentDay][0]; // Simple logic: returns first scheduled
        }
        return -1;
    }

    // Getters for UI Module
    int getLibrarySize() const { return librarySize; }
    AudioItem* getLibraryItem(int index) const { return library[index]; }
    int getScheduleSize(int day) const { return scheduleSizes[day]; }
    int getScheduleItemIndex(int day, int pos) const { return schedule[day][pos]; }
    OrderManager& getOrderModule() { return orderModule; }
};

// ============================================================================
// INCLUDE EXTERNAL DATA FILES (Connected right after classes definitions)
// ============================================================================
#include "SongsData.h"
#include "CommercialsData.h"

// ============================================================================
// MODULE 3: TESTING MODULE
// ============================================================================

class TestingModule {
public:
    static void runAutomatedTests() {
        std::cout << "\n[TEST MODULE] Starting automated architectural tests...\n";
        RadioStation testStation;
        testStation.addSongToLibrary("Test Track", "Artist", 120);
        testStation.addCommercialToLibrary("Test Ad", "Sponsor", 20);
        
        if (testStation.getLibrarySize() == 2) std::cout << "-> TEST 1 PASSED: Library counters valid.\n";
        else std::cout << "-> TEST 1 FAILED!\n";

        if (!testStation.requestTrack(1)) std::cout << "-> TEST 2 PASSED: Commercial block request rejected successfully.\n";
        else std::cout << "-> TEST 2 FAILED!\n";
        std::cout << "[TEST MODULE] Testing complete.\n\n";
    }
};

// ============================================================================
// MODULE 4: USER INTERACTION MODULE
// ============================================================================

class UserInterface {
public:
    void showMainMenu(RadioStation& station) {
        int choice = 0;
        int currentDay = 0; // Monday

        while (true) {
            std::cout << "==============================\n";
            std::cout << "    RADIO AIS INTERACTIVE UI  \n";
            std::cout << "==============================\n";
            std::cout << "Current Day: ";
            switch (currentDay) {
                case 0: std::cout << "Monday"; break;
                case 1: std::cout << "Tuesday"; break;
                case 2: std::cout << "Wednesday"; break;
                case 3: std::cout << "Thursday"; break;
                case 4: std::cout << "Friday"; break;
                case 5: std::cout << "Saturday"; break;
                case 6: std::cout << "Sunday"; break;
            }
            std::cout << "\n------------------------------\n";
            std::cout << "1. Print Media Library\n";
            std::cout << "2. Add New Song\n";
            std::cout << "3. Add New Commercial Ad\n";
            std::cout << "4. Print Today's Schedule\n";
            std::cout << "5. Add Item to Day Schedule\n";
            std::cout << "6. Listener Mode: Order a Song\n";
            std::cout << "7. Print Active Requests Queue\n";
            std::cout << "8. Air Control: Play Next Track\n";
            std::cout << "9. Switch Current Day\n";
            std::cout << "0. Shut Down Station\n";
            std::cout << "------------------------------\n";
            std::cout << "Select menu item: ";
            std::cin >> choice;

            if (choice == 0) {
                std::cout << "Shutting down. Goodbye!\n";
                break;
            }

            switch (choice) {
                case 1: {
                    std::cout << "\n--- MEDIA STATION LIBRARY ---\n";
                    for (int i = 0; i < station.getLibrarySize(); i++) {
                        std::cout << "[" << i << "] " << station.getLibraryItem(i)->getDescription() << "\n";
                    }
                    break;
                }
                case 2: {
                    std::string title, artist; int duration;
                    std::cout << "Enter Artist Name: "; std::cin.ignore(); std::getline(std::cin, artist);
                    std::cout << "Enter Song Title: "; std::getline(std::cin, title);
                    std::cout << "Enter Duration (sec): "; std::cin >> duration;
                    if (station.addSongToLibrary(title, artist, duration)) std::cout << "Song added.\n";
                    else std::cout << "Error: Full!\n";
                    break;
                }
                case 3: {
                    std::string title, sponsor; int duration;
                    std::cout << "Enter Ad Title: "; std::cin.ignore(); std::getline(std::cin, title);
                    std::cout << "Enter Sponsor: "; std::getline(std::cin, sponsor);
                    std::cout << "Enter Duration (sec): "; std::cin >> duration;
                    if (station.addCommercialToLibrary(title, sponsor, duration)) std::cout << "Commercial added.\n";
                    else std::cout << "Error: Full!\n";
                    break;
                }
                case 4: {
                    std::cout << "\n--- SCHEDULE PLAN FOR TODAY ---\n";
                    int size = station.getScheduleSize(currentDay);
                    if (size == 0) std::cout << "No tracks planned.\n";
                    else {
                        for (int i = 0; i < size; i++) {
                            int idx = station.getScheduleItemIndex(currentDay, i);
                            std::cout << (i + 1) << ". " << station.getLibraryItem(idx)->getDescription() << "\n";
                        }
                    }
                    break;
                }
                case 5: {
                    int targetDay, itemIdx;
                    std::cout << "Enter target day (0-6): "; std::cin >> targetDay;
                    std::cout << "Enter item index from global library (0-" << station.getLibrarySize() - 1 << "): ";
                    std::cin >> itemIdx;
                    if (station.addTrackToSchedule(targetDay, itemIdx)) std::cout << "Track attached.\n";
                    else std::cout << "Error: Invalid inputs or schedule full!\n";
                    break;
                }
                case 6: {
                    int itemIdx;
                    std::cout << "Enter Song index to request (0-" << station.getLibrarySize() - 1 << "): ";
                    std::cin >> itemIdx;
                    if (station.requestTrack(itemIdx)) std::cout << "Success! Registered.\n";
                    else std::cout << "Rejected: Invalid index OR item is an Ad!\n";
                    break;
                }
                case 7: {
                    std::cout << "\n--- ACTIVE REQUESTS QUEUE ---\n";
                    OrderManager& om = station.getOrderModule();
                    if (om.getCount() == 0) std::cout << "No active requests.\n";
                    else {
                        for (int i = 0; i < om.getCount(); i++) {
                            int idx = om.getRequestIndex(i);
                            std::cout << (i + 1) << ". " << station.getLibraryItem(idx)->getDescription() << "\n";
                        }
                    }
                    break;
                }
                case 8: {
                    bool isReq = false;
                    int idx = station.playNext(currentDay, isReq);
                    if (idx == -1) std::cout << "\n[AIR] -Silence- No active content.\n";
                    else {
                        std::cout << "\n>>> AIR BROADCASTING NOW <<<\n";
                        if (isReq) std::cout << "[LISTENER ORDER] ";
                        else std::cout << "[ROUTINE PLAN] ";
                        std::cout << station.getLibraryItem(idx)->getDescription() << "\n";
                    }
                    break;
                }
                case 9: {
                    int d; std::cout << "Enter new day code (0-6): "; std::cin >> d;
                    if (d >= 0 && d <= 6) { currentDay = d; std::cout << "Updated.\n"; }
                    else std::cout << "Invalid code!\n";
                    break;
                }
                default: std::cout << "Unknown command.\n";
            }
            std::cout << "\n";
        }
    }
};

// ============================================================================
// MAIN APPLICATION ENTRY POINT
// ============================================================================
int main() {
    // Execute automated tests first to prove system reliability
    TestingModule::runAutomatedTests();

    // Initialize core business entity
    RadioStation mainRadioStation;

    // Calling the helper functions from connected header files
    loadPopularSongs(mainRadioStation);         // Automatically reads and fills songs
    loadCommercialProposals(mainRadioStation);  // Automatically reads and fills commercials

    // Pre-scheduling two items for Monday demo
    mainRadioStation.addTrackToSchedule(0, 5);  // Mon: Song at index 5
    mainRadioStation.addTrackToSchedule(0, 52); // Mon: Commercial at index 52

    // Hand over control to user interaction module
    UserInterface ui;
    ui.showMainMenu(mainRadioStation);

    return 0;
}
