/*******************************************************************************
    Author: Alexey Frolov (alexwin32@mail.ru)

    This software is distributed freely under the terms of the MIT License.
    See "LICENSE" or "http://copyfree.org/content/standard/licenses/mit/license.txt".
*******************************************************************************/

#pragma once
#include <Exception.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>

namespace File
{

using Data = std::vector<int8_t>;

Data Read(const std::wstring &Path);
void Rewrite(const std::wstring &Path, const Data &FileData);

}