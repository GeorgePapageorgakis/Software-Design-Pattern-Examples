#include <list>
#include <iostream>
using namespace std;

//Component abstract class
class FileDescriptor {
    public:
        virtual ~FileDescriptor() {}
        virtual void traverse() const = 0; //as operation()
        virtual void add(FileDescriptor* g) {}
        virtual void remove(FileDescriptor* g) {}
};

//Leafs (leafs have no children)
class File : public FileDescriptor {
    public:
        File(const string& fileName) : m_fileName(fileName) {}
        void traverse() const { cout << "\t" << m_fileName << endl; }
    private:
        string m_fileName;
};

//Composite will contain leaf or a group of leafs
class Folder : public FileDescriptor {
    public:
        Folder(const string& folderName) : m_folderName(folderName) {}
        void traverse() const {
            cout << m_folderName << ":\n";
            // for each element in m_FileList, call traverse()
            for (list<FileDescriptor*>::const_iterator it = m_FileList.begin(); it != m_FileList.end(); ++it) {
                (*it)->traverse();
            }
        }
        void add(FileDescriptor* aFileDescriptor) {
            m_FileList.push_back(aFileDescriptor);
        }
        void remove(FileDescriptor* g) {}
    private:
        list<FileDescriptor*> m_FileList;
        string m_folderName;
};

//client
int main()
{
    File file1("Readme.txt"), file2("app.out"), file3("test.cpp");

    //pattern in action
    file2.traverse();
    file1.traverse();
    file3.traverse();
    cout << endl;

    //make a composition of leafs and simply use the same traverse() function
    Folder f("/Program Files");
    f.add(&file1);  f.add(&file2);  f.add(&file3);  f.add(&file2);

    Folder src("/Program Files/src");
    f.add(&src);
    src.add(new File("main.cpp")); src.add(new File("sort.cpp"));
    src.add(new File("main.h")); src.add(new File("a.out"));

    //pattern in action
    f.traverse();

    return 0;
}
