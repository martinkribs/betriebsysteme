// ConsoleZeitUndWarten.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <time.h>
#include <chrono>
#include <string>
#include <thread>
#include < conio.h >

int globalesInt;

void displayTime(void) {
    struct tm newtime;
    __time32_t aclock;

    char buffer[32];
    errno_t errNum;
   

    while (true)
    {
        _time32(&aclock);   // Get time in seconds.
        _localtime32_s(&newtime, &aclock);   // Convert time to struct tm form.

        // Print local time as a string.

        errNum = asctime_s(buffer, 32, &newtime);
        if (errNum)
        {
            printf("Error code: %d", (int)errNum);
            //return 1;
        }
        //printf("Current date and time: %s", buffer);
        std::cout << "Current date and time: " << ((std::string)buffer).substr(0, 24) << "\r";
        //std::cout << "Aktuelle Zeit:" << newTime << "\r";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
}

void waitForInput(void) {
    char input;
    input = _getch();
    if (input == 'x') {
        exit(0);
    }
}

int main()
{
    std::thread first(displayTime);
    std::thread second(waitForInput);

    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
   
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
