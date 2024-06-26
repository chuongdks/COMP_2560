/* rlsd.c - a remote ls server - with paranoia
 */
#include  <stdio.h>
#include  <unistd.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <netdb.h>
#include  <time.h>
#include  <strings.h>
#include  <stdlib.h>
#include  <ctype.h>
/*
Usage: ./rls IP_addr ~directory
The server listens for connections and handles directory listing requests from clients.
The client connects to the server, sends a directory name, and receives the directory listing from the server.
*/
#define   PORTNUM  15000   /* our remote ls server port */
#define   HOSTLEN  256
#define   oops(msg)      { perror(msg) ; exit(1) ; }

void sanitize(char *str);

int main(int ac, char *av[])
{
	struct  sockaddr_in		saddr;		/* build our address here */
	struct	hostent			*hp;   		/* this is part of our    */
	char	hostname[HOSTLEN];     		/* address 	         */
	int		sock_id,sock_fd;       		/* line id, file desc     */
	FILE	*sock_fpi,		*sock_fpo;	/* streams for in and out */
	FILE	*pipe_fp;	       			/* use popen to run ls    */
	char    dirname[BUFSIZ];       		/* from client            */
	char    command[BUFSIZ];       		/* for popen()            */
	int		dirlen, c;

    /** Step 1: ask kernel for a socket **/
	sock_id = socket( PF_INET, SOCK_STREAM, 0 );    /* get a socket */
	if ( sock_id == -1 )
	{
		oops( "socket" );
	}


    /** Step 2: bind address to socket.  Address is host,port **/
	// https://www.youtube.com/watch?v=sMnmQuLzoks
	bzero( (void *)&saddr, sizeof(saddr) ); /* clear out struct     */
	gethostname( hostname, HOSTLEN );       /* where am I ?         */
	hp = gethostbyname( hostname );         /* get info about host  */
	bcopy( (void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(PORTNUM);        /* fill in socket port  */
	saddr.sin_family = AF_INET ;            /* fill in addr family  */

	if ( bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0 )
	{
	    oops( "bind" );
	}

    /** Step 3: allow incoming calls with Qsize=1 on socket **/
	if ( listen(sock_id, 1) != 0 ) 
	{
		oops( "listen" );
	}

	/*
	* main loop: accept(), write(), close()
	*/
	while ( 1 )
	{
		// 4. Accept. Successful if client connect, return value is a Client Socket Descriptor
		/* wait for call */
		if ( (sock_fd = accept(sock_id, NULL, NULL)) == -1 )
		{
			oops("accept");  
		}

		// 5. Read/Write
		/* open reading direction as buffered stream, bind File Pointer to File Descriptor*/
		if( (sock_fpi = fdopen(sock_fd,"r")) == NULL ) // use fdopen on Socket Descriptor to turn in to File Pointer to use Standard IO stuff
		{
			oops("fdopen reading");
		}

		// Read data from "sock_fpi" and store it in "dirname"
		if (fgets(dirname, BUFSIZ-5, sock_fpi) == NULL)
		{
			oops("reading dirname");
		}

		sanitize(dirname);

		/* open writing direction as buffered stream, bind File Pointer to File Descriptor */
		if ( (sock_fpo = fdopen(sock_fd,"w")) == NULL ) // use fdopen on Socket Descriptor to turn in to File Pointer to use Standard IO stuff
		{
			oops("fdopen writing");
		}
 
		// Add "ls" before the "dirname" and store it in "command"
		sprintf(command,"ls %s", dirname);
		// Read stuff from the cmd shell "command" (data from ls) and store it in pipe_fp ???
		if ( (pipe_fp = popen(command, "r")) == NULL ) 
		{
			oops("popen");
		}

		/* Write data from "ls" to socket */
		while( (c = getc(pipe_fp)) != EOF ) // Read from "pipe_fp"
		{
			putc(c, sock_fpo); // Write to 
		}
		pclose(pipe_fp);
		fclose(sock_fpo);
		fclose(sock_fpi);
    }
}

void sanitize(char *str)
/*
 * it would be very bad if someone passed us an dirname like
 * "; rm *"  and we naively created a command  "ls ; rm *"
 *
 * so..we remove everything but slashes and alphanumerics
 * There are nicer solutions, see exercises
 */
{
	char *src, *dest;

	for ( src = dest = str ; *src ; src++ )
		if ( *src == '/' || isalnum(*src) )
			*dest++ = *src;
	*dest = '\0';
}
