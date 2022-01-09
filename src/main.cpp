#include "../include/kbd_hook.hpp"

int main()
{
  auto& kh = kbd_hook_t::instance();
  return kh.get_messages();
}

