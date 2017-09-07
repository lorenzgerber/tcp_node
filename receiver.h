/*
 * File: receiver.h
 *
 * Date:        2017-08-27
 *
 */
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <net/if.h>
#include <math.h>
#include "messages.h"
#include "election.h"
#define BUF_SIZE 100
#define NI_MAXHOST 1025
#define NI_MAXSERV 32
#ifndef __RECEIVER
#define __RECEIVER

typedef struct host {
	char *name;
	int *port;
}host;

typedef struct dataContainer {
	host ** host;
	char ** sendBuffer;
	int *finished;
	int **gotMessage;
	int **mode;
}dataContainer;

// global mutex lock
extern pthread_mutex_t mtx_lock;

/* Sets up a socket for receiving messages for the program
 * @param arg   hostController of the program.
 * @returned    void pointer (needed to end the thread)
 */
void *receiver_init(void *arg);
/* Will receive and print to the host, uses protocol UDP.
 * @param   ht      The host of the program
 * @param   sfd     The socket it will receive data to.
 */
void receiver_listenUDP(host *ht, int sfd);
/* Will receive and print messages to the host, uses protocol TCP.
 * @param   ht      The host of the program
 * @param   sfd     The socket it will receive data to.
 */
void receiver_listenTCP(dataContainer *ht, int sfd);


char* getCurrentId(char* sendPort);

#endif
