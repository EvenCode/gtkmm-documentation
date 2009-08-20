#include <gtkmm/main.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menu.h>
#include <gtkmm/stock.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/separatortoolitem.h>

#include <cstdio>
//#include <glib.h>
//#include <gdk/gdk.h>
//#include <gtk/gtk.h>

class MainWindowClass 
  : public Gtk::Window
{
public:
    MainWindowClass();
    virtual ~MainWindowClass();

private:
  
    void quit_pressed_cb();
    void toolbar_cb(const char*);
    void toolbar_item_cb(Gtk::Toolbar* toolbar, Gtk::ToolbarStyle style);
};

void 
MainWindowClass::toolbar_cb(const char* c)
{
    printf("toolbar_cb : %s\n", c);
}

void 
MainWindowClass::toolbar_item_cb(Gtk::Toolbar* toolbar,
                                  Gtk::ToolbarStyle style)
{
    toolbar->set_toolbar_style(style);
}

MainWindowClass::MainWindowClass()
{
    using namespace Gtk::Menu_Helpers;

    set_size_request(350, -1);
  
    Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox(false, 0));
    add(*vbox);

    Gtk::MenuBar* menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK);
    
    Gtk::Toolbar* toolbar = Gtk::manage(new Gtk::Toolbar());
    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK);

    Gtk::Button* button = Gtk::manage(new Gtk::Button("Quit"));
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindowClass::quit_pressed_cb));
    vbox->pack_start(*button, Gtk::PACK_SHRINK);


    Gtk::ToolButton* toolbutton = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    toolbutton->set_label("New Item");
    toolbutton->set_is_important();
    toolbar->append(*toolbutton, sigc::bind( sigc::mem_fun( 
                                             *this, &MainWindowClass::toolbar_cb),
                                             "New Item"));

    toolbutton = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::OPEN));
    toolbutton->set_label("Open Item");
    toolbar->append(*toolbutton, sigc::bind( sigc::mem_fun( *this, &MainWindowClass::toolbar_cb), "Open Item"));

    toolbutton = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE));
    toolbutton->set_label("Save Item");
    toolbar->append(*toolbutton, sigc::bind( sigc::mem_fun(*this, &MainWindowClass::toolbar_cb), "Save Item"));

    Gtk::SeparatorToolItem* separator = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*separator);

    toolbutton = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::UNDO));
    toolbutton->set_label("Undo Item");
    toolbar->append(*toolbutton, sigc::bind( sigc::mem_fun(*this, &MainWindowClass::toolbar_cb), "Undo Item"));

    toolbutton = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::REDO));
    toolbutton->set_label("Redo Item");
    toolbar->append(*toolbutton, sigc::bind( sigc::mem_fun(*this, &MainWindowClass::toolbar_cb), "Redo Item"));

    separator = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*separator);

    Gtk::ToggleToolButton* togglebutton = Gtk::manage(new Gtk::ToggleToolButton(Gtk::Stock::CONVERT));
    togglebutton->set_label("Convert Toggle");
    toolbar->append(*togglebutton, sigc::bind( sigc::mem_fun(*this, &MainWindowClass::toolbar_cb), "Convert Toggle"));


    menubar->items().push_back(MenuElem("Options"));
    Gtk::MenuItem* pMenuItem = &(menubar->items().back());

    Gtk::Menu* menu = Gtk::manage(new Gtk::Menu());
    pMenuItem->set_submenu(*menu);

    menu->items()
        .push_back(MenuElem("Icons", sigc::bind(sigc::mem_fun(*this, &MainWindowClass::toolbar_item_cb), toolbar, Gtk::TOOLBAR_ICONS)));
    menu->items()
        .push_back(MenuElem("Text", sigc::bind(sigc::mem_fun(*this, &MainWindowClass::toolbar_item_cb), toolbar, Gtk::TOOLBAR_TEXT)));
    menu->items()
        .push_back(MenuElem("Both", sigc::bind(sigc::mem_fun(*this, &MainWindowClass::toolbar_item_cb), toolbar, Gtk::TOOLBAR_BOTH)));
    menu->items()
        .push_back(MenuElem("Both (horiz)", sigc::bind(sigc::mem_fun(*this, &MainWindowClass::toolbar_item_cb), toolbar,  Gtk::TOOLBAR_BOTH_HORIZ)));
    
    menu->items()[0].activate();

    show_all_children();
}

MainWindowClass::~MainWindowClass()
{}

void MainWindowClass::quit_pressed_cb()
{
    hide();
}

int main(gint argc, gchar **argv)
{
    Gtk::Main kit(argc, argv);
    MainWindowClass main_window;
  
    Gtk::Main::run(main_window);

    return 0;
}
