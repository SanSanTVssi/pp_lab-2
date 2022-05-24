//
//  Constants.h
//  PP_lab2
//
//  Created by AAI on 23.05.2022.
//

#ifndef Constants_h
#define Constants_h

#include <math.h>

const double A = -M_PI;
const double B = M_PI;
const int N = 8;
const double H = (B - A) / N;

#define tableHorizontalLine \
" _______________________________________________________________________________________ \n"

#define tableHorizontalLine2 \
"|___|___________|_______________________|_______________________|_______________________|\n"

#define FUNCTION1 "cos^2(x)+sin(x)"
#define FUNCTION2 "sin^2(x)*(1+cos(x))"
#define FUNCTION3 "sin(x)*(1+cos^2(x))"


#endif /* Constants_h */
