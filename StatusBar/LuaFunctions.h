
#ifndef _IR_LUA_FUNCTIONS_STATUSBAR_PLUGIN_H_
#define _IR_LUA_FUNCTIONS_STATUSBAR_PLUGIN_H_

void StatusBar_RegisterLuaFunctions(lua_State* luaState);
static int Slider_GetText(lua_State* luaState);
static int Slider_SetText(lua_State* luaState);
static int Slider_SetTipText(lua_State* luaState);

#endif