package main

import (
    "bufio"
    "fmt"
    "math"
    "os"
    "strconv"
    "strings"
)

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

func aXmodP(a, x, p int) int {
    degree := x % (p - 1)
    if x == 0 {
        degree = 1
    }
    result := 1
    for i := 0; i < degree; i++ {
        result = (result * a) % p
    }
    return result
}

func decToBin(number int) []int {
    binNumbers := []int{}
    for number != 0 {
        binNumbers = append(binNumbers, number%2)
        number /= 2
    }
    return binNumbers
}

func aXmodPviaLog(a, x, p int) int {
    if x == 0 {
        return 1 % p
    }
    if p == 1 {
        return 0
    }
    maxPowerOfTwo := int(math.Ceil(math.Log2(float64(x))))
    if 1<<maxPowerOfTwo < x {
        maxPowerOfTwo++
    }
    rowOfAs := []int{}
    for i := 0; i <= maxPowerOfTwo; i++ {
        exponent := 1 << i
        rowOfAs = append(rowOfAs, aXmodP(a, exponent, p))
    }
    binX := decToBin(x)
    result := 1
    for i := 0; i < len(binX); i++ {
        if i < len(rowOfAs) && binX[i] == 1 {
            result = (result * rowOfAs[i]) % p
        }
    }
    return result
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    fmt.Print("Введите первое число и его степень через пробел: ")
    line1, _ := reader.ReadString('\n')
    line1 = strings.TrimSpace(line1)
    parts1 := strings.Split(line1, " ")
    a1, _ := strconv.Atoi(parts1[0])
    x1, _ := strconv.Atoi(parts1[1])

    fmt.Print("Введите второе число и его степень через пробел: ")
    line2, _ := reader.ReadString('\n')
    line2 = strings.TrimSpace(line2)
    parts2 := strings.Split(line2, " ")
    a2, _ := strconv.Atoi(parts2[0])
    x2, _ := strconv.Atoi(parts2[1])

    fmt.Print("Введите модуль: ")
    line3, _ := reader.ReadString('\n')
    line3 = strings.TrimSpace(line3)
    p, _ := strconv.Atoi(line3)

    if !isPrime(p) {
        fmt.Println("Ошибка, p должно быть простым")
        return
    }

    result1 := aXmodPviaLog(a1, x1, p)
    result2 := aXmodPviaLog(a2, x2, p)

    if result1 == result2 {
        fmt.Printf("%d**%d mod %d == %d**%d mod %d\n", a1, x1, p, a2, x2, p)
    } else {
        fmt.Printf("%d**%d mod %d != %d**%d mod %d\n", a1, x1, p, a2, x2, p)
    }
}