#pragma once

#include "stdafx.h"
#include "mfloat.h"
#include "widgets.h"

struct additive_queue
{
    char add_type;
    mfloat add_value;
    string add_ASC;
};

struct multiplicative_queue
{
    char m_type;
    mfloat m_value;
    string m_ASC;
};

//struct local_buttons
//{
//    Gtk::Button * lbn;
//    bool hideable;
//};

class GUI
{
public:
    GUI(void);
    ~GUI(void);
    
    void HandleNumberButton(const unsigned char &);
    void HandlePiButton(void);
    void HandlePointButton(void);
    void HandleClearButton(void);
    void HandleAllClearButton(void);
    void HandleLNButton(void);
    void HandleEXPButton(void);
    void HandleATANButton(void);
    void HandleTimesButton(void);
    void HandleDivideButton(void);
    void HandleSINButton(void);
    void HandleCOSButton(void);
    void HandleTANButton(void);
    void HandlePlusButton(void);
    void HandleMinusButton(void);
    void HandleMultiplicativeInverseButton(void);
    void HandleSquareButton(void);
    void HandleSquareRootButton(void);
    void HandleEqualButton(void);
    void HandleAdditiveInverseButton(void); // s/b all ustring
    void HandleFractorialButton(void);
    void HandleLDXButton(void);
    void HandleChangePrecisionButton(void);
    void GetX(void);
    void writeIN(const Glib::ustring &);  // replaces text & triggers on_InputBuffer_insert
    void writeOUT(const Glib::ustring &, const bool & = true); // prepends
    void clearPRODUCT(void);
    void clearSUM(void);
    void HandlePrecisionDialogCancelButton(void);
    void HandlePrecisionDialogChangeButton(void);
    void HandleTenButton(void);
    void HandleLOGButton(void);
    void HandleRaiseButton(void);
    void on_InputBuffer_insert(const Gtk::TextBuffer::iterator &, const Glib::ustring &, int);
    void on_InputBuffer_changed(void);
    bool on_timeout(int);
    void setupTimer(char);
    void WaitForIt(void);
    void AcceptInput(void);
    Glib::ustring ResX(const string &);
    string makeASC(const Glib::ustring &);
    
	sigc::connection conn;
	sigc::slot<bool> my_slot;
	int m_timer_number; //, timer_control;

    pGEXT pG;
    Gtk::Window * mainWnd;
    Gtk::TextView * oBox, * iBox;
    Glib::RefPtr<Gtk::TextBuffer> otb, itb;
    Gtk::ProgressBar * pBar;
    Gtk::Dialog * precisionDlg;
    Gtk::Entry * precisionEntry;
    vector<Gtk::ButtonBox*> btnbx;
    
    mfloat x;
    vector<additive_queue> SUM;
    vector<multiplicative_queue> PRODUCT;
    Glib::ustring xStr, typedBuffer;
    string ASC; // ascii only
    static Glib::ustring plus, minus, multiply, divide,
        line_start, sum, product, fRtn, exp_char, wait_char;
    char state, typedFunction;
    int xCount;
    
    
};