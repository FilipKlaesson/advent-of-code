package main

import (
	"bufio"
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
	commands, err := readLines("commands.txt")
	if err != nil {
		log.Fatalf("Error while reading input file: %s", err.Error())
	}

	for 
	parts := strings.Fields(someString)

	var horizontal int
	var depth int

	// split on space, find command and update

}
