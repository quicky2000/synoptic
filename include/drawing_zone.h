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
#ifndef DRAWING_ZONE_H
#define DRAWING_ZONE_H

#include "display_zone.h"
#include "quicky_exception.h"
#include <map>
#include <string>
#include <sstream>

namespace synoptic
{
  class drawing_zone: public display_zone
  {
  public:
    inline drawing_zone(zone_owner_if &,
			const std::string & p_name,
			const uint32_t & p_width,
			const uint32_t & p_height);
    inline void set_pixel(const uint32_t & p_x,
			  const uint32_t & p_y,
			  const uint8_t & p_r,
			  const uint8_t & p_g,
			  const uint8_t & p_b);
  private:
    inline void internal_paint(void);
  };
  //----------------------------------------------------------------------------
  drawing_zone::drawing_zone(zone_owner_if & p_owner,
			     const std::string & p_name,
			     const uint32_t & p_width,
			     const uint32_t & p_height):
    display_zone(p_owner,p_name,p_width,p_height)
    {
    }
    //----------------------------------------------------------------------------
    void drawing_zone::internal_paint(void)
    {
    }

    //----------------------------------------------------------------------------
    void drawing_zone::set_pixel(const uint32_t & p_x,
				 const uint32_t & p_y,
				 const uint8_t & p_r,
				 const uint8_t & p_g,
				 const uint8_t & p_b)
    {
      uint32_t l_color = get_owner().get_color_code(p_r,p_g,p_b);
      display_zone::set_pixel(p_x,p_y,l_color);
    }
}

#endif // DRAWING_ZONE_H
//EOF
