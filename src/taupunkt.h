/** \file
 * Taupunktberechnung.
 * Eingabe:
 *   * Temperatur T
 *   * rel. Feuchte r
 *
 * Ausgabe:
 *   * Taupunkttemperatur TD
 *
 * Parameters:
 *   a = 7.5, b = 237.3 für T >= 0
 *   a = 7.6, b = 240.7 für T < 0 über Wasser (Taupunkt)
 *   a = 9.5, b = 265.5 für T < 0 über Eis (Frostpunkt)
 * 
 * R* = 8314.3 J/(kmol*K) (universelle Gaskonstante)
 * mw = 18.016 kg/kmol (Molekulargewicht des Wasserdampfes)
 * AF = absolute Feuchte in g Wasserdampf pro m3 Luft
 * 
 * Equations:
 *   SDD(T) = 6.1078 * 10^((a*T)/(b+T))
 *   DD(r,T) = r/100 * SDD(T)
 *   r(T,TD) = 100 * SDD(TD) / SDD(T)
 *   TD(r,T) = b*v/(a-v) mit v(r,T) = log10(DD(r,T)/6.1078)
 *   AF(r,TK) = 10^5 * mw/R* * DD(r,T)/TK; AF(TD,TK) = 10^5 * mw/R* * SDD(TD)/TK
 *
 */
#ifndef _TAUPUNKT_H_
#define _TAUPUNKT_H_

/** Data to calculate the taupunkt.
 */
struct Tp {
	float a;    //!< Temperaturabh. Konstante, siehe oben
	float b;    //!< Temperaturabh. Konstante, siehe oben
	float r;    //!< [in] relative Luftfeuchte
	float T;    //!< [in] Temperatur in °C
	float TK;   //!< Temperatur in Kelvin(TK = T + 273.15)
	float DD;   //!< Dampfdruck in hPa
	float SDD;  //!< Sättigungsdampfdruck in hPa
	float TD;   //!< [out] Taupunkttemperatur in °C
};

void Tp_Init(struct Tp* me, float T, float r);
void Tp_Update_r(struct Tp* me, float r);
void Tp_Update_T(struct Tp* me, float T);

#endif
