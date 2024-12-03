// class name is, "Prescription" [number 02]
// comparision doing is, "Dosage"


#include <iostream>
#include <iomanip>
using namespace std;

// Constants
const int MAX_PRESCRIPTIONS = 100;

class Prescription {
    friend class PrescriptionManager;
    private: // member data
        string PrescriptionID;
        int Dosage;
    public: // member functions
        bool GreaterThan(const Prescription& other);
        bool LessThan(const Prescription& other);
         //getters-setters
        string GetPrescriptionId();
        int GetDosage();
};

class PrescriptionManager {
    friend class PrescriptionAggregator;
    friend int main();
    private:
        // member data
        Prescription prescriptions[MAX_PRESCRIPTIONS];    
        int numOfPrescriptions;
    public: // member functions
        // support
        int findIndexById(string PrescriptionID);
        // behaviours - crud
        void create();
        void displayAll();
        void editById();
        void deleteById();
        // constructor
        PrescriptionManager();
};


class PrescriptionAggregator {
    public:
        int findMin(PrescriptionManager& prescription_obj1);
        int findMax(PrescriptionManager& prescription_obj1);
        int findSecondMin(PrescriptionManager& prescription_obj1);
        int findSecondMax(PrescriptionManager& prescription_obj1);
};


void printMenu();


// main 
int main() {
    PrescriptionManager prescription_obj1;
    PrescriptionAggregator aggregator_obj1;
   
    int choice; 

    do {
        printMenu(); 

        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {
            case 1: prescription_obj1.create();    
                break;
            case 2: prescription_obj1.displayAll();  
                break;
            case 3: prescription_obj1.editById();      
                break;
            case 4: prescription_obj1.deleteById();    
                break;
            case 5: 
                std::cout << "Prescription with Min Dosage: " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findMin(prescription_obj1)].GetPrescriptionId() 
                    << " with Dosage " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findMin(prescription_obj1)].GetDosage() 
                    << std::endl;
                break;
            case 6: 
                std::cout << "Prescription with Max Dosage: " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findMax(prescription_obj1)].GetPrescriptionId() 
                    << " with Dosage " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findMax(prescription_obj1)].GetDosage() 
                    << std::endl;
                break;
            case 7: 
                std::cout << "Prescription with 2nd Min Dosage: " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findSecondMin(prescription_obj1)].GetPrescriptionId() 
                    << " with Dosage " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findSecondMin(prescription_obj1)].GetDosage() 
                    << std::endl; 
                break;
            case 8: 
                std::cout << "Prescription with 2nd Max Dosage: " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findSecondMax(prescription_obj1)].GetPrescriptionId() 
                    << " with Dosage " 
                    << prescription_obj1.prescriptions[aggregator_obj1.findSecondMax(prescription_obj1)].GetDosage() 
                    << std::endl;
                break;
            case 9:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 9);

    return 0;
}



// create prescriptions
void PrescriptionManager::create() {
    if (numOfPrescriptions >= MAX_PRESCRIPTIONS) {
        cout << "Error: Maximum prescription limit reached.\n";
        return;
    }

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


    prescriptions[numOfPrescriptions].PrescriptionID = PrescriptionID;
    prescriptions[numOfPrescriptions].Dosage = Dosage;
    numOfPrescriptions++;

    cout << "Prescription created successfully.\n";
}


// print(display) prescription details
void PrescriptionManager::displayAll() {
    if (numOfPrescriptions == 0) {
        cout << "No Dosages are available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "|   PrescriptionID | Dosage                     |\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < numOfPrescriptions; i++) {
        cout << "| " << setw(10) << prescriptions[i].PrescriptionID << " | "
             << setw(13) << prescriptions[i].Dosage << " |\n";
    }
    cout << "------------------------------------------------\n";
}




int PrescriptionManager::findIndexById(string PrescriptionID) {
    for (int i = 0; i < numOfPrescriptions; i++) {
        if (prescriptions[i].PrescriptionID == PrescriptionID) {
            return i;
        }
    }
    return -1;
}


// update(edit) dosage
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


// delete dosage
void PrescriptionManager::deleteById() {
    string PrescriptionID;
    cout << "Enter PrescriptionID to delete: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: PrescriptionID not found.\n";
        return;
    }

    // filling the gap
    for (int i = index; i < numOfPrescriptions - 1; i++) {
        prescriptions[i] = prescriptions[i + 1];
    }
    numOfPrescriptions--;

    cout << "Prescription deleted successfully.\n";
}

// constructor
PrescriptionManager::PrescriptionManager() {
    numOfPrescriptions = 0;
}


void printMenu() {
    cout << "\n=== prescription Management Module ===\n";
    cout << "1. Create prescription\n";
    cout << "2. Display All prescriptions\n";
    cout << "3. Edit prescription\n";
    cout << "4. Delete prescription\n";
    cout << "5. Find Min Dosage\n";
    cout << "6. Find Max Dosage\n";
    cout << "7. Find Second Min Dosage\n";
    cout << "8. Find Second Max Dosage\n";
    cout << "9. Exit\n";
}


bool Prescription::GreaterThan(const Prescription& other)
{
    return (Dosage > other.Dosage);
}

bool Prescription::LessThan(const Prescription& other)
{
    return (Dosage < other.Dosage);
}

//getters-setters
string Prescription::GetPrescriptionId()
{
    return PrescriptionID;
}
int Prescription::GetDosage()
{
    return Dosage;
}


// aggregator functions

int PrescriptionAggregator::findMin(PrescriptionManager& prescription_obj1) {
    Prescription* arr = prescription_obj1.prescriptions;
    int& n = prescription_obj1.numOfPrescriptions;
    
    int minIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].LessThan(arr[minIndex])) {
            minIndex = i;
        }
    }
    return minIndex;
}


int PrescriptionAggregator::findMax(PrescriptionManager& prescription_obj1) {
    Prescription* arr = prescription_obj1.prescriptions;
    int& n = prescription_obj1.numOfPrescriptions;
    
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].GreaterThan(arr[maxIndex])) {
            maxIndex = i;
        }
    }
    return maxIndex;
}


int PrescriptionAggregator::findSecondMin(PrescriptionManager& prescription_obj1) {
    Prescription* arr = prescription_obj1.prescriptions;
    int& n = prescription_obj1.numOfPrescriptions;
    
    int minIndex = findMin(prescription_obj1);
    int secondMinIndex = (minIndex == 0) ? 1 : 0;
    
    for (int i = 0; i < n; ++i) {
        if (i != minIndex) {
            if (arr[i].LessThan(arr[secondMinIndex])) {
                secondMinIndex = i;
            }
        }
    }
    return secondMinIndex;
}


int PrescriptionAggregator::findSecondMax(PrescriptionManager& prescription_obj1) {
    Prescription* arr = prescription_obj1.prescriptions;
    int& n = prescription_obj1.numOfPrescriptions;
    
    int maxIndex = findMax(prescription_obj1);
    int secondMaxIndex = (maxIndex == 0) ? 1 : 0;
    
    for (int i = 0; i < n; ++i) {
        if (i != maxIndex) {
            if (arr[i].GreaterThan(arr[secondMaxIndex])) {
                secondMaxIndex = i;
            }
        }
    }
    return secondMaxIndex;
}
