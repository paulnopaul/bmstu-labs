package main

import (
	"01-lab1/internal/pkg/key"
	"fmt"
)

func main() {
	err := key.WriteKey()
	if err != nil {
		fmt.Println("Installation failed: ", err)
	} else {
		fmt.Println("Successfull installation")
	}
}
