/**
Frameworks are applications (or subsystems) with "holes" in them.
Each framework specifies the infrastructure, superstructure, and flow of
control for its "domain", and the client of the framework may: exercise
the framework's default behavior "as is", extend selected pieces of the
framework, or replace selected pieces.

The Factory Method pattern addresses the notion of "creation" in the context
of frameworks. In this example, the framework knows WHEN a new document
should be created, not WHAT kind of Document to create. The "placeholder"
Application::CreateDocument() has been declared by the framework, and the
client is expected to "fill in the blank" for his/her specific document(s).
Then, when the client asks for Application::NewDocument(), the framework
will subsequently call the client's MyApplication::CreateDocument().
*/
#include <iostream>
#include <string>

using namespace std;

/* Abstract base class declared by framework */
class Document
{
    public:
        Document(string & fn) : name(fn) {}
        virtual void Open() = 0;
        virtual void Close() = 0;
        string & GetName() { return name; }
    private:
        string name;
};

/* Concrete derived class defined by client */
class MyDocument: public Document
{
    public:
        MyDocument(string & fn): Document(fn) {}
        void Open() { cout << "\tMyDocument: Open()" << endl; }
        void Close() { cout << "\tMyDocument: Close()" << endl; }
};

/* Abstract Framework declaration */
class Application
{
    public:
        Application(): _index(0) { cout << "Application: ctor" << endl; }
        /* The client will call this "entry point" of the framework */
        void NewDocument(string name)
        {
            cout << "Application: NewDocument()" << endl;
            /* Framework calls the "hole" reserved for client customization */
            _docs[_index] = CreateDocument(name);
            _docs[_index++]->Open();
        }
        void ReportDocs()
        {
          cout << "Application: ReportDocs()" << endl;
          for (int i = 0; i < _index; i++)
            cout << "   " << _docs[i]->GetName() << endl;
        }
        void OpenDocument() {}
        /* Framework declares a "hole" for the client to customize */
        virtual Document *CreateDocument(string &) = 0;
    private:
        int _index;
        /* Framework uses Document's base class */
        Document * _docs[10];
};

/* Customization of framework defined by client */
class MyApplication: public Application
{
    public:
        MyApplication() { cout << "MyApplication: ctor" << endl; }
        /* Client defines Framework's "hole" */
        Document *CreateDocument(string & fn)
        {
            cout << "\tMyApplication: CreateDocument()" << endl;
            return new MyDocument(fn);
        }
};

int main()
{
    /* Client's customization of the Framework */
    {
        MyApplication myApp;

        myApp.NewDocument("foo");
        myApp.NewDocument("bar");
        myApp.ReportDocs();
    }
}
