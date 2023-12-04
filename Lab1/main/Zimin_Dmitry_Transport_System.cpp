#include "Utilites.h"
#include "Station.h"
#include "Pipe.h"
#include "GTS.h"
#include "Menu.h"
#include <format>
#include <chrono>

using namespace std;
using namespace chrono;


// Основной цикл
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    redirect_stream_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("Logs/log_" + time + ".txt");

    if (logfile) cerr_out.redirect(logfile);

    GTS GasSystem;
    MainMenu(GasSystem);
}
