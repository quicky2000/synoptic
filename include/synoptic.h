/*    This file is part of synoptic
      The aim of this software is to provide synoptic reprenstation
      utilities
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef SYNOPTIC_H
#define SYNOPTIC_H

#include "simple_gui.h"
#include "zone_owner_if.h"
#include "zone_container.h"
#include "zone_information.h"
#include "quicky_exception.h"
#include <iostream>
#include <map>
#include <set>

namespace synoptic
{
  class synoptic: protected simple_gui::simple_gui, public zone_owner_if
  {
  public:
    inline synoptic(const uint32_t & p_width,
		    const uint32_t & p_height);
    inline void set_pixel(const zone &,
                          const uint32_t & p_x,
                          const uint32_t & p_y,
                          const uint32_t & p_color);
    // Methods from zone_owner_if
    inline uint32_t get_color_code(const uint8_t & r,
				   const uint8_t & g,
				   const uint8_t & b);
    inline void paint(void);
    inline void pack(void);
    inline void to_refresh(const zone & p_zone);
    // End of methods from zone_owner_if

    inline void add_zone(const uint32_t & p_x,
                         const uint32_t & p_y,
                         zone & p_zone);
    inline void refresh(bool p_all=true);
  private:
    bool m_packed;
    zone_container m_zone_container;
    std::map<const zone * const,zone_information> m_zones;
    std::set<const zone *> m_zones_to_refresh;
  };

  #include "synoptic.hpp"
}
#endif // SYNOPTIC_H
//EOF
