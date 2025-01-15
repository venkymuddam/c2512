#include <iostream>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

class Prescription{
    
    private:
        string prescriptionID;
        int Dosage;


    public:
        Prescription(string p_id, int p_dosage) : prescriptionID(p_id), Dosage(p_dosage) {}
        int getDosageValue() {
            return Dosage;
        }
};



template<class T>
T accumulate(const vector<Prescription>& prescriptions,function<T(T, Prescription)> functionLamda,T initial_value) {
    T res = initial_value;
    for (auto curr_prescription : prescriptions) {
        res = functionLamda(res, curr_prescription);
    }
    return res;
}



int main() {
    
    vector<Prescription> prescriptions;
    
    
    prescriptions.push_back(Prescription("1",100));
    prescriptions.push_back(Prescription("2",200));
    prescriptions.push_back(Prescription("3",300));
    prescriptions.push_back(Prescription("4",400));
    prescriptions.push_back(Prescription("5",500));
    


    auto sumLamdaFun = [](int curr_sum,Prescription curr_obj)->int{

        curr_sum += curr_obj.getDosageValue();
        return curr_sum;
    };
    int sum_value = accumulate<int>(prescriptions,sumLamdaFun,0);
    
    cout << "sum of all the dosages is : " << sum_value << endl;

    auto minLamdaFun = [](int curr_mini,Prescription curr_obj)->int{

        if (curr_obj.getDosageValue()<curr_mini){
            curr_mini = curr_obj.getDosageValue();
        }
        return curr_mini;
    };
    int mini_value = accumulate<int>(prescriptions,minLamdaFun, INT_MAX );
    cout << "minimum dosage among all the dosages is : " << mini_value << endl;

    return 0;
}








