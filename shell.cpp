#include <iostream>
#include <string>

#include "parser.h"

int main( int argc , char **argv )
{
  while(1) {
	char inputC;
	std::string inputS;
	
	std::cout << "?- ";
	
	do{
	  inputC = getchar();
	  
	  if(inputC != '\n') {
		inputS = inputS + inputC;
	  }
	  else {
		if(inputS[inputS.size()-1] == ';' || inputS[inputS.size()-1] == ',') {
		  std::cout << "|   ";
		}
		else if(inputS.size()==0) {
		  break;
		}
		else {
		  try{
			Scanner s(inputS);  
			Parser p(s);
            p.buildExpression();
			string result = p.getExpressionResult();
			std::cout << result << std::endl;
          }			
		  catch (std::string & msg) {
            std::cout << msg << std::endl;
          }
		  break;
		}
	  }
	} while(inputS != "halt.");
	
	if(inputS == "halt.") break;
  }
}
