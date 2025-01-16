#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>

#define SHM_KEY 1234

class Prescription {
public:
    std::string prescriptionID;
    int Dosage;

    Prescription(std::string id, int dosage) : prescriptionID(id), Dosage(dosage) {}

    std::string getPrescriptionId() const { return prescriptionID; }
    int getDosage() const { return Dosage; }
};

struct SharedMemory {
    int doses[5];
    int sum;
    bool dataReady;       
    bool serverDone;      
};

void client(int& shmid) {
    SharedMemory* sharedMem = (SharedMemory*)shmat(shmid, nullptr, 0);
    if (sharedMem == (void*)-1) {
        std::cerr << "Client failed to attach to shared memory!" << std::endl;
        exit(1);
    }

    std::vector<Prescription> doss = {
        Prescription("P001", 100),
        Prescription("P002", 200),
        Prescription("P003", 300),
        Prescription("P004", 400),
        Prescription("P005", 500)
    };

    for (int i = 0; i < 5; ++i) {
        sharedMem->doses[i] = doss[i].getDosage();
    }

    std::cout << "Client sent doses: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << sharedMem->doses[i] << " ";
    }
    std::cout << std::endl;

    sharedMem->dataReady = true;

    while (!sharedMem->serverDone) {
        sleep(1);
    }

    std::cout << "Client received sum from server: " << sharedMem->sum << std::endl;

    shmdt(sharedMem);
}

void server(int& shmid) {
    SharedMemory* sharedMem = (SharedMemory*)shmat(shmid, nullptr, 0);
    if (sharedMem == (void*)-1) {
        std::cerr << "Server failed to attach to shared memory!" << std::endl;
        exit(1);
    }

    while (!sharedMem->dataReady) {
        sleep(1);
    }

    std::cout << "Server received doses: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << sharedMem->doses[i] << " ";
    }
    std::cout << std::endl;

    sharedMem->sum = 0;
    for (int i = 0; i < 5; ++i) {
        sharedMem->sum += sharedMem->doses[i];
    }

    std::cout << "Server calculated sum: " << sharedMem->sum << std::endl;

    sharedMem->serverDone = true;

    shmdt(sharedMem);
}

int main() {
    int shmid = shmget(SHM_KEY, sizeof(SharedMemory), 0666 | IPC_CREAT);
    if (shmid == -1) {
        std::cerr << "Shared memory allocation failed!" << std::endl;
        return 1;
    }

    SharedMemory* sharedMem = (SharedMemory*)shmat(shmid, nullptr, 0);
    if (sharedMem == (void*)-1) {
        std::cerr << "Failed to initialize shared memory!" << std::endl;
        return 1;
    }
    sharedMem->dataReady = false;
    sharedMem->serverDone = false;
    shmdt(sharedMem);

    pid_t pid = fork();
    if (pid == 0) {
        server(shmid);
        return 0;
    }

    sleep(1); // Ensure server starts first
    pid = fork();
    if (pid == 0) {
        client(shmid);
        return 0;
    }

    wait(nullptr);
    wait(nullptr);

    shmctl(shmid, IPC_RMID, nullptr);

    return 0;
}
