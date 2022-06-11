//#define_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "windows.h"
#include "WQlist.h"
#include "Functions.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const char* tempPtr;
    const char* words[maxWords] = slovar;
    const char* questions[maxWords] = qtoslovar;
    //Оголошення змінних
    char board[maxBoardSize][maxBoardSize], currentString[80];
    int n, successWords = 0, newRow, newColumn, newOrientation, numLetters,
        letters[maxBoardSize * maxBoardSize], letterRow, letterColumn,
        bestCross, bestRow, bestColumn, bestOrientation, bestWord,
        searchWord[maxWords * 10], searchLetterPos[maxWords * 10],
        searchCross[maxWords * 10], boardSize, builds = 0, choice = 0, choice2,
        horizontal[maxWords] = { 0 }, vertical[maxWords] = { 0 }, numWord = 0;
    bool running = true;

    srand(time(NULL));

    //запит на кількість слів
    while (running) {
        cout << "Введіть кількість слів у кросворді (не більше 25 )";
        cin >> n;
        if (n < 1 || n > 25 || !cin) {//перевірка
            InputError;
            cin.clear();
            while (cin.get() != '\n');
        }
        else {
            running = false;
        }
    }
    running = true;

    //запит на розмір поля
    while (running) {
        if (n < 5) {
            cout << "Введіть розмір дошки (5 - "
                << maxBoardSize - 4 << "): ";
            cin >> boardSize;
            if (boardSize < 5 || boardSize > maxBoardSize - 4 || !cin) { //перевірка
                InputError;
                cin.clear();
                while (cin.get() != '\n');
            }
            else {
                running = false;
            }
        }
        else if (n > 5) {
            cout << "Введіть розмір дошки (" << n << "-"
                << maxBoardSize - 4 << "): ";
            cin >> boardSize;
            if (boardSize < n || boardSize > maxBoardSize - 4 || !cin) { //перевірка
                InputError;
                cin.clear();
                while (cin.get() != '\n');
            }
            else {
                running = false;
            }
        }
    }

    running = true;
    boardSize += 4;
    // цикл підбору комбінації слів
    while (successWords != n) {
        builds++;
        //Початкова ініціалізація матриці
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++)
                board[i][j] = 0;
        }
        // робимо випадкове перетасовування, поки перший елемент гарантовано не буде більше розмірів (дошки-2)
        do {
            // випадкове перетасовування слів та питань
            for (int i = 0; i < maxWords; i++) {
                int r = rand() % maxWords;
                // перевірка на не виконання перестановки з однаковими елементами
                if (i != r) {
                    tempPtr = words[i];
                    words[i] = words[r];
                    words[r] = tempPtr;
                    tempPtr = questions[i];
                    questions[i] = questions[r];
                    questions[r] = tempPtr;
                }
            }
        } while (strlen(words[0]) > boardSize - 2);
        // слово рандомно по горизонталі чи вертикалі (0 або 1)
        newOrientation = rand() % 2;
        // Визначення початкової позиції слова по горизонталі у вихідному масиві. По середині з урахуванням напрямку
        newRow = boardSize / 2 - strlen(words[0]) / 2 * newOrientation;
        // Визначення початкової позиції слова по вертикалі у вихідному масиві. По середині з урахуванням напрямку
        newColumn = boardSize / 2 - strlen(words[0]) / 2 * !newOrientation;
        // додавання слова у вихідний масив
        addWord(words[0], board, boardSize, newRow, newColumn, newOrientation);
        successWords = 1;
        // Визначаємо кількість букв внесеного слова з урахуванням маркера#
        numLetters = strlen(words[0]) - 2;

        // цикл генерації слів
        for (int stop = 0, word = 1; word < n && stop == 0; word++) {
            // заносимо до масиву початкову нумерацію букв
            for (int i = 0; i < numLetters; i++) {
                letters[i] = i;
            }
            // Випадково перетасовуємо номери букв
            for (int i = 0; i < numLetters; i++) {
                // рандом за модулем кількості букв
                int t, r = rand() % numLetters;
                // при збігу рандому та початкового значення не переставляємо
                if (i != r) {
                    t = letters[i];
                    letters[i] = letters[r];
                    letters[r] = t;
                }
            }
            // прапор успішного підбору скидаємо
            bestCross = 0;
            // проходимося вихідною матрицею і перевіряємо кількість букв
            for (int letter = 0; letter < numLetters; letter++) {
                letterRow = 0;      // Початкова ініціалізація ряд
                letterColumn = -1;  // Початкова ініціалізація стовпець тому що йде інкремент перед перевіркою
                //лічильник циклу
                for (int i = 0; i <= letters[letter];) {
                    letterColumn++;
                    // Перевірка закінчення стовпця за розмірами матриці, що перейшли на наступний ряд
                    if (letterColumn == boardSize) {
                        letterRow++;
                        letterColumn = 0;
                    }
                    // якщо символ відрізняється від маркера та 0, то збільшуємо лічильник
                    if (board[letterRow][letterColumn] != 0 &&
                        board[letterRow][letterColumn] != '#') {
                        i++;
                    }
                }// у результаті letterRow і letterColumn координати літери letters[letter]
                //робимо функцію успішного підбору
                checkBestWord(words, board, boardSize, searchWord,
                    searchLetterPos, searchCross, successWords,
                    letterRow, letterColumn, bestCross, bestRow,
                    bestColumn, bestOrientation, bestWord);
            }
            //якщо прапор успішного підбору не дорівнює нулю
            if (bestCross != 0) {
                //якщо вдале слово не дорівнює підсумковому слову, то робимо перестановку
                if (successWords != bestWord) {
                    tempPtr = words[successWords];
                    words[successWords] = words[bestWord];
                    words[bestWord] = tempPtr;
                    tempPtr = questions[successWords];
                    questions[successWords] = questions[bestWord];
                    questions[bestWord] = tempPtr;
                }
                //додаємо слово у вихідний масив
                addWord(words[successWords], board, boardSize, bestRow,
                    bestColumn, bestOrientation);
                numLetters += strlen(words[successWords]) - 2 - bestCross;
                successWords++;
            }
            else {
                stop = 1;
            }// Встановлюємо прапор зупинки циклу генерації слів
        }
    }
    // Замінюємо маркер # на 0 у вихідний матриці
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == '#')
                board[i][j] = 0;
        }
    }

    for (int i = 2; i < boardSize - 2; i++) {
        for (int j = 2; j < boardSize - 2; j++) {
            //якщо є слово і не зафарбовано маркером
            if (board[i][j] != 0 && board[i][j] != '#') {
                if (board[i - 1][j] == 0 && board[i + 1][j] != 0 ||
                    board[i][j - 1] == 0 && board[i][j + 1] != 0) {
                    //ставимо номер слова
                    numWord++;
                    //ідемо по вертикалі
                    if (board[i - 1][j] == 0 && board[i + 1][j] != 0) {
                        //копіюємо маркер
                        strcpy(currentString, "#");
                        // Перевірка
                        for (int k = 0; board[i + k][j] != 0; k++) {
                            currentString[k + 1] = board[i + k][j];

                            if (board[i + k + 1][j] == 0) {
                                currentString[k + 2] = '\0';
                            }
                        }
                        //додаємо маркери за розміром слова
                        strcat(currentString, "#");

                        for (int word = 0; word < maxWords; word++) {
                            if (strcmp(words[word], currentString) == 0)//порівнюємо рядок зі словника з нашим рядком, що вийшов.
                                vertical[numWord - 1] = word;//якщо вони рівні - записуємо
                        }
                    }
                    // йдемо по горизонталі
                    if (board[i][j - 1] == 0 && board[i][j + 1] != 0) {
                        //копіюємо маркер 
                        strcpy(currentString, "#");
                        //перевірка
                        for (int k = 0; board[i][j + k] != 0; k++) {
                            currentString[k + 1] = board[i][j + k];

                            if (board[i][j + k + 1] == 0) {
                                currentString[k + 2] = '\0';
                            }
                        }
                        //додаємо маркер за розміром слова
                        strcat(currentString, "#");

                        for (int word = 0; word < maxWords; word++) {
                            if (strcmp(words[word], currentString) == 0) {//порівнюємо рядок зі словника з нашим рядком, що вийшов.
                                horizontal[numWord - 1] = word;//якщо вони рівні - записуємо
                            }
                        }
                    }
                }
            }
        }
    }

    cout << endl << "Кількість побудов: " << builds << endl;
    //виведення поля 
    printBoard(words, board, boardSize);
    //Виведення питання для слів
    while (choice != 3) {
        while (running) {
            cout << "Виберіть: 1. Горизонталь, 2. Вертикаль, 3. Вихід: ";
            cin >> choice;
            if (choice != 1 && choice != 2 && choice != 3 || !cin) {
                InputError;
                cin.clear();
                while (cin.get() != '\n');;
            }
            else {
                running = false;
            }
        }
        running = true;
        //запит на номер слова
        if (choice != 3) {
            //якщо вибрали питання щодо горизонталі
            if (choice == 1) {
                //запит на номер слова
                while (running) {
                    cout << "Введіть номер запитання горизонталі: ";
                    cin >> choice2;
                    //перевірка
                    if (choice2 < 1 || choice2 > n ||
                        horizontal[choice2 - 1] == 0 || !cin) {
                        InputError;
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else {
                        running = false;
                    }
                }
                //виведення дошки
                printBoard(words, board, boardSize);
                //Виведення питання
                cout << "Питання " << choice2 << " по горизонталі: "
                    << questions[horizontal[choice2 - 1]] << endl;
            }
            running = true;
            //якщо вибрали питання щодо вертикалі
            if (choice == 2) {
                while (running) {
                    cout << "Введіть номер запитання вертикалі: ";
                    cin >> choice2;
                    //перевірка
                    if (choice2 < 1 || choice2 > n ||
                        vertical[choice2 - 1] == 0 || !cin) {
                        InputError;
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else {
                        running = false;
                    }
                }
                //виведення дошки
                printBoard(words, board, boardSize);
                //Виведення питання
                cout << "Запитання " << choice2 << " по вертикалі: "
                    << questions[vertical[choice2 - 1]] << endl;
                running = true;
            }
        }
    }
    //Виведення відповідей
    printAnswer(words, board, boardSize);

    system("pause");
    return 0;
}

//функція додавання слова у вихідний масив
void addWord(const char* word, char board[][maxBoardSize], int boardSize,
    int row, int column, int orientation)
{
    //цикл за довжиною слова
    for (int i = 0; i < strlen(word); i++) {
        //запис слова в масив по горизонталі або по вертикалі
        board[row + i * orientation][column + i * !orientation] = word[i];
    }
}

//функція успішного підбору
void checkBestWord(const char* words[], const char board[][maxBoardSize],
    int boardSize, int searchWords[], int searchLetterPos[],
    int searchCross[], int successWords, int letterRow, int letterColumn,
    int& bestCross, int& bestRow, int& bestColumn, int& bestOrientation,
    int& bestWord)
{   //Оголошення змінних
    int orientation = -1, firstSearch = 0, searchSize = 0, newRow, newColumn,
        letter1, letter2, letter3, lenWord;
    char symbol = board[letterRow][letterColumn], newSymbol, wordSymbol, t, r;
    // Визначення орієнтації (якщо зверху або знизу немає символів)
    if (board[letterRow - 1][letterColumn] != 0 &&
        board[letterRow - 1][letterColumn] != '#' ||
        board[letterRow + 1][letterColumn] != 0 &&
        board[letterRow + 1][letterColumn] != '#') {
        orientation = 0;
    }
    // Визначення орієнтації (якщо ліворуч або праворуч немає символів)
    if (board[letterRow][letterColumn - 1] != 0 &&
        board[letterRow][letterColumn - 1] != '#' ||
        board[letterRow][letterColumn + 1] != 0 &&
        board[letterRow][letterColumn + 1] != '#') {
        if (orientation == -1)
            orientation = 1;
        else
            orientation = -1;
    }

    if (orientation == -1)
        return;
    // шукаємо у масиві слів, не використовуючи слова, які вставили
    for (int i = successWords; i < maxWords; i++) {
        for (int j = 0; j < strlen(words[i]); j++) {// перебираємо решту слів
            if (words[i][j] == symbol) {// шукаємо в інших словах збіги за буквою
                searchWords[searchSize] = i;//додамо знайдене слово за масивом
                searchLetterPos[searchSize] = j;// додамо букву збігу за її номером
                searchCross[searchSize] = 0;
                searchSize++;
            }
        }
    }
    //цикл перетасовування 
    for (int i = 0; i < searchSize; i++) {
        r = rand() % searchSize;// випадково вибираємо з усіх пошуків
        if (i != r) {// випадково перетасуємо
            t = searchWords[i];
            searchWords[i] = searchWords[r];
            searchWords[r] = t;
            t = searchLetterPos[i];
            searchLetterPos[i] = searchLetterPos[r];
            searchLetterPos[r] = t;
        }
    }
    // цикл підстановки з перевіркою не виходу за межі поля
    for (int i = 1, stopSearch = 0; (letterRow + i) * orientation +
        (letterColumn + i) * !orientation < boardSize && stopSearch == 0;
        i++) {
        // пішли на наступний символ підібраного слова
        newRow = letterRow + orientation * i;
        newColumn = letterColumn + !orientation * i;
        newSymbol = board[newRow][newColumn];
        // Перевірка на маркер кінця слова
        if (newSymbol == 0 || newSymbol == '#') {
            letter1 = 0;
        }
        else {
            letter1 = 1;
        }
        // дивимося чи є поруч ще літера
        if (board[newRow - !orientation][newColumn - orientation] == 0 ||
            board[newRow - !orientation][newColumn - orientation] == '#') {
            letter2 = 0;
        }
        else {
            letter2 = 1;
        }
        // Теж саме, тільки з іншого боку
        if (board[newRow + !orientation][newColumn + orientation] == 0 ||
            board[newRow + !orientation][newColumn + orientation] == '#') {
            letter3 = 0;
        }
        else {
            letter3 = 1;
        }
        // зупиняємо пошук, якщо потрапили на початок чи кінець слова
        if (letter1 == 0 && (letter2 == 1 || letter3 == 1)) {
            stopSearch = 1;
        }
        // цикл підбору за розміром
        for (int word = firstSearch; word < searchSize; word++) {
            // визначаємо довжину слова за знайденою літерою перетину
            lenWord = strlen(words[searchWords[word]]);
            if (searchLetterPos[word] + i < lenWord) {
                wordSymbol = words[searchWords[word]]
                    [searchLetterPos[word] + i];
                // якщо не виходимо за краї і не маркери кінця слів
                if (newSymbol != 0 && newSymbol != wordSymbol ||
                    newRow >= boardSize - 1 || newColumn >= boardSize - 1 ||
                    stopSearch == 1 && newSymbol != '#') {
                    t = searchWords[word];//робимо перестановку знайденого слова
                    searchWords[word] = searchWords[firstSearch];
                    searchWords[firstSearch] = t;
                    t = searchLetterPos[word];// Перестановка знайденої загальної літери
                    searchLetterPos[word] = searchLetterPos[firstSearch];
                    searchLetterPos[firstSearch] = t;
                    t = searchCross[word];// Перестановка перетину
                    searchCross[word] = searchCross[firstSearch];
                    searchCross[firstSearch] = t;
                    firstSearch++;
                }
                else if (newSymbol != 0 && newSymbol != '#') {
                    searchCross[word]++;
                }
            }
        }
    }
    // цикл підбору по літерах, що залишилися
    for (int i = 0, stopSearch = 0; (letterRow + i) * orientation +
        (letterColumn + i) * !orientation >= 0 && stopSearch == 0;
        i--) {
        // пішли на наступний символ підібраного слова
        newRow = letterRow + orientation * i;
        newColumn = letterColumn + !orientation * i;
        newSymbol = board[newRow][newColumn];
        // Перевірка на маркер кінця слова
        if (newSymbol == 0 || newSymbol == '#') {
            letter1 = 0;
        }
        else {
            letter1 = 1;
        }
        // дивимося чи є поруч ще літера
        if (board[newRow - !orientation][newColumn - orientation] == 0 ||
            board[newRow - !orientation][newColumn - orientation] == '#') {
            letter2 = 0;
        }
        else {
            letter2 = 1;
        }
        // Теж саме, тільки з іншого боку
        if (board[newRow + !orientation][newColumn + orientation] == 0 ||
            board[newRow + !orientation][newColumn + orientation] == '#') {
            letter3 = 0;
        }
        else {
            letter3 = 1;
        }
        // зупиняємо пошук, якщо потрапили на початок чи кінець слова
        if (letter1 == 0 && (letter2 == 1 || letter3 == 1)) {
            stopSearch = 1;
        }
        // цикл підбору за розміром
        for (int word = firstSearch; word < searchSize; word++) {
            // визначаємо довжину слова за знайденою літерою перетину
            lenWord = strlen(words[searchWords[word]]);

            if (searchLetterPos[word] + i >= 0) {
                wordSymbol = words[searchWords[word]]
                    [searchLetterPos[word] + i];

                if (newSymbol != 0 && newSymbol != wordSymbol ||
                    newRow <= 0 || newColumn <= 0 || stopSearch == 1 &&
                    newSymbol != '#') {
                    t = searchWords[word]; //робимо перестановку знайденого слова
                    searchWords[word] = searchWords[firstSearch];
                    searchWords[firstSearch] = t;
                    t = searchLetterPos[word];// Перестановка знайденої загальної літери
                    searchLetterPos[word] = searchLetterPos[firstSearch];
                    searchLetterPos[firstSearch] = t;
                    t = searchCross[word];// Перестановка перетину
                    searchCross[word] = searchCross[firstSearch];
                    searchCross[firstSearch] = t;
                    firstSearch++;
                }
                else {
                    //якщо є буква перетину і вона не дорівнює маркеру
                    if (newSymbol != 0 && newSymbol != '#') {
                        searchCross[word]++;
                    }
                    if (searchLetterPos[word] + i == 0) {
                        if (searchCross[word] > bestCross) {// якщо ще є кількість комбінацій
                            //Запам'ятовуємо підсумкові значення 
                            bestCross = searchCross[word];
                            bestRow = letterRow + orientation * i;
                            bestColumn = letterColumn + !orientation * i;
                            bestOrientation = orientation;
                            bestWord = searchWords[word];
                        }
                    }
                }
            }
        }
    }
}

// функція виведення дошки із зашифрованими словами
void printBoard(const char* words[], const char board[][maxBoardSize],
    int boardSize)
{
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    int n = 0;
    for (int i = 2; i < boardSize - 2; i++) {
        for (int j = 2; j < boardSize - 2; j++) {
            SetConsoleTextAttribute(h, (((15 << 4) | 0)));
            if (board[i][j] != 0 && board[i][j] != '#') {
                if (board[i - 1][j] == 0 && board[i + 1][j] != 0 ||//нумерція слів за рахунок першої літери слова
                    board[i][j - 1] == 0 && board[i][j + 1] != 0) {
                    SetConsoleTextAttribute(h, (((4 << 4) | 15)));
                    n++;
                    cout << (n < 10 ? " " : "") << n;
                }
                else {//зашифровка решти слова
                    SetConsoleTextAttribute(h, (((4 << 4) | 15)));
                    cout << ' ' << '#';
                }
            }
            else {// Заповнення порожніх осередків поля
                cout << " .";
            }
        }
        SetConsoleTextAttribute(h, (((0 << 4) | 15)));
        cout << endl;
    }
   
}

// Функція виведення дошки з розшифрованими словами
void printAnswer(const char* words[], const char board[][maxBoardSize],
    int boardSize)
{
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 2; i < boardSize - 2; i++) {
        for (int j = 2; j < boardSize - 2; j++) {
            SetConsoleTextAttribute(h, (((15 << 4) | 0)));
            //якщо знайшли слово, то виведенням його
            if (board[i][j] != 0) {
                SetConsoleTextAttribute(h, (((4 << 4) | 15)));
                cout << ' ' << board[i][j];
            }
            //якщо не знайшли, то виводимо крапку
            else {
                cout << " .";
            }
        }
        SetConsoleTextAttribute(h, (((0 << 4) | 15)));
        cout << endl;
    }
}
