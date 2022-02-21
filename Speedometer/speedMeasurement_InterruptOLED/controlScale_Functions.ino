/*
  Functions to alter and to print the scale of the speedometer
*/

SCALETYPE setNextScale(SCALETYPE oldScaleSetting) { //given current scale, return next scale. 
  SCALETYPE returnValue;        
  switch (oldScaleSetting) {
    case G: returnValue = O;                        //Attention sequence in case statement must match enum sequence in main program
      break;
    case O: returnValue = S;
      break;
    case S: returnValue = H0;
      break;
    case H0: returnValue = N;
      break;
    case N: returnValue = Z;
      break;
    case Z: returnValue = G;
      break;
  }
  return returnValue;
}

String printScale(SCALETYPE currentScale) {
  String scaleLetter;
  switch (currentScale) {
    case G: scaleLetter = "G";
      break;
    case O: scaleLetter = "O";
      break;
    case S: scaleLetter = "S";
      break;
    case H0: scaleLetter = "H0";
      break;
    case N: scaleLetter = "N";
      break;
    case Z: scaleLetter = "Z";
      break;
  }
  return scaleLetter; 
}
