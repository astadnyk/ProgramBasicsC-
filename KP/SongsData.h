#ifndef SONGS_DATA_H
#define SONGS_DATA_H

#include <string>

// Forward declaration of RadioStation class so the compiler knows it exists
class RadioStation;

// Helper function to seed 50 popular tracks into the radio library
void loadPopularSongs(RadioStation& station) {
    // Top hits from various genres and eras
    station.addSongToLibrary("Blinding Lights", "The Weeknd", 200);
    station.addSongToLibrary("Shape of You", "Ed Sheeran", 233);
    station.addSongToLibrary("Bohemian Rhapsody", "Queen", 355);
    station.addSongToLibrary("Stay", "The Kid LAROI & Justin Bieber", 141);
    station.addSongToLibrary("As It Was", "Harry Styles", 167);
    station.addSongToLibrary("Bad Guy", "Billie Eilish", 194);
    station.addSongToLibrary("Perfect", "Ed Sheeran", 263);
    station.addSongToLibrary("Believer", "Imagine Dragons", 204);
    station.addSongToLibrary("Levitating", "Dua Lipa", 203);
    station.addSongToLibrary("Flowers", "Miley Cyrus", 200);
    
    station.addSongToLibrary("Starboy", "The Weeknd", 230);
    station.addSongToLibrary("Someone You Loved", "Lewis Capaldi", 182);
    station.addSongToLibrary("Sweater Weather", "The Neighbourhood", 240);
    station.addSongToLibrary("Another One Bites the Dust", "Queen", 215);
    station.addSongToLibrary("Smells Like Teen Spirit", "Nirvana", 301);
    station.addSongToLibrary("Hotel California", "Eagles", 390);
    station.addSongToLibrary("Billie Jean", "Michael Jackson", 294);
    station.addSongToLibrary("In the End", "Linkin Park", 216);
    station.addSongToLibrary("Counting Stars", "OneRepublic", 257);
    station.addSongToLibrary("Wake Me Up", "Avicii", 247);
    
    station.addSongToLibrary("Riptide", "Vance Joy", 204);
    station.addSongToLibrary("Radioactive", "Imagine Dragons", 186);
    station.addSongToLibrary("Stressed Out", "Twenty One Pilots", 202);
    station.addSongToLibrary("Take Me to Church", "Hozier", 241);
    station.addSongToLibrary("Shallow", "Lady Gaga & Bradley Cooper", 215);
    station.addSongToLibrary("Love Yourself", "Justin Bieber", 233);
    station.addSongToLibrary("7 Rings", "Ariana Grande", 178);
    station.addSongToLibrary("Closer", "The Chainsmokers", 244);
    station.addSongToLibrary("Thinking Out Loud", "Ed Sheeran", 281);
    station.addSongToLibrary("Say You Won't Let Go", "James Arthur", 211);
    
    station.addSongToLibrary("Dynamite", "BTS", 199);
    station.addSongToLibrary("Cruel Summer", "Taylor Swift", 178);
    station.addSongToLibrary("Mockingbird", "Eminem", 251);
    station.addSongToLibrary("Without Me", "Eminem", 290);
    station.addSongToLibrary("Lose Yourself", "Eminem", 326);
    station.addSongToLibrary("Till I Collapse", "Eminem", 297);
    station.addSongToLibrary("Numb", "Linkin Park", 185);
    station.addSongToLibrary("Chop Suey!", "System of a Down", 210);
    station.addSongToLibrary("Calm Down", "Rema & Selena Gomez", 239);
    station.addSongToLibrary("Drivers License", "Olivia Rodrigo", 242);
    
    station.addSongToLibrary("Good 4 U", "Olivia Rodrigo", 178);
    station.addSongToLibrary("Heat Waves", "Glass Animals", 235);
    station.addSongToLibrary("Cold Heart", "Elton John & Dua Lipa", 202);
    station.addSongToLibrary("Industry Baby", "Lil Nas X & Jack Harlow", 212);
    station.addSongToLibrary("Montero", "Lil Nas X", 137);
    station.addSongToLibrary("Watermelon Sugar", "Harry Styles", 174);
    station.addSongToLibrary("Circles", "Post Malone", 215);
    station.addSongToLibrary("Sunflower", "Post Malone & Swae Lee", 158);
    station.addSongToLibrary("Rockstar", "Post Malone", 218);
    station.addSongToLibrary("One Dance", "Drake", 174);
}

#endif
