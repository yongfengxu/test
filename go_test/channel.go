package main
import "fmt"

func ping(channel chan string, str string) {
	fmt.Println("send", str, "to chan", channel)
	channel <- str
	fmt.Println(str, "sent to chan", channel)
}

func main() {
	// By default channels are unbuffered, meaning that they will only accept sends (chan <-) if there is a corresponding receive (<- chan) ready to receive the sent value. Buffered channels accept a limited number of values without a corresponding receiver for those values.
	// messages := make(chan string)

	messages := make(chan string, 3)

	// go func() {messages <- "ping"}()

	go ping(messages, "ping")

	msg := <- messages

	fmt.Println(msg)

	go ping(messages, "ping again")

	fmt.Scanln()

	msg = <- messages

	fmt.Println(msg)
	fmt.Println("done")
	fmt.Scanln()
	fmt.Println("done")
}
