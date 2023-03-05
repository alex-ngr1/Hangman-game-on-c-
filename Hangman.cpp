#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include<chrono>

using namespace std;
using namespace std::chrono;

// Ограничение на количество попыток
const int MAX_WRONG = 7;

// Слова для игры
vector<string> words {"GUESS", "HANGMAN", "DIFFICULT", "ANSWER", "XYLOPHONE"};
// const string ENCRYPTED_WORDS = "R2VzdA==\nSExJU1M=\nRElGRklDVFQ=\nQU5TV0VSLA==\nWFlMT1BPTEg=";

long long getCurrentTime()
{
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}



void drawHangman(int wrong) {
    // Отображаем структуру виселицы
    cout << "__________" << endl;
    cout << "|         |" << endl;
    cout << "|         ";
    
    // Отображаем тело повешенного человека
    if (wrong >= 1) cout << "O";
    if (wrong >= 2) cout << endl << "|        /";
    if (wrong >= 3) cout << "|";
    if (wrong >= 4) cout << "\\";
    if (wrong >= 5) cout << endl << "|        ";
    if (wrong >= 6) cout << "/";
    if (wrong >= 7) cout << " \\";
    
    // Отображаем оставшееся пространство
    cout << endl << "|" << endl << "|" << endl << "|" << endl << endl;
}


int main() {
    int start_time, end_time;
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(words.begin(), words.end());
    const string THE_WORD = words[0];
    int wrong = 0;
    string soFar(THE_WORD.size(), '-');
    string used = "";
    cout << "Добро пожаловать в игру \"Весильница\". Удачи вам!\n";
    start_time = time(nullptr);

    while ((wrong < MAX_WRONG) && (soFar != THE_WORD)) {
        cout << "\n\nОшибки: " << wrong << " из " << MAX_WRONG << endl;
        cout << "Неправильно использованные буквы: " << used << endl;
        cout << "Текущее слово: " << soFar << endl;
        cout << "Введите букву: ";
        char guess;
        cin >> guess;
        guess = toupper(guess);
        while (used.find(guess) != string::npos) {
            cout << "Вы уже использовали букву " << guess << endl;
            cout << "Введите другую букву: ";
            cin >> guess;
            guess = toupper(guess);
        }
        used += guess;
        if (THE_WORD.find(guess) != string::npos) {
            cout << "Буква " << guess << " найдена в слове!\n";
            for (int i = 0; i < THE_WORD.size(); ++i) {
                if (THE_WORD[i] == guess) {
                    soFar[i] = guess;
                }
            }
        } else {
            cout << "Буква " << guess << " не найдена в слове.\n";
            ++wrong;
            drawHangman(wrong); // выводим часть весельницы
        }
    }

    if (wrong == MAX_WRONG) {
        cout << "\nВы проиграли! Загаданное слово было: " << THE_WORD << endl;
        end_time = time(nullptr);
        double time_taken = difftime(end_time, start_time);
        cout<<"Вы потратили: " << time_taken << " Секунд на игру:" << endl;
        
    } else {
        cout << "\nВы выиграли! Загаданное слово было: " << THE_WORD << endl;
        end_time = time(nullptr);
        double time_taken = difftime(end_time, start_time);
        cout<<"Вы потратили: " << time_taken << "Секунд на игру:" << endl;
    }

    return 0;
}
