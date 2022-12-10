package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func readLines(path string) (*[]int, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()
	var lines []int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		intLine, err := strconv.Atoi(scanner.Text())
		if err != nil {
			return nil, err
		}
		lines = append(lines, intLine)
	}
	return &lines, scanner.Err()
}

func main() {
	measurements, err := readLines("measurements.txt")
	if err != nil {
		log.Fatalf("Error while reading input file: %s", err.Error())
	}

	var increments int
	for i := 1; i < len(*measurements); i++ {
		if (*measurements)[i] > (*measurements)[i-1] {
			increments += 1
		}
	}

	var slidingIncrements int
	for i := 3; i < len(*measurements); i++ {
		if (*measurements)[i]+(*measurements)[i-1]+(*measurements)[i-2] >
			(*measurements)[i-1]+(*measurements)[i-2]+(*measurements)[i-3] {
			slidingIncrements += 1
		}
	}

	fmt.Printf("Number of increments: %d\n", increments)
	fmt.Printf("Number of sliding increments: %d\n", slidingIncrements)
}
