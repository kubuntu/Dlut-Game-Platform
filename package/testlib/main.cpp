#include <DgpPkgWritter>
#include <DgpPkgReader>

int main()
{
    DgpPkgWritter writter("try.dgp");
    writter.open();
    PackageMetainfo info;
    writter.write(info);
    writter.close();
    DgpPkgReader reader("try.dgp");
    reader.open();
    info = reader.read();
    reader.close();
    return 0;
}
