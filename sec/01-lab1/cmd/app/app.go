package main

import (
	"01-lab1/internal/pkg/key"
	"fmt"
)

/*
1. Режим инсталлятора
2. В режиме программы
встроить в них одну и ту же библиотеку,
которая привязывается к какой-то характеристике ПК
В качестве параметров для привязки использовать
использовать постоянные легче.
Параметры:
- постоянные (хардварные характеристики)
- переменные (генерация ключей и их проверка)
Критерии характеристики для привязки:
- уникальность
- постоянность
- неизменность
- доступность
*/

func main() {
	checkRes, _ := key.CheckKey()
	if !checkRes {
		fmt.Println("App not installed! Install it")
	} else {
		fmt.Println("Successfull run!")
	}
}
