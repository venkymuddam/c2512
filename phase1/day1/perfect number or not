//check a number is perfect or not

Pseudofunctions:

function isPerfectNumber(number->int)->bool

 	sum = 0
 	
 	half = (number / 2)
 	
 	for i from 1 ..half
 		if (number % i == 0)
 			sum = sum + i
 		endif
 	endfor
 	
 	return (sum == number)
 	
 function isPerfectNumberTest()
 
 	input number
 	bool result = isPerfectNumber(number)
 	
 	if (result)
 		print "The number is perfect"
 	else
 		print "The number is not perfect"
 	endif
 	
 Pseudocode:
 
 isPerfectNumberTest()


#include<iostream>
using std::cout;
using std::cin;


bool isPerfectNumber(int number)
{
    int sum = 0;
    
    int half = (number / 2);
 	
 	for (int i = 1 ; i <= half ; i++)
 	{
 	    if (number % i == 0)
 	    {
 	       sum = (sum + i);
 	    }
 	}
 	
 	return (sum == number);
}

void isPerfectNumberTest(void)
{
    int number;
    
    cout << "Enter a number:";
    cin >> number;
    
 	bool result = isPerfectNumber(number);
 	
 	if (result)
 	{
 		cout << number << " is a perfect number";
 	}
 	else
 	{
 	    cout << number << " is not a perfect number";
 	}
}

int main(void)
{
    isPerfectNumberTest();
 
    return 0;
}
 		
