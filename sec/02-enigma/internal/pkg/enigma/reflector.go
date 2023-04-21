package enigma

import (
	"math/rand"
)

type Reflector struct {
	Transpositions map[byte]byte
}

func GenerateReflector() Reflector {
	r := Reflector{Transpositions: map[byte]byte{}}
	values := MakeRange[byte](0, 255)
	rand.Shuffle(len(values), func(i, j int) { values[i], values[j] = values[j], values[i] })
	for i := 0; i < 255; i += 2 {
		r.Transpositions[values[i]] = values[i+1]
		r.Transpositions[values[i+1]] = values[i]
	}
	return r
}

func (r *Reflector) Transpose(v byte) byte {
	return r.Transpositions[v]
}

func ValidateReflector(r Reflector) bool {
	for i := 0; i <= 255; i++ {
		// fmt.Printf("i = %v, direct = %v, revserse = %v\n", i, x, y)
		x := r.Transpose(byte(i))
		if r.Transpose(x) != byte(i) {
			return false
		}
	}
	return true
}
