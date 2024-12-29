#include <iostream>
#include <vector>
#include <set>

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

int main() {
    // Исходная функция (8 значений)
    vector<int> initial_func = {1, 0, 0, 0, 0, 0, 0, 0};

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

        // Вывод всех комбинаций текущей итерации
        cout << "Current combinations:" << endl;
        for (const auto& combination : combinations) {
            for (const auto& vec : combination) {
                cout << "[";
                for (int val : vec) {
                    cout << val << " ";
                }
                cout << "] ";
            }
            cout << endl;
        }

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

        // Вывод всех уникальных функций текущей итерации
        cout << "Unique functions after this iteration:" << endl;
        for (const auto& uf : uniqueFunctions) {
            for (int val : uf) {
                cout << val << " ";
            }
            cout << endl;
        }

        // Перегенерация комбинаций с учётом новых функций
        combinations = generateAllCombinations(x1, x2, generatedFunctions);
    }

    // Вывод всех уникальных функций
    cout << "All unique functions:" << endl;
    for (const auto& uf : uniqueFunctions) {
        for (int val : uf) {
            cout  <<  val << " ";
        }
        cout << endl;
    }

    return 0;
}