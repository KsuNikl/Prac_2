#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "func.h"

using namespace std;

int main() {
    srand(time(NULL));

    // Запрос имени файла
    string inputFilename;
    cout << "Введите имя файла для шифрования: ";
    cin >> inputFilename;

    // Генерация ключей
    auto [p, g, x, y] = KeysGenerator();

    // Открытие файлов
    ifstream inFile(inputFilename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка: не удалось открыть файл " << inputFilename << endl;
        return 1;
    }

    ofstream outFile("output.txt");
    ofstream encFile("encrypted.bin", ios::binary);
    ofstream decFile("decrypted.bin", ios::binary);

    // Чтение исходного файла
    vector<unsigned char> plainData(
        (istreambuf_iterator<char>(inFile)),
        istreambuf_iterator<char>()
    );
    inFile.close();

    // Шифрование
    vector<unsigned char> cipherData;
    crypt(p, g, x, y, plainData, cipherData, outFile);
    encFile.write(reinterpret_cast<const char*>(cipherData.data()), cipherData.size());
    encFile.close();

    // Имитация атаки "человек посередине" - генерация нового x
    x = get<2>(KeysGenerator());

    // Дешифрование
    vector<unsigned char> decryptedData;
    decrypt(p, x, cipherData, decryptedData, outFile);
    decFile.write(reinterpret_cast<const char*>(decryptedData.data()), decryptedData.size());
    decFile.close();

    // Проверка
    outFile << "\nПроверка: ";
    if (plainData == decryptedData) {
        outFile << "Успешно! Данные совпадают." << endl;
    } else {
        outFile << "Ошибка! Данные не совпадают." << endl;
    }

    outFile.close();
    
    cout << "Операция завершена. Результаты сохранены в:\n"
         << " - encrypted.bin (зашифрованные данные)\n"
         << " - decrypted.bin (расшифрованные данные)\n"
         << " - output.txt (лог операции)\n";

    return 0;
}