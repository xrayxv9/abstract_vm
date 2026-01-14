#pragma once

// INCLUDES
#include <cstdint>
#include <iostream>
#include <vector>
#include <exception>

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
	_exit
} e_commands;

typedef enum {
	INT8 = 0,
	INT16,
	INT32,
	FLOAT,
	DOUBLE,
	null
} e_IO;

// DEFINE
#define STDIN 1
#define FILE_OUT 2

// STRUCT
typedef struct {
	int command;
	std::string cmd_written;
	int io; 
	std::string io_written;
	int value;
} t_command;
