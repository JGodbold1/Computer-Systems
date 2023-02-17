/*-------------------------------------------------------------------------*
 *---									---*
 *---		fileFinder.h						---*
 *---									---*
 *---	    This file declares C functions and constants common to both	---*
 *---	fileFinderClient.c and fileFinderServer.c.			---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//---		Header file inclusion					---//

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>	// For write(), read(), close()
#include	<sys/types.h>	// For opendir(), open()
#include	<dirent.h>	// For opendir(), readdir(), closedir()
#include	<sys/socket.h>	// For socket()
#include	<netinet/in.h>	// For sockaddr_in and htons()
#include	<netdb.h>	// For getaddrinfo()
#include	<errno.h>	// For errno var
#include	<sys/stat.h>	// For open(), read(),write(), stat()
#include	<fcntl.h>	// and close()


//---		Definition of constants:				---//

const int	BUFFER_LEN		= 4096;
