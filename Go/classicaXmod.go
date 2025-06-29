package main

import (
    "bufio"
    "fmt"
    "math"
    "os"
    "strconv"
    "strings"
)

func aXmodP(a, x, p int) int {
    degree := x % (p - 1)
    result := 1
    for i := 0; i < degree; i++ {
        result = (result * a) % p
    }
    return result
}

func gcd(a, b int) int {
    for b != 0 {
        a, b = b, a%b
    }
    return a
}

func isPrime(p int) bool {
    if p%2 == 0 || p%3 == 0 || p <= 1 {
        return false
    }
    squareRootN := int(math.Sqrt(float64(p))) + 1
    maxI := (squareRootN + 1) / 6
    for i := 1; i < maxI; i++ {
        dividerMinusOne := 6*i - 1
        dividerPlusOne := 6*i + 1
        if dividerMinusOne <= squareRootN && p%dividerMinusOne == 0 {
            return false
        }
        if dividerPlusOne <= squareRootN && p%dividerPlusOne == 0 {
            return false
        }
    }
    return true
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    fmt.Print("Введите первое число и его степень через пробел: ")
    line1, _ := reader.ReadString('\n')
    parts1 := strings.Fields(line1)
    a1, _ := strconv.Atoi(parts1[0])
    x1, _ := strconv.Atoi(parts1[1])

    fmt.Print("Введите второе число и его степень: ")
    line2, _ := reader.ReadString('\n')
    parts2 := strings.Fields(line2)
    a2, _ := strconv.Atoi(parts2[0])
    x2, _ := strconv.Atoi(parts2[1])

    fmt.Print("Введите модуль p: ")
    line3, _ := reader.ReadString('\n')
    p, _ := strconv.Atoi(strings.TrimSpace(line3))

    if !isPrime(p) {
        fmt.Println("\nМодуль не является простым числом, попробуйте другой. Модуль обязательно должен быть > 0!")
        return
    }

    if aXmodP(a1, x1, p) == aXmodP(a2, x2, p) {
        fmt.Printf("%d**%d mod %d == %d**%d mod %d\n", a1, x1, p, a2, x2, p)
    } else {
        fmt.Printf("%d**%d mod %d != %d**%d mod %d\n", a1, x1, p, a2, x2, p)
    }
}