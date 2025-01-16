#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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

void client(int shm_id) {
    vector<Prescription> prescriptions = {
        Prescription("01", 4), 
        Prescription("02", 5), 
        Prescription("03", 6), 
        Prescription("04", 7), 
        Prescription("05", 1)
    };

    int size = prescriptions.size();
    int* shared_memory = (int*) shmat(shm_id, NULL, 0);
    if (shared_memory == (void*) -1) {
        perror("Client: shmat failed");
        exit(1);
    }

    // Store the size and dosages in shared memory
    shared_memory[0] = size;
    for (int i = 0; i < size; i++) {
        shared_memory[i + 1] = prescriptions[i].getDosage();
    }

    cout << "Client sending dosages: ";
    for (int i = 0; i < size; ++i) {
        cout << shared_memory[i + 1] << " ";
    }
    cout << endl;

    // Wait for the server to write back the result
    while (shared_memory[0] != -1) {
        sleep(1); // Wait for the server to finish calculation
    }

    cout << "Client received sum from server: " << shared_memory[1] << endl;

    shmdt(shared_memory); // Detach shared memory
}

void server(int shm_id) {
    int* shared_memory = (int*) shmat(shm_id, NULL, 0);
    if (shared_memory == (void*) -1) {
        perror("Server: shmat failed");
        exit(1);
    }

    int size = shared_memory[0];
    int sum = 0;

    cout << "Server received dosages: ";
    for (int i = 0; i < size; i++) {
        cout << shared_memory[i + 1] << " ";
        sum += shared_memory[i + 1];
    }
    cout << endl;

    cout << "Server calculated sum: " << sum << endl;

    // Store the sum in shared memory and signal client by setting size to -1
    shared_memory[1] = sum;
    shared_memory[0] = -1;  // Indicate to client that server is done

    shmdt(shared_memory); // Detach shared memory
}

int main() {
    // Create shared memory segment
    key_t key = ftok("shmfile", 65);
    int shm_id = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  
        client(shm_id);
        exit(0);
    } else {  
        server(shm_id);
        wait(nullptr); 
    }

    
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
