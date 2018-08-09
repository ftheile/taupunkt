/** \file
 * Taupunktberechnung aus Temperatur und rel. Luftfeuchte.
 */
#include "taupunkt.h"
#include <math.h>
#include <stdio.h>

// Konstanten:
#define R_STAR 8314.3   /**< Universelle Gaskonstante [J / (kmol*K)] */
#define MW       18.016 /**< Molekulargewicht des Wasserdampfes [kg / kmol] */

#define RF_MIN    0.0
#define RF_MAX  100.0

/** Berechnung Saettigungsdampfdruck SDD(T)
 * \param me Taupunkt data
 */
static void Calc_SDD(struct Tp* me)
{
	// Update Konstanten:
	if (me->T >= 0.0) {
		me->a = 7.5;
		me->b = 237.3;
	} else {
		// ??? Ueber Wasser, ueber Eis ???
		// fuer T < 0 ueber Wasser (Taupunkt):
		me->a = 7.6;
		me->b = 240.7;

		// fuer T < 0 ueber Eis (Frostpunkt):
//		me->a = 9.5;
//		me->b = 265.5;
	}
	me->SDD = 6.1078 * pow(10, me->a * me->T / (me->b + me->T));
}

/** Berechnung Taupunkttemperatur TD(r, T)
 * \param me Taupunkt data
 */
static void Calc_TD(struct Tp* me)
{
	float DD = me->r / 100.0 * me->SDD;
	float v = log10(DD / 6.1078);
	me->TD = me->b * v / (me->a - v);
}

/** Initialisierung Taupunktberechnung.
 * \param me Taupunkt data
 * \param T Temperatur in °C
 * \param r rel. Feuchte
 * \retval true OK
 * \retval false Fehler (me oder r ungueltig)
 */
bool Tp_Init(struct Tp* me, float T, float r)
{
	if (me && (r > RF_MIN) && (r <= RF_MAX)) {
		me->T = T;
		me->r = r;
		Calc_SDD(me);
		Calc_TD(me);
		return true;
	} else {
		return false;
	}
}

/** Update rel. Feuchte.
 * Neuberechnung des Taupunkts nach Aenderung der rel. Feuchte.
 * \param me Taupunkt data
 * \param r rel. Feuchte [%]
 * \retval true OK
 * \retval false Fehler (me oder r ungueltig)
 */
bool Tp_Update_r(struct Tp* me, float r)
{
	if (me && (r > RF_MIN) && (r <= RF_MAX)) {
		if (me->r != r) {
			me->r = r;
			Calc_TD(me);
		}
		return true;
	} else {
		return false;
	}
}

/** Update Temperatur.
 * Neuberechnung des Taupunkts nach Aenderung der Temperatur.
 * \param me Taupunkt data
 * \param T Temperatur [°C]
 * \retval true OK
 * \retval false Fehler (me ungueltig)
 */
bool Tp_Update_T(struct Tp* me, float T)
{
	if (me) {
		if (me->T != T) {
			me->T = T;
			Calc_SDD(me);
			Calc_TD(me);
		}
		return true;
	} else {
		return false;
	}
}

/** Ausgabe der Berechnung.
 * \param me Taupunkt data
 */
void Tp_Print(const struct Tp* me)
{
	if (me) {
		printf("TD(%.1f°C, %.1f%%) = %.1f°C\n", me->T, me->r, me->TD);
	}
}
