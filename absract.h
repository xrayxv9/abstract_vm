#pragma once

// INCLUDES
#include <cstdint>
#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <cstddef>
#include <ostream>
#include <string>

// ENUM
typedef enum {
	push = 0,
	pop,
	dump,
	assert,
	add,
	sub,
	mul,
	_div,
	mod,
	print,
	_exit,
	nullCommand,
} e_commands;

typedef enum {
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double,
	nullOperand
} eOperandType;

typedef enum {
	plus = 0,
	minus,
	divide,
	modulus,
	mult,
} calculChar;



// DEFINE
#define STDIN 1
#define FILE_OUT 2
#define ERROR_IN 3

// STRUCT
typedef struct {
	e_commands command;
	std::string cmd_written;
	eOperandType io; 
	std::string io_written;
	std::string value;
} t_command;
