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
    //���������� ������
    char board[maxBoardSize][maxBoardSize], currentString[80];
    int n, successWords = 0, newRow, newColumn, newOrientation, numLetters,
        letters[maxBoardSize * maxBoardSize], letterRow, letterColumn,
        bestCross, bestRow, bestColumn, bestOrientation, bestWord,
        searchWord[maxWords * 10], searchLetterPos[maxWords * 10],
        searchCross[maxWords * 10], boardSize, builds = 0, choice = 0, choice2,
        horizontal[maxWords] = { 0 }, vertical[maxWords] = { 0 }, numWord = 0;
    bool running = true;

    srand(time(NULL));

    //����� �� ������� ���
    while (running) {
        cout << "������ ������� ��� � �������� (�� ����� 25 )";
        cin >> n;
        if (n < 1 || n > 25 || !cin) {//��������
            InputError;
            cin.clear();
            while (cin.get() != '\n');
        }
        else {
            running = false;
        }
    }
    running = true;

    //����� �� ����� ����
    while (running) {
        if (n < 5) {
            cout << "������ ����� ����� (5 - "
                << maxBoardSize - 4 << "): ";
            cin >> boardSize;
            if (boardSize < 5 || boardSize > maxBoardSize - 4 || !cin) { //��������
                InputError;
                cin.clear();
                while (cin.get() != '\n');
            }
            else {
                running = false;
            }
        }
        else if (n > 5) {
            cout << "������ ����� ����� (" << n << "-"
                << maxBoardSize - 4 << "): ";
            cin >> boardSize;
            if (boardSize < n || boardSize > maxBoardSize - 4 || !cin) { //��������
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
    // ���� ������ ��������� ���
    while (successWords != n) {
        builds++;
        //��������� ����������� �������
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++)
                board[i][j] = 0;
        }
        // ������ ��������� ���������������, ���� ������ ������� ����������� �� ���� ����� ������ (�����-2)
        do {
            // ��������� ��������������� ��� �� ������
            for (int i = 0; i < maxWords; i++) {
                int r = rand() % maxWords;
                // �������� �� �� ��������� ������������ � ���������� ����������
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
        // ����� �������� �� ���������� �� �������� (0 ��� 1)
        newOrientation = rand() % 2;
        // ���������� ��������� ������� ����� �� ���������� � ��������� �����. �� ������� � ����������� ��������
        newRow = boardSize / 2 - strlen(words[0]) / 2 * newOrientation;
        // ���������� ��������� ������� ����� �� �������� � ��������� �����. �� ������� � ����������� ��������
        newColumn = boardSize / 2 - strlen(words[0]) / 2 * !newOrientation;
        // ��������� ����� � �������� �����
        addWord(words[0], board, boardSize, newRow, newColumn, newOrientation);
        successWords = 1;
        // ��������� ������� ���� ��������� ����� � ����������� �������#
        numLetters = strlen(words[0]) - 2;

        // ���� ��������� ���
        for (int stop = 0, word = 1; word < n && stop == 0; word++) {
            // �������� �� ������ ��������� ��������� ����
            for (int i = 0; i < numLetters; i++) {
                letters[i] = i;
            }
            // ��������� ������������ ������ ����
            for (int i = 0; i < numLetters; i++) {
                // ������ �� ������� ������� ����
                int t, r = rand() % numLetters;
                // ��� ���� ������� �� ����������� �������� �� �������������
                if (i != r) {
                    t = letters[i];
                    letters[i] = letters[r];
                    letters[r] = t;
                }
            }
            // ������ �������� ������ �������
            bestCross = 0;
            // ����������� �������� �������� � ���������� ������� ����
            for (int letter = 0; letter < numLetters; letter++) {
                letterRow = 0;      // ��������� ����������� ���
                letterColumn = -1;  // ��������� ����������� �������� ���� �� ��� ��������� ����� ���������
                //�������� �����
                for (int i = 0; i <= letters[letter];) {
                    letterColumn++;
                    // �������� ��������� ������� �� �������� �������, �� �������� �� ��������� ���
                    if (letterColumn == boardSize) {
                        letterRow++;
                        letterColumn = 0;
                    }
                    // ���� ������ ����������� �� ������� �� 0, �� �������� ��������
                    if (board[letterRow][letterColumn] != 0 &&
                        board[letterRow][letterColumn] != '#') {
                        i++;
                    }
                }// � ��������� letterRow � letterColumn ���������� ����� letters[letter]
                //������ ������� �������� ������
                checkBestWord(words, board, boardSize, searchWord,
                    searchLetterPos, searchCross, successWords,
                    letterRow, letterColumn, bestCross, bestRow,
                    bestColumn, bestOrientation, bestWord);
            }
            //���� ������ �������� ������ �� ������� ����
            if (bestCross != 0) {
                //���� ����� ����� �� ������� ����������� �����, �� ������ ������������
                if (successWords != bestWord) {
                    tempPtr = words[successWords];
                    words[successWords] = words[bestWord];
                    words[bestWord] = tempPtr;
                    tempPtr = questions[successWords];
                    questions[successWords] = questions[bestWord];
                    questions[bestWord] = tempPtr;
                }
                //������ ����� � �������� �����
                addWord(words[successWords], board, boardSize, bestRow,
                    bestColumn, bestOrientation);
                numLetters += strlen(words[successWords]) - 2 - bestCross;
                successWords++;
            }
            else {
                stop = 1;
            }// ������������ ������ ������� ����� ��������� ���
        }
    }
    // �������� ������ # �� 0 � �������� �������
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == '#')
                board[i][j] = 0;
        }
    }

    for (int i = 2; i < boardSize - 2; i++) {
        for (int j = 2; j < boardSize - 2; j++) {
            //���� � ����� � �� ����������� ��������
            if (board[i][j] != 0 && board[i][j] != '#') {
                if (board[i - 1][j] == 0 && board[i + 1][j] != 0 ||
                    board[i][j - 1] == 0 && board[i][j + 1] != 0) {
                    //������� ����� �����
                    numWord++;
                    //����� �� ��������
                    if (board[i - 1][j] == 0 && board[i + 1][j] != 0) {
                        //������� ������
                        strcpy(currentString, "#");
                        // ��������
                        for (int k = 0; board[i + k][j] != 0; k++) {
                            currentString[k + 1] = board[i + k][j];

                            if (board[i + k + 1][j] == 0) {
                                currentString[k + 2] = '\0';
                            }
                        }
                        //������ ������� �� ������� �����
                        strcat(currentString, "#");

                        for (int word = 0; word < maxWords; word++) {
                            if (strcmp(words[word], currentString) == 0)//��������� ����� � �������� � ����� ������, �� ������.
                                vertical[numWord - 1] = word;//���� ���� ��� - ��������
                        }
                    }
                    // ����� �� ����������
                    if (board[i][j - 1] == 0 && board[i][j + 1] != 0) {
                        //������� ������ 
                        strcpy(currentString, "#");
                        //��������
                        for (int k = 0; board[i][j + k] != 0; k++) {
                            currentString[k + 1] = board[i][j + k];

                            if (board[i][j + k + 1] == 0) {
                                currentString[k + 2] = '\0';
                            }
                        }
                        //������ ������ �� ������� �����
                        strcat(currentString, "#");

                        for (int word = 0; word < maxWords; word++) {
                            if (strcmp(words[word], currentString) == 0) {//��������� ����� � �������� � ����� ������, �� ������.
                                horizontal[numWord - 1] = word;//���� ���� ��� - ��������
                            }
                        }
                    }
                }
            }
        }
    }

    cout << endl << "ʳ������ �������: " << builds << endl;
    //��������� ���� 
    printBoard(words, board, boardSize);
    //��������� ������� ��� ���
    while (choice != 3) {
        while (running) {
            cout << "�������: 1. �����������, 2. ���������, 3. �����: ";
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
        //����� �� ����� �����
        if (choice != 3) {
            //���� ������� ������� ���� ����������
            if (choice == 1) {
                //����� �� ����� �����
                while (running) {
                    cout << "������ ����� ��������� ����������: ";
                    cin >> choice2;
                    //��������
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
                //��������� �����
                printBoard(words, board, boardSize);
                //��������� �������
                cout << "������� " << choice2 << " �� ����������: "
                    << questions[horizontal[choice2 - 1]] << endl;
            }
            running = true;
            //���� ������� ������� ���� ��������
            if (choice == 2) {
                while (running) {
                    cout << "������ ����� ��������� ��������: ";
                    cin >> choice2;
                    //��������
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
                //��������� �����
                printBoard(words, board, boardSize);
                //��������� �������
                cout << "��������� " << choice2 << " �� ��������: "
                    << questions[vertical[choice2 - 1]] << endl;
                running = true;
            }
        }
    }
    //��������� ��������
    printAnswer(words, board, boardSize);

    system("pause");
    return 0;
}

//������� ��������� ����� � �������� �����
void addWord(const char* word, char board[][maxBoardSize], int boardSize,
    int row, int column, int orientation)
{
    //���� �� �������� �����
    for (int i = 0; i < strlen(word); i++) {
        //����� ����� � ����� �� ���������� ��� �� ��������
        board[row + i * orientation][column + i * !orientation] = word[i];
    }
}

//������� �������� ������
void checkBestWord(const char* words[], const char board[][maxBoardSize],
    int boardSize, int searchWords[], int searchLetterPos[],
    int searchCross[], int successWords, int letterRow, int letterColumn,
    int& bestCross, int& bestRow, int& bestColumn, int& bestOrientation,
    int& bestWord)
{   //���������� ������
    int orientation = -1, firstSearch = 0, searchSize = 0, newRow, newColumn,
        letter1, letter2, letter3, lenWord;
    char symbol = board[letterRow][letterColumn], newSymbol, wordSymbol, t, r;
    // ���������� �������� (���� ������ ��� ����� ���� �������)
    if (board[letterRow - 1][letterColumn] != 0 &&
        board[letterRow - 1][letterColumn] != '#' ||
        board[letterRow + 1][letterColumn] != 0 &&
        board[letterRow + 1][letterColumn] != '#') {
        orientation = 0;
    }
    // ���������� �������� (���� ������ ��� �������� ���� �������)
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
    // ������ � ����� ���, �� �������������� �����, �� ��������
    for (int i = successWords; i < maxWords; i++) {
        for (int j = 0; j < strlen(words[i]); j++) {// ���������� ����� ���
            if (words[i][j] == symbol) {// ������ � ����� ������ ���� �� ������
                searchWords[searchSize] = i;//������ �������� ����� �� �������
                searchLetterPos[searchSize] = j;// ������ ����� ���� �� �� �������
                searchCross[searchSize] = 0;
                searchSize++;
            }
        }
    }
    //���� ��������������� 
    for (int i = 0; i < searchSize; i++) {
        r = rand() % searchSize;// ��������� �������� � ��� ������
        if (i != r) {// ��������� ����������
            t = searchWords[i];
            searchWords[i] = searchWords[r];
            searchWords[r] = t;
            t = searchLetterPos[i];
            searchLetterPos[i] = searchLetterPos[r];
            searchLetterPos[r] = t;
        }
    }
    // ���� ���������� � ��������� �� ������ �� ��� ����
    for (int i = 1, stopSearch = 0; (letterRow + i) * orientation +
        (letterColumn + i) * !orientation < boardSize && stopSearch == 0;
        i++) {
        // ���� �� ��������� ������ ��������� �����
        newRow = letterRow + orientation * i;
        newColumn = letterColumn + !orientation * i;
        newSymbol = board[newRow][newColumn];
        // �������� �� ������ ���� �����
        if (newSymbol == 0 || newSymbol == '#') {
            letter1 = 0;
        }
        else {
            letter1 = 1;
        }
        // �������� �� � ����� �� �����
        if (board[newRow - !orientation][newColumn - orientation] == 0 ||
            board[newRow - !orientation][newColumn - orientation] == '#') {
            letter2 = 0;
        }
        else {
            letter2 = 1;
        }
        // ��� ����, ����� � ������ ����
        if (board[newRow + !orientation][newColumn + orientation] == 0 ||
            board[newRow + !orientation][newColumn + orientation] == '#') {
            letter3 = 0;
        }
        else {
            letter3 = 1;
        }
        // ��������� �����, ���� ��������� �� ������� �� ����� �����
        if (letter1 == 0 && (letter2 == 1 || letter3 == 1)) {
            stopSearch = 1;
        }
        // ���� ������ �� �������
        for (int word = firstSearch; word < searchSize; word++) {
            // ��������� ������� ����� �� ��������� ������ ��������
            lenWord = strlen(words[searchWords[word]]);
            if (searchLetterPos[word] + i < lenWord) {
                wordSymbol = words[searchWords[word]]
                    [searchLetterPos[word] + i];
                // ���� �� �������� �� ��� � �� ������� ���� ���
                if (newSymbol != 0 && newSymbol != wordSymbol ||
                    newRow >= boardSize - 1 || newColumn >= boardSize - 1 ||
                    stopSearch == 1 && newSymbol != '#') {
                    t = searchWords[word];//������ ������������ ���������� �����
                    searchWords[word] = searchWords[firstSearch];
                    searchWords[firstSearch] = t;
                    t = searchLetterPos[word];// ������������ �������� �������� �����
                    searchLetterPos[word] = searchLetterPos[firstSearch];
                    searchLetterPos[firstSearch] = t;
                    t = searchCross[word];// ������������ ��������
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
    // ���� ������ �� ������, �� ����������
    for (int i = 0, stopSearch = 0; (letterRow + i) * orientation +
        (letterColumn + i) * !orientation >= 0 && stopSearch == 0;
        i--) {
        // ���� �� ��������� ������ ��������� �����
        newRow = letterRow + orientation * i;
        newColumn = letterColumn + !orientation * i;
        newSymbol = board[newRow][newColumn];
        // �������� �� ������ ���� �����
        if (newSymbol == 0 || newSymbol == '#') {
            letter1 = 0;
        }
        else {
            letter1 = 1;
        }
        // �������� �� � ����� �� �����
        if (board[newRow - !orientation][newColumn - orientation] == 0 ||
            board[newRow - !orientation][newColumn - orientation] == '#') {
            letter2 = 0;
        }
        else {
            letter2 = 1;
        }
        // ��� ����, ����� � ������ ����
        if (board[newRow + !orientation][newColumn + orientation] == 0 ||
            board[newRow + !orientation][newColumn + orientation] == '#') {
            letter3 = 0;
        }
        else {
            letter3 = 1;
        }
        // ��������� �����, ���� ��������� �� ������� �� ����� �����
        if (letter1 == 0 && (letter2 == 1 || letter3 == 1)) {
            stopSearch = 1;
        }
        // ���� ������ �� �������
        for (int word = firstSearch; word < searchSize; word++) {
            // ��������� ������� ����� �� ��������� ������ ��������
            lenWord = strlen(words[searchWords[word]]);

            if (searchLetterPos[word] + i >= 0) {
                wordSymbol = words[searchWords[word]]
                    [searchLetterPos[word] + i];

                if (newSymbol != 0 && newSymbol != wordSymbol ||
                    newRow <= 0 || newColumn <= 0 || stopSearch == 1 &&
                    newSymbol != '#') {
                    t = searchWords[word]; //������ ������������ ���������� �����
                    searchWords[word] = searchWords[firstSearch];
                    searchWords[firstSearch] = t;
                    t = searchLetterPos[word];// ������������ �������� �������� �����
                    searchLetterPos[word] = searchLetterPos[firstSearch];
                    searchLetterPos[firstSearch] = t;
                    t = searchCross[word];// ������������ ��������
                    searchCross[word] = searchCross[firstSearch];
                    searchCross[firstSearch] = t;
                    firstSearch++;
                }
                else {
                    //���� � ����� �������� � ���� �� ������� �������
                    if (newSymbol != 0 && newSymbol != '#') {
                        searchCross[word]++;
                    }
                    if (searchLetterPos[word] + i == 0) {
                        if (searchCross[word] > bestCross) {// ���� �� � ������� ���������
                            //�����'������� �������� �������� 
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

// ������� ��������� ����� �� ������������� �������
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
                if (board[i - 1][j] == 0 && board[i + 1][j] != 0 ||//�������� ��� �� ������� ����� ����� �����
                    board[i][j - 1] == 0 && board[i][j + 1] != 0) {
                    SetConsoleTextAttribute(h, (((4 << 4) | 15)));
                    n++;
                    cout << (n < 10 ? " " : "") << n;
                }
                else {//���������� ����� �����
                    SetConsoleTextAttribute(h, (((4 << 4) | 15)));
                    cout << ' ' << '#';
                }
            }
            else {// ���������� ������� �������� ����
                cout << " .";
            }
        }
        SetConsoleTextAttribute(h, (((0 << 4) | 15)));
        cout << endl;
    }
   
}

// ������� ��������� ����� � �������������� �������
void printAnswer(const char* words[], const char board[][maxBoardSize],
    int boardSize)
{
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 2; i < boardSize - 2; i++) {
        for (int j = 2; j < boardSize - 2; j++) {
            SetConsoleTextAttribute(h, (((15 << 4) | 0)));
            //���� ������� �����, �� ���������� ����
            if (board[i][j] != 0) {
                SetConsoleTextAttribute(h, (((4 << 4) | 15)));
                cout << ' ' << board[i][j];
            }
            //���� �� �������, �� �������� ������
            else {
                cout << " .";
            }
        }
        SetConsoleTextAttribute(h, (((0 << 4) | 15)));
        cout << endl;
    }
}
