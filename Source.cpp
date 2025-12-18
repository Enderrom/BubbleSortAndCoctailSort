#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// сортировка пузырьком
void bubbleSort(vector<int>& sp, int n) {
    bool t = true;
    int i = 0;
    while (t) { // алгоритм работает до тех пор, пока есть смена
        t = false;
        for (int j = 0; j < n - i - 1; j++)
                if (sp[j] > sp[j + 1]) {
                    t = true; // произошла смена элементов, нужно пройти еще раз
                    swap(sp[j], sp[j + 1]);
        }
        i++;
    }
}

// шейкерная сортировка
void coctailShakerSort(vector<int>& sp, int n) {
    bool t = true;
    int start = 0;
    int end = n - 1;
    while (t) { // алгоритм работает до тех пор, пока есть смены
        t = false;
        for (int j = start; j < end; j++)
            if (sp[j] > sp[j + 1]) {
                t = true; // произошла смена элементов, нужно пройти еще раз
                swap(sp[j], sp[j + 1]);
            }

        if (!t) // проверяем, можно ли выйти раньше, чтобы не делать лишние операции
            break;
        t = false;
        end--;

        for (int j = end; j > start; j--)
            if (sp[j] < sp[j - 1]) {
                t = true; // снова нашли неправильный порядок, нужно пройти еще раз
                swap(sp[j], sp[j - 1]);
            }
        start++;
    }
}

int main() {

    int sp[]={10,20,50,100,200,500,1000,2000,5000,10000};
    const int iterations = 10000;
    std::ifstream file("random_numbers.txt");

    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл!" << std::endl;
        return 1;
    }
    for (int i:sp) {
        chrono::nanoseconds t1(0);
        chrono::nanoseconds t2(0);
        for (int j=0;j<iterations;j++) {
            std::string line;
            vector<int> v;
            vector<int> v3;

            getline(file, line);

            std::stringstream ss(line);
            int value;

            while (ss >> value) {
                v.push_back(value);
                v3.push_back(value);
            }
            auto start = chrono::high_resolution_clock::now();
            bubbleSort(v,i);
            auto end = chrono::high_resolution_clock::now();
            t1+=end-start;

            start = chrono::high_resolution_clock::now();
            coctailShakerSort(v3,i);
            end = chrono::high_resolution_clock::now();
            t2+=end-start;
        }
        cout << i << " ";
        double avg1 = t1.count() / 1e9 / iterations; //
        double avg2 = t2.count() / 1e9 / iterations;
        cout << avg1 << " "<< avg2 << endl;
    }

    system("pause");
    
    return 0;
}
