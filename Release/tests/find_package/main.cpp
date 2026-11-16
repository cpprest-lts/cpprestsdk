#include <cpprest/http_client.h>
#include <cpprest/json.h>
#if !defined(CPPREST_EXCLUDE_WEBSOCKETS)
#include <cpprest/ws_client.h>
#endif
#include <clocale>
#include <iostream>

static bool early_locale_set = false;

// With a static cpprest, this initializer runs before cpprest's own. Parsing JSON in a locale other than "C"
// makes cpprest create its "C" locale during another translation unit's static initialization
static const web::json::value early = []()
{
    early_locale_set = std::setlocale(LC_ALL, "C.UTF-8") || std::setlocale(LC_ALL, "en_US.UTF-8");
    return web::json::value::parse(U("{\"first\":1.5}"));
}();

int main()
{
    if (!early_locale_set)
    {
        std::cerr << "Unable to set a locale other than \"C\"" << std::endl;
        return 1;
    }

    // Constructing the clients links the HTTP client and the websocket client, and with them OpenSSL
    web::http::client::http_client client(U("https://localhost/"));
#if !defined(CPPREST_EXCLUDE_WEBSOCKETS)
    web::websockets::client::websocket_client ws;
#endif
    // Parsing JSON again checks that cpprest's "C" locale is still valid after cpprest's own initializers have run.
    // Both parses include a number, because on Windows cpprest uses its "C" locale only for numbers
    std::cout << utility::conversions::to_utf8string(web::json::value::parse(U("{\"second\":1.5}")).serialize())
              << std::endl;
}
