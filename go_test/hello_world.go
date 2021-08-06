package main

import "fmt"

func testArray() {
	fmt.Println("testArray")
	var v [5]int

	v[0] = 10
	v[4] = 1
	fmt.Println("array v is ", v)

	fmt.Println("len of v is", len(v))

	// var v1 []int = []int{1, 2, 3}
	v1 := []int{1, 2, 3}
	fmt.Println("array v1 is ", v1)
	fmt.Println("len of v1 is", len(v1))


}

func main() {

	testArray()

	// var declares 1 or more variables.
	var s1, s2 string = "Charlie go", "lang"
	fmt.Println(s1+s2)

	// declare multiple variables at once
	var i1, i2 int = 1, 2
	fmt.Println("1+2 =", i1 + i2)

	var i3 int
	fmt.Println("i3 = ", i3)

	// Go will infer the type of initialized variables
	var d1, d2 = 7.0, 3.0
	fmt.Println("7.0/3.0 =", d1 / d2)

	var flag1 , flag2 = true, false
	fmt.Println(flag1 && flag2)
	fmt.Println(flag1 || flag2)
	fmt.Println(!flag1)

	shorthand := "hello world!"
	fmt.Println(shorthand)


	i := 1
	for i < 3 {
		fmt.Println(i)
		i++
	}

	for i:=3; i < 5; i++ {
		fmt.Println(i)
	}

	for {
		fmt.Println("hello")
		break
	}

	for i:=0; i < 10; i++ {
		if (i % 2 == 0) {
			fmt.Println(i, "is even")
		} else {
			fmt.Println(i, "is odd")
		}
	}
}
