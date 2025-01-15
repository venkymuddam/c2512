
#include<iostream>
#include<vector>
#include<string>
#include<climits>

using namespace std;

class Prescription {
    private: 
    string PrescriptionID;
    int Dosage;

    public: 
        Prescription(string p_id, int p_dosage) : PrescriptionID(p_id), Dosage(p_dosage) {}
        friend int findSum(const vector<Prescription>& prescriptions);
        friend int findMinInFirstHalf(const vector<Prescription>& prescriptions);
        friend int findMaxInSecondHalf(const vector<Prescription>& prescriptions);
        
};


int findSum(const vector<Prescription>& prescriptions) {


            int sum = 0;
            for (auto curr : prescriptions) {
                sum += curr.Dosage;
            }
            return sum;
        }

        int findMinInFirstHalf(const vector<Prescription>& prescriptions) {



            int mini = INT_MAX;
            for (int i = 0; i < (prescriptions.size() / 2); i++) {
                if (prescriptions[i].Dosage < mini) {
                    mini = prescriptions[i].Dosage;
                }
            }

            return mini;
        }

        int findMaxInSecondHalf(const vector<Prescription>& prescriptions) {


            int maxi = INT_MIN;
            for (int i = (prescriptions.size() / 2); i < prescriptions.size(); i++) {
                if (prescriptions[i].Dosage > maxi) {
                    maxi = prescriptions[i].Dosage;
                }
            }

            return maxi;
        }

int main() {


    vector<Prescription> prescriptions;


    prescriptions.push_back(Prescription("1", 100));
    prescriptions.push_back(Prescription("2", 200));
    prescriptions.push_back(Prescription("3", 300));
    prescriptions.push_back(Prescription("4", 400));
    prescriptions.push_back(Prescription("5", 500));

    //Prescription ob1("0", 0);

    cout << "The sum of dosages is : " << findSum(prescriptions)<<endl; 

    cout << "The minimum in first half is : " <<findMinInFirstHalf(prescriptions)<<endl;
    cout << "The maximum in second half is : " <<findMaxInSecondHalf(prescriptions) << endl;


    return 0;
}
