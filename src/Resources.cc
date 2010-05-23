// Resources.cc for Fluxbox Window Manager
// Copyright (c) 2004 - 2006 Henrik Kinnunen (fluxgen at fluxbox dot org)
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// holds main resource functions

#include "FbTk/StringUtil.hh"
#include "FbTk/Resource.hh"
#include "WinButton.hh"

#include "fluxbox.hh"

#include "Layer.hh"

#include <stdio.h>
#include <string>
#include <vector>
#ifdef HAVE_CSTRING
  #include <cstring>
#else
  #include <string.h>
#endif

using std::string;
using std::vector;

using namespace FbTk;

//-----------------------------------------------------------------
//---- accessors for int, bool, and some enums with Resource ------
//-----------------------------------------------------------------
namespace FbTk {

template<>
string FbTk::Resource<int>::
getString() const {
    char strval[256];
    sprintf(strval, "%d", **this);
    return string(strval);
}

template<>
void FbTk::Resource<int>::
setFromString(const char* strval) {
    int val;
    if (sscanf(strval, "%d", &val)==1)
        *this = val;
}

template<>
string FbTk::Resource<string>::
getString() const { return **this; }

template<>
void FbTk::Resource<string>::
setFromString(const char *strval) {
    *this = strval;
}


template<>
string FbTk::Resource<bool>::
getString() const {
    return string(**this == true ? "true" : "false");
}

template<>
void FbTk::Resource<bool>::
setFromString(char const *strval) {
    *this = (bool)!strcasecmp(strval, "true");
}


template<>
string FbTk::Resource<vector<WinButton::Type> >::
getString() const {
    string retval;
    for (size_t i = 0; i < m_value.size(); i++) {
        switch (m_value[i]) {
        case WinButton::SHADE:
            retval.append("Shade");
            break;
        case WinButton::MINIMIZE:
            retval.append("Minimize");
            break;
        case WinButton::MAXIMIZE:
            retval.append("Maximize");
            break;
        case WinButton::CLOSE:
            retval.append("Close");
            break;
        case WinButton::STICK:
            retval.append("Stick");
            break;
        case WinButton::MENUICON:
            retval.append("MenuIcon");
            break;
        default:
            break;
        }
        retval.append(" ");
    }

    return retval;
}



template<>
void FbTk::Resource<vector<WinButton::Type> >::
setFromString(char const *strval) {
    vector<string> val;
    StringUtil::stringtok(val, strval);
    //clear old values
    m_value.clear();

    std::string v;
    for (size_t i = 0; i < val.size(); i++) {
        v = FbTk::StringUtil::toLower(val[i]);
        if (v == "maximize")
            m_value.push_back(WinButton::MAXIMIZE);
        else if (v == "minimize")
            m_value.push_back(WinButton::MINIMIZE);
        else if (v == "shade")
            m_value.push_back(WinButton::SHADE);
        else if (v == "stick")
            m_value.push_back(WinButton::STICK);
        else if (v == "menuIcon")
            m_value.push_back(WinButton::MENUICON);
        else if (v == "close")
            m_value.push_back(WinButton::CLOSE);
    }
}

template<>
string FbTk::Resource<Fluxbox::TabsAttachArea>::
getString() const {
    if (m_value == Fluxbox::ATTACH_AREA_TITLEBAR)
        return "Titlebar";
    else
        return "Window";
}

template<>
void FbTk::Resource<Fluxbox::TabsAttachArea>::
setFromString(char const *strval) {
    if (strcasecmp(strval, "Titlebar")==0)
        m_value= Fluxbox::ATTACH_AREA_TITLEBAR;
    else
        m_value= Fluxbox::ATTACH_AREA_WINDOW;
}

template<>
string FbTk::Resource<unsigned int>::
getString() const {
    char tmpstr[128];
    sprintf(tmpstr, "%ul", m_value);
    return string(tmpstr);
}

template<>
void FbTk::Resource<unsigned int>::
setFromString(const char *strval) {
    if (sscanf(strval, "%ul", &m_value) != 1)
        setDefaultValue();
}


template<>
string FbTk::Resource<long long>::
getString() const {
    char tmpstr[128];
    sprintf(tmpstr, "%llu", (unsigned long long) m_value);
    return string(tmpstr);
}

template<>
void FbTk::Resource<long long>::
setFromString(const char *strval) {
    if (sscanf(strval, "%lld", &m_value) != 1)
        setDefaultValue();
}


template<>
string FbTk::Resource<Layer>::
getString() const {
    return ::Layer::getString(m_value.getNum());
}

template<>
void FbTk::Resource<Layer>::
setFromString(const char *strval) {
    string str(strval);
    int tempnum = ::Layer::getNumFromString(str);
    if (tempnum >= 0 && tempnum < ::Layer::NUM_LAYERS)
        m_value = tempnum;
    else
        setDefaultValue();
}

template<>
string FbTk::Resource<long>::
getString() const {
    char tmpstr[128];
    sprintf(tmpstr, "%ld", m_value);
    return string(tmpstr);
}

template<>
void FbTk::Resource<long>::
setFromString(const char *strval) {
    if (sscanf(strval, "%ld", &m_value) != 1)
        setDefaultValue();
}

} // end namespace FbTk
