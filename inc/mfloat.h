#pragma once

#include "stdafx.h"
#include "mint.h"
// mfloat is memory float 
// it's size is variable and is limited only by the size of memory

struct store_float
{ // for storage of mfloats
    store_float(void): FLAGS(0), EXPONENT(0), BIT_COUNT(0), SIG(NULL) {}
    store_float(const store_float & a): FLAGS(a.FLAGS), EXPONENT(a.EXPONENT), BIT_COUNT(a.BIT_COUNT) 
    {
        SIG = NULL;
        if (a.BIT_COUNT > 0)
        {
            SIG = new unsigned char[a.BIT_COUNT];
            memcpy(SIG, a.SIG, a.BIT_COUNT);
        }
    }
    ~store_float(void) {if (SIG != NULL) delete[]SIG;}
    store_float & operator =(const store_float & a) 
    {
        FLAGS = a.FLAGS;
        EXPONENT = a.EXPONENT;
        BIT_COUNT = a.BIT_COUNT;
        if (SIG != NULL) delete[]SIG;
        SIG = NULL;
        if (BIT_COUNT > 0)
        {
            SIG = new unsigned char[BIT_COUNT];
            memcpy(SIG, a.SIG, BIT_COUNT);
        }
        return *this;
    }
    unsigned char FLAGS;
    int EXPONENT;
    unsigned int BIT_COUNT;
    unsigned char * SIG;
};

struct display_float
{ // for the display of mfloats
    display_float(void): PB(NULL), OBInitialized(false) {}

    Gtk::ProgressBar * PB;
    Glib::RefPtr<Gtk::TextBuffer> OB;
    bool OBInitialized;

    void progress_text(const string & s) {if (PB != NULL) PB->set_text(s);}

    void progress(const double & pd) 
    {
        if (PB == NULL) return;
        PB->set_fraction(pd);
        while (gtk_events_pending()) gtk_main_iteration();
    }

    void write (const string & s)
    {
        if (!OBInitialized) cout << s;
        else
        {
            OB->insert(OB->begin(), s);
            //int lc = OB->get_line_count();
            if (OB->get_line_count() > 2)
            {
                OB->move_mark_by_name("insert", OB->begin());
                OB->move_mark_by_name("selection_bound", OB->get_iter_at_line(2));
                while (gtk_events_pending()) gtk_main_iteration();
                usleep(300000); // three tenths of a second?
            }
            OB->move_mark_by_name("insert", OB->begin());
            OB->move_mark_by_name("selection_bound", OB->get_iter_at_line(1));

        }
        
    }
};

class mfloat
{
public:
    mfloat(void);
    mfloat(const mfloat &);
    mfloat(const float &);
    mfloat(const double &);
    mfloat(const int &);
    mfloat(const mint &);
    mfloat(const string &);
    mfloat(const store_float &);
    ~mfloat(void);

    // cast operators:
    operator int(void);
    operator mint(void);
    operator float(void);
    operator double(void);
    
    mfloat & operator=(const mfloat &);
    mfloat & operator+=(const mfloat &);
    mfloat & operator-=(const mfloat &);
    mfloat & operator*=(const mfloat &);
    mfloat & operator/=(const mfloat &);
    

    friend bool operator == (const mfloat & a, const mfloat & b) {return a.IsEq(b);}
    friend bool operator != (const mfloat & a, const mfloat & b) {return !a.IsEq(b);}
    friend bool operator < (const mfloat & a, const mfloat & b) {return a.IsLT(b);}
    friend bool operator > (const mfloat & a, const mfloat & b) {return a.IsGT(b);}
    friend bool operator <= (const mfloat & a, const mfloat & b) {return (a.IsEq(b) || a.IsLT(b));}
    friend bool operator >= (const mfloat & a, const mfloat & b) {return (a.IsEq(b) || a.IsGT(b));}
    friend mfloat operator + (const mfloat & a, const mfloat & b) {mfloat r(a); r+=b; return r;}
    friend mfloat operator - (const mfloat & a, const mfloat & b) {mfloat r(a); r-=b; return r;}
    friend mfloat operator * (const mfloat & a, const mfloat & b) {mfloat r(a); r*=b; return r;}
    friend mfloat operator / (const mfloat & a, const mfloat & b) {mfloat r(a); r/=b; return r;}
    friend mfloat sqr(const mfloat & a) {mfloat r(a); r *= a; return r;}
    friend mfloat inverse_m(const mfloat & a) {mfloat r(mint(1)); r /= a; return r;} // mfloat r(a); r.newton_inverse_m(); slower
    friend mfloat inverse_a(const mfloat & a) {mfloat r(a); if (!r.zero) r.pos = !r.pos; return r;}
    friend mfloat exp(const mfloat & a) {mfloat r(a); r.taylor_agm_e(); return r;} //r.householder8_e();r.newton_e(); ~half-speed r.halley_e(); r.eToThex();
    friend mfloat log(const mfloat & a) {mfloat r(a); r.eLog(); return r;} // r.natural_log_2(); r.eLog(); r.naturalLog_1(); 
    friend mfloat cos(const mfloat & a) {mfloat r(a); r.cosine(); return r;}
    friend mfloat sin(const mfloat & a) {mfloat r(a); r.sine(); return r;}
    friend mfloat tan(const mfloat & a) {mfloat r(a); r.tangent(); return r;}
    friend mfloat atan(const mfloat & a) {mfloat r(a); r.arctan(); return r;}
    friend mfloat sqrt(const mfloat & a) {mfloat r(a); r.square_root(); return r;} //r.square_root();r.newton_sqrt(); way slower
    friend mfloat fact(const mfloat & a) {mfloat r(a); r.factorial(); return r;}
    friend mfloat x_to_the_y(const unsigned int & x, const mfloat & y) {mfloat r(y); r.base_raised_to_the_x(x); return r;}
    friend mfloat log_base_b(const unsigned int & b, const mfloat & x) {mfloat r(x); r.non_natural_log(b); return r;}
    friend mfloat abs(const mfloat & a) {mfloat r(a); r.pos = true; return r;}
    
    string print(void);
    string print_bits(void);
    void display_all_constants(void);
    void reset_DROUND(const int &);
    string ConvertToDecimal(void);
    void pi_me(void);
    bool IsFloat(const string &, string &, string &, string &);
    bool isthisZero(const string &, const string &);
    bool isInt(void);
    bool isNumber(void);
    int & getExponent(void);

    void test(void);
    void test2(void);
    void test3(void);
    void test4(void);
    void test5(void);
    void test6(void);
    void test7(void);
    void test8(void);

    static display_float disp;
    //static Glib::ustring exp_char;
    static bool SaveSigFigs(void);
    static int DMAX, BMAX, DROUND, BROUND, LOG_BROUND; // maximum decimal digits and bits
    enum CONSTANTS{LN_2=0, LN_5=1, LN_10=2, LN_2_OVER_10=3, LN_10_OVER_2=4, EXP_1=5, P_I=6};
    mfloat handleCONSTANT(const CONSTANTS &);
    void getFirstRotation(void);
    static int max(const int &, const int &);
    static int min(const int &, const int &);
private:
    static const char *_constants[];
    static store_float _ln2, _ln5, _ln10, _ln10oln2, _ln2oln10, _exp1, _pi;
    static bool LittleEndianSys, SigFigsLoaded;
    static bool IsLittleEndian(void); // checks with the float 3.0f
    static bool DoesPathExist(const string &);
    static bool LoadSigFigs(void);
    //static store_float ln_2, ln_5, ln_10, ln_2_over_10, ln_10_over_2, exp_1, p_i;
    int exponent; // 2^exponent in [-2^31, 2^31 - 1] which is [-2147483648, 2147483647]
    bool pos, nan, zero, inf, sub; // pos: >=0?; nan: not a number; zero =0
    vector<unsigned char> sig; // significand left to right 1 + bit_i * 2^-i

    string trim(const string &);
    char ClassifyChar(const char &);
    string half(const string &); // returns one half of decimal string
    string twice(const string &); // returns 2X decimal string
    bool IsEq(const mfloat &) const;
    bool IsLT(const mfloat &) const;
    bool IsGT(const mfloat &) const;
    bool IsMagEq(const mfloat &) const; // magnitude: distance from 0 always positive
    bool IsMagLT(const mfloat &) const;
    bool IsMagGT(const mfloat &) const;
    int eToThex(const bool & = false);
    int naturalLog(void); //(const int & = 0);
    int naturalLog_1(void); //gets ln using 1 + x operand
    void alignByte(const unsigned char &, const unsigned char &, unsigned char &, const unsigned char &);
    int exponent_cmp(const string &);
    int exponent_cmp(const int &, const int &);
    void standardize_d(string &, int &);
    void get2sComplement(int &);
    unsigned char getRightZeros(const vector<unsigned char> &);
    
    vector<unsigned char> add_magnitude(const vector<unsigned char> &, const vector<unsigned char> &, int &);
    vector<unsigned char> subtract_magnitude(const vector<unsigned char> &, const vector<unsigned char> &, int &);
    
    int standardize_v(vector<unsigned char> &);
    int getFirstNonZero(const vector<unsigned char> &); // returns index not count
    int getFirstNonZero(const int &);

    int getIntAndReal(bool &);
    void ClearInt(void);
    string RoundMe(const string &);
    void RoundMe(void);
    void power(const int &);
    int power(const mfloat &);
    int arctan(const bool & = false);
    int arctan2(const mfloat &);
    int binary_log(void); //very slow
    int square_root(void);
    int agm(const mfloat &, const string & = ""); // arithmetic-geometric mean
    int eLog(const string & = ""); // natural log w/ agm
    int newton_e(void); // e^x using Newtorn's method
    int halley_e(void); // e^x using Halley's method
    void calculateCONSTANT(const CONSTANTS &);
    void storeCONSTANT(const CONSTANTS &);
    store_float * getCONSTANT(const CONSTANTS &);
    store_float make_store_float(const mfloat &, const bool & = true);
    int sine(void);
    int cosine(void);
    int tangent(void);
    bool unset_final(double &);
    void factorial(void);
    void base_raised_to_the_x(const unsigned int &);
    void non_natural_log(const unsigned int &);
    mfloat split_off(const int &);
    int getBitCount(void);    
    mfloat karatsuba(const mfloat &, const mfloat &);
    void multiply(const mfloat &);
    void divide(const mfloat &);   
    int newton_inverse_m(void);
    int newton_sqrt(void);
    void gauss_legendre_pi(void);
    int householder3_e(void);
    int householder4_e(const bool & = false);
    int householder5_e(void);
    void natural_log_2(void);
    int householder6_e(void);
    int householder7_e(void);
    int householder8_e(const bool & = false);
    int taylor_agm_e(const bool & = false);
};

class mcomplex
{
public:
    mcomplex(void); // constructs 0
    mcomplex(const mcomplex &);
    mcomplex(const mfloat &); // e^i*theta on unit circle
    mcomplex(const mfloat &, const mfloat &); // a + ib
    ~mcomplex(void);

    mcomplex & operator=(const mcomplex &);
    mcomplex & operator+=(const mcomplex &);
    mcomplex & operator-=(const mcomplex &);
    mcomplex & operator*=(const mfloat &);
    mcomplex & operator*=(const mcomplex &);
    mcomplex & operator/=(const mfloat &);
    mcomplex & operator/=(const mcomplex &);

    friend bool operator == (const mcomplex & a, const mcomplex & b) {return a.IsEq(b);}
    friend mcomplex operator + (const mcomplex & a, const mcomplex & b) {mcomplex r(a); r+=b; return r;}
    friend mcomplex operator - (const mcomplex & a, const mcomplex & b) {mcomplex r(a); r-=b; return r;}
    friend mcomplex operator * (const mcomplex & a, const mcomplex & b) {mcomplex r(a); r*=b; return r;}
    friend mcomplex operator * (const mfloat & a, const mcomplex & b) {mcomplex r(b); r*=a; return r;}
    friend mcomplex operator * (const mcomplex & a, const mfloat & b) {mcomplex r(a); r*=b; return r;}
    friend mcomplex operator / (const mcomplex & a, const mcomplex & b) {mcomplex r(a); r/=b; return r;}
    friend mcomplex operator / (const mfloat & a, const mcomplex & b) {mcomplex r(a, 0); r/=b; return r;}
    friend mcomplex operator / (const mcomplex & a, const mfloat & b) {mcomplex r(a); r/=b; return r;}
    friend mfloat atan(const mcomplex & a) {mcomplex r(a); r.eLog("ℂ atan"); r.IM.getFirstRotation(); return r.IM;}

    mfloat getRealPart(void);
    mfloat getImaginaryPart(void);

private:
    mfloat RE, IM;

    bool IsEq(const mcomplex &) const;
    mfloat getMagnitude(void);
    mfloat getMagnitudeAndNormalize(void);
    void square_root(void);
    int agm(const mcomplex &, const string & = ""); // arithmetic-geometric mean
    int eLog(const string & = ""); // natural log w/ agm
    int taylor_agm_e(void);
    //int taylor_agm_e_exp(void);
    void multiply_with_order(const mcomplex &, char &);
    mfloat cross(const mcomplex &);
};
