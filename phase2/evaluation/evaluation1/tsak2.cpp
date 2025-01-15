
#include<iostream>
#include<thread>
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
    friend void findSum(const vector<Prescription>& prescriptions, int& summ);
    friend void findMinInFirstHalf(const vector<Prescription>& prescriptions, int& mini);
    friend void findMaxInSecondHalf(const vector<Prescription>& prescriptions, int& maxi);
        
};




void findSum(const vector<Prescription>& prescriptions, int& sum) {


            sum = 0;
            for (auto curr : prescriptions) {
                sum += curr.Dosage;
            }
            
        }

        void findMinInFirstHalf(const vector<Prescription>& prescriptions, int& mini) {



            mini = INT_MAX;
            for (int i = 0; i < (prescriptions.size() / 2); i++) {
                if (prescriptions[i].Dosage < mini) {
                    mini = prescriptions[i].Dosage;
                }
            }

            
        }

        void findMaxInSecondHalf(const vector<Prescription>& prescriptions, int& maxi) {


            maxi = INT_MIN;
            for (int i = (prescriptions.size() / 2); i < prescriptions.size(); i++) {
                if (prescriptions[i].Dosage > maxi) {
                    maxi = prescriptions[i].Dosage;
                }
            }

            
        }

int main() {


    vector<Prescription> prescriptions;


    prescriptions.push_back(Prescription("1", 100));
    prescriptions.push_back(Prescription("2", 200));
    prescriptions.push_back(Prescription("3", 300));
    prescriptions.push_back(Prescription("4", 400));
    prescriptions.push_back(Prescription("5", 500));

    //Prescription ob1("0", 0);
    
    int sum = 0;
    int mini = 0;
    int maxi = 0;
    
    std::thread thrSum(findSum, ref(prescriptions), ref(sum));
    std::thread thrMin(findMinInFirstHalf, ref(prescriptions), ref(mini));
    std::thread thrMax(findMaxInSecondHalf, ref(prescriptions), ref(maxi));
    
    
    thrSum.join();
    thrMin.join();
    thrMax.join();

    cout << "The sum of dosages is : " << sum<<endl; 

    cout << "The minimum in first half is : " <<mini<<endl;
    cout << "The maximum in second half is : " << maxi<< endl;


    return 0;
}
