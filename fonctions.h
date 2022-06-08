

int x_absolute(int x_centre, int x_relatif){
    return(x_relatif+x_centre);
}

int y_absolute(int y_centre, int y_relatif){
    return(y_relatif+y_centre);
}

float calculAbscisse(float secondes)
{
    float longueurAbscisse;
    float angle = (2 * M_PI * secondes) / 365;
    longueurAbscisse = cos(angle);
    return longueurAbscisse;
}

float calculOrdonnee(float secondes)
{
    float longueurOrdonne;
    float angle = (2 * M_PI * secondes) / 365;
    longueurOrdonne = sin(angle);
    return longueurOrdonne;
}