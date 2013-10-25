#include "emu/odmbdev/utils.h"

#include "xcept/Exception.h"

#include <bitset>
#include <limits>

/*****************************************************************************
 * Utility functions
 *****************************************************************************/

using namespace std;

namespace emu{ namespace odmbdev{


unsigned int binaryStringToUInt(const std::string& s)
{
  return  static_cast<unsigned int>( bitset<numeric_limits<unsigned long>::digits>(s).to_ulong() );
}


std::string withoutSpecialChars(const std::string& s)
{
  std::string sout = s;
  char chars[10] = " /#\t\n";
  for (int i = 0; i < 5; ++i)
  {
    char c = chars[i];
    while(sout.find(c,0) != std::string::npos) sout.erase(sout.find(c,0),1);
  }
  return sout;
}


int getFormValueInt(const string& form_element, xgi::Input *in)
{
  const cgicc::Cgicc cgi(in);
  int form_value;
  cgicc::const_form_iterator name = cgi.getElement(form_element);
  if(name != cgi.getElements().end())
  {
    form_value = cgi[form_element]->getIntegerValue();
  }
  else
  {
    XCEPT_RAISE( xcept::Exception, "Form element, " + form_element + ", was not found." );
  }
  //cout<<"\""<<form_element<<"\"->"<<form_value<<endl;
  return form_value;
}


int getFormValueIntHex(const string& form_element, xgi::Input *in)
{
  const cgicc::Cgicc cgi(in);
  int form_value;
  cgicc::const_form_iterator name = cgi.getElement(form_element);
  if(name != cgi.getElements().end())
  {
    stringstream convertor;
    string hex_as_string = cgi[form_element]->getValue();
    convertor << hex << hex_as_string;
    convertor >> form_value;
  }
  else
  {
    XCEPT_RAISE( xcept::Exception, "Form element, " + form_element + ", was not found." );
  }
  //cout<<"\""<<form_element<<"\"->"<<form_value<<endl;
  return form_value;
}


float getFormValueFloat(const string& form_element, xgi::Input *in)
{
  const cgicc::Cgicc cgi(in);
  float form_value;
  cgicc::const_form_iterator name = cgi.getElement(form_element);
  if(name != cgi.getElements().end())
  {
    form_value = cgi[form_element]->getDoubleValue();
  }
  else
  {
    XCEPT_RAISE( xcept::Exception, "Form element, " + form_element + ", was not found." );
  }
  //cout<<"\""<<form_element<<"\"->"<<form_value<<endl;
  return form_value;
}


string getFormValueString(const string& form_element, xgi::Input *in)
{
  const cgicc::Cgicc cgi(in);
  string form_value;
  cgicc::const_form_iterator name = cgi.getElement(form_element);
  if(name != cgi.getElements().end())
  {
    form_value = cgi[form_element]->getValue();
  }
  else
  {
    XCEPT_RAISE( xcept::Exception, "Form element, " + form_element + ", was not found." );
  }
  //cout<<"\""<<form_element<<"\"->"<<form_value<<endl;
  return form_value;
}

string GetLogFileName(unsigned int port_number) {
  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  char year[10], month[10], day[10], hour[10], minute[10], second[10];
  strftime(year, 10, "%g", timeinfo ); strftime(month, 10, "%m", timeinfo ); strftime(day, 10, "%d", timeinfo ); 
  strftime(hour, 10, "%H", timeinfo ); strftime(minute, 10, "%M", timeinfo ); strftime(second, 10, "%S", timeinfo );
  string file_name("/data/odmb/logfiles/odmb_log_");
  char time_stamp[100];
  sprintf (time_stamp,"%s%s%s_%s%s%s_p%d.log",year,month,day,hour,minute,second,port_number);
  file_name+=time_stamp;
  return file_name;
}


}} // namespaces

