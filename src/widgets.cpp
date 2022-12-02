#include "widgets.h"
#include "GUI.h"
//#include "gdk/gdkkeysyms.h"

//using namespace std;

extern char glade_start		asm("_binary_rsc_glade_glade_start");
extern char glade_end		asm("_binary_rsc_glade_glade_end");
extern char style_start		asm("_binary_rsc_style_css_start");
extern char style_end		asm("_binary_rsc_style_css_end");

Glib::RefPtr<Gtk::CssProvider> GEXT::provider;
Glib::RefPtr<Gdk::Display> GEXT::display;
Glib::RefPtr<Gdk::Screen> GEXT::screen;
Glib::RefPtr<Gtk::Application> GEXT::the_app;
Glib::RefPtr<Gtk::Builder> GEXT::refBuilder;
Gtk::Window* GEXT::CMW = NULL;
pGEXT GEXT::pGEXTInstance = NULL;
//initialize these next statics first in main before getInst():
int GEXT::argc = 0;
char ** GEXT::argv = NULL;

glade_extract::glade_extract(void)
{
	the_app = Gtk::Application::create(argc, argv, "from.the.glade");
	//Load the GtkBuilder file and instantiate its widgets:
	refBuilder = Gtk::Builder::create();

	char * g_s = &glade_start, * g_e = &glade_end;
	gsize g_z = g_e - g_s;
	//string gStr(g_s, g_z);
	//// // cout << "size: " << gStr.size() << "|SOF|\n" << gStr << "|EOF|\n";
	refBuilder->add_from_string(g_s, g_z);
/*
	try
	{
		refBuilder->add_from_file("rsc/glade.glade");
	}
	catch(const Glib::FileError& ex)
	{
		// // cout << "FileError: " << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch(const Glib::MarkupError& ex)
	{
		// // cout << "MarkupError: " << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch(const Gtk::BuilderError& ex)
	{
		// // cout << "BuilderError: " << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}
*/

	provider = Gtk::CssProvider::create();
	//Gtk::CssProvider * pProvider = provider.get();
	display = Gdk::Display::get_default();
	//Gdk::Display * pDisplay = display.get();
	screen = display->get_default_screen();
	Gtk::StyleContext::add_provider_for_screen(screen, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	char * s_s = &style_start, * s_e = &style_end;
	//gsize s_z = s_e - s_s;
	string s_str(s_s, s_e);
	provider->load_from_data(s_str);
	//pProvider->load_from_path("resources/style.css");

	GI[MainWindow].classType = "GtkWindow";
	GI[MainWindow].id = "MainWindow";
	refBuilder->get_widget("MainWindow", GI[MainWindow].pW);
	mains["MainWindow"] = &GI[MainWindow];
	((Gtk::Window*)GI[MainWindow].pW)->signal_delete_event().connect(sigc::mem_fun<GdkEventAny *, bool>(*this, &glade_extract::on_MainWindow_delete_event));
	((Gtk::Window*)GI[MainWindow].pW)->signal_size_allocate().connect(sigc::mem_fun<Gtk::Allocation&, void>(*this, &glade_extract::on_MainWindow_size_allocate));
	CMW = ((Gtk::Window*)GI[MainWindow].pW);
	GI[MsgDlg].classType = "GtkMessageDialog";
	GI[MsgDlg].id = "MsgDlg";
	refBuilder->get_widget("MsgDlg", GI[MsgDlg].pW);
	mains["MsgDlg"] = &GI[MsgDlg];
	((Gtk::MessageDialog*)GI[MsgDlg].pW)->signal_delete_event().connect(sigc::mem_fun<GdkEventAny *, bool>(*this, &glade_extract::on_MsgDlg_delete_event));
	((Gtk::MessageDialog*)GI[MsgDlg].pW)->signal_size_allocate().connect(sigc::mem_fun<Gtk::Allocation&, void>(*this, &glade_extract::on_MsgDlg_size_allocate));
	GI[PrecisionDialog].classType = "GtkDialog";
	GI[PrecisionDialog].id = "PrecisionDialog";
	refBuilder->get_widget("PrecisionDialog", GI[PrecisionDialog].pW);
	mains["PrecisionDialog"] = &GI[PrecisionDialog];
	((Gtk::Dialog*)GI[PrecisionDialog].pW)->signal_delete_event().connect(sigc::mem_fun<GdkEventAny *, bool>(*this, &glade_extract::on_PrecisionDialog_delete_event));
	((Gtk::Dialog*)GI[PrecisionDialog].pW)->signal_size_allocate().connect(sigc::mem_fun<Gtk::Allocation&, void>(*this, &glade_extract::on_PrecisionDialog_size_allocate));
	GI[GridWindow].classType = "GtkGrid";
	GI[GridWindow].id = "GridWindow";
	refBuilder->get_widget("GridWindow", GI[GridWindow].pW);
	styles["GridWindow"] = &GI[GridWindow];
	GI[BBox0].classType = "GtkButtonBox";
	GI[BBox0].id = "BBox0";
	refBuilder->get_widget("BBox0", GI[BBox0].pW);
	styles["BBox0"] = &GI[BBox0];
	GI[BBox1].classType = "GtkButtonBox";
	GI[BBox1].id = "BBox1";
	refBuilder->get_widget("BBox1", GI[BBox1].pW);
	styles["BBox1"] = &GI[BBox1];
	GI[BBox2].classType = "GtkButtonBox";
	GI[BBox2].id = "BBox2";
	refBuilder->get_widget("BBox2", GI[BBox2].pW);
	styles["BBox2"] = &GI[BBox2];
	GI[BBox3].classType = "GtkButtonBox";
	GI[BBox3].id = "BBox3";
	refBuilder->get_widget("BBox3", GI[BBox3].pW);
	styles["BBox3"] = &GI[BBox3];
	GI[BBox4].classType = "GtkButtonBox";
	GI[BBox4].id = "BBox4";
	refBuilder->get_widget("BBox4", GI[BBox4].pW);
	styles["BBox4"] = &GI[BBox4];
	GI[BBox5].classType = "GtkButtonBox";
	GI[BBox5].id = "BBox5";
	refBuilder->get_widget("BBox5", GI[BBox5].pW);
	styles["BBox5"] = &GI[BBox5];
	GI[BBox6].classType = "GtkButtonBox";
	GI[BBox6].id = "BBox6";
	refBuilder->get_widget("BBox6", GI[BBox6].pW);
	styles["BBox6"] = &GI[BBox6];
	GI[BBox7].classType = "GtkButtonBox";
	GI[BBox7].id = "BBox7";
	refBuilder->get_widget("BBox7", GI[BBox7].pW);
	styles["BBox7"] = &GI[BBox7];
	GI[BBox8].classType = "GtkButtonBox";
	GI[BBox8].id = "BBox8";
	refBuilder->get_widget("BBox8", GI[BBox8].pW);
	styles["BBox8"] = &GI[BBox8];
	GI[MsgButtonBox].classType = "GtkButtonBox";
	GI[MsgButtonBox].id = "MsgButtonBox";
	refBuilder->get_widget("MsgButtonBox", GI[MsgButtonBox].pW);
	styles["MsgButtonBox"] = &GI[MsgButtonBox];
	GI[PrecisionDialogButtonBox].classType = "GtkButtonBox";
	GI[PrecisionDialogButtonBox].id = "PrecisionDialogButtonBox";
	refBuilder->get_widget("PrecisionDialogButtonBox", GI[PrecisionDialogButtonBox].pW);
	styles["PrecisionDialogButtonBox"] = &GI[PrecisionDialogButtonBox];
	GI[InputBoxScrolled].classType = "GtkScrolledWindow";
	GI[InputBoxScrolled].id = "InputBoxScrolled";
	refBuilder->get_widget("InputBoxScrolled", GI[InputBoxScrolled].pW);
	containers["InputBoxScrolled"] = &GI[InputBoxScrolled];
	GI[OutputBoxScrolled].classType = "GtkScrolledWindow";
	GI[OutputBoxScrolled].id = "OutputBoxScrolled";
	refBuilder->get_widget("OutputBoxScrolled", GI[OutputBoxScrolled].pW);
	containers["OutputBoxScrolled"] = &GI[OutputBoxScrolled];
	GI[PrecisionDialogBox].classType = "GtkBox";
	GI[PrecisionDialogBox].id = "PrecisionDialogBox";
	refBuilder->get_widget("PrecisionDialogBox", GI[PrecisionDialogBox].pW);
	containers["PrecisionDialogBox"] = &GI[PrecisionDialogBox];
	GI[ProgressBar].classType = "GtkProgressBar";
	GI[ProgressBar].id = "ProgressBar";
	refBuilder->get_widget("ProgressBar", GI[ProgressBar].pW);
	controls["ProgressBar"] = &GI[ProgressBar];
	((Gtk::ProgressBar*)GI[ProgressBar].pW)->signal_button_release_event().connect(sigc::mem_fun<GdkEventButton*, bool>(*this, &glade_extract::on_ProgressBar_button_release_event));
	GI[InputBox].classType = "GtkTextView";
	GI[InputBox].id = "InputBox";
	refBuilder->get_widget("InputBox", GI[InputBox].pW);
	controls["InputBox"] = &GI[InputBox];
	((Gtk::TextView*)GI[InputBox].pW)->signal_key_press_event().connect(sigc::mem_fun<GdkEventKey*, bool>(*this, &glade_extract::on_InputBox_key_press_event));
	((Gtk::TextView*)GI[InputBox].pW)->signal_key_release_event().connect(sigc::mem_fun<GdkEventKey*, bool>(*this, &glade_extract::on_InputBox_key_release_event));
	GI[OutputBox].classType = "GtkTextView";
	GI[OutputBox].id = "OutputBox";
	refBuilder->get_widget("OutputBox", GI[OutputBox].pW);
	controls["OutputBox"] = &GI[OutputBox];
	GI[OutputLabel].classType = "GtkLabel";
	GI[OutputLabel].id = "OutputLabel";
	refBuilder->get_widget("OutputLabel", GI[OutputLabel].pW);
	controls["OutputLabel"] = &GI[OutputLabel];
	GI[InputLabel].classType = "GtkLabel";
	GI[InputLabel].id = "InputLabel";
	refBuilder->get_widget("InputLabel", GI[InputLabel].pW);
	controls["InputLabel"] = &GI[InputLabel];
	GI[SevenButton].classType = "GtkButton";
	GI[SevenButton].id = "SevenButton";
	refBuilder->get_widget("SevenButton", GI[SevenButton].pW);
	controls["SevenButton"] = &GI[SevenButton];
	((Gtk::Button*)GI[SevenButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_SevenButton_clicked));
	GI[EightButton].classType = "GtkButton";
	GI[EightButton].id = "EightButton";
	refBuilder->get_widget("EightButton", GI[EightButton].pW);
	controls["EightButton"] = &GI[EightButton];
	((Gtk::Button*)GI[EightButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_EightButton_clicked));
	GI[NineButton].classType = "GtkButton";
	GI[NineButton].id = "NineButton";
	refBuilder->get_widget("NineButton", GI[NineButton].pW);
	controls["NineButton"] = &GI[NineButton];
	((Gtk::Button*)GI[NineButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_NineButton_clicked));
	GI[ClearButton].classType = "GtkButton";
	GI[ClearButton].id = "ClearButton";
	refBuilder->get_widget("ClearButton", GI[ClearButton].pW);
	controls["ClearButton"] = &GI[ClearButton];
	((Gtk::Button*)GI[ClearButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ClearButton_clicked));
	GI[AllClearButton].classType = "GtkButton";
	GI[AllClearButton].id = "AllClearButton";
	refBuilder->get_widget("AllClearButton", GI[AllClearButton].pW);
	controls["AllClearButton"] = &GI[AllClearButton];
	((Gtk::Button*)GI[AllClearButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_AllClearButton_clicked));
	GI[LNButton].classType = "GtkButton";
	GI[LNButton].id = "LNButton";
	refBuilder->get_widget("LNButton", GI[LNButton].pW);
	controls["LNButton"] = &GI[LNButton];
	((Gtk::Button*)GI[LNButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_LNButton_clicked));
	GI[ExpButton].classType = "GtkButton";
	GI[ExpButton].id = "ExpButton";
	refBuilder->get_widget("ExpButton", GI[ExpButton].pW);
	controls["ExpButton"] = &GI[ExpButton];
	((Gtk::Button*)GI[ExpButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ExpButton_clicked));
	GI[ATANButton].classType = "GtkButton";
	GI[ATANButton].id = "ATANButton";
	refBuilder->get_widget("ATANButton", GI[ATANButton].pW);
	controls["ATANButton"] = &GI[ATANButton];
	((Gtk::Button*)GI[ATANButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ATANButton_clicked));
	GI[FourButton].classType = "GtkButton";
	GI[FourButton].id = "FourButton";
	refBuilder->get_widget("FourButton", GI[FourButton].pW);
	controls["FourButton"] = &GI[FourButton];
	((Gtk::Button*)GI[FourButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_FourButton_clicked));
	GI[FiveButton].classType = "GtkButton";
	GI[FiveButton].id = "FiveButton";
	refBuilder->get_widget("FiveButton", GI[FiveButton].pW);
	controls["FiveButton"] = &GI[FiveButton];
	((Gtk::Button*)GI[FiveButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_FiveButton_clicked));
	GI[SixButton].classType = "GtkButton";
	GI[SixButton].id = "SixButton";
	refBuilder->get_widget("SixButton", GI[SixButton].pW);
	controls["SixButton"] = &GI[SixButton];
	((Gtk::Button*)GI[SixButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_SixButton_clicked));
	GI[TimesButton].classType = "GtkButton";
	GI[TimesButton].id = "TimesButton";
	refBuilder->get_widget("TimesButton", GI[TimesButton].pW);
	controls["TimesButton"] = &GI[TimesButton];
	((Gtk::Button*)GI[TimesButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_TimesButton_clicked));
	GI[DivideButton].classType = "GtkButton";
	GI[DivideButton].id = "DivideButton";
	refBuilder->get_widget("DivideButton", GI[DivideButton].pW);
	controls["DivideButton"] = &GI[DivideButton];
	((Gtk::Button*)GI[DivideButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_DivideButton_clicked));
	GI[SineButton].classType = "GtkButton";
	GI[SineButton].id = "SineButton";
	refBuilder->get_widget("SineButton", GI[SineButton].pW);
	controls["SineButton"] = &GI[SineButton];
	((Gtk::Button*)GI[SineButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_SineButton_clicked));
	GI[CosineButton].classType = "GtkButton";
	GI[CosineButton].id = "CosineButton";
	refBuilder->get_widget("CosineButton", GI[CosineButton].pW);
	controls["CosineButton"] = &GI[CosineButton];
	((Gtk::Button*)GI[CosineButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_CosineButton_clicked));
	GI[TangentButton].classType = "GtkButton";
	GI[TangentButton].id = "TangentButton";
	refBuilder->get_widget("TangentButton", GI[TangentButton].pW);
	controls["TangentButton"] = &GI[TangentButton];
	((Gtk::Button*)GI[TangentButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_TangentButton_clicked));
	GI[OneButton].classType = "GtkButton";
	GI[OneButton].id = "OneButton";
	refBuilder->get_widget("OneButton", GI[OneButton].pW);
	controls["OneButton"] = &GI[OneButton];
	((Gtk::Button*)GI[OneButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_OneButton_clicked));
	GI[TwoButton].classType = "GtkButton";
	GI[TwoButton].id = "TwoButton";
	refBuilder->get_widget("TwoButton", GI[TwoButton].pW);
	controls["TwoButton"] = &GI[TwoButton];
	((Gtk::Button*)GI[TwoButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_TwoButton_clicked));
	GI[ThreeButton].classType = "GtkButton";
	GI[ThreeButton].id = "ThreeButton";
	refBuilder->get_widget("ThreeButton", GI[ThreeButton].pW);
	controls["ThreeButton"] = &GI[ThreeButton];
	((Gtk::Button*)GI[ThreeButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ThreeButton_clicked));
	GI[AddButton].classType = "GtkButton";
	GI[AddButton].id = "AddButton";
	refBuilder->get_widget("AddButton", GI[AddButton].pW);
	controls["AddButton"] = &GI[AddButton];
	((Gtk::Button*)GI[AddButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_AddButton_clicked));
	GI[MinusButton].classType = "GtkButton";
	GI[MinusButton].id = "MinusButton";
	refBuilder->get_widget("MinusButton", GI[MinusButton].pW);
	controls["MinusButton"] = &GI[MinusButton];
	((Gtk::Button*)GI[MinusButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_MinusButton_clicked));
	GI[MultiplicativeInverseButton].classType = "GtkButton";
	GI[MultiplicativeInverseButton].id = "MultiplicativeInverseButton";
	refBuilder->get_widget("MultiplicativeInverseButton", GI[MultiplicativeInverseButton].pW);
	controls["MultiplicativeInverseButton"] = &GI[MultiplicativeInverseButton];
	((Gtk::Button*)GI[MultiplicativeInverseButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_MultiplicativeInverseButton_clicked));
	GI[SquareButton].classType = "GtkButton";
	GI[SquareButton].id = "SquareButton";
	refBuilder->get_widget("SquareButton", GI[SquareButton].pW);
	controls["SquareButton"] = &GI[SquareButton];
	((Gtk::Button*)GI[SquareButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_SquareButton_clicked));
	GI[SqrtButton].classType = "GtkButton";
	GI[SqrtButton].id = "SqrtButton";
	refBuilder->get_widget("SqrtButton", GI[SqrtButton].pW);
	controls["SqrtButton"] = &GI[SqrtButton];
	((Gtk::Button*)GI[SqrtButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_SqrtButton_clicked));
	GI[PiButton].classType = "GtkButton";
	GI[PiButton].id = "PiButton";
	refBuilder->get_widget("PiButton", GI[PiButton].pW);
	controls["PiButton"] = &GI[PiButton];
	((Gtk::Button*)GI[PiButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_PiButton_clicked));
	GI[ZeroButton].classType = "GtkButton";
	GI[ZeroButton].id = "ZeroButton";
	refBuilder->get_widget("ZeroButton", GI[ZeroButton].pW);
	controls["ZeroButton"] = &GI[ZeroButton];
	((Gtk::Button*)GI[ZeroButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ZeroButton_clicked));
	GI[PointButton].classType = "GtkButton";
	GI[PointButton].id = "PointButton";
	refBuilder->get_widget("PointButton", GI[PointButton].pW);
	controls["PointButton"] = &GI[PointButton];
	((Gtk::Button*)GI[PointButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_PointButton_clicked));
	GI[EqualButton].classType = "GtkButton";
	GI[EqualButton].id = "EqualButton";
	refBuilder->get_widget("EqualButton", GI[EqualButton].pW);
	controls["EqualButton"] = &GI[EqualButton];
	((Gtk::Button*)GI[EqualButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_EqualButton_clicked));
	GI[InvertSignButton].classType = "GtkButton";
	GI[InvertSignButton].id = "InvertSignButton";
	refBuilder->get_widget("InvertSignButton", GI[InvertSignButton].pW);
	controls["InvertSignButton"] = &GI[InvertSignButton];
	((Gtk::Button*)GI[InvertSignButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_InvertSignButton_clicked));
	GI[FactorialButton].classType = "GtkButton";
	GI[FactorialButton].id = "FactorialButton";
	refBuilder->get_widget("FactorialButton", GI[FactorialButton].pW);
	controls["FactorialButton"] = &GI[FactorialButton];
	((Gtk::Button*)GI[FactorialButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_FactorialButton_clicked));
	GI[LDXButton].classType = "GtkButton";
	GI[LDXButton].id = "LDXButton";
	refBuilder->get_widget("LDXButton", GI[LDXButton].pW);
	controls["LDXButton"] = &GI[LDXButton];
	((Gtk::Button*)GI[LDXButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_LDXButton_clicked));
	GI[ChangePrecisionButton].classType = "GtkButton";
	GI[ChangePrecisionButton].id = "ChangePrecisionButton";
	refBuilder->get_widget("ChangePrecisionButton", GI[ChangePrecisionButton].pW);
	controls["ChangePrecisionButton"] = &GI[ChangePrecisionButton];
	((Gtk::Button*)GI[ChangePrecisionButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ChangePrecisionButton_clicked));
	GI[ExitButton].classType = "GtkButton";
	GI[ExitButton].id = "ExitButton";
	refBuilder->get_widget("ExitButton", GI[ExitButton].pW);
	controls["ExitButton"] = &GI[ExitButton];
	((Gtk::Button*)GI[ExitButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ExitButton_clicked));
	GI[OKButton].classType = "GtkButton";
	GI[OKButton].id = "OKButton";
	refBuilder->get_widget("OKButton", GI[OKButton].pW);
	controls["OKButton"] = &GI[OKButton];
	((Gtk::Button*)GI[OKButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_OKButton_clicked));
	GI[CancelButton].classType = "GtkButton";
	GI[CancelButton].id = "CancelButton";
	refBuilder->get_widget("CancelButton", GI[CancelButton].pW);
	controls["CancelButton"] = &GI[CancelButton];
	((Gtk::Button*)GI[CancelButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_CancelButton_clicked));
	GI[ChangeButton].classType = "GtkButton";
	GI[ChangeButton].id = "ChangeButton";
	refBuilder->get_widget("ChangeButton", GI[ChangeButton].pW);
	controls["ChangeButton"] = &GI[ChangeButton];
	((Gtk::Button*)GI[ChangeButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_ChangeButton_clicked));
	GI[PrecisionDialogLabel].classType = "GtkLabel";
	GI[PrecisionDialogLabel].id = "PrecisionDialogLabel";
	refBuilder->get_widget("PrecisionDialogLabel", GI[PrecisionDialogLabel].pW);
	controls["PrecisionDialogLabel"] = &GI[PrecisionDialogLabel];
	GI[PrecisionDialogEntry].classType = "GtkEntry";
	GI[PrecisionDialogEntry].id = "PrecisionDialogEntry";
	refBuilder->get_widget("PrecisionDialogEntry", GI[PrecisionDialogEntry].pW);
	controls["PrecisionDialogEntry"] = &GI[PrecisionDialogEntry];
	((Gtk::Entry*)GI[PrecisionDialogEntry].pW)->signal_changed().connect(sigc::mem_fun(*this, &glade_extract::on_PrecisionDialogEntry_changed));
	GI[TenButton].classType = "GtkButton";
	GI[TenButton].id = "TenButton";
	refBuilder->get_widget("TenButton", GI[TenButton].pW);
	controls["TenButton"] = &GI[TenButton];
	((Gtk::Button*)GI[TenButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_TenButton_clicked));
	GI[LOGButton].classType = "GtkButton";
	GI[LOGButton].id = "LOGButton";
	refBuilder->get_widget("LOGButton", GI[LOGButton].pW);
	controls["LOGButton"] = &GI[LOGButton];
	((Gtk::Button*)GI[LOGButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_LOGButton_clicked));
	GI[RaiseButton].classType = "GtkButton";
	GI[RaiseButton].id = "RaiseButton";
	refBuilder->get_widget("RaiseButton", GI[RaiseButton].pW);
	controls["RaiseButton"] = &GI[RaiseButton];
	((Gtk::Button*)GI[RaiseButton].pW)->signal_clicked().connect(sigc::mem_fun(*this, &glade_extract::on_RaiseButton_clicked));
	//the_app->run(*CMW);
}
pGEXT glade_extract::getInst(void)
{
	if(argv == NULL)
	{
		// // cout << "Error: intitialize GEXT::argc & GEXT::argv before calling getInst\n";
		exit(EXIT_FAILURE);
	}

	if(pGEXTInstance == NULL) pGEXTInstance = new glade_extract();
	return pGEXTInstance;
}
Gtk::Widget * glade_extract::get(const string & wName)
{
	map<string, glade_info *>::iterator mit = controls.find(wName);
	if (mit != controls.end()) return (*mit).second->getWidget();
	mit = containers.find(wName);
	if (mit != containers.end()) return (*mit).second->getWidget();
	mit = mains.find(wName);
	if (mit != mains.end()) return (*mit).second->getWidget();
	mit = styles.find(wName);
	if (mit != styles.end()) return (*mit).second->getWidget();
	return NULL;
}
bool glade_extract::on_MainWindow_delete_event(GdkEventAny* any_event)
{
	// // cout << "MainWindow delete connected\n";
	return false;
}
void glade_extract::on_MainWindow_size_allocate(Gtk::Allocation & allocation)
{
	// // cout << "MainWindow size connected\n";
}
bool glade_extract::on_MsgDlg_delete_event(GdkEventAny* any_event)
{
	// cout << "MsgDlg delete connected\n";
	return false;
}
void glade_extract::on_MsgDlg_size_allocate(Gtk::Allocation & allocation)
{
	// cout << "MsgDlg size connected\n";
}
bool glade_extract::on_PrecisionDialog_delete_event(GdkEventAny* any_event)
{
	// cout << "PrecisionDialog delete connected\n";
	return false;
}
void glade_extract::on_PrecisionDialog_size_allocate(Gtk::Allocation & allocation)
{
	// cout << "PrecisionDialog size connected\n";
}
bool glade_extract::on_ProgressBar_button_release_event(GdkEventButton* release_event)
{
	// cout << "ProgressBar connected\n";
	return false;
}
bool glade_extract::on_InputBox_key_press_event(GdkEventKey* key_event)
{
	// cout << "InputBox connected\n";
	return false;
	guint k = key_event->keyval;
	switch(k)
	{
	case GDK_KEY_KP_Equal:
	case GDK_KEY_equal: 
								gui->HandleEqualButton();
								break;
	case GDK_KEY_KP_Multiply:
	case GDK_KEY_asterisk:
								gui->HandleTimesButton();
								break;
	case GDK_KEY_KP_Add:
	case GDK_KEY_plus:
								gui->HandlePlusButton();
								break;
	case GDK_KEY_KP_Subtract:
	case GDK_KEY_minus:
								gui->HandleMinusButton();
								break;
	case GDK_KEY_KP_Decimal:
	case GDK_KEY_period:
								gui->HandlePointButton();
								break;
	case GDK_KEY_KP_Divide:
	case GDK_KEY_slash:
								gui->HandleDivideButton();
								break;
	case GDK_KEY_KP_0:
	case GDK_KEY_0:
								gui->HandleNumberButton(0);
								break;
	case GDK_KEY_KP_1:
	case GDK_KEY_1:
								gui->HandleNumberButton(1);
								break;
	case GDK_KEY_KP_2:
	case GDK_KEY_2:
								gui->HandleNumberButton(2);
								break;
	case GDK_KEY_KP_3:
	case GDK_KEY_3:
								gui->HandleNumberButton(3);
								break;
	case GDK_KEY_KP_4:
	case GDK_KEY_4:
								gui->HandleNumberButton(4);
								break;
	case GDK_KEY_KP_5:
	case GDK_KEY_5:
								gui->HandleNumberButton(5);
								break;
	case GDK_KEY_KP_6:
	case GDK_KEY_6:
								gui->HandleNumberButton(6);
								break;
	case GDK_KEY_KP_7:
	case GDK_KEY_7:
								gui->HandleNumberButton(7);
								break;
	case GDK_KEY_KP_8:
	case GDK_KEY_8:
								gui->HandleNumberButton(8);
								break;
	case GDK_KEY_KP_9:
	case GDK_KEY_9:
								gui->HandleNumberButton(9);
								break;
	case GDK_KEY_C:
	case GDK_KEY_c:
								gui->HandleClearButton();
								break;
	default: 
								return false;

	}
	return true;
}
bool glade_extract::on_InputBox_key_release_event(GdkEventKey* key_event)
{
	// cout << "OutputBox connected\n";
	return false;
}

void glade_extract::on_SevenButton_clicked(void)
{
	// cout << "SevenButton connected\n";
	gui->HandleNumberButton(7);
}

void glade_extract::on_EightButton_clicked(void)
{
	// cout << "EightButton connected\n";
	gui->HandleNumberButton(8);
}
void glade_extract::on_NineButton_clicked(void)
{
	// cout << "NineButton connected\n";
	gui->HandleNumberButton(9);
}
void glade_extract::on_ClearButton_clicked(void)
{
	// cout << "ClearButton connected\n";
	gui->HandleClearButton();
}
void glade_extract::on_AllClearButton_clicked(void)
{
	// cout << "AllClearButton connected\n";
	gui->HandleAllClearButton();
}
void glade_extract::on_LNButton_clicked(void)
{
	// cout << "LNButton connected\n";
	gui->HandleLNButton();
}
void glade_extract::on_ExpButton_clicked(void)
{
	// cout << "ExpButton connected\n";
	gui->HandleEXPButton();
}
void glade_extract::on_ATANButton_clicked(void)
{
	// cout << "ATANButton connected\n";
	gui->HandleATANButton();
}
void glade_extract::on_FourButton_clicked(void)
{
	// cout << "FourButton connected\n";
	gui->HandleNumberButton(4);
}
void glade_extract::on_FiveButton_clicked(void)
{
	// cout << "FiveButton connected\n";
	gui->HandleNumberButton(5);
}
void glade_extract::on_SixButton_clicked(void)
{
	// cout << "SixButton connected\n";
	gui->HandleNumberButton(6);
}
void glade_extract::on_TimesButton_clicked(void)
{
	// cout << "TimesButton connected\n";
	gui->HandleTimesButton();
}
void glade_extract::on_DivideButton_clicked(void)
{
	// cout << "DivideButton connected\n";
	gui->HandleDivideButton();
}
void glade_extract::on_SineButton_clicked(void)
{
	// cout << "SineButton connected\n";
	gui->HandleSINButton();
}
void glade_extract::on_CosineButton_clicked(void)
{
	// cout << "CosineButton connected\n";
	gui->HandleCOSButton();
}
void glade_extract::on_TangentButton_clicked(void)
{
	// cout << "TangentButton connected\n";
	gui->HandleTANButton();
}
void glade_extract::on_OneButton_clicked(void)
{
	// cout << "OneButton connected\n";
	gui->HandleNumberButton(1);
}
void glade_extract::on_TwoButton_clicked(void)
{
	// cout << "TwoButton connected\n";
	gui->HandleNumberButton(2);
}
void glade_extract::on_ThreeButton_clicked(void)
{
	// cout << "ThreeButton connected\n";
	gui->HandleNumberButton(3);
}
void glade_extract::on_AddButton_clicked(void)
{
	// cout << "AddButton connected\n";
	gui->HandlePlusButton();
}
void glade_extract::on_MinusButton_clicked(void)
{
	// cout << "MinusButton connected\n";
	gui->HandleMinusButton();
}
void glade_extract::on_MultiplicativeInverseButton_clicked(void)
{
	// cout << "MultiplicativeInverseButton connected\n";
	gui->HandleMultiplicativeInverseButton();
}
void glade_extract::on_SquareButton_clicked(void)
{
	// cout << "SquareButton connected\n";
	gui->HandleSquareButton();
}
void glade_extract::on_SqrtButton_clicked(void)
{
	// cout << "SqrtButton connected\n";
	gui->HandleSquareRootButton();
}
void glade_extract::on_PiButton_clicked(void)
{
	// cout << "PiButton connected\n";
	gui->HandlePiButton();
}
void glade_extract::on_ZeroButton_clicked(void)
{
	// cout << "ZeroButton connected\n";
	gui->HandleNumberButton(0);
}
void glade_extract::on_PointButton_clicked(void)
{
	// cout << "PointButton connected\n";
	gui->HandlePointButton();
}
void glade_extract::on_EqualButton_clicked(void)
{
	// cout << "EqualButton connected\n";
	gui->HandleEqualButton();
}
void glade_extract::on_InvertSignButton_clicked(void)
{
	// cout << "InvertSignButton connected\n";
	gui->HandleAdditiveInverseButton();
}
void glade_extract::on_FactorialButton_clicked(void)
{
	// cout << "FactorialButton connected\n";
	gui->HandleFractorialButton();
}
void glade_extract::on_LDXButton_clicked(void)
{
	// cout << "LDXButton connected\n";
	gui->HandleLDXButton();
}
void glade_extract::on_ChangePrecisionButton_clicked(void)
{
	// cout << "ChangePrecisionButton connected\n";
	gui->HandleChangePrecisionButton();
}
void glade_extract::on_ExitButton_clicked(void)
{
	// cout << "ExitButton connected\n";
	//exit(EXIT_SUCCESS);
	the_app->quit();
}
void glade_extract::on_OKButton_clicked(void)
{
	// cout << "OKButton connected\n";
}
void glade_extract::on_CancelButton_clicked(void)
{
	// cout << "CancelButton connected\n";
	gui->HandlePrecisionDialogCancelButton();
}
void glade_extract::on_ChangeButton_clicked(void)
{
	// cout << "ChangeButton connected\n";
	gui->HandlePrecisionDialogChangeButton();

}
void glade_extract::on_PrecisionDialogEntry_changed(void)
{
	// cout << "PrecisionDialogEntry connected\n";
}
void glade_extract::on_TenButton_clicked(void)
{
	// cout << "TenButton connected\n";
	gui->HandleTenButton();
}
void glade_extract::on_LOGButton_clicked(void)
{
	// cout << "LOGButton connected\n";
	gui->HandleLOGButton();
}
void glade_extract::on_RaiseButton_clicked(void)
{
	// cout << "RaiseButton connected\n";
	gui->HandleRaiseButton();
}

