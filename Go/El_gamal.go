package main

import (
    "bufio"
    "crypto/rand"
    "encoding/binary"
    "fmt"
    "math"
    "math/big"
    "os"
)

func isPrime(p int) bool {
    if p <= 1 {
        return false
    }
    if p <= 3 {
        return true
    }
    if p%2 == 0 || p%3 == 0 {
        return false
    }
    i := 5
    for i*i <= p {
        if p%i == 0 || p%(i+2) == 0 {
            return false
        }
        i += 6
    }
    return true
}

func gcd(a, b int) int {
    for b != 0 {
        a, b = b, a%b
    }
    return a
}

func aXmodP(a, x, p int) int {
    res := 1
    a = a % p
    for x > 0 {
        if x&1 == 1 {
            res = (res * a) % p
        }
        a = (a * a) % p
        x >>= 1
    }
    return res
}

func mulMod(a, b, n int) int {
    return (a * b) % n
}

func primeFactors(n int) []int {
    factors := []int{}
    if n%2 == 0 {
        factors = append(factors, 2)
        for n%2 == 0 {
            n /= 2
        }
    }
    i := 3
    for i*i <= n {
        for n%i == 0 {
            factors = append(factors, i)
            n /= i
        }
        i += 2
    }
    if n > 2 {
        factors = append(factors, n)
    }
    return factors
}

func isPrimitiveRoot(g, p int) bool {
    if gcd(g, p) != 1 {
        return false
    }
    phi := p - 1
    factors := primeFactors(phi)
    for _, q := range factors {
        if aXmodP(g, phi/q, p) == 1 {
            return false
        }
    }
    return true
}

func randomInt(min, max int) int {
    nBig, _ := rand.Int(rand.Reader, big.NewInt(int64(max-min+1)))
    return int(nBig.Int64()) + min
}

func keysGenerator() (int, int, int, int) {
    var p, g, x, y int
    for {
        p = randomInt(1000, 9999)
        if isPrime(p) {
            break
        }
    }
    for {
        g = randomInt(1, p-1)
        if isPrimitiveRoot(g, p) {
            break
        }
    }
    x = randomInt(1, p-1)
    y = aXmodP(g, x, p)
    return p, g, x, y
}

func crypt(p, g, x, y int, plainData []byte, logFile *os.File) []byte {
    fmt.Fprintf(logFile, "Открытый ключ (p, g, y) = (%d, %d, %d)\n", p, g, y)
    fmt.Fprintf(logFile, "Закрытый ключ x = %d\n\n", x)
    fmt.Fprintf(logFile, "Шифруемые данные (бинарные, %d байт):\n", len(plainData))

    cipherData := make([]byte, 0, len(plainData)*16)
    for i, m := range plainData {
        var k int
        for {
            k = randomInt(1, p-2)
            if gcd(k, p-1) == 1 {
                break
            }
        }
        a := aXmodP(g, k, p)
        b := mulMod(aXmodP(y, k, p), int(m), p)

        aBytes := make([]byte, 8)
        bBytes := make([]byte, 8)
        binary.LittleEndian.PutUint64(aBytes, uint64(a))
        binary.LittleEndian.PutUint64(bBytes, uint64(b))
        cipherData = append(cipherData, aBytes...)
        cipherData = append(cipherData, bBytes...)

        if i < 10 {
            fmt.Fprintf(logFile, "Байт %d (m=%d) → (a=%d, b=%d)\n", i, m, a, b)
        }
    }
    fmt.Fprintf(logFile, "\nЗашифровано %d байт. Размер шифра: %d байт.\n", len(plainData), len(cipherData))
    return cipherData
}

func decrypt(p, x int, cipherData []byte, logFile *os.File) []byte {
    fmt.Fprintln(logFile, "\nДешифрование:")
    decryptedData := make([]byte, 0, len(cipherData)/16)
    for i := 0; i+16 <= len(cipherData); i += 16 {
        a := int(binary.LittleEndian.Uint64(cipherData[i : i+8]))
        b := int(binary.LittleEndian.Uint64(cipherData[i+8 : i+16]))
        m := mulMod(b, aXmodP(a, p-1-x, p), p)
        decryptedData = append(decryptedData, byte(m))
        if i/16 < 10 {
            fmt.Fprintf(logFile, "(a=%d, b=%d) → m=%d\n", a, b, m)
        }
    }
    fmt.Fprintf(logFile, "\nДешифровано %d байт.\n", len(decryptedData))
    return decryptedData
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    fmt.Print("Введите имя файла для шифрования: ")
    inputFilename, _ := reader.ReadString('\n')
    inputFilename = inputFilename[:len(inputFilename)-1]

    plainData, err := os.ReadFile(inputFilename)
    if err != nil {
        fmt.Printf("Ошибка: не удалось открыть файл %s\n", inputFilename)
        return
    }

    p, g, x, y := keysGenerator()

    outFile, _ := os.Create("output.txt")
    defer outFile.Close()
    encFile, _ := os.Create("encrypted.bin")
    defer encFile.Close()
    decFile, _ := os.Create("decrypted.bin")
    defer decFile.Close()

    cipherData := crypt(p, g, x, y, plainData, outFile)
    encFile.Write(cipherData)

    decryptedData := decrypt(p, x, cipherData, outFile)
    decFile.Write(decryptedData)

    fmt.Println("Операция завершена. Результаты сохранены в:\n - encrypted.bin (зашифрованные данные)\n - decrypted.bin (расшифрованные данные)\n - output.txt (лог операции)")
}