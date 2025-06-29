package main

import (
    "fmt"
)

// Вычисление цепной дроби для a/b
func computeContinuedFraction(a, b int) []int {
    coefficients := []int{}
    for b != 0 {
        quotient := a / b
        coefficients = append(coefficients, quotient)
        remainder := a % b
        a, b = b, remainder
    }
    return coefficients
}

// Вычисление НОД (алгоритм Евклида)
func computeGCD(a, b int) int {
    for b != 0 {
        a, b = b, a%b
    }
    return a
}

// Вывод компактного решения
func printCompactSolution(aPart, aCoeff, bPart, bCoeff int) {
    var k int
    if aCoeff != 0 && bCoeff != 0 {
        k1 := 0
        if aCoeff != 0 {
            k1 = aPart / aCoeff
        }
        k2 := 0
        if bCoeff != 0 {
            k2 = bPart / bCoeff
        }
        if k1 < k2 {
            k = k1
        } else {
            k = k2
        }
    }
    fmt.Printf("Одно компактное решение: a = %d, b = %d\n", aPart+aCoeff*k, bPart-bCoeff*k)
    fmt.Printf("Общее компактное решение: a = %d + %d*k, b = %d + %d*k, где k - целое число\n",
        aPart+aCoeff*k, aCoeff, bPart-bCoeff*k, bCoeff)
}

// Решение диофантова уравнения
func solveDiophantine(a, b, c int) {
    fraction := computeContinuedFraction(a, b)

    // Инициализация рекуррентных соотношений
    xCurrent, yCurrent := 0, 1
    xPrev, yPrev := 1, 0

    // Вычисление подходящих дробей
    for _, quotient := range fraction {
        xPrev, xCurrent = xCurrent, xPrev-quotient*xCurrent
        yPrev, yCurrent = yCurrent, yPrev-quotient*yCurrent
    }

    gcd := computeGCD(a, b)

    // Проверка существования решения
    if c%gcd != 0 {
        fmt.Println("Уравнение не имеет решений.")
        return
    }

    // Вычисление частного решения
    k := c / gcd
    fmt.Printf("Частное решение: x = %d, y = %d\n", xPrev*k, yPrev*k)

    // Вывод общего решения
    fmt.Printf("Общее решение: x = %d + %d*k, y = %d - %d*k, где k - целое число\n\n",
        xPrev*k, b/gcd, yPrev*k, a/gcd)

    // Вывод компактного решения
    printCompactSolution(xPrev*k, b/gcd, yPrev*k, a/gcd)
}

func main() {
    fmt.Println("Решение уравнения 1256x + 847y = 119\n")
    solveDiophantine(1256, 847, 119)
}