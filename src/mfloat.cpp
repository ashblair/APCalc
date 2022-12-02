#include "stdafx.h"
//#include "mint.h"
#include "mfloat.h"

// static stuff:
int mfloat::DMAX = 1011, mfloat::BMAX = 3376, mfloat::BROUND = 3360, mfloat::DROUND = 1001, mfloat::LOG_BROUND = 12;

//Glib::ustring mfloat::exp_char = "⏨";
display_float mfloat::disp;
bool mfloat::LittleEndianSys = mfloat::IsLittleEndian(),
    mfloat::SigFigsLoaded = mfloat::LoadSigFigs();
const char * mfloat::_constants[] = {"LN_2", "LN_5", "LN_10", "LN_2_OVER_10", "LN_10_OVER_2", "EXP_1", "P_I"};
store_float mfloat::_ln2, 
            mfloat::_ln5, 
            mfloat::_ln10, 
            mfloat::_ln10oln2, 
            mfloat::_ln2oln10, 
            mfloat::_exp1, 
            mfloat::_pi;
/*
store_float mfloat::ln_2 =         {0x128, -1, 1066, "62E42FEFA39EF35793C7673007E5ED5E81E6864CE5316C5B141A2EB71755F457CF70EC40DBD75930AB2AA5F695F43621DA5D5C6B827042884EAE765222D3704A7D2D942C4495D18A3597B42262F870FD73D53787626CC0764ADF41D8ECAFEE96E59D0F633ACA9195EBBF4D7A70606490CABF430E5E41C745B45B2F8A1E7FAB8C0FE99423F6B7F720C21A61F11FCAA345DCAD3ADBF83DF42AFA5C47BC2801672C2E8C0EEBB71321CB9287CE6568F39A6799989CCB2726A29898343C17A3AC12BA4ACD36666AC9466ED538FF14BC291D040E9B6C02B9FCF546189014A82E6A1A592ABAA2F363C2F73B5C6279B6D8C0D9620F1EE6BA365B6636BEA16A30A0C983169A2C5B6766CB0A7AEB31432A35C4E7DCAAE16D8D1F2D30692DA9CDA6615F113689404AA8E639B91D42E527A245149DF31ADEA2EFF79E0EAA4D14B83F2A717304C35FFA88D639479EBD24457118CDA78A844307DB9328421217762DF5E7B293E46DC056419DD10D720B8251AA7A17A5F2C426C632D5EA060400C1C93210723418AE6737457D74FA0A558B6C3989D240F9DE5E19C5AE6E72B1AEC44CB1203CC8D52A3088C1B89A49"},
            mfloat::ln_5 =         {0x128, 0, 2885, "9C041F7ED8D336AFDF77A516075931F4494C70C0F6DF2E0C850B62AC7C15BB9E7103953E58B494DADC2DDC0566821A8FC459E22B42F76A27C6E6A6E6FA2AA334A21D187407E75BB4BE9EC0FD91E48F7103B09EFD7998BBAE20174C3AD20F27A3B6D045BAF01BF94B446D3377D9B23EF506C31FD82896A49A404CFE753CD7D04181297518B98FBED212499FC118B706C3A3A48F2C62127B29EF467FCB4B53436D78E9C7BA9CC6B8C34C958C45E5931A3C053257521908F036720703AED506F71BD28E56129CD512817686A3BF20A7E0A99AB369C48F37F29F98DFA0576672956B489B8C07886F69E5DFF81F2893184A15AE207CA24559350DD370649D3684D0B07150F5E426F7B79B7071FC9D76950B31CF98CF19D4B3518456EF0C95851D2C8392F2A1CE9079A79C08257EC3A6B0C07964245889BC970E4355EA7D90EC60274ED3CA13B816740A8CCAF9238091D71B90FD129CDB6058A9927026511CB97F7EF6D19BAC61F127BBC97DA5E0ACA81E8AC679E975DD5538A9CDD0507EE2DA55FAAB5E73295447C65FBDAE8380E96B70D99D782C3B57B444BB5668B9BC7A68330440E7DAEA6B861F21"},
            mfloat::ln_10 =        {0x128, 1, 0, "26BB1BBB5551582DD4ADAC5705A61451C51FD9F3B4BBF21D078C3D0403E05AE52C5E05AF635020B998E1978058BE1AD058C448308217C5B5F71EF10805CA2DACF059F1451519223CECB54D8761B063F7DECD9D6095678DF4A2C37693A4338F7794CF66B646C0A10B1D266D1A88F1389EB61160AFABDBC41E8D3D4B1D260BD303C48F1F955A75DD3139AB685CD44E2C3348FD964D2F18BA9FB63A51D4AFA9FB81C817E7983C2824D48AECB9BC4D0673B7E8FF52DBD64E20C15F1090DD536E803C7BFA78A2E91CDADC709191A4BF5E3795D1008FE2F61B36A15293D555BED3D14BEEFC6EC09D2872C1C714AE01FFBC5B635AD7F7FFB043741499608CDAC374C91DDF3391CBED2E9E6C73054F1948BBBF901284C2F03224F4DC76E1F9B45AE65A8F6BC9639181CB421554CC094A649D87B978C9D500DC330ACC3E3A6CD840CC70689ABD087E40C8572E14C5A31C8F1EF7AB1F9A106494F6654DBDF0B40BD6AC6474843DEBC16008214141B384C0F2952EDFEDFE6C7B6016D667E858B1BDF1478A5BDAD3627B83406E616CA49B83182CFD0D33ADA41D45BDFA57A00DF1697C28B455BE79976631362280"},
            mfloat::ln_2_over_10 = {0x128, -2, 0, "34413509F79FEF311F12B35816F922F04D5A618A87A3E69314BCDE4D6F98C79650D45B03233F57A13CB978E668E37A25228E692B6317243CB16A4FEA4AA5A598BF06FBDC04AAB97939E3A321880C05CBA4D84E5FBCE205E9D72225362B25B3B8091AFD4B3D62A7B01610678B28357042D46CF70279E991F7BDD462EF91F119557FF00142B5B0CEBAA34A17EE86ACB5B8A23257DABCAA93450D4AA3C28773F1C194019A41C2BC793E276995148F36C5EACBD4F8B1D2B37B9C7652CE684F70EBFEFDBF5F5B31E729813E9DA6BC5D590C881EA1965B9CA185D2B7C7A53DD6035FDA3F4E9BC12644CF40F3CEBDC5793AB9B46B43759A9F6C2895F17E6366D44AF65BBB4CD8D08F83B2FEC9C494FC7BE46299B033AB193D5E904DBA92EC9DDC73DE1CDD8EA7EA87DB46142505E2266732DE59785807AB507E4DDF732DBAADA925036CAD850F6FFA0142C0EA0A55643F3D6C603B38E7AEE32E6CB4E633D1F89EDB460B04F7212D22E9187FD1AA928C687A5F424A6CEC7DAF32467EC8F252660918C83E44F6430B41A337C5D80E33317E186F4175F335374D16071A96FB1420C889459228F0C5AB4C8860"},
            mfloat::ln_10_over_2 = {0x128, 1, 0, "A934F0979A3715FC9257EDFE9B5FB699B2D8ABFC6F675A9D236D590105CF0B3A0CCA1FBD3BAA3E747C497D56C75A17AC286BDC900ACB94A99FE2C59A9EC06703EC9F2D82FB36BA9BFDCD84D71F1937A070BCBF203985A3591D1EEAEEA212A6170CB18DBFD47DDAE2609F11687D6570DF5526C79F38331189AD389784113C3EC2D776E587D34A9FBA34BC7E23242362BBDF47F52F18843F0CC63F820B491A61D9623768A9E55F8D24062DAFD9DD45E33B26054A2B44D7DD9E51A086E02EA5637C8B4E5D34B97A6A70A201C29E99678DE2E35BF5F2F192CD11E2E43F1EF1BCDC0EAE16700D51F2A4B22FC1D844693FC50A38E1887000DBAD926924F8A801609DB7FAD2FA010FBA6A4097D96B0A284BC28A2F2D81BA86F4CD93868FC3473B99A800960CA07A8E0D84CD0961899999EC0EF97D7BE0AE1BEA85509CDABF2D97F508E51B9DF32D4933A51E39AE40DE9C0BE4740579DC1AE55D9156E64D0281590C89C0FBD82EB582DBC01D31D438CB4D583BE22377480BF2183FA159FF320E2924A646046C6537D668DA6BDA1F37F7B218814EC41DA3C36EE127A2EB217EECF950E48C5D447DBCB6D3E4"},
            mfloat::exp_1 =        {0x128, 1, 457, "5BF0A8B1457695355FB8AC404E7A79E3B1738B079C5A6D2B53C26C8228C867F799273B9C49367DF2FA5FC6C6C618EBB1ED0364055D88C2F5A7BE3DABABFACAC24867EA3EBE0CDDA10AC6CAAA7BDA35E76AAE26BCFEAF926B309E18E1C1CD16EFC54D13B5E7DFD0E43BE2B1426D5BCE6A6159949E9074F2F5781563056649F6C3A21152976591C7F772D5B56EC1AFE8D03A9E8547BC729BE95CADDBCEC6E57632160F4F91DC14DAE13C05F9C39BEFC5D98068099A50685EC322E5FD39D30B07FF1C9E2465DDE5030787FC763698DF5AE6776BF9785D84400B8B1DE306FA2D07658DE6944D8365DFF510D68470C23F9FB9BC6AB676CA3206B77869E9BDF3380470C368DF93ADCD920EF5B23A4D23EFEFDCB31961F5830DB2395DFC26130A2724E1682619277886F289E9FA88A5C5AE9BA6C9E5C43CE3EA97FEB95D0557393BED3DD0DA578A446C741B578A432F361BD5B43B7F3485AB88909C1579A0D7F4A7BBDE783641DC7FAB3AF84BC83A56CD3C3DE2DCDEA5862C9BE9F6F261D3C9CB10AF6D58FABE85AD3EDA30EEC79E3AAA0680090FEAB74AFC6398F4E26B910DDF686315DAD43C025B3CDF"},
            mfloat::p_i =          {0x128, 1, 0, "921FB54442D18469898CC51701B839A252049C1114CF98E804177D4C76273644A29410F31C6809BBDF2A33679A748636605614DBE4BE286E9FC26ADADAA3848BC90B6AECC4BCFD8DE89885D34C6FDAD617FEB96DE80D6FDBDC70D7F6B5133F4B5D3E4822F8963FCC9250CCA3D9C8B67B8400F97142C77E0B31B4906C38ABA734D22C7F51FA499EBF06CABA47B9475B2C38C5E6AC410AA5773DAA520EE12D2CDACE186A9C95793009E2E8D811943042F86520BC8C5C6D9C77C73CEE58301D0C07364F0745D80F451F6B8ABBE0DE98A593BC5797ED2AB02E30732A92F9D52AD5CA2BA44C3131F40A202AE51CB51555885B5A662E1A08A0F46750AA4357BE3974C9D9F70A08B1B7DE1515D4E2AEBA0C18FB672E1F0B4DC3C98F57EB5D19B61267AE3D1929C0944AC33B9DC7A44C35A5DCD7E25FF40DB31410C9B0EC04E67D90D4C8A43E56302EF6401977C22EAEF4C2BAD8EE13118175B28DC411C49F40E9CB566287B6B7F9C1FA211C9705A2415242100234E478254F0FCDAF10E334217B74B64D33864E30D5E9C4783528D0696C2A17B44B07D39455A899D1B77785B609BD1DF25D"};
*/
bool mfloat::IsLittleEndian(void)
{ // this is backwards
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

bool mfloat::DoesPathExist(const string & path)
{
    struct stat f_s;
    return (0 == stat(path.c_str(), &f_s));

}
    
bool mfloat::LoadSigFigs(void)
{
    DMAX = 1011;
    BMAX = 3376;
    BROUND = 3360;
    DROUND = 1001;
    LOG_BROUND = 12;

    string the_path = "./constants/stats";
    bool DPE = DoesPathExist(the_path);
    if (DPE)
    {
        ifstream cIn;
        cIn.open(the_path, ifstream::in | ifstream::binary);
        char rBuff[10];
        assert (sizeof(int) == 4);
        cIn.read(rBuff, 4);
        memcpy(&DROUND, rBuff, 4);
        cIn.read(rBuff, 4);
        memcpy(&DMAX, rBuff, 4);
        cIn.read(rBuff, 4);
        memcpy(&BROUND, rBuff, 4);
        cIn.read(rBuff, 4);
        memcpy(&BMAX, rBuff, 4);
        cIn.read(rBuff, 4);
        memcpy(&LOG_BROUND, rBuff, 4);
        cIn.close();
    }
    else SaveSigFigs();
    return true;
}
    
bool mfloat::SaveSigFigs(void)
{
	ofstream cOUT;
    string fDir = "./constants", fPath = fDir + "/stats";
    bool DPE = DoesPathExist(fDir);
    //int dirExist = stat(fDir.c_str(), &f_s);
    if (!DPE)
    { // directory does not exist:
        mode_t m = S_IRWXU;
        int m_d = 0;
        #ifdef _CROSS_COMPILE
        m_d = mkdir(fDir.c_str());
        #else
        m_d = mkdir(fDir.c_str(), m);
        #endif
        if (m_d < 0)
        {
            //cout << "Cannot make directory " << fDir << " or file " << _constants[c] << " (this can make things very slow)\n";
            disp.write("Cannot make directory " + fDir + " (the change of significant figures will not persist)\n\n");
            return false;
        }
    }
    cOUT.open(fPath, ofstream::out | ofstream::trunc | ofstream::binary);
    cOUT.write((const char *)&DROUND, sizeof(int));
    cOUT.write((const char *)&DMAX, sizeof(int));
    cOUT.write((const char *)&BROUND, sizeof(int));
    cOUT.write((const char *)&BMAX, sizeof(int));
    cOUT.write((const char *)&LOG_BROUND, sizeof(int));
    cOUT.close();
    return true;
}


// mfloat constructors & other methods:
mfloat::mfloat(void)
{ // constructs 0
    zero = true;
    nan = false;
    pos = true;
    inf = false;
    sub = false;
    exponent = 0;

}

mfloat::mfloat(const mfloat & f)
{
    zero = f.zero;
    nan = f.nan;
    pos = f.pos;
    inf = f.inf;
    sub = f.sub;
    exponent = f.exponent;
    if (f.sig.size() > 0) sig = f.sig;
    //sig.insert(sig.end(), f.sig.begin(), f.sig.end());

}

mfloat::mfloat(const float & f)
{
    zero = false;
    nan = false;
    pos = false;
    inf = false;
    sub = false;

    union {
        float uf;
        unsigned char uc[4];
    } f_union;
    f_union.uf = f;
    if (!LittleEndianSys)
    {
        unsigned char buff[4];
        memcpy(buff, f_union.uc, 4);
        for (unsigned char i = 0; i < 4; ++i)
        {
            f_union.uc[i] = buff[3 - i];
        }
    }
    unsigned char B0 = f_union.uc[0], B1 = f_union.uc[1], B2 = f_union.uc[2], B3 = f_union.uc[3],
        S = B0 >> 7, E = (B0 << 1) | (B1 >> 7), s[3];
    s[0] = (B1 << 1) | (B2 >> 7);
    s[1] = (B2 << 1) | (B3 >> 7);
    s[2] = B3 << 1;  
    bool sigZero = (0 == (s[0] | s[1] | s[2]));
    exponent = static_cast<int>(E) - 127;
    if (exponent == 128)
    {
        pos = true;
        if (sigZero) inf = true;
        else nan = true;
        return;
    }
    
    if (exponent == -127)
    {
        pos = true;
        if (sigZero) zero = true;
        else sub = true;
        return;
    }
    pos = (S == 0);
    for (int i = 0; i < 3; ++i)
    {
        sig.push_back(s[i]);
    }
    while ((sig.size() > 0) && (sig.at(sig.size() - 1) == 0))
    {
        sig.pop_back();
    }
}

mfloat::mfloat(const double & d)
{
    zero = false;
    nan = false;
    pos = false;
    inf = false;
    sub = false;

    union {
        double ud;
        unsigned char uc[8];
    } d_u;
    d_u.ud = d;
    if (!LittleEndianSys)
    {
        unsigned char buff[8];
        memcpy (buff, d_u.uc, 8);
        for (unsigned char i = 0; i < 8; ++i)
        {
            d_u.uc[i] = buff[7 - i];
        }
    }
    unsigned char B0 = d_u.uc[0], B1 = d_u.uc[1], B2 = d_u.uc[2], B3 = d_u.uc[3],
        B4 = d_u.uc[4], B5 = d_u.uc[5], B6 = d_u.uc[6], B7 = d_u.uc[7],
        S = B0 >> 7, s[7];
    s[0] = (B1 << 4) | (B2 >> 4); 
    s[1] = (B2 << 4) | (B3 >> 4);
    s[2] = (B3 << 4) | (B4 >> 4);
    s[3] = (B4 << 4) | (B5 >> 4);
    s[4] = (B5 << 4) | (B6 >> 4);
    s[5] = (B6 << 4) | (B7 >> 4);
    s[6] = B7 << 4;
    unsigned int E = ((B0 & 0x7f) << 4) | (B1 >> 4);
    unsigned char s_z = 0;
    for (int i = 0; i < 7; ++i)
    {
        s_z |= s[i];
    }
    bool sigZero = (0 == s_z);
    exponent = static_cast<int>(E) - 1023;
    if (exponent == 1024)
    {
        pos = true;
        if (sigZero) inf = true;
        else nan = true;
        return;
    }
    
    if (exponent == -1023)
    {
        pos = true;
        if (sigZero) zero = true;
        else sub = true;
        return;
    }
    pos = (S == 0);
    for (int i = 0; i < 7; ++i)
    {
        sig.push_back(s[i]);
    }
    while ((sig.size() > 0) && (sig.at(sig.size() - 1) == 0))
    {
        sig.pop_back();
    }
}

mfloat::mfloat(const int & iIn)
{
    zero = (iIn == 0);
    nan = false;
    pos = (iIn >= 0);
    inf = false;
    sub = false;
    exponent = 0;
    if ((zero) || (nan) || (inf) || (sub)) return;
    int buff = iIn, iflt0 = 0xff, iflt = 0;
    if (!pos) get2sComplement(buff);
    unsigned char iChar[] = {0, 0, 0, 0}, 
        cflt0 = 0x1, cflt = 0, bit = 0, oChar = 0;
    for (int i = 0; i < 4; ++i)
    {
        iflt = iflt0 << (8 * i);
        iChar[i] = (buff & iflt) >> (8 * i);
    }
    int firstNZ = -1;
    for (int i = 3; i >= 0; --i)
    {
        if (iChar[i] != 0)
        {
            for (int j = 7; j >= 0; --j)
            {
                cflt = cflt0 << j;
                bit = (iChar[i] & cflt) >> j;
                if (bit == 1)
                {
                    firstNZ = 8 * i + j;
                    j = 0;
                    i = 0;
                }
            }
        } 
    }
    exponent = firstNZ;
    int s = firstNZ - 1, j = 0, iCharIdx = -1, id8 = 0;
    unsigned char jm8 = 7, im8 = 0;
    for (int i = s; i >=0; --i)
    {
        id8 = i / 8;
        im8 = i % 8;
        j = s - i; // 0,1,...,s
        jm8 = j % 8;
        cflt = cflt0 << im8;
        bit = (iChar[id8] & cflt) >> im8;
        oChar |= bit;
        if (jm8 == 7)
        {
            sig.push_back(oChar);
            oChar = 0;
        }
        else oChar <<= 1;
    }
    if (oChar != 0)
    {
        oChar <<= (6 - jm8);
        sig.push_back(oChar);
    }
    while ((sig.size() > 0) && (0 == sig.at(sig.size() - 1))) sig.pop_back();
}

mfloat::mfloat(const mint & m)
{
    zero = (m == 0);
    nan = false;
    pos = m.positive;
    inf = false;
    sub = false;
    exponent = 0;
    //sig.clear();
    if (zero) return;
    int charCount = static_cast<int>(m.digits.size()), 
        FNZ = getFirstNonZero(m.digits), 
        bitCount = charCount * 8 - FNZ, 
        iCharIdx = FNZ == 7? 1: 0, 
        d8 = 0;
    assert ((FNZ >= 0) && (FNZ < 8));
    unsigned char leftShift = static_cast<unsigned char>(FNZ + 1), 
        iChar = iCharIdx < charCount? m.digits.at(iCharIdx): 0, 
        oChar = 0, obit = 0,
        filter0 = 0x80, ifilter = 0, m8 = 0, jm8 = 0;
    --bitCount;
    exponent = bitCount;

    for (size_t j = 0; j < bitCount; ++j)
    { // bit by bit
        jm8 = j % 8;
        size_t i = j + leftShift;
        d8 = i / 8;
        m8 = i % 8;
        ifilter = filter0 >> m8;
        //o = i - leftShift;
        if (d8 > iCharIdx)
        {
            iCharIdx = d8;
            iChar = m.digits.at(iCharIdx);
        }
        obit = (ifilter & iChar) << m8;
        oChar |= obit >> jm8;
        if (7 == jm8)
        {
            sig.push_back(oChar);
            oChar = 0;
        }

    }
    if (oChar > 0) sig.push_back(oChar);
    else 
    {
        while ((sig.size() > 0) && (sig.at(sig.size() - 1) == 0))
        {
            sig.pop_back();
        }
    }
}

mfloat::mfloat(const string & s)
{
    string int_part, fract_part, exp_part;
    nan = !IsFloat(s, int_part, fract_part, exp_part);
    zero = isthisZero(int_part, fract_part);
    if (exp_part.size() == 0) exp_part = '0';
    if (fract_part.size() == 0) fract_part = '0';
    if (int_part.size() == 0) int_part = '0';
    int e_cmp = exponent_cmp(exp_part);
    char e_sign = exp_part.at(0), f_sign = fract_part.at(0);
    e_sign = ((e_sign == '-') || (e_sign == '+'))? e_sign: '+';
    pos = int_part.at(0) != '-';
    inf = (e_cmp == 1) && (e_sign == '+');
    sub = (e_cmp == 1) && (e_sign == '-');
    exponent = 0;
    if ((nan) || (inf) || (sub) || (zero)) return;
    int B = 0, D = stoi(exp_part); 
                                // To convert to exponent:
                                // E = e_i + e_f = D * ln(10) / ln(2),
                                // B += e_i (which is an integer, e_f is a float in [0,1) )& 
                                // b = e^(e_f * ln(2)) * d
                                // exponent is B which may need adjusting (decrementing) to get b into standard form
    
    if ((f_sign == '-') || (f_sign == '+')) fract_part = fract_part.substr(1);
    string d = int_part + '.' + fract_part;
    char first = d.at(0);
    if ((first == '+') || (first == '-')) d = d.substr(1);
    standardize_d(d, D);
    size_t dotat = d.find('.');
    int_part = d.substr(0, dotat);
    while ((int_part.size() > 1) || (int_part.at(0) > '1'))
    {
        ++B;
        d = half(d);
        dotat = d.find('.');
        assert ((dotat > 0) && (dotat != string::npos));
        int_part = d.substr(0, dotat);
        
    }
    char c1 = int_part.at(0);
    assert (c1 == '1');
    d[0] = '0';
    unsigned char oChar = 0, bit = 0, im8 = 0;
    for (int i = 0; i < BMAX; ++i)
    {
        size_t dotat = d.find('.');
        assert (dotat == 1);
        fract_part = d.substr(2);
        if (fract_part.size() == 0) break;
        d = twice(d);
        bit = d[0] - '0'; // s/b 0 or 1
        oChar |= bit;
        d[0] = '0';
        im8 = i % 8;
        if (im8 == 7)
        {
            sig.push_back(oChar);
            oChar = 0;
        }
        else oChar <<= 1;
    }
    if (oChar != 0) 
    {
        oChar <<= (6 - im8);
        sig.push_back(oChar);
    }
    while ((sig.size() > 0) && (0 == sig.at(sig.size() - 1))) sig.pop_back();

    // to do: store/retrieve ln10, ln2, ln10/ln2, ln2/ln10
    // finish conversion d X 10^D = b X 2^B
    mfloat b(handleCONSTANT(LN_2)), 
        E(handleCONSTANT(LN_10_OVER_2));
    if ((D < -100) || (D > 100))
    {
        
        E *= D;
        bool overflow = false;
        int intPart = E.getIntAndReal(overflow);
        //assert (!overflow);
        if ((exponent_cmp(intPart, B) == 1) || (overflow))
        {
            sig.clear();
            exponent = 0;
            inf = true;
            return;
        }
        B += intPart;
        b *= E;
        //b.eToThex();
        //b.newton_e();
        b.taylor_agm_e();
        *this *= b;
        
    }
    else
    {
        mfloat ten(10);
        if (D > 0)
        {
            for (int i = 0; i < D; ++i)
            {
                *this *= ten;
            }
        }
        if (D < 0)
        {
            for (int i = 0; i < (-D); ++i)
            {
                *this /= ten;
            }
        }
    }
    
    exponent += B;
    RoundMe();
}

mfloat::mfloat(const store_float & sf)
{
    unsigned char f = sf.FLAGS;
    zero = (f & 0x40) == 0x40;
    nan = (f & 0x20) == 0x20;
    pos = (f & 0x80) == 0x80;
    inf = (f & 0x10) == 0x10;
    sub = (f & 0x8) == 0x8;
    exponent = sf.EXPONENT;
    unsigned int sZ = sf.BIT_COUNT / 8 + ((sf.BIT_COUNT % 8) > 0? 1: 0);
    unsigned char * p = sf.SIG;
    if (p != NULL) --p;
    for (unsigned int i = 0; i < sZ; ++i) sig.push_back(*(++p));

    /*
    string h = sf.HEX_SIG;
    size_t hSz = h.size(), hIdx = 0;
    assert ((hSz % 2) == 0);
    unsigned char HI = 0, LO = 0, oChar = 0;
    char hiChar = 0, loChar = 0;
    for (int i = 0; i < (hSz / 2); ++i)
    { // not limited to current BMAX
        hIdx = 2 * i;
        hiChar = h.at(hIdx);
        HI = hiChar - (hiChar >= 'A'? 'A' - 10: '0');
        loChar = h.at(hIdx + 1);
        LO = loChar - (loChar >='A'? 'A' - 10: '0');
        assert ((HI < 16) && (LO < 16));
        oChar = HI << 4;
        oChar |= LO;
        sig.push_back(oChar);
    }
    */
}

mfloat::~mfloat(void)
{

}
    
string mfloat::print(void)
{
    size_t sSz = sig.size();
    const char lu[] = "0123456789ABCDEF";
    string r = "<pos is " + (string)(pos?"true> ":"false> ") +
        "<nan is " + (string)(nan?"true> ":"false> ") + "<zero is " + (string)(zero?"true> ":"false> ") +
        "<inf is " + (string)(inf?"true> ":"false> ") + "<sub is " + (string)(sub?"true> ":"false> ") +
        "\n<exponent (2^)= " + to_string(exponent) + "> <significand has " + to_string(sSz) + " bytes>\n **IN 1.HEX FORM**: 1.";
    if (sSz == 0) r += '0';
    else
    {
        unsigned char iflt = 0xf;
        for (size_t i = 0; i < sSz; ++i)
        {
            unsigned char iChar = sig.at(i), nibb = iChar >> 4;
            r += lu[nibb];
            nibb = iChar & iflt;
            r += lu[nibb];
        }
    }
    r += '\n';
    r += " ** As DOUBLE: " + to_string(static_cast<double>(*this)) + "\n";
    r += " ** As FLOAT: " + to_string(static_cast<float>(*this)) + "\n";
    r += " ** As INTEGER: " + to_string(static_cast<int>(*this)) + "\n";
    r += " ** As MINT: " +  (this->operator mint()).print() /* static_cast<mint>(*this).print() */ + "\n";
    //r += " ** As DECIMAL STRING: " + ConvertToDecimal() + "\n";

    return r;
}

string mfloat::print_bits(void)
{
    cout << " ** AS BITS **: 1.";
    const char * lu[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    size_t sSz = sig.size();
    string r = "";
    if (sSz == 0) r += "0";
    else
    {
        for (size_t i = 0; i < sSz; ++i)
        {
            unsigned char iChar = sig.at(i), nibb = iChar >> 4;
            r += to_string(i);
            r += '<';
            r += lu[nibb];
            r += '|';
            nibb = iChar & 0xf;
            r += lu[nibb];
            r += '>';
        }
    }
    r += '\n';

    return r;
}

void mfloat::display_all_constants(void)
{ // this will also re-calculate all constants as needed:

    int count = sizeof(_constants) / sizeof(_constants[0]);
    string s = "";
    for (int i = 0; i < count; ++i)
    {
        s += to_string(i + 1) + ") here is " + _constants[i] + " ---> ";
        mfloat buff = handleCONSTANT((CONSTANTS)i);
        s += buff.print();
        s += buff.ConvertToDecimal();
        s += "\n===============================================================\n\n";
        disp.write(s);
        s = "";
    }
    //disp.write(s);
        
        //cout << (i + 1) << ") displaying " << _constants[i] << ": ";
        //mfloat buff = handleCONSTANT((CONSTANTS)i);
        //cout << buff.print();
        //cout << " ** AS DECIMAL STRING: " << buff.ConvertToDecimal() << "\n";
        //cout << "===============================================================\n\n";
}

string mfloat::trim(const string & s_in)
{
    string allowables = "+-.0123456789Ee", r_val = "";
    for (size_t i = 0; i < s_in.size(); ++i)
    {
        char c = s_in.at(i);
        if (allowables.find(c) != string::npos) r_val += c;
    }
    return r_val;
}

char mfloat::ClassifyChar(const char & c)
{
    string sign = "+-", digit = "0123456789", exp = "Ee", point = ".", allowables = "+-.0123456789Ee";
    size_t a = allowables.find(c), d = digit.find(c), e = exp.find(c);

    if (allowables.find(c) == string::npos) return 'n';
    if (sign.find(c) != string::npos) return 's';
    if (digit.find(c) != string::npos) return 'd';
    if (exp.find(c) != string::npos) return 'e';
    if (c == '.') return 'p';
    return 'n';

}

bool mfloat::IsFloat(const string & s_in0, string & int_part, string & fract_part, string & exp_part)
{

    string s_in = trim(s_in0);

    int_part = "";
    fract_part = "";
    exp_part = "";

    bool intFound = false, fractFound = false, expFound = false;

    string sign = "+-", digit = "0123456789", exp = "Ee";
    char the_sign = '+';

    size_t sSz = s_in.size(),
        sign_pos1 = s_in.find_first_of(sign), 
        sign_pos2 = sign_pos1 == string::npos? string::npos: s_in.find_first_of(sign, sign_pos1 + 1), 
        sign_pos3 = sign_pos2 == string::npos? string::npos: s_in.find_first_of(sign, sign_pos2 + 1), 
        point_pos1 = s_in.find('.'), 
        point_pos2 = point_pos1 == string::npos? string::npos: s_in.find('.', point_pos1 + 1),
        exp_pos1 = s_in.find_first_of(exp),
        exp_pos2 = exp_pos1 == string::npos? string::npos: s_in.find_first_of(exp, exp_pos1 + 1);

    if (sSz == 0) return false;
    char finalchar = s_in.at(s_in.size() - 1);
    if (ClassifyChar(finalchar) != 'd') return false;
    if ((sign_pos3 != string::npos) || (point_pos2 != string::npos) || (exp_pos2 != string::npos)) return false;
    if (exp_pos1 != string::npos)
    {
        if (sign_pos2 != string::npos)
        {
            if (exp_pos1 != (sign_pos2 - 1)) return false;
            char c = s_in.at(sign_pos2 + 1);
            if (c == '0') return false;
            exp_part = s_in.substr(sign_pos2);
            expFound = true;
        }
        else
        {
            {
                if ((exp_pos1 == 0) || ((point_pos1 != string::npos) && (exp_pos1 < point_pos1))) return false;
                char c = exp_pos1 == sign_pos1 - 1? s_in.at(exp_pos1 + 2): (exp_pos1 + 2 == sSz)? ' ': s_in.at(exp_pos1 + 1); //, l = ClassifyChar(c);
                //if ((l != 'd') && (l != 's')) return false;
                if (c == '0') return false;
                //exp_part = l == 'd'? the_sign + s_in.substr(exp_pos1 + 1): s_in.substr(exp_pos1 + 1);
                exp_part = exp_pos1 == sign_pos1 - 1? s_in.substr(exp_pos1 + 1): the_sign + s_in.substr(exp_pos1 + 1);
                expFound = true;
            }
        }
        
        //if ((!expFound) && (exp_pos1 != string::npos))
        //{ 
        //    if ((exp_pos1 == (sSz - 1)) || (exp_pos1 == 0) || ((point_pos1 != string::npos) && (exp_pos1 < point_pos1))) return false;
        //    char c = s_in.at(exp_pos1 + 1), l = ClassifyChar(c);
        //    if ((l != 'd') && (l != 's')) return false;
        //    exp_part = l == 'd'? the_sign + s_in.substr(exp_pos1 + 1): s_in.substr(exp_pos1 + 1);
        //    expFound = true;
        //}
    }
    if ((sign_pos1 == string::npos) || (sign_pos1 > 0))
    {
        char c1 = s_in.at(0), l1 = ClassifyChar(c1), c2 = ' ', l2 = ' ';
        switch (l1)
        {
        case 'd':
            int_part = the_sign + (point_pos1 == string::npos? expFound? s_in.substr(0, exp_pos1): s_in: s_in.substr(0, point_pos1));
            intFound = true;
            break;
        case 'p':
            if (sSz == 1) return false;
            c2 = s_in.at(1), l2 = ClassifyChar(c2);
            if (l2 != 'd') return false;
            fract_part = the_sign + (expFound? s_in.substr(1, exp_pos1 - 1): s_in.substr(1));
            fractFound = true;
            break;
        default:
            return false;
        }
        
    }
    else
    {
        if ((sign_pos1 > 0) || (sSz == 1)) return false;
        char c1 = s_in.at(1), l1 = ClassifyChar(c1), c2 = ' ', l2 = ' ';
        the_sign = s_in.at(0); 
        switch (l1)
        {
        case 'd':
            int_part = point_pos1 == string::npos? expFound? s_in.substr(0, exp_pos1): s_in: s_in.substr(0, point_pos1);
            intFound = true;
            break;
        case 'p':
            if (sSz == 1) return false;
            c2 = s_in.at(2), l2 = ClassifyChar(c2);
            if (l2 != 'd') return false;
            fract_part = the_sign + (expFound? s_in.substr(2, exp_pos1 - 2): s_in.substr(2));
            fractFound = true;
            break;
        default:
            return false;
        }
    }
    if ((point_pos1 != string::npos) && (!fractFound))
    {
        
        fract_part = expFound? s_in.substr(point_pos1 + 1, exp_pos1 - point_pos1 - 1): s_in.substr(point_pos1 + 1);
        if (fract_part.size() > 0) fract_part = the_sign + fract_part;
        fractFound = true;
    }
    return true;
}

void mfloat::test(void)
{
    /*
    string test_float = "Hassenfeffer", stop_str = "0", ip, fp, ep;
    while (test_float.compare(stop_str) != 0)
    {
        cout << "Enter a floating point number (0 to stop)\n";
        getline(cin, test_float);
        //cin >> test_float;
        //test_float = trim(test_float);
        bool i_f = IsFloat(test_float, ip, fp, ep);
        cout << test_float << " is " << (i_f? "": "not ") << "a real number\n";
        if (i_f) 
        {
            cout << "the integer part is " << ip << " the fractional part is " << fp << " & the exponential part is " << ep << "\n";
            cout << "Is This Zero? " + (string)(isthisZero(ip, fp)?"Yes":"No") + "\n";
        }
    }
    

    string test_float = "Hassenfeffer", stop_str = "0", ip, fp, ep;
    while (test_float.compare(stop_str) != 0)
    {
        cout << "Enter a floating point number (0 to stop)\n";
        getline(cin, test_float);
        //cin >> test_float;
        //test_float = trim(test_float);
        bool i_f = IsFloat(test_float, ip, fp, ep);
        cout << test_float << " is " << (i_f? "": "not ") << "a real number\n";
        if (i_f) 
        {
            mfloat fIn(test_float), lb(fIn);
            int iterations = lb.binary_log();
            cout << "the input float is " << fIn.print();
            cout << "the binary log (" << to_string(iterations) << " iterations) is: " << lb.print();
            cout << " ** AS DECIMAL STRING: " << lb.ConvertToDecimal() << "\n";
        }
    }
    

    string test_float = "Hassenfeffer", stop_str = "0", ip, fp, ep;
    while (test_float.compare(stop_str) != 0)
    {
        cout << "Enter a floating point number (0 to stop)\n";
        getline(cin, test_float);
        //cin >> test_float;
        //test_float = trim(test_float);
        bool i_f = IsFloat(test_float, ip, fp, ep);
        cout << test_float << " is " << (i_f? "": "not ") << "a real number\n";
        if (i_f) 
        {
            mfloat fIn(test_float), SQRT(fIn);
            int iterations = SQRT.square_root();
            SQRT.RoundMe();
            cout << "the input float is " << fIn.print();
            cout << "the square root (" << to_string(iterations) << " bits) is: " << SQRT.print();
            cout << " ** AS DECIMAL STRING: " << SQRT.ConvertToDecimal() << "\n";
        }
    }
    

    string test_float2 = "BiteMe";
    test_float = "Hassenfeffer";
    while (test_float.compare(stop_str) != 0)
    {
        cout << "Enter 2 floating point numbers (0s to stop)\n";
        getline(cin, test_float);
        size_t blankAt = test_float.find(' ');
        if (blankAt == string::npos) break;
        test_float2 = test_float.substr(blankAt + 1);
        test_float = test_float.substr(0, blankAt);
        //cin >> test_float;
        //test_float = trim(test_float);
        bool i_f1 = IsFloat(test_float, ip, fp, ep),
            i_f2 = IsFloat(test_float2, ip, fp, ep);
        cout << test_float << " is " << (i_f1? "": "not ") << "a real number\n";
        cout << test_float2 << " is " << (i_f2? "": "not ") << "a real number\n";
        if (i_f1 && i_f2) 
        {
            mfloat fIn(test_float), M(fIn), fIn2(test_float2);
            int iterations = M.agm(fIn2);
            M.RoundMe();
            cout << "the input floats are " << fIn.print() << fIn2.print();
            cout << "the arithmetic-geometric mean (" << to_string(iterations) << " iterations) is: " << M.print();
            cout << " ** AS DECIMAL STRING: " << M.ConvertToDecimal() << "\n";
        }
    }


    mfloat e2(handleCONSTANT(EXP_1));
    BMAX += 8;
    e2 = sqr(e2);
    BMAX -= 8;
    cout << " e squared is :";
    cout << e2.print();
    cout << " ** AS DECIMAL STRING: " << e2.ConvertToDecimal() << "\n";

    string test_float = "Hassenfeffer", stop_str = "0", ip, fp, ep;
    while (test_float.compare(stop_str) != 0)
    {
        cout << "eLog test: Enter a floating point number (0 to stop)\n";
        getline(cin, test_float);
        //cin >> test_float;
        //test_float = trim(test_float);
        bool i_f = IsFloat(test_float, ip, fp, ep);
        cout << test_float << " is " << (i_f? "": "not ") << "a real number\n";
        if (i_f) 
        {
            BMAX += 8;
            mfloat fIn(test_float), 
                ln(fIn);
            int iterations = ln.eLog(PB);
            BMAX -= 8;
            ln.RoundMe();
            cout << "the input float is " << fIn.print();
            cout << "the natural log (" << to_string(iterations) << " bits) is: " << ln.print();
            cout << " ** AS DECIMAL STRING: " << ln.ConvertToDecimal() << "\n";
        }
    }
*/


    mfloat pi(handleCONSTANT(P_I)), pio2(pi), pio6(pi), pio3(pi), six(6.0f), three(3.0f);
    --pio2.exponent;
    pio6 /= six;
    pio3 /= three;
    cout << " pi  ** AS DECIMAL STRING: " << pi.ConvertToDecimal() << "\n";
    cout << " pi/2  ** AS DECIMAL STRING: " << pio2.ConvertToDecimal() << "\n";
    cout << " pi/3  ** AS DECIMAL STRING: " << pio3.ConvertToDecimal() << "\n";
    cout << " pi/6  ** AS DECIMAL STRING: " << pio6.ConvertToDecimal() << "\n";
    
    string test_float = "Hassenfeffer", stop_str = "0", ip, fp, ep;
    while (test_float.compare(stop_str) != 0)
    {
        cout << "sine, cosine & tangent test: Enter a floating point number (0 to stop)\n";
        getline(cin, test_float);
        //cin >> test_float;
        //test_float = trim(test_float);
        bool i_f = IsFloat(test_float, ip, fp, ep);
        cout << test_float << " is " << (i_f? "": "not ") << "a real number\n";
        if (i_f) 
        {
            mfloat fIn(test_float), 
                s(fIn), c(s), t(s);

            cout << "the input float is " << fIn.print();

            int iterations1 = s.sine();
            s.RoundMe();
            cout << "the sine (" << to_string(iterations1) << " iterations) is: " << s.print();
            cout << " ** AS DECIMAL STRING: " << s.ConvertToDecimal() << "\n";

            int iterations2 = c.cosine();
            c.RoundMe();
            cout << "the cosine (" << to_string(iterations2) << " iterations) is: " << c.print();
            cout << " ** AS DECIMAL STRING: " << c.ConvertToDecimal() << "\n";

            int iterations3 = t.tangent();
            t.RoundMe();
            cout << "the tangent (" << to_string(iterations3) << " iterations) is: " << t.print();
            cout << " ** AS DECIMAL STRING: " << t.ConvertToDecimal() << "\n";



        }
    }

}

void mfloat::test2(void)
{
    BMAX += 32;
    cout << "e is: ";
    // setting up this to be 1:
    *this = mfloat(1.0f);
    cout << "<iterations: " << to_string(eToThex(true)) << "> ";
    cout << print();
    cout << " ** AS DECIMAL STRING: " << ConvertToDecimal() << "\n";
    cout << " e^2 is: ";
    mfloat esqr = sqr(*this);
    cout << esqr.print();
    cout << " ** AS DECIMAL STRING: " << esqr.ConvertToDecimal() << "\n";

    BMAX -= 32;

    cout << "1000 is: ";
    mfloat thousand("1000");
    thousand.RoundMe();
    cout << thousand.print();
    cout << " ** AS DECIMAL STRING: " << thousand.ConvertToDecimal() << "\n";

    //BMAX -= 32;
}

void mfloat::test3(void)
{
    cout << "3 times itself is: ";
    mfloat a(3.0);
    *this = a;
    *this *= a;
    cout << print() << "\n";

    cout << "1/10 is: ";
    a = 10.0f;
    *this = 1.0f;
    *this /= a;
    cout << print() << "\n";

}

void mfloat::test4(void)
{
    cout << "3 + 5 is :";
    mfloat a(3.0f);
    *this = 5.0f;
    *this += a;
    cout << print() << "\n";

    cout << "10 - 3 is :";
    *this = 10.0f;
    *this -= a;
    cout << print() << "\n";

    //mfloat ln5(ln_5);
    //cout << "natural log 5 is :" << ln5.print();

}

void mfloat::test5(void)
{
    BMAX += 32;

    cout << "natural log 2 is: ";
    mfloat ln2 = 2.0f;
    int iterations = ln2.naturalLog();
    cout << "Iterations: " << to_string(iterations) << " ";
    cout << ln2.print() << "\n";

    cout << "natural log 5 is: ";
    mfloat ln5 = 5.0f;
    iterations = ln5.naturalLog();
    cout << "Iterations: " << to_string(iterations) << " ";
    cout << ln5.print() << "\n";

    mfloat ln10 = ln2 + ln5, ln10o2 = ln10, ln2o10 = ln2;
    cout << "natural log 10 is: " << ln10.print() << "\n";
    ln10o2 /= ln2;
    ln2o10 /= ln10;
    cout << "natural log 10 / natural log 2 is: " << ln10o2.print() << "\n";
    cout << "natural log 2 / natural log 10 is: " << ln2o10.print() << "\n";

    BMAX -= 32;
}

void mfloat::test6(void)
{
	mint m(1000), i(131);
	cout << "m is " << m.print() << "\n";
	cout << "i is " << i.print() << "\n";
	//m.factorial();
	//i.factorial();
	mfloat m_f(m), i_f(i), r(m),
		esqr("7.3890560989306502272304274605750078131803155705518473240871278225225737960790577633843124850791217947737531612654788661238846036927812733744783922133980777749001228956074107537023913309475506820865818202696478682084042209822552348757424625414146799281293318880707633010193378997407299869600953033075153208188236846947930299135587714456831239232727646025883399964612128492852096789051388246639871228137268610647356263792951822278429484345861352876938669857520015499601480750719712933694188519972288826362559719410958661914798715043283976932646102351163123899900105137834067644986638926856158218642155772484920111935316211719517317472697968293451998505418486319713568594702291255739835611051497936814502776448076429851041821170559441917876834712852764978097134625041402352421587409386682542715703926452964045506287780013110926501384833453026463631415604718881176579427863485990767045271193729587239959870733108149612531097705935300990503296810754210908776263085724850038278722761448667450564987385877157E0");
	cout << "m_f s/b 1000 it is: " << m_f.print() << "\ni_f s/b 131 it is: " << i_f.print() <<"\n1000 + 131 : ";
	r += i;
	cout << r.print() << "\n";
	cout << "131 - 1000 : ";
	r = i;
	r -= m;
	cout << r.print() << "\n";
	cout << "e squared is: " << esqr.print() << "\n";
	// s/b 1.D8E64B8D4DDADCC33A3BA206B68ABBA847AE7AF64F221FAD67B5DE5DF4427C521E08B35DE1AA55B7FDB18A27FDD4D2D1D28FF96208878AD651FEE4ACAF6EC03201D4E0F443BB7F46BA4325D2CB8EDC7078B4609E867C5D7DF7ECC576AB2026E65E1D03BEC51D45C31E96606B6A0366EB7FF9830DA2CB566146095D320B2772EDDEC43EA6DC142BE34CC093E76A0BB0907FD1EB487B651B63EE064187DB2792866495E36A5AAB9BCDD825395DBB3D45B5A289F90E9029E35A7CFCC07E97AB5FB0FCA8F52E93C3971395ABE3E6CD9226BAD465ABB28F8093A9BCC4942307EB799BFA5FB253285CC9E1D29836CB27D2DDED4ECA178A3BB64E16C45443122FE7B19C14D1CA0F0C7C29B729C56B64DA1F73C2FAF417338613E31AA03E5875A251AC43C0AC052F356C44B99DED95055C5CA00018154E0E9CF7B382BEE7C7CF456E03E2EC993B305AC256CAA98D4C2FE789098D0BACAD04657036E6F5649271245AA61FD30D389E96C034521C49A9E25A89C2FB202A28A6C1C8CCEAACD5A8FEC515A7DBC326DB16247D11265383B37D91A1C42B50F507FA3D9BE7386C28C526DBDDFAE28070 * 2^2
	//cout << "11! = " << m.print() << "\n" << "9! = " << i.print() << "\n" << "11! % 9! = " << q.print() << "\n";
	//cout << "1000 / 131 = 131 times " << q.print() << " remainder " << r.print() << "\n";
	mfloat pi(3.141592654), thousand(1000);
	cout << "pi @ 3.141592654 as an mfloat -> " << pi.print() << "\n";
	//pi.test4();
    thousand.RoundMe();
	cout << "one thousand is :" << thousand.print() << "\n";

    double d_f = 1.0 / 5.0, d_t = 1.0 / 239.0;
    mfloat one(1.0f), fifth(5.0f), two39th(239.0f);
    fifth = one / fifth;
    two39th = one / two39th;
    cout << "one fifth is: " << fifth.print() << "one 239th is: " << two39th.print();
    int fCnt = fifth.arctan(), tCnt = two39th.arctan();
    cout << "arctan 1/5 is: " << fifth.print() << " ** AS DECIMAL STRING: " << fifth.ConvertToDecimal() << "\n";
    cout << "arctan 1/239 is: " << two39th.print() << " ** AS DECIMAL STRING: " << two39th.ConvertToDecimal() << "\n";
    fifth.exponent += 4; // * 16
    two39th.exponent += 2; // * 4
    pi = fifth;
    pi -= two39th;
    cout << "16 * arctan 1/5 is: " << fifth.print() << " ** AS DECIMAL STRING: " << fifth.ConvertToDecimal() << "\n";
    cout << "4 * arctan 1/239 is: " << two39th.print() << " ** AS DECIMAL STRING: " << two39th.ConvertToDecimal() << "\n";
    pi.RoundMe();
    cout << "pi via arctan calculations is: " << pi.print();
    cout << " ** AS DECIMAL STRING: " << pi.ConvertToDecimal() << "\n";
    
    mfloat s(1.0f), M(1.0f), ln2(handleCONSTANT(LN_2));
    s.exponent = -1675;
    cout << "initial M: " << M.print() << "\ninitial s: " << s.print();
    int iterations = M.agm(s);
    cout << "arithmetic-geometric mean is : <iterations=" << to_string(iterations) << "> " << M.print();
    cout << "pi via the agm is: ";
    ln2 *= 1677;
    pi = M;
    pi *= 2;
    pi *= ln2;
    cout << pi.print();
    cout << " ** AS DECIMAL STRING: " << pi.ConvertToDecimal() << "\n";
    
}

void mfloat::test7(void)
{
    
    cout << " ln(10) using agm is : ";
    mfloat l(10);
    int iterations = l.eLog();
    cout << "<itertions=" << to_string(iterations) << "> " <<l.print();
    cout << " ** AS DECIMAL STRING: " << l.ConvertToDecimal() << "\n";

    cout << " e using agm & Newton is : ";
    mfloat e(1);
    iterations = e.newton_e();
    cout << "<itertions=" << to_string(iterations) << "> " <<e.print();
    cout << " ** AS DECIMAL STRING: " << e.ConvertToDecimal() << "\n";
    
    cout << "e using power series is : ";
    e = 1;
    iterations = e.eToThex(true);
    cout << "<iterations=" << iterations << "> " << e.print();
    cout << " ** AS DECIMAL STRING: " << e.ConvertToDecimal() << "\n";

    /*
    cout << " ln(2) stored is : ";
    mfloat ln2(handleCONSTANT(LN_2));
    cout << ln2.print();
    cout << " ** AS DECIMAL STRING: " << ln2.ConvertToDecimal() << "\n";

    cout << " pi stored is : ";
    mfloat pi(handleCONSTANT(P_I));
    cout << pi.print();
    cout << " ** AS DECIMAL STRING: " << pi.ConvertToDecimal() << "\n";

    cout << " e is: ";
    mfloat e(handleCONSTANT(EXP_1));
    cout << e.print();
    cout << " ** AS DECIMAL STRING: " << e.ConvertToDecimal() << "\n";

    cout << "e squared is : ";
    mfloat esqr("7.3890560989306502272304274605750078131803155705518473240871278225225737960790577633843124850791217947737531612654788661238846036927812733744783922133980777749001228956074107537023913309475506820865818202696478682084042209822552348757424625414146799281293318880707633010193378997407299869600953033075153208188236846947930299135587714456831239232727646025883399964612128492852096789051388246639871228137268610647356263792951822278429484345861352876938669857520015499601480750719712933694188519972288826362559719410958661914798715043283976932646102351163123899900105137834067644986638926856158218642155772484920111935316211719517317472697968293451998505418486319713568594702291255739835611051497936814502776448076429851041821170559441917876834712852764978097134625041402352421587409386682542715703926452964045506287780013110926501384833453026463631415604718881176579427863485990767045271193729587239959870733108149612531097705935300990503296810754210908776263085724850038278722761448667450564987385877157E0");
    cout << esqr.print();
    cout << " ** AS DECIMAL STRING: " << esqr.ConvertToDecimal() << "\n";
    */
    

}

void mfloat::test8(void)
{

    cout << " ln(50) using agm is : ";
    mfloat l(50);
    int iterations = l.eLog();
    cout << "<itertions=" << to_string(iterations) << "> " <<l.print();
    //cout << " ** AS DECIMAL STRING: " << l.ConvertToDecimal() << "\n";
    disp.write(l.ConvertToDecimal());
}

string mfloat::half(const string &a) // returns one half of decimal string in
{ // a will have a string of decimal digits left and (optionally) right of a decimal point
    string r = "";
    unsigned char carry = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
        char d = a.at(i);
        if (d == '.')
        {
            if (r.size() == 0) r += '0';
            r += d;
        }
        else
        {
            unsigned char u = d - '0';
            carry += u; // in {0 .. 19}
            r += ((carry / 2) + '0');
            carry = 10 * (carry % 2); // 0 or 10 for even or odd respectively
        }
        
    }
    if (carry == 10) r += '5';
    while ((r.size() > 0) && ('0' == r.at(r.size() - 1))) r.pop_back();
    return r;
}
    
string mfloat::twice(const string &a) // returns 2X decimal string in
{ // a will have a string of decimal digits left and (optionally) right of a decimal point
    string r = a;
    unsigned char carry = 0;
    for (size_t i = a.size(); i > 0; --i)
    {
        char d = a.at(i - 1);
        if (d != '.')
        {
            unsigned char u = d - '0';
            u *= 2;
            u += carry;
            r[i - 1] = ('0' + (u % 10));
            carry = u / 10;

        }
        
    }
    if (carry > 0) 
    { // this should never happen because a s/b 0.dddddd...
        char d = carry + '0';
        r = d + r;
    }
    while ((r.size() > 0) && (r.at(r.size() - 1) == '0'))
    {
        r.pop_back();
    }
    return r;
}

bool mfloat::IsEq(const mfloat &a) const
{
    if (zero != a.zero) return false;
    if (nan || a.nan) return false;
    if (pos != a.pos) return false;
    if (inf || a.inf) return false;
    if (sub || a.sub) return false;
    if (exponent != a.exponent) return false;
    return sig == a.sig;
    //size_t sSz = sig.size(), aSz = a.sig.size();
    //if (sSz != aSz) return false;
    //for (size_t i = 0; i < sSz; ++i)
    //{
    //    unsigned char s1Char = sig.at(i), s2Char = a.sig.at(i);
    //    if (s1Char != s2Char) return false;
    //}
    //return true;
}
    
bool mfloat::IsLT(const mfloat &a) const
{
    if (nan || a.nan) return false;
    if (inf || a.inf) return false;
    if (sub || a.sub) return false;
    if (pos != a.pos) return a.pos;
    if (zero || a.zero) 
    {
        if (zero && a.zero) return false;
        if (zero) return a.pos;
        if (a.zero) return !(pos);
    }
    if (exponent != a.exponent) return pos? exponent < a.exponent: exponent > a.exponent; 
    return pos? sig < a.sig: sig > a.sig;
    //size_t sSz = sig.size(), aSz = a.sig.size();
    //for (size_t i = 0; i < sSz; ++i)
    //{
    //    unsigned char s1Char = sig.at(i), s2Char = a.sig.at(i);
    //    if (s1Char != s2Char) return pos? s1Char < s2Char: s1Char > s2Char;
    //}
    //return false;
}
    
bool mfloat::IsGT(const mfloat &a) const
{
    if (nan || a.nan) return false;
    if (inf || a.inf) return false;
    if (sub || a.sub) return false;
    if (pos != a.pos) return pos;
    if (zero || a.zero) 
    {
        if (zero && a.zero) return false;
        if (zero) return !a.pos;
        if (a.zero) return pos;
    }
    if (exponent != a.exponent) return pos? exponent > a.exponent: exponent < a.exponent; 
    return pos? sig > a.sig: sig < a.sig;
    //size_t sSz = sig.size(), aSz = a.sig.size();
    //for (size_t i = 0; i < sSz; ++i)
    //{
    //    unsigned char s1Char = sig.at(i), s2Char = a.sig.at(i);
    //    if (s1Char != s2Char) return pos? s1Char > s2Char: s1Char < s2Char;
    //}
    //return false;
}

bool mfloat::IsMagEq(const mfloat & b) const 
{ // magnitude: distance from 0 always positive
    if (exponent != b.exponent) return false;
    return (sig == b.sig);

}
    
bool mfloat::IsMagLT(const mfloat & b) const
{
    if (zero || b.zero) 
    {
        if (zero && b.zero) return false;
        if (zero) return true;
        if (b.zero) return false;
    }
    if (exponent != b.exponent) return exponent < b.exponent; 
    return (sig < b.sig);

}

bool mfloat::IsMagGT(const mfloat & b) const
{
    if (zero || b.zero) 
    {
        if (zero && b.zero) return false;
        if (zero) return false;
        if (b.zero) return true;
    }
    if (exponent != b.exponent) return exponent > b.exponent; 
    return (sig > b.sig);

}


int mfloat::eToThex(const bool & ReCalc)
{
    if ((nan) || (inf) || (sub)) return 0;
    if (zero)
    { // return 1 as 1.0 * 2^0
        pos = true;
        zero = false;
        exponent = 0;
        return 0;
    }
    disp.progress_text("e^x");
    mfloat x = *this, one(1.0f), mone(-1.0f), zer(0.0f), multiplier(one), 
        term(one), acc(term), /*error = zer,*/ denom(zer), e(2.718281828);
    //pos = true;
    int count = 0, iPart = 0;

    bool invert = x.pos;

    //BMAX += 24;
    if (!ReCalc)
    {
        e = handleCONSTANT(EXP_1);
        
        if (x.IsEq(one))
        {
            *this = e;
            return 0;
        }
        if (x.IsEq(mone))
        {
            one /= e;
            *this = one;
            return 0;
        }
        if (x.IsGT(one) || x.IsLT(mone)) 
        {
            bool overflow = false;
            iPart = x.getIntAndReal(overflow);
            assert (!overflow);
            //x.RoundMe();
        }
    }
    x.pos = false;
    bool dBug = false;
    double eCk1 = static_cast<double>(x);
    //char cat = !x.pos? 'n': (x < one)? 'o': 'a';
    //int M = (cat == 'a')? x.isInt()? static_cast<int>(x): static_cast<int>(x + one): 0,
    /*
    if (cat == 'o') multiplier = one / (one - x);
    switch (cat)
    {
        case 'n': // alternating series test:
            error = term;
            break;
        case 'o': // geometric series:
            error = term * multiplier;
            break;
        case 'a': // Taylor Lagrange Remainder:
            error = term;
            error.exponent += 2 * M;
            break;
    }
    */
    if (!x.zero) while ((1 + BMAX + term.exponent) > 0)
    {
        denom += one;
        ++count; // should match denom
        term *= x;
        //assert (term.sig.at(term.sig.size() - 1) != 0);
        //assert (dBug == term.pos);
        //dBug = !dBug;
        term /= denom;
        //bool screwup = (term.sig.size() > 0) && (term.sig.at(term.sig.size() - 1) == 0);
        acc += term;
        disp.progress(static_cast<double>(-term.exponent) / static_cast<double>(1 + BMAX));
        /*
        switch (cat)
        {
            case 'n': // alternating series test:
                error = term;
                break;
            case 'o': // geometric series:
                error = term * multiplier;
                break;
            case 'a': // Taylor Lagrange Remainder e^t_x < 4^M = 2^2M:
                error = term;
                error.exponent += 2 * M;
                break;
        }
        */
    }
    double eCk2 = static_cast<double>(acc);

    //cout << "iterations: " << to_string(count) << " ";
    if ((invert) || (iPart != 0))
    {
        one /= acc;
        acc = one;
    }
    if (iPart != 0) 
    {
        e.power(iPart);
        double eCk3 = static_cast<double>(e);

        acc *= e;
    }
    *this = acc;
    disp.progress_text("");
    //BMAX -= 24;
    return count;
}

int mfloat::naturalLog(void)
{
    if ((zero) || !(pos))
    { // error -infinity
        nan = !(pos);
        inf = zero;
        pos = false;
        zero = false;
        exponent = 0;
        sig.clear();
    }
    disp.progress_text("ln(x)");
    if ((nan) || (inf) || (sub)) return 0;
    mfloat y = *this, zer(0.0f), one(1.0f), two(2.0f), three(3.0f), 
        x = (y - one) / (y + one), xsqr = x * x, x_term = x, 
        denom = one, e_mult = one / (one - xsqr), acc = zer, term = one;
    int e_exp = e_mult.exponent, count = 0;

    // error is < 2^(this + 2 + term's exponent)
    //double yD = static_cast<double>(y), xD = static_cast<double>(x),
    //    tD = 0.0, dD = 0.0, x2D = static_cast<double>(xsqr);
    while ((3 + BMAX + e_exp + term.exponent) > 0)
    {
    //    term = two;
    //    tD = static_cast<double>(term);
    //    term *= x_term;
    //    tD = static_cast<double>(term);
    //    term /= denom;
    //    tD = static_cast<double>(term);
        term = two * x_term / denom;
    //    tD = static_cast<double>(term);
        acc += term;
        denom += two;
    //    dD = static_cast<double>(denom);
        x_term *= xsqr;
    //    xD = static_cast<double>(x_term);
        ++count;
        disp.progress(static_cast<double>(-term.exponent) / static_cast<double>(3 + BMAX + e_exp));
        //num *= xsqr;
        //next_term = two * num / denom;
        //error = next_term * multiplier;
    }
    //cout << "Iterations: " << to_string(count) << " ";
    *this = acc;
    disp.progress_text("");
    return count;
}

int mfloat::naturalLog_1(void) //(const int & = 0);
{ // ln(1+x) use when x is very close to 1

    if ((zero) || !(pos))
    { // error -infinity
        nan = !(pos);
        inf = zero;
        pos = false;
        zero = false;
        exponent = 0;
        sig.clear();
    }
    if ((nan) || (inf) || (sub)) return 0;

    disp.progress_text("ln(x)");

    mfloat y(*this), zer(0), one(1), delta = y - one, acc(zer), term(delta), denom(one);
    int count = 0;

    while ((1 + BMAX + term.exponent) > 0)
    {
        acc += term / denom;
        term *= delta;
        if (delta.pos) term.pos = !term.pos;
        else term.pos = false;
        denom += one;
        ++count;
        disp.progress(static_cast<double>(-term.exponent) / static_cast<double>(BMAX));
    }
    //cout << "Iterations: " << to_string(count) << " ";
    *this = acc;
    disp.progress_text("");
    return count;


}


mfloat & mfloat::operator=(const mfloat & f)
{
    zero = f.zero;
    nan = f.nan;
    pos = f.pos;
    inf = f.inf;
    sub = f.sub;
    exponent = f.exponent;
    sig = f.sig;
    //sig.clear();
    //sig.insert(sig.end(), f.sig.begin(), f.sig.end());

    return *this;
}

mfloat & mfloat::operator+=(const mfloat & a)
{
    if (nan) return *this;
    if (inf) return *this;
    if (sub) return *this;
    if (zero) 
    {
        *this = a;
        return *this;
    }
    if (a.zero) return *this;
    if (pos == a.pos)
    {
        if (exponent >= a.exponent)
        {
            int delta = exponent - a.exponent;
            sig = add_magnitude(sig, a.sig, delta);
            if (exponent_cmp(exponent, delta) == 1)
            {
                inf = exponent > 0;
                sub = exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent += delta;
        }
        else
        {
            int delta = a.exponent - exponent;
            sig = add_magnitude(a.sig, sig, delta);
            if (exponent_cmp(exponent, delta) == 1)
            {
                inf = exponent > 0;
                sub = exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent = a.exponent + delta;
        }
    }
    else
    {
        //bool signBuff0 = pos, signBuff1 = a.pos;
        //pos = true;
        //mfloat b = a;
        //b.pos = true;
        if (IsMagEq(a))
        {
            zero = true;
            pos = true;
            exponent = 0;
            sig.clear();
        }
        else if (IsMagGT(a))
        {
            int delta = exponent - a.exponent;
            sig = subtract_magnitude(sig, a.sig, delta);
            if (exponent_cmp(exponent, delta) == 1)
            {
                inf = exponent > 0;
                sub = exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent += delta;
            //pos = signBuff0;
        }
        else
        {
            int delta = a.exponent - exponent;
            sig = subtract_magnitude(a.sig, sig, delta);
            if (exponent_cmp(exponent, delta) == 1)
            {
                inf = exponent > 0;
                sub = exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent = a.exponent + delta;
            pos = a.pos;
        }
        
    }
    
    return *this;
}
    
mfloat & mfloat::operator-=(const mfloat & a)
{
    if (nan) return *this;
    if (inf) return *this;
    if (sub) return *this;
    if (zero) 
    {
        *this = a;
        pos = !a.pos;
        return *this;
    }
    if (a.zero) return *this;
    if (pos != a.pos)
    {
        if (exponent >= a.exponent)
        {
            int delta = exponent - a.exponent;
            sig = add_magnitude(sig, a.sig, delta);
            if (exponent_cmp(exponent, delta) == 1)
            {
                inf = exponent > 0;
                sub = exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent += delta;
        }
        else
        {
            int delta = a.exponent - exponent;
            sig = add_magnitude(a.sig, sig, delta);
            if (exponent_cmp(exponent, delta) == 1)
            {
                inf = exponent > 0;
                sub = exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent = a.exponent + delta;
        }
    }
    else
    {
        if (IsMagEq(a))
        {
            zero = true;
            pos = true;
            exponent = 0;
            sig.clear();
        }
        else if (IsMagGT(a))
        {
            int delta = exponent - a.exponent;
            sig = subtract_magnitude(sig, a.sig, delta);
            if (exponent_cmp(exponent, delta) == 1)
            {
                inf = exponent > 0;
                sub = exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent += delta;
        }
        else
        {
            int delta = a.exponent - exponent;
            sig = subtract_magnitude(a.sig, sig, delta);
            if (exponent_cmp(a.exponent, delta) == 1)
            {
                inf = a.exponent > 0;
                sub = a.exponent < 0;
                exponent = 0;
                sig.clear();
                return *this;
            }
            exponent = a.exponent + delta;
            pos = !pos;
        }
        
    }
    
    return *this;
}

mfloat & mfloat::operator*=(const mfloat & a)
{
    if (nan) return *this;
    if (inf) return *this;
    if (sub) return *this;
    if ((zero) || (a.zero)) 
    {
        zero = true;
        sig.clear();
        pos = true;
        exponent = 0;
        return *this;
    }
    pos = pos == a.pos;
    if (exponent_cmp(exponent, a.exponent) == 1)
    {
        inf = exponent > 0;
        sub = exponent < 0;
        exponent = 0;
        sig.clear();
        return *this;
    }
    int tBitCount = getBitCount() + 1, 
        aBitCount = const_cast<mfloat &>(a).getBitCount() + 1,
        minBitCount = min(tBitCount, aBitCount);

    // @BMAX=3376 classic method is faster than using karatsuba
    //if (minBitCount < 640) 
    //{
        multiply(a);
        return *this;
    //}

    // setting up karatsuba:
    mfloat k1(*this), k2(a);  // our operands
    int bias1 = 0, bias2 = 0; // integerizing the mfloats
    if (exponent < tBitCount) bias1 += tBitCount - exponent;
    if (a.exponent < aBitCount) bias2 += aBitCount - a.exponent;
    k1.exponent += bias1; // this makes k1 an integer
    k2.exponent += bias2; // this makes k2 an integer
    k1.pos = true; // whole numbers only
    k2.pos = true;
    mfloat kM = karatsuba(k1, k2);

    if (!(kM.nan || kM.inf || kM.sub || kM.zero))
    {
        kM.exponent -= bias1 + bias2;
    }
    *this = kM;
    return *this;
/*    
    if (inf) return *this;
    if (sub) return *this;
    if ((zero) || (a.zero)) 
    {
        zero = true;
        sig.clear();
        pos = true;
        exponent = 0;
        return *this;
    }
    pos = pos == a.pos;
    

    exponent += a.exponent; // re-adjust as needed at the end of the calculation sig will be in [1, 4)
    int tSz = static_cast<int>(sig.size()), aSz = static_cast<int>(a.sig.size()), cSz = aSz,
        tBitCount = 8 * tSz - getRightZeros(sig), aBitCount = 8 * aSz - getRightZeros(a.sig), cBitCount = aBitCount,
        tCharIdx = -1, aCharIdx = -1, cCharIdx = -1, 
        id8 = 0, jd8 = 0, k = 0, kd8 = 0, km8 = 0, ext = 0,
        bytesNeeded = 0, delta = 0;
    unsigned char tChar = 0, aChar = 0, 
        cChar = 0, carry = 0, 
        tbit = 0, abit = 0, cbit = 0, obit = 0, flt = 0X80, f = 0,
        im8 = 0, jm8 = 0, cm1Char = 1;
    vector<unsigned char> acc = a.sig;

    for (int i = 0; i < tBitCount; ++i)
    {
        id8 = i / 8;
        im8 = i % 8;
        if (id8 != tCharIdx)
        {
            tCharIdx = id8;
            tChar = sig.at(tCharIdx);
        }
        tbit = (tChar & (flt >> im8)) >> (7 - im8);
        if (tbit == 1)
        {
            ext = min(i + 1 + aBitCount, BMAX - 1);
            if (ext > cBitCount)
            {
                bytesNeeded = ext / 8 + 1 - cSz;
                if (bytesNeeded > 0) acc.insert(acc.end(), static_cast<size_t>(bytesNeeded), 0);
                cSz += bytesNeeded;
                cBitCount = ext;
            }
            delta = i + 1; //ext - i - 1;
            aCharIdx = -1;
            cCharIdx = -1;
            carry = 0;
            for (int j = ext - 1; j >= 0; --j)
            {
                jd8 = j / 8;
                if (jd8 != cCharIdx)
                {
                    cCharIdx = jd8;
                    cChar = acc.at(cCharIdx);
                }
                jm8 = j % 8;
                f = flt >> jm8;
                cbit = (cChar & f) >> (7 - jm8);
                k = j - delta;
                kd8 = k / 8;
                if ((kd8 != aCharIdx) && (k >= 0))
                {
                    aCharIdx = kd8;
                    aChar = a.sig.at(aCharIdx);
                }
                km8 = k % 8;
                abit = k == -1? 1: k < -1? 0: (aChar & (flt >> km8)) >> (7 - km8);
                obit = carry ^ cbit ^ abit;
                if (obit != cbit) cChar ^= f; // this will change cChar at bit f
                carry = carry == 0? cbit & abit: cbit | abit;
                if ((carry == 0) && (j < i))
                {
                    acc[cCharIdx] = cChar;
                    break;
                }
                if (jm8 == 0) acc[cCharIdx] = cChar;
            }
            if (carry == 1)
            {
                ++cm1Char;
                assert(cm1Char < 4);
            }
        }
    }
    if (cm1Char > 1) 
    {
        if (exponent_cmp(exponent, 1) == 1)
        {
            inf = true;
            exponent = 0;
            sig.clear();
            return *this;
        }
        ++exponent;
        acc.insert(acc.begin(), cm1Char);
        standardize_v(acc);
    }
    else
    {
        while ((acc.size() > 0) && (acc.at(acc.size() - 1) == 0)) acc.pop_back();
    }
    
    sig = acc;
    return *this;
*/
}

mfloat & mfloat::operator/=(const mfloat & a)
{
    if (a.zero)
    {
        nan = true;
        inf = true;
        zero = false;
        //pos = true; + or - infinity is OK
        exponent = 0;
        sig.clear();
    }
    if (nan) return *this;
    if (inf) return *this;
    if (sub) return *this;
    if (zero) return *this; 

    pos = pos == a.pos;
    if (exponent_cmp(exponent, -a.exponent) == 1)
    {
        sub = true;
        exponent = 0;
        sig.clear();
        return *this;
    }
    exponent -= a.exponent; // decrement if units bit is 0 

    bool allZeros = false, appendBit = true, ABeginReached = false;
    int tSz = static_cast<int>(sig.size()), aSz = static_cast<int>(a.sig.size()), cSz = aSz,
        tBitCount = 8 * tSz - getRightZeros(sig), aBitCount = 8 * aSz - getRightZeros(a.sig), cBitCount = 0,
        tIdx = 0, qIdx = 0, tCharIdx = -1, aCharIdx = -1, cCharIdx = -1, 
        id8 = 0, leadZeros = 0, td8 = 0;
    unsigned char tChar = 0, aChar = 0, 
        cChar = 0, borrow = 0, 
        tbit = 0, abit = 0, cbit = 0, rbit = 0, qbit = 0, flt = 0X80, f = 0,
        im8 = 0, notcbit = 0, 
        qm1Char = 0, qChar = 0, qm8 = 0, tm8 = 0;
    vector<unsigned char> Q;
    list<unsigned char> A, C;
    list<unsigned char>::iterator AIT, CIT, nZIT;
   // loading a's significand into bit list A
    // and this significand into bit list C:
    A.push_back(1); // leading 1 bit in significand
    C.push_back(1); // leading 1 bit in significand
    for (int i = 0; i < aBitCount; ++i)
    { // load a.sig into A & sig into C (i.e. vectors into lists)
        id8 = i / 8;
        im8 = i % 8;
        if (id8 != aCharIdx)
        {
            aCharIdx = id8;
            aChar = a.sig.at(aCharIdx);
            tChar = aCharIdx < tSz? sig.at(aCharIdx): 0;
        }
        abit = (aChar & (flt >> im8)) >> (7 - im8);
        A.push_back(abit);
        tbit = (tChar & (flt >> im8)) >> (7 - im8);
        C.push_back(tbit);

    }
    tIdx = aBitCount;  // this is the next bit to get
    td8 = tIdx / 8;
    tm8 = tIdx % 8;
    if (td8 != tCharIdx)
    {
        tCharIdx = td8;
        tChar = tCharIdx < tSz? sig.at(tCharIdx): 0;
    }
    ++aBitCount; // this is the total number of bits in A and C at this point
    cBitCount = aBitCount;
    // dealing with bit -1, ensuring that it is equal to 1:
    if (C < A) 
    {
        if (exponent_cmp(exponent, -1) == 1)
        {
            sub = true;
            exponent = 0;
            sig.clear();
            return *this;
        }
        --exponent;
        tbit = (tChar & (flt >> tm8)) >> (7 - tm8);
        C.push_back(tbit);
        td8 = (++tIdx) / 8;
        tm8 = tIdx % 8;
        if (td8 != tCharIdx)
        {
            tCharIdx = td8;
            tChar = tCharIdx < tSz? sig.at(tCharIdx): 0;
        }
        ++cBitCount;
    }
    f = 1;
    while (qIdx < BMAX)
    {
        leadZeros = 0;
        borrow = 0;
        ABeginReached = false;
        AIT = A.end();
        CIT = C.end();
        nZIT = CIT;
        do 
        {  // subtraction C(omparator) - A:
            if (!ABeginReached) --AIT;
            --CIT;
            cbit = *CIT; 
            abit = ABeginReached? 0: *AIT;
            rbit = borrow ^ cbit ^ abit;
            notcbit = (~cbit) & f;
            borrow = borrow == 1? notcbit | abit: notcbit & abit;
            if (rbit != cbit) *CIT = rbit;
            if (rbit == 0) ++leadZeros;
            else 
            {
                leadZeros = 0;
                nZIT = CIT;
            }
            ABeginReached = (AIT == A.begin());
        } while (CIT != C.begin());
        //assert (leadZeros > (cBitCount - aBitCount));
        if (leadZeros == cBitCount)
        {
            if (tIdx >= tBitCount) 
            {
                if (qChar != 0) 
                {
                    Q.push_back(qChar);
                    qChar = 0;
                }
                break;
            }
            allZeros = true;
        }
        C.erase(C.begin(), nZIT);
        cBitCount -= leadZeros;
        do
        {
            tm8 = tIdx % 8;
            tbit = (tChar & (flt >> tm8)) >> (7 - tm8);
            allZeros = allZeros && (tbit == 0);
            if (!allZeros)
            {
                C.push_back(tbit);
                ++cBitCount;
            }
            td8 = (++tIdx) / 8;
            if (td8 != tCharIdx)
            {
                tCharIdx = td8;
                tChar = tCharIdx < tSz? sig.at(tCharIdx): 0;
            }
            appendBit = (cBitCount < aBitCount) || ((cBitCount == aBitCount) && (C < A));
            if (appendBit)
            { // appending zeros to quotient:
                qm8 = (++qIdx) % 8;
                if ((qm8 == 0) || (qIdx == BMAX))
                {
                    Q.push_back(qChar);
                    qChar = 0;
                    if (qIdx == BMAX) break;
                }
            }
        } while (appendBit);
        // appending one to quotient:
        if (qIdx < BMAX)
        {
            qChar |= (flt >> qm8);
            qm8 = (++qIdx) % 8;
            if (qm8 == 0)
            {
                Q.push_back(qChar);
                qChar = 0;
            }
        }

    }
    if ((qChar != 0) && (qIdx < BMAX) && (qm8 > 0)) Q.push_back(qChar);
    while ((Q.size() > 0) && (Q.at(Q.size() - 1) == 0)) Q.pop_back();
    sig = Q;
    return *this;

}

mfloat::operator mint(void)
{ // returns zero on nan inf sub zero or negative exponent
    mint r;  // default constructor r is 0
    if ((exponent < 0) || (zero) || (nan) || (inf) || (sub)) return r;
    r.positive = pos;
    r.digits.clear();
    int bitCount = exponent + 1, bytesAvailable = sig.size(), 
        iCharIdx = -1, oIdx = (8 - (bitCount % 8)) % 8, jCharIdx = -1,
        id8 = 0, jd8 = 0, totalbits = 8 * ((bitCount / 8) + (bitCount % 8 == 0? 0: 1)),
        j = 0;
    unsigned char iChar = 0, flt0 = 0x80, oChar = 0, om8 = 0, iflt = 0, oflt = 0, im8 = 0, jm8 = 0, bit = 0;
    for (int i = oIdx; i < totalbits; ++i)
    {
        id8 = i / 8;
        im8 = i % 8;
        oflt = flt0 >> im8;
        // get bit:
        if (i == oIdx) bit = 1; // leading one
        else
        {
            j = i - oIdx - 1;
            jd8 = j / 8;
            jm8 = j % 8;
            if (jd8 != jCharIdx)
            {
                jCharIdx = jd8;
                iChar = jCharIdx < bytesAvailable? sig.at(jCharIdx): 0;
            }
            iflt = flt0 >> jm8;
            bit = (iChar & iflt) >> (7 - jm8);
        }
        if (bit == 1) oChar |= oflt;
        if (im8 == 7)
        {
            r.digits.push_back(oChar);
            oChar = 0;
        }
    }
    assert (im8 == 7);
    return r;
}

mfloat::operator float(void)
{
    union {
        float uf;
        unsigned char uc[4];
    } f_union;
    size_t tSz = sig.size();
    int e = (exponent < -127) || (sub) || (zero)? -127: (exponent > 128) || (inf) || (nan)? 128: exponent;
    unsigned char S = pos? 0: 1, E = static_cast<unsigned char>(e + 127),
        tByte = 0, cByte = 0, nxtByte = 0, B0, B1;
    for (size_t i = 1; i < 4; ++i) 
    {
        tByte = i < (1 + tSz)? sig.at(i - 1): 0;
        cByte = (tByte >> 1) | nxtByte;
        f_union.uc[i] = cByte;
        nxtByte = tByte << 7;
    }
    B0 = (S << 7) | (E >> 1);
    B1 = (E << 7) | f_union.uc[1];
    f_union.uc[0] = B0;
    f_union.uc[1] = B1;

    if (nan || sub) f_union.uc[3] = 0xff;
    if (!LittleEndianSys)
    {
        unsigned char buff[4];
        memcpy(buff, f_union.uc, 4);
        for (size_t i = 0; i < 4; ++i)
        {
            f_union.uc[i] = buff[3 - i];
        }
    }
    float r = f_union.uf;
    return r;

}

mfloat::operator double(void)
{
    union {
        double ud;
        unsigned char uc[8];
    } d;
    size_t tSz = sig.size();
    int e0 = (exponent < -1023) || (sub) || (zero)? -1023: (exponent > 1024) || (inf) || (nan)? 1024: exponent;
    unsigned int e1 = e0 + 1023;

    unsigned char S = pos? 0: 1, E0 = static_cast<unsigned char>(e1 >> 4), 
        E1 = static_cast<unsigned char>(e1 & 0xf), 
        tByte = 0, cByte = 0, nxtByte = 0, B0, B1;
    for (size_t i = 1; i < 8; ++i) 
    {
        tByte = i < (1 + tSz)? sig.at(i - 1): 0;
        cByte = (tByte >> 4) | nxtByte;
        d.uc[i] = cByte;
        nxtByte = tByte << 4;
    }
    B0 = (S << 7) | E0;
    B1 = (E1 << 4) | d.uc[1];
    d.uc[0] = B0;
    d.uc[1] = B1;
    if (nan || sub) d.uc[7] = 0xff;

    if (!LittleEndianSys)
    {
        unsigned char buff[8];
        memcpy(buff, d.uc, 8);
        for (size_t i = 0; i < 8; ++i)
        {
            d.uc[i] = buff[7 - i];
        }
    }
    double r = d.ud;
    return r;
    
}


void mfloat::alignByte(const unsigned char & iChar, const unsigned char & iCharIdx, unsigned char & oChar, const unsigned char & oCharIdx)
{
    unsigned char f_i = 0x80 >> iCharIdx, ibit = iChar & f_i, 
        f_o = 0x80 >> oCharIdx, 
        obit = f_i > f_o? ibit << (f_i - f_o): f_i < f_o? ibit >> (f_o - f_i): ibit;
    oChar |= obit;
}

int mfloat::exponent_cmp(const string & exp_part)
{ // [2^(-2^31), 2^(2^31 - 1)] comparable to (10^-646456993, 10^646456992)
    string buff = exp_part, cmpto = "646456992"; //cmpto = "2147483647";
    size_t l_c = cmpto.size();
    bool isNeg = (buff.size() > 0) && (buff.at(0) == '-');
    if (isNeg) 
    {
        buff = buff.substr(1);
        cmpto = "646456993"; //"2147483648";
    }
    if (buff.size() > l_c) return 1;
    if (buff.size() < l_c) return -1;
    return buff.compare(cmpto);
}

int mfloat::exponent_cmp(const int & a, const int & b)
{ // checks sum of a and b: if within integer range returns -1, if on returns 0 else returns 1
    long la = a, lb = b, l = la + lb;

    if ((l == -2147483648) || (l == 2147483647)) return 0;
    if ((l > -2147483648) && (l < 2147483647)) return -1;
    return 1;
}

bool mfloat::isthisZero(const string & int_part, const string & fract_part)
{ // d will be int_part + '.' + fract_part

    //bool ipZero = int_part.size() == 0, fpZero = fract_part.size() == 0;
    size_t ipSz = int_part.size(), fpSz = fract_part.size();
    string buff = "";
    if (ipSz > 0)
    {
        buff = int_part;
        //ipZero = true;
        char c = buff.at(0);
        if ((c == '+') || (c == '-')) buff = buff.substr(1);
        ipSz = buff.size();
        for (size_t i = 0; i < buff.size(); ++i)
        {
            c = buff.at(i);
            if (c != '0') return false;
        }
    }
    if (fpSz > 0)
    {
        buff = fract_part;
        //fpZero = true;
        char c = buff.at(0);
        if ((c == '+') || (c == '-')) buff = buff.substr(1);
        fpSz = buff.size();
        for (size_t i = 0; i < buff.size(); ++i)
        {
            char c = buff.at(i);
            if (c != '0') return false;
        }

    }
    return ((ipSz + fpSz) > 0);
}

void mfloat::standardize_d(string & d, int & D)
{ // d will be a non-zero positive decimal string dddd.dddd D is the exponent

    size_t point_pos = d.find('.');
    assert (point_pos != string::npos);
    if (point_pos == 0) 
    {
        d = '0' + d;
        ++point_pos;
    }
    size_t delta = point_pos - 1;
    D += delta;
    // removing decimal point:
    d = d.substr(0, point_pos) + d.substr(point_pos + 1);
    size_t dPos = d.find_first_not_of('0');
    assert (dPos != string::npos);
    // removing leading zeros:
    d = d.substr(dPos);
    D -= dPos;
    // adding the decimal point back in:
    d = d.substr(0, 1) + "." + d.substr(1);
    // adding final zero for integer returns:
    if (d.size() == 2) d += "0";
    // removing trailing zeros
    while ((d.size() > 3) && ('0' == d.at(d.size() - 1))) d.pop_back();

}

void mfloat::get2sComplement(int & a)
{
    assert (sizeof(int) == 4);
    bool set1 = false;
    int b = a, iflt = 0xff000000;
    unsigned char B[4], cflt0 = 0x80, BIdx = 0;
    for (int i = 0; i < 4; ++i)
    {
        B[i] = static_cast<unsigned char>((b & iflt) >> 24);
        b <<= 8;
    }
    for (int i = 31; i >= 0; --i)
    {
        BIdx = i / 8;
        unsigned char im8 = i % 8, f = cflt0 >> im8, bit = (B[BIdx] & f) >> (7 - im8);
        if (set1) B[BIdx] ^= f;
        set1 = set1 || (bit == 1);

    }
    for (int i = 0; i < 4; ++i)
    {
        a <<= 8;
        a |= B[i];
    }
    assert (a != 0);  // the 2s comp of -2^31 is an error
}


mfloat::operator int(void)
{ // -2^31 .. 2^31-1 returns 0 on error
    int r = 0;
    if ((zero) || (nan) || (inf) || (sub) ||  (exponent < 0)) return r;
    if ((exponent == 31) && (!pos))
    {
        if (sig.size() == 0) return -2147483648; // minimum int -2^31
        return r;
    }
    if (exponent > 30) return r;
    size_t bytesAvailable = sig.size(), iCharIdx = 0;
    unsigned char /*B[] = {0, 0, 0, 0}, BIdx = 0, BFill = 1, */f0 = 0x80, iChar = 0;
    if (bytesAvailable > iCharIdx) iChar = sig.at(iCharIdx);
    //B[0] = 1; // MSB
    r = 1;
    for (size_t i = 0; i < exponent; ++i)
    {
        unsigned char im8 = i % 8, f = f0 >> im8;
        //B[BIdx] <<= 1;
        //B[BIdx] |= (iChar & f) >> (7 - im8);
        //BFill = (BFill + 1) % 8;
        //if (BFill == 0) ++ BIdx;
        r <<= 1;
        r |= (iChar & f) >> (7 - im8);
        if (7 == im8) 
        {
            iChar = 0;
            ++iCharIdx;
            if (sig.size() > iCharIdx) iChar = sig.at(iCharIdx);
        }
    }
    //for (int i = 0; i < 4; ++i)
    //{
    //    r <<= 8;
    //    r |= B[i];
    //}
    if (!pos) get2sComplement(r);

    return r;
}

bool mfloat::isInt(void)
{
    if ((nan) || (inf) || (sub) ||  (exponent < 0)) return false;
    if (zero) return true;
    size_t sZ = sig.size() * 8;
    if ((exponent == 31) && (!pos)) return (sZ == 0);
    if (exponent > 30) return false;
    unsigned char f0 = 0x80;
    if (sZ > 0)
    {
        unsigned char fChar = sig.at(sig.size() - 1);
        for (int i = 7; i >= 0; --i)
        {
            unsigned char f = f0 >> i, bit = (fChar & f) >> (7 - i);
            if (bit == 1) break;
            else --sZ;
        }
        
    }
    return (exponent >= sZ);
}

bool mfloat::isNumber(void)
{
    return (!nan && !inf && !sub);

}

int & mfloat::getExponent(void)
{
    return exponent;
}

int mfloat::min(const int & a, const int & b)
{
    int r = a;
    if (a > b) r = b;
    return r;
}

int mfloat::max(const int & a, const int & b)
{
    int r = a;
    if (a < b) r = b;
    return r;
}

unsigned char mfloat::getRightZeros(const vector<unsigned char> & s)
{
    size_t sSz = s.size();
    unsigned char lstChar = 0, r = 0, lFlt = 0x80;
    if (sSz == 0) return r;
    lstChar = s.at(sSz - 1);
    assert (lstChar != 0);
    for (int i = 7; i >=0; --i)
    {
        unsigned char f = lFlt >> i,
            bit = (lstChar & f) >> (7 - i);
        if (bit == 1) return r;
        ++r;
    }
    assert (1 == 2);
    return r;
}

vector<unsigned char> mfloat::add_magnitude(const vector<unsigned char> & primary, const vector<unsigned char> & secondary, int & delta)
{ // delta in >= 0 is difference in exponent (primary - secondary), out is 0 or 1 indicating change in primary exponent of resultant
  // for zero result delta is set to -1 as a flag
    vector<unsigned char> r;
    int d = delta;
    delta = d == 0? 1: 0;
    assert (d >= 0);
    int pSz = static_cast<int>(primary.size()), sSz = static_cast<int>(secondary.size()), 
        pBitCount = 8 * pSz, sBitCount = 8 * sSz;
    unsigned char pChar = 0, sChar = 0,
        pRightZeros = getRightZeros(primary), sRightZeros = getRightZeros(secondary),
        flt = 0x80;

    pBitCount -= pRightZeros;
    sBitCount -= sRightZeros;

    int m = min(BMAX - 1, max(pBitCount - 1, sBitCount - 1 + d)), // starting index
        pIdx = pBitCount - 1, sIdx = sBitCount - 1, j = 0,
        pCharIdx = -1, sCharIdx = -1,
        idiv8 = 0, sdiv8 = 0;
    unsigned char carry = 0, oChar = 0, im8 = 0,
        pbit = 0, sbit = 0, sm8 = 0, pm8 = 0, rbit = 0;
    for (int i = m; i >= 0; --i)
    {
        idiv8 = i / 8;
        im8 = i % 8;
        j = i - d;
        sdiv8 = j / 8;
        sm8 = j % 8;
        if (pCharIdx != idiv8) 
        {
            pCharIdx = idiv8;
            pChar = pCharIdx < pSz? primary.at(pCharIdx): 0;
        }
        if (j >= 0) 
        {
            if (sCharIdx != sdiv8)
            {
                sCharIdx = sdiv8;
                sChar = sCharIdx < sSz? secondary.at(sCharIdx): 0;
            }
        }
        else sChar = 0;
        
        //if (i > pIdx) pbit = 0;
        //else pbit = (pChar & (flt >> im8)) >> (7 - im8);

        pbit = i > pIdx? 0: (pChar & (flt >> im8)) >> (7 - im8);
        
        //if (j < 0)
        //{
        //    if (j == -1) sbit = 1;
        //    else sbit = 0;
        //}
        //else
        //{
        //    if (j > sIdx) sbit = 0;
        //    else sbit = (sChar & (flt >> sm8) >> (7 - sm8));
        //}
        
        

        sbit = j == -1? 1: j < -1? 0: j > sIdx? 0: (sChar & (flt >> sm8)) >> (7 - sm8);
        
        if (i == pIdx) --pIdx;
        if (j == sIdx) -- sIdx;
        rbit = carry ^ (pbit ^ sbit);
        oChar |= (rbit << 7);
        if (im8 == 0)
        {
            r.push_back(oChar);
            oChar = 0;
        }
        else oChar >>= 1;

        carry = carry == 0? pbit & sbit: pbit | sbit;
    }
    oChar = 1;
    if (d == 0)
    {
        oChar <<= 1;
        oChar |= carry; 
    }
    else 
    {
        oChar += carry;
        delta += carry;
    }
    r.push_back(oChar);
    std::reverse(r.begin(), r.end());    
    if (standardize_v(r) < 0)
    { // we have zero:
        r.clear();
        delta = -1;
    }
    return r;
}
    
vector<unsigned char> mfloat::subtract_magnitude(const vector<unsigned char> & primary, const vector<unsigned char> & secondary, int & delta)
{ // delta in >= 0 is difference in exponent (primary - secondary), out is <=0 indicating change in primary exponent of resultant
  // check for zero result before calling this method - zero cannot be standardized
  // check that primary > secondary

    vector<unsigned char> r;
    int d = delta;
    //delta = d == 0? 1: 0;
    int pSz = static_cast<int>(primary.size()), sSz = static_cast<int>(secondary.size()), 
        pBitCount = 8 * pSz, sBitCount = 8 * sSz;
    unsigned char pChar = 0, sChar = 0,
        pRightZeros = getRightZeros(primary), sRightZeros = getRightZeros(secondary),
        flt = 0x80, bit_flt = 0x1;

    pBitCount -= pRightZeros;
    sBitCount -= sRightZeros;

    int m = min(BMAX - 1, max(pBitCount - 1, sBitCount - 1 + d)),
        pIdx = pBitCount, sIdx = sBitCount, j = 0,
        pCharIdx = -1, sCharIdx = -1,
        idiv8 = 0, sdiv8 = 0;
    unsigned char borrow = 0, oChar = 0, im8 = 0,
        pbit = 0, sbit = 0, sm8 = 0, pm8 = 0, rbit = 0,
        notpbit = 0;
    for (int i = m; i >= 0; --i)
    {
        idiv8 = i / 8;
        im8 = i % 8;
        j = i - d;
        sdiv8 = j / 8;
        sm8 = j % 8;
        if (pCharIdx != idiv8) 
        {
            pCharIdx = idiv8;
            pChar = pCharIdx < pSz? primary.at(pCharIdx): 0;
        }
        if (j >= 0) 
        {
            if (sCharIdx != sdiv8)
            {
                sCharIdx = sdiv8;
                sChar = sCharIdx < sSz? secondary.at(sCharIdx): 0;
            }
        }
        else sChar = 0;
        pbit = i > pIdx? 0: (pChar & (flt >> im8)) >> (7 - im8);
        sbit = j < 0? j == -1? 1: 0: j > sIdx? 0: (sChar & (flt >> sm8)) >> (7 - sm8);
        if (i == pIdx) --pIdx;
        if (j == sIdx) -- sIdx;
        rbit = borrow ^ pbit ^ sbit;
        oChar |= (rbit << 7);
        if (im8 == 0)
        {
            r.push_back(oChar);
            oChar = 0;
        }
        else oChar >>= 1;
        notpbit = (~pbit) & bit_flt;
        borrow = borrow == 1? notpbit | sbit: notpbit & sbit; 
    }
    bool Insert1 = (borrow == 0) && (d != 0), 
        UseFNZ = (d == 0) || (borrow == 1);
    if (d == 0) assert (borrow == 0); // no negatives allowed here
    if (Insert1)
    {
        delta = 0;
        r.push_back(1);
    }
    std::reverse(r.begin(), r.end());
    if (UseFNZ)
    {
        int FNZ = getFirstNonZero(r) + 1;
        delta = -FNZ;
    }
    
    //r.push_back(oChar);
    //std::reverse(r.begin(), r.end());
    //int FNZ = getFirstNonZero(r);
    //delta = -FNZ;    
    standardize_v(r);
    return r;

}



int mfloat::standardize_v(vector<unsigned char> & NQR)
{ // on entry: NQR must have a non-zero byte, the inital 1 of the bits in the significand (i.e. NQR) is included
  // on exit: initial one is removed, bit 1 (if present) will be in position 0 of significand (i.e. NQR)

    int fNZ = getFirstNonZero(NQR), iCharIdx = fNZ / 8;
    if (fNZ == -1) return fNZ;

    unsigned char iIdx = fNZ % 8, shiftLeft = (iIdx + 1) % 8, shiftRight = 8 - shiftLeft, 
        iChar0 = NQR.at(iCharIdx), iChar1 = 0, oChar = 0, 
        flt = 0x80, f = flt >> iIdx, bit = (iChar0 & f) >> (7 - iIdx);

    assert (bit == 1);

    NQR[iCharIdx] ^= f; // should clear bit in this byte

    size_t nSz = NQR.size(), delFront = iCharIdx + (shiftLeft == 0? 1: 0);

    
    // remove 0 bytes
    if (delFront > 0) NQR.erase(NQR.begin(), NQR.begin() + delFront);
    nSz -= delFront; 
    assert (nSz == NQR.size());
    while ((nSz > 0) && (NQR.at(nSz - 1) == 0))
    {
        --nSz;
        NQR.pop_back();
    }
    if ((nSz > 0) && (shiftLeft > 0))
    {
        iChar0 = 0;
        for (size_t i = nSz; i > 0; --i)
        {
            iChar1 = iChar0;
            iChar0 = NQR.at(i - 1);
            oChar = (iChar0 << shiftLeft) | (iChar1 >> shiftRight);
            NQR[i - 1] = oChar; 
        }
    }
    assert (nSz == NQR.size());
    int byteMax = BMAX / 8 + (BMAX % 8 == 0? 0: 1);
    while (nSz > byteMax)
    {
        --nSz;
        NQR.pop_back();
    }
    while ((nSz > 0) && (NQR.at(nSz - 1) == 0))
    {
        --nSz;
        NQR.pop_back();
    }
    return fNZ;
}

int mfloat::getFirstNonZero(const vector<unsigned char> & v)
{
    int r = -1, vSz = static_cast<int>(v.size());
    unsigned char iChar = 0, flt = 0x80;
    for (int i = 0; i < vSz; ++i)
    {
        iChar = v.at(i);
        if (iChar != 0)
        {
            for (unsigned char j = 0; j < 8; ++j)
            {
                if ((flt & iChar) == flt)
                {
                    r = 8 * i + j;
                    return r;
                }
                flt >>= 1;
            }
        }
    }
    return r;
}

int mfloat::getFirstNonZero(const int & iIn)
{
    if (iIn == 0) return -1;
    unsigned char B[4], flt0 = 0x80, f = 0, bit = 0;
    int iflt0 = 0xff000000, iflt = 0;

    for (int i = 0; i < 4; ++i)
    {
        iflt = iflt0 >> (8 * i);
        B[i] = (iIn & iflt) >> (8 * (3 - i));

    }

    for (int i = 0; i < 4; ++i)
    {
        if (B[i] != 0)
        {
            for (unsigned char j = 0; j < 8; ++j)
            {
                f = flt0 >> j;
                bit = (B[i] & f) >> (7 - j);
                if (bit == 1) return ((8 * i) + j);
            }
        }
    }

    return -1;
}

string mfloat::ConvertToDecimal(void)
{
    string dStr = nan? "nan": inf? "inf": sub? "sub": "";
    if ((nan) || (inf) || (sub)) return dStr;
    if (zero) 
    {
        //dStr = "0.0" + exp_char + "0";
        dStr = "0.0E0";
        return dStr;
    }

    char dChar = 0;
    mfloat Dr(handleCONSTANT(LN_2_OVER_10)), bfact(handleCONSTANT(LN_10)), b(*this), ten(10.0f);
    //double D1 = static_cast<double>(Dr),
    //    D2 = static_cast<double>(bfact),
    //    D3 = static_cast<double>(b),
    //    D4 = static_cast<double>(ten);
    int B = exponent, Dz = 0, dInt = 0;
    //if (!pos) dStr = "-";

    b.pos = true;
    b.exponent = 0;
    bool overflow = false;

    bool exp_small = (B > -100) && (B < 100);
    if (!exp_small)    
    {
        
        BMAX += 32;
        Dr *= B;
        //double D5 = static_cast<double>(Dr);
        Dz = Dr.getIntAndReal(overflow);
        assert (!overflow);
        BMAX -= 32;
        //double D6 = static_cast<double>(Dr);
        bfact *= Dr;
        //double D7 = static_cast<double>(bfact);
        //bfact.eToThex();
        //bfact.newton_e();
        bfact.taylor_agm_e();
        //double D8 = static_cast<double>(bfact);
        b *= bfact;
        //double D9 = static_cast<double>(bfact);
        
    }
    if (b.IsGT(ten)) 
    {
        b /= ten;    
        ++Dz;
    }

    for (int i = 0; i < DMAX; ++i)
    {
        if (b.zero) break;
        //double db0 = static_cast<double>(b);
        dInt = b.getIntAndReal(overflow);
        if (overflow) break;
        //double db1 = static_cast<double>(b);
        assert (dInt < 10);
        dChar = '0' + static_cast<char>(dInt);
        dStr += dChar;
        if (i == 0) dStr += ".";
        //b -= mint(dInt);
        b *= ten;
    }

    if (exp_small)
    {
        if (B > 0)
        {
            for (int i = 0; i < B; ++i)
            {
                dStr = twice(dStr);
            }
        }
        if (B < 0)
        {
            for (int i = 0; i < (-B); ++i)
            {
                dStr = half(dStr);
            }
        }
    }
    dStr = RoundMe(dStr);
    standardize_d(dStr, Dz);
    int sigfigs = dStr.size() - 1;
    if (!pos) dStr = '-' + dStr;
    dStr += "E" + to_string(Dz);
    //dStr += exp_char + to_string(Dz);
    //dStr += " <" + to_string(sigfigs) + " significant figures>\n";
    return dStr;
}

int mfloat::getIntAndReal(bool & overflow)
{ // returns an integer r such that this is r + fract where fract is a real number >=0 &  < 1.0
  // this becomes fract
    //double Dt = static_cast<double>(*this);
    overflow = exponent > 30;
    if (overflow) 
    {
        zero = true;
        pos = true;
        exponent = 0;
        sig.clear();
        return 0;
    }
    int r = static_cast<int>(*this);
    bool Exact = isInt();
    if (Exact)
    {
        zero = true;
        exponent = 0;
        sig.clear();
        pos = true;
        return r;
    }

    //mint rm(r);
    //mfloat rf(rm);
    //double Dt3 = static_cast<double>(rf);

    //*this -= rf;
    ClearInt();
    
    //double Dt2 = static_cast<double>(*this);
    if (!pos)
    { // at this point -1 < this < 0
        --r;
        mfloat buff(*this);
        *this = 1.0f;
        *this += buff;
    }

    return r;
}

void mfloat::ClearInt(void)
{
    if ((nan) || (inf) || (sub) ||  (exponent < 0) || (zero)) return;
    int sZ = static_cast<int>(sig.size()), bitCount = sZ * 8 - getRightZeros(sig),
        e = exponent, ed8 = e / 8, id8 = 0, iCharIdx = -1, i = 0;
    unsigned char f0 = 0x80, em8 = e % 8, im8 = 0, iChar = 0, ibit = 0,
        iChar0 = 0, oChar = 0;
    if (e >= bitCount)
    {
        zero = true;
        exponent = 0;
        pos = true;
        sig.clear();
        return;
    }
    // find first 1 after bit after e:
    for (i = e; i < bitCount; ++i)
    {
        id8 = i / 8;
        im8 = i % 8;
        if (id8 != iCharIdx)
        {
            iCharIdx = id8;
            iChar = sig.at(iCharIdx);
        }
        ibit = (iChar & (f0 >> im8)) >> (7 - im8);
        if (ibit == 1) break;
    }
    assert (i < bitCount);
    exponent = e - i - 1; //-(i - e + 1);
    // shifting sig:
    
    ++im8;
    if (im8 == 8) ++id8;
    im8 %= 8;
    if (id8 > 0) sig.erase(sig.begin(), sig.begin() + id8);
    sZ -= id8;
    if (im8 > 0)
    {
        iChar0 = 0;
        for (i = sZ; i > 0; --i)
        {
            iChar = sig.at(i - 1);
            oChar = (iChar << im8) | (iChar0 >> (8 - im8));
            iChar0 = iChar;
            sig[i - 1] = oChar;
        }

    }
    while ((sig.size() > 0) && (sig.at(sig.size() - 1) == 0)) sig.pop_back();
}

string mfloat::RoundMe(const string & s)
{ // for decimal strings
    string r = trim(s);
    size_t point_pos = r.find('.');
    if (point_pos == string::npos) return r;
    string int_part = r.substr(0, point_pos),
        fract_part = r.substr(point_pos + 1);
    char sgnChar = int_part.at(0);
    bool signPresent = (sgnChar == '-') || (sgnChar == '+');
    if (signPresent) int_part = int_part.substr(1);
    size_t fSz = fract_part.size(), iSz = int_part.size(), i = 0;
    if (fSz <= DROUND) return r;
    if (signPresent) r = sgnChar;
    else r = "";
    char iChar = fract_part.at(DROUND - 1);
    fract_part = fract_part.substr(0, DROUND - 1);
    bool carry = (iChar >= '5');
    unsigned char uChar = 0;
    if (carry)
    {
        for (i = (DROUND - 1); i > 0; --i)
        {
            iChar = fract_part.at(i - 1);
            uChar = iChar - '0';
            carry = uChar == 9;
            uChar += 1;
            uChar %= 10;
            iChar = uChar + '0';
            fract_part[i - 1] = iChar;
            if (!carry) break;
        }
        if (carry)
        {
            for (i = iSz; i > 0; --i)
            {
                iChar = int_part.at(i - 1);
                uChar = iChar - '0';
                carry = uChar == 9;
                uChar += 1;
                uChar %= 10;
                iChar = uChar + '0';
                int_part[i - 1] = iChar;
                if (!carry) break;
            }
            if (carry) int_part = "1" + int_part;
        }
    }
    while ((fract_part.size() > 0) && ('0' == fract_part.at(fract_part.size() - 1))) fract_part.pop_back();
    r += int_part + '.' + fract_part;
    return r;    
}

void mfloat::RoundMe(void)
{ // handles truncating and rounding the significand from BMAX to BROUND

    int delta = BROUND + 1;
    vector<unsigned char> rBit, r = add_magnitude(sig, rBit, delta);
    int id8 = 0, rSz = static_cast<int>(r.size()), rIdx = -1;
    unsigned char im8 = 0, flt = 0x80, f = 0, rChar = 0, bit = 0;
    for (int i = BROUND; i < BMAX; ++i)
    {
        id8 = i / 8;
        if (id8 >= rSz) break;
        im8 = i % 8;
        f = flt >> im8;
        if (rIdx != id8)
        {
            rIdx = id8;
            rChar = r.at(rIdx);
        }
        bit = (rChar & f) >> (7 - im8);
        if (bit == 1) r[rIdx] ^= f; // reset to 0

    }
    int count = 0;
    while ((r.size() > 0) && (0 == r.at(r.size() - 1)))
    {
        ++count;
        r.pop_back();
    }
    //assert (count > 0); // s/b true if BMAX exceeds BROUND by 8 or more
    sig = r;
    if (exponent_cmp(exponent, delta) == 1)
    {
        inf = true;
        exponent = 0;
        sig.clear();
        return;
    }
    exponent += delta;
}

void mfloat::power(const int & c)
{
    //double pCk1 = static_cast<double>(*this), pCk2 = 0.0;
    mfloat one(1.0f), p(one), frame[31]; // = {*this, one, one, one, one};

    int frameSet = 0, C = c;

    if (C == 0) 
    {
        *this = one;
        return;
    }
    bool invert = (C < 0);
    if (invert) get2sComplement(C);
    if (C == 1)
    {
        if (invert) 
        {
            *this = inverse_m(*this);
        }
        return;
    }
    // getting top set bit (i.e. log2int):
    unsigned char B[4];
    int flt = 0xff, topNZbyte = -1;
    for (int i = 0; i < 4; ++i)
    {
        B[i] = flt & C;
        if (B[i] != 0) topNZbyte = i;
        flt <<= 8;
    }
    assert (topNZbyte >= 0);
    int log2int = topNZbyte * 8 + 7;
    flt = 0x80;
    for (unsigned char i = 0; i < 8; ++i)
    {
        unsigned char f = flt >> i, bit = (f & B[topNZbyte]) >> (7 - i);
        if (bit == 1) 
        {
            log2int -= i;
            break;
        }
    }
    // setting up frame array:
    flt = 0x1; // i.e. 2^0
    frame[0] = *this;
    for (int i = 1; i < 31; ++i)
    {
        //unsigned char f = flt << i; // 2, 4, 8, 16
        if (log2int >= i) 
        {
            frame[i] = sqr(frame[i - 1]);
            //pCk2 = static_cast<double>(frame[i]);
        }
        else frame[i] = one;

    }
    // multiplying p by appropriate elements of frame:
    for (int i = 0; i <= log2int; ++i)
    {
        int bIdx = i / 8, bm8 = i % 8;
        unsigned char f = flt << bm8, bit = (B[bIdx] & f) >> (bm8);
        if (bit == 1) p *= frame[i];
        /*
        {
            int j = flt << i;
            for (int k = 4; k >= 0; --k)
            {
                f = flt << k; // 16, 8, 4, 2, 1
                if (j >= f) 
                {
                    j -= f;
                    p *= frame[k];
                }
            }
            assert (j == 0);
        }
        */
    }
    if (invert)
    {
        one /= p;
        p = one;
    }
    *this = p;

}

int mfloat::power(const mfloat & y)
{ // return x^y where x is this and y is parameter y
  // strategy: return e^(y * ln(x))

    int count = 0; 

    if (!pos) nan = true;
    nan = nan || y.nan;
    inf = inf || y.inf;
    sub = sub || y.sub;
    if (nan || inf || sub) 
    {
        pos = true;
        sig.clear();
        exponent = 0;
        return count;
    }
    if (y.zero)
    {
        *this = 1;
        return count;
    }

    mfloat x(*this);

    count += x.eLog();
    x *= y;
    //count += x.eToThex();
    //count += x.newton_e();
    count += x.taylor_agm_e();
    *this = x;
    return count;
}


int mfloat::arctan(const bool & ReCalc)
{ // modify this to be in the range -pi/2 to +pi/2
    int count = 0;

    if (nan || sub) return count;

    disp.progress_text("arctan(x)");

    mfloat mone(-1.0f), zer(0.0f), one(1.0f), two(2.0f), 
        denom(one), x(*this), x2(sqr(x)), x_term(x), term(x), acc(zer),
        pi(3.141592654), pio4(pi), pio2(pi);
    
    if (!ReCalc)
    {
        pi = handleCONSTANT(P_I);
        pio4 = pi;
        pio2 = pi;        
    }
    pio4.exponent -= 2;
    pio2.exponent -= 1;

    if (x.IsEq(one) || x.IsEq(mone))
    {
        *this = pio4;
        pos = x.IsEq(one);
        return count;
    }
    if (x.inf)
    {
        *this = pio2;
        pos = x.pos;
        return count;
    }

    bool take_complement = !(x.IsGT(mone) && x.IsLT(one));
    if (take_complement)
    {
        x = inverse_m(x);
        x_term = x;
        x2 = sqr(x);
    }

    *this = 0.0f;

    while ((1 + BMAX + term.exponent) > 0)
    {
        ++count;
        term = x_term;
        term /= denom;
        acc += term;
        x_term *= x2;
        denom += two;
        x_term.pos = !(x_term.pos);
        disp.progress(static_cast<double>(-term.exponent) / static_cast<double>(1 + BMAX));

    }
    //cout << "ATAN Iterations: " << to_string(count) << " ";
    if (take_complement) 
    {
        pio2.pos = x.pos;
        acc = pio2 - acc;
    }
    *this = acc;
    disp.progress_text("");
    return count;
}

int mfloat::arctan2(const mfloat & x)
{ // this will be y
    int count = 0;
    mfloat y(*this), pi(handleCONSTANT(P_I)), atan(y);

    // degenerate cases:
    if (IsEq(0) || x.IsEq(0))
    {
        if (IsEq(0) && x.IsEq(0))
        { // the origin point
            nan = true;
            zero = false;
            exponent = 0;
            sig.clear();
            return count;
        }
        if (IsEq(0))
        { // y is 0 - arctan is 0 or pi
            if (x.pos)
            {
                zero = true;
                exponent = 0;
                pos = true;
                sig.clear();
                return count;
            }
            else
            {
                *this = pi;
                return count;
            }
        }
        // x is 0 - artan is + or - pi / 2
        --pi.exponent;
        pi.pos = pos;
        *this = pi;
        return count;
    }

    atan /= x;
    atan.pos = true;
    count = atan.arctan();

    // quadrant adjustment:
    if (x.pos)
    {
        if (!y.pos)
        { // Quad 4:
            atan.pos = false;
            ++pi.exponent;
            atan += pi; //2pi - atan
        }
    }
    else
    { // x is negative:
        if (y.pos)
        { // Quad 2:
            atan.pos = false;
            atan += pi; // pi - atan
        }
        else
        { // y is negative: Quad3:
            atan += pi; // pi + atan
        }
        
    }
    
    *this = atan;

    return count;
}

int mfloat::binary_log(void)
{ // this is too slow when significand has bits
  // iterations needed in this case will be BMAX 
  // (square and compare for each iteration)

    mfloat x(*this);
    //double d1 = static_cast<double>(x);
    sig.clear();
    exponent = 0;
    pos = true;
    zero = true;
    if (x.IsEq(0) || x.IsLT(0))
    {
        nan = true;
        return 0;
    } 
    if (x.IsEq(1)) 
    {
        zero = true;
        return 0;
    }
    zero = false;
    int count = 0, N = x.exponent, e = 0, firstNZ = 1;
    unsigned char oChar = 0, im8 = 0, flt0 = 0x80, f = 0;
    bool foundFZ = false;
    x.exponent = 0;
    for (int i = 0; i < BMAX; ++i)
    {
        im8 = i % 8;

        if (x.sig.size() == 0) break;
        x = sqr(x);
        e = x.exponent;
        assert (e <= 1);
        if (e == 1)
        {
            foundFZ = true;
            f = flt0 >> im8;
            oChar |= f;
            x.exponent = 0;
        }
        else
        {
            if (!foundFZ) ++firstNZ;
        }
        
        if (im8 == 7)
        {
            sig.push_back(oChar);
            oChar = 0;
        }
        ++count;
    }
    if (oChar != 0) sig.push_back(oChar);
    //double d2 = static_cast<double>(*this);
    //if (foundFZ) 
    //{
    //    standardize_v(sig);
    //    double d3 = static_cast<double>(*this);
    //    exponent -= firstNZ;
    //}
    --N;
    mfloat delta_f(N);
    //double d4 = static_cast<double>(delta_f);
    *this += delta_f;
    
    //double d3 = static_cast<double>(*this);
    
    RoundMe();



    return count;
}

int mfloat::square_root(void)
{
    int e = exponent, em2 = abs(e) % 2;
    e -= em2;
    mfloat x(*this);

    if ((zero) || IsEq(1) || (nan) || (inf) || (sub)) return 0;
    if (!pos)
    {
        pos = true;
        nan = true;
        exponent = 0;
        sig.clear();
        return 0;

    }
    sig.clear();
    exponent = e / 2;

    list<unsigned char> P, C;
    int pCount = 0, cCount = 0, 
        xSz = static_cast<int>(x.sig.size()), 
        RZ = getRightZeros(x.sig), xCount = 8 * xSz - RZ,
        i1 = 0, i2 = 0, i1d8 = 0, i2d8 = 0, 
        iChar1Idx = 0, iChar2Idx = 0, xDelta = 2;
    unsigned char iChar1 = 0, iChar2 = 0, 
        oChar = 0, i1m8 = 0, i2m8 = 0, 
        flt0 = 0x80, flt = 0, 
        bit = 0, ybit = 0, cbit = 0, notcbit = 0, 
        borrow = 0;

    // set up first bits:
    P.push_back(1);
    ++pCount;
    if (xSz > 0) iChar1 = x.sig.at(0);
    iChar2 = iChar1;
    if (em2 == 1)
    { // the significand and the invisible first 1 
      // must be shifted left 1 position
        C.push_back(1);
        ++cCount;
        bit = (iChar1 & flt0) >> 7;
        if (bit == 1) 
        {
            C.push_back(0);
            ++cCount;
        }
        // prevent possible range error:
        if (RZ == 0) x.sig.push_back(0);
    }
    else
    {
        xCount += xCount % 2; // let xCount be divisible by 2
        if (RZ == 0) x.sig.push_back(0); // prevent range error
    }

    list<unsigned char>::iterator pit = P.end(), 
        pins = P.end(), cit = C.end();

    // P will be turned into Y here:
    P.push_back(0);
    P.push_back(1);
    pCount += 2;
    --pins; // this will be the insert position for P
    --pins;

    for (int i = 0; i < (xCount / 2); ++i)
    {
        i1 = (2 * i) + em2;
        i1d8 = i1 / 8;
        i1m8 = i1 % 8;
        
        i2 = i1 + 1;
        i2d8 = i2 / 8;
        i2m8 = i2 % 8;
        if (i2d8 != iChar2Idx)
        {
            iChar2Idx = i2d8;
            iChar2 = x.sig.at(iChar2Idx);
        }
        
        
        if (i1d8 != iChar1Idx)
        {
            iChar1Idx = i1d8;
            iChar1 = iChar2;
        }
        flt = flt0 >> i1m8;
        cbit = (iChar1 & flt) >> (7 - i1m8);
        C.push_back(cbit);

        flt = flt0 >> i2m8;
        cbit = (iChar2 & flt) >>(7 - i2m8);
        C.push_back(cbit);
        cCount += 2;
        while ((cCount > 0) && (0 == *C.begin()))
        {
            --cCount;
            C.pop_front();
        }
        if ((pCount < cCount) || ((pCount == cCount) && (P <= C)))
        { // let C = C - P:
            pit = P.end();
            cit = C.end();
            bool pbeginreached = false, cbeginreached = false;
            borrow = 0;
            do
            {
                ybit = 0;
                if (!pbeginreached) 
                {
                    --pit;
                    ybit = *pit;
                }
                --cit;
                cbit = *cit;
                notcbit = (~cbit) & 0x1;
                *cit = borrow ^ (cbit ^ ybit);
                borrow = borrow == 1? notcbit | ybit: notcbit & ybit;

                pbeginreached = (pit == P.begin());
                cbeginreached = (cit == C.begin());

            } while (!cbeginreached);

            assert (borrow == 0);
            P.insert(pins, 1);

        }
        else P.insert(pins, 0);
        ++pCount;

    }

    for (int i = (xCount / 2); i < BMAX; ++i)
    {
        C.push_back(0);
        C.push_back(0);

        cCount += 2;
        while ((cCount > 0) && (0 == *C.begin()))
        {
            --cCount;
            C.pop_front();
        }
        if (cCount == 0) break;
        
        if ((pCount < cCount) || ((pCount == cCount) && (P <= C)))
        { // let C = C - P:
            pit = P.end();
            cit = C.end();
            bool pbeginreached = false, cbeginreached = false;
            borrow = 0;
            do
            {
                ybit = 0;
                if (!pbeginreached) 
                {
                    --pit;
                    ybit = *pit;
                }
                --cit;
                cbit = *cit;
                notcbit = (~cbit) & 0x1;
                *cit = borrow ^ (cbit ^ ybit);
                borrow = borrow == 1? notcbit | ybit: notcbit & ybit;

                pbeginreached = (pit == P.begin());
                cbeginreached = (cit == C.begin());

            } while (!cbeginreached);

            assert (borrow == 0);
            P.insert(pins, 1);

        }
        else P.insert(pins, 0); 
        ++pCount;
    }

    // restoring P from Y:
    P.pop_back();
    P.pop_back();
    pCount -= 2;


    // now to put P into sig:
    pit = P.begin();
    assert (*pit == 1);
    ++pit; // first bit is the invisible 1
    --pCount;
    for (int i = 0; i < pCount; ++i)
    {
        i1d8 = i / 8;
        i1m8 = i % 8;
        flt = flt0 >> i1m8;
        bit = *pit;
        if (bit == 1) oChar |= flt;
        if (i1m8 == 7)
        {
            sig.push_back(oChar);
            oChar = 0;
        }
        ++pit;
    }
    if (oChar != 0) sig.push_back(oChar);
    else while ((sig.size() > 0) && (0 == sig.at(sig.size() - 1))) sig.pop_back();
    
    return pCount;
}

int mfloat::agm(const mfloat & gIn, const string & dInfo) // arithmetic-geometric mean
{
    int count = 0;
    size_t dSz = dInfo.size();
    //if (PB != NULL) PB->set_text("arithmetic-geometric mean");
    if (dSz == 0) disp.progress_text("arithmetic-geometric mean");
    else disp.progress_text(dInfo + " using agm");
    mfloat a(*this), g(gIn), delta = a - g, 
        //old_delta(delta), change(delta),
        aNxt(a), gNxt(g);

    nan = nan || g.nan;
    inf = inf || g.inf;
    sub = sub || g.sub;
    if (nan || inf || sub) return 0;
    if (a.IsEq(g)) return 0;
    sig.clear();
    exponent = 0;
    zero = true;
    pos = true;
    //double ad = 0.0, gd = 0.0;
    double fraction = 0.0,
        bmax = static_cast<double>(BMAX);
        //aDbl = 0.0, gDbl = 0.0, dDbl = 0.0;
    while ((1 + delta.exponent + BMAX) > 0)
    {
        //ad = static_cast<double>(a);
        //gd = static_cast<double>(g);
        ++count;
        aNxt = a;
        aNxt += g;
        //assert (aNxt.sig.size() <= 424);
        //aNxt /= two;
        --aNxt.exponent;
        gNxt = a;
        gNxt *= g;
        gNxt.square_root();
        //assert (gNxt.sig.size() <= 424);
        a = aNxt;
        g = gNxt;
        delta = a;
        delta -= g;
        if (delta.zero) break;
        //if (PB != NULL) 
        //{
            fraction = -delta.exponent / bmax;
            //aDbl = static_cast<double>(a);
            //gDbl = static_cast<double>(g);
            //dDbl = static_cast<double>(delta);
            //if (fraction >= 1.0) fraction = 0.999999;
            //cout << dInfo << delta.exponent << " " << BMAX << " " << fraction << " " << aDbl << " " << gDbl << " " << dDbl << "\n";
            disp.progress(fraction);
            //PB->set_fraction(fraction);
            //while (gtk_events_pending()) gtk_main_iteration();
            //PB->show_all();
        //}
        //change = delta;
        //change -= old_delta;
        //old_delta = delta;
    }
    *this = g;
    if (dSz == 0) disp.progress_text("");
    disp.progress(1.0);
    return count;
}

int mfloat::eLog(const string & dInfo) // natural log w/ agm
{ // this seems faster when inputs are higher
    int count = 0;
    if ((zero) || !(pos))
    { // error -infinity
        pos = true;
        zero = true;
        exponent = 0;
        sig.clear();
        nan = true;
        inf = true;
    }
    if ((nan) || (inf) || (sub)) return 0;

    if (IsEq(1)) 
    {
        *this = 0;
        return 0;
    }
    mfloat x(*this), acc(handleCONSTANT(P_I)), LN2(handleCONSTANT(LN_2)), M(1), s(x), delta = x - M;
    
    if (delta.exponent + BROUND / LOG_BROUND < 0) return naturalLog_1();
    bool invert = IsLT(1);
    if (invert) x = inverse_m(x);
    int m = BMAX / 2 - x.exponent + 1;
    if (!invert) s = inverse_m(s);
    if (exponent_cmp(s.exponent, 2 - m) == 1)
    {
        inf = true;
        exponent = 0;
        sig.clear();
        return 0;
    }
    s.exponent += 2 - m;
    count = M.agm(s, dInfo.size() == 0? "ln(x)": dInfo);
    if (dInfo.size() == 0) disp.progress_text("");
    ++M.exponent;
    acc /= M;
    LN2 *= m;
    acc -= LN2;
    if (invert) acc = inverse_a(acc);
    *this = acc;

    return count;
}

int mfloat::newton_e(void) // e^x using Newtorn's method
{ // y = e^x; ln(y) = x; f(y) = ln(y) - x = 0; f'(y) = 1/y; y - f(y)/f'(y) = y + xy - yln(y)
    int count = 0, agmCount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));// / 2.0;
    //bool unsetted = unset_final(y0);
    //assert (unsetted);
    BMAX += 16;
    mfloat x(*this), y(y0), one(1), //y_prev(y0),
        LOG(one), f_y(one); //delta(x);
    int e_prev = 0;
    // set up x0:
    //x.exponent = y.exponent;
    //double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((1 + f_y.exponent + BMAX) > 16)
    {
        //BMAX += 16;
        //xd0 = static_cast<double>(x);
        //LOG = x;
        e_prev = f_y.exponent;
        LOG = y;
        agmCount += LOG.eLog("e^x via Newton's Method n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        //cout << to_string(count) << " ";
        //xNxt = x * (one + y - LOG);
        //e_prev = y.exponent;
        //y_prev = y;
        //xd1 = static_cast<double>(y_prev);
        f_y = LOG - x;
        //f_y -= x;
        y *= (one - f_y);
        //xd2 = static_cast<double>(y);
        //delta = y - y_prev;
        //delta = xNxt - x;
        
        if ((f_y.zero) || (f_y.exponent >= e_prev)) 
        {
            //BMAX -= 16;
            break;
        }
        //x = xNxt;
        //xd1 = static_cast<double>(x);
        //BMAX -= 16;
        //cout << count << ") Newton so far: " << f_y.exponent << "\n";
    }
    disp.progress_text("");
    *this = y;
    BMAX -= 16;
    return count;
}

int mfloat::halley_e(void) // e^x using Halley's method
{ // y = e^x; ln(y) = x; f(y) = ln(y) - x = 0; f'(y) = 1/y; f''(y) = -1/y^2; 
    int count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));// / 2.0;
    //bool unsetted = unset_final(y0);
    //assert (unsetted);
    BMAX += 32;
    mfloat x(*this), y(y0), one(1), two(2), //y_prev(y0),
        LOG(one), /*delta(x),*/ f_y(one), q(one);
    int e_prev = 0;
    // set up x0:
    //x.exponent = y.exponent;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y.exponent + BMAX) > 32)
    {
        e_prev = f_y.exponent;
        LOG = y;
        agmcount += LOG.eLog("e^x via Halley's Method n=" + to_string(++count));
        xd0 = static_cast<double>(LOG);
        f_y = LOG - x;
        q = one - two * f_y / (two + f_y);
        y *= q;
        //LOG -= x;
        //f_y = LOG;
        //--LOG.exponent; // divide by 2
        //LOG = one - LOG;
        //y_prev = y;
        //xd1 = static_cast<double>(y_prev);
        //y *= (one - f_y / LOG);
        xd2 = static_cast<double>(y);
        //e_prev = delta.exponent;
        //delta = y - y_prev;
        //LOG = y;
        
        //if ((delta.zero) || (delta.exponent == e_prev)) 
        if ((f_y.zero) || (f_y.exponent >= e_prev))
        {
            break;
        }
        cout << count << ") Halley so far: " << f_y.exponent << "\n";
    }
    BMAX -= 32;
    disp.progress_text("");
    *this = y;
    return count;
}

void mfloat::calculateCONSTANT(const CONSTANTS & c)
{
    mfloat F1, F2;
    int iterations;
    string oStr = "";


    switch(c)
    {
        case LN_2:          //cout << "calculating natural log 2 " << flush;
                            disp.write("calculating natural log 2\n");
                            BMAX += 32; // increased precision
                            F1.natural_log_2();
                            //F1 = 2;
                            //iterations = F1.naturalLog();
                            //cout << "<iterations needed: " << F1.naturalLog() << ">\n" << flush;
                            //oStr = "<iterations needed: " + to_string(iterations) + ">\n";
                            oStr += F1.print() + "\n";
                            disp.write(oStr);
                            _ln2 = make_store_float(F1);
                            storeCONSTANT(LN_2);
                            BMAX -= 32;
                            break;

        case LN_5:          //cout << "calculating natural log 5 " << flush;
                            disp.write("calculating natural log 5\n");
                            if (_pi.BIT_COUNT < BMAX) F1 = handleCONSTANT(P_I);
                            if (_ln2.BIT_COUNT < BMAX) F1 = handleCONSTANT(LN_2);
                            BMAX += 32; // increased precision
                            F1 = 5;
                            iterations = F1.eLog(); //F1.naturalLog();//F1.eLog();
                            //cout << "<iterations needed: " << F1.eLog() << ">\n" << flush;
                            oStr = "<iterations needed: " + to_string(iterations) + ">\n";
                            oStr += F1.print() + "\n";
                            disp.write(oStr);
                            _ln5 = make_store_float(F1);
                            storeCONSTANT(LN_5);
                            BMAX -= 32;
                            break;

        case LN_10:         //cout << "calculating natural log 10 (i.e. ln5 + ln2)\n" << flush;
                            disp.write("calculating natural log 10 (i.e. ln5 + ln2)\n\n");
                            F1 = _ln2.BIT_COUNT < BMAX? handleCONSTANT(LN_2): _ln2;
                            F2 = _ln5.BIT_COUNT < BMAX? handleCONSTANT(LN_5): _ln5;
                            //F1 = _ln2;
                            //F2 = _ln5;
                            BMAX += 32;
                            F2 += F1;
                            _ln10 = make_store_float(F2);
                            storeCONSTANT(LN_10);
                            BMAX -= 32;
                            break;         

        case LN_2_OVER_10:  //cout << "calculating natural log 2 divided by natural log 10\n" << flush;
                            disp.write("calculating natural log 2 divided by natural log 10\n\n");
                            F2 = _ln10.BIT_COUNT < BMAX? handleCONSTANT(LN_10): _ln10;
                            F1 = _ln2;
                            //F2 = _ln10;
                            BMAX += 32;
                            F1 /= F2;
                            _ln2oln10 = make_store_float(F1);
                            storeCONSTANT(LN_2_OVER_10);
                            BMAX -= 32;
                            break;

        case LN_10_OVER_2:  //cout << "calculating natural log 10 divided by natural log 2\n" << flush;
                            disp.write("calculating natural log 10 divided by natural log 2\n\n");
                            F2 = _ln10.BIT_COUNT < BMAX? handleCONSTANT(LN_10): _ln10;
                            F1 = _ln2;
                            //F2 = _ln10;
                            BMAX += 32;
                            F2 /= F1;
                            _ln10oln2 = make_store_float(F2);
                            storeCONSTANT(LN_10_OVER_2);
                            BMAX -= 32;
                            break;

        case EXP_1:         //cout << "calculating e " << flush;
                            disp.write("calculating e\n");
                            BMAX += 32; // increased precision
                            F1 = 1;
                            iterations = F1.taylor_agm_e(true);//F1.eToThex(true);
                            //iterations = F1.newton_e();
                            //cout << "<iterations needed: " <<F1.eToThex(true) << ">\n" << flush;
                            oStr = "<iterations needed: " + to_string(iterations) + ">\n";
                            oStr += F1.print() + "\n";
                            disp.write(oStr);
                            _exp1 = make_store_float(F1);
                            storeCONSTANT(EXP_1);
                            BMAX -= 32;
                            break;

        case P_I:           //cout << "calculating pi " << flush;
                            disp.write("calculating pi\n");
                            BMAX += 32; // increased precision
                            F1.gauss_legendre_pi();
                            //F1 = 5;
                            //F1 = inverse_m(F1);
                            //disp.write("1/5 is " + F1.print());
                            //iterations = F1.arctan(true);
                            //cout << "arctan 1/5 needed " << F1.arctan(true) << " iterations. " << flush;
                            //oStr = "arctan 1/5 needed " + to_string(iterations) + " iterations.\n";
                            //oStr += F1.print() + "\n";
                            //disp.write(oStr);
                            //disp.write("arctan 1/5 needed " + to_string(iterations) + " iterations.\n");
                            //F1.exponent += 4;
                            //F2 = 239;
                            //F2 = inverse_m(F2);
                            //disp.write("1/239 is " + F2.print());
                            //cout << "& arctan 1/239 needed " << F2.arctan(true) << "iterations.\n" << flush;
                            //iterations = F2.arctan(true);
                            //oStr = "arctan 1/239 needed " + to_string(iterations) + " iterations.\n";
                            //oStr += F2.print() + "\n";
                            //disp.write(oStr);

                            //disp.write("& arctan 1/239 needed " + to_string(iterations) + " iterations.\n\n");
                            //F2.exponent += 2;
                            //F1 -= F2;
                            disp.write("pi is " + F1.print());
                            _pi = make_store_float(F1);
                            storeCONSTANT(P_I);
                            BMAX -= 32;
                            break;

    }

}


void mfloat::storeCONSTANT(const CONSTANTS & c)
{ // stores indicated store_float into ./constants/{fn}
  // windows port may require .\\constants\\{fn}

    store_float * x = getCONSTANT(c);
	ofstream cOUT;
    string fDir = "./constants", fPath = fDir + '/' + (string)_constants[c];
    struct stat f_s;
    int dirExist = stat(fDir.c_str(), &f_s);
    if (dirExist != 0)
    { // directory does not exist:
        mode_t m = S_IRWXU;
        int m_d = 0;
        #ifdef _CROSS_COMPILE
        m_d = mkdir(fDir.c_str());
        #else
        m_d = mkdir(fDir.c_str(), m);
        #endif
        if (m_d < 0)
        {
            //cout << "Cannot make directory " << fDir << " or file " << _constants[c] << " (this can make things very slow)\n";
            disp.write("Cannot make directory " + fDir + " or file " + _constants[c] + " (this can make things very slow)\n\n");
            return;
        }
    }
    cOUT.open(fPath, ofstream::out | ofstream::trunc | ofstream::binary);
    cOUT.write((const char *)&x->FLAGS, sizeof(unsigned char));
    cOUT.write((const char *)&x->EXPONENT, sizeof(int));
    unsigned int bCount = x->BIT_COUNT, 
        byteCount = bCount / 8 + ((bCount % 8) == 0? 0: 1);
    cOUT.write((const char *)&bCount, sizeof(unsigned int));
    unsigned char * p = x->SIG;
    if (p != NULL) --p;
    for (unsigned int i = 0; i < byteCount; ++i) cOUT.write((const char *)(++p), sizeof(unsigned char));
    cOUT.close();
                
}
 


store_float * mfloat::getCONSTANT(const CONSTANTS & c)
{ 
    switch(c)
    {
        case LN_2:          return &_ln2;
        case LN_5:          return &_ln5;
        case LN_10:         return &_ln10;
        case LN_2_OVER_10:  return &_ln2oln10;
        case LN_10_OVER_2:  return &_ln10oln2;
        case EXP_1:         return &_exp1;
        case P_I:           return &_pi;
    }
    assert (1 == 2);

}

mfloat mfloat::handleCONSTANT(const CONSTANTS & c)
{
    store_float * buff = getCONSTANT(c);
    if (buff->FLAGS > 0) 
    {
        if (buff->BIT_COUNT < BMAX) calculateCONSTANT(c);
    }
    else
    { // attempt to retrieve from file:
        string fPath = "./constants/" + (string)_constants[c];
        struct stat f_s;
        if (0 == stat(fPath.c_str(), &f_s))
        { // file exists:
            ifstream cIn;
            cIn.open(fPath, ifstream::in | ifstream::binary);
            char rBuff[10];
            assert ((sizeof(unsigned char) == 1) && (sizeof(int) == 4) && (sizeof(unsigned int) == 4));
            cIn.read(rBuff, 1);
            memcpy(&buff->FLAGS, rBuff, 1);
            cIn.read(rBuff, 4);
            memcpy(&buff->EXPONENT, rBuff, 4);
            cIn.read(rBuff, 4);
            memcpy(&buff->BIT_COUNT, rBuff, 4);
            if (buff->BIT_COUNT >= BMAX)
            { // appropriate size:
                unsigned int byteCount = (buff->BIT_COUNT / 8) + ((buff->BIT_COUNT % 8) > 0? 1: 0);
                unsigned char * p = new unsigned char[byteCount];
                char fChar = ' ';
                for (unsigned int i = 0; i < byteCount; ++i)
                {
                    cIn.read(&fChar, 1);
                    p[i] = (unsigned char)fChar;
                }
                buff->SIG = p;
                cIn.close();
            }
            else
            { // need more bytes:
                cIn.close();
                calculateCONSTANT(c);
            }
        }
        else calculateCONSTANT(c); // file does not exist
    }
    return *buff;   

}

store_float mfloat::make_store_float(const mfloat & f, const bool & isConstant)
{
    mfloat tmp(f);
    double fd = static_cast<double>(tmp);
    store_float r;
    unsigned char oChar = f.pos? 0x80: 0 | f.zero? 0x40: 0 | f.nan? 0x20: 0 | f.inf? 0x10: 0 | f.sub? 0x8: 0;
    r.FLAGS = oChar;
    r.EXPONENT = f.exponent;
    unsigned int bCount = (unsigned int)f.sig.size(),
        cCount = (8 * bCount) - getRightZeros(f.sig);
    r.BIT_COUNT = isConstant? max(BMAX, cCount): min(BMAX, cCount);
    unsigned char * p = new unsigned char[bCount];
    r.SIG = p;
    for (unsigned int i = 0; i < bCount; ++i)
    {
        oChar = f.sig.at(i);
        *p = oChar;
        ++p;
    }

    return r;

}

int mfloat::sine(void)
{
    int count = 0;

    getFirstRotation();
    mfloat two(2.0f), three(3.0f),
        denom1(two), denom2(three),
        term(*this), x2(sqr(term)), acc(term);
    
    if (inf || sub || nan || zero) return count;
    
    disp.progress_text("sin(x)");

    term.pos = !(term.pos);
    while ((1 + BMAX + term.exponent) > 0)
    {
        ++count;
        term *= x2;
        term /= denom1;
        term /= denom2;
        acc += term;
        denom1 += two;
        denom2 += two;
        term.pos = !(term.pos);
        disp.progress(static_cast<double>(-term.exponent) / static_cast<double>(BMAX + 1));
    }
    *this = acc;
    disp.progress_text("");
    return count;

}

int mfloat::cosine(void)
{
    int count = 0;

    getFirstRotation();
    mfloat zer(0.0f), one(1.0f), two(2.0f),
        denom1(one), denom2(two),
        x2(sqr(*this)), term(one), acc(one);
    
    if (zero) 
    {
        *this = one;
        return count;
    }
    if (inf || sub || nan) return count;

    disp.progress_text("cos(x)");

    ++count;
    term.pos = false;
    while ((1 + BMAX + term.exponent) > 0)
    {
        ++count;
        
        term *= x2;
        term /= denom1;
        term /= denom2;
        acc += term;
        denom1 += two;
        denom2 += two;
        term.pos = !(term.pos);
        disp.progress(static_cast<double>(-term.exponent) / static_cast<double>(BMAX + 1));

    }

    *this = acc;
    disp.progress_text("");
    return count;

}

int mfloat::tangent(void)
{
    int count = 0;
    if (inf || sub || nan) return count;
    count = sine();
    mfloat cos(1.0f), pio2(handleCONSTANT(P_I));
    --pio2.exponent;
    cos -= sqr(*this);
    cos.square_root();
    if (cos.zero)
    {
        pio2.pos = pos;
        *this = pio2;
    }
    else *this /= cos;


    return count;
}

bool mfloat::unset_final(double & dIn)
{
    union {
        double ud;
        unsigned char uc[8];
    } d_u;
    d_u.ud = dIn;
    if (!LittleEndianSys)
    {
        unsigned char buff[8];
        memcpy (buff, d_u.uc, 8);
        for (unsigned char i = 0; i < 8; ++i)
        {
            d_u.uc[i] = buff[7 - i];
        }
    }
    unsigned char flt = 0x80, f = 0, bit = 0;
    bool found_final = false;
    int id8 = 0, dIdx = 0;
    for (int i = 0; i < 53; ++i)
    {
        id8 = i / 8;
        dIdx = 7 - id8;
        if (found_final) break;
        for (unsigned char j = 8; j > 0; --j)
        {
            f = flt >> (j - 1);
            bit = (d_u.uc[dIdx] & f) >> (8 - j);
            if (bit == 1)
            {
                d_u.uc[dIdx] ^= f;
                found_final = true;
                break;
            }
        }
    }
    return found_final;

}

void mfloat::reset_DROUND(const int & nwD)
{ // resets DROUND, DMAX, BROUND & BMAX

    if (nwD < 100) return;
    if (nwD == DROUND) return;
    int dround = nwD, dmax = dround + 10;

    mfloat cf(handleCONSTANT(LN_10_OVER_2)), blog_factor(handleCONSTANT(LN_2));
    cf *= dmax;
    bool o_f = false;
    int bround = cf.getIntAndReal(o_f), bm8 = bround % 8;    
    if (o_f) return;
    if (bm8 != 0) bround += 8 - bm8;
    mfloat blog(bround);
    blog.eLog("getting corresponding significant bits");
    blog /= blog_factor;

    // getting bmax to be at least log(bround) above bround for 
    // agm calculation accuracy
    int bmax = blog.getIntAndReal(o_f);
    if (o_f) return;

    LOG_BROUND = bmax;
    if (!blog.zero) ++LOG_BROUND;

    bm8 = bmax % 8;
    if (bm8 != 0) bmax += 8 - bm8;
    bmax += bround;

    DROUND = dround;
    DMAX = dmax;
    BROUND = bround;
    BMAX = bmax;

    int count = sizeof(_constants) / sizeof(_constants[0]);
    disp.progress_text("resetting constants");
    for (int i = 0; i < count; ++i)
    { // this will recalculate the constants if needed:
        mfloat buff = handleCONSTANT((CONSTANTS)i);
    }
    disp.progress_text("");
    bool pBl = SaveSigFigs();
}

void mfloat::pi_me(void)
{
    mfloat r(handleCONSTANT(P_I));

    *this = r;
    //gauss_legendre_pi();

}

void mfloat::factorial(void)
{
    if (nan || inf || sub || (!pos)) return;
    double fCk1 = static_cast<double>(*this);
    disp.progress_text("factorial");
    mint mTop = this->operator mint() /*static_cast<mint>(*this)*/, m(1);
    double denom = static_cast<double>(mTop);
    for (mint i = 2; i <= mTop; ++i)
    {
        m *= i;
        disp.progress(static_cast<double>(i) / denom);        
    }
    disp.progress_text("");
    *this = m;

}

void mfloat::base_raised_to_the_x(const unsigned int & base)
{
    mfloat ln_b(static_cast<int>(base));
    // get ln(base):
    BMAX += 32;
    switch (base)
    {
        case 2:
            ln_b = handleCONSTANT(LN_2);
            break;
        case 5:
            ln_b = handleCONSTANT(LN_5);
            break;
        case 10:
            ln_b = handleCONSTANT(LN_10);
            break;
        default:
            ln_b.eLog();
            break;

    }

    *this *= ln_b;
    BMAX -= 32;
    RoundMe();
    //mfloat buff = *this;
    //eToThex();
    //halley_e();
    //householder3_e();
    //householder4_e();
    //*this = buff;
    //householder5_e();
    //*this = buff;
    //householder6_e();
    //*this = buff;
    //householder7_e();
    //*this = buff;
    //householder8_e();
    //newton_e();
    taylor_agm_e();
}

void mfloat::non_natural_log(const unsigned int & base)
{
    mfloat ln_b(static_cast<int>(base));
    // get ln(base):
    switch (base)
    {
        case 2:
            ln_b = handleCONSTANT(LN_2);
            break;
        case 5:
            ln_b = handleCONSTANT(LN_5);
            break;
        case 10:
            ln_b = handleCONSTANT(LN_10);
            break;
        default:
            ln_b.eLog();
            break;

    }

    eLog();
    *this /= ln_b;

}

mfloat mfloat::split_off(const int & a)
{
    mfloat r;
    vector<unsigned char> rsig;
    bool firstSetBitFound = false;
    int delta = 0, iCharIdx = -1, id8 = 0,
        sSz = static_cast<int>(sig.size()),
        start_at = exponent - a, j = 0;
    unsigned char iChar = 0, oChar = 0,
        flt0 = 0x80, iflt = 0, oflt = 0,
        bit = 0, im8 = 0, om8 = 0;

    for (int i = start_at; i < exponent; ++i)
    {
        id8 = i / 8;
        im8 = i % 8;
        if (iCharIdx != id8)
        {
            if ((iCharIdx > -1) && (iCharIdx < sSz)) sig[iCharIdx] = iChar;
            iCharIdx = id8;
            iChar = iCharIdx < sSz? sig.at(iCharIdx): 0;
        }
        iflt = flt0 >> im8;
        bit = (iChar & iflt) >> (7 - im8);
        bool bitIsOne = (bit == 1);
        if (bitIsOne) iChar ^= iflt;  // zeroing bit in iChar
        j = i - start_at - delta;
        if (firstSetBitFound)
        {
            om8 = j % 8;
            oflt = flt0 >> om8;
            if (bitIsOne) oChar |= oflt;
            if (om8 == 7) 
            {
                rsig.push_back(oChar);
                oChar = 0;
            }
        }
        else
        {
            ++delta;
            firstSetBitFound = bitIsOne;
        }
    }
    if ((iCharIdx > -1) && (iCharIdx < sSz)) sig[iCharIdx] = iChar;
    if (oChar > 0) rsig.push_back(oChar);
    while ((rsig.size() > 0) && (0 == rsig.at(rsig.size() - 1))) rsig.pop_back();
    if (firstSetBitFound) 
    {
        r.zero = false;
        if (rsig.size() > 0) r.sig = rsig;
        r.exponent = a - delta;
    }
    while((sig.size() > 0) && (0 == sig.at(sig.size() -1))) sig.pop_back();
    exponent -= a;
    return r;
}
    
int mfloat::getBitCount(void)
{
    int sZ = static_cast<int>(sig.size()), RZ = getRightZeros(sig);
    return 8 * sZ - RZ;
}


mfloat mfloat::karatsuba(const mfloat & a, const mfloat & b)
{ // faster multiplication?:
    if ((a.zero) || (b.zero)) return 0;
/*
    if (a.sig.size() == 0) 
    {
        b.exponent += a.exponent;
        return b;
    }
    if (b.sig.size() == 0) 
    {
        a.exponent += b.exponent;
        return a;
    }
*/
    mfloat hiA(a), hiB(b);
    int aBC = hiA.getBitCount(), bBC = hiB.getBitCount();
    // integer check:
    assert ((a.exponent >= aBC) && (b.exponent >= bBC));
    // increment bitcounts to include the initial one bit:
    ++aBC;
    ++bBC;
    int m = min(aBC, bBC), m2 = m / 2; // our reduction factors
    if (m < 10) 
    { // main exit condition:
        mfloat r(a);
        r.multiply(b);
        return r;
    }
    mfloat loA(hiA.split_off(m2)), loB(hiB.split_off(m2));

    mfloat  z0 = karatsuba(loA, loB), a1(loA), a2(loB);
    a1 += hiA;
    a2 += hiB;
    mfloat  z1 = karatsuba(a1, a2), 
            z2 = karatsuba(hiA, hiB),
            z3 = z1 - z2 - z0;

    z2.exponent += m2 * 2;
    z3.exponent += m2;
    return z2 + z3 + z0;
}

void mfloat::multiply(const mfloat & b)
{
/*
    if (nan) return;
    if (inf) return;
    if (sub) return;
    if ((zero) || (b.zero)) 
    {
        zero = true;
        sig.clear();
        pos = true;
        exponent = 0;
        return;
    }
    if (exponent_cmp(exponent, b.exponent) == 1)
    {
        inf = exponent > 0;
        sub = exponent < 0;
        exponent = 0;
        sig.clear();
        return;
    }
    pos = pos == b.pos;
*/
    exponent += b.exponent; // re-adjust as needed at the end of the calculation sig will be in [1, 4)
    int tSz = static_cast<int>(sig.size()), bSz = static_cast<int>(b.sig.size()), cSz = bSz,
        tBitCount = 8 * tSz - getRightZeros(sig), bBitCount = 8 * bSz - getRightZeros(b.sig), cBitCount = bBitCount,
        tCharIdx = -1, bCharIdx = -1, cCharIdx = -1, 
        id8 = 0, jd8 = 0, k = 0, kd8 = 0, km8 = 0, ext = 0,
        bytesNeeded = 0, delta = 0;
    unsigned char tChar = 0, bChar = 0, 
        cChar = 0, carry = 0, 
        tbit = 0, bbit = 0, cbit = 0, obit = 0, flt = 0X80, f = 0,
        im8 = 0, jm8 = 0, cm1Char = 1;
    vector<unsigned char> acc = b.sig;

    for (int i = 0; i < tBitCount; ++i)
    {
        id8 = i / 8;
        im8 = i % 8;
        if (id8 != tCharIdx)
        {
            tCharIdx = id8;
            tChar = sig.at(tCharIdx);
        }
        tbit = (tChar & (flt >> im8)) >> (7 - im8);
        if (tbit == 1)
        {
            ext = min(i + 1 + bBitCount, BMAX - 1);
            if (ext > cBitCount)
            {
                bytesNeeded = ext / 8 + 1 - cSz;
                if (bytesNeeded > 0) acc.insert(acc.end(), static_cast<size_t>(bytesNeeded), 0);
                cSz += bytesNeeded;
                cBitCount = ext;
            }
            delta = i + 1; //ext - i - 1;
            bCharIdx = -1;
            cCharIdx = -1;
            carry = 0;
            for (int j = ext - 1; j >= 0; --j)
            {
                jd8 = j / 8;
                if (jd8 != cCharIdx)
                {
                    cCharIdx = jd8;
                    cChar = acc.at(cCharIdx);
                }
                jm8 = j % 8;
                f = flt >> jm8;
                cbit = (cChar & f) >> (7 - jm8);
                k = j - delta;
                kd8 = k / 8;
                if ((kd8 != bCharIdx) && (k >= 0))
                {
                    bCharIdx = kd8;
                    bChar = b.sig.at(bCharIdx);
                }
                km8 = k % 8;
                bbit = k == -1? 1: k < -1? 0: (bChar & (flt >> km8)) >> (7 - km8);
                obit = carry ^ cbit ^ bbit;
                if (obit != cbit) cChar ^= f; // this will change cChar at bit f
                carry = carry == 0? cbit & bbit: cbit | bbit;
                if ((carry == 0) && (j < i))
                {
                    acc[cCharIdx] = cChar;
                    break;
                }
                if (jm8 == 0) acc[cCharIdx] = cChar;
            }
            if (carry == 1)
            {
                ++cm1Char;
                assert(cm1Char < 4);
            }
        }
    }
    if (cm1Char > 1) 
    {
        if (exponent_cmp(exponent, 1) == 1)
        {
            inf = true;
            exponent = 0;
            sig.clear();
            return;
        }
        ++exponent;
        acc.insert(acc.begin(), cm1Char);
        standardize_v(acc);
    }
    else
    {
        while ((acc.size() > 0) && (acc.at(acc.size() - 1) == 0)) acc.pop_back();
    }
    
    sig = acc;
    //return *this;

}
    
void mfloat::divide(const mfloat & b)
{

}    

int mfloat::newton_inverse_m(void)
{ // slower than one / x
    int count = 0;
    if (zero)
    {
        zero = false;
        inf = true;
    }
    if (nan || inf || sub) return -1;
    double x0_DBL = 1.0 / static_cast<double>(*this),
        fraction = 0.0,
        bMax = static_cast<double>(BMAX);

    BMAX += 8;

    mfloat a(*this), x(x0_DBL), one(1.0),
        epsilon(one), ax(one);

    disp.progress_text("⅟ₓ via Newton's Method");
    while (!(epsilon.zero) && ((epsilon.exponent + BMAX) > 8))
    {
        ++count;
        ax = a * x;
        //ax *= x;
        epsilon = ax - one;
        //epsilon -= ax;
        x *= one - epsilon;
        //f_x = ax;
        //f_x -= one;
        fraction = -epsilon.exponent / bMax;
        disp.progress(fraction);
    }
    BMAX -= 8;
    disp.progress(1.0);
    disp.progress_text("");
    *this = x;
    return count;
}

int mfloat::newton_sqrt(void)
{
    int count = 0;
    if (zero)
    {
        zero = false;
        inf = true;
    }
    if (nan || inf || sub) return -1;
    double x0_DBL = 1.0 / sqrt(static_cast<double>(*this)),
        fraction = 0.0,
        bMax = static_cast<double>(BMAX);

    BMAX += 8;
    mfloat a(*this), x(x0_DBL), x2 = sqr(x), 
        one(1.0), two(2.0), three(3.0), four(4.0),
        one_half(one), three_fourths(three), 
        ax2 = a * x2, q(one), 
        epsilon = ax2 - one, epsilon2(one);

    --one_half.exponent; 
    three_fourths.exponent -= 2;
    disp.progress_text("sqrt via Newton's Method");
    while (!(epsilon.zero) && ((epsilon.exponent + BMAX) > 8))
    {
        ++count;
        epsilon = ax2 - one;
        epsilon2 = sqr(epsilon);
        //q = one - epsilon * (two - three * epsilon) / four;
        q = one - one_half * (epsilon - three_fourths * epsilon2);
        x *= q;
        x2 = sqr(x);
        ax2 = a * x2;
        fraction = -epsilon.exponent / bMax;
        disp.progress(fraction);
    }
    BMAX -= 8;
    disp.progress(1.0);
    disp.progress_text("");
    *this = a * x;
    return count;

}

void mfloat::gauss_legendre_pi(void)
{
    BMAX += 8;
    mfloat A(1.0), B(2.0), T(A), X(A), Y(A), D(A);
    B.square_root();
    B = inverse_m(B);
    T.exponent -= 2;
    disp.progress_text("Gauss-Legendre pi");
    double fraction = 0.0, bMax = static_cast<double>(BMAX);
    while (1 + D.exponent + BMAX > 8)
    {
        Y = A;
        A += B;
        --A.exponent;
        B *= Y;
        B.square_root();
        T -= X * sqr(A - Y);
        ++X.exponent;
        D = A - B;
        fraction = -D.exponent / bMax;
        disp.progress(fraction);
    }
    disp.progress_text("");
    disp.progress(1.0);
    BMAX -=8;
    *this = sqr(A + B) / T;
    exponent -= 2;
}

int mfloat::householder3_e(void)
{
    int count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));// / 2.0;
    //bool unsetted = unset_final(y0);
    //assert (unsetted);
    BMAX += 32;
    mfloat x(*this), y(y0), one(1), two(2), //y_prev(y0),
        three(3), four(4), six(6),
        LOG(one),  f_y(one), f_y2(one), q(one);
    int e_prev = 0;
    // set up x0:
    //x.exponent = y.exponent;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y.exponent + BMAX) > 32)
    {
        e_prev = f_y.exponent;
        LOG = y;
        agmcount += LOG.eLog("e^x via Householder-3 Method n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        f_y = LOG - x;
        f_y2 = sqr(f_y);
        q = one - (six * f_y + three * f_y2) / (six + six * f_y + two * f_y2);
        y *= q;
        //LOG -= x;
        //f_y = LOG;
        //--LOG.exponent; // divide by 2
        //LOG = one - LOG;
        //y_prev = y;
        //xd1 = static_cast<double>(y_prev);
        //y *= (one - f_y / LOG);
        //xd2 = static_cast<double>(y);
        //e_prev = delta.exponent;
        //delta = y - y_prev;
        //LOG = y;
        
        //if ((delta.zero) || (delta.exponent == e_prev)) 
        if ((f_y.zero) || (f_y.exponent >= e_prev))
        {
            break;
        }
        //cout << count << ") Householder-3 so far: " << f_y.exponent << "\n";
    }
    BMAX -= 32;
    *this = y;
    disp.progress_text("");
    return count;

}

int mfloat::householder4_e(const bool & ReCalc)
{
    int count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));// / 2.0;
    //bool unsetted = unset_final(y0);
    //assert (unsetted);
    mfloat x(*this), y(y0), one(1), three(3), //y_prev(y0),
        four(4), eleven(11), twelve(12), eighteen(18),
        LOG(one),  f_y(one), f_y2(one), f_y3(one), q(one),
        e(2.718281828);
    
    if (!ReCalc) 
    {
        e = handleCONSTANT(EXP_1);
        if (x.IsEq(one))
        {
            *this = e;
            return count;
        } 
    }
    BMAX += 64;
    int e_prev = 0;
    // set up x0:
    //x.exponent = y.exponent;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y.exponent + BMAX) > 64)
    {
        e_prev = f_y.exponent;
        LOG = y;
        agmcount += LOG.eLog("e^x via Householder-4 Method n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        f_y = LOG - x;
        f_y2 = sqr(f_y);
        f_y3 = f_y * f_y2;
        q = one - (twelve * f_y2 + twelve * f_y + four * f_y3) /
            (twelve + eighteen * f_y + eleven * f_y2 + three * f_y3);
        y *= q;
        //LOG -= x;
        //f_y = LOG;
        //--LOG.exponent; // divide by 2
        //LOG = one - LOG;
        //y_prev = y;
        //xd1 = static_cast<double>(y_prev);
        //y *= (one - f_y / LOG);
        //xd2 = static_cast<double>(y);
        //e_prev = delta.exponent;
        //delta = y - y_prev;
        //LOG = y;
        
        //if ((delta.zero) || (delta.exponent == e_prev)) 
        if ((f_y.zero) || (f_y.exponent >= e_prev))
        {
            break;
        }
        cout << count << ") Householder-4 so far: " << f_y.exponent << "\n";
    }
    BMAX -= 64;
    *this = y;
    disp.progress_text("");
    return count;

}

int mfloat::householder5_e(void)
{
    int count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));
    BMAX += 64;
    mfloat x(*this), y(y0), one(1), three(3), five(5),
        ten(10), eleven(11), twelve(12), twelve_fifths = twelve / five,
        eighteen(18), twenty_one(21), twenty_four(24),
        LOG(one),  f_y(one), f_y2(one), f_y3(one), f_y4(one), q(one);
    int e_prev = 0;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y.exponent + BMAX) > 64)
    {
        e_prev = f_y.exponent;
        LOG = y;
        agmcount += LOG.eLog("e^x via Householder-5 Method n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        f_y = LOG - x;
        f_y2 = sqr(f_y);
        f_y3 = f_y * f_y2;
        f_y4 = sqr(f_y2);
        q = one - (twelve * f_y + eighteen * f_y2 + eleven * f_y3 + three * f_y4) /
            (twelve + twenty_four * f_y + twenty_one * f_y2 + ten * f_y3 + twelve_fifths * f_y4);
        y *= q;
        //xd2 = static_cast<double>(y);
        if ((f_y.zero) || (f_y.exponent >= e_prev))
        {
            break;
        }
        cout << count << ") Householder-5 so far: " << f_y.exponent << "\n";
    }
    BMAX -= 64;
    *this = y;
    disp.progress_text("");
    return count;

}

void mfloat::natural_log_2(void)
{
    mfloat one(1), a(one), g(one), two(2), 
        pi(handleCONSTANT(P_I)),
        bMax(BMAX);
    g.exponent = 2 - BMAX;
    a.agm(g, "natural log 2");
    *this = pi / (two * a * bMax);
    disp.progress_text("");
}

int mfloat::householder6_e(void)
{
    int count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));
    BMAX += 64;
    mfloat x(*this), y(y0), deg(6), one(1), zer(0), 
        num(zer), num_ints[] = {zer, -120, -240, -210, -100, -24},
        den(zer), den_ints[] = {720, 1800, 2040, 1350, 548, 120},
        f_y[] ={one, one, one, one, one, one},
        LOG(one);
    int e_prev = 0;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y[1].exponent + BMAX) > 64)
    {
        e_prev = f_y[1].exponent;
        LOG = y;
        agmcount += LOG.eLog("e^x via Householder-6 Method n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        f_y[1] = LOG - x;
        for (int i = 2; i < 6; ++i)
        {
            f_y[i] = f_y[i - 1] * f_y[1];
        }
        num = zer;
        for (int i = 0; i < 6; ++i) 
        {
            num += num_ints[i] * f_y[i];
            //xd0 = static_cast<double>(num_ints[i]);
            //cout << i << ") numerator integer = " << xd0 << "\n"; 
        }
        den = zer;
        for (int i = 0; i < 6; ++i) den += den_ints[i] * f_y[i];
        y *= (one + deg * num / den);
        //xd2 = static_cast<double>(y);
        if ((f_y[1].zero) || (f_y[1].exponent >= e_prev))
        {
            break;
        }
        cout << count << ") Householder-6 so far: " << f_y[1].exponent << "\n";
    }
    BMAX -= 64;
    *this = y;
    disp.progress_text("");
    return count;


}

int mfloat::householder7_e(void)
{
    int degree = 7, count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));
    BMAX += 64;
    mfloat x(*this), y(y0), deg(degree), one(1), zer(0), 
        num(zer), num_ints[] = {zer, 720, 1800, 2040, 1350, 548, 120},
        den(zer), den_ints[] = {-5040, -15120, -21000, -17640, -9744, -3528, -720},
        f_y[degree], LOG(one);
    for (int i = 0; i < degree; ++i) f_y[i] = one;
    int e_prev = 0;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y[1].exponent + BMAX) > 64)
    {
        e_prev = f_y[1].exponent;
        LOG = y;
        agmcount += LOG.eLog("e^x via Householder-7 Method n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        f_y[1] = LOG - x;
        num = zer;
        den = zer;
        for (int i = 0; i < degree; ++i) 
        {
            if (i > 1) f_y[i] = f_y[i - 1] * f_y[1];
            num += num_ints[i] * f_y[i];
            den += den_ints[i] * f_y[i];
            //xd0 = static_cast<double>(num_ints[i]);
            //cout << i << ") numerator integer = " << xd0 << "\n"; 
        }
        y *= (one + deg * num / den);
        //xd2 = static_cast<double>(y);
        if ((f_y[1].zero) || (f_y[1].exponent >= e_prev))
        {
            break;
        }
        cout << count << ") Householder-7 so far: " << f_y[1].exponent << "\n";
    }
    BMAX -= 64;
    *this = y;
    disp.progress_text("");
    return count;

}

int mfloat::householder8_e(const bool & ReCalc)
{
    int degree = 8, count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));
    mfloat x(*this), y(y0), deg(degree), one(1), zer(0), 
        num(zer), num_ints[] = {zer, -5040, -15120, -21000, -17640, -9744, -3528, -720},
        den(zer), den_ints[] = {40320, 141120, 231840, 235200, 162456, 78792, 26136, 5040},
        f_y[degree], LOG(one), e(2.718281828);
    
    if (!ReCalc) 
    {
        e = handleCONSTANT(EXP_1);
        if (x.IsEq(one))
        {
            *this = e;
            return count;
        } 
    }
    BMAX += 64;

    for (int i = 0; i < degree; ++i) f_y[i] = one;
    int e_prev = 0;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y[1].exponent + BMAX) > 64)
    {
        e_prev = f_y[1].exponent;
        LOG = y;
        agmcount += LOG.eLog("ℯ˟ via 8° householder n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        f_y[1] = LOG - x;
        num = zer;
        den = zer;
        for (int i = 0; i < degree; ++i) 
        {
            if (i > 1) f_y[i] = f_y[i - 1] * f_y[1];
            num += num_ints[i] * f_y[i];
            den += den_ints[i] * f_y[i];
            //xd0 = static_cast<double>(num_ints[i]);
            //cout << i << ") numerator integer = " << xd0 << "\n"; 
        }
        y *= (one + deg * num / den);
        //xd2 = static_cast<double>(y);
        if ((f_y[1].zero) || (f_y[1].exponent >= e_prev))
        {
            break;
        }
        //cout << count << ") Householder-8 so far: " << f_y[1].exponent << "\n";
    }
    BMAX -= 64;
    *this = y;
    disp.progress_text("");
    return count;

}


int mfloat::taylor_agm_e(const bool & ReCalc)
{
    int count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));
    mfloat x(*this), y(y0), one(1), zer(0), fact(one),
        f_y, LOG(y), sum(one), term(one), e(2.718281828);

    //cout << "e^x as double " << y0 << "\n";

    if (!ReCalc) 
    {
        e = handleCONSTANT(EXP_1);
        if (x.IsEq(one))
        {
            *this = e;

            return count;
        } 
        if (isInt())
        {
            e.power(this->operator int());
            *this = e;
            return count;
        }
    }

    agmcount = LOG.eLog("Step 1: ℯ˟ from ln(x)");
    f_y = x - LOG;
    //zer += f_y;
    BMAX += 64;

    //for (int i = 0; i < degree; ++i) f_y[i] = one;
    int e_prev = 0;
    double fraction = 0.0, bMax = static_cast<double>(BMAX), xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    disp.progress_text("Step 2: ℯ˟ via taylor");
    while ((y.exponent + 2 + term.exponent + BMAX) > 64)
    {
        ++count;
        e_prev = term.exponent;
        term *= f_y / fact;
        sum += term;
        fact += one;
        fraction = -(y.exponent + term.exponent) / bMax;
        disp.progress(fraction);
        if (term.exponent >= e_prev) break;
    }
    //cout << count << ") taylor/agm so far: " << f_y[1].exponent << "\n";
    y *= sum;
    BMAX -= 64;
    *this = y;
    disp.progress_text("");
    disp.progress(0.0);
    return count;

}

/*
int mfloat::taylor_agm_e(const bool & ReCalc)
{
    int degree = 21, count = 0, agmcount = 0;
    if ((nan) || (inf) || (sub)) return 0;

    double y0 = exp(static_cast<double>(*this));
    mfloat x(*this), y(y0), one(1), zer(0), 
        denom[] = {string("1"), string("1"), string("2"), string("6"), string("24"), 
                    string("120"), string("720"), string("5040"), string("40320"), string("362880"), string("3628800"),
                    string("3.99168E7"), string("4.790016E8"), string("6.2270208E9"),
                    string("8.71782912E10"), string("1.307674368E12"), string("2.0922789888E13"),
                    string("3.55687428096E14"), string("6.402373705728E15"), 
                    string("1.21645100408832E17"), string("2.43290200817664E18")},
        f_y[degree], LOG(one), sum(zer), e(2.718281828);

    if (!ReCalc) 
    {
        e = handleCONSTANT(EXP_1);
        if (x.IsEq(one))
        {
            *this = e;

            return count;
        } 
        if (isInt())
        {
            e.power(this->operator int());
            *this = e;
            return count;
        }
    }

    BMAX += 64;

    for (int i = 0; i < degree; ++i) f_y[i] = one;
    int e_prev = 0;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0;
    while ((f_y[1].exponent + BMAX) > 64)
    {
        e_prev = f_y[1].exponent;
        if (count > 0)
        {
            sum = zer;
            for (int i = 0; i < degree; ++i)
            {
                if (i > 1) f_y[i] = f_y[i - 1] * f_y[1];
                sum += f_y[i] / denom[i];
            }
            y *= sum;
        }
        LOG = y;
        agmcount += LOG.eLog("ℯ˟ via taylor/agm n=" + to_string(++count));
        //xd0 = static_cast<double>(LOG);
        f_y[1] = x - LOG;
        if ((f_y[1].zero) || (f_y[1].exponent >= e_prev))
        {
            break;
        }
        //cout << count << ") taylor/agm so far: " << f_y[1].exponent << "\n";
    }
    BMAX -= 64;
    *this = y;
    disp.progress_text("");
    return count;

}
*/


void mfloat::getFirstRotation(void)
{ // this is an angle in radians
  // this function puts it in (-pi, pi]

    mfloat pi2(handleCONSTANT(P_I)), theta(*this), NFact(1);
    ++pi2.exponent; // times two
    --NFact.exponent; // divided by two
    NFact -= theta / pi2;
    bool o_f = false;
    int N = NFact.getIntAndReal(o_f);
    assert (!o_f);
    theta += mfloat(N) * pi2;

}


mcomplex::mcomplex(void)
{
    RE = 0;
    IM = 0;
}
    
mcomplex::mcomplex(const mcomplex & a)
{
    RE = a.RE;
    IM = a.IM;
}

mcomplex::mcomplex(const mfloat & theta)
{ 
    // to do: replace these w/ agm implementation
    //RE = cos(theta);
    //IM = sin(theta);
    RE = 0;
    IM = theta;
    taylor_agm_e();
}   

mcomplex::mcomplex(const mfloat & a, const mfloat & b)
{
    RE = a;
    IM = b;
}
    
mcomplex::~mcomplex(void)
{

}

mcomplex & mcomplex::operator=(const mcomplex & b)
{
    RE = b.RE;
    IM = b.IM;
    return *this;
}
    
mcomplex & mcomplex::operator+=(const mcomplex & b)
{
    RE += b.RE;
    IM += b.IM;
    return *this;
}
    
mcomplex & mcomplex::operator-=(const mcomplex & b)
{
    RE -= b.RE;
    IM -= b.IM;
    return *this;
}

mcomplex & mcomplex::operator*=(const mfloat & c)
{
    RE *= c;
    IM *= c;
    return *this;
}  

mcomplex & mcomplex::operator*=(const mcomplex & b)
{
    mfloat reTmp = RE * b.RE,
        imTmp = IM * b.IM,
        tTmp = RE + IM,
        bTmp = b.RE + b.IM;
    
    RE = reTmp - imTmp;
    IM = tTmp * bTmp - (reTmp + imTmp);
    return *this;
}

mcomplex & mcomplex::operator/=(const mfloat & c)
{
    RE /= c;
    IM /= c;
    return *this;
}   

mcomplex & mcomplex::operator/=(const mcomplex & b)
{
    mcomplex conj(b);
    conj.IM = inverse_a(conj.IM);
    *this *= conj;
    *this /= (sqr(b.RE) + sqr(b.IM));
    return *this;
}

mfloat mcomplex::getRealPart(void)
{
    return RE;
}

mfloat mcomplex::getImaginaryPart(void)
{
    return IM;
}


bool mcomplex::IsEq(const mcomplex & b) const
{

    return ((RE == b.RE) && (IM == b.IM));
}


mfloat mcomplex::getMagnitude(void)
{
    return sqrt(sqr(RE) + sqr(IM));
}

mfloat mcomplex::getMagnitudeAndNormalize(void)
{
    mfloat mag = getMagnitude();
    RE /= mag;
    IM /= mag;
    return mag;
}

void mcomplex::square_root(void)
{
    mfloat mag = sqrt(getMagnitudeAndNormalize()),
        one(1), two(2), 
        c2 = sqrt((RE + one) / two), 
        s2 = sqrt((one - RE) / two),
        zero(0);
    
    RE = c2;
    if (IM < zero) s2 = inverse_a(s2);
    IM = s2;

    *this *= mag;
    
}

int mcomplex::agm(const mcomplex & gIn, const string & dInfo) // arithmetic-geometric mean
{
    int count = 0;
    size_t dSz = dInfo.size();
    //if (PB != NULL) PB->set_text("arithmetic-geometric mean");
    if (dSz == 0) RE.disp.progress_text("ℂ arithmetic-geometric mean");
    else RE.disp.progress_text(dInfo + " using agm");
    mcomplex a(*this), g(gIn), delta = a - g, 
        aNxt(a), gNxt(g), *hi = NULL;

    mfloat two(2), zer(0), cross(zer), nan = two / zer;

    mcomplex badNum(nan, nan);

    char order = ' ';
    
    bool badNumber = false;

    if (!RE.isNumber() || !IM.isNumber() || !g.RE.isNumber() || !g.IM.isNumber()) 
    {
        *this = badNum;
        return count;
    }
    if (a.IsEq(g)) return 0;
    //sig.clear();
    //exponent = 0;
    //zero = true;
    //pos = true;
    //double ad = 0.0, gd = 0.0;
    double fraction = 0.0, bmax = static_cast<double>(RE.BROUND); 
    //    are = static_cast<double>(a.RE), 
    //    aim = static_cast<double>(a.IM),
    //    gre = static_cast<double>(g.RE), 
    //    gim = static_cast<double>(g.IM),
    //    bmax = static_cast<double>(RE.BROUND);
    int reExp = 0, imExp = 0;
        //aDbl = 0.0, gDbl = 0.0, dDbl = 0.0;
    mfloat::BMAX += 64;
    while ((((1 + delta.RE.getExponent() + RE.BROUND) > 0) && (delta.RE != zer)) ||
        (((1 + delta.IM.getExponent() + RE.BROUND) > 0) && (delta.IM != zer)))
    {
        //ad = static_cast<double>(a);
        //gd = static_cast<double>(g);
        if (((RE.BROUND + delta.RE.getExponent()) <= 0) || ((RE.BROUND + delta.IM.getExponent() <= 0)))
        {
            reExp = delta.RE.getExponent();
            imExp = delta.IM.getExponent();
        }
        badNumber =  !a.RE.isNumber() || !a.IM.isNumber() || !g.RE.isNumber() || !g.IM.isNumber();
        if (badNumber) break;
        ++count;
        aNxt = a;
        aNxt += g;
        //assert (aNxt.sig.size() <= 424);
        //aNxt /= two;
        //--aNxt.exponent;
        aNxt /= two;

        gNxt = a;
        gNxt.multiply_with_order(g, order);
        assert (order != 'n');
        if (order == 't') hi = &g;
        else hi = &a;

        //gNxt *= g;
        gNxt.square_root();
        cross = gNxt.cross(*hi);
        if (cross < zer)
        {
            gNxt.RE = inverse_a(gNxt.RE);
            gNxt.IM = inverse_a(gNxt.IM);
        }
        //assert (gNxt.sig.size() <= 424);
        a = aNxt;
        g = gNxt;
        delta = a;
        delta -= g;
        //if ((delta.RE == zer) || (delta.IM == zer)) break;
        //if (PB != NULL) 
        //{
        int rExp = delta.RE.getExponent(), iExp = delta.IM.getExponent();
        fraction = -(rExp + iExp) / (2.0 * bmax);

        //are = static_cast<double>(a.RE);
        //aim = static_cast<double>(a.IM);
        //gre = static_cast<double>(g.RE);
        //gim = static_cast<double>(g.IM);
        //cout << "delta RE" << rExp << " IM" << iExp << " a(" << are << ", " << aim << ") g(" << gre << ", " << gim << ")\n";
        //aDbl = static_cast<double>(a);
        //gDbl = static_cast<double>(g);
        //dDbl = static_cast<double>(delta);
        //if (fraction >= 1.0) fraction = 0.999999;
        //cout << dInfo << delta.exponent << " " << BMAX << " " << fraction << " " << aDbl << " " << gDbl << " " << dDbl << "\n";
        RE.disp.progress(fraction);
        //PB->set_fraction(fraction);
        //while (gtk_events_pending()) gtk_main_iteration();
        //PB->show_all();
        //}
        //change = delta;
        //change -= old_delta;
        //old_delta = delta;
        if ((delta.RE.getExponent() >= reExp) || (delta.IM.getExponent() >= imExp)) break;
    }
    mfloat::BMAX -= 64;
    *this = badNumber? badNum: g;
    if (dSz == 0) RE.disp.progress_text("");
    RE.disp.progress(1.0);
    return count;
}



int mcomplex::eLog(const string & dInfo) // natural log w/ agm
{
    int count = 0;
    //if ((zero) || !(pos))
    //{ // error -infinity
    //    pos = true;
    //    zero = true;
    //    exponent = 0;
    //    sig.clear();
    //    nan = true;
    //    inf = true;
    //}

    mfloat zero(0), one(1), two(2), acc_0(RE.handleCONSTANT(mfloat::P_I)), 
        LN2_0(RE.handleCONSTANT(mfloat::LN_2)),
        mag = getMagnitude(), nan = one / zero;

    mcomplex badNum(nan, nan);

    if (!RE.isNumber() || !IM.isNumber() || (mag == zero)) 
    {
        *this = badNum;
        return 0;
    }

    //if (IsEq(1)) 
    //{
    //    *this = 0;
    //    return 0;
    //}

    mcomplex x(*this), M(1, 0), s(x), delta = x - M, acc(acc_0, 0), 
        LN2(LN2_0, 0), four(4, 0);
    //if (delta.exponent + BROUND / LOG_BROUND < 0) return naturalLog_1();
    //bool invert = IsLT(1);
    //if (invert) x = inverse_m(x);
    int m = RE.BMAX / 2 - mag.getExponent() + 1;
    if (s.RE != zero) s.RE.getExponent() += m;
    if (s.IM != zero) s.IM.getExponent() += m;
    s = four / s;
    count = M.agm(s, dInfo.size() == 0? "ℂ ln(x)": dInfo);
    if (dInfo.size() == 0) RE.disp.progress_text("");
    bool goodNumber = M.RE.isNumber() && M.IM.isNumber();
    M *= two;
    acc /= M;
    LN2 *= m;
    acc -= LN2;
    *this = goodNumber? acc: badNum;

    return count;


}

int mcomplex::taylor_agm_e(void)
{ // this is x. barring errors it shall become e^x 
    int count = 0, agmcount = 0, reExp = 0, imExp = 0;
    if (!RE.isNumber() || !IM.isNumber()) return 0;
    
    mfloat R = exp(RE), zero(0), m_one(1), denom(m_one), nan = m_one / zero;
    
    IM.getFirstRotation();
    if (IM == zero)
    {
        RE = R;
        return count;
    }
    double theta0 = static_cast<double>(IM);
    //BMAX += 64;
    mcomplex x(0, IM), y(cos(theta0), sin(theta0)), one(1, 0), zer(0, 0), 
        t_y(one), term(one), LOG(one), sum(one), badNum(nan, nan);

    int & rExp = term.RE.getExponent(), & iExp = term.IM.getExponent();
    bool goodNumber = true, makingProgress = true;
    LOG = y;
    agmcount = LOG.eLog("Step 1: ℯ˟ from ln(x) in ℂ");
    LOG.IM.getFirstRotation();
    double fraction = 0.0,
        bRound = static_cast<double>(mfloat::BROUND),
        reLog = static_cast<double>(LOG.RE),
        imLog = static_cast<double>(LOG.IM);

    goodNumber = LOG.RE.isNumber() && LOG.IM.isNumber();
    if (goodNumber)
    {
        t_y = x -  LOG;
        RE.disp.progress_text("Step 2: ℯ˟ via taylor in ℂ");
        //f_y = LOG - x;
        //while ((((term.RE.getExponent() + RE.BROUND) > 0) && (term.RE != zero)) ||
        //    (((term.IM.getExponent() + RE.BROUND) > 0) && term.IM != zero))
        while ((((rExp + 2 + RE.BROUND) > 0) && (term.RE != zero)) ||
            (((iExp + 2 + RE.BROUND) > 0) && term.IM != zero))
        {
            ++count; // should equal sum index
            //if (((term.RE.getExponent() + RE.BROUND) <= 0) || ((term.IM.getExponent() + RE.BROUND) <= 0))
            if (((rExp + RE.BROUND) <= 0) || ((iExp + RE.BROUND) <= 0))
            {
                //reExp = term.RE.getExponent();
                //imExp = term.IM.getExponent();
                reExp = rExp;
                imExp = iExp;
            }
            term *= t_y;
            term /= denom;
            sum += term;
            denom += m_one; // denom is factorial component
            int dChk = static_cast<int>(denom);
            //if ((term.RE.getExponent() >= reExp) || (term.IM.getExponent() >= imExp)) break;
            if ((rExp >= reExp) || (iExp >= imExp)) 
            {
                makingProgress = false;
                break;
            }
            fraction = -RE.min(rExp, iExp) / bRound;
            RE.disp.progress(fraction);
        }
        sum += term;
        y *= sum;
    }
    *this = goodNumber? R * y: badNum;
    RE.disp.progress_text("");
    RE.disp.progress(0.0);
    return count;


}


/*
int mcomplex::taylor_agm_e(void)
{ // this is x. barring errors it shall become e^x 
    int degree = 21, count = 0, agmcount = 0;
    if (!RE.isNumber() || !IM.isNumber()) return 0;
    
    mfloat R = exp(RE), zero(0), m_one(1), nan = m_one / zero,
        denom0[] = {string("1"), string("1"), string("2"), string("6"), string("24"), 
                    string("120"), string("720"), string("5040"), string("40320"), string("362880"), string("3628800"),
                    string("3.99168E7"), string("4.790016E8"), string("6.2270208E9"),
                    string("8.71782912E10"), string("1.307674368E12"), string("2.0922789888E13"),
                    string("3.55687428096E14"), string("6.402373705728E15"), 
                    string("1.21645100408832E17"), string("2.43290200817664E18")};
    
    IM.getFirstRotation();
    if (IM == zero)
    {
        RE = R;
        return count;
    }
    double theta0 = static_cast<double>(IM);
    //BMAX += 64;
    mcomplex x(0, IM), y(cos(theta0), sin(theta0)), one(1, 0), zer(0, 0), f_y(one),
        t_y[degree], LOG(one), sum(zer), iLU[4], badNum(nan, nan), denom(zer);

    bool goodNumber = true;

    iLU[0] = mcomplex(1, 0); // i^0
    iLU[1] = mcomplex(0, 1); // i^1
    iLU[2] = mcomplex(-1, 0);// i^2
    iLU[3] = mcomplex(0, -1);// i^3

    for (int i = 0; i < degree; ++i) t_y[i] = one;
    int e_prev = 0;
    double xd0 = 0.0, xd1 = 0.0, xd2 = 0.0, xd3 = 0.0, xd4 = 0.0, xd5 = 0.0;
    while ((((f_y.RE.getExponent() + RE.BROUND) > 0) && (f_y.RE != zero)) ||
        (((f_y.IM.getExponent() + RE.BROUND) > 0) && f_y.IM != zero))
    {
        if (count > 0)
        {
            sum = zer;
            for (int i = 0; i < degree; ++i)
            {
                if (i > 1) t_y[i] = t_y[i - 1] * t_y[1];
                sum += t_y[i] / denom0[i];
            }
            y *= sum;
        }
        LOG = y;
        agmcount += LOG.eLog("ℂ ℯ˟ via taylor/agm n=" + to_string(++count));
        goodNumber = LOG.RE.isNumber() && LOG.IM.isNumber();
        if (!goodNumber) break;
        //LOG.IM.getFirstRotation();
        //xd0 = static_cast<double>(y.RE);
        //xd1 = static_cast<double>(y.IM);
        //xd2 = static_cast<double>(sum.RE);
        //xd3 = static_cast<double>(sum.IM);
        //xd4 = static_cast<double>(LOG.RE);
        //xd5 = static_cast<double>(LOG.IM);
        t_y[1] = x -  LOG;
        f_y = LOG - x;
        //cout << count << ") ℂ taylor/agm so far: RE<" << f_y.RE.getExponent() << "> IM<" << f_y.IM.getExponent() << 
        //    "> y is (" << xd0 << ", " << xd1 << ") sum is (" << xd2 << ", " << xd3 << ") log is (" <<
        //    xd4 << ", " << xd5 << ") \n";
        if (f_y.getMagnitude() == zero)
        {
            break;
        }
    }
    *this = goodNumber? R * y: badNum;
    RE.disp.progress_text("");
    return count;


}
*/


void mcomplex::multiply_with_order(const mcomplex & b, char & order)
{ // this will be multiplied by b, 
  // order will be 't' if angle this origin b < pi
  //               'b' if angle b origin this < pi
  //               'n' if angle this origin b = pi
    mfloat outer = RE * b.IM, inner = IM * b.RE,
        thisDiff = RE - IM, bSum = b.RE + b.IM,
        pBuff = thisDiff * bSum, cross = outer - inner,
        zero(0);

    IM = outer + inner;
    RE = pBuff - outer + inner;

    order = cross == zero? 'n': cross > zero? 't': 'b';


}

mfloat mcomplex::cross(const mcomplex & b)
{ // returns this cross b
    mfloat outer = RE * b.IM, inner = IM * b.RE,
        cross = outer - inner;

    return cross;
}

