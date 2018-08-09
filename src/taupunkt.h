/** \file
 * Taupunktberechnung aus Temperatur und rel. Luftfeuchte.
 *
 * Eingaben:
 *   * Temperatur T [°C]
 *   * rel. Feuchte r [%]
 *
 * Ausgabe:
 *   * Taupunkttemperatur TD [°C]
 *
 * Parameter:
 *   a = 7.5, b = 237.3 fuer T >= 0
 *   a = 7.6, b = 240.7 fuer T < 0 ueber Wasser (Taupunkt)
 *   a = 9.5, b = 265.5 fuer T < 0 ueber Eis (Frostpunkt)
 *
 * Konstanten:
 *   R* = 8314.3 J/(kmol*K) (universelle Gaskonstante)
 *   mw = 18.016 kg/kmol (Molekulargewicht des Wasserdampfes)
 * 
 * Gleichungen:
 *   SDD(T) = 6.1078 * 10^((a*T)/(b+T))
 *   DD(r,T) = r/100 * SDD(T)
 *   TD(r,T) = b*v/(a-v) mit v(r,T) = log10(DD(r,T)/6.1078)
 */
#ifndef _TAUPUNKT_H_
#define _TAUPUNKT_H_

/** Data to calculate the taupunkt.
 */
struct Tp {
	float a;    //!< Temperaturabh. Konstante, siehe oben
	float b;    //!< Temperaturabh. Konstante, siehe oben
	float r;    //!< [in] relative Luftfeuchte
	float T;    //!< [in] Temperatur [°C]
	float DD;   //!< Dampfdruck [hPa]
	float SDD;  //!< Saettigungsdampfdruck [hPa]
	float TD;   //!< [out] Taupunkttemperatur [°C]
};

void Tp_Init(struct Tp* me, float T, float r);
void Tp_Update_r(struct Tp* me, float r);
void Tp_Update_T(struct Tp* me, float T);

#endif
