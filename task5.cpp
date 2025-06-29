#include <iostream>
#include <vector>

using namespace std;

// Вычисление цепной дроби для a/b
vector<int> ComputeContinuedFraction(int a, int b) {
    vector<int> coefficients;
    while (b != 0) {
        int quotient = a / b;
        coefficients.push_back(quotient);
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return coefficients;
}

// Алгоритм Евклида для нахождения НОД
int ComputeGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Вывод компактного решения
void PrintCompactSolution(int a_part, int a_coeff, int b_part, int b_coeff) {
    int k = (a_part / a_coeff < b_part / b_coeff) ? 
             a_part / a_coeff : b_part / b_coeff;

    cout << "Одно компактное решение: a = " << a_part + (a_coeff * k) 
         << ", b = " << b_part + (-b_coeff * k) << endl;

    cout << "Общее компактное решение: a = " << a_part + (a_coeff * k) << " + " 
         << a_coeff << " * k, b = " << b_part + (-b_coeff * k) << " + " 
         << b_coeff << " * k, где k - целое число" << endl;
}

// Решение диофантова уравнения ax + by = c
void SolveDiophantine(int a, int b, int c) {
    vector<int> fraction = ComputeContinuedFraction(a, b);
    
    // Инициализация рекуррентных соотношений
    int x_current = 0, y_current = 1;
    int x_prev = 1, y_prev = 0;
    
    // Вычисление подходящих дробей
    for (int quotient : fraction) {
        int x_temp = x_current;
        x_current = x_prev - quotient * x_current;
        x_prev = x_temp;
        
        int y_temp = y_current;
        y_current = y_prev - quotient * y_current;
        y_prev = y_temp;
    }

    int gcd = ComputeGCD(a, b);
    
    // Проверка существования решения
    if (c % gcd != 0) {
        cout << "Уравнение не имеет решений." << endl;
        return;
    }
    
    // Вычисление частного решения
    int k = c / gcd;
    cout << "Частное решение: x = " << x_prev * k << ", y = " << y_prev * k << endl;
    
    // Вывод общего решения
    cout << "Общее решение: x = " << x_prev * k << " + " << b/gcd << " * k, "
         << "y = " << y_prev * k << " - " << a/gcd << " * k, где k - целое число" << endl << endl;

    // Вывод компактного решения
    PrintCompactSolution(x_prev * k, b/gcd, y_prev * k, a/gcd);
}

int main() {
    cout << "Решение уравнения 1256x + 847y = 119" << endl << endl;
    SolveDiophantine(1256, 847, 119);

    return 0;
}