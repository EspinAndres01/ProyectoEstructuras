#include "WebOpener.h"

#ifdef _WIN32 // Para sistemas Windows
void WebOpener::abrirPaginaWeb(const std::string& url) {
    std::string comando = "start " + url;
    system(comando.c_str());
}
#else // Para sistemas no Windows (por ejemplo, Linux)
void WebOpener::abrirPaginaWeb(const std::string& url) {
    std::string comando = "xdg-open " + url;
    system(comando.c_str());
}
#endif