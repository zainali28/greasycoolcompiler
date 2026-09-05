#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// constants
#define MAX_FILENAME_LEN 64	// max filename len
#define MIN_FILENAME_LEN 4
#define FILE_EXTENSION_LEN 3	// including the '.'
#define INPUT_ARG_IDX 1
#define OUTPUT_ARG_IDX 2
#define MIN_NUM_VALID_ARGS 2

// return codes
#define ARG_ERR -3
#define FILENAME_ERR -2
#define FAILED	-1
#define SUCCESS 0
#define FILE_EXISTS 1
#define NO_FILE_EXIST 2
#define SPECIAL_CHAR_FOUND 3
#define NO_SPECIAL_CHAR_FOUND 4
#define EXTENSION_VALID 5
#define EXTENSION_INVALID 6

// ascii table reference values
#define ASCII_0 '0'
#define ASCII_9 '9'
#define ASCII_A 'A'
#define ASCII_Z 'Z'
#define ASCII_a	'a'
#define ASCII_z 'z'
#define ASCII_dot '.'

void print_error(int err)
{
	printf("[FAILED] Reason: ");
	switch(err)
	{
		case ARG_ERR:
		{
			printf("Wrong arguements\r\n");
			break;
		}
		
		case FILENAME_ERR:
		{
			printf("Filename error\r\n");
			break;
		}

		case FAILED:
		{
			printf("Failed\r\n");
			break;
		}

		case FILE_EXISTS:
		{
			printf("File already exists\r\n");
			break;
		}

		case NO_FILE_EXIST:
		{
			printf("File does not exist\r\n");
			break;
		}

		case SPECIAL_CHAR_FOUND:
		{
			printf("Special character found\r\n");
			break;
		}

		case NO_SPECIAL_CHAR_FOUND:
		{
			printf("No special character found\r\n");
			break;
		}

		case EXTENSION_VALID:
		{
			printf("Extension valid\r\n");
			break;
		}

		case EXTENSION_INVALID:
		{
			printf("Extension invalid\r\n");
			break;
		}	
		default:
		{
			printf("Unkown\r\n");
			break;
		}	
	}
}


int check_file_exists(char *filename)
{
	// local vars
	int err = FAILED;

	FILE *fptr;

	fptr = fopen(filename, "r");
	if (NULL == fptr)
	{
		goto fail;
	}
	else
	{
		goto pass;
	}

pass:
	return FILE_EXISTS;
fail:
	return NO_FILE_EXIST;
}

int check_special_character(char *str)
{
	// local vars
	char *str_buf = str;
	
	while ('\0' != *str_buf)
	{
		if ( ( (ASCII_0 > *str_buf) && (ASCII_dot != *str_buf) ) || ((ASCII_9 < *str_buf) && (ASCII_A > *str_buf)) || ( (ASCII_Z < *str_buf) && (ASCII_a > *str_buf) ) || (ASCII_z < *str_buf) )
		{
			goto fail;
		}
		else
		{
			str_buf++;
		}
	}

pass:
	return NO_SPECIAL_CHAR_FOUND;

fail:
	return SPECIAL_CHAR_FOUND;
}


int check_input_file_extension(char *filename)
{
	// local vars
	uint8_t file_len = strlen(filename);
	uint8_t ext_idx = file_len - FILE_EXTENSION_LEN;
	
	// check if the extension is there or not
	if ('.' == filename[ext_idx++])
	{
		// check if the extension is valid or not
		if ( ('g' == filename[ext_idx++]) && ('c' == filename[ext_idx++]) )
		{
			// check if this is the complete extension
			if ('\0' == filename[ext_idx])
			{
				goto pass;
			}
			else
			{
				goto fail;
			}

		}
		else
		{
			goto fail;
		}
	}
	else
	{
		goto fail;
	}


fail:
	return EXTENSION_INVALID;

pass:
	return EXTENSION_VALID;
}

int check_input_filename(char *filename)
{
	// local vars
	uint8_t file_len = strlen(filename);
	int err = FAILED;

	// check if it is within bounds
	if ( (MIN_FILENAME_LEN > file_len) ||  (MAX_FILENAME_LEN < file_len) )
	{
		err = FILENAME_ERR;
		goto fail;	
	}	
	else
	{
		;
	}

	// check extension
	err = check_input_file_extension(filename);
	if (EXTENSION_VALID != err)
	{
		goto fail;
	}
	else
	{
		;
	}

	// check for the filename itself for any special characters
	err = check_special_character(filename);
	if (SPECIAL_CHAR_FOUND == err)
	{
		goto fail;
	}
	else
	{
		;
	}
	
	// check if the file exists
	err = check_file_exists(filename);
	if (FILE_EXISTS != err)
	{
		goto fail;
	}	
	else 
	{
		goto pass;
	}

fail:
	return err;
pass:
	return SUCCESS;
}

int check_output_filename(char *filename)
{	
	// local vars
	int err = FAILED;

	// check for the filename itself for any special characters
	err = check_special_character(filename);
	if (SUCCESS != err)
	{
		goto fail;
	}
	else
	{
		;
	}

	// check if the file already exists
	err = check_file_exists(filename);
	if (FILE_EXISTS == err)
	{
		goto fail;
	}
	else
	{
		;
	}
pass:
	return SUCCESS;
fail:
	return err;
}

void set_input_filename(char *input_filename, char *filename)
{
	return;
}

void set_output_filename(char *output_filename, char *input_filename)
{
	return;
}

int main(int argc, char **argv)
{
	// error vars
	int err = FAILED;
	
	// buffer vars
	char input_filename[MAX_FILENAME_LEN];
	char output_filename[MAX_FILENAME_LEN];

	// init buffer vars
	memset(input_filename, '\0', MAX_FILENAME_LEN);
	memset(output_filename, '\0', MAX_FILENAME_LEN);

	// logic vars
	bool output_filename_passed = false;

	// arguement checks
	if ((1 >= argc) || (3 < argc))
	{
		err = ARG_ERR;
		print_error(err);
		return err;
	}
	else if (MIN_NUM_VALID_ARGS == argc)
	{
		printf("[WARN] Didn't pass the second arguement (output file name), will use input file name as output filename...\r\n");
		output_filename_passed = false;
	}
	else
	{
		output_filename_passed = true;
	}

	// check input file name
	err = check_input_filename(argv[INPUT_ARG_IDX]);
	if (SUCCESS != err)
	{
		print_error(err);
		return err;
	}
	else
	{
		;
	}

	// copy the input filename in the local buffer
	set_input_filename(input_filename, argv[INPUT_ARG_IDX]);

	// check output filename if passed as arguement
	if (output_filename_passed)
	{
		err = check_output_filename(argv[OUTPUT_ARG_IDX]);
		if (SUCCESS != err)
		{
			print_error(err);
			return err;
		}
		else
		{
			;
		}
	}
	else
	{
		// set output file name using input file name
		set_output_filename(output_filename, input_filename);
	}
	
	// copy the contents of user input to local vars
	// memcpy(input_file, user_input_file, input_file_len);
	// memcpy(output_file, user_output_file, output_file_len);

	// return exit success
	return SUCCESS;
}
