// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_GOTO
#define SSVMS_ITEM_GOTO

#include "SSVMenuSystem/Global/Typedefs.hpp"
#include "SSVMenuSystem/Menu/ItemBase.hpp"
#include "SSVMenuSystem/Menu/Menu.hpp"

#include <string>

namespace ssvms
{
    class Category;

    namespace Items
    {
        class Goto final : public ItemBase
        {
        private:
            Category& target;

        public:
            Goto(Menu& mMenu, Category& mCategory, const std::string& mName,
                Category& mTarget)
                : ItemBase{mMenu, mCategory, mName}, target(mTarget)
            {
            }
            inline void exec() override { menu.setCategory(target); }
        };
    }
}

#endif
