#include <sys/types.h> 
#include <sys/stat.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <vector>

using namespace std;

class Prescription {
private:
    string PrescriptionId;
    int Dosage;

public:
    Prescription(string PrescriptionId, int dosage) : PrescriptionId(PrescriptionId), Dosage(dosage) {}

    int getDosage() {
        return Dosage;
    }
};

int main() {
    vector<Prescription> doses;
    doses.emplace_back("p001", 100);
    doses.emplace_back("p002", 200);
    doses.emplace_back("p003", 300);
    doses.emplace_back("p004", 400);
    doses.emplace_back("p005", 500);

    int Dosages[doses.size()] = {0};

    for (int i = 0; i < doses.size(); i++) {
        Dosages[i] = doses[i].getDosage();
    }

    int numOfElements = doses.size();

    const char* pipe1 = "pipe1";
    const char* pipe2 = "pipe2";
    int pipe_two_read_fd, pipe_one_write_fd;
    pipe_one_write_fd = open(pipe1, O_WRONLY);
    pipe_two_read_fd = open(pipe2, O_RDONLY);

    if (pipe_one_write_fd == -1) {
        perror("pipe1 open failure at client");
        return 1;
    }
    if (pipe_two_read_fd == -1) {
        perror("pipe2 open failure at client");
        return 1;
    }

    write(pipe_one_write_fd, &numOfElements, sizeof(int));
    cout << "Client sent number of elements: " << numOfElements << endl;

    write(pipe_one_write_fd, Dosages, sizeof(Dosages));
    cout << "Client sent test Dosages: ";
    for (int Dosage : Dosages) {
        cout << Dosage << "\t";
    }
    cout << endl;
    close(pipe_one_write_fd);

    sleep(1);

    int sum;
    read(pipe_two_read_fd, &sum, sizeof(int));
    cout << "Sum received from server: " << sum << endl;

    close(pipe_two_read_fd);

    return 0;
}
