#pragma once
#ifndef TEMPLATE_MENU_H
#define TEMPLATE_MENU_H

#include "Library.h"
#include <functional>
#include "Collection.h"
#include <string>

using namespace std;

template <typename T>
void run_single_template_menu(const string& title, Collection<T>& col, function<T()> selector, bool isReader);

void run_templates_menu(Library& library);

#endif