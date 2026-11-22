
#include <iostream>
#include <string>
using namespace std;

class Song
{
private:
    int songID;
    string songTitle;
    string artistName;
    string albumName;
    string genre;
    float duration;
    string playlist;
    int playCount;
    bool available;

public:

    // Default Constructor
    Song()
    {
        songID = 0;
        songTitle = "Not Set";
        artistName = "Not Set";
        albumName = "Not Set";
        genre = "Not Set";
        duration = 0;
        playlist = "None";
        playCount = 0;
        available = true;
    }

    // Parameterized Constructor
    Song(int id, string title, string artist,
         string album, string g, float d)
    {
        songID = id;
        songTitle = title;
        artistName = artist;
        albumName = album;
        genre = g;
        duration = d;
        playlist = "None";
        playCount = 0;
        available = true;
    }

    // Copy Constructor
    Song(const Song &s)
    {
        songID = s.songID;
        songTitle = s.songTitle;
        artistName = s.artistName;
        albumName = s.albumName;
        genre = s.genre;
        duration = s.duration;
        playlist = s.playlist;
        playCount = s.playCount;
        available = s.available;
    }

    // Destructor
    ~Song()
    {
        cout << "\n   Song object destroyed: " << songTitle;
    }

    // Add Song Record
    void addSong()
    {
        cout << "\nEnter Song ID: ";
        cin >> songID;

        cin.ignore();

        cout << "Enter Song Title: ";
        getline(cin, songTitle);

        cout << "Enter Artist Name: ";
        getline(cin, artistName);

        cout << "Enter Album Name: ";
        getline(cin, albumName);

        cout << "Enter Genre: ";
        getline(cin, genre);

        cout << "Enter Duration (minutes): ";
        cin >> duration;

        playlist = "None";
        playCount = 0;
        available = true;

        cout << "\nSong added successfully!\n";
    }

    // Display Song Details
    void displaySong()
    {
        cout << "\n----- SONG DETAILS -----\n";
        cout << "Song ID      : " << songID << endl;
        cout << "Song Title   : " << songTitle << endl;
        cout << "Artist Name  : " << artistName << endl;
        cout << "Album Name   : " << albumName << endl;
        cout << "Genre        : " << genre << endl;
        cout << "Duration     : " << duration << " minutes" << endl;
        cout << "Playlist     : " << playlist << endl;
        cout << "Play Count   : " << playCount << endl;
        cout << "Availability : " << (available ? "Available" : "Restricted") << endl;
    }

    // Play Song
    void playSong()
    {
        if (available)
        {
            playCount++;
            cout << "\nPlaying: " << songTitle << endl;
            cout << "Total Plays: " << playCount << endl;
        }
        else
        {
            cout << "\nSong is restricted and cannot be played!\n";
        }
    }

    // Add Song to Playlist
    void addToPlaylist()
    {
        cin.ignore();

        cout << "Enter Playlist Name: ";
        getline(cin, playlist);

        cout << "\nSong added to playlist successfully!\n";
    }

    // Remove Song from Playlist
    void removeFromPlaylist()
    {
        playlist = "None";
        cout << "\nSong removed from playlist!\n";
    }

    // Check Availability and Statistics
    void showStatistics()
    {
        cout << "\n----- SONG STATISTICS -----\n";
        cout << "Song Title   : " << songTitle << endl;
        cout << "Availability : " << (available ? "Available" : "Restricted") << endl;
        cout << "Total Plays  : " << playCount << endl;
        cout << "Playlist     : " << playlist << endl;
    }

    // Change Availability
    void changeAvailability()
    {
        available = !available;

        cout << "\nAvailability changed to: " << (available ? "Available" : "Restricted") << endl;
    }

    // Getter for Song ID
    int getID()
    {
        return songID;
    }
};

int main()
{
    Song songs[50];
    int count = 0;
    int choice, id, i;
    
    do
    {
        cout << "\n\n===== ONLINE MUSIC MANAGEMENT SYSTEM =====";
        cout << "\n1. Add New Song";
        cout << "\n2. Display Song Details";
        cout << "\n3. Play a Song";
        cout << "\n4. Add Song to Playlist";
        cout << "\n5. Remove Song from Playlist";
        cout << "\n6. View Availability and Statistics";
        cout << "\n7. Change Song Availability";
        cout << "\n8. Demonstrate Copy Constructor";
        cout << "\n9. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                if (count < 50)
                {
                    songs[count].addSong();
                    count++;
                }
                else
                {
                    cout << "\nDatabase is full!";
                }
                break;

            case 2:
                cout << "\nEnter Song ID: ";
                cin >> id;

                for (i = 0; i < count; i++)
                {
                    if (songs[i].getID() == id)
                    {
                        songs[i].displaySong();
                        break;
                    }
                }
 
                if (i == count)
                    cout << "\nSong not found!";
                break;

            case 3:
                cout << "\nEnter Song ID: ";
                cin >> id;

                for (i = 0; i < count; i++)
                {
                    if (songs[i].getID() == id)
                    {
                        songs[i].playSong();
                        break;
                    }
                }

                if (i == count)
                    cout << "\nSong not found!";
                break;

            case 4:
                cout << "\nEnter Song ID: ";
                cin >> id;

                for (i = 0; i < count; i++)
                {
                    if (songs[i].getID() == id)
                    {
                        songs[i].addToPlaylist();
                        break;
                    }
                }

                if (i == count)
                    cout << "\nSong not found!";
                break;

            case 5:
                cout << "\nEnter Song ID: ";
                cin >> id;

                for (i = 0; i < count; i++)
                {
                    if (songs[i].getID() == id)
                    {
                        songs[i].removeFromPlaylist();
                        break;
                    }
                }

                if (i == count)
                    cout << "\nSong not found!";
                break;

            case 6:
                cout << "\nEnter Song ID: ";
                cin >> id;

                for (i = 0; i < count; i++)
                {
                    if (songs[i].getID() == id)
                    {
                        songs[i].showStatistics();
                        break;
                    }
                }

                if (i == count)
                    cout << "\nSong not found!";
                break;

            case 7:
                cout << "\nEnter Song ID: ";
                cin >> id;

                for (i = 0; i < count; i++)
                {
                    if (songs[i].getID() == id)
                    {
                        songs[i].changeAvailability();
                        break;
                    }
                }

                if (i == count)
                    cout << "\nSong not found!";
                break;

            case 8:
                cout << "\nEnter Song ID: ";
                cin >> id;

                for (i = 0; i < count; i++)
                {
                    if (songs[i].getID() == id)
                    {
                        Song copySong(songs[i]);

                        cout << "\nCopy Constructor Demonstration:";
                        copySong.displaySong();
                        break;
                    }
                }

                if (i == count)
                    cout << "\nSong not found!";
                break;

            case 9:
                cout << "\nExiting Music Management System...";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 9);

    return 0;
}
