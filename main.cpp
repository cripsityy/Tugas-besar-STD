#include "tubes.h"

int main()
{
    ListRuangan LR;
    ListPelanggan LP;
    createListRuangan(LR);
    createListPelanggan(LP);
    pilihanSelamatDatang(LR, LP);
    return 0;
}
