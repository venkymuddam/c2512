#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

class Prescription {
    friend class PrescriptionManager;
    private: 
        string PrescriptionID;
        int Dosage;
    public: 
        bool GreaterThan(const Prescription& other);
        bool LessThan(const Prescription& other);
        string GetPrescriptionId();
        int GetDosage();
};

class PrescriptionManager {
    friend class PrescriptionAggregator;
    friend int main();
    private:
        vector<Prescription> prescriptions; 
    public:
        int findIndexById(const string& PrescriptionID);
        void create();
        void displayAll();
        void editById();
        void deleteById();
};

class PrescriptionAggregator {
    public:
        int findMin(PrescriptionManager& prescription_obj1);
        int findMax(PrescriptionManager& prescription_obj1);
        int findSecondMin(PrescriptionManager& prescription_obj1);
        int findSecondMax(PrescriptionManager& prescription_obj1);
};

void printMenu();

int main() {
    PrescriptionManager prescription_obj1;
    PrescriptionAggregator aggregator_obj1;

    int choice;
    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                prescription_obj1.create();
                break;
            case 2:
                prescription_obj1.displayAll();
                break;
            case 3:
                prescription_obj1.editById();
                break;
            case 4:
                prescription_obj1.deleteById();
                break;
            case 5:
                cout << "Prescription with Min Dosage: "
                     << prescription_obj1.prescriptions[aggregator_obj1.findMin(prescription_obj1)].GetPrescriptionId()
                     << " with Dosage "
                     << prescription_obj1.prescriptions[aggregator_obj1.findMin(prescription_obj1)].GetDosage()
                     << endl;
                break;
            case 6:
                cout << "Prescription with Max Dosage: "
                     << prescription_obj1.prescriptions[aggregator_obj1.findMax(prescription_obj1)].GetPrescriptionId()
                     << " with Dosage "
                     << prescription_obj1.prescriptions[aggregator_obj1.findMax(prescription_obj1)].GetDosage()
                     << endl;
                break;
            case 7:
                cout << "Prescription with 2nd Min Dosage: "
                     << prescription_obj1.prescriptions[aggregator_obj1.findSecondMin(prescription_obj1)].GetPrescriptionId()
                     << " with Dosage "
                     << prescription_obj1.prescriptions[aggregator_obj1.findSecondMin(prescription_obj1)].GetDosage()
                     << endl;
                break;
            case 8:
                cout << "Prescription with 2nd Max Dosage: "
                     << prescription_obj1.prescriptions[aggregator_obj1.findSecondMax(prescription_obj1)].GetPrescriptionId()
                     << " with Dosage "
                     << prescription_obj1.prescriptions[aggregator_obj1.findSecondMax(prescription_obj1)].GetDosage()
                     << endl;
                break;
            case 9:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}

void PrescriptionManager::create() {
    string PrescriptionID;
    int Dosage;

    cout << "Enter PrescriptionID: ";
    cin >> PrescriptionID;

    if (findIndexById(PrescriptionID) != -1) {
        cout << "Error: PrescriptionID already exists. Please use a unique PrescriptionID.\n";
        return;
    }

    cout << "Enter The Dosage : ";
    cin >> Dosage;

    Prescription newPrescription;
    newPrescription.PrescriptionID = PrescriptionID;
    newPrescription.Dosage = Dosage;
    prescriptions.push_back(newPrescription);

    cout << "Prescription created successfully.\n";
}

void PrescriptionManager::displayAll() {
    if (prescriptions.empty()) {
        cout << "No Dosages are available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "|   PrescriptionID | Dosage                     |\n";
    cout << "------------------------------------------------\n";
    for (const auto& prescription : prescriptions) {
        cout << "| " << setw(10) << prescription.PrescriptionID << " | "
             << setw(13) << prescription.Dosage << " |\n";
    }
    cout << "------------------------------------------------\n";
}

int PrescriptionManager::findIndexById(const string& PrescriptionID) {
    for (size_t i = 0; i < prescriptions.size(); ++i) {
        if (prescriptions[i].PrescriptionID == PrescriptionID) {
            return i;
        }
    }
    return -1;
}

void PrescriptionManager::editById() {
    string PrescriptionID;
    cout << "Enter PrescriptionID to edit: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: PrescriptionID not found.\n";
        return;
    }

    cout << "Current Details - Dosage : " << prescriptions[index].Dosage << "\n";
    cout << "Enter New Dosage : ";
    cin >> prescriptions[index].Dosage;
    cout << "Prescription updated successfully.\n";
}

void PrescriptionManager::deleteById() {
    string PrescriptionID;
    cout << "Enter PrescriptionID to delete: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: PrescriptionID not found.\n";
        return;
    }

    prescriptions.erase(prescriptions.begin() + index);
    cout << "Prescription deleted successfully.\n";
}

bool Prescription::GreaterThan(const Prescription& other) {
    return (Dosage > other.Dosage);
}

bool Prescription::LessThan(const Prescription& other) {
    return (Dosage < other.Dosage);
}

string Prescription::GetPrescriptionId() {
    return PrescriptionID;
}

int Prescription::GetDosage() {
    return Dosage;
}

int PrescriptionAggregator::findMin(PrescriptionManager& prescription_obj1) {
    auto& prescriptions = prescription_obj1.prescriptions;
    int minIndex = 0;
    for (size_t i = 1; i < prescriptions.size(); ++i) {
        if (prescriptions[i].LessThan(prescriptions[minIndex])) {
            minIndex = i;
        }
    }
    return minIndex;
}

int PrescriptionAggregator::findMax(PrescriptionManager& prescription_obj1) {
    auto& prescriptions = prescription_obj1.prescriptions;
    int maxIndex = 0;
    for (size_t i = 1; i < prescriptions.size(); ++i) {
        if (prescriptions[i].GreaterThan(prescriptions[maxIndex])) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

int PrescriptionAggregator::findSecondMin(PrescriptionManager& prescription_obj1) {
    auto& prescriptions = prescription_obj1.prescriptions;
    int minIndex = findMin(prescription_obj1);
    int secondMinIndex = (minIndex == 0) ? 1 : 0;

    for (size_t i = 0; i < prescriptions.size(); ++i) {
        if (i != minIndex && prescriptions[i].LessThan(prescriptions[secondMinIndex])) {
            secondMinIndex = i;
        }
    }
    return secondMinIndex;
}

int PrescriptionAggregator::findSecondMax(PrescriptionManager& prescription_obj1) {
    auto& prescriptions = prescription_obj1.prescriptions;
    int maxIndex = findMax(prescription_obj1);
    int secondMaxIndex = (maxIndex == 0) ? 1 : 0;

    for (size_t i = 0; i < prescriptions.size(); ++i) {
        if (i != maxIndex && prescriptions[i].GreaterThan(prescriptions[secondMaxIndex])) {
            secondMaxIndex = i;
        }
    }
    return secondMaxIndex;
}

void printMenu() {
    cout << "\n=== Prescription Management Module ===\n";
    cout << "1. Create Prescription\n";
    cout << "2. Display All Prescriptions\n";
    cout << "3. Edit Prescription\n";
    cout << "4. Delete Prescription\n";
    cout << "5. Find Min Dosage\n";
    cout << "6. Find Max Dosage\n";
    cout << "7. Find Second Min Dosage\n";
    cout << "8. Find Second Max Dosage\n";
    cout << "9. Exit\n";
}
