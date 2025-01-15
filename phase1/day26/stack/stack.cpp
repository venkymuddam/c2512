// // // 1. complete Stack implementation 
// // // 1.2. Exceptions Overflow ex, Underflow ex 
// // // 2. convert Stack as generic Stack 
// // // 3. dynamic array 
// // // DONT DO::4. smart pointer [unique_ptr]
#include <iostream>
#include <exception>
using namespace std;

class OverFlowException : public exception{
    public:
        const char* what() const noexcept override{
            return "Stack Overflow Exception";
        }
};

class UnderFlowException : public exception{
    public:
        const char* what() const noexcept override{
            return "Stack Underflow Exception";
        }
};

class EmptyStackException : public exception{
    public:
        const char* what() const noexcept override{
            return "Empty Stack Exception";
        }
};

class c2512Stack 
{
    private:
        static const int _size {3};
        double arr[_size];
        int _top;
    public: 
        c2512Stack() : _top(0) {};
        
        void push(double data){
            if (_top == _size){
                throw OverFlowException();
            }
            
            arr[_top] = data;
            _top++;
        }
        
        void pop(){
            if (_top == 0){
                throw UnderFlowException();
            }  
            
            _top--;
        }
        double top(){
            if (_top == 0){
                throw EmptyStackException();
            }
            
            return arr[_top - 1];               
        }
};


// driver code 
int main(){
   
    c2512Stack stack;
    
    try{
        stack.push(10.0);
        stack.push(12.0);
        stack.push(11.0);
    }
    catch(OverFlowException& e){
        cout << e.what() << endl;
    }
    try{
        cout << stack.top() << endl; //11.0
        stack.pop();
        cout << stack.top() << endl; //12.0
        stack.pop();
        cout << stack.top() << endl; //10.0
        stack.pop();
        cout << stack.top() << endl; //Err/Underflow
        stack.pop();
    }
    catch(EmptyStackException& e){
        cout << e.what() << endl;
    }
    catch(UnderFlowException& e){
        cout << e.what() << endl;
    }
    
    return 0;
}
