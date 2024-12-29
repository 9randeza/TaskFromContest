#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

// Функция для генерации всех возможных комбинаций
vector<vector<vector<int>>> generateAllCombinations(const vector<int>& var1, const vector<int>& var2, const vector<vector<int>>& generatedFunctions) {
    vector<vector<vector<int>>> combinations;

    // Общее количество источников
    vector<vector<int>> allSources = {var1, var2};
    allSources.insert(allSources.end(), generatedFunctions.begin(), generatedFunctions.end());

    int totalSources = allSources.size();

    // Генерация всех комбинаций (каждая позиция может брать значение из любого источника)
    for (int i = 0; i < totalSources; ++i) {
        for (int j = 0; j < totalSources; ++j) {
            for (int k = 0; k < totalSources; ++k) {
                vector<vector<int>> combination = {allSources[i], allSources[j], allSources[k]};
                combinations.push_back(combination);
            }
        }
    }

    return combinations;
}

// Функция для вычисления новых функций
vector<int> f(const vector<int>& func, const vector<int>& x1_vals, const vector<int>& x2_vals, const vector<int>& x3_vals, set<vector<int>>& uniqueFunctions) {
    vector<int> ch;

    for (int i = 0; i < 4; ++i) {
        int x1 = x1_vals[i];
        int x2 = x2_vals[i];
        int x3 = x3_vals[i];
        int index = (x1 << 2) | (x2 << 1) | x3;
        ch.push_back(func[index]);
    }

    if (uniqueFunctions.find(ch) == uniqueFunctions.end()) {
        uniqueFunctions.insert(ch);
        return ch;
    } else {
        return {};
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./program <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return 1;
    }

    // Чтение входного файла
    int k, numVariables;
    string funcString;
    inputFile >> k >> numVariables >> funcString;

    if (k <= 1) {
        cerr << "Error: k must be greater than 1." << endl;
        return 1;
    }

    vector<int> initial_func;
    for (char c : funcString) {
        if (c >= '0' && c < '0' + k) {
            initial_func.push_back(c - '0');
        } else {
            cerr << "Error: Function values must be in the range [0, k-1]." << endl;
            return 1;
        }
    }


    // Изначальные векторы переменных
    vector<int> x1 = {0, 0, 1, 1};
    vector<int> x2 = {0, 1, 0, 1};

    // Хранилище всех уникальных функций
    set<vector<int>> uniqueFunctions;

    // Вектор для хранения всех порождённых функций
    vector<vector<int>> generatedFunctions;

    // Первая итерация: генерируем комбинации только для x1 и x2
    vector<vector<vector<int>>> combinations = generateAllCombinations(x1, x2, {});

    // Начинаем цикл вычисления функций
    bool changed = true;
    while (changed) {
        changed = false;
        vector<vector<int>> newFunctions; // Для временного хранения новых уникальных функций

        // Обработка каждой комбинации
        for (const auto& combination : combinations) {
            vector<int> ch = f(initial_func, combination[0], combination[1], combination[2], uniqueFunctions);
            if (!ch.empty()) {
                newFunctions.push_back(ch);
                changed = true;
            }
        }

        // Добавляем новые функции к порождённым
        for (const auto& func : newFunctions) {
            generatedFunctions.push_back(func);
        }

        // Перегенерация комбинаций с учётом новых функций
        combinations = generateAllCombinations(x1, x2, generatedFunctions);
    }
    // Запись всех уникальных функций в выходной файл
    for (const auto& uf : uniqueFunctions) {
        outputFile << 2 << " " << 2 << " " ;
        for (int val : uf) {
            outputFile << val;
        }
        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
