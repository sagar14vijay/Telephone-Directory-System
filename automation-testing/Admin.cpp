#include "stdafx.h"
#include "Admin.h"
#include <string.h>

int main()
{
    return 0;
}
Admin::Admin()
{
    u = "Admin";
    p = "Admin";
}
int Admin::check(string a, string b)
{
    if (a == "Admin" && b == "Admin")
        return 1;

    else
        return 0;
}

int Admin::contactno(string contact)
{
    if (contact.length()==10)
        return 1;
    else
        return 0;
}

int Admin::pancard(string pancard)
{
    if (pancard.length()==10)
        return 1;
    else
        return 0;
}


Admin::~Admin()
{
}
