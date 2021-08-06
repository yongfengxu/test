package main
import "fmt"

func f(str string) {
	for i := 0; i < 3; i++ {
		fmt.Println(str, i)
	}
}

func main() {
	f("directional")

	go f("in go routine")

	go func(ss string) {
	    fmt.Println(ss)
	} ("nonName")

	fmt.Scanln()
	fmt.Println("done")
}
