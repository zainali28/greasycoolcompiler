#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// constants
#define MAX_FILENAME_LEN 64	// max filename len
#define MIN_FILENAME_LEN 4
#define FILE_EXTENSION_LEN 3	// including the '.'
#define INPUT_ARG_IDX 1
#define OUTPUT_ARG_IDX 2
#define MIN_NUM_VALID_ARGS 2

// return codes
#define SUCCESS 0
#define FAILED	-1
#define FILENAME_ERR -2
#define ARG_ERR -3

// ascii table reference values
#define ASCII_0 48
#define ASCII_9 57
#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_a	97
#define ASCII_z 122

int check_special_character(char *str_p)
{
	// local vars
	char *str_buf_p = str_p;
	
	while (*(str_buf_p++) != '\0')
	{
		if ( (ASCII_0 > *str_buf_p) || ((ASCII_9 < *str_buf_p) && (ASCII_A > *str_buf_p)) || ( (ASCII_Z < *str_buf_p) && (ASCII_a > *str_buf_p) ) \
			       || (ASCII_z < *str_buf_p)	)
		{
			goto fail;
		}
		else
		{
			;
		}
	}

pass:
	return SUCCESS;

fail:
	printf("[ERROR] Invalid special characters in the name: %s, exiting...\r\n", str_p);
	return FILENAME_ERR;
}


int check_input_file_extension(char *filename_p)
{
	// local vars
	uint8_t file_len = strlen(filename_p);

	uint8_t ext_idx = file_len - FILE_EXTENSION_LEN;
	
	// check if the extension is there or not
	if ('.' == filename_p[ext_idx++])
	{
		// check if the extension is valid or not
		if ( ('g' == filename_p[ext_idx++]) && ('c' == filename_p[ext_idx++]) )
		{
			// check if this is the complete extension
			if ('\0' == filename_p[ext_idx])
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
	printf("[ERROR] No / invalid extension, exiting...\r\n");
	return FILENAME_ERR;

pass:
	printf("[INFO] Extension verified...\r\n");
	return SUCCESS;
}

int check_input_filename(char *filename_p)
{
	// local vars
	uint8_t file_len = strlen(filename_p);
	int err = FAILED;

	// check if it is within bounds
	if ( (MIN_FILENAME_LEN > file_len) ||  (MAX_FILENAME_LEN < file_len) )
	{
		goto fail;	
	}	
	else
	{
		;
	}
	
	// check for the filename itself for any special characters
	err = check_special_character(filename_p);
	if (err != SUCCESS)
	{
		goto fail;
	}
	else
	{
		;
	}

	// check extension
	err = check_input_file_extension(filename_p);
	if (err != SUCCESS)
	{
		goto fail;
	}
	else
	{
		goto pass;
	}
	
fail:
	printf("[ERROR] Error in input filename, exiting...\r\n");
	return FILENAME_ERR;
pass:
	return SUCCESS;
}

int check_output_filename(char *filename_p)
{
pass:
	return SUCCESS;
}

void set_input_filename(char *input_filename_p, char *filename_p)
{
	return;
}

void set_output_filename(char *output_filename_p, char *input_filename_p)
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
		printf("[ERROR] Invalid number of arguements, exiting...\r\n");
		return ARG_ERR;
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
	if (err != SUCCESS)
	{
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
		if (err != SUCCESS)
		{
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
