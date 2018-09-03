#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
string padding_by_zero(string smaller , string larger );
bool isnegative_num(string num);
int ctoi(char c);
int smaller(string s1, string s2);
void remove_padding_zeros(string& str);

class large_int
{   
    public:
    string num;
    //int length;
    bool isnegative;
    large_int()
    {}
    large_int(string s, bool b)
    {
        num =s;
        //length = len;
        isnegative = b;
    }

};
large_int addition(large_int num1, large_int num2);
large_int operator+(large_int num1, large_int num2);
large_int subtraction(large_int num1, large_int num2);
large_int multipication(large_int num1, large_int num2);
void string_processing(string& str)
{
    if(str[0] == '-')
    {
        str.erase(0,1);
    }
}
large_int operator+(large_int num1, large_int num2)
{ 
    large_int answer;
    if(num1.isnegative && !(num2.isnegative))
    {
        answer = subtraction(num2,num1);
    }
    if(!(num1.isnegative) && num2.isnegative)
    {
        answer = subtraction(num1,num2);
    }
    if(num1.isnegative && num2.isnegative)
    {
        answer = addition(num1,num2);
        answer.num = "-"+answer.num;
        answer.isnegative = true;
    }
    if(!(num1.isnegative) && !(num2.isnegative))
    {
        answer = addition(num1,num2);
    }
    return answer;
  
}
large_int operator-(large_int num1, large_int num2)
{ 
    large_int answer;
    if(num1.isnegative && !(num2.isnegative))
    {
        answer = addition(num1,num2);
        answer.num = "-"+answer.num;
        answer.isnegative = true;
    }
    if(!(num1.isnegative) && num2.isnegative)
    {
        answer = addition(num1,num2);
    }
    if(num1.isnegative && num2.isnegative)
    {
        answer = subtraction(num2,num1);
    }
    if(!(num1.isnegative) && !(num2.isnegative))
    {
        answer = subtraction(num1,num2);
    }
    return answer;
  
}

large_int operator*(large_int num1, large_int num2)
{ 
    large_int answer;
    if(num1.isnegative && !(num2.isnegative))
    {
        answer = multipication(num1,num2);
        answer.num = "-"+answer.num;
        answer.isnegative = true;
    }
    if(!(num1.isnegative) && num2.isnegative)
    {
        answer = multipication(num1,num2);
        answer.num = "-"+answer.num;
        answer.isnegative = true;
    }
    if(num1.isnegative && num2.isnegative)
    {
        answer = multipication(num2,num1);
    }
    if(!(num1.isnegative) && !(num2.isnegative))
    {
        answer = multipication(num1,num2);
    }
    return answer;
  
}

large_int addition(large_int num1, large_int num2)
{
    large_int answer;
    string padded = "";
    string num3 = "";
    string numone = num1.num;
    string numtwo = num2.num;
    string_processing(numone);
    string_processing(numtwo);
    cout<<numone<<endl;
    cout<<numtwo<<endl;
    int carry = 0;
    if(numone.size() > numtwo.size())
    {   
        padded = padding_by_zero(numtwo, numone);  
        numtwo = padded;  
    }
    else if (numone.size() < numtwo.size())
    {
    padded = padding_by_zero(numone, numtwo);
    numone = padded;
    }
    cout<<numone<<endl;
    cout<<numtwo<<endl;
    for(int i = numone.size()-1 ; i>-1 ; i--)
    {
        int digitsum = ( numone[i] - '0') + (numtwo[i] - '0') + carry;
        cout<<digitsum<<endl;
        int rem = digitsum%10;
        num3.insert(0,to_string(rem));
        carry = digitsum/10;

    }
    if(carry > 0)num3.insert(0,to_string(carry));
    answer.num = num3;
    //answer.length = num3.size();
    answer.isnegative = false;
    return answer;
   
}
large_int multipication(large_int num1, large_int num2)
{
    large_int answer;
    string padded = "";
    string numone = num1.num;
    string numtwo = num2.num;
    string_processing(numone);
    string_processing(numtwo);
    string num3(numone.size()+numtwo.size()+1,'0');
    string num4 = "";
    if(numone.size() == 0 || numone == "0" ||numtwo.size() == 0 || numtwo == "0")
    {
        return large_int("0",false);
    }
    if(numone == "1")
    {
        return large_int(numtwo,false);
    }
    if(numtwo == "1")
    {
        return large_int(numone,false);
    }
    cout<<numone<<endl;
    cout<<numtwo<<endl;
    int p1,p2;
    for(int i = numone.size()-1 ; i>-1 ; i--)
    {   
        int carry = 0;
        p1 = numone.size()-1-i;
        p2 = 0;
        for(int j = numtwo.size()-1 ; j>-1 ; j--)
        {
            p2 = numtwo.size()-1-j;
            int digitmul = ctoi(numone[i]) * ctoi(numtwo[j]) + ctoi(num3[p1+p2])+carry;
            int rem = digitmul%10;
            carry = digitmul/10;
            cout<<digitmul<<" "<<rem<<" "<<carry<<"this"<<endl;
            num3.replace(p1+p2,1,to_string(rem));
            cout<<num3<<endl;
        }
        if(carry) num3.replace(p1+p2+1, 1, to_string(ctoi(num3[p1+p2+1])+carry));
        cout<<num3<<"this2"<<endl;
    }
    for(int i = num3.size()-1 ;i>-1;i--)
    {
        num4 = num4 + num3[i];
    }
    remove_padding_zeros(num4);
    answer.num = num4;
    //answer.length = num3.size();
    answer.isnegative = false;
    return answer;
   
}
large_int subtraction(large_int num1, large_int num2)
{
    large_int answer;
    string padded = "";
    string num3 = "";
    string numone = num1.num;
    string numtwo = num2.num;
    int negative_flag = 0;
    if (numone == numtwo)
    {
        return large_int("0",false);
    }
    string_processing(numone);
    string_processing(numtwo);
    if(smaller(numone,numtwo)) 
    {
        swap(numone,numtwo);
        negative_flag = 1;
    }
    cout<<numone<<endl;
    cout<<numtwo<<endl;
    int borrow = 0;
    if(numone.size() > numtwo.size())
    {   
    padded = padding_by_zero(numtwo, numone);  
    numtwo = padded;  
    }
    else if (numone.size() < numtwo.size())
    {
    padded = padding_by_zero(numone,numtwo);
    numone = padded;
    }
    cout<<numone<<endl;
    cout<<numtwo<<endl;
    for(int i = numone.size()-1 ; i>-1 ; i--)
    {
        int digitdiff = ( numone[i] - '0') - (numtwo[i] - '0') - borrow;
        cout<<digitdiff<<endl;
        if(digitdiff < 0)
        {
            borrow = 1;
            digitdiff = digitdiff + 10;
        }
        else borrow = 0;
        num3.insert(0,to_string(digitdiff));


    }
    remove_padding_zeros(num3);
    if(negative_flag) 
    {   
        answer.num = "-"+num3;
        answer.isnegative = true;
    }
    else 
    {
        answer.num = num3;
        answer.isnegative = false;
    }
    //answer.length = num3.size();
    
    return answer;
   
}
bool isnegative_num(string num)
{   

    if(num[0] == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

string padding_by_zero(string smaller , string larger )
{
    int no_of_zeroes = larger.size() - smaller.size();
    for(int i = 0 ; i<no_of_zeroes; i++)
    {
        smaller.insert(0,1,'0');
    }
    return smaller;
}
int smaller(string s1, string s2)
{
    int flag_of_same = 1;
    if(s1.size() < s2.size())
    {
        return 1;
        flag_of_same = 0 ;
    }
    if(s2.size() < s1.size())
    {
        return 0;
        flag_of_same = 0 ;
    }
    for(int i = 0 ; i<s1.size(),flag_of_same != 0 ;i++ )
    {
        if( ctoi(s1[i]) > ctoi(s2[i]) )
        {
            return 0;
        }
        if( ctoi(s1[i]) < ctoi(s2[i]) )
        {
            return 1;
        }
    }
    return 0;

}
int ctoi(char c)
{
    return (c - '0');
}
void remove_padding_zeros(string& str)
{
    for(int i = 0 ; i<str.size()-1 ; i++)
    {
        char a = str[i];
        if(a=='0')
        {
            str.erase(0,1);
            i--;
        }
        else break;
    }
}
int main()
{   
    string one;
    string two;
    cin>>one>>two;
    large_int a(one,isnegative_num(one)), b(two,isnegative_num(two));
    //large_int c = a-b;
    large_int d = a*b;
    //large_int mul = multipication(a,b);
    cout<<d.num<<endl;
    //cout<<c.num<<endl;
    //cout<<mul.num;
    //cout<<c.num;
    return 0;
}