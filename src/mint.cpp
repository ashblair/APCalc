#include "stdafx.h"
#include "mint.h"

bool mint::LittleEndianSys = mint::IsLittleEndian();

bool mint::IsLittleEndian(void)
{
    union
    {
        float f;
        unsigned char uc[4];
    } f_u;
    f_u.f = 3.0f;
    unsigned char B0 = f_u.uc[0], B1 = f_u.uc[1], B2 = f_u.uc[2], B3 = f_u.uc[3];
    bool LE = (B0 == 0x40) && (B1 == B0) && (B2 == 0) && (B3 == B2),
        BE = (B2 == 0x40) && (B3 == B2) && (B0 == 0) && (B1 == B0);
    assert (BE || LE);
    return LE;
    
}



mint::mint(void)
{
    positive = true;
    digits.push_back(0);
}
    
mint::mint(const mint & m)
{
    positive = m.positive;
    digits.insert(digits.end(), m.digits.begin(), m.digits.end());
}
    
mint::mint(const int & i_in)
{
    positive = (i_in >= 0);
    int i = abs(i_in);
    assert(sizeof(int) == 4);
    unsigned char d = 0;
    for (unsigned int j = 0; j < 4; ++j)
    {
        d = i % 0x100;
        digits.push_back(d);
        i /= 0x100;
    }
    while (digits.at(digits.size() -1) == 0)
    {
        if (digits.size() == 1) break;
        digits.pop_back();
    }
    if (digits.size() > 1) std::reverse(digits.begin(), digits.end());

}
    
mint::mint(const long & l_in)
{
    positive = (l_in >= 0);
    long l = abs(l_in);
    assert(sizeof(long) == 8);
    unsigned char d = 0;
    for (unsigned int j = 0; j < 8; ++j)
    {
        d = l % 0x100;
        digits.push_back(d);
        l /= 0x100;
    }
    while (digits.at(digits.size() -1) == 0)
    {
        if (digits.size() == 1) break;
        digits.pop_back();
    }
    if (digits.size() > 1) std::reverse(digits.begin(), digits.end());
}

mint::mint(const size_t & s_in)
{
    positive = true;
    size_t s = s_in;
    assert (sizeof(size_t) == 8);
    unsigned char d = 0;
    for (unsigned int j = 0; j < 8; ++j)
    {
        d = s % 0x100;
        digits.push_back(d);
        s /= 0x100;
    }
    while (digits.at(digits.size() -1) == 0)
    {
        if (digits.size() == 1) break;
        digits.pop_back();
    }
    if (digits.size() > 1) std::reverse(digits.begin(), digits.end());


}

bool mint::IsStringPositive(const string & s)
{
    size_t pos = s.find('-');
    return (string::npos == pos);
}

string  mint::RemoveExtraneousChars(const string & s)
{
    string allowables = "0123456789", r = "";
    for (int i = 0; i < s.size(); ++i)
    {
        char c = s.at(i);
        size_t pos = allowables.find(c);
        if (pos != string::npos) r += c;
    }
    return r;
}

string mint::MultiplyBinary1010(const string & a)
{
    string by2 = a + '0', by8 = a + "000";
    return AddBinary(by2, by8);

}

string mint::MultiplyBinaryByDecimal(const string & bin, unsigned char dec)
{
    assert (dec < 10);
    const char * cvt[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001"};
    if (dec == 0) return "0";
    if (dec == 1) return bin;
    string acc = "0", sfx0 = "", b = cvt[dec];
    for (size_t sz = 5; sz > 0; --sz)
    {
        char unit = b.at(sz - 1);
        string bpp = bin + sfx0;
        if (unit == '1') acc = AddBinary(acc, bpp);
        sfx0 += '0';
    }
    return acc;
}

string mint::AddDecimal(const string&a, const string &b)
{
    string r = "";
    unsigned char carry = 0;
    size_t aSz = a.size(), bSz = b.size(), mSz = aSz > bSz? aSz: bSz;
    for (size_t s = 0; s < mSz; ++s)
    {
        unsigned char aChr = s >= aSz? 0: a.at(aSz - 1 - s) - '0',
            bChr = s >= bSz? 0: b.at(bSz - 1 - s) - '0',
            c = aChr + bChr + carry;
        carry = c / 10;
        c %= 10;
        char rChr = c + '0';
        r = rChr + r;
    }
    char pfx = carry + '0';
    if (carry > 0) r = pfx + r;
    else
    {
        while ((r.size() > 1) && (r.at(0) == '0')) r = r.substr(1);
    }
    
    return r;
}
    
string mint::MultiplyDecimal(const string &a, const string & b)
{
    string r = "0", sfx = "";
    size_t aSz = a.size(), bSz = b.size();
    for (size_t i = aSz; i > 0; --i)
    {
        unsigned char aChr = a.at(i - 1) - '0', carry = 0;
        char rChr = ' ';
        string acc = "";
        for (size_t j = bSz; j > 0; --j)
        {
            unsigned char bChr = b.at(j - 1) - '0', pdct = bChr * aChr + carry;
            carry = pdct / 10;
            pdct %= 10;
            rChr = pdct + '0';
            acc = rChr + acc;
        }
        rChr = carry + '0';
        if (carry > 0) acc = rChr + acc;
        acc += sfx;
        r = AddDecimal(r, acc);
        sfx += "0";
    }

    return r;
}

string mint::print(void)
{
    string r = "0", pFact = "1", base = "256", uStr = "";
    size_t dSz = digits.size();
    //cout << "Number of digits (base 256): " << to_string(dSz) << "\n";
    for (size_t s = dSz; s > 0; --s)
    {
        //cout << to_string(s) << " " << flush;
        unsigned char unit = digits.at(s - 1);
        uStr = to_string(unit);
        //uStr = static_cast<char>(unit);
        if (unit > 0) r = AddDecimal(r, MultiplyDecimal(pFact, uStr));
        pFact = MultiplyDecimal(base, pFact);
    }
    //cout << "\n";
    if (!positive) r = "-" + r;
    return r;
}

string mint::AddBinary(const string & a, const string & b)
{
    size_t aSz = a.size(), bSz = b.size();
    string A = a, B = b;
    if (aSz > bSz) B.insert(B.begin(), (aSz - bSz), '0');
    if (bSz > aSz) A.insert(A.begin(), (bSz - aSz), '0');
    string r = A;
    bool carry = false;
    for (size_t sz = 1 + A.size(); sz > 0; --sz)
    {
        char ac = A.at(sz - 1), bc = B.at(sz - 1), unit = '0', nxt = '0';
        assert(((ac == '0') || (ac == '1')) && ((bc == '0') || (bc == '1')));
        if (ac != bc) unit = '1';
        else 
        {
            if (ac == '1') nxt = '1';
        }
        if (carry)
        {
            unit = unit == '0'? '1': '0';
            nxt = unit == '0'? '1': '0';
        }
        carry = nxt == '1';
        r = unit + r;
    }
    if (carry) r = '1' + r;
    return r;
}


string mint::ConvertToBinary(const string & s)
{
    string powerfact = "1", conversion = "0";
    for (size_t sz = s.size() + 1; sz > 0; --sz)
    {
        unsigned char c = s.at(sz - 1) - '0';
        conversion = AddBinary(conversion, MultiplyBinaryByDecimal(powerfact, c));
        powerfact = MultiplyBinary1010(powerfact);
    }
    size_t cSz = conversion.size(), zCt = cSz % 8;
    if (zCt > 0) conversion.insert(conversion.begin(), zCt, '0');
    return conversion;
}

mint::mint(const string & s_in)
{
    positive = IsStringPositive(s_in);
    string decimalStr = RemoveExtraneousChars(s_in), 
        bStr = ConvertToBinary(decimalStr);
    size_t chrCount = bStr.size() / 8;
    for (size_t sz = 0; sz < chrCount; ++sz)
    {
        unsigned char unit = 0, orFact0 = 0x80;
        size_t b_at = sz * 8;
        for (int j = 0; j < 8; ++j)
        {
            unsigned char orFact = orFact0 >> j,
                bunit = bStr.at(b_at + j);
            if (bunit == '1') unit |= orFact;
        }
        digits.push_back(unit);
    }
}
    
mint::~mint(void)
{

}

mint & mint::operator=(const mint & m)
{ // assignment operator
    positive = m.positive;
    digits.clear();
    digits.insert(digits.end(), m.digits.begin(), m.digits.end());
    return *this;
}

unsigned int mint::getNth(size_t n, const vector<unsigned char>& a)
{ 
    unsigned int r = 0;
    size_t aSz = a.size();
    if (n < aSz) r = a.at(aSz - 1 - n);
    return r;
}


vector<unsigned char> mint::AddBinary(const vector<unsigned char>&a, const vector<unsigned char>&b)
{
    size_t aSz = a.size(), bSz = b.size(), mSz = aSz < bSz? bSz: aSz;
    vector<unsigned char> r;
    //bool carryOver = false;
    unsigned int ufact0 = 0x80, cfact0 = 0x100, cfact1 = 0xff, carry = 0;
    for (size_t sz = 0; sz < mSz; ++sz)
    {
        unsigned int aChar = getNth(sz, a), bChar = getNth(sz, b), c = aChar ^ bChar, adj = 0;
        for (int i = 7; i >= 0; --i)
        {
            unsigned int cfactOUT = cfact0 >> i,
                cfactIN = cfact0 >> (i + 1), 
                ufact = ufact0 >> i,
                bitA = aChar & ufact,
                bitB = bChar & ufact,
                bitC = carry & cfactIN; 

            bool setMe = ((bitC == 0) && ((bitA != 0) && (bitB != 0))) || 
                ((bitC != 0) && !((bitA == 0) && (bitB == 0)));
            if (setMe) carry |= cfactOUT;
        }
        //carryOver = (0 != (carry & cfact0));
        adj = carry & cfact1;
        c ^= adj;
        //adj = static_cast<unsigned char>(carry);
        unsigned char sum = static_cast<unsigned char>(c);
        r.push_back(sum);
        carry >>= 8;
    }
    if (carry != 0) r.push_back(1);
    std::reverse(r.begin(), r.end());
    return r;
}
    
vector<unsigned char>  mint::SubtractBinary(const vector<unsigned char>&a, const vector<unsigned char>&b)
{ // magnitude of a must exceed that of b - check before calling please
    size_t aSz = a.size(), bSz = b.size();
    assert (aSz >= bSz);
    vector<unsigned char> r;
    //bool carryOver = false;
    unsigned int ufact0 = 0x80, cfact0 = 0x100, cfact1 = 0xff;
    bool borrow = false;
    for (size_t sz = 0; sz < aSz; ++sz)
    {
        unsigned int aChar = getNth(sz, a), bChar = getNth(sz, b), c = 0;
        for (int i = 7; i >= 0; --i)
        {
            unsigned int ufact = ufact0 >> i,
                byteA = aChar & ufact,
                byteB = bChar & ufact,
                xOr = byteA ^ byteB,
                notxOr = xOr == 0? ufact: 0;
            bool bitA = (byteA != 0), bitB = (byteB != 0);
            c |= borrow? notxOr: xOr;
            borrow = borrow? !(bitA && !(bitB)): !(bitA) && bitB; 
        }
        //carryOver = (0 != (carry & cfact0));
        //adj = carry & cfact1;
        //adj = static_cast<unsigned char>(carry);
        unsigned char minus = static_cast<unsigned char>(c);
        r.push_back(minus);
    }
    assert (!(borrow));
    for (size_t sz = r.size(); sz > 1; --sz)
    {
        unsigned char msb = r.at(sz - 1);
        if (msb == 0) r.pop_back();
        else break;
    }
    std::reverse(r.begin(), r.end());
    return r;
}


mint & mint::operator+=(const mint & m)
{
    if (positive == m.positive) digits = AddBinary(digits, m.digits);
    else
    {
        int cmp = compare(m.digits);
        switch (cmp)
        {
        case -1:
            positive = m.positive;
            digits = SubtractBinary(m.digits, digits);
            break;
        case 0:
            positive = true;
            digits.clear();
            digits.push_back(0);
            break;
        case 1:
            digits = SubtractBinary(digits, m.digits);
            break;
        }
    }
    return *this;
}
    
mint & mint::operator-=(const mint & m)
{
    if (positive != m.positive) digits = AddBinary(digits, m.digits);
    else
    {
        int cmp = compare(m.digits);
        switch (cmp)
        {
        case -1:
            positive = m.positive;
            digits = SubtractBinary(m.digits, digits);
            break;
        case 0:
            positive = true;
            digits.clear();
            digits.push_back(0);
            break;
        case 1:
            digits = SubtractBinary(digits, m.digits);
            break;
        }
    }
    return *this;
}

unsigned char mint::preceedingZeros(unsigned char unit)
{
    unsigned char uFact0 = 0x80, i = 0;
    for (i = 0; i < 8; ++i)
    {
        if (((uFact0 >> i) & unit) != 0) break;
    }
    return i;
}

 vector<unsigned char> mint::shiftLeft(const unsigned char ls)
 {
    assert(ls < 8);
    vector<unsigned char> r;
    size_t dSz = digits.size();
    unsigned char a = digits.at(0), 
        mask0 = 0xff, rs = 8 - ls, 
        maskR = mask0 >> ls, 
        maskL = mask0 << rs, 
        h2l = (a & maskL) >> rs, 
        l2h = (a & maskR) << ls;
    if (h2l != 0) r.push_back(h2l);
    a = l2h;
    for (size_t s = 1; s < dSz; ++s)
    {
        unsigned char dChar = digits.at(s);
        h2l = (dChar & maskL) >> rs;
        a |= h2l;
        r.push_back(a);
        l2h = (dChar & maskR) << ls;
        a = l2h;
    }
    r.push_back(a);
    return r;
 }

mint & mint::operator*=(const mint & m)
{
    if (IsEq(0) || m.IsEq(0))
    {
        positive = true;
        digits.clear();
        digits.push_back(0);
    }
    else
    {
        positive = (positive == m.positive);
        vector<unsigned char> a, t;
        size_t mSz = m.digits.size();
        a.push_back(0);
        unsigned char uFact0 = 0x80;
        for (size_t s = 0; s < mSz; ++s)
        {
            unsigned char c = m.digits.at(s);
            if (c != 0)
            {
                for (unsigned char i = 0; i < 8; ++i)
                {
                    unsigned char uFact = uFact0 >> i;
                    if ((uFact & c) != 0)
                    {
                        if (i < 7) t = shiftLeft(7 - i);
                        else t = digits;
                        size_t app0s = mSz - s - 1;
                        if (app0s > 0) t.insert(t.end(), app0s, 0);
                        a = AddBinary(a, t);
                    }
                }
            }
        }

        digits = a;    
    }
    
    return *this;
}

void mint::shiftLeftFillRight(const size_t & idx, const vector<unsigned char>& num)
{
    unsigned char msbMask = 0x80, hi2loMask = msbMask, lo2hiMask = 0x7f, c = digits.at(0), hi = c & hi2loMask, lo = c & lo2hiMask,
        num_chr = num[idx / 8], num_mask = msbMask >> (idx % 8), num_bit = (num_chr & num_mask) >> (7 - (idx % 8));

    size_t dSz = digits.size();

    hi >>= 7;
    lo <<= 1;

    bool prependMe = (hi == 1) ;

    unsigned char a = lo;

    for (size_t i = 1; i < dSz; ++i)
    {
        c = digits[i];
        hi = c & hi2loMask;
        hi >>= 7;
        a |= hi;
        digits[i - 1] = a;
        lo = c & lo2hiMask;
        lo <<= 1;
        a = lo;
    }

    digits[dSz - 1] = a | num_bit;
    if (prependMe) digits.insert(digits.begin(), 1);
}


mint & mint::operator/=(const mint & m)
{
    assert (!(m.IsEq(0)));
    int cmp = compare(m.digits);
    if ((IsEq(0)) || (cmp < 0))
    {
        positive = true;
        digits.clear();
        digits.push_back(0);
    }
    else
    {
        positive = (positive == m.positive);
        if (cmp == 0)
        {
            digits.clear();
            digits.push_back(1);
        }
        else
        {
            size_t dSz = digits.size(), bitCount = dSz * 8;
            vector<unsigned char> num = digits, q;
            digits.clear();
            digits.push_back(0);
            unsigned char qChr = 0, bitMask0 = 0x80;
            bool qStarted = false;
            for (size_t s = 0; s < bitCount; ++s)
            {
                unsigned char cIdx = s % 8, bitMask = bitMask0 >> cIdx;
                if ((s > 0) && (cIdx == 0) && qStarted) 
                {
                    q.push_back(qChr);
                    qChr = 0;
                }
                shiftLeftFillRight(s, num);
                cmp = compare(m.digits);
                if (cmp >= 0)
                {
                    qStarted = true;
                    qChr |= bitMask;
                    digits = SubtractBinary(digits, m.digits);

                }
            }
            if (qStarted) q.push_back(qChr);
            else q.push_back(0);
            digits = q;
        }
    }
    
    return *this;
}

void mint::factorial(void)
{
    if ((IsEq(1) || IsLT(1))) 
    {
        positive = true;
        digits.clear();
        digits.push_back(1);
    }
    else
    {
        mint dec = *this;
        do
        {
            //cout << dec.print() << "\t";
            dec -= 1;
            *this *= dec;
        } while (dec.IsGT(1));
        //cout << "\n";
    }

}

mint & mint::operator++(void)
{
    vector<unsigned char> buff;
    buff.push_back(1);
    if (positive) digits = AddBinary(digits, buff);
    else digits = SubtractBinary(digits, buff);
    if (IsEq(0)) positive = true;
    return *this;
}

mint mint::operator++(int)
{
    mint r(*this);
    vector<unsigned char> buff;
    buff.push_back(1);
    if (positive) digits = AddBinary(digits, buff);
    else digits = SubtractBinary(digits, buff);
    if (IsEq(0)) positive = true;
    return r;
}

mint & mint::operator--(void)
{
    if (IsEq(0)) 
    {
        positive = false;
        digits[0] = 1;
    }
    else
    {
        vector<unsigned char> buff;
        buff.push_back(1);
        if (positive) digits = SubtractBinary(digits, buff);
        else digits = AddBinary(digits, buff);
        
    }
    return *this;
    
}

mint mint::operator--(int)
{
    mint r(*this);
    if (IsEq(0)) 
    {
        positive = false;
        digits[0] = 1;
    }
    else
    {
        vector<unsigned char> buff;
        buff.push_back(1);
        if (positive) digits = SubtractBinary(digits, buff);
        else digits = AddBinary(digits, buff);
        
    }
    return r;

}

mint & mint::operator%=(const mint & m)
{
    assert (!(m.IsEq(0)));
    int cmp = compare(m.digits);
    if ((IsEq(0)) || (cmp == 0))
    {
        positive = true;
        digits.clear();
        digits.push_back(0);
    }
    else
    {
        positive = (positive == m.positive);
        if (cmp > 0)
        {
            size_t dSz = digits.size(), bitCount = dSz * 8;
            vector<unsigned char> num = digits, q;
            digits.clear();
            digits.push_back(0);
            unsigned char qChr = 0, bitMask0 = 0x80;
            bool qStarted = false;
            for (size_t s = 0; s < bitCount; ++s)
            {
                unsigned char cIdx = s % 8, bitMask = bitMask0 >> cIdx;
                if ((s > 0) && (cIdx == 0) && qStarted) 
                {
                    q.push_back(qChr);
                    qChr = 0;
                }
                shiftLeftFillRight(s, num);
                cmp = compare(m.digits);
                if (cmp >= 0)
                {
                    qStarted = true;
                    qChr |= bitMask;
                    digits = SubtractBinary(digits, m.digits);

                }
            }
            if (qStarted) q.push_back(qChr);
            else q.push_back(0);
        }
    }

    return *this;
}


bool mint::IsEq(const mint & m) const
{
    if (m.positive != positive) return false;
    if (m.digits.size() != digits.size()) return false;
    return (0 == compare(m.digits));
}

bool mint::IsLT(const mint & m) const
{
    if (m.positive != positive) return m.positive;
    int cmp = compare(m.digits), pInt = positive? 1: -1, adj = cmp * pInt;
    return (adj < 0);    
}

bool mint::IsGT(const mint & m) const
{
    if (m.positive != positive) return positive;
    int cmp = compare(m.digits), pInt = positive? 1: -1, adj = cmp * pInt;
    return (adj > 0);    
}

int mint::compare(const vector<unsigned char>& a)  const // -1=less:0=equal:+1=greater
{ // magnitudes only, sign is not considered
    size_t aSz = a.size(), tSz = digits.size();
    int r = 0;
    if (aSz != tSz)
    {
        r = aSz < tSz? 1: -1;
        return r;
    }
    for (size_t sz = 0; sz < tSz; ++sz)
    {
        unsigned char aChr = a.at(sz), tChr = digits.at(sz);
        if (aChr != tChr) 
        {
            r = aChr < tChr? 1: -1;
            return r;
        }
    }
    return r;
}

mint::operator double(void)
{
    union {
        double ud;
        unsigned char uc[8];
    } d;
    for (int i = 0; i < 8; ++i)
    {
        d.uc[i] = 0;
    }
    double r = d.ud;
    if (IsEq(0)) return r;
    
    // PZ could be 8 if mint is 0:
    int tSz = digits.size(), PZ = preceedingZeros(digits.at(0)), exponent = 8 * tSz - 1 - PZ,
        e0 = (exponent > 1024)? 1024: (exponent < 0)? -1023: exponent, tCharIdx = -1;
    unsigned int e1 = static_cast<unsigned int>(e0 + 1023);

    unsigned char S = positive? 0: 1, E0 = static_cast<unsigned char>(e1 >> 4), 
        E1 = static_cast<unsigned char>(e1 & 0xf), 
        tByte = 0, cByte = 0, nxtByte = 0, B0, B1, 
        delta = 11 - PZ, flt = 0x80, f_i = 0, f_j = 0,
        im8 = 0, jm8 = 0, bit = 0;

    for (int i = 12; i < 64; ++i) 
    {
        int id8 = i / 8,
            j = i - delta, // bit index in digits
            jd8 = j / 8;
        im8 = i % 8;
        jm8 = j % 8;
        f_i = flt >> im8;
        f_j = flt >> jm8;

        if (jd8 != tCharIdx)
        {
            tCharIdx = jd8;
            tByte = tCharIdx < tSz? digits.at(tCharIdx): 0;
        }
        bit = (tByte & f_j) >> (7 - jm8);
        if (bit == 1) d.uc[id8] |= f_i;
    }

    B0 = (S << 7) | E0;
    B1 = (E1 << 4) | d.uc[1];
    d.uc[0] = B0;
    d.uc[1] = B1;

    if (!LittleEndianSys)
    {
        unsigned char buff[8];
        memcpy(buff, d.uc, 8);
        for (size_t i = 0; i < 8; ++i)
        {
            d.uc[i] = buff[7 - i];
        }
    }
    r = d.ud;
    return r;
    
}


