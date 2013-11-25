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
#ifndef COLOR_ZONE_H
#define COLOR_ZONE_H

#include "zone.h"

namespace synoptic
{
  class color_zone: public zone
  {
  public:
    inline color_zone(zone_owner_if &,
		      const std::string & p_name,
                      const uint32_t & p_width,
                      const uint32_t & p_height,
                      const uint8_t & p_r,
                      const uint8_t & p_g,
                      const uint8_t & p_b);
    inline void set_color(const uint8_t & p_r,
                          const uint8_t & p_g,
                          const uint8_t & p_b);
  private:
    inline void internal_paint(void);
    uint32_t m_color;
  };

  //----------------------------------------------------------------------------
  color_zone::color_zone(zone_owner_if & p_owner,
			 const std::string & p_name,
                         const uint32_t & p_width,
                         const uint32_t & p_height,
                         const uint8_t & p_r,
                         const uint8_t & p_g,
                         const uint8_t & p_b):
    zone(p_owner,p_name,p_width,p_height),
    m_color(p_owner.get_color_code(p_r,p_g,p_b))
      {
      }
    //----------------------------------------------------------------------------
    void color_zone::internal_paint(void)
    {
      for(uint32_t l_x = 0 ; l_x < get_width() ; ++l_x)
        {
          for(uint32_t l_y = 0 ; l_y < get_height() ; ++l_y)
            {
              set_pixel(l_x,l_y,m_color);
            }
        }
    }

    //----------------------------------------------------------------------------
    void color_zone::set_color(const uint8_t & p_r,
                               const uint8_t & p_g,
                               const uint8_t & p_b)
    {
      m_color = get_owner().get_color_code(p_r,p_g,p_b);
    }
}
#endif // COLOR_ZONE_H
//EOF
