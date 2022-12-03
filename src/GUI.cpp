#include "GUI.h"

// static initializations:
//Glib::ustring GUI::plus = "➕️", GUI::minus = "➖️", GUI::multiply = "✖️", GUI::divide = "➗️", 
//    GUI::line_start = "↪️", GUI::sum = "⅀", GUI::product = "∏", GUI::fRtn = "✅";
Glib::ustring GUI::plus = "+", GUI::minus = "-", GUI::multiply = "×", GUI::divide = "÷", 
    GUI::line_start = "▶", GUI::sum = "∑", GUI::product = "⋇", GUI::fRtn = "⟹", 
    GUI::exp_char = "⏨", GUI::wait_char = "⋯";//"⌛";


GUI::GUI(void)
{
/*
    union uDbg_union_type
    {
        uDbg_union_type(void): uVal(' ') {}
        ~uDbg_union_type(void) {}
        Glib::ustring::value_type uVal;
        unsigned char uChar[10];
    } uDbg;
    //for (int i = 0; i < 10; ++i) uDbg.uChar[i] = 0;
    Glib::ustring tmp = "⎺";
    Glib::ustring::size_type uStrbytes = tmp.bytes();
    //uDbg.uStr = tmp;
    uDbg.uVal = tmp[0];
    size_t vt_sz = sizeof(Glib::ustring::value_type);
*/
    //timer_control = 0;
    //bool btmp = mfloat::SaveSigFigs();
    typedFunction = ' ';
    state = 'e';
    pG = GEXT::getInst();
    pG->gui = this;
    mainWnd = NULL;
	pG->get(GEXT::MainWindow, mainWnd);
	mainWnd->set_title("Adjustable Precision Calculation");
    //mainWnd->maximize();

    oBox = NULL;
    pG->get("OutputBox", oBox);
    oBox->set_editable(false);
    Pango::FontDescription fdesc;
    fdesc.set_family("Arial");
    fdesc.set_size(10 * PANGO_SCALE);
    oBox->override_font(fdesc);    
    otb = Gtk::TextBuffer::create();
    oBox->set_buffer(otb);
    //otb->set_text("Hi There!\n");
    mfloat::disp.OB = otb;
    mfloat::disp.OBInitialized = true;
    
    iBox = NULL;
    pG->get("InputBox", iBox);
    iBox->override_font(fdesc);
    itb = Gtk::TextBuffer::create();
    iBox->set_buffer(itb);
	itb->signal_insert().connect(sigc::mem_fun<const Gtk::TextBuffer::iterator &, const Glib::ustring &, int, void>(*this, &GUI::on_InputBuffer_insert));
    itb->signal_changed().connect(sigc::mem_fun(*this, &GUI::on_InputBuffer_changed));
    //itb->set_text("Hi There!\n");
    //mfloat::disp.TB = itb.get();
    Glib::RefPtr<Gtk::TextTag> dTag = itb->create_tag("DBL_ME"),
        cTag = itb->create_tag("CTR_ME");
    dTag->set_property("size", 20 * PANGO_SCALE); //("scale", 2.0);
    cTag->set_property("justification", Gtk::JUSTIFY_CENTER);


    pBar = NULL;
    pG->get("ProgressBar", pBar);
    mfloat::disp.PB = pBar;

    mainWnd->show_all();

    precisionDlg = NULL;
    pG->get("PrecisionDialog", precisionDlg);

    precisionEntry = NULL;
    pG->get("PrecisionDialogEntry", precisionEntry);

    for (int i = 0; i <= 8; ++i)
    {
        Gtk::ButtonBox * pBB = NULL;
        pG->get("BBox" + to_string(i), pBB);
        btnbx.push_back(pBB);

    }

    HandleAllClearButton();
}

GUI::~GUI(void)
{

}

void GUI::HandleNumberButton(const unsigned char & nIn)
{
    // // cout << "HandleNumberButton w/ " << nIn << "\n";
    xStr = itb->get_text();
    //char c = nIn + '0';
    string s = to_string(nIn);
    Glib::ustring buff1 = s, buff2 = line_start + buff1;
    //if (xStr.find(line_start) != Glib::ustring::npos) itb->insert_at_cursor(buff1);
    if (state == 'e') itb->insert_at_cursor(buff1);
    else 
    {
        state = 'e';
        writeIN(buff2);
    }
    xCount = 0;
    mainWnd->set_focus(*iBox);
}

void GUI::HandlePiButton(void)
{
    // cout << "HandlePiButton\n";
 
    x.pi_me();
    state = 'e';
    writeIN("ℿ" + ResX(x.ConvertToDecimal()));
    //state = 'f';
    xCount = 0;
}

void GUI::HandlePointButton(void)
{
    // cout << "HandlePointButton\n";
    xStr = itb->get_text();
    if (state == 'e')
    {
        if (xStr.find('.') == Glib::ustring::npos) itb->insert_at_cursor(".");
    }
    else
    {
        state = 'e';
        writeIN(line_start + "0.");
        
    }
    xCount = 0;
}

void GUI::HandleClearButton(void)
{
    // cout << "HandleClearButton\n";
    xStr = line_start;
    state = 'e';
    xCount = 0;
    writeIN(xStr);

}

void GUI::HandleAllClearButton(void)
{
    // cout << "HandleAllClearButton\n";
    PRODUCT.clear();
    SUM.clear();
    x = 0;
    xStr = line_start;
    state = 'e'; // entry
    xCount = 0;
    writeIN(xStr);
}

void GUI::HandleLNButton(void)
{
    // cout << "HandleLNButton\n";
    GetX();
    writeOUT("㏑(" + ResX(ASC) + ")\n");
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    x = log(x);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;
}

void GUI::HandleEXPButton(void)
{
    // cout << "HandleEXPButton\n";
    GetX();
    writeOUT("ℯ˟(" + ResX(ASC) + ")\n");
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    x = exp(x);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;

}

void GUI::HandleATANButton(void)
{
    // cout << "HandleATANButton\n";
    GetX();
    writeOUT("atan(" + ResX(ASC) + ")\n");
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    //chrono::_V2::steady_clock::time_point start = std::chrono::steady_clock::now();

    //x = atan(x);
    mcomplex arcTan(1, x);
    x = atan(arcTan);

    //chrono::_V2::steady_clock::time_point end = std::chrono::steady_clock::now();
    //chrono::duration<double> elapsed_seconds = end-start;
    //cout << "ATAN elapsed time: " << elapsed_seconds.count() << "s\n";

    state = 'e';
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;
    
}

void GUI::HandleTimesButton(void)
{
    // cout << "HandleTimesButton\n";
    GetX();
    clearPRODUCT();
    multiplicative_queue mq = {'*', x, ASC};
    PRODUCT.push_back(mq);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += product;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    //writeIN(product + ASC);
    state = 'f';
    xCount = 0;
}

void GUI::HandleDivideButton(void)
{
    // cout << "HandleDivideButton\n";
    GetX();
    clearPRODUCT();
    multiplicative_queue mq = {'/', x, ASC};
    PRODUCT.push_back(mq);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += product;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    //writeIN(product + ASC);
    state = 'f';
    xCount = 0;
    //double dCk1 = static_cast<double>(x);
}

void GUI::HandleSINButton(void)
{
    // cout << "HandleSINButton\n";
    GetX();
    writeOUT("sin(" + ResX(ASC) + ")\n");
    state = 'e';
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    //chrono::_V2::steady_clock::time_point start = std::chrono::steady_clock::now();

    x = sin(x);
    //mcomplex theta(x);
    //x = theta.getImaginaryPart();

    //chrono::_V2::steady_clock::time_point end = std::chrono::steady_clock::now();
    //chrono::duration<double> elapsed_seconds = end-start;
    //cout << "SIN elapsed time: " << elapsed_seconds.count() << "s\n";

    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;
}

void GUI::HandleCOSButton(void)
{
    // cout << "HandleCOSButton\n";
    GetX();
    writeOUT("cos(" + ResX(ASC) + ")\n");
    state = 'e';
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    x = cos(x);
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;
}

void GUI::HandleTANButton(void)
{
    // cout << "HandleTANButton\n";
    GetX();
    writeOUT("tan(" + ResX(ASC) + ")\n");
    state = 'e';
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    x = tan(x);
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;
}

void GUI::HandlePlusButton(void)
{
    // cout << "HandlePlusButton\n";
    GetX();
    clearPRODUCT();
    clearSUM();
    additive_queue aq = {'+', x, ASC};
    SUM.push_back(aq);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += sum;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    //writeIN(sum + ASC);
    state = 'f';
    xCount = 0;
}

void GUI::HandleMinusButton(void)
{
    // cout << "HandleMinusButton\n";
    GetX();
    clearPRODUCT();
    clearSUM();
    additive_queue aq = {'-', x, ASC};
    SUM.push_back(aq);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += sum;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    //writeIN(sum + ASC);
    state = 'f';
    xCount = 0;
}

void GUI::HandleMultiplicativeInverseButton(void)
{
    // cout << "HandleMultiplicativeInverseButton\n";
    GetX();
    writeOUT("⅟ₓ(" + ResX(ASC) + ")\n");
    x = inverse_m(x);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    state = 'f';
    xCount = 0;
}

void GUI::HandleSquareButton(void)
{
    // cout << "HandleSquareButton\n";
    GetX();
    writeOUT("x²(" + ResX(ASC) + ")\n");
    x = sqr(x);
    state = 'e';
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    state = 'f';
    xCount = 0;
}

void GUI::HandleSquareRootButton(void)
{
    // cout << "HandleSquareRootButton\n";
    GetX();
    writeOUT("√(" + ResX(ASC) + ")\n");
    //chrono::_V2::steady_clock::time_point start = std::chrono::steady_clock::now();

    x = sqrt(x);

    //chrono::_V2::steady_clock::time_point end = std::chrono::steady_clock::now();
    //chrono::duration<double> elapsed_seconds = end-start;
    //cout << "square root elapsed time: " << elapsed_seconds.count() << "s\n";

    state = 'e';
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    state = 'f';
    xCount = 0;
}

void GUI::HandleEqualButton(void)
{
    // cout << "HandleEqualButton\n";
    GetX();
    //chrono::_V2::steady_clock::time_point start = std::chrono::steady_clock::now();

    clearPRODUCT();
    clearSUM();

    //chrono::_V2::steady_clock::time_point end = std::chrono::steady_clock::now();
    //chrono::duration<double> elapsed_seconds = end-start;
    //cout << "= elapsed time: " << elapsed_seconds.count() << "s\n";



    //GetX();
    writeOUT("=(" + ResX(ASC) + ")\n");
    state = 'e';
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(ASC)); //x.ConvertToDecimal());
    state = 'f';
    xCount = 0;
}

void GUI::HandleAdditiveInverseButton(void)
{   // like Handle_Number s/b all string manipulation
    // this will change the sign of the exponent if present
    // otherwise this will change the sign of the significand
    // cout << "HandleAdditiveInverseButton\n";
    
    if (state == 'f') return;
    xStr = itb->get_text();
    string aBuff = makeASC(xStr), int_part = "", fract_part = "", exp_part = "";
    if (aBuff.size() == 0) return;
    bool is_float = x.IsFloat(aBuff, int_part, fract_part, exp_part),
        is_zero = is_float && x.isthisZero(int_part, fract_part);
    if (!is_float || is_zero) return;
    Glib::ustring signs = "+-", digits = signs + "0123456789", allowable = "." + digits;
    if (exp_part.size() > 0)
    { // change sign in exponent:
        char e_sign = exp_part[0];
        exp_part = exp_part.substr(1);
        exp_part = (e_sign == '+'? "-": "") + exp_part;
        Glib::ustring::size_type e_pos = xStr.find(exp_char);
        assert(e_pos != Glib::ustring::npos);
        ++e_pos;
        Glib::ustring::size_type f_pos = xStr.find_first_not_of(digits, e_pos);
        Gtk::TextBuffer::iterator it1 = itb->get_iter_at_offset(e_pos),
            it2 = f_pos == Glib::ustring::npos? itb->end(): itb->get_iter_at_offset(f_pos);
        itb->erase(it1, it2);
        it1 = itb->get_iter_at_offset(e_pos);
        itb->insert(it1, exp_part); 
    }
    else
    { // change sign in significand:
        char n_sign = ' ';
        if (int_part.size() == 0) 
        {
            int_part = "+0";
            n_sign = fract_part[0];
        }
        else n_sign = int_part[0];
        string significand = int_part.substr(1);
        if (fract_part.size() > 0)  significand += "." + fract_part.substr(1);
        Glib::ustring::size_type n_pos = xStr.find_first_of(allowable),
            f_pos = xStr.find_first_not_of(allowable, n_pos);
        assert (n_pos != Glib::ustring::npos);
        Glib::ustring c_at = "";
        c_at = xStr[n_pos];
        Gtk::TextBuffer::iterator it1 = itb->get_iter_at_offset(n_pos);
        if (signs.find(c_at) != Glib::ustring::npos) 
        { // + or - actually in x string so remove it:
            it1 = itb->get_iter_at_offset(n_pos + 1);
            itb->backspace(it1);
            if (f_pos != Glib::ustring::npos) --f_pos;
            it1 = itb->get_iter_at_offset(n_pos);
        }
        if (n_sign == '+') 
        { // if significand has to be made negative add sign:
            significand = "-" + significand;
            Gtk::TextBuffer::iterator it2 = f_pos == Glib::ustring::npos? itb->end(): itb->get_iter_at_offset(f_pos);
            itb->erase(it1, it2);
            it1 = itb->get_iter_at_offset(n_pos);
            itb->insert(it1, significand);
        }
        
    }
    xCount = 0;
    mainWnd->set_focus(*iBox);
}

void GUI::HandleFractorialButton(void)
{
    // cout << "HandleFractorialButton\n";
    GetX();
    writeOUT("x!(" + ResX(ASC) + ")\n");
    state = 'e';
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    x = fact(x);
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;
}

void GUI::HandleLDXButton(void)
{
    // cout << "HandleLDXButton\n";
    Glib::RefPtr<Gtk::TextMark> i_tm = otb->get_mark("insert"),
        sb_tm = otb->get_mark("selection_bound");
    for (int i = xCount; i < (otb->get_line_count() - 1); ++i)
    {
        Gtk::TextBuffer::iterator it1 = otb->get_iter_at_line(i),
            it2 = otb->get_iter_at_line(i + 1);
        Glib::ustring slice = otb->get_slice(it1, it2);
        // look for an x value:
        Glib::ustring::size_type p1 = slice.find('('), p2 = slice.find(')');
        if ((p1 != Glib::ustring::npos) && (p2 != Glib::ustring::npos))
        { // found an x:
            ++p1;
            Glib::ustring uBuff = slice.substr(p1, p2 - p1), tmp = "";
            ASC = makeASC(uBuff);
            //WaitForIt();
            //while (gtk_events_pending()) gtk_main_iteration(); 
            x = ASC;
            //AcceptInput();
            //while (gtk_events_pending()) gtk_main_iteration(); 
            tmp += line_start;
            state = 'e';
            writeIN(tmp + uBuff);
            //state = 'f';
            it1 = otb->get_iter_at_line_offset(i, p1);
            it2 = otb->get_iter_at_line_offset(i, p2);
            otb->select_range(it1, it2);
            //otb->move_mark(i_tm, it1);
            //otb->move_mark(sb_tm, it2);
            oBox->scroll_to(i_tm, 0.0, 0.0, 0.0);
            xCount = (i + 1) % (otb->get_line_count() - 1);
            break;
        }

    }

}

void GUI::HandleChangePrecisionButton(void)
{
    // cout << "HandleChangePrecisionButton\n";
    precisionEntry->set_text(to_string(mfloat::DROUND));
    //WaitForIt();
    precisionDlg->run();
}

void GUI::HandlePrecisionDialogCancelButton(void)
{
    // cout << "HandlePrecisionDialogCancelButton\n";
    precisionDlg->hide();
    x.display_all_constants();
    //AcceptInput();
}

void GUI::HandlePrecisionDialogChangeButton(void)
{
    // cout << "HandlePrecisionDialogChangeButton\n";
    Glib::ustring u_tmp = precisionEntry->get_text();
    string tmp = makeASC(u_tmp);
    int itmp = stoi(tmp);
    x.reset_DROUND(itmp);
    //AcceptInput();
    precisionDlg->hide();
    x.display_all_constants();
}

void GUI::HandleTenButton(void)
{
    // cout << "HandleTenButton\n";
    GetX();
    writeOUT("10˟(" + ResX(ASC) + ")\n");
    state = 'e';
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();

    //chrono::_V2::steady_clock::time_point start = std::chrono::steady_clock::now();

    x = x_to_the_y(10, x);

    //chrono::_V2::steady_clock::time_point end = std::chrono::steady_clock::now();
    //chrono::duration<double> elapsed_seconds = end-start;
    //cout << "10^x elapsed time: " << elapsed_seconds.count() << "s\n";

    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;

}
void GUI::HandleLOGButton(void)
{
    // cout << "HandleLOGButton\n";
    GetX();
    writeOUT("㏒(" + ResX(ASC) + ")\n");
    state = 'e';
    //writeIN("☕ Calculating...(please wait)");
    WaitForIt();
    x = log_base_b(10, x);
    Glib::ustring tmp = "";
    tmp += fRtn;
    writeIN(tmp + ResX(x.ConvertToDecimal()));
    AcceptInput();
    state = 'f';
    xCount = 0;

}
void GUI::HandleRaiseButton(void)
{
    // cout << "HandleRaiseButton\n";
    xStr = itb->get_text();
    if (state == 'e')
    {
        if (xStr.find(exp_char) == Glib::ustring::npos) itb->insert_at_cursor(exp_char);
    }
    else
    {
        state = 'e';
        itb->set_text(line_start + "1.0" + exp_char);
    }
    xCount = 0;
    mainWnd->set_focus(*iBox);

}


void GUI::GetX(void)
{

    xStr = itb->get_text();
    ASC = "";
    Glib::ustring buff = "";
    for (int i = 0; i < xStr.size(); ++i)
    {
        buff = xStr[i];
        if (buff.is_ascii()) ASC += buff;
        if (0 == buff.compare(exp_char)) ASC += "E";
    }
    if (ASC.size() == 0) ASC.push_back('0');
    char lst = ASC.at(ASC.size() - 1);
    while ((lst < '0') || (lst > '9')) 
    { // removing non-numerics at string end esp. + - * / \n \r
        
        if (ASC.size() == 0)
        {
            lst = '0';
            ASC.push_back(lst);
            break;
        }
        ASC.pop_back();
        //char sbuff = state;
        //state = 'e';
        itb->backspace(itb->end());
        //state = sbuff;
        lst = ASC.at(ASC.size() - 1);
    }
    //if (xStr.find(line_start) != Glib::ustring::npos) x = ASC;
    if (state == 'e') 
    {
        // cout << "state e in GetX ASC is " << ASC << "\n";
        x = ASC;
        ASC = x.ConvertToDecimal();
    }
    
}

void GUI::writeIN(const Glib::ustring & w)  // replaces
{
    itb->set_text(w);
    Gtk::TextBuffer::iterator tb_it = itb->get_iter_at_offset(1);
    itb->apply_tag_by_name("DBL_ME", itb->begin(), tb_it);
    mainWnd->set_focus(*iBox);

}
    
void GUI::writeOUT(const Glib::ustring & w, const bool & animate) // prepends
{
    otb->remove_all_tags(otb->begin(), otb->end());
    if (0 != oBox->get_pixels_inside_wrap()) oBox->set_pixels_inside_wrap(0);
    //Glib::RefPtr<Pango::Context> p_c = oBox->get_pango_context();
    //Pango::FontDescription fdesc = p_c->get_font_description();
    //string w2 = fdesc.to_string() + w;
    
    otb->insert(otb->begin(), w);
    //Glib::RefPtr<Gtk::Adjustment> vadj = oBox->get_vadjustment();
    //double lower = vadj->get_lower(), upper = vadj->get_upper(), current = vadj->get_value();
    //// cout << "lower:" << lower << " upper:" << upper << " current:" << current;
    Glib::RefPtr<Gtk::TextMark> i_tm = otb->get_mark("insert");//,
        //sb_tm = otb->get_mark("selection_bound");
    //otb->move_mark(i_tm, otb->begin());
    //oBox->scroll_to(i_tm, 0.0, 0.0, 0.0);
    //int lc = OB->get_line_count();
    if (otb->get_line_count() > 2)
    {
        otb->select_range(otb->begin(), otb->get_iter_at_line(2));
        //otb->move_mark(i_tm, otb->begin());
        //vadj->set_value(vadj->get_lower());
        //current = vadj->get_value();
        oBox->scroll_to(i_tm, 0.0, 0.0, 0.0);
        
        //otb->move_mark(sb_tm, otb->get_iter_at_line(2));
        //otb->move_mark_by_name("insert", otb->begin());
        //otb->move_mark_by_name("selection_bound", otb->get_iter_at_line(2));
        while (gtk_events_pending()) gtk_main_iteration();
        if (animate) usleep(300000); // three tenths of a second?
    }
    otb->select_range(otb->begin(), otb->get_iter_at_line(1));
    if (0 != oBox->get_pixels_inside_wrap()) oBox->set_pixels_inside_wrap(0);
    //cout << "pixels inside wrap for oBox: " << oBox->get_pixels_inside_wrap() << "\n";
    //otb->move_mark(i_tm, otb->begin());
    //oBox->scroll_to(i_tm, 0.0, 0.0, 0.0);
    //otb->move_mark(sb_tm, otb->get_iter_at_line(1));

    //otb->move_mark_by_name("insert", otb->begin());
    //otb->move_mark_by_name("selection_bound", otb->get_iter_at_line(1));
    //lower = vadj->get_lower();
    //upper = vadj->get_upper(); 
    //current = vadj->get_value();
    //// cout << "lower:" << lower << " upper:" << upper << " current:" << current;

}

void GUI::clearPRODUCT(void)
{ // will modify x w/ the values and functions in the queue
    //if (PRODUCT.size() == 0) return;
    while (PRODUCT.size() > 0)
    {
        multiplicative_queue mq = PRODUCT.at(PRODUCT.size() - 1);
        assert ((mq.m_type == '*') || (mq.m_type == '/'));
        writeOUT("@(" + ResX(mq.m_ASC) + ")\n", false);
        switch (mq.m_type)
        {
            case '*':
                //writeOUT(multiply + "(" + x.ConvertToDecimal() + ")\n");
                writeOUT(multiply + "(" + ResX(ASC) + ")\n", false);
                x *= mq.m_value;
                break;
            case '/':
                //writeOUT(divide + "(" + x.ConvertToDecimal() + ")\n");
                writeOUT(divide + "(" + ResX(ASC) + ")\n", false);
                x /= mq.m_value;
                x = inverse_m(x);
                break;
        }
        state = 'e';
        Glib::ustring tmp = "";
        tmp += product;
        writeIN(tmp + ResX(x.ConvertToDecimal()));
        //writeIN(product + x.ConvertToDecimal());
        state = 'f';
        GetX();
        
        PRODUCT.pop_back();
        assert(PRODUCT.size() == 0); // should only be one element
    }
}
    
void GUI::clearSUM(void)
{
    while (SUM.size() > 0)
    {
        additive_queue aq = SUM.at(SUM.size() - 1);
        assert ((aq.add_type == '+') || (aq.add_type == '-'));
        writeOUT("@(" + ResX(aq.add_ASC) + ")\n", false);
        switch (aq.add_type)
        {
            case '+':
                //writeOUT(plus + "(" + x.ConvertToDecimal() + ")\n");
                writeOUT(plus + "(" + ResX(ASC) + ")\n", false);
                x += aq.add_value;
                break;
            case '-':
                //writeOUT(minus + "(" + x.ConvertToDecimal() + ")\n");
                writeOUT(minus + "(" + ResX(ASC) + ")\n", false);
                x -= aq.add_value;
                x = inverse_a(x);
                break;
        }
        state = 'e';
        Glib::ustring tmp = "";
        tmp += sum;
        writeIN(tmp + ResX(x.ConvertToDecimal()));
        //writeIN(sum + x.ConvertToDecimal());
        state = 'f';
        GetX();

        SUM.pop_back();
        assert (SUM.size() == 0); // should only be one element
    }

}

void GUI::on_InputBuffer_insert(const Gtk::TextBuffer::iterator & pos, const Glib::ustring & text, int bytes)
{ // textbuffer not yet updated (should happen in default handler next)
    // cout << "InputBuffer insert signal handler called w/ " << text << " & state=" << state << "\n";
    //timer_control = 0;
    Glib::ustring::value_type lastChar = text[text.size() - 1];
    char lst = static_cast<char>(lastChar);
    switch(lst)
    {
    case '*':
    case '/':
    case '+':
    case '-':
    case '=':
    case '\n':
    case 'c':
    case 'C':
    case 'e':
    case 'E':
                setupTimer(lst);
                return;
    }
    if (state == 'f')
    { // this will clear the input text buffer to start 
      // receiving the 2nd operand for a binary operator like + - * or / 
        state = 'e';
        Glib::ustring firstChar = "";
        firstChar = text[0];
        if (firstChar.is_ascii()) typedBuffer = line_start + text;
        else typedBuffer = text;
        setupTimer('f');
    }

}

void GUI::on_InputBuffer_changed(void)
{ // called before textbuffer update
    // cout << "InputBuffer changed signal handler called\n";

}

bool GUI::on_timeout(int timerID)
{
    conn.disconnect(); // one-shot timeout
    // hopefully this will allow the input text buffer's default handler to finish:
    while (gtk_events_pending()) gtk_main_iteration(); 
    switch(typedFunction)
    {
    case '*':
                HandleTimesButton();
                break;
    case '/':
                HandleDivideButton();
                break;
    case '+':
                HandlePlusButton();
                break;
    case '-':
                HandleMinusButton();
                break;
    case '=':
    case '\n':
                HandleEqualButton();
                break;
    case 'c':
                HandleClearButton();
                break;
    case 'C':
                HandleAllClearButton();
                break;
    case 'e':
    case 'E':
                itb->backspace(itb->end());
                itb->insert_at_cursor(exp_char);
                break;
    case 'f':
                itb->set_text(typedBuffer);
                break;

    }
    typedFunction = ' ';
    return false;
}
    
void GUI::setupTimer(char fChar)
{
    typedFunction = fChar;
    m_timer_number = rand();
    my_slot = sigc::bind(sigc::mem_fun(*this,
                &GUI::on_timeout), m_timer_number);

    // This is where we connect the slot to the Glib::signal_timeout()
    conn = Glib::signal_timeout().connect(my_slot, 10); // 10 ms = 1/100 seconds

}

void GUI::WaitForIt(void)
{
    for (vector<Gtk::ButtonBox*>::iterator bbIT = btnbx.begin(); bbIT != btnbx.end(); ++bbIT)
    {
        Gtk::ButtonBox * pBB = *bbIT;
        vector<Gtk::Widget *> ch = pBB->get_children();
        for (vector<Gtk::Widget*>::iterator wIT = ch.begin(); wIT != ch.end(); ++wIT)
        {
            Gtk::Widget * pWidg = *wIT;
            pWidg->set_sensitive(false);
        }
    }
    //Glib::ustring tmp = "∞ Calculating...(please wait) ∞";
    //writeIN(tmp);
    //Gtk::TextBuffer::iterator tb_it = itb->get_iter_at_offset(tmp.size() - 1);
    //itb->set_text(tmp);
    iBox->set_editable(false);
    char sBuff = state;
    state = 'e';
    //Glib::RefPtr<Pango::Context> p_c = oBox->get_pango_context();
    //Pango::FontDescription fdesc = p_c->get_font_description();
    string w2 = /*fdesc.to_string() + */wait_char + " calculating...(please wait) " + wait_char;

    itb->set_text(w2);
    state = sBuff;
    //itb->erase(itb->begin(), itb->end());
    //itb->remove_all_tags(itb->begin(), itb->end());
    //Glib::OptionGroup::vecustrings vstrs;
    //vstrs.push_back("DBL_ME");
    //vstrs.push_back("CTR_ME");
    //itb->insert_with_tags_by_name(itb->begin(), tmp, vstrs);
    //while (gtk_events_pending()) gtk_main_iteration(); 
    //timer_control = 1;
    //setupTimer(' ');
    itb->apply_tag_by_name("DBL_ME", itb->begin(), itb->end());
    itb->apply_tag_by_name("CTR_ME", itb->begin(), itb->end()); 
    //iBox->set_editable(false);

}
    
void GUI::AcceptInput(void)
{
    for (vector<Gtk::ButtonBox*>::iterator bbIT = btnbx.begin(); bbIT != btnbx.end(); ++bbIT)
    {
        Gtk::ButtonBox * pBB = *bbIT;
        vector<Gtk::Widget *> ch = pBB->get_children();
        for (vector<Gtk::Widget*>::iterator wIT = ch.begin(); wIT != ch.end(); ++wIT)
        {
            Gtk::Widget * pWidg = *wIT;
            pWidg->set_sensitive(true);
        }
    }
    iBox->set_editable(true);
    itb->remove_all_tags(itb->begin(), itb->end());

}

Glib::ustring GUI::ResX(const string & sIn)
{ // turns ASC into a displayable ustring
    size_t E_at = sIn.find('E');
    Glib::ustring r = sIn;
    if (E_at == string::npos) return r;
    r = sIn.substr(0, E_at) + exp_char + sIn.substr(E_at + 1);
    return r;
}

string GUI::makeASC(const Glib::ustring & uIn)
{
    string aBuff = "";
    Glib::ustring buff = "";
    for (int i = 0; i < uIn.size(); ++i)
    {
        buff = uIn[i];
        if (buff.is_ascii()) aBuff += buff;
        if (0 == buff.compare(exp_char)) aBuff += "E";
    }
    return aBuff;

}
