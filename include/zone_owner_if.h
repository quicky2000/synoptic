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
#ifndef ZONE_OWNER_IF_H
#define ZONE_OWNER_IF_H

#include <inttypes.h>

namespace synoptic
{
  class zone;

  class zone_owner_if
  {
  public:
    virtual void set_pixel(const zone &,
                           const uint32_t & p_x,
                           const uint32_t & p_y,
                           const uint32_t & p_color)=0;
    virtual uint32_t get_color_code(const uint8_t & r,
                                    const uint8_t & g,
                                    const uint8_t & b)=0;                 
    virtual void to_refresh(const zone & p_zone)=0;
  private:
  };
}
#endif // ZONE_OWNER_IF_H
//EOF
