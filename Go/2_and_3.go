package main

import (
    "fmt"
)

func gcd(a, b int) int {
    for b != 0 {
        a, b = b, a%b
    }
    return a
}

func extendedEuclidean(a, b, m int) int {
    fmt.Println("-------------------------")
    fmt.Println("r \tx \ty \tq")
    fmt.Println("-------------------------")

    x0, x1 := 1, 0
    y0, y1 := 0, 1
    var r, q int

    for b != 0 {
        r = a % b
        q = a / b

        newX := x0 - q*x1
        newY := y0 - q*y1

        fmt.Printf("%d\t%d\t%d\t%d\n", r, newX, newY, q)
        fmt.Println("-------------------------")

        a, b = b, r
        x0, x1 = x1, newX
        y0, y1 = y1, newY
    }

    if x0 < 0 {
        x0 += m
    }

    return x0
}

func main() {
    var c, m int
    fmt.Print("Введите c (число для обратного элемента): ")
    fmt.Scan(&c)
    fmt.Print("Введите m (модуль): ")
    fmt.Scan(&m)

    d := extendedEuclidean(c, m, m)

    fmt.Printf("Обратный элемент d = %d\n", d)
    fmt.Printf("%d^(-1) mod %d = %d\n", c, m, d)
    fmt.Printf("%d*%d mod %d = %d\n", c, d, m, (c*d)%m)
}