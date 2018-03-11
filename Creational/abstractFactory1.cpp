/*
 Copyright (C) 2011 Radek Pazdera

 Abstract factory pattern provides a way to encapsulate a group of individual
 factories that have a common theme without specifying their concrete classes.
 In normal usage, the client software creates a concrete implementation of the
 abstract factory and then uses the generic interface of the factory to create
 the concrete objects that are part of the theme. The client doesn't know
 (or care) which concrete objects it gets from each of these internal factories,
 since it uses only the generic interfaces of their products.
 This pattern separates the details of implementation of a set of objects from
 their general usage and relies on object composition, as object creation is
 implemented in methods exposed in the factory interface

 This makes a class independent of how its objects are created (which concrete
 classes are instantiated). A class can be configured with a factory object,
 which it uses to create objects, and even more, the factory object can be
 exchanged at run-time.
 */
#include <iostream>
#include <string>

class Window
{
    protected:
        int width;
        int height;
        std::string toolkit;
        std::string type;
        Window(std::string usedToolkit, std::string windowType)
            : toolkit(usedToolkit), type(windowType) {}
    public:
        std::string getToolkit() { return toolkit; }
        std::string getType() { return type; }
};

class GtkToolboxWindow : public Window
{
    public:
        GtkToolboxWindow() : Window("Gtk", "ToolboxWindow") {}
};

class GtkLayersWindow : public Window
{
    public:
        GtkLayersWindow() : Window("Gtk", "LayersWindow") {}
};

class GtkMainWindow : public Window
{
    public:
        GtkMainWindow() : Window("Gtk", "MainWindow") {}
};

class QtToolboxWindow : public Window
{
    public:
        QtToolboxWindow() : Window("Qt", "ToolboxWindow") {}
};

class QtLayersWindow : public Window
{
    public:
        QtLayersWindow() : Window("Qt", "LayersWindow") {}
};

class QtMainWindow : public Window
{
    public:
        QtMainWindow() : Window("Qt", "MainWindow") {}
};


/* Abstract Factory */
class UIFactory
{
    public:
        virtual Window* getToolboxWindow() = 0;
        virtual Window* getLayersWindow()  = 0;
        virtual Window* getMainWindow()    = 0;
};

/* Factory for Gtk toolkit */
class GtkUIFactory : public UIFactory
{
    public:
        Window* getToolboxWindow()  { return new GtkToolboxWindow(); }
        Window* getLayersWindow()   { return new GtkLayersWindow(); }
        Window* getMainWindow()     { return new GtkMainWindow(); }
};

/* Factory for Qt toolkit */
class QtUIFactory : public UIFactory
{
    public:
        Window* getToolboxWindow()  { return new QtToolboxWindow(); }
        Window* getLayersWindow()   { return new QtLayersWindow(); }
        Window* getMainWindow()     { return new QtMainWindow(); }
};

int main()
{
    UIFactory* ui = nullptr;
    bool Gtk = false;
    /* Check and create appropriate factory. */
    if (Gtk)
    {
        ui = new GtkUIFactory();
    }
    else
    {
        ui = new QtUIFactory();
    }

    /* Use the factory to build interface. */
    Window* toolbox = ui->getToolboxWindow();
    Window* layers  = ui->getLayersWindow();
    Window* main    = ui->getMainWindow();

    /* See what have we recieved. */
    std::cout << toolbox->getToolkit() << ":" << toolbox->getType() << std::endl;
    std::cout << layers->getToolkit() << ":" << layers->getType() << std::endl;
    std::cout << main->getToolkit() << ":" << main->getType() << std::endl;

    return EXIT_SUCCESS;
}
