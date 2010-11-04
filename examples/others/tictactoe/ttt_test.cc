#include "tictactoe.h"
#include <gtkmm/window.h>
#include <gtkmm/main.h>


void
win (TicTacToe *ttt)
{
  g_print ("Yay!\n");
  ttt->clear();
}


int
main (int argc, char *argv[])
{
  Gtk::Main m(argc, argv);

  TicTacToe* ttt = manage( new TicTacToe );
  ttt->tictactoe.connect( sigc::bind (sigc::ptr_fun(&win), ttt) );

  Gtk::Window window;
  window.set_title("Tic-Tac-Toe");
  window.set_border_width(10);
  window.add(*ttt);
  window.show_all_children();

  Gtk::Main::run(window);

  return 0;
}
