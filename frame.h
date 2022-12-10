/*

Frame Lib


*/
#include <string>
#include <sstream>
#include <iomanip>

#pragma once


class frame
{
    std::string val;
    char borderChar;


public:

    enum class ChoiceOri {left,right,center};

    ChoiceOri thisChoice = ChoiceOri::left; //okay its public

    enum class ChoiceBorder {defaultB,singleL,doubleL,shaded};

    ChoiceBorder thisBorder = ChoiceBorder::defaultB;

    frame(std::string valIn = "", char borderIn = '*')
        :
        val(valIn),
        borderChar(borderIn)
    {

    }

    void set_border(char b)
    {
        borderChar = b;
    }

    char get_border()
    {
        return borderChar;
    }







    friend std::istream & operator>>(std::istream & in, frame & r)
    {

        //takes care of reading in whitespace
        if (in.peek() == '\n')
        {
            in.ignore();
        }


        std::getline(in,r.val);

        return in;


    }

    friend std::ostream & operator<<(std::ostream & out,
                                     const frame & r)
    {
        std::string a = "";
        std::string largestWord = "";

        std::string main = r.val;

        std::istringstream iss;

        // std::string borderStringSide = r.borderChar;
        std::string borderStringSide(1, r.borderChar);

        iss.str(main);

        do //first pass
        {
            iss >> a;

            if(a.length() > largestWord.length())
            {
                largestWord = a;

            }

        }
        while (!iss.eof());

        iss.clear();
        iss.str (main);

        std::string borderString;

        switch(r.thisBorder)
        {

        case ChoiceBorder::defaultB:

            //out << r.borderChar <<" ";
            borderString =
                std::string(largestWord.length()+4, r.borderChar);
            out << borderString << '\n';

            break;

        case ChoiceBorder::singleL:
            borderString = "+"
                           + std::string(largestWord.length()+2, '-') + "+";
            out << borderString << '\n';
            borderStringSide = "|";


            break;

        case ChoiceBorder::doubleL:
            borderString = "+"
                           + std::string(largestWord.length()+4, '=') + "+";
            out << borderString << '\n';
            borderStringSide = "||";

            break;

        case ChoiceBorder::shaded:
            borderString = "+"
                           + std::string(largestWord.length()+2, '-') + "+";
            out << borderString << '\n';
            borderStringSide = "|";

            break;
        }

        do
        {
            iss >> a;

            out << borderStringSide <<" ";

            switch(r.thisChoice)
            {

            case ChoiceOri::left:

                out << std::left
                    << std::setw(static_cast<int>(largestWord.length()))
                    << a;
                break;

            case ChoiceOri::right:

                out  << std::right
                     << std::setw(static_cast<int>(largestWord.length()))
                     << a;
                break;

            case ChoiceOri::center:
                out << std::setw(static_cast<int>(
                                     (largestWord.length()-a.length())/2))
                    << "" << a
                    << std::setw(static_cast<int>(
                                     largestWord.length()-a.length()
                                     -(largestWord.length()-a.length())/2))
                    << "";
                break;
            }

            if( r.thisBorder == ChoiceBorder::shaded)
            {
                out << " "<< borderStringSide << "*" << '\n';
            }
            else
            {
                out << " "<< borderStringSide  << '\n';
            }


        }
        while (!iss.eof());

        if( r.thisBorder == ChoiceBorder::shaded)
        {
            out << borderString << "*" << '\n';
            out << std::string(largestWord.length()+4, '*') << "*" << '\n';
        }
        else
        {
            out << borderString <<'\n';
        }



        return out;

    }

};
