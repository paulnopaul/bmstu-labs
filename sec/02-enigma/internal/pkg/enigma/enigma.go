package enigma

import (
	"fmt"
	"math/rand"
	"time"
)

// Enigma Reflector <-> R[2] <-> R[1] <-> R[0] <-> *message*
type Enigma struct {
	Reflector Reflector
	Rotors    [3]Rotor
}

func NewEnigma() Enigma {
	fmt.Println("Enigma generating start...")
	rand.Seed(int64(time.Now().Nanosecond()))

	e := Enigma{}
	for i := 0; i < 3; i++ {
		r := GenerateRotor()
		fmt.Printf("Rotor #%v validate: %s\n", i+1, BoolAnswer(ValidateRotor(r)))
		e.Rotors[i] = r
	}
	refl := GenerateReflector()
	fmt.Println("Reflector validate: ", BoolAnswer(ValidateReflector(refl)))
	e.Reflector = refl
	fmt.Println("Successfull enigma generation!")
	return e
}

func (e *Enigma) Reset() {
	for i := 0; i < len(e.Rotors); i++ {
		e.Rotors[i].Position = 0
	}
}

func (e *Enigma) Encrypt(v []byte) []byte {
	res := make([]byte, len(v))
	for i, value := range v {
		res[i] = e.encrypt(value)
	}
	return res
}

func (e *Enigma) encrypt(v byte) byte {
	for i := 0; i < len(e.Rotors); i++ {
		v = e.Rotors[i].DirectTranspose(v)
	}
	v = e.Reflector.Transpositions[v]
	for i := len(e.Rotors) - 1; i >= 0; i-- {
		v = e.Rotors[i].ReverseTranspose(v)
	}
	e.rotate()
	return v
}

func (e *Enigma) rotate() {
	var remainder byte
	remainder = 1
	for i := 0; i < len(e.Rotors) && remainder != 0; i++ {
		e.Rotors[i].Position += remainder
		if e.Rotors[i].Position == 0 {
			remainder = 1
		} else {
			remainder = 0
		}
	}
}
