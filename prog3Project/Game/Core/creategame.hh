#ifndef CREATEGAME_HH
#define CREATEGAME_HH
#include "../Game/Graphics/mainwindow.hh"
namespace Junttarit {
/**
 * @brief creategame
 * @param w MainWindow pointer to give to the city, so the city can execute its functions according to game logic.
 *
 * @return shared_ptr to the city instance, but it's not utilized.
 */
std::shared_ptr<Interface::ICity> creategame(std::shared_ptr<Junttarit::MainWindow> w);


};


#endif // CREATEGAME_HH
