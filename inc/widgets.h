#pragma once

/*
#include <gtkmm.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <map>

*/
#include "stdafx.h"
//using namespace std;
/*
	usage: (in main start with:) GEXT::argc = argc; GEXT::argv = argv;
	from the glade file, an extract:
	MAINS:
		MainWindow, a GtkWindow
		MsgDlg, a GtkMessageDialog
		PrecisionDialog, a GtkDialog


	STYLES:
		GridWindow, a GtkGrid
		BBox0, a GtkButtonBox
		BBox1, a GtkButtonBox
		BBox2, a GtkButtonBox
		BBox3, a GtkButtonBox
		BBox4, a GtkButtonBox
		BBox5, a GtkButtonBox
		BBox6, a GtkButtonBox
		BBox7, a GtkButtonBox
		BBox8, a GtkButtonBox
		MsgButtonBox, a GtkButtonBox
		PrecisionDialogButtonBox, a GtkButtonBox


	CONTAINERS:
		InputBoxScrolled, a GtkScrolledWindow
		OutputBoxScrolled, a GtkScrolledWindow
		PrecisionDialogBox, a GtkBox


	CONTROLS:
		ProgressBar, a GtkProgressBar
		InputBox, a GtkTextView
		OutputBox, a GtkTextView
		OutputLabel, a GtkLabel
		InputLabel, a GtkLabel
		SevenButton, a GtkButton
		EightButton, a GtkButton
		NineButton, a GtkButton
		ClearButton, a GtkButton
		AllClearButton, a GtkButton
		LNButton, a GtkButton
		ExpButton, a GtkButton
		ATANButton, a GtkButton
		TenButton, aGtkButton
		FourButton, a GtkButton
		FiveButton, a GtkButton
		SixButton, a GtkButton
		TimesButton, a GtkButton
		DivideButton, a GtkButton
		SineButton, a GtkButton
		CosineButton, a GtkButton
		TangentButton, a GtkButton
		LOGButton, a GtkButton
		OneButton, a GtkButton
		TwoButton, a GtkButton
		ThreeButton, a GtkButton
		AddButton, a GtkButton
		MinusButton, a GtkButton
		MultiplicativeInverseButton, a GtkButton
		SquareButton, a GtkButton
		SqrtButton, a GtkButton
		RaiseButton, a GtkButton
		PiButton, a GtkButton
		ZeroButton, a GtkButton
		PointButton, a GtkButton
		EqualButton, a GtkButton
		InvertSignButton, a GtkButton
		FactorialButton, a GtkButton
		LDXButton, a GtkButton
		ChangePrecisionButton, a GtkButton
		ExitButton, a GtkButton
		OKButton, a GtkButton
		CancelButton, a GtkButton
		ChangeButton, a GtkButton
		PrecisionDialogLabel, a GtkLabel
		PrecisionDialogEntry, a GtkEntry
*/
// forward declaration:
typedef class GUI * pGUI;


class glade_info
{
public:
	string classType, id;
	Gtk::Widget * pW;

	glade_info(void):classType{}, id{}, pW{NULL}{}
	glade_info(const glade_info &a):classType{a.classType}, id{a.id}, pW{a.pW}{}
	~glade_info(void){}

	Gtk::Widget * getWidget(void) {return pW;}
	string getName() {return id;}
	string getClassType() {return classType;}
};
typedef class glade_extract GEXT;
typedef GEXT * pGEXT;

class glade_extract
{
	glade_info GI[64];
	glade_extract(void);
	static pGEXT pGEXTInstance;
	Gtk::Widget * get(const string &);
public:
	enum wdg_enum{MainWindow, MsgDlg, PrecisionDialog, GridWindow, BBox0, BBox1, BBox2, BBox3, BBox4, BBox5, BBox6, BBox7, BBox8, MsgButtonBox, PrecisionDialogButtonBox, InputBoxScrolled, OutputBoxScrolled, PrecisionDialogBox, ProgressBar, InputBox, OutputBox, OutputLabel, InputLabel, SevenButton, EightButton, NineButton, ClearButton, AllClearButton, LNButton, ExpButton, ATANButton, TenButton, FourButton, FiveButton, SixButton, TimesButton, DivideButton, SineButton, CosineButton, TangentButton, LOGButton, OneButton, TwoButton, ThreeButton, AddButton, MinusButton, MultiplicativeInverseButton, SquareButton, SqrtButton, RaiseButton, PiButton, ZeroButton, PointButton, EqualButton, InvertSignButton, FactorialButton, LDXButton, ChangePrecisionButton, ExitButton, OKButton, CancelButton, ChangeButton, PrecisionDialogLabel, PrecisionDialogEntry};
	void get(const string & s, Gtk::Button*&gtk){gtk=dynamic_cast<Gtk::Button*>(get(s));}
	void get(const string & s, Gtk::ButtonBox*&gtk){gtk=dynamic_cast<Gtk::ButtonBox*>(get(s));}
	void get(const string & s, Gtk::Dialog*&gtk){gtk=dynamic_cast<Gtk::Dialog*>(get(s));}
	void get(const string & s, Gtk::Entry*&gtk){gtk=dynamic_cast<Gtk::Entry*>(get(s));}
	void get(const string & s, Gtk::Grid*&gtk){gtk=dynamic_cast<Gtk::Grid*>(get(s));}
	void get(const string & s, Gtk::Label*&gtk){gtk=dynamic_cast<Gtk::Label*>(get(s));}
	void get(const string & s, Gtk::MessageDialog*&gtk){gtk=dynamic_cast<Gtk::MessageDialog*>(get(s));}
	void get(const string & s, Gtk::ProgressBar*&gtk){gtk=dynamic_cast<Gtk::ProgressBar*>(get(s));}
	void get(const string & s, Gtk::TextView*&gtk){gtk=dynamic_cast<Gtk::TextView*>(get(s));}
	//void get(const string & s, Gtk::Window*&gtk){gtk=dynamic_cast<Gtk::Window*>(get(s));}
	void get(const wdg_enum & e, Gtk::Window*&gtk){gtk=dynamic_cast<Gtk::Window*>(GI[e].pW);}
	bool on_MainWindow_delete_event(GdkEventAny*);
	void on_MainWindow_size_allocate(Gtk::Allocation&);
	bool on_MsgDlg_delete_event(GdkEventAny*);
	void on_MsgDlg_size_allocate(Gtk::Allocation&);
	bool on_PrecisionDialog_delete_event(GdkEventAny*);
	void on_PrecisionDialog_size_allocate(Gtk::Allocation&);
	bool on_ProgressBar_button_release_event(GdkEventButton*);
	bool on_InputBox_key_press_event(GdkEventKey*);
	bool on_InputBox_key_release_event(GdkEventKey*);
	void on_SevenButton_clicked(void);
	void on_EightButton_clicked(void);
	void on_NineButton_clicked(void);
	void on_ClearButton_clicked(void);
	void on_AllClearButton_clicked(void);
	void on_LNButton_clicked(void);
	void on_ExpButton_clicked(void);
	void on_ATANButton_clicked(void);
	void on_FourButton_clicked(void);
	void on_FiveButton_clicked(void);
	void on_SixButton_clicked(void);
	void on_TimesButton_clicked(void);
	void on_DivideButton_clicked(void);
	void on_SineButton_clicked(void);
	void on_CosineButton_clicked(void);
	void on_TangentButton_clicked(void);
	void on_OneButton_clicked(void);
	void on_TwoButton_clicked(void);
	void on_ThreeButton_clicked(void);
	void on_AddButton_clicked(void);
	void on_MinusButton_clicked(void);
	void on_MultiplicativeInverseButton_clicked(void);
	void on_SquareButton_clicked(void);
	void on_SqrtButton_clicked(void);
	void on_PiButton_clicked(void);
	void on_ZeroButton_clicked(void);
	void on_PointButton_clicked(void);
	void on_EqualButton_clicked(void);
	void on_InvertSignButton_clicked(void);
	void on_FactorialButton_clicked(void);
	void on_LDXButton_clicked(void);
	void on_ChangePrecisionButton_clicked(void);
	void on_ExitButton_clicked(void);
	void on_OKButton_clicked(void);
	void on_CancelButton_clicked(void);
	void on_ChangeButton_clicked(void);
	void on_PrecisionDialogEntry_changed(void);
	void on_TenButton_clicked(void);
	void on_LOGButton_clicked(void);
	void on_RaiseButton_clicked(void);
	static Gtk::Window* CMW;
	static int argc;
	static char ** argv;
	static Glib::RefPtr<Gtk::Application> the_app;
	static Glib::RefPtr<Gtk::Builder> refBuilder;
	static Glib::RefPtr<Gtk::CssProvider> provider;
	static Glib::RefPtr<Gdk::Display> display;
	static Glib::RefPtr<Gdk::Screen> screen;
	static pGEXT getInst(void);
	map<string, glade_info *> mains, styles, containers, controls;
	pGUI gui;
};
