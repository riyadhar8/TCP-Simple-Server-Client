#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h> 
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define SA struct sockaddr

char *reverse_string(char *string1) {
    
    int len = strlen(string1);

    int left = 0;
    int right = len - 1;
    
    for(int i = left; i < right; i++) {
        char tmp = string1[i];
        string1[i] = string1[right];
        string1[right] = tmp;
        right--;
    }

    return string1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No Port Number specified.\n");
        printf("Server Exiting.\n");
        exit(1);
    }

    int port = atoi(argv[1]);
    printf("Port number: %d\n", port);

    struct sockaddr_in servaddr;
    int sockfd;
    int connectfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("----- Error creating a socket.\n");
        exit(2);
    } else {
        printf("----- Socket created successfully.\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);       //respond to any client
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("----- Could not bind to socket.\n");
        exit(3);
    } else {
        printf("----- Successfully bound.\n");
    }

    if ((listen(sockfd, 1)) < 0) {
        printf("----- Could not listen.\n");
        exit(4);
    } else {
        printf("----- Listening.\n");
    }



    while (1) {
        printf("Waiting for a Client.\n");
        fflush(stdout);

        if ((connectfd = accept(sockfd, (struct sockaddr *)NULL, NULL)) < 0) {
            printf("----- Failed to Connect.\n");
            fflush(stdout);
            continue;
        }

        printf("----- Connected to a Client.\n");
        fflush(stdout);

        
        char sndLine[1024];
        char recLine[1024];

        memset(sndLine, 0, 1024);
        memset(recLine, 0, 1024);

        struct sockaddr_in addr;
        socklen_t addr_len;

        if ((read(connectfd, recLine, sizeof(recLine))) < 0){
            printf("----- Failed to receive.\n");
        } else {
            printf("----- Line received, printing reverse:\n");
            printf("%s\n", reverse_string(recLine));
        }

        fflush(stdout);

        printf("Enter the line that has to be sent: ");
        fgets(sndLine, 1024, stdin);

        for(int i=0; i<1024; i++) {
            if (sndLine[i]=='\n') {
                sndLine[i] = '\0';
                break;
            }
        }

        fflush(stdout);

        if (write(connectfd, sndLine, strlen(sndLine)) < 0) {
            printf("----- Error while Sending to Client.\n");
        } else {
            printf("----- Successfully sent to Client.\n");
        }

        printf("Client has Exited.\n");
        fflush(stdout);
    }
}