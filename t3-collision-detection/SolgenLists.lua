-- SolgenLists.lua
-- This file will be used by solgen generator (Lua bindings
-- generator for Algine)

-- Enable Lua bindings generation for the listed classes,
-- since they will be used in order to draw rounded
-- background for widgets

setListMode(ListMode.Allow)
add("Widget",
    "Painter",
    "Paint",
    "Color",
    "RectF",
    "Dimen",
    "Unit")