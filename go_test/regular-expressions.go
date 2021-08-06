package main

import (
	"bytes"
	"fmt"
	"regexp"
)

func main() {

	match, _ := regexp.MatchString("p([a-z]+)ch", "peach")
	fmt.Println(match)

	r, _ := regexp.Compile("p([a-z]+)ch")

	in := []byte("a peach")
	out := r.ReplaceAllFunc(in, bytes.ToUpper)
	fmt.Println(string(out))

	fmt.Println(r.MatchString("peach"))

	fmt.Println(r.FindString("peach punch peach"))

	fmt.Println(r.FindStringIndex("peach punch"))

	fmt.Println(r.FindStringSubmatch("peach punch"))

	// fmt.Println(r.FindStringSubmatchIndex("peach punch"))

	rawString := "peach punch"
	si := r.FindStringIndex(rawString)

	fmt.Println(rawString[si[0]: si[1]])
	fmt.Println(si)

	si = r.FindStringSubmatchIndex(rawString)
	fmt.Println(rawString[si[0]: si[1]])
	fmt.Println(rawString[si[2]: si[3]])
	fmt.Println(si)



	// fmt.Println(r.FindAllString("peach punch pinch", -1))

	// fmt.Println(r.FindAllStringSubmatchIndex(
	// 	"peach punch pinch", -1))

	// fmt.Println(r.FindAllString("peach punch pinch", 2))

	// fmt.Println(r.Match([]byte("peach")))

	// r = regexp.MustCompile("p([a-z]+)ch")
	// fmt.Println(r)

	// fmt.Println(r.ReplaceAllString("a peach", "<fruit>"))

}
