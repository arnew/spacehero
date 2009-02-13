/** @file local.h
 * @brief Globale Konstanten und Strukturen.
 */

#ifndef LOCAL_H
#define LOCAL_H

#define YEARINSECONDS 365*24*60*60.0
#define TIMESCALE 1400000.0*YEARINSECONDS /* -> so viele Sekunden werden pro Schritt berechnet */
#define TIMESTEP 0.02 /* Sekunden zwischen zwei Berechnungen */

#define GRAVKONST 6.67428e-11
#define SUNMASS 1.9891e30
#define LJ 9.461e15
#define WIDTHINMETERS (600000.0*LJ)
/*#define WIDTHINMETERS 56766e17*/
#define WIDTHINMETERS2 3222378756.0e34

//#define SUNGRAV 13275810348.0e10
#define SUNGRAV (GRAVKONST*SUNMASS)
#define SUNGRAVTIME 5861323371883392.0e18
#define SUNGRAVTIMEWIDTH (SUNGRAVTIME/WIDTHINMETERS2)
//#define SUNGRAVTIMEWIDTH 1.81894303e-10

/* maximale Anzahl an... */ 
#define MAX_GALAXIES 50
#define MAX_PUT_HOLES 10
#define MAX_LEVEL_HOLES 50
#define MAX_STARS 2000

#define ORTHOGONAL 56345
#define PERSPECTIVE 34523

#define HOLESMALLMASS 8.0e11
#define HOLEMEDIUMMASS HOLESMALLMASS*3.0
#define HOLELARGEMASS HOLESMALLMASS*5.0
#define MAXSTARTRESERVE MAX_PUT_HOLES*HOLESMALLMASS

#define MAXTIME 1000 /* in Timesteps */

#define BULGESIZE 0.015f
#define STARSIZE 0.0028f
#define HOLESIZE 0.018f

#define VORN 300
#define SPEED 0
#endif
