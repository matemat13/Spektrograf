#include "include/debug_exit.hpp"

void exit_message(const char* error_message, int error)
{
	// Print an error message
	//OutputDebugString(TEXT(error_message));
	OutputDebugString(TEXT("\n"));
	
	
	// Exit the program
	if (false)
	 exit(error);
}