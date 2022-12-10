#include <iostream>
#include <fstream>

#include "frame.h"

using namespace std;


ofstream openOutputfile();
void closeOutputFile(ofstream & file);
void mainframe();


int main(void)
{

    bool run = true;
    char in;

    cout << "Frame Project:\n";

    do
    {
        mainframe();

        cout << "\nPress q to quit, any other char to continue\n";
        cin >> in;

        if(in == 'q')
        {
            run = false;
        }



    }while(run);

    return 0;
}

void mainframe()
{
    frame source;
    //frame mainFrame;

    char framechoice = '1';
    char indentchoice = '4';
    char choice = '1';
    char choice2 = '0';
    char borderChoice = '*'; //default

    string savename = "saveOp.txt";

    ifstream save_fileIn;


    ofstream outputfile;




    save_fileIn.open(savename);

    if (!save_fileIn)
    {
        save_fileIn.close();
        save_fileIn.clear();

        cerr << "Could not read in save file, A new save file will be\n"
             "made after a getting settings for a frame";

    }
    else
    {

        //save_fileIn >> ws;

        save_fileIn >> framechoice;
        save_fileIn >> indentchoice;
        save_fileIn >> choice;
        save_fileIn >> choice2;
        save_fileIn >> borderChoice;

        //save_fileIn >> ws;

        /*
        cout << framechoice << "\n";
        cout << indentchoice<< "\n";
        cout << choice<< "\n";
        cout << choice2<< "\n";
        cout << borderChoice<< "\n";
        */

        save_fileIn.close();
        save_fileIn.clear();

    }


    char y;
    cout << "Edit/create options executing program?\n"
         "Press y, otherwise press any key\n"
         "to run program based on previous settings\n";
    cin >> y;
    if(y == 'y')
    {
        cout << "Press 1 for single line frame\n"
             "Press 2 double line frame\n"
             "Press 3 for shaded line frame\n"
             "Press 4 for custom frame from one char\n";


        cin >> framechoice;

        if(framechoice == '4')
        {
            cout << "Enter a char for it's border: ";
            cin >> borderChoice;
        }

        cout << "Press 1 for Left indentation\n"
             "Press 2 for Right indentation\n"
             "Press 3 for Centered indentation\n";


        cin >> indentchoice;

        cout << "Press 1 to enter phrases from file,"
             << " any other number to input manually: ";

        cin >> choice;

        cout << "Press 1 to enter print into a file,"
             << " any other number to print onto screen: ";

        cin >> choice2;
    }

    switch(framechoice)
    {
    case '1':
        source.thisBorder = frame::ChoiceBorder::singleL;
        break;

    case '2':
        source.thisBorder = frame::ChoiceBorder::doubleL;
        break;

    case '3':
        source.thisBorder = frame::ChoiceBorder::shaded;
        break;
    case '4':

        source.thisBorder = frame::ChoiceBorder::defaultB;
        source.set_border(borderChoice);

        break;


    }

    switch(indentchoice)
    {
    case '1':
        source.thisChoice = frame::ChoiceOri::left;
        break;

    case '2':
        source.thisChoice = frame::ChoiceOri::right;
        break;

    case '3':
        source.thisChoice = frame::ChoiceOri::center;
        break;

    default:
        source.thisChoice = frame::ChoiceOri::left;
        break;
    }

    if(choice2 == '1')
    {
        outputfile = openOutputfile();
    }


    if(choice == '1')
    {
        ifstream data_file;
        string fname = "";

        cout << "what's the name of input file?  ";
        cin >> fname;
        // }
        data_file.open(fname);

        while (!data_file)
        {
            data_file.close();
            data_file.clear();
            cerr << "\n\aCould not open file '" << fname << "'!\n\n";
            cout << "what's the name of input file?  ";
            getline(cin, fname);
            data_file.open(fname);
        }

        /*
        if(choice2 == '1')
        {
            outputfile = openOutputfile();
        }
        */

        data_file >> ws;

        while(!data_file.eof())
        {

            frame tempy = source;

            if(choice2 == '1')
            {
                data_file >> tempy;

                outputfile << tempy;

                data_file >> ws;

            }
            else
            {
                data_file >> tempy;

                cout << tempy;

                data_file >> ws;
            }

        }

        //closeOutputFile(outputfile);
        data_file.clear();
        data_file.close();
    }
    else if(choice != '1')
    {

        if(choice2 == '1')
        {
            cout << "Enter Phrase : ";
            frame k = source;

            cin >> k;

            outputfile << k;
        }
        else
        {
            cout << "Enter Phrase: ";
            frame k = source;

            cin >> k;

            cout << k;

        }

    }

    closeOutputFile(outputfile);

    ofstream save_fileOut;

    save_fileOut.open(savename,std::ofstream::trunc);

    /*
           cout << framechoice << "\n";
           cout << indentchoice<< "\n";
           cout << choice<< "\n";
           cout << choice2<< "\n";
           cout << borderChoice<< "\n";
     */

    save_fileOut << framechoice;
    save_fileOut << indentchoice;
    save_fileOut << choice;
    save_fileOut << choice2;
    save_fileOut << borderChoice;

    save_fileOut.close();
    save_fileOut.clear();



}


ofstream openOutputfile()
{
    ofstream file;
    string fname;
    cout << "What should the Output file name be?  ";
    //getline(cin, fname);
    cin >> fname;
    file.open(fname);


    while (!file)
    {
        file.close();
        file.clear();
        cout << "\nCannot write to '" << fname
             << "'!!\a\n\nPlease choose "
             "another name (and/or location):  ";
        //getline(cin, fname);
        cin >> fname;
        file.open(fname);
    }

    return file;


}

void closeOutputFile(ofstream & file)
{
    file.close();
    file.clear();

}











