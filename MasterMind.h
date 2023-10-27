#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "colors.cpp"

using namespace std;

class MastermindGame {

public:

    MastermindGame() : title("MASTERMIND"), difficulty(0)
    {
        srand(time(nullptr));
    }

    void run()
    {
        do {
            displayMenu();
            chooseDifficulty();
        } while (playAgain());
    }

private:

    string title;

    const string difficultyNames[3] = {"Fácil", "Media", "Extrema"};
    const int difficultyAttempts[3] = {12, 10, 8};
    const int difficultyDigits[3] = {3, 4, 5};

    int difficulty;
    int selectedDigits{};
    int userCurrentAttempts{};

    static void drawTitle()
    {
        cout << "\n"
             << "\033[" << Color::FG_RED << "m" <<
             "███╗░░░███╗░█████╗░░██████╗████████╗███████╗██████╗░███╗░░░███╗██╗███╗░░██╗██████╗░\n"
             "████╗░████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗████╗░████║██║████╗░██║██╔══██╗\n"
             "██╔████╔██║███████║╚█████╗░░░░██║░░░█████╗░░██████╔╝██╔████╔██║██║██╔██╗██║██║░░██║\n"
             "██║╚██╔╝██║██╔══██║░╚═══██╗░░░██║░░░██╔══╝░░██╔══██╗██║╚██╔╝██║██║██║╚████║██║░░██║\n"
             "██║░╚═╝░██║██║░░██║██████╔╝░░░██║░░░███████╗██║░░██║██║░╚═╝░██║██║██║░╚███║██████╔╝\n"
             "╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═════╝░\n"
             << "\033[" << Color::FG_DEFAULT << "m" << endl;
    }

    void displayMenu() const
    {
        drawTitle();
        cout << "Selecciona una dificultad:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << " - " << difficultyNames[i] << endl;
        }
    }

    void startGame(int selectedDifficulty)
    {
        selectedDigits = difficultyDigits[selectedDifficulty - 1];
        userCurrentAttempts = difficultyAttempts[selectedDifficulty - 1];
        cout << "\n---------------------------------------" << endl;
        cout << "Has seleccionado la dificultad " << difficultyNames[selectedDifficulty - 1];
        cout << "\n---------------------------------------" << endl;
        int randomNumber = generateRandomNumber(selectedDigits);
        playGame(randomNumber);
    }

    static int generateRandomNumber(int digits)
    {
        int minNumber = 1;
        int maxNumber = 1;
        for (int i = 1; i < digits; i++) {
            minNumber *= 10;
            maxNumber = maxNumber * 10 + 9;
        }
        return minNumber + rand() % (maxNumber - minNumber + 1);
    }

    void playGame(int randomNumber)
    {
        cout << "Adivina el número de " << selectedDigits << " dígitos.\n" << endl;
        while (userCurrentAttempts > 0) {
            int userGuess = getUserGuess();
            if (userGuess == randomNumber) {
                cout << "¡Has adivinado el número!" << endl;
                break;
            } else {
                compareNumbers(userGuess, randomNumber);
            }
        }
        if (userCurrentAttempts == -1) {
            cout << "\033[" << Color::FG_RED << "m";
            cout << "¡Has agotado tus intentos! El número era: " << randomNumber << endl;
            cout << "\033[" << Color::FG_DEFAULT << "m";
        }
    }

    static int getUserGuess()
    {
        int guess;
        cout << "Ingresa tu número: ";
        cin >> guess;
        return guess;
    }

    void compareNumbers(int userGuess, int randomNumber)
    {
        string userGuessStr = to_string(userGuess);
        string randomNumberStr = to_string(randomNumber);

        if (userGuessStr.length() < randomNumberStr.length()) {
            int numbersToAdd = randomNumberStr.length() - userGuessStr.length();
            userGuessStr = string(numbersToAdd, '0') + userGuessStr;
        }

        int correctCount = 0;
        int incorrectCount = 0;

        for (int i = 0; i < selectedDigits; i++) {
            if (userGuessStr[i] == randomNumberStr[i]) {
                correctCount++;
            } else if (randomNumberStr.find(userGuessStr[i]) != string::npos) {
                incorrectCount++;
            }
        }

        userCurrentAttempts--;

        cout << "\n---------------------------------------" << endl;
        cout << "Números en posición correcta: " << correctCount << endl;
        cout << "Números en posición incorrecta: " << incorrectCount << endl;
        cout << "Intentos restantes: " << userCurrentAttempts << endl;
        cout << "--------------------------------------- \n" << endl;
    }

    void chooseDifficulty()
    {
        cout << "Elija una dificultad (1/2/3): ";
        cin >> difficulty;
        if (difficulty >= 1 && difficulty <= 3) {
            startGame(difficulty);
        } else {
            cout << "Opción no válida. Por favor, elija 1, 2 o 3." << endl;
        }
    }

    static bool playAgain()
    {
        char playAgainChoice;
        cout << "¿Quieres jugar otra partida? (S/N): ";
        cin >> playAgainChoice;
        return (playAgainChoice == 'S' || playAgainChoice == 's');
    }

};
