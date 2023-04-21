package enigma

import (
	"math/rand"
)

type Rotor struct {
	Direct   map[byte]byte
	Reverse  map[byte]byte
	Position byte
}

func GenerateRotor() Rotor {
	r := Rotor{Direct: map[byte]byte{}, Reverse: map[byte]byte{}}
	values := MakeRange[byte](0, 255)
	rand.Shuffle(len(values), func(i, j int) { values[i], values[j] = values[j], values[i] })
	for i := 0; i <= 255; i++ {
		r.Direct[byte(i)] = values[i]
		r.Reverse[values[i]] = byte(i)
	}
	r.Position = 0
	return r
}

func (r *Rotor) DirectTranspose(v byte) byte {
	return r.Direct[v]
}

func (r *Rotor) ReverseTranspose(v byte) byte {
	return r.Reverse[v]
}

func ValidateRotor(r Rotor) bool {
	for i := 0; i <= 255; i++ {
		x := r.DirectTranspose(byte(i))
		y := r.ReverseTranspose(x)
		// fmt.Printf("i = %v, direct = %v, revserse = %v\n", i, x, y)
		if y != byte(i) {
			return false
		}
	}
	return true
}
