#pragma once
#define WIN_LEAN_AND_MEAN

#include <map>
#include <windows.h>

using vk_codes_t = const std::map<int, const char*>;

vk_codes_t vk_storage
{
  { VK_BACK,        "[backspace]"   },
  { VK_TAB,         "[tab]"         },
  { VK_CAPITAL,     "[caps lock]"   },
  { VK_LSHIFT,      "[left shift]"  },
  { VK_RSHIFT,      "[right shift]" },
  { VK_CONTROL,     "[ctrl]"        },
  { VK_LCONTROL,    "[left ctrl]"   },
  { VK_RCONTROL,    "[right ctrl]"  },
  { VK_MENU,        "[alt]"         },
  { VK_LWIN,        "[left win]"    },
  { VK_RWIN,        "[right win]"   },
  { VK_ESCAPE,      "[esc]"         },
  { VK_END,         "[end]"         },
  { VK_HOME,        "[home]"        },
  { VK_LEFT,        "[left]"        },
  { VK_RIGHT,       "[right]"       },
  { VK_UP,          "[up]"          },
  { VK_DOWN,        "[down]"        },
  { VK_PRIOR,       "[pg up]"       },
  { VK_NEXT,        "[pg down]"     },
  { VK_SPACE,       " "             },
  { VK_RETURN,      "\n"            },
  { VK_OEM_PERIOD,  "."             },
  { VK_DECIMAL,     "."             },
  { VK_OEM_PLUS,    "+"             },
  { VK_OEM_MINUS,   "-"             },
  { VK_ADD,         "+"             },
  { VK_SUBTRACT,    "-"             },
};