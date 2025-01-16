#include <iostream>
#include <vector>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <string>

using namespace std;

class Prescription {
private:
    string Prescription_id;
    double Dosage;
public:
    Prescription(string p_id, double p_dosage) : Prescription_id(p_id), Dosage(p_dosage) {}

    double getDosage() { 
        return Dosage; 
    }
};


struct msg_buffer {
    long msg_type;  
    int data[100];  
};

void client(int msgid) {
    vector<Prescription> prescriptions = {
        Prescription("01", 4), 
        Prescription("02", 5), 
        Prescription("03", 6), 
        Prescription("04", 7), 
        Prescription("05", 1)
    };

    int size = prescriptions.size();
    msg_buffer message;

    message.msg_type = 1;  
    message.data[0] = size;  

    
    for (int i = 0; i < size; ++i) {
        message.data[i + 1] = prescriptions[i].getDosage();
    }

    cout << "Client sending dosages: ";
    for (int i = 0; i < size; ++i) {
        cout << message.data[i + 1] << " ";
    }
    cout << endl;

    // Send the dosages message to the server
    msgsnd(msgid, &message, sizeof(message.data), 0);

    // Receive the sum from the server (message type 2)
    msgrcv(msgid, &message, sizeof(message.data), 2, 0);
    
    cout << "Client received sum from server: " << message.data[0] << endl;
}

void server(int msgid) {
    msg_buffer message;

    
    msgrcv(msgid, &message, sizeof(message.data), 1, 0);

    int size = message.data[0];
    int sum = 0;

    cout << "Server received dosages: ";
    for (int i = 0; i < size; i++) {
        cout << message.data[i + 1] << " ";
        sum += message.data[i + 1];
    }
    cout << endl;

    cout << "Server calculated sum: " << sum << endl;

    
    message.msg_type = 2;
    message.data[0] = sum;
    msgsnd(msgid, &message, sizeof(message.data), 0);
}

int main() {
    // Create a message queue
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  
        client(msgid);
        exit(0);
    } else {  
        server(msgid);
        wait(nullptr);  
    }

    
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
