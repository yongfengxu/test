package main

import "fmt"

func findPos(slice []int, value int) int {
	for ind, v := range slice {
		if v == value {
			return ind
		}
	}
	return -1;
}

func main() {
	fmt.Println("test range")

	nums := []int{1, 2, 3, 4, 5}
	var sum int

	for _,num := range nums {
		fmt.Println(num)
		sum += num
	}

	fmt.Println("sum is ", sum)

	p3 := findPos(nums, 3)
	fmt.Println("the position of 3 in nums is", p3)

}
