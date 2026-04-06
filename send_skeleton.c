#include <mqueue.h> // allows us to work with message queues (mqd_t new data type to create message queue variables and operations)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // allows us to work with file control options.
		   // O_CREAT, O_WRONLY, O_RDONLY these are flags that specify the operation of 
		   // the file
#include <sys/stat.h> // work with the system call stat() so we can check the status of a file
#include <unistd.h> // allows us to work with system calls such as read() write() fork()

int main() {
    const char *mailbox = "/mailboxA"; // mailbox appended to end of /dev/mqueue
    				      // once we finish code, we should see dev/mqueue/mailboxA

    struct mq_attr mailbox_queue = { 
    	.mq_flags = 0, // set queue to block initially
    	.mq_maxmsg = 5, // holds 5 messages at a time
    	.mq_msgsize = 256, // max size of message
    	.mq_curmsgs = 0 // number of messages currently queued
	     
	      // fill int the four appropriate attributes needed for a mail queue structure
	      
    };
    mqd_t mailq = mq_open(mailbox, O_CREAT | O_WRONLY, 0644, &mailbox_queue); 
    
    /*mq_open will either create our mailbox queue if it doesn't exist already or
    mq_open will open a connection with mailbox queue if it exists
    Also returns a descriptor handled by mailq (mailq kinda becomes our file descriptor)
    Mailbox is name of our mailbox
    O_CREAT is a flag to create queue
    O_WRONLY is used if queue exists, to write only (send message not receieve message 0644)
    User can read and write to /dev/mequeue and group and other can only read
    mailbox_queue is schematics of our queue if it needs to be created */

    if (mailq == (mqd_t)-1) { //can also cast as a mqd_t data type 
	    perror("mq_open error"); 
	    return 1; 
	    // check to see mailbox queue opened correctly
    }

    for (int i = 1; i <= 5; i++) {
        char msg[64];
        
	snprintf(msg, sizeof(msg), "Message %d from PID %d", i, getpid());

        if (mq_send(mailq, msg, strlen(msg), 0) == -1) { 
		perror("mq_send"); 
		break;
		// check if sends correctly, if not, there is an error
		// zero at the end represents priority of the message
		// 0 is lowest priority while 256 is highest priority 
	}
    }
    mq_send(mailq, "term", 4, 0); // 4 is length of message "term" and 0 is the priority level
    mq_close(mailq);
    return 0;
}

