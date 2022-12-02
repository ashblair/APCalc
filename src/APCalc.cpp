#include "stdafx.h"
#include "mfloat.h"
#include "widgets.h"
#include "GUI.h"

int main (int argc, char **argv)
{
    GEXT::argc = argc;
    GEXT::argv = argv;

    pGEXT pG = GEXT::getInst();
    pGUI gui = new GUI();

	GEXT::the_app->run(*GEXT::CMW);
    delete gui;
    exit(EXIT_SUCCESS);
}
