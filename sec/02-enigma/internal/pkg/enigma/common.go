package enigma

func MakeRange[K int | byte](left, right K) []K {
	x := make([]K, int(right)-int(left)+1)
	for i := range x {
		x[i] = left + K(i)
	}
	return x
}

func BoolAnswer(val bool) string {
	if val {
		return "OK"
	}
	return "FAIL"
}
