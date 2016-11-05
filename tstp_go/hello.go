package main

import "fmt"

//  comment
/*
	comments
*/
func main() {
	fmt.Println("Hello, 世界")

	var age int = 40
	var favnum float64 = 1.444

	//randNum := 1

	fmt.Println(age, " ", favnum)

	var (
			var1 = 1
			var2 = 3
		)

	fmt.Println(var1, var2)

	var myName string = "goodwill"

		fmt.Println( myName, "\n")

	const pi float64 = 3.14156677

	fmt.Printf("%.4f \n", pi)
	fmt.Printf("%e \n", pi)

	for j:=0; j<5;j++ {
		fmt.Println(j)
	}

	youAge := 16

	if youAge >= 16 {
		fmt.Println("you can drive")

	} else {
		fmt.Println("you cannot drive")
	}
}