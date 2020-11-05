// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_SLIDER
#define SSVMS_ITEM_SLIDER

#include "SSVMenuSystem/Global/Typedefs.hpp"
#include "SSVMenuSystem/Menu/ItemBase.hpp"
#include "SSVMenuSystem/Menu/Menu.hpp"

#include <functional>
#include <string>

namespace ssvms
{
    class Menu;
    class Category;

    namespace Items
    {
        class Slider final : public ItemBase
        {
        private:
            using ValueGetter = std::function<std::string()>;
            ValueGetter valueGetter;
            Action increaseAction, decreaseAction;

        public:
            Slider(Menu& mMenu, Category& mCategory, const std::string& mName,
                ValueGetter mValueGetter, Action mIncreaseAction,
                Action mDecreaseAction)
                : ItemBase{mMenu, mCategory, mName}, valueGetter{mValueGetter},
                  increaseAction{mIncreaseAction},
                  decreaseAction{mDecreaseAction}
            {
                increasable = true;
            }

            template <typename T, typename TFuncGet, typename TFuncSet>
            Slider(Menu& mMenu, Category& mCategory, const std::string& mName,
                TFuncGet mFuncGet, TFuncSet mFuncSet, T mMin, T mMax,
                T mIncrement)
                : ItemBase{mMenu, mCategory, mName},
                  valueGetter{[=]
                      {
                          return ssvu::toStr(mFuncGet());
                      }},
                  increaseAction{[=]
                      {
                          mFuncSet(ssvu::getClamped(
                              mFuncGet() + mIncrement, mMin, mMax));
                      }},
                  decreaseAction{[=]
                      {
                          mFuncSet(ssvu::getClamped(
                              mFuncGet() - mIncrement, mMin, mMax));
                      }}
            {
                increasable = true;
            }

            inline void increase() override { increaseAction(); }
            inline void decrease() override { decreaseAction(); }
            inline std::string getName() const override
            {
                return name + ": " + valueGetter();
            }
        };
    }
}

#endif
