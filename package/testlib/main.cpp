#include <DgpPkgWritter>
#include <DgpPkgReader>

int main()
{
    DgpPkgWritter writter("try.dgp");
    writter.open();
    PackageMetainfo info;
    writter.writeMetainfo(info);
    writter.close();
    DgpPkgReader reader("try.dgp");
    reader.open();
    info = reader.readMetainfo();
    reader.close();
    return 0;
}
