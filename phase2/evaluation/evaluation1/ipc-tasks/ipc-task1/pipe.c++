#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <string>
#include <climits>

using namespace std;

class Prescription{
    private: 
    
    string PrescriptionID;
    int Dosage;

    public: 
    
    Prescription(string p_id,int p_dosage):PrescriptionID(p_id),Dosage(p_dosage) {}

    int getDosageValue() {
        return Dosage;
    }
};


void client(int clientEnd) {
    int n;
    cout << "Enter the number of prescriptions : ";
    cin >> n;
    
    vector<Prescription> prescriptions;
    
    for (int i=0;i<n;i++) {
        string id;
        int dosage;
        
        cout << "Enter Prescription ID : ";
        cin >> id;
        
        cout << "Enter Dosage : ";
        cin >> dosage;
        
        
        prescriptions.emplace_back(id, dosage);
    }
    
    
    write(clientEnd,&n,sizeof(n));

    for (auto curr : prescriptions) {
        
        int dosage =curr.getDosageValue();
        
        write(clientEnd,&dosage,sizeof(dosage));
    }
    close(clientEnd); 
}

void server(int serverEnd){
    int n;
    
    read(serverEnd,&n,sizeof(n));
    
    int sum=0;
    
    for (int i=0;i<n;i++) {
        
        int dosage;
        
        read(serverEnd,&dosage,sizeof(dosage));
        
        sum += dosage;
    }
    
    cout <<"The server is received The sum of dosages : " << sum << endl;
    
    close(serverEnd); 
}

int main() {
    int pipefd[2];
    
    if (pipe(pipefd) == -1) {
        perror("error");
        return 1;
    }
    
    {
        pid_t pid = fork();
        
        if (pid == -1){
            perror("error");
            return 1;
        }
        
        if (pid == 0){
            close(pipefd[0]); 
            client(pipefd[1]);
            return 0;
        }
        
    }

    close(pipefd[1]); 
    server(pipefd[0]);


    return 0;
}
