package main

import (
	"02-enigma/internal/pkg/enigma"
	"fmt"
)

func main() {
	e := enigma.NewEnigma()
	cyp := e.Encrypt([]byte("hello"))
	fmt.Println(cyp)
	e.Reset()
	cyp = e.Encrypt(cyp)
	fmt.Println(cyp)
	fmt.Println(string(cyp))
}
