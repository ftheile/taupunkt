/** \file
 * Taupunktberechnung aus Temperatur und rel. Luftfeuchte.
 */
#include "taupunkt.h"
#include <math.h>

// Konstanten:
#define R_STAR 8314.3   /**< Universelle Gaskonstante [J / (kmol*K)] */
#define MW       18.016 /**< Molekulargewicht des Wasserdampfes [kg / kmol] */

/** Update interne Konstanten.
 * \param me Taupunkt data
 */
static void Update_a_b(struct Tp* me)
{
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

}

/** Berechnung Saettigungsdampfdruck SDD(T)
 * \param me Taupunkt data
 */
static void Calc_SDD(struct Tp* me)
{
	me->SDD = 6.1078 * pow(10, (me->a * me->T / (me->b + me->T)));
}

/** Berechnung Dampfdruck DD(r, T)
 * \param me Taupunkt data
 */
static void Calc_DD(struct Tp* me)
{
	me->DD = me->r / 100.0 * me->SDD;
}

/** Berechnung Taupunkttemperatur TD(r, T)
 * \param me Taupunkt data
 */
static void Calc_TD(struct Tp* me)
{
	float v = log10(me->DD / 6.1078);
	me->TD = me->b * v / (me->a - v);
}

/** Initialisierung Taupunktberechnung.
 * \param me Taupunkt data
 * \param T Temperatur in °C
 * \param r rel. Feuchte
 */
void Tp_Init(struct Tp* me, float T, float r)
{
	if (me) {
		me->T = T;
		me->r = r;
		Update_a_b(me);
		Calc_SDD(me);
		Calc_DD(me);
		Calc_TD(me);
	}
}

/** Update rel. Feuchte.
 * Neuberechnung des Taupunkts nach Aenderung der rel. Feuchte.
 * \param me Taupunkt data
 * \param r rel. Feuchte
 */
void Tp_Update_r(struct Tp* me, float r)
{
	if (me && (me->r != r)) {
		me->r = r;
		Calc_DD(me);
		Calc_TD(me);
	}
}

/** Update Temperatur.
 * Neuberechnung des Taupunkts nach Aenderung der Temperatur.
 * \param me Taupunkt data
 * \param T Temperatur in °C
 */
void Tp_Update_T(struct Tp* me, float T)
{
	if (me && (me->T != T)) {
		me->T = T;
		Update_a_b(me);
		Calc_SDD(me);
		Calc_DD(me);
		Calc_TD(me);
	}
}
