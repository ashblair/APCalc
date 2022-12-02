#pragma once

//#include "stdafx.h"
// mint is memory integer 
// it's size is variable and is limited only by the size of memory

class mint
{
public:
    mint(void);
    mint(const mint &);
    mint(const int &);
    mint(const long &);
    mint(const size_t &);
    mint(const string &);
    ~mint(void);

    operator double(void);

    mint & operator=(const mint &);
    mint & operator+=(const mint &);
    mint & operator-=(const mint &);
    mint & operator*=(const mint &);
    mint & operator/=(const mint &);
    mint & operator%=(const mint &);
    mint & operator++(void);
    mint operator++(int);
    mint & operator--(void);
    mint operator--(int);

    friend bool operator == (const mint & a, const mint & b) {return a.IsEq(b);}
    friend bool operator < (const mint & a, const mint & b) {return a.IsLT(b);}
    friend bool operator > (const mint & a, const mint & b) {return a.IsGT(b);}
    friend bool operator <= (const mint & a, const mint & b) {return (a.IsEq(b) || a.IsLT(b));}
    friend bool operator >= (const mint & a, const mint & b) {return (a.IsEq(b) || a.IsGT(b));}
    friend mint operator + (const mint & a, const mint & b) {mint r(a); r+=b; return r;}
    friend mint operator - (const mint & a, const mint & b) {mint r(a); r-=b; return r;}
    friend mint operator * (const mint & a, const mint & b) {mint r(a); r*=b; return r;}
    friend mint operator / (const mint & a, const mint & b) {mint r(a); r/=b; return r;}
    friend mint operator % (const mint & a, const mint & b) {mint r(a); r%=b; return r;}

    string print(void);
    void factorial(void);

    bool positive;
    vector<unsigned char> digits;

private:
    static bool LittleEndianSys;
    static bool IsLittleEndian(void); // checks with the float 3.0f

    bool IsEq(const mint &) const;
    bool IsLT(const mint &) const;
    bool IsGT(const mint &) const;
    
    bool IsStringPositive(const string &);
    string RemoveExtraneousChars(const string &);
    string ConvertToBinary(const string &);
    string MultiplyBinary1010(const string &);
    string MultiplyBinaryByDecimal(const string &, unsigned char);
    string AddBinary(const string &, const string &);
    string AddDecimal(const string&, const string &);
    string MultiplyDecimal(const string &, const string &);
    vector<unsigned char> AddBinary(const vector<unsigned char>&, const vector<unsigned char>&);
    vector<unsigned char> SubtractBinary(const vector<unsigned char>&, const vector<unsigned char>&);
    int compare(const vector<unsigned char>&) const;  // -1=less:0=equal:+1=greater
    unsigned int getNth(size_t, const vector<unsigned char>&);
    unsigned char preceedingZeros(unsigned char);
    vector<unsigned char> shiftLeft(const unsigned char);
    void shiftLeftFillRight(const size_t &, const vector<unsigned char>&);

    
};