#ifndef GETKEYLABELMAP_H
#define GETKEYLABELMAP_H

#include "common.h"

TKeyMap getKeyLabelMap()
{
    TKeyMap keymap;

    {
        TIntList codes;

        codes.push_back(XK_Alt_L);
        codes.push_back(XK_Alt_R);

        keymap["Alt"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Control_L);
        codes.push_back(XK_Control_R);

        keymap["Ctrl"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Shift_L);
        codes.push_back(XK_Shift_R);

        keymap["Shift"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Tab);

        keymap["Tab"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Escape);

        keymap["Esc"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_BackSpace);

        keymap["Bckspc"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Caps_Lock);

        keymap["CapsLock"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Page_Up);

        keymap["PgUp"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Page_Down);

        keymap["PgDn"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Home);

        keymap["Home"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_End);

        keymap["End"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Insert);

        keymap["Ins"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Delete);

        keymap["Del"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_comma);

        keymap[","] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_semicolon);

        keymap[";"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Return);

        keymap["Return"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_slash);

        keymap["\\"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_backslash);

        keymap["/"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_1);

        keymap["1"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_2);

        keymap["2"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_3);

        keymap["3"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_4);

        keymap["4"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_5);

        keymap["5"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_6);

        keymap["6"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_7);

        keymap["7"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_8);

        keymap["8"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_9);

        keymap["9"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_0);

        keymap["0"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_a);

        keymap["a"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_b);

        keymap["b"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_c);

        keymap["c"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_d);

        keymap["d"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_e);

        keymap["e"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_f);

        keymap["f"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_g);

        keymap["g"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_h);

        keymap["h"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_i);

        keymap["i"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_j);

        keymap["j"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_k);

        keymap["k"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_l);

        keymap["l"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_m);

        keymap["m"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_n);

        keymap["n"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_o);

        keymap["o"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_p);

        keymap["p"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_q);

        keymap["q"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_r);

        keymap["r"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_s);

        keymap["s"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_t);

        keymap["t"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_u);

        keymap["u"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_v);

        keymap["v"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_w);

        keymap["w"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_x);

        keymap["x"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_y);

        keymap["y"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_z);

        keymap["z"] = codes;
    }

    return keymap;
}

#endif // GETKEYLABELMAP_H
