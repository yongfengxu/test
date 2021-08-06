package main

import "fmt"

func main() {

	m := make(map[string]string)
	m["a1"] = "a"
	m["b2"] = "bb"

	fmt.Println(m)
	fmt.Println("len of map m", len(m))

	delete(m, "b2")

	fmt.Println("after deleting key b2, len of map m", len(m))

	v1 := m["a1"]
	fmt.Println(v1)

	v2 := m["b2"]
	fmt.Println(v2)

	v3, present := m["a1"]
	fmt.Println("v3=", v3, ",present", present)

	_, present = m["a2"]
	fmt.Println("present", present)

}


