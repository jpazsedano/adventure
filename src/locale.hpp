/**
 * En este módulo nos encargams la gestión de traducciones. Básicamente
 * permite la carga de textos en diferentes idiomas y su traducción
 * utilizando una referencia universal que es traducida al idioma
 * seleccionado.
 * 
 * @author Javier Paz Sedano
 */

#include <string>
#include <map>

#ifndef ADVENTURE_LOCALE_H
#define ADVENTURE_LOCALE_H

using namespace std;

/**
 * La clase debe inicializarse con el directorio donde se encuentran los
 * ficheros de localización y éstos deben estar nombrados '<lang>.cfg' para
 * que el código los cargue.
 */
class Localization {

    map<string, string> locale;
    string localeFolder;

    public:
      string lang;

      Localization(string);

      void loadLanguage(string);
      string getLocale(string text);
};

#endif // ADVENTURE_LOCALE_H
