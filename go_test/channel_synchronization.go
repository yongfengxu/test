package main
import ("fmt"
	"time")

func worker(channel chan bool) {
	fmt.Println("working...")
	time.Sleep(2)
	fmt.Println("Done")

	channel <- true
}

func main() {
	done := make(chan bool)

	go worker(done)

	<- done

	fmt.Println("Bye")
}
