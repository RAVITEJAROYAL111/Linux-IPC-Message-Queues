#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

// Message structure
struct message {
    long type;
    char text[100];
};

int main() {
    key_t key = ftok(".", 'a');

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    struct message msg;
    msg.type = 1;

    strcpy(msg.text, "monish");

    // Send message
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s\n", msg.text);

    return 0;
}
